#include <iostream>

struct User{
    int id;
    int count;
    bool operator< (const User& r) const{
        return (this->count < r.count);
    }
    bool operator> (const User& r) const{
        return (this->count > r.count);
    }
};


template <class T>
struct DefComp{
    bool operator() (const T& l, const T& r){
        return l > r;
    }
};

template <class T, class Comp=DefComp<T> >
class Heap{
public:
    Heap(Comp comp=Comp()){
        buffer = new T[3];
        size_heap = 0;
        capacity = 3;
        this->comp = comp;
    }
    Heap(T* arr, size_t size, Comp comp=Comp()){
        this->comp = comp;
        buffer = new T[size];
        for (int i = 0; i < size; i++){
            buffer[i] = arr[i];
        }
        size_heap = size;
        capacity = size;
        heapify();
    }
    ~Heap(){
        delete[] buffer;
    }

    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;
    Heap& operator= (const Heap&) = delete;
    Heap& operator= (Heap&&) = delete;

    const T& top() const;
    void pop();
    void push(const T& value);

    size_t size() const;
    bool empty() const;

private:
    void sift_up(size_t idx);
    void sift_down(int idx);

    void heapify();

    void grow();

    T* buffer;
    size_t size_heap;
    size_t capacity;

    Comp comp;
};

template<class T, class Comp>
const T& Heap<T, Comp>::top() const {
    return buffer[0];
}

template<class T, class Comp>
void Heap<T, Comp>::pop() {
    if (size_heap <= 0)
        return;
    size_heap--;
    buffer[0] = buffer[size_heap];
    heapify();
}

template<class T, class Comp>
void Heap<T, Comp>::push(const T &value) {
    size_heap++;
    if (size_heap >= capacity)
        grow();
    buffer[size_heap - 1] = value;
    sift_up(size_heap - 1);
}

template<class T, class Comp>
size_t Heap<T, Comp>::size() const {
    return size_heap;
}

template<class T, class Comp>
bool Heap<T, Comp>::empty() const {
    return size_heap == 0;
}

template<class T, class Comp>
void Heap<T, Comp>::sift_up(size_t idx) {
    while(idx > 0) {
        size_t parent = (idx - 1) / 2;
        if( comp(buffer[idx], buffer[parent]) )
            return;
        std::swap( buffer[idx], buffer[parent] );
        idx = parent;
    }
}

template<class T, class Comp>
void Heap<T, Comp>::sift_down(int idx) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int largest = idx;
    if (left < (int)size() && comp(buffer[largest], buffer[left]))
        largest = left;
    if (right < (int)size() && comp(buffer[largest], buffer[right]))
        largest = right;
    if (largest != idx) {
        std::swap(buffer[idx], buffer[largest]);
        sift_down(largest);
    }
}

template<class T, class Comp>
void Heap<T, Comp>::heapify() {
    if (size_heap == 0 || size_heap == 1) {
        return;
    }
    for(int i = (size_heap / 2) - 1; i >= 0; i--)
        sift_down(i);
}

template<class T, class Comp>
void Heap<T, Comp>::grow() {
    capacity *= 2;
    T* new_buffer = new T[capacity];
    for (int i = 0; i < (int)size_heap; i++){
        new_buffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = new_buffer;
}


int main() {
    int n, k;
    std::cin >> n >> k;
    if (n == 0 || k == 0)
        return 0;
    User *a = new User[n];
    for (int i = 0; i < n; i++){
        std::cin >> a[i].id >> a[i].count;
    }
    Heap<User> *heap = new Heap<User>();
    for(int i = 0; i < n; i++){
        if (i >= k){
            heap->push(a[i]);
            heap->pop();
        } else
            heap->push(a[i]);
    }
    int temp;
    if (k < n)
        temp = k;
    else
        temp= n;
    for (int i = 0; i < temp; i++){
        std::cout << heap->top().id << " ";
        heap->pop();
    }
    return 0;
}