#include <object.h>
#include <parser.h>
#include <tokenizer.h>
#include <stdexcept>
#include <memory>

std::shared_ptr<Object> ListASTFromVector(std::vector<std::shared_ptr<Object>> list) {
    std::shared_ptr<Object> result = std::make_shared<Cell>();
    if (list.empty()) {
        return result;
    }
    auto cur = result;
    auto prev = cur;
    for (size_t i = 0; i < list.size(); ++i) {
        if (Is<Dot>(list[i])) {
            if (i + 2 != list.size() || i == 0) {
                throw SyntaxError("Wrong Syntax");
            }
            As<Cell>(prev)->GetSecond() = list.back();
            break;
        } else {
            As<Cell>(cur)->GetFirst() = list[i];
            if (i != list.size() - 1) {
                As<Cell>(cur)->GetSecond() = std::make_shared<Cell>();
            }
        }
        prev = cur;
        cur = As<Cell>(cur)->GetSecond();
    }
    return result;
}

std::shared_ptr<Object> ReadImpl(Tokenizer* tokenizer, bool is_list = false);

std::shared_ptr<Object> ReadList(Tokenizer* tokenizer) {
    tokenizer->Next();
    std::vector<std::shared_ptr<Object>> list;
    while (true) {
        if (IsCloseBracket(tokenizer->GetToken())) {
            break;
        }
        list.push_back(ReadImpl(tokenizer, true));
    }
    if (list.empty()) {
        return nullptr;
    }
    return ListASTFromVector(list);
}

std::shared_ptr<Object> ReadImpl(Tokenizer* tokenizer, bool is_list) {
    auto token = tokenizer->GetToken();
    std::shared_ptr<Object> result;
    if (IsOpenBracket(token)) {
        result = ReadList(tokenizer);
    } else if (IsConstantToken(token)) {
        result = std::make_shared<Number>(GetConstantTokenValue(token));
    } else if (IsQuoteToken(token)) {
        auto str = "quote";
        auto first = std::make_shared<Symbol>(str);
        result = std::make_shared<Cell>();
        As<Cell>(result)->GetFirst() = first;
        tokenizer->Next();
        auto argument = ReadImpl(tokenizer);
        auto second_cell = std::make_shared<Cell>();
        second_cell->GetFirst() = argument;
        As<Cell>(result)->GetSecond() = second_cell;
        return result;
    } else if (IsSymbolToken(token)) {
        auto str = GetSymbolTokenValue(token);
        if (str == "#t" || str == "#f") {
            result = std::make_shared<Bool>(str);
        } else {
            result = std::make_shared<Symbol>(GetSymbolTokenValue(token));
        }
    } else if (IsDotToken(token) && is_list) {
        result = std::make_shared<Dot>();
    } else {
        throw SyntaxError("Wrong Syntax");
    }
    tokenizer->Next();
    return result;
}

std::shared_ptr<Object> Read(Tokenizer* tokenizer) {
    auto result = ReadImpl(tokenizer);
    if (!tokenizer->IsEnd()) {
        throw SyntaxError("Wrong Syntax");
    }
    return result;
}
