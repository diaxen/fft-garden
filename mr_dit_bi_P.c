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
#include "mr_bf.h"
#include "bit_reverse.h"

/* A breadth-first implementation of the mixed radix 2/4 DIT FFT. A
   single radix2 stage is used when the transform stage is not a power
   of 4. */

static inline void
mr_dit_bi(const complex double * restrict in,
	  complex double * restrict out,
	  int log2_N)
{
  unsigned N = 1 << log2_N;

  if (log2_N & 1)      /* stage 0 */
    {
      BIT_REVERSE42_LOOP(i, r, N, {
          ct_dit_bf2_0(1, N / 2, out + i, in + r);
          ct_dit_bf2_0(1, N / 2, out + i + 2, in + r + N / 8);
      });
    }
  else                 /* stage 1 */
    {
      BIT_REVERSE42_LOOP(i, r, N, {
	  mr_dit_bf4_0(1, N / 4, out + i, in + r);
      });
    }

  /* higher stages */
  for (unsigned j = 2 - (log2_N & 1); j < log2_N; j += 2)
    {
      unsigned s = log2_N - (j + 2);
      unsigned l = 1 << j;

      for (unsigned i = 0; i < (1 << s); i++)
	{
          complex double *t = out + (i << (j + 2));
	  mr_dit_bf4_0(l, l, t, t);
          mr_dit_bf4_1(l, t + l / 2);

          unsigned k;
          for (k = 1; k < l / 2; k++)
            mr_dit_bf4(l, t + k,
                   get_twiddle(k << s, log2_N),
                   get_twiddle(k * 2 << s, log2_N),
                   get_twiddle_mr(k * 3 << s, log2_N));
          for (k++; k < l; k++)
            mr_dit_bf4(l, t + k,
                   get_twiddle(k << s, log2_N),
                   get_twiddle(k * 2 << s, log2_N),
                   get_twiddle_mr(k * 3 << s, log2_N));
	}
    }
}

void
fft(unsigned N, complex double *out,
    const complex double *in)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  mr_dit_bi(in, out, log2_N);
}

void fft_init(unsigned N)
{
  twiddles_init(N, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
