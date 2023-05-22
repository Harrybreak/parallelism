// OPENMP
#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#define NPM 1000000.0
using namespace std;
void f(size_t x)
{
    double pi_over_4 = 0.0;
    const double n = (double)x;
    size_t k = 0;
    for (k = 0 ; k < x ; k++)
    {
        double x = (double)k;
        pi_over_4 = pi_over_4 + n/(n*n + x*x);
    }
}
int main()
{
    size_t n[4] = {10000, 100000, 1000000, 10000000};
    size_t t[4] = {12, 24, 48, 96};
    for (const size_t N : n) {
    for (const size_t T : t) {
    cout << "===========================" << endl;
    cout << "| N = " << N << " | T = " << T << " |" << endl;
    double ave = 0.0;
    for (size_t j = 0 ; j < 12 ; j++) {

    chrono::system_clock::time_point start = 
    chrono::system_clock::now();
    
    #pragma omp parallel num_threads(T)
    #pragma omp parallel
    {
        #pragma omp task
        f(N);
        #pragma omp taskwait
        #pragma omp task
        f(N);
        #pragma omp taskwait
    }

    chrono::duration<clock_t, nano> stop = 
    chrono::system_clock::now() - start;

    if (j>1)
        ave += static_cast<double>(stop.count()) / NPM;
    cout << "Time of running : " <<
    static_cast<double>(stop.count()) / NPM << "ms" << endl;
    } cout << "Average : " << ave / 10.0 << "ms" << endl;
    }}
    return 0;
}

