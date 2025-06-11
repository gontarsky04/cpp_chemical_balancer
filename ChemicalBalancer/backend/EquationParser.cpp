#include "ChemicalEquation.h"
#include "FormulaParser.h"
#include "Molecule.h"
#include <sstream>
#include <cctype>

std::string removeSpaces(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (!std::isspace(c))
            result += c;
    }
    return result;
}

void parseEquation(const std::string& equationStr,
                    std::vector<Molecule>& reactants,
                    std::vector<Molecule>& products) {
    std::string eqNoSpaces = removeSpaces(equationStr);
    size_t arrowPos = eqNoSpaces.find("->");
    if (arrowPos == std::string::npos) {
        throw std::runtime_error("Równanie musi zawierać '->'");
    }
    std::string leftSide = eqNoSpaces.substr(0, arrowPos);
    std::string rightSide = eqNoSpaces.substr(arrowPos + 2);
    auto parseSide = [](const std::string& sideStr) -> std::vector<Molecule> {
        std::vector<Molecule> molecules;
        std::stringstream ss(sideStr);
        std::string molStr;
        while (std::getline(ss, molStr, '+')) {
            if (molStr.empty()) continue;
            Molecule mol(molStr);
            FormulaParser parser(molStr);
            mol.elements = parser.parse();
            mol.coefficient = 1;
            molecules.push_back(mol);
        }
        return molecules;
    };
    reactants = parseSide(leftSide);
    products = parseSide(rightSide);
}