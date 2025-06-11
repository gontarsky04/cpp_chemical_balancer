cmake_minimum_required(VERSION 3.30)
project(ChemicalBalancer)

set(CMAKE_CXX_STANDARD 23)
include_directories(libs/eigen-3.4.0)

add_executable(ChemicalBalancer
        main/main.cpp
        backend/ChemicalBalancer.cpp
        backend/Molecule.cpp
        backend/ChemicalEquation.cpp
        backend/FormulaParser.cpp
        backend/EquationParser.cpp
)
