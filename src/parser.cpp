#include "parser.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

Parser::Parser() {
    initializeFunctions();
}

void Parser::initializeFunctions() {
    functionMap = {
        {"sin", 0}, {"cos", 1}, {"tan", 2},
        {"asin", 3}, {"acos", 4}, {"atan", 5},
        {"log", 6}, {"log10", 7}, {"ln", 8},
        {"sqrt", 9}, {"abs", 10}, {"floor", 11},
        {"ceil", 12}, {"round", 13}, {"exp", 14},
        {"pow", 15}
    };
}

std::vector<Parser::Token> Parser::tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < expression.length()) {
        if (std::isspace(expression[i])) {
            i++;
            continue;
        }

        if (std::isdigit(expression[i]) || expression[i] == '.') {
            std::string numStr;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                numStr += expression[i++];
            }
            
            // Check for scientific notation (e or E)
            if (i < expression.length() && (expression[i] == 'e' || expression[i] == 'E')) {
                size_t tempI = i + 1;
                // Handle optional + or - sign after e
                if (tempI < expression.length() && (expression[tempI] == '+' || expression[tempI] == '-')) {
                    tempI++;
                }
                // Check if there's at least one digit after e/E
                if (tempI < expression.length() && std::isdigit(expression[tempI])) {
                    numStr += expression[i++];
                    if (i < expression.length() && (expression[i] == '+' || expression[i] == '-')) {
                        numStr += expression[i++];
                    }
                    // Collect exponent digits
                    while (i < expression.length() && std::isdigit(expression[i])) {
                        numStr += expression[i++];
                    }
                }
            }
            
            Token token;
            token.type = TokenType::NUMBER;
            token.value = numStr;
            try {
                token.numValue = std::stod(numStr);
            } catch (const std::exception& e) {
                throw std::runtime_error("Invalid number format: " + numStr);
            }
            tokens.push_back(token);
            continue;
        }

        if (std::isalpha(expression[i])) {
            std::string name;
            while (i < expression.length() && (std::isalnum(expression[i]) || expression[i] == '_')) {
                name += expression[i++];
            }

            Token token;
            if (name == "pi") {
                token.type = TokenType::NUMBER;
                token.value = "pi";
                token.numValue = 3.14159265358979323846264338327950288;
            } else if (name == "e") {
                token.type = TokenType::NUMBER;
                token.value = "e";
                token.numValue = 2.71828182845904523536028747135266249;
            } else if (name == "phi") {
                token.type = TokenType::NUMBER;
                token.value = "phi";
                token.numValue = 1.61803398874989484820458683436563811;
            } else if (functionMap.count(name)) {
                token.type = TokenType::FUNCTION;
                token.value = name;
            } else {
                token.type = TokenType::VARIABLE;
                token.value = name;
            }
            tokens.push_back(token);
            continue;
        }

        switch (expression[i]) {
            case '+': {
                Token token;
                token.type = TokenType::PLUS;
                token.value = "+";
                tokens.push_back(token);
                i++;
                break;
            }
            case '-': {
                Token token;
                token.type = TokenType::MINUS;
                token.value = "-";
                tokens.push_back(token);
                i++;
                break;
            }
            case '*': {
                Token token;
                token.type = TokenType::MUL;
                token.value = "*";
                tokens.push_back(token);
                i++;
                break;
            }
            case '/': {
                Token token;
                token.type = TokenType::DIV;
                token.value = "/";
                tokens.push_back(token);
                i++;
                break;
            }
            case '^': {
                Token token;
                token.type = TokenType::POW;
                token.value = "^";
                tokens.push_back(token);
                i++;
                break;
            }
            case '%': {
                Token token;
                token.type = TokenType::MOD;
                token.value = "%";
                tokens.push_back(token);
                i++;
                break;
            }
            case '(': {
                Token token;
                token.type = TokenType::LPAREN;
                token.value = "(";
                tokens.push_back(token);
                i++;
                break;
            }
            case ')': {
                Token token;
                token.type = TokenType::RPAREN;
                token.value = ")";
                tokens.push_back(token);
                i++;
                break;
            }
            case ',': {
                Token token;
                token.type = TokenType::COMMA;
                token.value = ",";
                tokens.push_back(token);
                i++;
                break;
            }
            case '=': {
                Token token;
                token.type = TokenType::ASSIGN;
                token.value = "=";
                tokens.push_back(token);
                i++;
                break;
            }
            default:
                throw std::runtime_error(std::string("Unknown character: ") + expression[i]);
        }
    }

    Token endToken;
    endToken.type = TokenType::END;
    tokens.push_back(endToken);
    return tokens;
}

double Parser::parseFunction(const std::string& funcName, double arg) {
    if (funcName == "sin") return std::sin(arg);
    if (funcName == "cos") return std::cos(arg);
    if (funcName == "tan") return std::tan(arg);
    if (funcName == "asin") return std::asin(arg);
    if (funcName == "acos") return std::acos(arg);
    if (funcName == "atan") return std::atan(arg);
    if (funcName == "log") return std::log10(arg);
    if (funcName == "log10") return std::log10(arg);
    if (funcName == "ln") return std::log(arg);
    if (funcName == "sqrt") return std::sqrt(arg);
    if (funcName == "abs") return std::abs(arg);
    if (funcName == "floor") return std::floor(arg);
    if (funcName == "ceil") return std::ceil(arg);
    if (funcName == "round") return std::round(arg);
    if (funcName == "exp") return std::exp(arg);
    throw std::runtime_error("Unknown function: " + funcName);
}

double Parser::parseFactor(const std::vector<Token>& tokens, size_t& pos) {
    const Token& token = tokens[pos];

    if (token.type == TokenType::NUMBER) {
        pos++;
        return token.numValue;
    }

    if (token.type == TokenType::VARIABLE) {
        pos++;
        throw std::runtime_error("Variable not defined: " + token.value);
    }

    if (token.type == TokenType::FUNCTION) {
        std::string funcName = token.value;
        pos++;
        if (pos >= tokens.size() || tokens[pos].type != TokenType::LPAREN) {
            throw std::runtime_error("Expected '(' after function: " + funcName);
        }
        pos++;
        
        // Handle pow function with two arguments
        if (funcName == "pow") {
            double arg1 = parseExpression(tokens, pos);
            if (pos >= tokens.size() || tokens[pos].type != TokenType::COMMA) {
                throw std::runtime_error("pow() requires two arguments separated by comma");
            }
            pos++; // skip comma
            double arg2 = parseExpression(tokens, pos);
            if (pos >= tokens.size() || tokens[pos].type != TokenType::RPAREN) {
                throw std::runtime_error("Expected ')' after pow arguments");
            }
            pos++;
            return std::pow(arg1, arg2);
        }
        
        double arg = parseExpression(tokens, pos);
        if (pos >= tokens.size() || tokens[pos].type != TokenType::RPAREN) {
            throw std::runtime_error("Expected ')' after function argument");
        }
        pos++;
        return parseFunction(funcName, arg);
    }

    if (token.type == TokenType::LPAREN) {
        pos++;
        double result = parseExpression(tokens, pos);
        if (pos >= tokens.size() || tokens[pos].type != TokenType::RPAREN) {
            throw std::runtime_error("Expected ')' to match '('");
        }
        pos++;
        return result;
    }

    if (token.type == TokenType::MINUS) {
        pos++;
        return -parseFactor(tokens, pos);
    }

    if (token.type == TokenType::PLUS) {
        pos++;
        return parseFactor(tokens, pos);
    }

    throw std::runtime_error("Unexpected token");
}

double Parser::parseTerm(const std::vector<Token>& tokens, size_t& pos) {
    double result = parsePower(tokens, pos);

    while (pos < tokens.size()) {
        const Token& token = tokens[pos];
        if (token.type == TokenType::MUL) {
            pos++;
            result *= parsePower(tokens, pos);
        } else if (token.type == TokenType::DIV) {
            pos++;
            double divisor = parsePower(tokens, pos);
            if (divisor == 0) {
                throw std::runtime_error("Division by zero");
            }
            result /= divisor;
        } else if (token.type == TokenType::MOD) {
            pos++;
            double mod = parsePower(tokens, pos);
            if (mod == 0) {
                throw std::runtime_error("Modulo by zero");
            }
            result = std::fmod(result, mod);
        } else if (token.type == TokenType::FUNCTION || (token.type == TokenType::LPAREN && pos > 0)) {
            // Implicit multiplication: 2log(x) -> 2*log(x), 2(3+4) -> 2*(3+4)
            result *= parsePower(tokens, pos);
        } else {
            break;
        }
    }

    return result;
}

double Parser::parsePower(const std::vector<Token>& tokens, size_t& pos) {
    double result = parseFactor(tokens, pos);

    while (pos < tokens.size()) {
        const Token& token = tokens[pos];
        if (token.type == TokenType::POW) {
            pos++;
            result = std::pow(result, parseFactor(tokens, pos));
        } else if (token.type == TokenType::FUNCTION || 
                   (token.type == TokenType::NUMBER && token.value != "(" && token.value != ")")) {
            // Implicit multiplication: 2pi -> 2*pi (but not at end of expression)
            if (pos < tokens.size()) {
                result *= parseFactor(tokens, pos);
            } else {
                break;
            }
        } else {
            break;
        }
    }

    return result;
}

double Parser::parseExpression(const std::vector<Token>& tokens, size_t& pos) {
    double result = parseTerm(tokens, pos);

    while (pos < tokens.size()) {
        const Token& token = tokens[pos];
        if (token.type == TokenType::PLUS) {
            pos++;
            result += parseTerm(tokens, pos);
        } else if (token.type == TokenType::MINUS) {
            pos++;
            result -= parseTerm(tokens, pos);
        } else {
            break;
        }
    }

    return result;
}

double Parser::parse(const std::string& expression) {
    auto tokens = tokenize(expression);
    size_t pos = 0;
    return parseExpression(tokens, pos);
}
