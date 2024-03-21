#pragma once

#include <variant>
#include <istream>
#include <vector>
#include <error.h>
#include <sstream>

struct SymbolToken {
    std::string name;

    bool operator==(const SymbolToken& other) const {
        return name == other.name;
    }
};

struct QuoteToken {
    bool operator==(const QuoteToken&) const {
        return true;
    }
};

struct DotToken {
    bool operator==(const DotToken&) const {
        return true;
    }
};

enum class BracketToken { OPEN, CLOSE };

struct ConstantToken {
    int value;

    bool operator==(const ConstantToken& other) const {
        return value == other.value;
    }
};

using Token = std::variant<ConstantToken, BracketToken, SymbolToken, QuoteToken, DotToken>;

inline bool IsConstantToken(Token token) {
    return std::holds_alternative<ConstantToken>(token);
}

inline int GetConstantTokenValue(Token token) {
    return std::get<ConstantToken>(token).value;
}

inline bool IsSymbolToken(Token token) {
    return std::holds_alternative<SymbolToken>(token);
}

inline std::string GetSymbolTokenValue(Token token) {
    return std::get<SymbolToken>(token).name;
}

inline bool IsOpenBracket(Token token) {
    if (std::holds_alternative<BracketToken>(token)) {
        return std::get<BracketToken>(token) == BracketToken::OPEN;
    }
    return false;
}

inline bool IsCloseBracket(Token token) {
    if (std::holds_alternative<BracketToken>(token)) {
        return std::get<BracketToken>(token) == BracketToken::CLOSE;
    }
    return false;
}

inline bool IsDotToken(Token token) {
    return std::holds_alternative<DotToken>(token);
}

inline bool IsQuoteToken(Token token) {
    return std::holds_alternative<QuoteToken>(token);
}

inline void PutBack(std::string& str, std::istream* input) {
    while (!str.empty()) {
        input->putback(str.back());
        str.pop_back();
    }
}

inline bool IsDigit(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

inline void RemoveSpaces(std::istream* input) {
    while (input->peek() == ' ' || input->peek() == '\n') {
        input->get();
    }
}

inline ConstantToken ReadConstantToken(std::string& str, std::istream* input) {
    while (IsDigit(input->peek())) {
        str.push_back(input->get());
    }
    ConstantToken result{std::stoi(str)};
    PutBack(str, input);
    return result;
}

inline bool IsSymbolStart(char symbol) {
    static std::string required_symbols = "<=>*/#";
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') ||
           (required_symbols.find(symbol) != std::string::npos);
}

inline bool IsSymbolMid(char symbol) {
    return IsSymbolStart(symbol) || IsDigit(symbol) || symbol == '!' || symbol == '-' ||
           symbol == '?';
}

inline SymbolToken ReadSymbolToken(std::string& str, std::istream* input) {
    while (IsSymbolMid(input->peek())) {
        str.push_back(input->get());
    }
    SymbolToken result{str};
    PutBack(str, input);
    return result;
}

class Tokenizer {
private:
    std::istream* input_;

public:
    Tokenizer(std::istream* input) : input_(input) {
    }

    bool IsEnd() {
        RemoveSpaces(input_);
        return input_->peek() == EOF;
    }

    void Next() {
        if (IsEnd()) {
            return;
        }
        Token token = GetToken();
        size_t pos = 1;
        if (IsConstantToken(token)) {
            std::string str = std::to_string(GetConstantTokenValue(token));
            pos = str.size();
        } else if (IsSymbolToken(token)) {
            std::string str = GetSymbolTokenValue(token);
            pos = str.size();
        }
        while (pos) {
            input_->get();
            --pos;
        }
        if (IsConstantToken(token) && IsDigit(input_->peek())) {
            input_->get();
        }
        if (!IsEnd()) {
            GetToken();
        }
    }

    Token GetToken() {
        RemoveSpaces(input_);
        std::string str;
        char first_sym = input_->peek();
        if (first_sym == '(') {
            return BracketToken::OPEN;
        } else if (first_sym == ')') {
            return BracketToken::CLOSE;
        } else if (first_sym == '\'') {
            return QuoteToken();
        } else if (first_sym == '.') {
            return DotToken();
        } else if (IsDigit(first_sym)) {
            return ReadConstantToken(str, input_);
        } else if (first_sym == '+' || first_sym == '-') {
            str.push_back(input_->get());
            if (IsDigit(input_->peek())) {
                return ReadConstantToken(str, input_);
            } else {
                PutBack(str, input_);
                return SymbolToken{std::string(1, first_sym)};
            }
        } else if (IsSymbolStart(first_sym)) {
            return ReadSymbolToken(str, input_);
        } else {
            throw SyntaxError("STOP RIGHT THERE, CRIMINAL SCUM!");
        }
    }
};

