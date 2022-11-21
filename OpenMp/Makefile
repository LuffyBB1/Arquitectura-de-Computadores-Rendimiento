GCC = gcc
GFLAGS = -ansi -pedantic -Wall -std=c99 -D_POSIX_C_SOURCE=199309L
PROGRAMAS = MM1cOMP
FLAGS = -fopenmp

MM1cOMP:
	$(GCC) $(FLAGS) module.c -c -D_POSIX_C_SOURCE=199309L $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS)
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS)

clean:
	$(RM) $(THEPROGS) *.o
