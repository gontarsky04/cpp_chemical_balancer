#include "ChemicalEquation.h"
#include "FormulaParser.h"
#include <sstream>

std::string ChemicalEquation::getBalancedEquationString() const {
    auto sideToString = [](const std::vector<Molecule>& side) {
        std::stringstream ss;
        for (size_t i = 0; i < side.size(); ++i) {
            const auto& mol = side[i];
            if (mol.coefficient != 1)
                ss << mol.coefficient;
            ss << mol.formula;
            if (i != side.size() - 1)
                ss << " + ";
        }
        return ss.str();
    };
    std::stringstream finalEq;
    finalEq << sideToString(reactants) << " -> " << sideToString(products);
    return finalEq.str();
}

void parseEquation(const std::string& equationStr,
                    std::vector<Molecule>& reactants,
                    std::vector<Molecule>& products);

ChemicalEquation::ChemicalEquation(const std::string& equationStr) {
    parseEquation(equationStr, reactants, products);
}