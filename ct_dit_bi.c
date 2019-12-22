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
   radix 2 Cooley Tukey DIT FFT */

static inline void
ct_fft_bi(const complex double * restrict in,
	   complex double * restrict out,
	   int log2_N)
{
  unsigned N = 1 << log2_N;

  /* stage 0 */
  BIT_REVERSE2_LOOP(i, j, N, {
      ct_dit_bf2_0(1, N / 2, out + i, in + j);
  });

  /* stages 1 to log2_N - 1 */
  for (unsigned j = 1; j < log2_N; j++)
    {
      unsigned s = log2_N - j - 1;
      unsigned l = 1 << j;

      for (unsigned i = 0; i < (1 << s); i++)
	{
	  complex double *t = out + (i << (j + 1));

          for (unsigned k = 0; k < l; k++)
            ct_dit_bf2(l, t + k, get_twiddle(k << s, log2_N));
	}
    }
}

void
fft(unsigned N, complex double *out,
    const complex double *in)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  ct_fft_bi(in, out, log2_N);
}

void fft_init(unsigned N)
{
  twiddles_init(N / 2, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
