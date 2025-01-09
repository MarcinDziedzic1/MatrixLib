#include <iostream>
#include "matrix.hpp"

void runTests() {
    
    using namespace md;

    try {
        std::cout << "Test 1: Creating a matrix and displaying it\n";
        Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        m1.print();
        std::cout << "\n";

        std::cout << "Test 2: Transposing the matrix\n";
        Matrix m2 = m1.transpose();
        m2.print();
        std::cout << "\n";

        std::cout << "Test 3: Adding matrices\n";
        Matrix m3 = m1 + m2;
        m3.print();
        std::cout << "\n";

        std::cout << "Test 4: Subtracting matrices\n";
        Matrix m4 = m1 - m2;
        m4.print();
        std::cout << "\n";

        std::cout << "Test 5: Multiplying matrices\n";
        Matrix m5 = m1 * m2;
        m5.print();
        std::cout << "\n";

        std::cout << "Test 6: Dividing one matrix by another matrix\n";
        Matrix m6({{8, 0}, {0, 8}});
        Matrix m7({{2, 0}, {0, 2}});
        Matrix m8 = m6 / m7;
        m8.print();
        std::cout << "\n";

        std::cout << "Test 7: Determinant of a matrix\n";
        double det = m1.determinant();
        std::cout << "Determinant of m1: " << det << "\n\n";

        std::cout << "Test 8: Inverting a matrix\n";
        SquareMatrix m9(2); // Creating an empty 2x2 matrix
        m9(0, 0) = 4;
        m9(0, 1) = 7;
        m9(1, 0) = 2;
        m9(1, 1) = 6;
        Matrix m10 = m9.inverse();
        m10.print();
        std::cout << "\n";

        std::cout << "Test 9: Adding a row to the matrix\n";
        m1.addRow({10, 11, 12});
        m1.print();
        std::cout << "\n";

        std::cout << "Test 10: Removing a row from the matrix\n";
        m1.removeRow();
        m1.print();
        std::cout << "\n";

        std::cout << "Test 11: Adding a column to the matrix\n";
        m1.addColumn({13, 14, 15});
        m1.print();
        std::cout << "\n";

        std::cout << "Test 12: Removing a column from the matrix\n";
        m1.removeColumn();
        m1.print();
        std::cout << "\n";

        std::cout << "Test 13: Creating a square matrix and assigning a single value to all elements\n";
        SquareMatrix squareMatrix(3); // Creating an empty 3x3 matrix
        squareMatrix = 3.0; // Assigning the value 3.0 to all elements
        squareMatrix.print();
        std::cout << "\n";

        std::cout << "Test 14: Operations on a square matrix\n";
        Matrix squareSum = squareMatrix + m2;
        squareSum.print();
        std::cout << "\n";

        std::cout << "Test 15: Inheritance: Identity matrix\n";
        SquareMatrixIdentity identity(3); // Creating a 3x3 identity matrix
        identity.print();
        std::cout << "\n";

        std::cout << "Test 16: Operations on the identity matrix\n";
        Matrix identityResult = identity + m2;
        identityResult.print();
        std::cout << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "Starting Matrix library tests...\n\n";
    runTests();
    std::cout << "Tests completed.\n";
    return 0;
}
