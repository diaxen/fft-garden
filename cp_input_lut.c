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


#include "cp_input_lut.h"
#include "fft.h"

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

unsigned *cp_input_lut;


void cp_input_lut_init(unsigned N)
{
  unsigned log2_N = 31 - clz32(N);
  unsigned r = 32 - log2_N;
  uint32_t p = 0, q = 0;

  cp_input_lut = malloc(N / 2 * sizeof(*cp_input_lut));
  assert(cp_input_lut);

  for (uint32_t hn, h = 0; h < N; h = hn) {

    /* eval binary carry sequence */
    hn = h + 2;
    unsigned c = 30 - clz32(h ^ hn);

    /* input indices */
    unsigned i0 = (p - q) >> r;

    cp_input_lut[h / 2] = i0;

    /* advance to next input index */
    uint32_t m2 = 0x20000000 >> c;
    uint32_t m1 = m2 - 1;
    uint32_t m  = p & m2;
    q = (q & m1) | m;
    p = (p & m1) | ((m ^ m2) << 1);
  }
}

void cp_input_lut_cleanup()
{
  free(cp_input_lut);
}
