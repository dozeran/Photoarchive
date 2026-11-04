
#include <iostream>

class BrokenList {
public:
    explicit BrokenList(int size)
        : items_(new int[size]) {
        std::cout << "Memory allocated\n";
    }

    ~BrokenList() {
        delete[] items_;
        std::cout << "Memory released\n";
    }

private:
    int* items_;
};

void printList(BrokenList copy) {
    (void)copy;
    std::cout << "Copy received\n";
}

int main() {
    BrokenList original(5);

    printList(original);

    return 0;
}
