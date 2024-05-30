#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>
#include <chrono>
#include <unordered_map>
#include <map>
#include <vector>
#include <unordered_set>
#include <cstddef>
#include <iomanip>
#include <numeric>

std::vector < std::vector< float > > ThreadTimers;

void foo(int N, int Iterations, int ThreadNumber, int intercaladas)
{

    int buffer = 0, option = 0, bufferDel = 0, insertCount = 0, modifyCount = 0, deleteCount = 0, insertCount2 = 0, modifyCount2 = 0, deleteCount2 = 0;
    std::unordered_map<int, int> map;
    std::map<int, int> map2;
    std::vector<int> aux;
    std::chrono::duration<double, std::milli> timeBuffer;
    std::chrono::time_point<std::chrono::high_resolution_clock> startInsert;
    std::chrono::time_point<std::chrono::high_resolution_clock> endInsert;
    std::vector<std::chrono::duration<double, std::milli>> totalInsert;
    std::vector<std::chrono::duration<double, std::milli>> totalInsert2;
    std::chrono::time_point<std::chrono::high_resolution_clock> startModify;
    std::chrono::time_point<std::chrono::high_resolution_clock> endModify;
    std::vector<std::chrono::duration<double, std::milli>> totalModify;
    std::vector<std::chrono::duration<double, std::milli>> totalModify2;
    std::chrono::time_point<std::chrono::high_resolution_clock> startDelete;
    std::chrono::time_point<std::chrono::high_resolution_clock> endDelete;
    std::vector<std::chrono::duration<double, std::milli>> totalDelete;
    std::vector<std::chrono::duration<double, std::milli>> totalDelete2;
    double timeTotalInsert = 0, timeTotalModify = 0, timeTotalDelete = 0, promInserts = 0, promModify = 0, promDelete = 0;
    double timeTotalInsert2 = 0, timeTotalModify2 = 0, timeTotalDelete2 = 0, promInserts2 = 0, promModify2 = 0, promDelete2 = 0;

    for (int i = 0; i < N; i++)
    {

        map.insert({ i, i + 10 });
        map2.insert({ i, i + 10 });
        aux.insert(aux.end(), i);

    }

    if (intercaladas == 0)
    {

        for (int i = 0; i < Iterations; ++i)
        {

            //std::cout << "Hilo 0 Insercion " << i << std::endl;

            buffer = aux.size();
            aux.insert(aux.end(), buffer);

            //insertas en el unordered_map

            startInsert = std::chrono::high_resolution_clock::now();
            map.insert({ buffer, buffer + 10 });
            endInsert = std::chrono::high_resolution_clock::now();

            timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - startInsert);
            timeTotalInsert += std::chrono::duration<double, std::milli>(timeBuffer).count();
            insertCount++;

            //insertas en el map

            startInsert = std::chrono::high_resolution_clock::now();
            map2.insert({ buffer, buffer + 10 });
            endInsert = std::chrono::high_resolution_clock::now();

            timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - startInsert);
            timeTotalInsert2 += std::chrono::duration<double, std::milli>(timeBuffer).count();
            insertCount2++;

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

            //eliminar en el unordered_map

            startDelete = std::chrono::high_resolution_clock::now();
            map.erase(buffer);
            endDelete = std::chrono::high_resolution_clock::now();

            timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - startDelete);
            timeTotalDelete += std::chrono::duration<double, std::milli>(timeBuffer).count();
            deleteCount++;

            //eliminar en el map

            startDelete = std::chrono::high_resolution_clock::now();
            map2.erase(buffer);
            endDelete = std::chrono::high_resolution_clock::now();

            timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - startDelete);
            timeTotalDelete2 += std::chrono::duration<double, std::milli>(timeBuffer).count();
            deleteCount2++;

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

            //modificar en el unordered_map

            startModify = std::chrono::high_resolution_clock::now();
            map[buffer] = buffer + 10;
            endModify = std::chrono::high_resolution_clock::now();

            timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endModify - startModify);
            timeTotalModify += std::chrono::duration<double, std::milli>(timeBuffer).count();
            modifyCount++;

            //modificar en el map

            startModify = std::chrono::high_resolution_clock::now();
            map2[buffer] = buffer + 10;
            endModify = std::chrono::high_resolution_clock::now();

            timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endModify - startModify);
            timeTotalModify2 += std::chrono::duration<double, std::milli>(timeBuffer).count();
            modifyCount2++;

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

                //insertas en el unordered_map

                startInsert = std::chrono::high_resolution_clock::now();
                map.insert({ buffer, buffer + 10 });
                endInsert = std::chrono::high_resolution_clock::now();

                timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - startInsert);
                timeTotalInsert += std::chrono::duration<double, std::milli>(timeBuffer).count();
                insertCount++;

                //insertas en el map

                startInsert = std::chrono::high_resolution_clock::now();
                map2.insert({ buffer, buffer + 10 });
                endInsert = std::chrono::high_resolution_clock::now();

                timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endInsert - startInsert);
                timeTotalInsert2 += std::chrono::duration<double, std::milli>(timeBuffer).count();
                insertCount2++;

            }

            if (option == 1 && !aux.empty()) //modify
            {

                buffer = (rand() % aux.size());
                bufferDel = buffer;
                buffer = aux[buffer];

                aux[bufferDel] = aux[aux.size() - 1];
                aux[aux.size() - 1] = buffer;

                aux.pop_back();

                //delete en el unordered_map

                startDelete = std::chrono::high_resolution_clock::now();
                map.erase(buffer);
                endDelete = std::chrono::high_resolution_clock::now();

                timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - startDelete);
                timeTotalDelete += std::chrono::duration<double, std::milli>(timeBuffer).count();
                deleteCount++;

                //delete en el map

                startDelete = std::chrono::high_resolution_clock::now();
                map2.erase(buffer);
                endDelete = std::chrono::high_resolution_clock::now();

                timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endDelete - startDelete);
                timeTotalDelete2 += std::chrono::duration<double, std::milli>(timeBuffer).count();
                deleteCount2++;

            }

            if (option == 2 && !aux.empty()) //delete
            {

                buffer = (rand() % aux.size());
                buffer = aux[buffer];

                //modify en el unordered_map

                startModify = std::chrono::high_resolution_clock::now();
                map[buffer] = buffer + 10;
                endModify = std::chrono::high_resolution_clock::now();

                timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endModify - startModify);
                timeTotalModify += std::chrono::duration<double, std::milli>(timeBuffer).count();
                modifyCount++;

                //modify en el map

                startModify = std::chrono::high_resolution_clock::now();
                map2[buffer] = buffer + 10;
                endModify = std::chrono::high_resolution_clock::now();

                timeBuffer = std::chrono::duration_cast<std::chrono::nanoseconds>(endModify - startModify);
                timeTotalModify2 += std::chrono::duration<double, std::milli>(timeBuffer).count();
                modifyCount2++;

            }

        }

    }

    promInserts = timeTotalInsert / insertCount;
    promModify = timeTotalModify / modifyCount;
    promDelete = timeTotalDelete / deleteCount;

    promInserts2 = timeTotalInsert2 / insertCount2;
    promModify2 = timeTotalModify2 / modifyCount2;
    promDelete2 = timeTotalDelete2 / deleteCount2;

    std::cout << "unordered_map Para N = " << N << " con i = " << Iterations << std::endl;
    std::cout << "El tiempo total de Inserts es de " << timeTotalInsert << " ms" << std::endl;
    std::cout << "El tiempo total de Modify es de " << timeTotalModify << " ms" << std::endl;
    std::cout << "El tiempo total de Delete es de " << timeTotalDelete << " ms" << std::endl;
    std::cout << "El tiempo total promedio de los Inserts es de " << promInserts << " ms" << std::endl;
    std::cout << "El tiempo total promedio de los Modify es de " << promModify << " ms" << std::endl;
    std::cout << "El tiempo total promedio de los Delete es de " << promDelete << " ms" << std::endl;

    std::cout << "map Para N = " << N << " con i = " << Iterations << std::endl;
    std::cout << "El tiempo total de Inserts es de " << timeTotalInsert2 << " ms" << std::endl;
    std::cout << "El tiempo total de Modify es de " << timeTotalModify2 << " ms" << std::endl;
    std::cout << "El tiempo total de Delete es de " << timeTotalDelete2 << " ms" << std::endl;
    std::cout << "El tiempo total promedio de los Inserts es de " << promInserts2 << " ms" << std::endl;
    std::cout << "El tiempo total promedio de los Modify es de " << promModify2 << " ms" << std::endl;
    std::cout << "El tiempo total promedio de los Delete es de " << promDelete2 << " ms" << std::endl << std::endl;


    //std::cout << "Hilo " << ThreadNumber << " Ejecucion Terminada"<< std::endl;

    map.clear();
    aux.clear();

}

int main(int argc, char* argv[]) {

    int f = 0, TotalIterations = 0, N = 0, TotalThreads = 0, intercalar = 0;
    std::vector< float > arr;


    N = 100;                  //N del algoritmo a ejecutar
    intercalar = 0;         //intercaladas, intercalar = 0 siginifica que seran secuenciales las iteraciones

    for (int i = 0; i < 6; i++)
    {

        ThreadTimers.push_back(arr);

    }

    std::srand(std::time(nullptr));

    foo(N, 100, 0, intercalar);
    foo(N, 1000, 1, intercalar);
    foo(N, 10000, 2, intercalar);
    foo(N, 100000, 3, intercalar);
    foo(N, 1000000, 4, intercalar);
    foo(N, 10000000, 5, intercalar);

    return 0;
}