#include <iostream>
#include "../backend/ChemicalEquation.h"
#include "../backend/ChemicalBalancer.h"

int main() {
    std::cout << "Podaj rownanie chemiczne (np. H2 + O2 -> H2O): ";
    std::string input;
    std::getline(std::cin, input);
    try {
        ChemicalEquation eq(input);
		balanceEquation(eq);
		std::cout << "\nZbilansowane rownanie:\n";
        std::cout << eq.getBalancedEquationString() << "\n";
    } catch (const std::exception& ex) {
        std::cerr << "Blad: " << ex.what() << std::endl;
    }
    return 0;
}
