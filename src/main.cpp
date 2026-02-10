#include "calculator.h"
#include "repl.h"
#include <iostream>
#include <string>

void showVersion() {
    std::cout << "calcpp v1.0.0 - CLI Calculator\n";
    std::cout << "Built with C++17\n";
}

void showUsage() {
    std::cout << "Usage: calcpp [options] [expression]\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help         Show this help message\n";
    std::cout << "  -v, --version      Show version information\n";
    std::cout << "  -p, --precision N  Set precision (1-20 digits)\n\n";
    std::cout << "Examples:\n";
    std::cout << "  calcpp \"3 + 5 * 2\"\n";
    std::cout << "  calcpp \"sqrt(16)\"\n";
    std::cout << "  calcpp \"sin(pi/2)\"\n";
    std::cout << "  calcpp              (interactive mode)\n";
}

int main(int argc, char* argv[]) {
    Calculator calculator;

    // No arguments - start REPL
    if (argc == 1) {
        REPL repl(calculator);
        repl.run();
        return 0;
    }

    // Parse arguments
    std::string expression;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            showUsage();
            return 0;
        }
        if (arg == "-v" || arg == "--version") {
            showVersion();
            return 0;
        }
        if (arg == "-p" || arg == "--precision") {
            if (i + 1 < argc) {
                try {
                    int precision = std::stoi(argv[++i]);
                    calculator.setPrecision(precision);
                } catch (const std::exception& e) {
                    std::cerr << "Error: Invalid precision value\n";
                    return 1;
                }
            } else {
                std::cerr << "Error: -p/--precision requires a value\n";
                return 1;
            }
        } else if (!arg.empty() && arg[0] != '-') {
            // Treat as expression
            if (!expression.empty()) {
                expression += " ";
            }
            expression += arg;
        }
    }

    // Calculate and output result
    try {
        double result = calculator.calculate(expression);
        std::cout << calculator.formatResult(result) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
