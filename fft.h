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


#ifndef _FFT_H_
#define _FFT_H_

#include <complex.h>

void print_cpx(complex double t);
void print_cpx_array(complex double *t, unsigned count);

#ifdef INPLACE
void fft(unsigned N, complex double *inout);
#else
void fft(unsigned N, complex double *out,
	 const complex double *in);
#endif

void fft_init(unsigned N);
void fft_cleanup();

#define clz32(x) __builtin_clz(x)

#endif
