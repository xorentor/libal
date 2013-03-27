all:
	cc -O2 -Wall -c libal.c
	ar -cvq libal.a libal.o

clean:
	rm libal.o libal.a
