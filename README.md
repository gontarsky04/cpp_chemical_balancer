# CPP Chemical Balancer
Author: Michał Gontarz

## About the project and its usage
This project was made in order to balance simple and more advanced chemical equations. You are able to solve for stoichiometric coefficients for :

* simple equations (combustion reaction, oxidation reaction, etc.)

    ```
    Input:  CH3OH + O2 -> CO2 + H2O
    Output: 2CH4OH + 3O2 -> 2CO2 + 4H2O
    ```
    ```
    Input:  CO + O2 -> CO2
    Output: 2CO + O2 -> 2CO2 
    ```
    ```
    Input:  Al(OH)3 + HBr -> AlBr3 + H2O
    Output: Al(OH)3 + 3HBr -> AlBr3 + 3H2O 
    ```
* reations of complex compounds
    ```
    Input:  Cu(OH)2 + NaOH -> Na2(Cu(OH)4)
    Output: Cu(OH)2 + 2NaOH -> Na2(Cu(OH)4)
    ```
    ```
    Input:  Cu(OH)2 + NH3 -> (Cu(NH3)4)(OH)2
    Output: Cu(OH)2 + 4NH3 -> (Cu(NH3)4)(OH)2
    ```
* advanced redox reactions
    ```
    Input:  Zn + HNO3 -> Zn(NO3)2 + NO + H2O
    Output: 3Zn + 8HNO3 -> 3Zn(NO3)2 + 2NO + 4H2O
    ```
    ```
    Input:  KMnO4 + KOH + KNO2 -> K2MnO4 + KNO3 + H2O
    Output: 2KMnO4 + 2KOH + KNO2 -> 2K2MnO4 + KNO3 + H2O
    ```
    ```
    Input:  K2Cr2O7 + H2SO4 + KI -> Cr2(SO4)3 + K2SO4 + I2 + H2O
    Output: K2Cr2O7 + 7H2SO4 + 6KI -> Cr2(SO4)3 + 4K2SO4 + 3I2 + 7H2O
    ```

It is a user responsibility to enter a real solvable chemical equation. 

It is also important not to enter any stoichiometric coefficients before molecules. 

The official standard for writing equations uses square brackets [ ] , however the program simplifies notation to use only one type of brackets - round brackets ( ) . 

Moreover the user is allowed to use the arrow symbol ( -> ) only once and only in this direction (from left to right).

## About the code
The main function responsible for solving for the stoichiometric coefficients uses a custom C++ library Eigen (version 3.4.0).

Below are the element and functions from Eigen library, which were used in the code, with an explanation of how they work:

* ```cpp
    Eigen::MatrixXd matrix(nElements, nMolecules);
    /*
    Eigen::MatrixXd is a dynamic (runtime-sized) matrix of doubles.
    The constructor (nElements, nMolecules) creates a matrix of size nElements rows by nMolecules columns.
    */
    ```
* ```cpp
    matrix.setZero();
    /*
    setZero() sets all entries of the matrix to zero.
    */
    ```
* ```cpp
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(matrix, Eigen::ComputeFullV);
    /*
    Eigen::JacobiSVD is a class that computes the singular value decomposition of a matrix — a very general method for decomposing a matrix into simpler components.
    The constructor takes the matrix matrix and the flag Eigen::ComputeFullV, telling it to compute the full V matrix.
    */
    ```
* ```cpp
    Eigen::MatrixXd V = svd.matrixV();
    /*
    svd.matrixV() returns the V matrix from the SVD, which contains the right singular vectors.
    */
    ```
* ```cpp
    Eigen::VectorXd coeffs = V.col(V.cols() - 1);
    /*
    Eigen::VectorXd is a dynamic vector of doubles.
    V.col(V.cols() - 1) extracts the last column of V, which corresponds to the null space of the matrix (the “zero” solution to the linear system).
    This vector represents the relative stoichiometric coefficients of the molecules to balance the chemical equation.
    */
    ```
* ```cpp
    double minCoeff = coeffs.minCoeff();
    /*
    coeffs.minCoeff() finds the smallest coefficient in the vector.
    */
    ```
* ```cpp
    coeffs = coeffs.array() / minCoeff;
    /*
    .array() converts the vector to an array type, which allows element-wise operations.
    */
    ```

