#pragma once
#include <vector>
#include "Molecule.h"

void parseEquation(const std::string& equationStr, std::vector<Molecule>& reactants, std::vector<Molecule>& products);

class ChemicalEquation {
public:
    ChemicalEquation(const std::string& equationStr);
    std::vector<Molecule> reactants;
    std::vector<Molecule> products;
    std::string getBalancedEquationString() const;
};