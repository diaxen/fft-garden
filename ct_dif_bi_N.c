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
#include "twiddles.h"
#include "ct_bf.h"
#include "bit_reverse.h"

/* A breadth-first implementation of the
   radix 2 Cooley Tukey DIF FFT.

   See ct_dit_bi_N.c for the DIT variant.
*/

static inline void
ct_fft_bi(complex double * restrict inout,
	  int log2_N)
{
  unsigned N = 1 << log2_N;

  /* stages 0 to log2_N - 1 */
  for (int j = log2_N - 1; j >= 0; j--)
    {
      unsigned s = log2_N - j - 1;
      unsigned l = 1 << j;

      for (unsigned i = 0; i < (1 << s); i++)
	{
	  complex double *t = inout + (i << (j + 1));

          for (unsigned k = 0; k < l; k++)
            ct_dif_bf2(l, t + k, get_twiddle(k << s, log2_N));
	}
    }

  BIT_REVERSE_SWAP_LOOP(i, j, N, {
      double complex t = inout[i];
      inout[i] = inout[j];
      inout[j] = t;
  });
}

void
fft(unsigned N, complex double *inout)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  ct_fft_bi(inout, log2_N);
}

void fft_init(unsigned N)
{
  twiddles_init(N / 2, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
