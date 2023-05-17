#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#define T   50
#define N   1000000
#define NPM 1000000.0
using namespace std;
void f()
{
    double pi_over_4 = 0.0;
    const double n = N;
    size_t k = 0;
    for (k = 0 ; k < N ; k++)
    {
        double x = (double)k;
        pi_over_4 = pi_over_4 + n/(n*n + x*x);
    }
}
int main()
{
    chrono::system_clock::time_point start = chrono::system_clock::now();

    #pragma omp parallel num_threads(T)
    #pragma omp parallel
    {
        #pragma omp task
        f();
        #pragma omp taskwait
        #pragma omp task
        f();
        #pragma omp taskwait
    }

    chrono::duration<clock_t, nano> stop = chrono::system_clock::now() - start;

    cout << "Time of running : " << static_cast<double>(stop.count()) / NPM << "ms" << endl;

    return 0;
}
