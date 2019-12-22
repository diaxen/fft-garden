
CFLAGS=-ggdb -Wall

CSRC =  twiddles.c cp_input_lut.c sr_input_lut.c sr_sched_lut.c
CHDR =  twiddles.h cp_input_lut.h sr_input_lut.h sr_sched_lut.h fft.h bit_reverse.h
LIBS = -lm

TESTS = test_ct_dit_dr \
	test_ct_dit_dr_P \
	test_ct_dit_dr_F_P \
	test_ct_dit_dr_S_P \
	test_ct_dit_dr_P_cexp \
	test_ct_dit_bi \
	test_ct_dit_bi_P \
	test_ct_dit_bi_F_P \
	test_ct_dit_bi_S_P \
	test_ct_dit_bi_N \
	test_ct_dit_bi_G \
	test_ct_dit_bi_G_P \
	test_ct_dit_bi_G_S_P \
	test_ct_dit_bi_G_F_P \
	test_ct_dit_bi_G_P_cexp \
	test_ct_dit_bi_P_cexp \
	test_ct_dif_bi_N \
	test_mr_dit_dr \
	test_mr_dit_dr_P \
	test_mr_dit_dr_F_P \
	test_mr_dit_dr_S_P \
	test_mr_dit_dr_S_F_P \
	test_mr_dit_dr_P_cexp \
	test_mr_dit_bi \
	test_mr_dit_bi_P \
	test_mr_dit_bi_F_P \
	test_mr_dit_bi_S_P \
	test_mr_dit_bi_S_F_P \
	test_mr_dit_bi_P_cexp \
	test_mr_dit_bi_G \
	test_mr_dit_bi_G_P \
	test_mr_dit_bi_G_S_P \
	test_mr_dit_bi_G_F_P \
	test_mr_dit_bi_G_S_F_P \
	test_mr_dit_bi_G_P_cexp \
	test_sr_dit_bi \
	test_sr_dit_bi_P \
	test_sr_dit_bi_F_P \
	test_sr_dit_bi_S_P \
	test_sr_dit_bi_S_F_P \
	test_sr_dit_bi_L_P_cexp \
	test_sr_dit_dr \
	test_sr_dit_dr_P \
	test_sr_dit_dr_F_P \
	test_sr_dit_dr_S_P \
	test_sr_dit_dr_S_F_P \
	test_sr_dit_dr_P_cexp \
	test_sr_dit_bi_G_L \
	test_sr_dit_bi_G_L_P \
	test_sr_dit_bi_G_L_S_P \
	test_sr_dit_bi_G_L_F_P \
	test_sr_dit_bi_G_L_S_F_P \
	test_sr_dit_bi_G_L_P_cexp \
	test_sr_dit_bi_G \
	test_sr_dit_bi_G_P \
	test_sr_dit_bi_G_F_P \
	test_sr_dit_bi_G_P_cexp \
	test_sr_dit_bi_N_G \
	test_cp_dit_di \
	test_cp_dit_di_P \
	test_cp_dit_di_S_P \
	test_cp_dit_di_F_P \
	test_cp_dit_di_P_cexp \
	test_cp_dit_dr \
	test_cp_dit_dr_P \
	test_cp_dit_dr_S_P \
	test_cp_dit_dr_F_P \
	test_cp_dit_dr_P_cexp \
	test_cp_dit_bi \
	test_cp_dit_bi_P \
	test_cp_dit_bi_S_P \
	test_cp_dit_bi_F_P \
	test_cp_dit_bi_P_cexp \
	test_cp_dit_bi_G \
	test_cp_dit_bi_G_P \
	test_cp_dit_bi_G_S_P \
	test_cp_dit_bi_G_F_P

all: $(TESTS)

test: $(TESTS)
	echo $(TESTS)
	@true $(foreach exe, $(TESTS), && echo $(exe) && ./$(exe))

$(TESTS): test.c

clean:
	rm $(TESTS)

%_ct_dit_dr: $(CSRC) $(CHDR) ct_dit_dr.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_dr.c $(LIBS) -o $@

%_ct_dit_dr_P: $(CSRC) $(CHDR) ct_dit_dr_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_dr_P.c $(LIBS) -o $@

%_ct_dit_dr_F_P: $(CSRC) $(CHDR) ct_dit_dr_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_dr_P.c $(LIBS) -D SHORT_TW -o $@

%_ct_dit_dr_S_P: $(CSRC) $(CHDR) ct_dit_dr_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_dr_S_P.c $(LIBS) -o $@

%_ct_dit_dr_P_cexp: $(CSRC) $(CHDR) ct_dit_dr_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_dr_P.c $(LIBS) -D NO_TW -o $@

%_ct_dit_bi: $(CSRC) $(CHDR) ct_dit_bi.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi.c $(LIBS) -o $@

%_ct_dit_bi_P: $(CSRC) $(CHDR) ct_dit_bi_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_P.c $(LIBS) -o $@

%_ct_dit_bi_F_P: $(CSRC) $(CHDR) ct_dit_bi_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_P.c $(LIBS) -D SHORT_TW -o $@

%_ct_dit_bi_S_P: $(CSRC) $(CHDR) ct_dit_bi_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_S_P.c $(LIBS) -o $@

%_ct_dit_bi_P_cexp: $(CSRC) $(CHDR) ct_dit_bi_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_P.c $(LIBS) -D NO_TW -o $@

%_ct_dit_bi_N: $(CSRC) $(CHDR) ct_dit_bi_N.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_N.c $(LIBS) -o $@ -D INPLACE

%_ct_dit_bi_G: $(CSRC) $(CHDR) ct_dit_bi_G.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_G.c $(LIBS) -o $@

%_ct_dit_bi_G_P: $(CSRC) $(CHDR) ct_dit_bi_G_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_G_P.c $(LIBS) -o $@

%_ct_dit_bi_G_S_P: $(CSRC) $(CHDR) ct_dit_bi_G_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_G_S_P.c $(LIBS) -o $@

%_ct_dit_bi_G_F_P: $(CSRC) $(CHDR) ct_dit_bi_G_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_G_P.c $(LIBS) -D SHORT_TW -o $@

%_ct_dit_bi_G_P_cexp: $(CSRC) $(CHDR) ct_dit_bi_G_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dit_bi_G_P.c $(LIBS) -D NO_TW -o $@

%_ct_dif_bi_N: $(CSRC) $(CHDR) ct_dif_bi_N.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) ct_dif_bi_N.c $(LIBS) -o $@ -D INPLACE

%_mr_dit_dr: $(CSRC) $(CHDR) mr_dit_dr.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_dr.c $(LIBS) -o $@

%_mr_dit_dr_P: $(CSRC) $(CHDR) mr_dit_dr_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_dr_P.c $(LIBS) -o $@

%_mr_dit_dr_F_P: $(CSRC) $(CHDR) mr_dit_dr_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_dr_P.c $(LIBS) -D SHORT_TW -o $@

%_mr_dit_dr_S_P: $(CSRC) $(CHDR) mr_dit_dr_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_dr_S_P.c $(LIBS) -o $@

%_mr_dit_dr_S_F_P: $(CSRC) $(CHDR) mr_dit_dr_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_dr_S_P.c $(LIBS) -D SHORT_TW -o $@

%_mr_dit_dr_P_cexp: $(CSRC) $(CHDR) mr_dit_dr_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_dr_P.c $(LIBS) -D NO_TW -o $@

%_mr_dit_bi: $(CSRC) $(CHDR) mr_dit_bi.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi.c $(LIBS) -o $@

%_mr_dit_bi_P: $(CSRC) $(CHDR) mr_dit_bi_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_P.c $(LIBS) -o $@

%_mr_dit_bi_F_P: $(CSRC) $(CHDR) mr_dit_bi_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_P.c $(LIBS) -D SHORT_TW -o $@

%_mr_dit_bi_S_P: $(CSRC) $(CHDR) mr_dit_bi_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_S_P.c $(LIBS) -o $@

%_mr_dit_bi_S_F_P: $(CSRC) $(CHDR) mr_dit_bi_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_S_P.c $(LIBS) -D SHORT_TW -o $@

%_mr_dit_bi_P_cexp: $(CSRC) $(CHDR) mr_dit_bi_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_P.c $(LIBS) -D NO_TW -o $@

%_mr_dit_bi_G: $(CSRC) $(CHDR) mr_dit_bi_G.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_G.c $(LIBS) -o $@

%_mr_dit_bi_G_P: $(CSRC) $(CHDR) mr_dit_bi_G_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_G_P.c $(LIBS) -o $@

%_mr_dit_bi_G_S_P: $(CSRC) $(CHDR) mr_dit_bi_G_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_G_S_P.c $(LIBS) -o $@

%_mr_dit_bi_G_F_P: $(CSRC) $(CHDR) mr_dit_bi_G_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_G_P.c $(LIBS) -D SHORT_TW -o $@

%_mr_dit_bi_G_S_F_P: $(CSRC) $(CHDR) mr_dit_bi_G_S_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_G_S_P.c $(LIBS) -D SHORT_TW -o $@

%_mr_dit_bi_G_P_cexp: $(CSRC) $(CHDR) mr_dit_bi_G_P.c ct_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) mr_dit_bi_G_P.c $(LIBS) -D NO_TW -o $@

%_sr_dit_dr: $(CSRC) $(CHDR) sr_dit_dr.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_dr.c $(LIBS) -o $@

%_sr_dit_dr_P: $(CSRC) $(CHDR) sr_dit_dr_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_dr_P.c $(LIBS) -o $@

%_sr_dit_dr_F_P: $(CSRC) $(CHDR) sr_dit_dr_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_dr_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_dr_S_P: $(CSRC) $(CHDR) sr_dit_dr_S_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_dr_S_P.c $(LIBS) -o $@

%_sr_dit_dr_S_F_P: $(CSRC) $(CHDR) sr_dit_dr_S_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_dr_S_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_dr_P_cexp: $(CSRC) $(CHDR) sr_dit_dr_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_dr_P.c $(LIBS) -D NO_TW -o $@

%_sr_dit_bi: $(CSRC) $(CHDR) sr_dit_bi_L.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_L.c $(LIBS) -o $@

%_sr_dit_bi_P: $(CSRC) $(CHDR) sr_dit_bi_L_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_L_P.c $(LIBS) -o $@

%_sr_dit_bi_F_P: $(CSRC) $(CHDR) sr_dit_bi_L_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_L_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_bi_S_P: $(CSRC) $(CHDR) sr_dit_bi_L_S_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_L_S_P.c $(LIBS) -o $@

%_sr_dit_bi_S_F_P: $(CSRC) $(CHDR) sr_dit_bi_L_S_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_L_S_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_bi_L_P_cexp: $(CSRC) $(CHDR) sr_dit_bi_L_P.c sr_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_L_P.c $(LIBS) -D NO_TW -o $@

%_sr_dit_bi_G: $(CSRC) $(CHDR) sr_dit_bi_G.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G.c $(LIBS) -o $@

%_sr_dit_bi_G_P: $(CSRC) $(CHDR) sr_dit_bi_G_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_P.c $(LIBS) -o $@

%_sr_dit_bi_G_F_P: $(CSRC) $(CHDR) sr_dit_bi_G_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_bi_G_P_cexp: $(CSRC) $(CHDR) sr_dit_bi_G_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_P.c $(LIBS) -D NO_TW -o $@

%_sr_dit_bi_N_G: $(CSRC) $(CHDR) sr_dit_bi_N_G.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_N_G.c $(LIBS) -o $@ -D INPLACE

%_sr_dit_bi_G_L: $(CSRC) $(CHDR) sr_dit_bi_G_L.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_L.c $(LIBS) -o $@

%_sr_dit_bi_G_L_P: $(CSRC) $(CHDR) sr_dit_bi_G_L_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_L_P.c $(LIBS) -o $@

%_sr_dit_bi_G_L_S_P: $(CSRC) $(CHDR) sr_dit_bi_G_L_S_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_L_S_P.c $(LIBS) -o $@

%_sr_dit_bi_G_L_F_P: $(CSRC) $(CHDR) sr_dit_bi_G_L_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_L_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_bi_G_L_S_F_P: $(CSRC) $(CHDR) sr_dit_bi_G_L_S_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_L_S_P.c $(LIBS) -D SHORT_TW -o $@

%_sr_dit_bi_G_L_P_cexp: $(CSRC) $(CHDR) sr_dit_bi_G_L_P.c
	$(CC) $(CFLAGS) $*.c $(CSRC) sr_dit_bi_G_L_P.c $(LIBS) -D NO_TW -o $@

%_cp_dit_di: $(CSRC) $(CHDR) cp_dit_di.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_di.c $(LIBS) -o $@

%_cp_dit_di_P: $(CSRC) $(CHDR) cp_dit_di_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_di_P.c $(LIBS) -o $@

%_cp_dit_di_S_P: $(CSRC) $(CHDR) cp_dit_di_S_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_di_S_P.c $(LIBS) -o $@

%_cp_dit_di_F_P: $(CSRC) $(CHDR) cp_dit_di_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_di_P.c $(LIBS) -D SHORT_TW -o $@

%_cp_dit_di_P_cexp: $(CSRC) $(CHDR) cp_dit_di_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_di_P.c $(LIBS) -D NO_TW -o $@

%_cp_dit_dr: $(CSRC) $(CHDR) cp_dit_dr.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_dr.c $(LIBS) -o $@

%_cp_dit_dr_P: $(CSRC) $(CHDR) cp_dit_dr_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_dr_P.c $(LIBS) -o $@

%_cp_dit_dr_S_P: $(CSRC) $(CHDR) cp_dit_dr_S_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_dr_S_P.c $(LIBS) -o $@

%_cp_dit_dr_F_P: $(CSRC) $(CHDR) cp_dit_dr_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_dr_P.c $(LIBS) -D SHORT_TW -o $@

%_cp_dit_dr_P_cexp: $(CSRC) $(CHDR) cp_dit_dr_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_dr_P.c $(LIBS) -D NO_TW -o $@

%_cp_dit_bi: $(CSRC) $(CHDR) cp_dit_bi_L.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_L.c $(LIBS) -o $@

%_cp_dit_bi_P: $(CSRC) $(CHDR) cp_dit_bi_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_P.c $(LIBS) -o $@

%_cp_dit_bi_S_P: $(CSRC) $(CHDR) cp_dit_bi_S_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_S_P.c $(LIBS) -o $@

%_cp_dit_bi_F_P: $(CSRC) $(CHDR) cp_dit_bi_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_P.c $(LIBS) -D SHORT_TW -o $@

%_cp_dit_bi_G: $(CSRC) $(CHDR) cp_dit_bi_G_L.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_G_L.c $(LIBS) -o $@

%_cp_dit_bi_G_P: $(CSRC) $(CHDR) cp_dit_bi_G_L_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_G_L_P.c $(LIBS) -o $@

%_cp_dit_bi_G_S_P: $(CSRC) $(CHDR) cp_dit_bi_G_L_S_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_G_L_S_P.c $(LIBS) -o $@

%_cp_dit_bi_G_F_P: $(CSRC) $(CHDR) cp_dit_bi_G_L_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_G_L_P.c $(LIBS) -D SHORT_TW -o $@

%_cp_dit_bi_P_cexp: $(CSRC) $(CHDR) cp_dit_bi_P.c cp_bf.h
	$(CC) $(CFLAGS) $*.c $(CSRC) cp_dit_bi_P.c $(LIBS) -D NO_TW -o $@
