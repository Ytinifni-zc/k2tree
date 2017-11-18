//
// Created by inFinity on 2017/11/15.
//

#ifndef K2TREE_SORT_H
#define K2TREE_SORT_H

#endif //K2TREE_SORT_H

#include <algorithm>

using std::min;

namespace libk2tree {
    namespace sort {
        template<typename T> //整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
        void merge_sort(T arr[], int len) {
            T* a = arr;
            T* b = new T[len];
            for (int seg = 1; seg < len; seg += seg) {
                for (int start = 0; start < len; start += seg + seg) {
                    int low = start, mid = min(start + seg, len), high = min(start + seg + seg, len);
                    int k = low;
                    int start1 = low, end1 = mid;
                    int start2 = mid, end2 = high;
                    while (start1 < end1 && start2 < end2)
                        b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
                    while (start1 < end1)
                        b[k++] = a[start1++];
                    while (start2 < end2)
                        b[k++] = a[start2++];
                }
                T* temp = a;
                a = b;
                b = temp;
            }
            if (a != arr) {
                for (int i = 0; i < len; i++)
                    b[i] = a[i];
                b = a;
            }
            delete[] b;
        }

        template<typename T>
        void merge_sort_recursive(T arr[], T reg[], int start, int end) {
            if (start >= end)
                return;
            int len = end - start, mid = (len >> 1) + start;
            int start1 = start, end1 = mid;
            int start2 = mid + 1, end2 = end;
            merge_sort_recursive(arr, reg, start1, end1);
            merge_sort_recursive(arr, reg, start2, end2);
            int k = start;
            while (start1 <= end1 && start2 <= end2)
                reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
            while (start1 <= end1)
                reg[k++] = arr[start1++];
            while (start2 <= end2)
                reg[k++] = arr[start2++];
            for (k = start; k <= end; k++)
                arr[k] = reg[k];
        }

        template<typename T> //整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
        void merge_sort_r(T arr[], const int len) {
            T reg[len];
            merge_sort_recursive(arr, reg, 0, len - 1);
        }
    }
}