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


/* Radix-4 butterflies for the Mixed Radix FFT */

#ifndef _MR_BF_H_
#define _MR_BF_H_

#include <complex.h>
#include <math.h>

static inline void
mr_dit_bf4_0(unsigned so, unsigned si,
         complex double * out,
         const complex double * in)
{
  complex double a = in[0     ];
  complex double b = in[si    ];
  complex double c = in[si * 2];
  complex double d = in[si * 3];
  complex double e = a + c;
  complex double f = a - c;
  complex double g = b + d;
  complex double j = (b - d) * I;
  out[0     ] = e + g;
  out[so    ] = f - j;
  out[so * 2] = e - g;
  out[so * 3] = f + j;
}

static inline void
mr_dit_bf4_1(unsigned s,
         complex double * restrict out)
{
  complex double a = out[0];
  complex double c = out[s * 2] * -I;
  complex double b = out[s] * M_SQRT1_2;
  complex double d = out[s * 3] * M_SQRT1_2;
  b = CMPLX(cimag(b) + creal(b), cimag(b) - creal(b));
  d = CMPLX(cimag(d) - creal(d), -cimag(d) - creal(d));
  complex double e = a + c;
  complex double f = a - c;
  complex double g = b + d;
  complex double j = (b - d) * I;
  out[0    ] = e + g;
  out[s    ] = f - j;
  out[s * 2] = e - g;
  out[s * 3] = f + j;
}

static inline void
mr_dit_bf4(unsigned s,
       complex double * restrict out,
       complex double w1,
       complex double w2,
       complex double w3)
{
  complex double a = out[0    ];
  complex double b = out[s    ] * w1;
  complex double c = out[s * 2] * w2;
  complex double d = out[s * 3] * w3;
  complex double e = a + c;
  complex double f = a - c;
  complex double g = b + d;
  complex double j = (b - d) * I;
  out[0    ] = e + g;
  out[s    ] = f - j;
  out[s * 2] = e - g;
  out[s * 3] = f + j;
}

#endif
