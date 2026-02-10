#pragma once

#include <string>
#include <unordered_map>
#include "parser.h"

class Calculator {
public:
    Calculator();
    
    double calculate(const std::string& expression);
    void setPrecision(int digits);
    int getPrecision() const;
    void setVariable(const std::string& name, double value);
    double getVariable(const std::string& name);
    bool hasVariable(const std::string& name) const;
    void clearVariables();
    double getLastResult() const;
    void setLastResult(double value);
    
    std::string formatResult(double value) const;

private:
    Parser parser;
    std::unordered_map<std::string, double> variables;
    int precision;
    double lastResult;
};
