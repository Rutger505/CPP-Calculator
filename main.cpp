#include <iostream>
#include <algorithm>

void printSupportedOperators();

void printHelp();

void preProcessInput(std::string &input);

void removeAllSpaces(std::string &input);

int main() {
    std::cout << "Welcome to my calculator" << std::endl;
    std::cout << "Enter your calculation (h for help, q to quit)" << std::endl;

    while (true) {
        // get user input
        std::string input;
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

    }

    std::cout << "Bye see you next time." << std::endl;
    return 0;
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
