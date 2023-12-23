#include <iostream>
#include <ctgmath>


enum class Operations {
    Add = '+',
    Subtract = '-',
    Multiply = '*',
    Device = '/',
    MODULO = '%',
    POWER = '^'
};

bool isSupportedOperation(char c) {
    return static_cast<Operations>(c) == Operations::Add || static_cast<Operations>(c) == Operations::Subtract ||
           static_cast<Operations>(c) == Operations::Multiply || static_cast<Operations>(c) == Operations::Device ||
           static_cast<Operations>(c) == Operations::MODULO || static_cast<Operations>(c) == Operations::POWER;
}

std::string removeWhiteSpaces(std::string *string) {
    std::string result;
    for (char c: *string) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}

std::string getAndFilterUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return removeWhiteSpaces(&input);;
}

/**
 * Calculate one operation.
 * @param prompt The prompt in with a number, operator and a number
 * @return The result of the operation
 */
double calculate(std::string *prompt) {
    std::string firstNumber;
    std::string secondNumber;
    Operations operation;
    bool operatorFound = false;

    for (char c: *prompt) {
        std::cout << "Current char: " << c << std::endl;

        std::cout << isSupportedOperation(c) << std::endl;
        std::cout << (static_cast<int>(operation) == 1) << std::endl;
        if (isSupportedOperation(c)) {
            operation = Operations(c);
            operatorFound = true;
        } else if (operatorFound) {
            secondNumber += c;
        } else {
            firstNumber += c;
        }
    }

    std::cout << "First number: " << firstNumber << std::endl;
    std::cout << "Operation: " << static_cast<char>(operation) << std::endl;
    std::cout << "Second number: " << secondNumber << std::endl;

    double firstNumberDouble = std::stod(firstNumber);
    double secondNumberDouble = std::stod(secondNumber);

    switch (operation) {
        case Operations::Add:
            return firstNumberDouble + secondNumberDouble;
        case Operations::Subtract:
            return firstNumberDouble - secondNumberDouble;
        case Operations::Multiply:
            return firstNumberDouble * secondNumberDouble;
        case Operations::Device:
            return firstNumberDouble / secondNumberDouble;
        case Operations::MODULO:
            return static_cast<int>(firstNumberDouble) % static_cast<int>(secondNumberDouble);
        case Operations::POWER:
            return pow(firstNumberDouble, secondNumberDouble);
        default:
            throw std::invalid_argument("Invalid operation");
    }
}

int main() {
    std::cout << "Hello, Welcome to my calculator" << std::endl;

    while (true) {
        std::cout << "Please your calculation. (type help for supported operations)" << std::endl;
        // Get user input
        std::string userInput = getAndFilterUserInput();

        std::cout << "Filtered prompt: " << userInput << std::endl;

        // if user input is help, print help message and return to step 1
        if (userInput == "help") {
            std::cout << "Supported operations: +, -, *, /, %, ^" << std::endl;
            continue;
        }

        // check if user input has any unsupported operations


        // check if user input has unclosed parentheses

        // check if user input has an operator at the end

        // check if user input has a . at the end

        // check if modulo operator is used with a double

        // determine the order of operations

        // get the extract the values out of string


        // calculate the result
        double result = calculate(&userInput);

        // print result
        std::cout << "Result: " << result << std::endl;
    }
    return 0;
}
