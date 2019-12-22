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


/*  Butterflies for the radix 2 Cooley-Tukey FFT */

#ifndef _CT_BF_H_
#define _CT_BF_H_

#include <complex.h>
#include <math.h>

static inline void
ct_dit_bf2_0(unsigned so, unsigned si,
	 complex double * out,
         const complex double * in)
{
  complex double a = in[0];
  complex double b = in[si];
  out[0] = a + b;
  out[so] = a - b;
}

static inline void
ct_dit_bf2_pi4(unsigned s,
           complex double * restrict out)
{
  complex double a = out[0];
  complex double b = out[s];
  complex double t = CMPLX(M_SQRT1_2 * (creal(b) + cimag(b)),
                           M_SQRT1_2 * (cimag(b) - creal(b)));
  out[0] = a + t;
  out[s] = a - t;
}

static inline void
ct_dit_bf2_3pi4(unsigned s,
             complex double * restrict out)
{
  complex double a = out[0];
  complex double b = out[s];
  complex double t = CMPLX(M_SQRT1_2 * (-creal(b) + cimag(b)),
                           M_SQRT1_2 * (-cimag(b) - creal(b)));
  out[0] = a + t;
  out[s] = a - t;
}

static inline void
ct_dit_bf2_pi2(unsigned s,
           complex double * restrict out)
{
  complex double a = out[0];
  complex double b = out[s];
  complex double t = CMPLX(cimag(b), -creal(b));
  out[0] = a + t;
  out[s] = a - t;
}

static inline void
ct_dit_bf2(unsigned s,
       complex double * restrict out,
       complex double w)
{
  complex double a = out[0];
  complex double b = out[s] * w;
  out[0] = a + b;
  out[s] = a - b;
}

static inline void
ct_dif_bf2_0(unsigned so, unsigned si,
	 complex double * out,
         const complex double * in)
{
  complex double a = in[0];
  complex double b = in[si];
  out[0] = a + b;
  out[so] = a - b;
}

static inline void
ct_dif_bf2(unsigned s,
       complex double * restrict out,
       complex double w)
{
  complex double a = out[0];
  complex double b = out[s];
  out[0] = a + b;
  out[s] = (a - b) * w;
}

#endif
