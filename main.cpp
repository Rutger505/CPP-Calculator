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
double calculate(double firstNumber, Operations operation, double secondNumber) {
    switch (operation) {
        case Operations::Add:
            return firstNumber + secondNumber;
        case Operations::Subtract:
            return firstNumber - secondNumber;
        case Operations::Multiply:
            return firstNumber * secondNumber;
        case Operations::Device:
            return firstNumber / secondNumber;
        case Operations::MODULO:
            return static_cast<int>(firstNumber) % static_cast<int>(secondNumber);
        case Operations::POWER:
            return pow(firstNumber, secondNumber);
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


        // check if user input has unclosed parentheses
        int amountTrailingParentheses = 0;
        for (char c: str) {
            if (c == '(') {
                amountTrailingParentheses++;
            } else if (c == ')') {
                amountTrailingParentheses--;
            }
            if (amountTrailingParentheses < 0) {
                break;
            }
        }

        if (amountTrailingParentheses != 0) {
            std::cout << "Invalid parentheses" << std::endl;
            continue;
        }


        // check if user input has an operator at the end

        // check if user input number has a . at the end

        // check if modulo operator is used with a double

        // determine the order of operations

        // get the extract the values out of string
        std::string firstNumberString;
        std::string secondNumberString;
        Operations operation;
        bool operatorFound = false;
        for (char c: userInput) {
            if (isSupportedOperation(c)) {
                operation = Operations(c);
                operatorFound = true;
            } else if (operatorFound) {
                secondNumberString += c;
            } else {
                firstNumberString += c;
            }
        }
        double firstNumber = std::stod(firstNumberString);
        double secondNumber = std::stod(secondNumberString);

        // check if user input has any unsupported operations
        if (!isSupportedOperation(static_cast<char>(operation))) {
            std::cout << "Unsupported operation" << std::endl;
            continue;
        }


        // calculate the result
        double result = calculate(firstNumber, operation, secondNumber);

        // print result
        std::cout << result << std::endl;
    }
    return 0;
}
