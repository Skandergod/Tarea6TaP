#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
#include <thread>
#include <chrono>
#include <unordered_map>
std::chrono::time_point<std::chrono::system_clock> *ThreadTimers;

void foo(int N, int Iterations, int ThreadNumber)
{
    //inicializar el dataset aqui

    std::chrono::time_point<std::chrono::system_clock> start;
    std::unordered_map<std::string, std::string> m1;
    
    start = std::chrono::system_clock::now();

    ThreadTimers[ThreadNumber] = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = ThreadTimers[ThreadNumber] - start;

    std::cout.flush();
    std::cout << "Soy el Thread Numero " << ThreadNumber + 1 << " y me ejecute en: " << elapsed_seconds.count() << " segundos" << std::endl;
    std::cout.flush();

}

int main(int argc, char *argv[]) {

    int f, TotalIterations, N, TotalThreads = 0;

    std::thread *threads;
    std::chrono::time_point<std::chrono::system_clock> start;

    TotalThreads = _strtoi64(argv[1], 0, 10);       //Primer parametro, total de hilos a usar (preferiblemente un numero par)
    TotalIterations = _strtoi64(argv[2], 0, 10);    //Segundo parametro, cuantos experimentos en total se van a realizar
    N = _strtoi64(argv[3], 0, 10);                  //N del algoritmo a ejecutar

    threads = new std::thread[TotalThreads];
    ThreadTimers = new std::chrono::time_point<std::chrono::system_clock>[TotalThreads];

    start = std::chrono::system_clock::now();

    for (int i = 0; i < TotalThreads; ++i)
    {
        if(i == 0)
        {
            threads[i] = std::thread(foo, N, ( TotalIterations/TotalThreads ) + ( TotalIterations%TotalThreads ), i);
        }
        else
        {
            threads[i] = std::thread(foo, N, TotalIterations/TotalThreads, i);
        }
    }

    for(int i = 0; i < TotalThreads; ++i)
    {

        threads[i].join();

    }

    return 0;
}