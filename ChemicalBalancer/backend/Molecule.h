#pragma once
#include <map>
#include "Element.h"

class Molecule {
public:
    Molecule(const std::string& formula_);
    std::string formula;
    std::map<Element, int> elements;
    int coefficient = 1;
};
