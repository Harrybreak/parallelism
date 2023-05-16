.PHONY:clean

CFLAGS=-fopenmp
OFLAGS=-lpthread -lgomp -fopenmp

omp: omp.cpp
	g++ -o $@.o $(CFLAGS) -c $^
	g++ -o $@ $@.o $(OFLAGS)
	./$@

threads: threads.cpp
	g++ -o $@.o $(CFLAGS) -c $^
	g++ -o $@ $@.o $(OFLAGS)
	./$@

clean:
	rm -Rf *.o *.exe threads omp