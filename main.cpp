#include "Types.cpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    TuringType abc{8}; //  8-bit type so supports 2^8 different values
    abc.setName("hey");

    int x = 0b0001 + 1;


    std::cout << abc.name;

    return 0;
}
