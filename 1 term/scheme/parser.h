#pragma once

#include <object.h>
#include <tokenizer.h>
#include <memory>

std::shared_ptr<Object> Read(Tokenizer* tokenizer);

std::shared_ptr<Object> ListASTFromVector(std::vector<std::shared_ptr<Object>> list);

