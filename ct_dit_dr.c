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

/* A recursive implementation of the radix 2 Cooley Tukey DIT FFT */

static inline void
ct_fft_dr(const complex double * restrict in,
           complex double * restrict out,
           int s, int log2_N)
{
  unsigned l = 1 << (log2_N - s - 1);
  unsigned stride = 1 << s;

  switch (l)
    {
    case 1:                     /* size 2 base case  */
      ct_dit_bf2_0(1, stride, out, in);
      break;

    default:
      ct_fft_dr(in, out, s + 1, log2_N);
      ct_fft_dr(in + stride, out + l, s + 1, log2_N);

      for (unsigned k = 0; k < l; k++)
        ct_dit_bf2(l, out + k, get_twiddle(k << s, log2_N));
    }
}

void
fft(unsigned N, complex double *out,
    const complex double *in)
{
  unsigned log2_N = 31 - __builtin_clz(N);
  ct_fft_dr(in, out, 0, log2_N);
}

void fft_init(unsigned N)
{
  twiddles_init(N / 2, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
