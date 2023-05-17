.PHONY:clean

CFLAGS=-fopenmp -fexceptions
OFLAGS=-lpthread -lgomp -fopenmp -fexceptions -O2

all:
	./omp
	./winapi
	./threads

omp: omp.cpp
	g++ -o $@.o $(CFLAGS) -c $^
	g++ -o $@ $@.o $(OFLAGS)
	./$@

threads: threads.cpp
	g++ -o $@.o $(CFLAGS) -c $^
	g++ -o $@ $@.o $(OFLAGS)
	./$@

winapi: winapi.cpp
	g++ -o $@.o $(CFLAGS) -c $^
	g++ -o $@ $@.o $(OFLAGS)
	./$@

clean:
	rm -Rf *.o *.exe threads omp winapi