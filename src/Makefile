main: main.o txtio.o del_sent.o txted.o dialog.o cmp.o
	gcc main.o txtio.o del_sent.o txted.o dialog.o cmp.o -o main

main.o: main.c
	gcc -c main.c

txtio.o: txtio.c
	gcc -c txtio.c

del_sent.o: del_sent.c
	gcc -c del_sent.c

txted.o: txted.c
	gcc -c txted.c

dialog.o: dialog.c
	gcc -c dialog.c

cmp.o: cmp.c
	gcc -c cmp.c

clean:
	rm *.o
