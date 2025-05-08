#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    int minVal = arr[0];
    int maxVal = arr[0];
    int sum = 0;

    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n; ++i) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }

    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n; ++i) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }

    double average = static_cast<double>(sum) / n;

    cout << "\nMinimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum    : " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
