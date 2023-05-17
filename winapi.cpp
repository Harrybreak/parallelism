#include <Windows.h>
#include <process.h>
#include <iostream>
#include <chrono>
#define T   50
#define N   1000000
#define NPM 1000000.0

using namespace std;

void f(void* data)
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

int main(int argc, char* args[])
{
    HANDLE ths[T] = {NULL};

    chrono::system_clock::time_point start = chrono::system_clock::now();

    for (size_t k = 0 ; k < T ; k++)                // Create
        ths[k] = (HANDLE)_beginthread(&f, 0, 0);
    for (size_t k = 0 ; k < T ; k++)                // Join
        WaitForSingleObject(ths[k], INFINITE);
    for (size_t k = 0 ; k < T ; k++)                // Delete
        CloseHandle(ths[k]);
    for (size_t k = 0 ; k < T ; k++)                // Create
        ths[k] = (HANDLE)_beginthread(&f, 0, 0);
    for (size_t k = 0 ; k < T ; k++)                // Join
        WaitForSingleObject(ths[k], INFINITE);
    for (size_t k = 0 ; k < T ; k++)                // Delete
        CloseHandle(ths[k]);

    chrono::duration<clock_t, nano> stop = chrono::system_clock::now() - start;

    cout << "Time of running : " << static_cast<double>(stop.count()) / NPM << "ms" << endl;

    return 0;
}
