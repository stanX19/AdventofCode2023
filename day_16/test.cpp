#include <bits/stdc++.h>

// Define function prototypes
void function1(int i);
void function2(int i);
void function3(int i);

int main() {
    // Create a map with string keys and function pointer values
    std::unordered_map<std::string, void (*)(int)> functionMap = {
        {"func1", &function1},
        {"func2", &function2},
        {"func3", &function3}
        // Add more entries as needed
    };

    // Call functions using the map
    functionMap["func1"](1);  // Calls function1
    functionMap["func2"](2);  // Calls function2
    functionMap["func3"](3);  // Calls function3

    return 0;
}

// Define the functions
void function1(int i) {
    std::cout << "Function 1 called" << i << std::endl;
}

void function2(int i) {
    std::cout << "Function 2 called" << i << std::endl;
}

void function3(int i) {
    std::cout << "Function 3 called" << i << std::endl;
}
