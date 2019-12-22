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


#include "sr_input_lut.h"
#include "fft.h"

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

unsigned *sr_input_lut;


static void
sr_lut_dr(unsigned log2_N, unsigned out,
	   unsigned l, unsigned i)
{
  unsigned is = 1 << (log2_N - l);
  unsigned os = 1 << (l - 2);

  switch (l)
    {
    case 1:
      sr_input_lut[out / 2] = i;
      break;

    case 2:
      sr_lut_dr(log2_N, out, 1, i);
      sr_input_lut[1 + out / 2] = i + is;
      break;

    default:
      sr_lut_dr(log2_N, out, l - 1, i);
      sr_lut_dr(log2_N, out + os * 2, l - 2, i + is);
      sr_lut_dr(log2_N, out + 3 * os, l - 2, i + 3 * is);
    }
}

void sr_input_lut_init(unsigned N)
{
  unsigned log2_N = 31 - clz32(N);

  sr_input_lut = malloc(N / 2 * sizeof(*sr_input_lut));
  assert(sr_input_lut);

  sr_lut_dr(log2_N, 0, log2_N, 0);
}

void sr_input_lut_cleanup()
{
  free(sr_input_lut);
}
