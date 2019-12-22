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


/* Lookup table for input reordering in some Conjugate Pair FFT
   algorithms */

#ifndef _CP_INPUT_LUT_H_
#define _CP_INPUT_LUT_H_

extern unsigned *cp_input_lut;	/* [N] */

void cp_input_lut_init(unsigned N);
void cp_input_lut_cleanup();

#endif
