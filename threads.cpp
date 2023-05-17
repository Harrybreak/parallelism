#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
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
    vector<thread> ths;

    chrono::system_clock::time_point start = chrono::system_clock::now();

    for (size_t k = 0 ; k < T ; k++)    // Create
        ths.push_back(thread(f));
    for (size_t k = 0 ; k < T ; k++)    // Join
        ths[k].join();
    ths.clear();                        // Erase

    for (size_t k = 0 ; k < T ; k++)    // Create
        ths.push_back(thread(f));
    for (size_t k = 0 ; k < T ; k++)    // Join
        ths[k].join();
    ths.clear();                        // Erase

    chrono::duration<clock_t, nano> stop = chrono::system_clock::now() - start;

    cout << "Time of running : " << static_cast<double>(stop.count()) / NPM << "ms" << endl;

    return 0;
}
