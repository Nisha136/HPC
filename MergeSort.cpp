#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge two halves
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid+1;

    while (i <= mid && j <= right) {
        if (arr[i] < arr[j])
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); ++k)
        arr[left + k] = temp[k];
}

// Sequential Merge Sort
void sequentialMergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;

    sequentialMergeSort(arr, left, mid);
    sequentialMergeSort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;
    int mid = (left + right) / 2;

    if (depth < 4) {
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid, depth + 1);

            #pragma omp section
            parallelMergeSort(arr, mid+1, right, depth + 1);
        }
    } else {
        sequentialMergeSort(arr, left, mid);
        sequentialMergeSort(arr, mid+1, right);
    }

    merge(arr, left, mid, right);
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
    sequentialMergeSort(seqArr, 0, n-1);
    double endSeq = omp_get_wtime();

    double startPar = omp_get_wtime();
    parallelMergeSort(parArr, 0, n-1);
    double endPar = omp_get_wtime();

    cout << "\nTime taken by Sequential Merge Sort: " << (endSeq - startSeq) << " seconds\n";
    cout << "Time taken by Parallel Merge Sort  : " << (endPar - startPar) << " seconds\n";

    return 0;
}
