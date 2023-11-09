#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

struct File {
    int ID;
};

// Merge Sort
void merge(std::vector<File>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<File> left_half(n1);
    std::vector<File> right_half(n2);

    for (int i = 0; i < n1; i++)
        left_half[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_half[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (left_half[i].ID <= right_half[j].ID) {
            arr[k] = left_half[i];
            i++;
        } else {
            arr[k] = right_half[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left_half[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right_half[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<File>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort
int partition(std::vector<File>& arr, int low, int high) {
    int pivot = arr[high].ID;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].ID <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<File>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;
    std::cout << "Enter the number of files: ";
    std::cin >> n;

    std::vector<File> files(n);

    int minID, maxID;
    std::cout << "Enter the range for random IDs (min max): ";
    std::cin >> minID >> maxID;

    // Generate a list of files with random IDs in the specified range
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < n; i++) {
        files[i].ID = minID + std::rand() % (maxID - minID + 1);
    }

    int choice;
    std::cout << "Choose a sorting algorithm (1 for Merge Sort, 2 for Quick Sort): ";
    std::cin >> choice;

    if (choice == 1) {
        // Measure time and space complexity for Merge Sort
        clock_t mergeSortStartTime = clock();
        mergeSort(files, 0, n - 1);
        clock_t mergeSortEndTime = clock();
        double mergeSortTime = static_cast<double>(mergeSortEndTime - mergeSortStartTime) / CLOCKS_PER_SEC;
        size_t mergeSortSpace = sizeof(files[0]) * n;

        std::cout << "Merge Sort:\n";
        std::cout << "Time Complexity: O(n log n) - (" << mergeSortTime << " seconds)\n";
        std::cout << "Space Complexity: O(n) - (" << mergeSortSpace << " bytes)\n";
    } else if (choice == 2) {
        // Measure time and space complexity for Quick Sort
        clock_t quickSortStartTime = clock();
        quickSort(files, 0, n - 1);
        clock_t quickSortEndTime = clock();
        double quickSortTime = static_cast<double>(quickSortEndTime - quickSortStartTime) / CLOCKS_PER_SEC;
        size_t quickSortSpace = sizeof(files[0]) * n;

        std::cout << "Quick Sort:\n";
        std::cout << "Time Complexity: O(n log n) - (" << quickSortTime << " seconds)\n";
        std::cout << "Space Complexity: O(log n) - (" << quickSortSpace << " bytes)\n";
    } else {
        std::cout << "Invalid choice.\n";
    }

    // Display the sorted list
    std::cout << "Sorted Files:\n";
    for (const File& file : files) {
        std::cout << file.ID << " ";
    }
    std::cout << "\n";

    return 0;
}