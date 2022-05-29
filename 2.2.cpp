#include <iostream>

int binarySearch(const int *arr, int left, int right){
    if (right + 1 == 2) {
        if (arr[0] < arr[1])
            return 1;
        else
            return 0;
    }
    if (arr[0] > arr[1])
        return 0;
    if (arr[right - 1] < arr[right])
        return right;
    int mid = 0;
    while (left != right){
        mid = (left + right) / 2;
        if (arr[mid] > arr[left])
            left = mid;
        else
            right = mid;
    }
    return mid;
}

int preparation_to_binarySearch(const int *arr, int len){
    int left = 0, right = 0;
    for (int i = 1; i < len; i = i * 2)
    {
        left = i / 2;
        if (arr[i] < arr[i / 2])
        {
            right = i;
            break;
        } else
            right = len - 1;
    }
    return binarySearch(arr, left, right);
}

int main() {
    int len, temp;
    std::cin >> len;
    int *a = new int[len];
    for(int i = 0; i < len; i++) {
        std::cin >> temp;
        a[i] = temp;
    }
    std::cout << preparation_to_binarySearch(a, len) << std::endl;
    delete[] a;
    return 0;
}
