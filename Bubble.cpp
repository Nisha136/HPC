#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP (Odd-Even)
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to print the array
void printArray(const vector<int>& arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> original(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> original[i];

    vector<int> seqArr = original;
    vector<int> parArr = original;

    double startSeq = omp_get_wtime();
    sequentialBubbleSort(seqArr);
    double endSeq = omp_get_wtime();

    double startPar = omp_get_wtime();
    parallelBubbleSort(parArr);
    double endPar = omp_get_wtime();

    cout << "\nSorted array (Sequential): ";
    printArray(seqArr);

    cout << "Sorted array (Parallel)  : ";
    printArray(parArr);

    cout << "\nTime taken by Sequential Bubble Sort: " << (endSeq - startSeq) << " seconds\n";
    cout << "Time taken by Parallel Bubble Sort  : " << (endPar - startPar) << " seconds\n";

    return 0;
}
