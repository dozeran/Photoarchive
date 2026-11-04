#include <iostream>
#include <memory>
#include <vector>

// Тип із noexcept-конструктором переміщення
struct WithNoexceptMove {
    std::unique_ptr<int> value;

    static int copies;
    static int moves;

    WithNoexceptMove()
        : value(std::make_unique<int>(42)) {}

    WithNoexceptMove(const WithNoexceptMove& other)
        : value(other.value
                    ? std::make_unique<int>(*other.value)
                    : nullptr) {
        ++copies;
    }

    WithNoexceptMove(WithNoexceptMove&& other) noexcept
        : value(std::move(other.value)) {
        ++moves;
    }
};

int WithNoexceptMove::copies = 0;
int WithNoexceptMove::moves = 0;


// Тип без noexcept-конструктора переміщення
struct WithoutNoexceptMove {
    std::unique_ptr<int> value;

    static int copies;
    static int moves;

    WithoutNoexceptMove()
        : value(std::make_unique<int>(42)) {}

    WithoutNoexceptMove(const WithoutNoexceptMove& other)
        : value(other.value
                    ? std::make_unique<int>(*other.value)
                    : nullptr) {
        ++copies;
    }

    WithoutNoexceptMove(WithoutNoexceptMove&& other)
        : value(std::move(other.value)) {
        ++moves;
    }
};

int WithoutNoexceptMove::copies = 0;
int WithoutNoexceptMove::moves = 0;


int main() {
    std::vector<WithNoexceptMove> safeVector;

    for (int i = 0; i < 10; ++i) {
        safeVector.emplace_back();
    }

    std::cout << "With noexcept:\n";
    std::cout << "Copies: " << WithNoexceptMove::copies << '\n';
    std::cout << "Moves: " << WithNoexceptMove::moves << "\n\n";


    std::vector<WithoutNoexceptMove> regularVector;

    for (int i = 0; i < 10; ++i) {
        regularVector.emplace_back();
    }

    std::cout << "Without noexcept:\n";
    std::cout << "Copies: " << WithoutNoexceptMove::copies << '\n';
    std::cout << "Moves: " << WithoutNoexceptMove::moves << '\n';

    return 0;
}