#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

class Parser {
public:
    enum class TokenType {
        NUMBER,
        PLUS,
        MINUS,
        MUL,
        DIV,
        POW,        // ^
        MOD,        // %
        LPAREN,
        RPAREN,
        FUNCTION,   // sin, cos, etc.
        VARIABLE,
        COMMA,
        ASSIGN,     // =
        SQRT,       // √
        END,
        UNKNOWN
    };

    struct Token {
        TokenType type;
        std::string value;
        double numValue;
    };

    Parser();
    std::vector<Token> tokenize(const std::string& expression);
    double parse(const std::string& expression);
    void setVariables(const std::unordered_map<std::string, double>* vars) {
        variables = vars;
    }

private:
    std::unordered_map<std::string, int> functionMap;
    const std::unordered_map<std::string, double>* variables = nullptr;
    void initializeFunctions();
    
    double parseExpression(const std::vector<Token>& tokens, size_t& pos);
    double parseTerm(const std::vector<Token>& tokens, size_t& pos);
    double parsePower(const std::vector<Token>& tokens, size_t& pos);
    double parseFactor(const std::vector<Token>& tokens, size_t& pos);
    double parseFunction(const std::string& funcName, double arg);
};
