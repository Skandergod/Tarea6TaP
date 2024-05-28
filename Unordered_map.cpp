#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <unordered_set>

std::chrono::duration<double> **ThreadTimers;

void foo(int N, int Iterations, int ThreadNumber, int intercaladas)
{
    //inicializar el dataset aqui

    int buffer = 0, bufferDel = 0, option = 0, insertRandomCount = 0, modifyRandomCount = 0, deleteRandomCount = 0;
    std::unordered_map<int, int> map;
    std::vector<int> aux;
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> startInsert;
    std::chrono::time_point<std::chrono::system_clock> endInsert;
    std::chrono::duration<double> totalInsert;
    std::chrono::time_point<std::chrono::system_clock> startModify;
    std::chrono::time_point<std::chrono::system_clock> endModify;
    std::chrono::duration<double> totalModify;
    std::chrono::time_point<std::chrono::system_clock> startDelete;
    std::chrono::time_point<std::chrono::system_clock> endDelete;
    std::chrono::duration<double> totalDelete;
    std::unordered_map<std::string, std::string> m1;

    std::srand(std::time(nullptr));
    
    for(int i = 0; i < N; i++)
    {

        map.insert({i, i+10});
        aux.insert(aux.end(), i);

    }

    if( intercaladas == 0 )
    {

        for(int i = 0; i < Iterations; i++)
        {

            buffer = aux.size();
            aux.insert(aux.end(), buffer);

            startInsert = std::chrono::system_clock::now();
            map.insert({buffer, buffer+10});
            endInsert = std::chrono::system_clock::now();

            totalInsert += endInsert - startInsert; 

        }

        for(int i = 0; i < Iterations; i++)
        {

            buffer = (rand() % aux.size()) - 1;
            bufferDel = buffer;
            buffer = aux[buffer];
            aux.erase(aux.begin()+bufferDel);

            startDelete = std::chrono::system_clock::now();
            map.erase(buffer);
            endDelete = std::chrono::system_clock::now();

            totalDelete += endDelete - startDelete; 

        }

        for(int i = 0; i < Iterations; i++)
        {

            buffer = (rand() % aux.size()) - 1;
            buffer = aux[buffer];

            startModify = std::chrono::system_clock::now();
            map[aux[buffer]] = buffer + 10; 
            endModify = std::chrono::system_clock::now();

            totalModify += endModify - startModify; 

        }


    }
    else
    {

        for(int i = 0; i < Iterations; i++)
        {

            option = rand() % 3;

            if(option == 0) //insert
            {

                buffer = aux.size();
                aux.insert(aux.end(), buffer);

                startInsert = std::chrono::system_clock::now();
                map.insert({buffer, buffer+10});
                endInsert = std::chrono::system_clock::now();

                totalInsert += endInsert - startInsert;

                insertRandomCount += 1;

            }

            if(option == 1 && !aux.empty()) //modify
            {
                
                buffer = (rand() % aux.size()) - 1;
                bufferDel = buffer;
                buffer = aux[buffer];
                aux.erase(aux.begin()+bufferDel);

                startDelete = std::chrono::system_clock::now();
                map.erase(buffer);
                endDelete = std::chrono::system_clock::now();

                totalDelete += endDelete - startDelete; 

                modifyRandomCount += 1;

            }

            if(option == 2 && !aux.empty()) //delete
            {

                buffer = (rand() % aux.size()) - 1;
                buffer = aux[buffer];

                startModify = std::chrono::system_clock::now();
                map[aux[buffer]] = buffer + 10; 
                endModify = std::chrono::system_clock::now();

                totalModify += endModify - startModify;

                deleteRandomCount += 1;

            }

        }

    }

    


    

}

int main(int argc, char *argv[]) {

    int f = 0, TotalIterations = 0, N = 0, TotalThreads = 0, intercalar = 0;

    std::thread *threads;
    std::chrono::time_point<std::chrono::system_clock> start;

    TotalThreads = _strtoi64(argv[1], 0, 10);       //Primer parametro, total de hilos a usar (preferiblemente un numero par)
    TotalIterations = _strtoi64(argv[2], 0, 10);    //Segundo parametro, cuantos experimentos en total se van a realizar
    N = _strtoi64(argv[3], 0, 10);                  //N del algoritmo a ejecutar
    intercalar = _strtoi64(argv[4], 0, 10);         //intercaladas

    threads = new std::thread[TotalThreads];
    ThreadTimers = new std::chrono::duration<double>*[TotalThreads];

    for(int i = 0; i < TotalThreads; ++i)
    {
    
        ThreadTimers[i] = new std::chrono::duration<double>[6];

    }

    start = std::chrono::system_clock::now();

    for (int i = 0; i < TotalThreads; ++i)
    {
        if(i == 0)
        {
            threads[i] = std::thread(foo, N, ( TotalIterations/TotalThreads ) + ( TotalIterations%TotalThreads ), i, intercalar);
        }
        else
        {
            threads[i] = std::thread(foo, N, TotalIterations/TotalThreads, i, intercalar);
        }
    }

    for(int i = 0; i < TotalThreads; ++i)
    {

        threads[i].join();

    }

    return 0;
}