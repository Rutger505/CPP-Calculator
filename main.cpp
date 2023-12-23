#include <iostream>
#include <ctgmath>
#include <vector>


enum class Operations {
    Add = '+',
    Subtract = '-',
    Multiply = '*',
    Devide = '/',
    MODULO = '%',
    POWER = '^'
};

bool isSupportedOperation(char c) {
    return static_cast<Operations>(c) == Operations::Add || static_cast<Operations>(c) == Operations::Subtract ||
           static_cast<Operations>(c) == Operations::Multiply || static_cast<Operations>(c) == Operations::Devide ||
           static_cast<Operations>(c) == Operations::MODULO || static_cast<Operations>(c) == Operations::POWER;
}

std::string removeWhiteSpaces(const std::string *string) {
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
    return removeWhiteSpaces(&input);
}

bool unSupportedCharactersInString(const std::string *string) {
    for (char c: *string) {
        if (!isSupportedOperation(c) && !isdigit(c) && c != '.') {
            return true;
        }
    }
    return false;
}

std::vector<Operations> operationsInCalculation(const std::string *string) {
    std::vector<Operations> operations;
    for (char c: *string) {
        if (isSupportedOperation(c)) {
            operations.push_back(Operations(c));

        }
    }
    return operations;
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
        case Operations::Devide:
            return firstNumber / secondNumber;
        case Operations::MODULO:
            return static_cast<int>(firstNumber) % static_cast<int>(secondNumber);
        case Operations::POWER:
            return pow(firstNumber, secondNumber);
        default:
            throw std::invalid_argument("Invalid operation");
    }
}

std::tuple<double, Operations, double>
getOperationAroundOperator(const std::string *completeOperation, Operations operatorChar) {
    std::vector<char> firstNumberChars;
    std::vector<char> secondNumberChars;

    int indexOperator = completeOperation->find(static_cast<char>(operatorChar));

    // firstNumberString
    int currentIndex = indexOperator;
    do {
        currentIndex--;
        if (currentIndex < 0) {
            break;
        }
        char currentChar = completeOperation->at(currentIndex);
        if (isSupportedOperation(currentChar)) {
            break;
        }
        firstNumberChars.insert(firstNumberChars.begin(), currentChar);
    } while (true);

    // secondNumberString
    currentIndex = indexOperator;
    do {
        currentIndex++;
        if (currentIndex >= completeOperation->length()) {
            break;
        }
        char currentChar = completeOperation->at(currentIndex);
        if (isSupportedOperation(currentChar)) {
            break;
        }
        secondNumberChars.push_back(currentChar);
    } while (true);

    double firstNumber = std::stod(std::string(firstNumberChars.begin(), firstNumberChars.end()));
    double secondNumber = std::stod(std::string(secondNumberChars.begin(), secondNumberChars.end()));

    return std::make_tuple(firstNumber, operatorChar, secondNumber);
}

void setResultOfOperationInString(std::string *completeOperation, Operations operatorChar, double result) {
    int indexOperator = completeOperation->find(static_cast<char>(operatorChar));
    int indexStartOperation;
    int indexEndOperation;
    // firstIndex
    int currentIndex = indexOperator;
    do {
        currentIndex--;
        if (currentIndex < 0) {
            break;
        }
        char currentChar = completeOperation->at(currentIndex);
        if (isSupportedOperation(currentChar)) {
            break;
        }
        indexStartOperation = currentIndex;
    } while (true);

    // secondIndex
    currentIndex = indexOperator;
    do {
        currentIndex++;
        if (currentIndex >= completeOperation->length()) {
            break;
        }
        char currentChar = completeOperation->at(currentIndex);
        if (isSupportedOperation(currentChar)) {
            break;
        }
        indexEndOperation = currentIndex;
    } while (true);


    completeOperation->replace(indexStartOperation, indexEndOperation, std::to_string(result));
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

        // check if user input has any unsupported characters (only numbers, points and operators are allowed)
        if (unSupportedCharactersInString(&userInput)) {
            std::cout << "Unsupported characters" << std::endl;
            continue;
        }

        // check if user input has an operator at the end


        // check if user input number has a . at the end

        // check if modulo operator is used with a double

        // get all operations in the calculation
        std::vector<Operations> operations = operationsInCalculation(&userInput);

        // determine the order of operations
        // modulos and power first
        // then multiply and divide
        // then add and subtract
        std::vector<Operations> operationsInOrder;
        for (Operations operation: operations) {
            if (operation == Operations::MODULO || operation == Operations::POWER) {
                operationsInOrder.push_back(operation);
            }
        }
        for (Operations operation: operations) {
            if (operation == Operations::Multiply || operation == Operations::Devide) {
                operationsInOrder.push_back(operation);
            }
        }
        for (Operations operation: operations) {
            if (operation == Operations::Add || operation == Operations::Subtract) {
                operationsInOrder.push_back(operation);
            }
        }

        for (Operations operater: operationsInOrder) {

            // get the extract the values out of string
            auto tuple = getOperationAroundOperator(&userInput, operater);
            double firstNumber = std::get<0>(tuple);
            Operations operation = std::get<1>(tuple);
            double secondNumber = std::get<2>(tuple);


            // check if modulo operator is used with a double
            if (operation == Operations::MODULO && (firstNumber != static_cast<int>(firstNumber) ||
                                                    secondNumber != static_cast<int>(secondNumber))) {
                std::cout << "Modulo operator can only be used with integers" << std::endl;
                continue;
            }


            // calculate the result
            double result = calculate(firstNumber, operation, secondNumber);

            // replace the operation with the result
            setResultOfOperationInString(&userInput, operation, result);
        }

        // print result
        std::cout << "Result: " << userInput << std::endl;

    }
    return 0;
}
