#include "repl.h"
#include <iostream>
#include <sstream>
#include <algorithm>

REPL::REPL(Calculator& calc) : calculator(calc), running(false) {}

std::string REPL::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

void REPL::printWelcome() {
    std::cout << "\n========================================\n";
    std::cout << "        calcpp v1.0 - CLI Calculator\n";
    std::cout << "   Type 'help' for available commands\n";
    std::cout << "========================================\n\n";
}

void REPL::showHelp() {
    std::cout << "\n=== Available Commands ===\n";
    std::cout << "  help              - Show this help message\n";
    std::cout << "  history           - Show calculation history\n";
    std::cout << "  clear             - Clear calculation history\n";
    std::cout << "  precision <n>     - Set decimal precision (1-20)\n";
    std::cout << "  tofrac            - Convert last result to fraction\n";
    std::cout << "  vars              - Show all variables\n";
    std::cout << "  clearVars         - Clear all variables\n";
    std::cout << "  exit / quit       - Exit calculator\n\n";

    std::cout << "=== Operators ===\n";
    std::cout << "  +  -  *  /        - Basic arithmetic\n";
    std::cout << "  ^                 - Exponentiation (power)\n";
    std::cout << "  %                 - Modulo (remainder)\n\n";

    std::cout << "=== Functions ===\n";
    std::cout << "  Trigonometric: sin, cos, tan, asin, acos, atan\n";
    std::cout << "  Logarithmic:   log, log10, ln, exp\n";
    std::cout << "  Other:         sqrt, abs, floor, ceil, round\n\n";

    std::cout << "=== Constants ===\n";
    std::cout << "  pi                - Ratio of circumference to diameter\n";
    std::cout << "  e                 - Euler's number\n";
    std::cout << "  phi               - Golden ratio\n\n";

    std::cout << "=== Variables ===\n";
    std::cout << "  a = 5             - Assign variable\n";
    std::cout << "  a * 2             - Use variable in expression\n";
    std::cout << "  ans               - Last calculation result\n\n";
}

void REPL::showHistory() {
    if (history.empty()) {
        std::cout << "History is empty\n";
        return;
    }
    std::cout << "\n=== Calculation History ===\n";
    for (size_t i = 0; i < history.size(); i++) {
        std::cout << "[" << (i + 1) << "] " << history[i] << "\n";
    }
    std::cout << "\n";
}

void REPL::clearHistory() {
    history.clear();
    std::cout << "History cleared\n";
}

void REPL::processCommand(const std::string& input) {
    std::string cmd = trim(input);
    
    if (cmd.empty()) return;

    if (cmd == "exit" || cmd == "quit") {
        running = false;
        return;
    }

    if (cmd == "help") {
        showHelp();
        return;
    }

    if (cmd == "history") {
        showHistory();
        return;
    }

    if (cmd == "clear") {
        clearHistory();
        return;
    }

    if (cmd.substr(0, 9) == "precision") {
        std::istringstream iss(cmd);
        std::string precCmd;
        int precValue;
        iss >> precCmd >> precValue;
        try {
            calculator.setPrecision(precValue);
            std::cout << "Precision set to " << precValue << " digits\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        return;
    }

    if (cmd == "vars") {
        std::cout << "ans = " << calculator.formatResult(calculator.getLastResult()) << "\n";
        std::cout << "No user variables defined\n";
        return;
    }

    if (cmd == "clearVars") {
        calculator.clearVariables();
        std::cout << "Variables cleared\n";
        return;
    }

    if (cmd == "tofrac") {
        double result = calculator.getLastResult();
        // 簡単な分数変換アルゴリズム（連分数展開）
        double tolerance = 1e-9;
        long long maxDenom = 10000;
        
        long long bestNum = 1, bestDenom = 1;
        double bestError = std::abs(result - 1.0);
        
        for (long long denom = 1; denom <= maxDenom; denom++) {
            long long num = static_cast<long long>(std::round(result * denom));
            double error = std::abs(result - static_cast<double>(num) / denom);
            
            if (error < bestError) {
                bestError = error;
                bestNum = num;
                bestDenom = denom;
            }
            
            if (error < tolerance) break;
        }
        
        std::cout << "Fraction: " << bestNum << "/" << bestDenom << "\n";
        std::cout << "Decimal:  " << calculator.formatResult(static_cast<double>(bestNum) / bestDenom) << "\n";
        return;
    }

    size_t assignPos = cmd.find('=');
    if (assignPos != std::string::npos && assignPos > 0) {
        std::string varName = trim(cmd.substr(0, assignPos));
        std::string expression = trim(cmd.substr(assignPos + 1));
        
        if (!varName.empty() && std::isalpha(varName[0])) {
            try {
                double result = calculator.calculate(expression);
                calculator.setVariable(varName, result);
                std::cout << varName << " = " << calculator.formatResult(result) << "\n";
                history.push_back(varName + " = " + expression);
                return;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\n";
                return;
            }
        }
    }

    try {
        double result = calculator.calculate(cmd);
        std::cout << calculator.formatResult(result) << "\n";
        history.push_back(cmd);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void REPL::run() {
    running = true;
    printWelcome();

    while (running) {
        std::cout << "> ";
        std::string input;
        
        if (!std::getline(std::cin, input)) {
            break;
        }

        processCommand(input);
    }

    std::cout << "\nThank you for using calcpp!\n";
}
