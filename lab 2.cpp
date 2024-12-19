/*
    заменить среднее на лучшее
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
//локальные бибилотеки
#include "sortingList.h"
#include "nglRandom.h"
#include "nglColors.h"
#include "nglService.h"
//количество проходов каждого теста
#define COUNT_PASS 10

using namespace std;

void runSortingTests();
double runSorting(int *arr, int typeSorting, int arraySize);
void createArray(int *arr, int count_elements, short typeArray);

enum type_array{RANDOM, SORTED, HALF_SORTED, REVERSED, COUNT_TYPE};
enum array_size{SIZE_01, SIZE_02, SIZE_03, SIZE_04, SIZE_05, SIZE_06, SIZE_07, COUNT_SIZE};
enum sorting_type{BUBBLE_SORT, SELECT_SORT, INSERT_SORT, MERGE_SORT, QUICK_SORT,
            HEAP_SORT, TIM_SORT, INTRO_SORT, SHELL_SORT_2, SHELL_SORT_4, SHELL_SORT_8, COUNT_SORTS};

int main(){
    showCursor(false);
    runSortingTests();
}

//____________________ ФУНКЦИИ ПО ТЕСТИРОВАНИЮ СОРТИРОВОК ____________________//
//общая функция по тестированию
void runSortingTests(){
    for (int typeSorting=3; typeSorting < COUNT_SORTS; typeSorting++){
        string nameSorting{};
        switch(typeSorting){
                case(BUBBLE_SORT): nameSorting = {"Bubble sorting"}; break;
                case(SELECT_SORT): nameSorting = {"Selection sorting"}; break;
                case(INSERT_SORT): nameSorting = {"Insertion sorting"}; break;
                case(MERGE_SORT): nameSorting = {"Merge sorting"}; break;
                case(QUICK_SORT): nameSorting = {"Quick sorting"};  break;
                case(HEAP_SORT): nameSorting = {"Heapsort"}; break;
                case(TIM_SORT): nameSorting = {"Timsorting"}; break;
                case(INTRO_SORT): nameSorting = {"Introsorting"}; break;
                case(SHELL_SORT_2): nameSorting = {"Shell sorting gap = n_2"}; break;
                case(SHELL_SORT_4): nameSorting = {"Shell sorting gap = n_4"}; break;
                case(SHELL_SORT_8): nameSorting = {"Shell sorting gap = n_8"}; break;
        }

        string fileName{};
        fileName = "_" + nameSorting + ".txt";
        ofstream fout(fileName);

        YL;
        cout << "__________________________________________________________" << endl;
        cout << nameSorting << endl;


        for (int typeArray=0; typeArray < COUNT_TYPE; typeArray++){
            string nameOfType{};
            switch(typeArray){
                case RANDOM: nameOfType = {"Random array type"}; break;
                case SORTED: nameOfType = {"Sorted array type"}; break;
                case HALF_SORTED: nameOfType = {"Half-sorted array type"}; break;
                case REVERSED: nameOfType = {"Reversed array type"}; break;
            }

            YL;
            cout << nameOfType << endl;
            fout << nameOfType << endl;

            for (int curSize=0; curSize < COUNT_SIZE; curSize++){
                int arraySize{};
                double middleTime{};
                switch(curSize){
                    case SIZE_01: arraySize = 2500; break;
                    case SIZE_02: arraySize = 5000; break;
                    case SIZE_03: arraySize = 10000; break;
                    case SIZE_04: arraySize = 50000; break;
                    case SIZE_05: arraySize = 100000; break;
                    case SIZE_06: arraySize = 150000; break;
                    case SIZE_07: arraySize = 250000; break;
                }

                int arr[arraySize];
                createArray(arr, arraySize, typeArray);


                for (int curPass=0; curPass < COUNT_PASS; curPass++){
                    cout << "Pass "<< curPass + 1<< "|" << COUNT_PASS << "\r";
                    middleTime += runSorting(arr, typeSorting, arraySize);
                }
                middleTime /= COUNT_PASS;


                RD;
                cout << "Size:" << arraySize << "\t";
                CN;
                if (middleTime > 1000)
                    cout << "middle time: " << fixed << middleTime/1000 << " sec" << endl;
                else
                    cout << "middle time: " << fixed << middleTime << " ms" << endl;
                fout << fixed << middleTime << endl;
            }
        }
        fout.close();
    }
}

double runSorting(int *arr, int typeSorting, int n){
    double timeSorting;
    clock_t t0{}, t1{};
    t0 = clock();
        switch(typeSorting){
        case(BUBBLE_SORT): bubbleSort(arr, n); break;
        case(SELECT_SORT): selectionSort(arr, n); break;
        case(INSERT_SORT): insertionSort(arr, n); break;
        case(MERGE_SORT): mergeSort(arr, 0, n-1); break;
        case(QUICK_SORT): quickSort(arr, 0, n-1); break;
        case(HEAP_SORT): heapSort(arr, n); break;
        case(TIM_SORT): timSort(arr, n); break;
        case(INTRO_SORT): introSort(arr, n); break;
        case(SHELL_SORT_2): shellSort(arr, n, n/2); break;
        case(SHELL_SORT_4): shellSort(arr, n, n/4); break;
        case(SHELL_SORT_8): shellSort(arr, n, n/8); break;
    }
    t1 = clock();
    timeSorting = double(t1 - t0) / CLOCKS_PER_SEC * 1000;
    return timeSorting;
}

//____________________ СОЗДАНИЕ ТЕСТОВЫХ МАССИВОВ ____________________//

void createArray(int *arr, int count_elements, short typeArray){
    int a = nglRandom(1000,500);
    for (int i=0; i < count_elements; arr[i++] = nglRandom(-a,a));
    switch(typeArray){
        case SORTED: heapSort_2(arr, count_elements); break;
        case HALF_SORTED: heapSort_2(arr, count_elements/2);break;
        case REVERSED: heapSort_2(arr, count_elements);
            //разворачиваем массив, наверное есть что-то шустрее, но у меня лапки
            for (int i = 0; i < count_elements / 2; i++){
                int temp = arr[i];
                arr[i] = arr[count_elements - i - 1];
                arr[count_elements - i - 1] = temp;
                }
            break;
    }
}



