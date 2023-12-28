#include <cmath>
#include <iostream>
#include <algorithm>

constexpr char ADD = '+';
constexpr char SUBTRACT = '-';
constexpr char MULTIPLY = 'x';
constexpr char DIVIDE = '/';
constexpr char POWER = '^';
constexpr char MODULO = '%';

void printSupportedOperators();

void printHelp();

void preProcessInput(std::string &input);

void removeAllSpaces(std::string &input);

float calculate(std::string expression);

float solveOperation(float number1, float number2, char op);

bool isOperator(char c);

int getPriority(char op);

float parseStringToFloat(const std::string &str);

bool isFloat(const std::string &str);

int main() {
    std::cout << "Welcome to my calculator" << std::endl;
    std::cout << "Enter your calculation (h for help, q to quit)" << std::endl;
    std::string input;
    while (true) {
        std::cout << ">" << std::flush;
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

        float result;
        try {
            result = calculate(input);
        } catch (std::invalid_argument &e) {
            std::cout << "Invalid input" << std::endl;
            continue;
        } catch (std::out_of_range &e) {
            std::cout << "Invalid input" << std::endl;
            continue;
        }

        std::cout << "Result: " << result << std::endl;
    }

    std::cout << "Bye see you next time." << std::endl;
    return 0;
}


/**
 * Calculates the result of the given input.
 * @param input The input to calculate: 1+4/6.
 * @return The result of the calculation.
 */
float calculate(std::string expression) {
    while (!isFloat(expression)) {
        std::string priorityNum1;
        std::string priorityNum2;
        char priorityOp = '\0';
        size_t priorityExpressionStart = -1;
        size_t priorityExpressionEnd = -1;

        std::string currentNum1;
        std::string currentNum2;
        char currentOp;
        bool currentOpFound = false;
        size_t currentExpressionStart = 0;
        size_t currentExpressionEnd = 0;

        bool opPrevious = false;

        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];
            opPrevious = isOperator(expression[i - 1]) && !opPrevious;
            bool charIsOp = isOperator(c) && !opPrevious;
            bool endCurrentExpression = !charIsOp && (isOperator(expression[i + 1]) || i + 1 >= expression.length());

            // Parse the char
            if (charIsOp) {
                currentOp = c;
                currentOpFound = true;
            } else if (!currentOpFound) {
                currentNum1 += c;
            } else {
                currentNum2 += c;
            }
            currentExpressionEnd++;

            // Check to update priority values
            if (endCurrentExpression && currentOpFound) {
                if (getPriority(currentOp) > getPriority(priorityOp)) {
                    priorityNum1 = currentNum1;
                    priorityNum2 = currentNum2;
                    priorityOp = currentOp;
                    priorityExpressionStart = currentExpressionStart;
                    priorityExpressionEnd = currentExpressionEnd;
                }

                currentNum1 = currentNum2;
                currentNum2 = "";
                currentOpFound = false;
                currentExpressionStart = i - currentNum1.length() + 1;
                currentExpressionEnd = i + 1;
            }
        }

        float parcedPriorityNumber1 = parseStringToFloat(priorityNum1);
        float parcedPriorityNumber2 = parseStringToFloat(priorityNum2);
        float priorityExpressionResult = solveOperation(parcedPriorityNumber1, parcedPriorityNumber2, priorityOp);

        expression =
                expression.substr(0, priorityExpressionStart) +
                std::to_string(priorityExpressionResult) +
                expression.substr(priorityExpressionEnd);
    }

    return parseStringToFloat(expression);
}

float solveOperation(float number1, float number2, char op) {
    switch (op) {
        case ADD:
            return number1 + number2;
        case SUBTRACT:
            return number1 - number2;
        case MULTIPLY:
            return number1 * number2;
        case DIVIDE:
            return number1 / number2;
        case POWER:
            return std::pow(number1, number2);
        case MODULO:
            return std::fmod(number1, number2);
        default:
            throw std::invalid_argument("Invalid operator");
    }
}

int getPriority(char op) {
    switch (op) {
        case ADD:
        case SUBTRACT:
            return 1;
        case MULTIPLY:
        case DIVIDE:
        case MODULO:
            return 2;
        case POWER:
            return 3;
        default:
            return 0;
    }
}

float parseStringToFloat(const std::string &str) {
    try {
        size_t pos;
        float result = std::stof(str, &pos);

        // Check if the entire string was successfully converted
        if (pos != str.length()) {
            throw std::invalid_argument("Invalid characters in the string");
        }

        return result;
    } catch (const std::invalid_argument &e) {
        throw std::invalid_argument("Invalid float value: " + std::string(e.what()));
    } catch (const std::out_of_range &e) {
        throw std::out_of_range("Float value out of range: " + std::string(e.what()));
    }
}

bool isFloat(const std::string &str) {
    try {
        parseStringToFloat(str);
        return true;
    } catch (const std::invalid_argument &e) {
        return false;
    } catch (const std::out_of_range &e) {
        return false;
    }
}

bool isOperator(char c) {
    return c == ADD || c == SUBTRACT || c == MULTIPLY || c == DIVIDE || c == POWER || c == MODULO;
}

void printHelp() {
    printSupportedOperators();
}

void printSupportedOperators() {
    std::cout << "Supported operations are: ";
    std::cout << ADD << ", ";
    std::cout << SUBTRACT << ", ";
    std::cout << MULTIPLY << ", ";
    std::cout << DIVIDE << ", ";
    std::cout << POWER << ", ";
    std::cout << MODULO << std::endl;
}

void preProcessInput(std::string &input) {
    removeAllSpaces(input);
}

void removeAllSpaces(std::string &input) {
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
}



