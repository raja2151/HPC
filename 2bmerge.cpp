#include <iostream>
#include <omp.h>

void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Temporary arrays to hold the subarrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of left subarray
    j = 0; // Initial index of right subarray
    k = l; // Initial index of merged subarray
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

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free dynamically allocated memory
    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Recursively sort the two halves in parallel using OpenMP tasks
        #pragma omp parallel
        {
            #pragma omp single
            {
                #pragma omp task
                mergeSort(arr, l, m);

                #pragma omp task
                mergeSort(arr, m + 1, r);
            }
        }

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int main() {
    int n;

    // Get the number of elements from the user
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    // Dynamically allocate memory for the array based on user input
    int* arr = new int[n];

    // Get the array elements from the user
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    double start, stop;

    std::cout << "Given array is: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    // Start measuring time
    start = omp_get_wtime();

    // Call mergeSort in parallel using OpenMP
    mergeSort(arr, 0, n - 1);

    // Stop measuring time
    stop = omp_get_wtime();

    // Print the sorted array
    std::cout << "Sorted array is: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    // Print the time taken for sorting
    std::cout << "Time taken: " << stop - start << " seconds" << std::endl;

    // Free dynamically allocated memory
    delete[] arr;

    return 0;
}

