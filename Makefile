
main: main.c
	gcc -o main main.c hash.c hash.h lru.c lru.h sec_ch.c sec_ch.h -lm
clean:
	rm -f *.o main
