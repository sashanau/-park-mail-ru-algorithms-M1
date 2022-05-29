#include <iostream>

class Deque{
public:
    Deque(int SIZE){
        CURRENT_SIZE = SIZE;
        arr = new int[CURRENT_SIZE];
        std::fill(arr, arr + CURRENT_SIZE, 0);
        head = 1;
        tail = 0;
    }
    ~Deque(){
        delete[] arr;
    }

    void push_front(int temp);
    void push_back(int temp);
    int pop_front(int temp);
    int pop_back(int temp);

private:
    void resize();
    int *arr;
    int CURRENT_SIZE;
    int head;
    int tail;
};

void Deque::push_front(int temp) {
    arr[tail] = temp;
    tail--;
    if (tail == -1)
        tail = CURRENT_SIZE - 1;
    if (head == tail)
        resize();
}

void Deque::push_back(int temp) {
    arr[head] = temp;
    head++;
    if (head == CURRENT_SIZE)
        head = 0;
    if (head == tail)
        resize();
}

int Deque::pop_front(int temp) {
    tail++;
    if (tail == CURRENT_SIZE)
        tail = 0;
    if (tail == head) {
        tail--;
        return -1;
    }
    if (arr[tail] == temp)
        return temp;
    else
        return 0;
}

int Deque::pop_back(int temp) {
    head--;
    if (head == -1)
        head = CURRENT_SIZE - 1;
    if (tail == head) {
        head++;
        return -1;
    }
    if (arr[head] == temp)
        return temp;
    else
        return 0;
}

void Deque::resize(){
    CURRENT_SIZE *= 2;
    int tail_new = 0, head_new = 1;
    int *arr_temp;
    int j = 1;
    arr_temp = new int[CURRENT_SIZE];
    std::fill(arr_temp, arr_temp + CURRENT_SIZE, 0);
    tail++;
    if (tail == CURRENT_SIZE)
        tail = 0;
    for(int i = tail; i != head; i++){
        if (i == CURRENT_SIZE / 2)
            i = -1;
        else {
            arr_temp[j] = arr[i];
            j++;
            head_new = j;
        }
    }
    delete[] arr;
    tail = tail_new;
    head = head_new;
    arr = arr_temp;
}

int main() {
    Deque A(5);
    int n, command, val;
    std::cin >> n;
    for (int i = 0; i < n; i++){
        std::cin >> command;
        if (command == 1){
            std::cin >> val;
            A.push_front(val);
        } else if (command == 2){
            std::cin >> val;
            if (A.pop_front(val) != val) {
                std::cout << "NO";
                return 0;
            }
        } else if (command == 3){
            std::cin >> val;
            A.push_back(val);
        } else if (command == 4){
            std::cin >> val;
            if (A.pop_back(val) != val) {
                std::cout << "NO";
                return 0;
            }
        } else{
            std::cout << "NO";
            return 0;
        }
    }
    std::cout << "YES";
    return 0;
}
