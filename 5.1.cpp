#include <iostream>
#include <cstring>

struct User {
    int start;
    int end;

    bool operator<=(const User &r) const {
        if (r.end == end) {
            return (this->start <= r.start);
        } else {
            return (this->end <= r.end);
        }
    }
};

template<class T>
struct DefComp {
    bool operator()(const T &l, const T &r) {
        return l <= r;
    }
};

template<class T, class Comp=DefComp<T> >
void Merge(T *arr1, size_t len1, T *arr2, size_t len2, T *new_arr, Comp comp) {
    int i = 0, j = 0, k = 0;
    while (i < len1 && j < len2) {
        if (comp(arr1[i], arr2[j])) {
            new_arr[k] = arr1[i++];
        } else {
            new_arr[k] = arr2[j++];
        }
        k++;
    }
    if (i == len1)
        std::memcpy(&new_arr[k], &arr2[j], sizeof(T) * (len2 - j));
    else
        std::memcpy(&new_arr[k], &arr1[i], sizeof(T) * (len1 - i));
}

template<class T, class Comp=DefComp<T> >
void MergeSort(T *arr, size_t len, Comp comp = Comp()) {
    if (len <= 1)
        return;
    size_t len1 = len / 2;
    size_t len2 = len - len1;
    MergeSort(arr, len1);
    MergeSort(arr + len1, len2);
    T *new_arr = new T[len];
    Merge(arr, len1, arr + len1, len2, new_arr, comp);
    std::memcpy(arr, new_arr, (sizeof(T) * len));
    delete[] new_arr;
}

int main() {
    int n;
    std::cin >> n;
    User *users = new User[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> users[i].start >> users[i].end;
    }
    MergeSort(users, n);
    int count = 0;
    int t0 = -1, t1 = -1;
    for (size_t i = 0; i < n; ++i) {
        User buf = users[i];
        if (buf.start > t1) {
            t0 = buf.end - 1;
            t1 = buf.end;
            count += 2;
        } else if (buf.start == t1 || (buf.start > t0 && buf.end > t1)) {
            t0 = t1;
            t1 = buf.end;
            count++;
        } else if (buf.start > t0 && buf.start < t1) {
            t0 = buf.end;
            count++;
        }
    }
    std::cout << count;
    delete[] users;
    return 0;
}