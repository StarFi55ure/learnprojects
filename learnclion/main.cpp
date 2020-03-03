#include <iostream>

void TestFunc() {
    std::cout << "From inside func" << std::endl;

};
int main() {
    std::cout << "Hello, World!" << std::endl;

    class NewClass {
    public:
        int firstProp;
        int nextProp;

        NewClass(int firstProp) : firstProp(firstProp) {}
    };

    TestFunc();
    return 0;
}