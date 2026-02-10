#include "calculator.h"
#include <iomanip>
#include <sstream>
#include <cmath>

Calculator::Calculator() : precision(15), lastResult(0.0) {}

double Calculator::calculate(const std::string& expression) {
    try {
        lastResult = parser.parse(expression);
        return lastResult;
    } catch (const std::exception& e) {
        throw;
    }
}

void Calculator::setPrecision(int digits) {
    if (digits < 1 || digits > 20) {
        throw std::runtime_error("Precision must be between 1 and 20");
    }
    precision = digits;
}

int Calculator::getPrecision() const {
    return precision;
}

void Calculator::setVariable(const std::string& name, double value) {
    variables[name] = value;
}

double Calculator::getVariable(const std::string& name) {
    if (variables.find(name) != variables.end()) {
        return variables[name];
    }
    throw std::runtime_error("Variable not defined: " + name);
}

bool Calculator::hasVariable(const std::string& name) const {
    return variables.find(name) != variables.end();
}

void Calculator::clearVariables() {
    variables.clear();
}

double Calculator::getLastResult() const {
    return lastResult;
}

void Calculator::setLastResult(double value) {
    lastResult = value;
}

std::string Calculator::formatResult(double value) const {
    // Handle special cases
    if (std::isnan(value)) return "NaN";
    if (std::isinf(value)) return (value > 0) ? "Infinity" : "-Infinity";

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string result = oss.str();

    // Remove trailing zeros
    size_t dotPos = result.find('.');
    if (dotPos != std::string::npos) {
        size_t lastNonZero = result.find_last_not_of('0');
        if (lastNonZero != std::string::npos && lastNonZero > dotPos) {
            result = result.substr(0, lastNonZero + 1);
        } else if (lastNonZero == dotPos) {
            result = result.substr(0, dotPos);
        }
    }

    return result;
}
