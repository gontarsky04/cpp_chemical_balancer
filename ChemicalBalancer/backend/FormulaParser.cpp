#include "FormulaParser.h"
#include <iostream>

FormulaParser::FormulaParser(const std::string& formula) : formula(formula), pos(0) {}

std::map<Element, int> FormulaParser::parse() {
    auto result = parseGroup();
    if (pos != formula.length()) {
        throw std::runtime_error("Nieprawidłowy koniec wzoru: " + formula.substr(pos));
    }
    return result;
}

std::map<Element, int> FormulaParser::parseGroup() {
    std::map<Element, int> counts;
    while (pos < formula.length()) {
        char current = formula[pos];
        if (current == '(') {
            ++pos;
            auto innerGroup = parseGroup();
            if (pos >= formula.length() || formula[pos] != ')') {
                throw std::runtime_error("Brakujący nawias zamykający w: " + formula);
            }
            ++pos;
            int multiplier = parseNumber();
            for (auto& [el, cnt] : innerGroup) {
                counts[el] += cnt * multiplier;
            }
        }
        else if (current == ')') {
            break;
        }
        else if (std::isupper(current)) {
            std::string symbol = parseElementSymbol();
            auto maybeElement = symbolToElement(symbol);
            if (!maybeElement.has_value()) {
                throw std::runtime_error("Nieznany pierwiastek: " + symbol);
            }
            Element el = maybeElement.value();
            int number = parseNumber();
            counts[el] += number;
        }
        else {
            throw std::runtime_error(std::string("Nieoczekiwany znak: ") + current);
        }
    }
    return counts;
}
std::string FormulaParser::parseElementSymbol() {
    std::string symbol;
    symbol += formula[pos++];
	if (pos < formula.length() && std::islower(formula[pos])) {
        symbol += formula[pos++];
    }
    return symbol;
}
int FormulaParser::parseNumber() {
    int number = 0;
    while (pos < formula.length() && std::isdigit(formula[pos])) {
        number = number * 10 + (formula[pos] - '0');
        ++pos;
    }
    return number == 0 ? 1 : number;
}