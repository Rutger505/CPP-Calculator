#include <iostream>
#include <algorithm>
#include <map>

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


float calculate(std::string &input);

void solveOperation(float &left, float &right, char &operation);

bool isOperator(char c);

int main() {
    std::cout << "Welcome to my calculator" << std::endl;
    std::cout << "Enter your calculation (h for help, q to quit)" << std::endl;
    std::string input;
    while (true) {
        std::cout << ": " << std::flush;
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

    std::string left;
    int leftIndex;
    std::string right;
    int rightIndex;
    Operator op;
    int opIndex;
    bool opFound = false;

    bool firstOperationRecorded = false;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];

        if (isOperator(c)) {
            if (opFound) {
                firstOperationRecorded = true;
                
            }

            Operator currentOp = static_cast<Operator>(c);

            op = currentOp;
            opIndex = i;
            opFound = true;


        } else if (!opFound) {
            left += c;
        } else {
            right += c;
        }

    }
    std::cout << "expression with priority: " << left << " " << static_cast<char>(op) << " " << right << std::endl;


    return -1.0;
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
