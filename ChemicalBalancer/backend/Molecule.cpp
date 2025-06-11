#include "Molecule.h"
#include "FormulaParser.h"

Molecule::Molecule(const std::string& formula_) : formula(formula_) {
    FormulaParser parser(formula_);
    elements = parser.parse();
}