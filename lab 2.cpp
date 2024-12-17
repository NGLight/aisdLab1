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

void createArray(int *arr, int count_elements, short type_array);
void reverseArray(int *arr, int n);
void runSortingTest(ofstream &fout, int arraySize, int type_array);
void runTestOnArraySize();
void runTestOnArrayType();

enum type_array{RANDOM, SORTED, HALF_SORTED, REVERSED, COUNT_TYPE};
enum arraySize{SIZE_01, SIZE_02, SIZE_03, SIZE_04, SIZE_05, SIZE_06, SIZE_07, COUNT_SIZE};
enum sorting{BUBBLE_SORT, SELECT_SORT, INSERT_SORT, MERGE_SORT, QUICK_SORT,
            HEAP_SORT, TIM_SORT, INTRO_SORT, SHELL_SORT_2, SHELL_SORT_4, SHELL_SORT_8, COUNT_SORTS};


int main(){
    showCursor(false);
    runTestOnArraySize();
    runTestOnArrayType();
}

//____________________ ФУНКЦИИ ПО ТЕСТИРОВАНИЮ СОРТИРОВОК ____________________//
//Тест первый, зависимость времени от количества элементов
void runTestOnArraySize(){
    int arraySize{};
    ofstream fout("output_aray_size.txt");
    cout << "This is a test of the dependence of time on the size of the array" << endl;
    fout << "This is a test of the dependence of time on the size of the array" << endl;
    for (int curSize=0; curSize < COUNT_SIZE; curSize++){
        switch(curSize){
            case SIZE_01: arraySize = 100; break;
            case SIZE_02: arraySize = 5000; break;
            case SIZE_03: arraySize = 10000; break;
            case SIZE_04: arraySize = 50000; break;
            case SIZE_05: arraySize = 100000; break;
            case SIZE_06: arraySize = 250000; break;
            case SIZE_07: arraySize = 500000; break;
        };
        YL;
        cout << "__________________________________________________________" << endl;
        fout << "__________________________________________________________ " << endl;

        cout << "Count array elements: " << arraySize << endl;
        fout << "Count array elements: " << arraySize << endl;

        runSortingTest(fout, arraySize, RANDOM);
    }
    fout.close();
}

//Тест второй, зависимость времени от типа массива (случайный, наполовину сортированный, развернутый)
void runTestOnArrayType(){
    int arraySize = 250000;
    string nameOfType{};
    ofstream fout("output_aray_type.txt");
    cout << "This is a check of the dependence of time on the type of array" << endl;
    fout << "This is a check of the dependence of time on the type of array" << endl;

    for (int curType=0; curType < COUNT_TYPE; curType++){
        switch(curType){
            case RANDOM: nameOfType = {"Random array type"}; break;
            case SORTED: nameOfType = {"Sorted array type"}; break;
            case HALF_SORTED: nameOfType = {"Half-sorted array type"}; break;
            case REVERSED: nameOfType = {"Reversed array type"}; break;
        };
        YL;
        cout << nameOfType << endl;
        fout << nameOfType << endl;

        runSortingTest(fout, arraySize, curType);

        cout << "__________________________________________________________" << endl;
        fout << "__________________________________________________________ " << endl;
    }
    fout.close();
}

//общая функция по тестированию всех типов массивов
void runSortingTest(ofstream &fout, int arraySize, int type_array){

    for (int curSorting=0; curSorting < COUNT_SORTS; curSorting++){
        string nameSorting{};
        double middleTime{};

        int n = arraySize;
        int arr[arraySize];
        createArray(arr, n, type_array);

        for (int curPass=0; curPass < COUNT_PASS; curPass++){
            clock_t t0{}, t1{};
            double timeSorting{};
            t0 = clock();
            switch(curSorting){
                case(BUBBLE_SORT): nameSorting = {"Bubble sorting"}; bubbleSort(arr, n); t1 = clock(); break;
                case(SELECT_SORT): nameSorting = {"Selection sorting"}; selectionSort(arr, n); t1 = clock(); break;
                case(INSERT_SORT): nameSorting = {"Insertion sorting"}; insertionSort(arr, n); t1 = clock(); break;
                case(MERGE_SORT): nameSorting = {"Merge sorting"}; mergeSort(arr, 0, n-1); t1 = clock(); break;
                case(QUICK_SORT): nameSorting = {"Quick sorting"}; quickSort(arr, 0, n-1); t1 = clock(); break;
                case(HEAP_SORT): nameSorting = {"Heapsort"}; heapSort(arr, n); t1 = clock(); break;
                case(TIM_SORT): nameSorting = {"Timsorting"}; timSort(arr, n); t1 = clock(); break;
                case(INTRO_SORT): nameSorting = {"Introsorting"}; introSort(arr, n); t1 = clock(); break;
                case(SHELL_SORT_2): nameSorting = {"Shell sorting gap = n/2"}; shellSort(arr, n, n/2); t1 = clock(); break;
                case(SHELL_SORT_4): nameSorting = {"Shell sorting gap = n/4"}; shellSort(arr, n, n/4); t1 = clock(); break;
                case(SHELL_SORT_8): nameSorting = {"Shell sorting gap = n/8"}; shellSort(arr, n, n/8); t1 = clock(); break;
            }
            //timeSorting = double(t1 - t0) / CLOCKS_PER_SEC;
            timeSorting = double(t1 - t0) / CLOCKS_PER_SEC * 1000;

            middleTime += timeSorting;
            RD;
            if (curPass == 0){cout << nameSorting << endl; fout << nameSorting << endl;}
            CN;
            if (COUNT_PASS > 1) cout << "Pass "<< curPass + 1<< "|" << COUNT_PASS << "\r";
            /*
            if (COUNT_PASS > 1){
            cout << "Pass "<< curPass + 1<< "|" << COUNT_PASS
                 << "\t\t" << "Time of sorting: " << timeSorting << " sec" << endl;
            fout << "Pass "<< curPass + 1 << "|" << COUNT_PASS
                 << "\t\t" << "Time of sorting: " << timeSorting << " sec" << endl;
            */
            }
            CN;

            middleTime /= COUNT_PASS;
            if (middleTime > 1000) {
                cout << "Middle time: " << middleTime/1000 << " sec" << '\n' <<endl;
                fout << "Middle time: " << middleTime/1000 << " sec" << '\n' << endl;
            }
            else {
                cout << "Middle time: " << middleTime << " ms" << '\n' <<endl;
                fout << "Middle time: " << middleTime << " ms" << '\n' << endl;
            }
        }
}

//____________________ СОЗДАНИЕ ТЕСТОВЫХ МАССИВОВ ____________________//

void createArray(int *arr, int count_elements, short type_array){
    for (int i=0; i < count_elements; arr[i++] = nglRandom(-1000,1000));
    switch(type_array){
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



