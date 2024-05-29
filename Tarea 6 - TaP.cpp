#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <unordered_set>

std::vector < std::vector< std::chrono::duration<double> > > ThreadTimers;

void foo(int N, int Iterations, int ThreadNumber, int intercaladas)
{

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

    std::cout << "Entre con i = " << Iterations << std::endl;

    for (int i = 0; i < N; i++)
    {

        map.insert({ i, i + 10 });
        aux.insert(aux.end(), i);

    }

    if (intercaladas == 0)
    {

        for (int i = 0; i < Iterations; ++i)
        {

            //std::cout << "Hilo 0 Insercion " << i << std::endl;

            buffer = aux.size();
            aux.insert(aux.end(), buffer);

            startInsert = std::chrono::system_clock::now();
            map.insert({ buffer, buffer + 10 });
            endInsert = std::chrono::system_clock::now();

            totalInsert += endInsert - startInsert;

        }

        //std::cout << "Termine de hacer Inserciones"<< std::endl;

        for (int i = 0; i < Iterations; ++i)
        {

            /*
            if(ThreadNumber == 0)
                std::cout << "Hilo 0 Busqueda " << i << std::endl;
            */

            buffer = (rand() % aux.size());
            bufferDel = buffer;
            buffer = aux[buffer];

            aux[bufferDel] = aux[aux.size() - 1];
            aux[aux.size() - 1] = buffer;

            aux.pop_back();

            startDelete = std::chrono::system_clock::now();
            map.erase(buffer);
            endDelete = std::chrono::system_clock::now();

            totalDelete += endDelete - startDelete;

        }

        //std::cout << "Termine de hacer Busquedas"<< std::endl;

        for (int i = 0; i < Iterations; ++i)
        {
            /*
            if(ThreadNumber == 0)
                std::cout << "Hilo 0 Delete " << i << std::endl;
            */

            buffer = (rand() % aux.size());
            buffer = aux[buffer];

            startModify = std::chrono::system_clock::now();
            map[buffer] = buffer + 10;
            endModify = std::chrono::system_clock::now();

            totalModify += endModify - startModify;

        }


    }
    else
    {

        for (int i = 0; i < Iterations; ++i)
        {

            option = rand() % 3;

            if (option == 0) //insert
            {

                buffer = aux.size();
                aux.insert(aux.end(), buffer);

                startInsert = std::chrono::system_clock::now();
                map.insert({ buffer, buffer + 10 });
                endInsert = std::chrono::system_clock::now();

                totalInsert += endInsert - startInsert;

                insertRandomCount += 1;

            }

            if (option == 1 && !aux.empty()) //modify
            {

                buffer = (rand() % aux.size());
                bufferDel = buffer;
                buffer = aux[buffer];

                aux[bufferDel] = aux[aux.size() - 1];
                aux[aux.size() - 1] = buffer;

                aux.pop_back();

                startDelete = std::chrono::system_clock::now();
                map.erase(buffer);
                endDelete = std::chrono::system_clock::now();

                totalDelete += endDelete - startDelete;

                deleteRandomCount += 1;

            }

            if (option == 2 && !aux.empty()) //delete
            {

                buffer = (rand() % aux.size());
                buffer = aux[buffer];

                startModify = std::chrono::system_clock::now();
                map[buffer] = buffer + 10;
                endModify = std::chrono::system_clock::now();

                totalModify += endModify - startModify;

                modifyRandomCount += 1;

            }

        }

    }


    ThreadTimers[ThreadNumber].push_back(totalInsert);    //Tiempo total de todas las operaciones de insercion
    ThreadTimers[ThreadNumber].push_back(totalModify);    //Tiempo total de todas las operaciones de busqueda y modificacion
    ThreadTimers[ThreadNumber].push_back(totalDelete);    //Tiempo total de todas las operaciones de borrar

    if (intercaladas == 0)
    {

        ThreadTimers[ThreadNumber].push_back(totalInsert / Iterations); //Tiempo Promedio de cada insercion
        ThreadTimers[ThreadNumber].push_back(totalModify / Iterations); //Tiempo Promedio de cada busqueda y modifcacion
        ThreadTimers[ThreadNumber].push_back(totalDelete / Iterations); //Tiempo Promedio de cada borrar

    }
    else
    {

        ThreadTimers[ThreadNumber].push_back(totalInsert / insertRandomCount);  //Tiempo Promedio de cada insercion
        ThreadTimers[ThreadNumber].push_back(totalModify / modifyRandomCount);  //Tiempo Promedio de cada busqueda y modifcacion
        ThreadTimers[ThreadNumber].push_back(totalDelete / deleteRandomCount);  //Tiempo Promedio de cada borrar

    }

    std::cout << "Tiempos Para i = " << Iterations << " y N = " << N << std::endl;
    std::cout << "Tiempo Total de inserciones del foo " << ThreadNumber << " es de " << std::chrono::duration_cast<std::chrono::milliseconds>(ThreadTimers[ThreadNumber][0]).count() << " ms" << std::endl;
    std::cout << "Tiempo Total de Busqueda del foo " << ThreadNumber << " es de " << std::chrono::duration_cast<std::chrono::milliseconds>(ThreadTimers[ThreadNumber][1]).count()  << " ms" << std::endl;
    std::cout << "Tiempo Total de Delete del foo " << ThreadNumber << " es de " << std::chrono::duration_cast<std::chrono::milliseconds>(ThreadTimers[ThreadNumber][2]).count() << " ms" << std::endl;
    std::cout << "Tiempo promedio de inserciones del foo " << ThreadNumber << " es de " << std::chrono::duration_cast<std::chrono::milliseconds>(ThreadTimers[ThreadNumber][3]).count()  << " ms" << std::endl;
    std::cout << "Tiempo promedio de Busqueda del foo " << ThreadNumber << " es de " << std::chrono::duration_cast<std::chrono::milliseconds>(ThreadTimers[ThreadNumber][4]).count() << " ms" << std::endl;
    std::cout << "Tiempo promedio de Busqueda del foo " << ThreadNumber << " es de " << std::chrono::duration_cast<std::chrono::milliseconds>(ThreadTimers[ThreadNumber][5]).count() << " ms" << std::endl;
    std::cout << std::endl;
    //std::cout << "Hilo " << ThreadNumber << " Ejecucion Terminada"<< std::endl;

    map.clear();
    aux.clear();

}

int main(int argc, char* argv[]) {

    int f = 0, TotalIterations = 0, N = 0, TotalThreads = 0, intercalar = 0;
    std::vector< std::chrono::duration<double> > arr;


    N = 10;                  //N del algoritmo a ejecutar
    intercalar = 0;         //intercaladas

    for (int i = 0; i < 6; i++)
    {

        ThreadTimers.push_back(arr);

    }

    std::srand(std::time(nullptr));

    foo(N, 100, 0, intercalar);

    std::cout << "Termine foo" << std::endl;

    foo(N, 1000, 1, intercalar);

    std::cout << "Termine foo" << std::endl;

    foo(N, 10000, 2, intercalar);
    foo(N, 100000, 3, intercalar);
    foo(N, 1000000, 4, intercalar);
    foo(N, 10000000, 5, intercalar);

    return 0;
}