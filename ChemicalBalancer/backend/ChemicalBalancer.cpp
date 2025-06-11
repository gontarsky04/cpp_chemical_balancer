#include "ChemicalEquation.h"
#include "Element.h"
#include <Eigen/Dense>
#include <set>
#include <vector>
#include <map>
#include <cmath>

std::vector<Element> getAllElements(const ChemicalEquation& eq) {
    std::set<Element> elementsSet;
    for (const auto& mol : eq.reactants)
        for (const auto& [el, _] : mol.elements)
            elementsSet.insert(el);
    for (const auto& mol : eq.products)
        for (const auto& [el, _] : mol.elements)
            elementsSet.insert(el);
    return std::vector<Element>(elementsSet.begin(), elementsSet.end());
}

int gcd(int a, int b) {
    return b == 0 ? std::abs(a) : gcd(b, a % b);
}

int gcd(const std::vector<int>& nums) {
    int result = nums[0];
    for (int i = 1; i < (int)nums.size(); ++i)
        result = gcd(result, nums[i]);
    return result;
}

std::vector<int> scaleAndSimplify(const Eigen::VectorXd& solution) {
    std::vector<int> intCoeffs;
    double multiplier = 1000.0;
    for (int i = 0; i < solution.size(); ++i) {
        intCoeffs.push_back(static_cast<int>(std::round(solution[i] * multiplier)));
    }
    int wsp_gcd = gcd(intCoeffs);
    for (int& c : intCoeffs)
        c /= wsp_gcd;
    return intCoeffs;
}

void balanceEquation(ChemicalEquation& eq) {
    auto elements = getAllElements(eq);
    int nElements = elements.size();
    int nMolecules = (int)eq.reactants.size() + (int)eq.products.size();
    Eigen::MatrixXd matrix(nElements, nMolecules);
    matrix.setZero();
    for (int i = 0; i < nElements; ++i) {
        Element el = elements[i];
        for (int j = 0; j < (int)eq.reactants.size(); ++j) {
            int count = 0;
            auto it = eq.reactants[j].elements.find(el);
            if (it != eq.reactants[j].elements.end()) count = it->second;
            matrix(i, j) = count;
        }
        for (int j = 0; j < (int)eq.products.size(); ++j) {
            int count = 0;
            auto it = eq.products[j].elements.find(el);
            if (it != eq.products[j].elements.end()) count = it->second;
            matrix(i, j + (int)eq.reactants.size()) = -count;
        }
    }

#ifdef DEBUG
    std::cout << "Macierz bilansowania:\n" << matrix << "\n";
#endif
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(matrix, Eigen::ComputeFullV);
    Eigen::MatrixXd V = svd.matrixV();
    Eigen::VectorXd coeffs = V.col(V.cols() - 1);
    double minCoeff = coeffs.minCoeff();
    coeffs = coeffs.array() / minCoeff;
    coeffs = coeffs.array().abs();
    std::vector<int> intCoeffs = scaleAndSimplify(coeffs);
    for (size_t i = 0; i < eq.reactants.size(); ++i) {
        eq.reactants[i].coefficient = intCoeffs[i];
    }
    for (size_t i = 0; i < eq.products.size(); ++i) {
        eq.products[i].coefficient = intCoeffs[i + eq.reactants.size()];
    }

#ifdef DEBUG
    std::cout << "\nZbalansowane równanie:\n";
    for (size_t i = 0; i < eq.reactants.size(); ++i) {
        int coeff = eq.reactants[i].coefficient;
        if (coeff != 1) std::cout << coeff;
        std::cout << eq.reactants[i].formula;
        if (i != eq.reactants.size() - 1) std::cout << " + ";
    }
    std::cout << " -> ";
    for (size_t i = 0; i < eq.products.size(); ++i) {
        int coeff = eq.products[i].coefficient;
        if (coeff != 1) std::cout << coeff;
        std::cout << eq.products[i].formula;
        if (i != eq.products.size() - 1) std::cout << " + ";
    }
    std::cout << std::endl;
#endif
}