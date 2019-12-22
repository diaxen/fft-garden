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


/* Lookup table for butterfly scheduling in some Split-Radix and
   Conjugate Pair FFT algorithms */

#ifndef _SR_SCHED_LUT_H_
#define _SR_SCHED_LUT_H_

/* number of blocks of butterflies for each stage */
extern unsigned *sr_sched_cnt;         /* [log2(N)] */

/* offset of block for stage 0 */
extern unsigned *sr_sched_off;         /* [N] */

void sr_sched_lut_init(unsigned N);
void sr_sched_lut_cleanup();

#endif
