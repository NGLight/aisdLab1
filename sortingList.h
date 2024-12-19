#pragma once
#include <windows.h>

using namespace std;
#include <cmath>

void runSortingTest(ofstream &fout, int action);
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void quickSort(int arr[], int low, int high);
void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void timSort(int arr[], int n);
void heapify_2(int *arr, int n, int i);


//__________ СОРТИРОВКА ПУЗЫРЬКОВА __________//
void bubbleSort(int arr[], int n){

    //сортировка пузырьком
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

//__________ СОРТИРОВКА ВЫБОРОМ __________//
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

//__________ СОРТИРОВКА ВСТАВКАМИ __________//
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//__________ СОРТИРОВКА СЛИЯНИЕМ __________//
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


//__________ БЫСТРАЯ СЛИЯНИЕМ __________//

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}


//__________ СОРТИРОВКА ПИРАМИДАЛЬНАЯ __________//
// Основная функция пирамидальной сортировки
void heapSort(int arr[], int n) {
    // Построение кучи (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Извлечение элементов из кучи по одному
    for (int i=n-1; i>0; i--) {
        // Перемещаем текущий корень в конец
        swap(&arr[0], &arr[i]);
        // Вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}
// Функция для построения кучи
void heapify(int arr[], int n, int i) {
    int largest = i; // Инициализируем наибольший элемент как корень
    int l = 2*i + 1; // Левый потомок
    int r = 2*i + 2; // Правый потомок

    // Если левый потомок больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Если правый потомок больше корня
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если наибольший элемент не корень
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        // Рекурсивно строим поддерево
        heapify(arr, n, largest);
    }
}


//__________ ЕЩЕ РАЗОК ПИРАМЕДАЛЬНАЯ __________//
void heapSort_2(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_2(arr, n, i);

    for (int i=n-1; i>0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify_2(arr, i, 0);
    }
}
// Функция для построения кучи
void heapify_2(int *arr, int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}


//__________ TIMESORT __________//
const int MIN_MERGE = 32;

int min(int x, int y) {
    return (x < y) ? x : y;
}

int calcMinRun(int n) {
    int r = 0;
    while (n >= MIN_MERGE) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void timSort(int arr[], int n) {
    int minRun = calcMinRun(n);

    for (int i = 0; i < n; i += minRun)
        insertionSort(arr, i, min(i + minRun - 1, n - 1));

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = min(left + size - 1, n - 1);
            int right = min((left + 2 * size - 1), (n - 1));
            merge(arr, left, mid, right);
        }
    }
}

//__________ INTROSORT __________//
void quickSort(int arr[], int low, int high, int maxDepth) {
    while (low < high) {
        if (maxDepth == 0) {
            insertionSort(arr, low, high);
            return;
        }
        maxDepth--;

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1, maxDepth);
        low = pi + 1;
    }
}

void introSort(int arr[], int n) {
    int maxDepth = log2(n) * 2;
    quickSort(arr, 0, n - 1, maxDepth);
}
//__________ СОРТИРОВКА ШЕЛЛА __________//
void shellSort(int arr[], int n, int gap) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


