#pragma once

#include <string>
#include "calculator.h"

class REPL {
public:
    REPL(Calculator& calc);
    void run();

private:
    Calculator& calculator;
    std::vector<std::string> history;
    bool running;
    
    void printWelcome();
    void processCommand(const std::string& input);
    void showHelp();
    void showHistory();
    void clearHistory();
    std::string trim(const std::string& str);
};
