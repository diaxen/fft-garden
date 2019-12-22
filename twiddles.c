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


#include "fft.h"

#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

complex double *twiddles;
complex double *twiddles_sr;

void twiddles_init(unsigned l, unsigned N)
{
#ifdef SHORT_TW
  l = N / 8 + 1;
#endif
#ifndef NO_TW
  twiddles = aligned_alloc(256, l * sizeof(complex double));
  assert(twiddles);

  for (unsigned i = 0; i < l; i++)
    twiddles[i] = cexp(-2 * M_PI * I * i / N);
#endif
}

void twiddles_sr_init(unsigned l, unsigned N)
{
#ifndef NO_TW
# ifdef SHORT_TW
  twiddles_init(N / 8, N);
# else
  twiddles = aligned_alloc(256, l * sizeof(complex double));
  twiddles_sr = aligned_alloc(256, l * sizeof(complex double));
  assert(twiddles);

  for (unsigned i = 0; i < l; i++)
    {
      twiddles[i]    = cexp(-2 * M_PI * I * i     / N);
      twiddles_sr[i] = cexp(-2 * M_PI * I * i * 3 / N);
    }

# endif
#endif
}

void twiddles_cleanup()
{
#ifndef NO_TW
  free(twiddles);
#endif
}
