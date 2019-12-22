/*
    Written in 2019 by Alexandre Becoulet <alexandre.becoulet@free.fr>

    To the extent possible under law, the author(s) have dedicated all
    copyright and related and neighboring rights to this software to
    the public domain worldwide. This software is distributed without
    any warranty.

    You should have received a copy of the CC0 Public Domain
    Dedication along with this software. If not, see
    http://creativecommons.org/publicdomain/zero/1.0/
*/


#include "sr_sched_lut.h"
#include "fft.h"

#include <stdlib.h>
#include <assert.h>

unsigned *sr_sched_cnt;
unsigned *sr_sched_off;


void sr_sched_lut_init(unsigned N)
{
  unsigned log2_N = 31 - clz32(N);
  unsigned i, j;

  static const unsigned jacobsthal[32] = {
    0,1,1,3,5,11,21,43,85,171,341,683,1365,2731,5461,10923,21845,
    43691,87381,174763,349525,699051,1398101,2796203,5592405,
    11184811,22369621,44739243,89478485,178956971,357913941
  };

  sr_sched_cnt = malloc(log2_N * sizeof(*sr_sched_cnt));
  assert(sr_sched_cnt);

  for (i = 0; i < log2_N; i++)
    sr_sched_cnt[i] = jacobsthal[log2_N - i];

  sr_sched_off = malloc((sr_sched_cnt[0] + 1) * sizeof(*sr_sched_off));
  assert(sr_sched_off);

  for (j = i = 0; j < sr_sched_cnt[0]; i++)
    if (__builtin_clz(i ^ (i + 1)) & 1)
      sr_sched_off[j++] = i;

  sr_sched_off[j] = N;
}

void sr_sched_lut_cleanup()
{
  free(sr_sched_cnt);
  free(sr_sched_off);
}
