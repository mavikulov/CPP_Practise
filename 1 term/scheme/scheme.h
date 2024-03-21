#pragma once

#include <string>
#include "parser.h"
#include "tokenizer.h"
#include "scheme.h"
#include "error.h"
#include <sstream>

class Scheme {
public:
    std::string Evaluate(const std::string& expr);
};
