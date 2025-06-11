#ifndef ELEMENT_H
#define ELEMENT_H

#pragma once
#include <string>
#include <optional>
#include <map>

enum class Element {
    H, He,
    Li, Be, B, C, N, O, F, Ne,
    Na, Mg, Al, Si, P, S, Cl, Ar,
    K, Ca, Sc, Ti, V, Cr, Mn, Fe,
    Co, Ni, Cu, Zn, Ga, Ge, As, Se,
    Br, Kr, Rb, Sr, Y, Zr, Nb, Mo,
    Tc, Ru, Rh, Pd, Ag, Cd, In, Sn,
    Sb, Te, I, Xe
};

inline const std::map<Element, std::string> elementToSymbol = {
    {Element::H, "H"},   {Element::He, "He"},
    {Element::Li, "Li"}, {Element::Be, "Be"},
    {Element::B, "B"},   {Element::C, "C"},
    {Element::N, "N"},   {Element::O, "O"},
    {Element::F, "F"},   {Element::Ne, "Ne"},
    {Element::Na, "Na"}, {Element::Mg, "Mg"},
    {Element::Al, "Al"}, {Element::Si, "Si"},
    {Element::P, "P"},   {Element::S, "S"},
    {Element::Cl, "Cl"}, {Element::Ar, "Ar"},
    {Element::K, "K"},   {Element::Ca, "Ca"},
    {Element::Sc, "Sc"}, {Element::Ti, "Ti"},
    {Element::V, "V"},   {Element::Cr, "Cr"},
    {Element::Mn, "Mn"}, {Element::Fe, "Fe"},
    {Element::Co, "Co"}, {Element::Ni, "Ni"},
    {Element::Cu, "Cu"}, {Element::Zn, "Zn"},
    {Element::Ga, "Ga"}, {Element::Ge, "Ge"},
    {Element::As, "As"}, {Element::Se, "Se"},
    {Element::Br, "Br"}, {Element::Kr, "Kr"},
    {Element::Rb, "Rb"}, {Element::Sr, "Sr"},
    {Element::Y, "Y"}, {Element::Zr, "Zr"},
    {Element::Nb, "Nb"}, {Element::Mo, "Mo"},
    {Element::Tc, "Tc"}, {Element::Ru, "Ru"},
    {Element::Rh, "Rh"}, {Element::Pd, "Pd"},
    {Element::Ag, "Ag"}, {Element::Cd, "Cd"},
    {Element::In, "In"}, {Element::Sn, "Sn"},
    {Element::Sb, "Sb"}, {Element::Te, "Te"},
    {Element::I, "I"}, {Element::Xe, "Xe"},

};

inline std::optional<Element> symbolToElement(const std::string& symbol) {
    for (const auto& [el, sym] : elementToSymbol) {
        if (sym == symbol) return el;
    }
    return std::nullopt;
}

#endif //ELEMENT_H