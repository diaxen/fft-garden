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
#include "cp_bf.h"

/* Based on implementation of the DIT Conjuate Pair FFT proposed in
   the paper "A Depth-First Iterative Algorithm For The Conjugate Pair
   Fast Fourier Transform". */


void
fft(unsigned N, complex double * restrict out,
    const complex double * restrict in)
{
  unsigned log2_N = 31 - clz32(N);
  unsigned r = 32 - log2_N;
  uint32_t p = 0, q = 0;

  for (uint32_t hn, h = 0; h < N; h = hn) {

    /* eval binary carry sequence */
    hn = h + 2;
    unsigned c = 30 - clz32(h ^ hn);

    /* input indices */
    unsigned i0 = (p - q) >> r;
    unsigned i1 = i0 ^ (N >> 1);

    if (c & 1) {                /* stage 1 */
      out[h    ] = in[i0];
      out[h + 1] = in[i1];

    } else {			/* stage 0 */
      complex double a = in[i0];
      complex double b = in[i1];
      out[h    ] = a + b;
      out[h + 1] = a - b;
    }

    /* higher stages */
    for (unsigned j = 1 - (c & 1); j < c; j += 2)
      {
        unsigned s = 1 << j;
        unsigned r = h + 2 - 4 * s;
        unsigned t = log2_N - j - 2;
	unsigned b;

	for (b = 0; b < s; b++)
	  cp_dit_bf(s, out + r + b, get_twiddle(b << t, log2_N));
      }

    /* advance to next input index */
    uint32_t m2 = 0x20000000 >> c;
    uint32_t m1 = m2 - 1;
    uint32_t m  = p & m2;
    q = (q & m1) | m;
    p = (p & m1) | ((m ^ m2) << 1);
  }
}

void fft_init(unsigned N)
{
  twiddles_init(N / 4, N);
}

void fft_cleanup()
{
  twiddles_cleanup();
}
