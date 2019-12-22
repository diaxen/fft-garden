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

/* A recursive implementation of the mixed radix 2/4 Cooley DIT FFT.
   A single radix2 stage is used when the transform stage is not a
   power of 4. */

static inline void
mr_dit_dr(const complex double * restrict in,
	      complex double * restrict out,
	      int s, int log2_N)
{
  unsigned l = 1 << (log2_N - s);
  unsigned stride = 1 << s;

  switch (l)
    {
    case 2:			/* last stage radix 2 */
      ct_dit_bf2_0(1, stride, out, in);
      break;

    case 4:			/* last stage radix 4 */
      mr_dit_bf4_0(1, stride, out, in);
      break;

    default:
      l >>= 2;
      mr_dit_dr(in,              out,         s + 2, log2_N);
      mr_dit_dr(in + stride,     out + l,     s + 2, log2_N);
      mr_dit_dr(in + stride * 2, out + 2 * l, s + 2, log2_N);
      mr_dit_dr(in + stride * 3, out + 3 * l, s + 2, log2_N);

      mr_dit_bf4_0(l, l, out, out);
      mr_dit_bf4_1(l, out + l / 2);

      unsigned k;
      for (k = 1; k < l / 2; k++)
        mr_dit_bf4(l, out + k,
               get_twiddle(k << s, log2_N),
               get_twiddle(k * 2 << s, log2_N),
               get_twiddle_mr(k * 3 << s, log2_N));
      for (k++; k < l; k++)
        mr_dit_bf4(l, out + k,
               get_twiddle(k << s, log2_N),
               get_twiddle(k * 2 << s, log2_N),
               get_twiddle_mr(k * 3 << s, log2_N));
    }
}

void
fft(unsigned N, complex double *out,
    const complex double *in)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  mr_dit_dr(in, out, 0, log2_N);
}

void fft_init(unsigned N)
{
  twiddles_init(N, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
