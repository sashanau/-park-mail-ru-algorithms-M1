#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

template <class T>
struct DefComp{
    bool operator() (const T& l, const T& r){
        return l < r;
    }
};

int take_rand(int l, int r){
    int diop = r - l;
    return (l + ((int)rand() % (diop + 1)));
}

template <class T, class Comp=DefComp<T>>
int partition(T *arr, int l, int r, Comp comp=Comp()){
    if (r - l < 1)
        return 0;
    int pivot_idx = take_rand(l, r - 1);
    T pivot = arr[pivot_idx];
    int i = l;
    int j = l;

    std::swap(arr[pivot_idx], arr[r - 1]);
    while (j != r - 1){
        if (comp(pivot, arr[j])){
            j++;
        } else{
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    std::swap(arr[r - 1], arr[i]);
    return i;
}

template <class T, class Comp=DefComp<T>>
int kStat(T *arr, size_t size, int k, Comp comp=Comp()){
    int l = 0;
    int r = (int)size;

    while (true){
        int m = partition(arr, l, r, comp);
        if (m == k)
            return arr[k];
        else if(m < k){
            l = m + 1;
        } else{
            r = m;
        }
    }
}

int main(){
    int n;
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++){
        std::cin >> a[i];
    }
    int p_10 = n / 10;
    int mid = n / 2;
    int p_90 = n * 9 / 10;
    std::cout << kStat(a, n, p_10) << std::endl << kStat(a, n, mid) << std::endl << kStat(a, n, p_90);
    delete[] a;
    return 0;
}