#pragma once
#include <string>
#include <map>
#include "Element.h"

class FormulaParser {
    const std::string& formula;
    size_t pos;
    std::map<Element, int> parseGroup();
	std::string parseElementSymbol();
	int parseNumber();
public:
    FormulaParser(const std::string& formula);
    std::map<Element, int> parse();
};