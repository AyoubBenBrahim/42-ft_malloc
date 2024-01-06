MAL_DIR = ../
MAL_LIB = $(MAL_DIR)libft_malloc.so
MAL_HEADER = $(MAL_DIR)inc


all:
	@gcc test0.c -o t0
	@gcc test1.c -o t1
	@gcc test2.c -o t2
	@gcc test3.c -o t3
	@gcc test4.c -o t4
	@gcc test5.c -o t5
	@gcc test6.c -o t6

wlib:
	@gcc test0.c $(MAL_LIB) -I $(MAL_HEADER) -o t0
	@gcc test1.c $(MAL_LIB) -I $(MAL_HEADER) -o t1
	@gcc test2.c $(MAL_LIB) -I $(MAL_HEADER) -o t2
	@gcc test3.c $(MAL_LIB) -I $(MAL_HEADER) -o t3
	@gcc test4.c $(MAL_LIB) -I $(MAL_HEADER) -o t4
	@gcc test5.c $(MAL_LIB) -I $(MAL_HEADER) -o t5
	@gcc test6.c $(MAL_LIB) -I $(MAL_HEADER) -o t6

clean:
	-rm t0
	-rm t1
	-rm t2
	-rm t3
	-rm t4
	-rm t5
	-rm t6

wre: clean wlib

re: clean all