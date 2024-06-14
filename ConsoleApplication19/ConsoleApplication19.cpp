#include <iostream>
#include <vector>
#include <thread>
using namespace std;

// сортировка массива методом сортировки слиянием
class MergeSort {
public:
    void Sort(vector<int>& array) {
        if (array.size() <= 1) {
            return;
        }
        vector<int> left(array.begin(), array.begin() + array.size() / 2);
        vector<int> right(array.begin() + array.size() / 2, array.end());

        // cортируем левую и правую части массива параллельно
        thread leftThread(&MergeSort::Sort, this, ref(left));
        thread rightThread(&MergeSort::Sort, this, ref(right));

        leftThread.join();
        rightThread.join();

        Merge(array, left, right);
    }

private:
    // объединение двух отсортированных частей массива
    void Merge(vector<int>& array, const vector<int>& left, const vector<int>& right) {
        size_t i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            }
            else {
                array[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            array[k++] = left[i++];
        }

        while (j < right.size()) {
            array[k++] = right[j++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> array(10);
    cout << "введи 10 чисел:" << endl;

    for (int& num : array) {
        cin >> num;
    }

    MergeSort sorter;

    // анонимная функция для вызова метода Sort
    auto sortFunction = [&sorter](vector<int>& arr) {
        sorter.Sort(arr);
        };

    // создание и запуск потока для сортировки
    thread mergeSortThread(sortFunction, ref(array));
    mergeSortThread.join();

    cout << "по возрастанию:" << endl;
    for (const int& num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
