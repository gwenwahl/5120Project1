

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <math.h>
#include <string.h>

using namespace std;

//GLOBALS
//For tracking compare
long long comparisons = 0;

//FUNCTION DEFINITIONS
int partitionFirst(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = high;
    int tmp;
    for (int j = high; j > low; --j) {
        ++comparisons;
        if (arr[j] >= pivot) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i--;
        }
    }
    tmp = arr[i];
    arr[i] = arr[low];
    arr[low] = tmp;
    return i;
}

int partitionLast(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    int tmp;
    for (int j = low; j <= high - 1; ++j) {
        ++comparisons;
        if (arr[j] <= pivot) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++i;
        }
    }
    tmp = arr[i];
    arr[i] = arr[high];
    arr[high] = tmp;
    return i;
}

int partitionMiddle(int arr[], int low, int high) {
    int pivot_i = (low + high) / 2;
    int pivot = arr[pivot_i];
    int i = low;
    int tmp;

    //Move pivot to end
    tmp = arr[high];
    arr[high] = pivot;
    arr[pivot_i] = tmp;

    for (int j = low; j <= high - 1; ++j) {
        ++comparisons;
        if (arr[j] <= pivot) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++i;
        }
    }
    tmp = arr[i];
    arr[i] = arr[high];
    arr[high] = tmp;
    return i;
}

int partitionRandom(int arr[], int low, int high) {
    int pivot_i = rand()%(high - low + 1) + low;
    int pivot = arr[pivot_i];
    int i = low;
    int tmp;

    //Move pivot to end
    tmp = arr[high];
    arr[high] = pivot;
    arr[pivot_i] = tmp;

    for (int j = low; j <= high - 1; ++j) {
        ++comparisons;
        if (arr[j] <= pivot) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            ++i;
        }
    }
    tmp = arr[i];
    arr[i] = arr[high];
    arr[high] = tmp;
    return i;
}

//These will be using tail recursion to avoid stack overflow
void quickSortLast(int arr[], int low, int high) {
    while (low < high) {
        int pivot = partitionLast(arr, low, high);
        quickSortLast(arr, low, pivot - 1);
        low = pivot + 1;
    }
}

void quickSortFirst(int arr[], int low, int high) {
    while (low < high) {
        int pivot = partitionFirst(arr, low, high);
        quickSortFirst(arr, low, pivot - 1);
        low = pivot + 1;
    }
}

void quickSortMiddle(int arr[], int low, int high) {
    while (low < high) {
        int pivot = partitionMiddle(arr, low, high);
        quickSortMiddle(arr, low, pivot - 1);
        low = pivot + 1;
    }
}

void quickSortRandom(int arr[], int low, int high) {
    while (low < high) {
        int pivot = partitionRandom(arr, low, high);
        quickSortRandom(arr, low, pivot - 1);
        low = pivot + 1;
    }
}
void siftDown(int arr[], int start, int end) {
    int root = start;

    while ((root * 2) + 1 <= end) {
        int child = (root * 2) + 1;
        int swap  = root;

        ++comparisons;
        if (arr[swap] < arr[child]) {
            swap = child;
        }
        ++comparisons;
        if (child + 1 <= end && arr[swap] < arr[child+1]) {
            swap = child + 1;
        }
        ++comparisons;
        if (swap == root) {
            return;
        } else {
            int tmp = arr[root];
            arr[root] = arr[swap];
            arr[swap] = tmp;
            root = swap;
        }
    }
}

void heapify(int arr[], int count) {
    int start = (count - 2) / 2;
    while (start >= 0) {
        siftDown(arr, start, count - 1);
        start--;
    }
}

void heapSort(int arr[], int count) {
    heapify(arr, count);
    int end = count - 1;
    while (end > 0) {
        int tmp = arr[end];
        arr[end] = arr[0];
        arr[0]   = tmp;
        end--;
        siftDown(arr, 0, end);
    }
}

vector<int> loadData(string filename) {
    ifstream dataFile(filename);
    string line;
    vector<int> dataArr;
    if (dataFile.is_open()) {
        while (getline(dataFile, line)) {
            dataArr.push_back(stoi(line));
        }
    } else {
        std::cout << "Unable to open file" << endl;
    }
    return dataArr;
}

//MAIN FUNCTION
int main(int argc, char* argv[]) {
    srand (time(NULL));
    if (argc < 3) {
        cout << "Invalid number of argument variables. Please enter the filename and desired sort method" << endl;
        return 1;
    }
    //Load into a vector as the line count is not specified
    vector<int> tempArr = loadData(argv[1]);
    if (tempArr.size() < 1) {
        cout << "Invalid data input. Either the file did not load, or there is no data present" << endl;
        return 1;
    }

    //Convert to C style arr for easier manipulation
    int data[tempArr.size()];
    for (int i = 0; i < tempArr.size(); ++i) {
        data[i] = tempArr[i];
    }
    auto start = chrono::high_resolution_clock::now();
    if (strcmp(argv[2], "quickSortLast") == 0) {
        quickSortLast(data, 0, tempArr.size() - 1);
        auto finish = chrono::high_resolution_clock::now();
        cout << tempArr.size() << ", " << comparisons << ", " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << endl;
    } else if (strcmp(argv[2], "quickSortFirst") == 0) {
        quickSortFirst(data, 0, tempArr.size() - 1);
        auto finish = chrono::high_resolution_clock::now();
        cout << tempArr.size() << ", " << comparisons << ", " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << endl;
    } else if (strcmp(argv[2], "quickSortMiddle") == 0) {
        quickSortMiddle(data, 0, tempArr.size() - 1);
        auto finish = chrono::high_resolution_clock::now();
        cout << tempArr.size() << ", " << comparisons << ", " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << endl;
    } else if (strcmp(argv[2], "quickSortRandom") == 0) {
        quickSortRandom(data, 0, tempArr.size() - 1);
        auto finish = chrono::high_resolution_clock::now();
        cout << tempArr.size() << ", " << comparisons << ", " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << endl;
    } else if (strcmp(argv[2], "heapSort") == 0) {
        heapSort(data, tempArr.size());
        auto finish = chrono::high_resolution_clock::now();
        cout << tempArr.size() << ", " << comparisons << ", " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << endl;
    } else {
        cout << "Invalid selection. Please use one of the valid arguments." << endl;
        cout << "quickSortLast"   << endl << "quickSortFirst"  << endl;
        cout << "quickSortRandom" << endl << "quickSortMiddle" << endl << "heapSort" << endl;
        return 1;
    }
    /*for (int i = 0; i < tempArr.size(); ++i) {
        //cout << data[i] << endl;
    }*/


    return 0;
}

