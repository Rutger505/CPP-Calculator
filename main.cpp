#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <valarray>

enum class Operator {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    MODULO
};

void printSupportedOperators();

void printHelp();

void preProcessInput(std::string &input);

void removeAllSpaces(std::string &input);

float calculate(std::string &expression);

float solveOperation(float &number1, float &number2, Operator &op);

bool isOperator(char c);

Operator getOperator(char c);

int main() {
    std::cout << "Welcome to my calculator" << std::endl;
    std::cout << "Enter your calculation (h for help, q to quit)" << std::endl;
    std::string input;
    while (true) {
        std::cout << "> " << std::flush;
        // get user input
        std::getline(std::cin, input);

        // check if user wants to quit
        if (input == "q") {
            break;
        }

        // check if user wants help
        if (input == "h" || input == "help") {
            printHelp();
            continue;
        }

        preProcessInput(input);

        std::cout << "Preprocessed input: " << input << std::endl;

        std::cout << "Result: " << calculate(input) << std::endl;
    }

    std::cout << "Bye see you next time." << std::endl;
    return 0;
}


int getPriority(Operator op) {
    static std::map<Operator, int> priorityMap = {
            {Operator::ADD,      1},
            {Operator::SUBTRACT, 1},
            {Operator::MULTIPLY, 2},
            {Operator::DIVIDE,   2},
            {Operator::POWER,    3},
            {Operator::MODULO,   3}
    };

    auto it = priorityMap.find(op);
    if (it != priorityMap.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Operator not found in priority map");
    }
}


/**
 * Calculates the result of the given input. Recursive function that claculates 1 operation at a time.
 * @param input The input to calculate: 1+4/6.
 * @return The result of the calculation.
 */
float calculate(std::string &expression) {

    // save the first number
    // save first number index
    // save the operator
    // save the operator index
    // save the second number
    // save the second number index

    // if the operatior that is next is a hight priority operator save the new operator and the next number

    // after the whole input is prosseces calculate the first oparation

    // replace the operation with the result

    // call the function again with the new expression
    bool startedSecond = false;

    std::string priorityNumber1;
    std::string priorityNumber2;
    Operator priorityOp;
    int priorityOperationStart = -1;
    int priorityOperationEnd = -1;

    std::string currentNumber1;
    std::string currentNumber2;
    Operator currentOp;
    bool currentOpFound = false;
    int currentOperationStart = -1;
    int currentOperationEnd = -1;

    // current operation stats


    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        bool opPrevious = isOperator(expression[i - 1]) && !opPrevious;

        bool firstOperationComplete = !priorityNumber1.empty() && !priorityNumber2.empty();

        if (!firstOperationComplete) {
            if (isOperator(c) && !opPrevious) {
                currentOp = getOperator(c);
                currentOpFound = true;
            } else if (!currentOpFound) {
                currentNumber1 += c;

                if (currentOperationStart == -1) {
                    currentOperationStart = i;
                }
            } else {
                currentNumber2 += c;
                if (currentOperationEnd == -1) {
                    currentOperationEnd = i;
                } else {
                    currentOperationEnd++;
                }
            }

            bool nextIsNewOperation =
                    (!currentOpFound && !isOperator(c) && isOperator(expression[i + 1])) ||
                    expression[i + 1] == '\0'; // Null char
            if (nextIsNewOperation) {
                priorityNumber1 = currentNumber1;
                priorityNumber2 = currentNumber2;
                priorityOp = currentOp;
                priorityOperationStart = currentOperationStart;
                priorityOperationEnd = currentOperationEnd;
            }
        } else if (isOperator(c) && !opPrevious) {
        }
//        else {
//            throw std::runtime_error("Invalid input");
//        }


    }

    std::cout << "expression with priority: " << priorityNumber1 << " "
              << priorityNumber2 << std::endl;

    float number1 = std::stof(priorityNumber1);
    float number2 = std::stof(priorityNumber2);

    return solveOperation(number1, number2, priorityOp);
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

void printSupportedOperators() {
    std::cout << "Supported operations are: +, -, *, /, ^, %" << std::endl;
}

void printHelp() {
    printSupportedOperators();
}

void preProcessInput(std::string &input) {
    removeAllSpaces(input);
}

void removeAllSpaces(std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
}


float solveOperation(float &number1, float &number2, Operator &op) {
    switch (op) {
        case Operator::ADD:
            return number1 + number2;
        case Operator::SUBTRACT:
            return number1 - number2;
        case Operator::MULTIPLY:
            return number1 * number2;
        case Operator::DIVIDE:
            return number1 / number2;
        case Operator::POWER:
            return std::pow(number1, number2);
        case Operator::MODULO:
            return static_cast<int>(number1) % static_cast<int>(number2);
        default:
            throw std::runtime_error("Invalid operator");
    }

}

Operator getOperator(char c) {
    switch (c) {
        case '+' :
            return Operator::ADD;
        case '-' :
            return Operator::SUBTRACT;
        case '*' :
            return Operator::MULTIPLY;
        case '/' :
            return Operator::DIVIDE;
        case '^' :
            return Operator::POWER;
        case '%' :
            return Operator::MODULO;
        default:
            throw std::runtime_error("Invalid operator");
    }
}
