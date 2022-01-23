all: av_l_sort.o check_index.o convert_sent.o del_and_shift.o del_m5_l2.o del_sent.o Input.o main.o mask_check.o Output.o menu.o
	gcc av_l_sort.o check_index.o convert_sent.o del_and_shift.o del_m5_l2.o del_sent.o Input.o main.o mask_check.o Output.o menu.o -o cw
av_l_sort.o: av_l_sort.c
	gcc -c av_l_sort.c
check_index.o: check_index.c
	gcc -c check_index.c
convert_sent.o: convert_sent.c
	gcc -c convert_sent.c
del_and_shift.o: del_and_shift.c
	gcc -c del_and_shift.c
del_m5_l2.o: del_m5_l2.c
	gcc -c del_m5_l2.c
del_sent.o: del_sent.c
	gcc -c del_sent.c
Input.o: Input.c
	gcc -c Input.c
main.o: main.c
	gcc -c main.c
mask_check.o: mask_check.c
	gcc -c mask_check.c
Output.o: Output.c
	gcc -c Output.c
menu.o: menu.c
	gcc -c menu.c

clean:
	rm -r *.o
