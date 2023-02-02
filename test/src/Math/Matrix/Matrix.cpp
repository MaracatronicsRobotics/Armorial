#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <Armorial/Math/Matrix/Matrix.h>

TEST(Math_Matrix_Test, When_Creating_A_Matrix_Should_Allocate_And_Initialize_Elements) {
    const int lines = 100;
    const int columns = 100;

    // Create Matrix object and use the generated lines/columns to allocate it
    Math::Matrix matrix = Math::Matrix(lines, columns);

    // Check if lines and columns are set properly
    EXPECT_EQ(matrix.lines(), lines);
    EXPECT_EQ(matrix.columns(), columns);

    // Check if the values are default initialized by zero
    for(int i = 0; i < lines; i++) {
        for(int j = 0; j < columns; j++) {
            EXPECT_FLOAT_EQ(matrix.get(i, j), 0);
        }
    }
}

TEST(Math_Matrix_Test, When_Creating_A_Matrix_With_Given_Vector_Should_Allocate_Elements) {
    // Given vector
    std::vector<std::vector<float>> givenVector = {{1, 5}, {7, 3}, {8, 2}};

    // Creating matrix
    Math::Matrix matrix(givenVector);

    // Check if values are all set
    for (unsigned int i = 0; i < givenVector.size(); i++) {
        for (unsigned int j = 0; j < givenVector[0].size(); j++) {
            EXPECT_FLOAT_EQ(matrix.get(i, j), givenVector[i][j]);
        }
    }
}

TEST(Math_Matrix_Test, When_Creating_A_Matrix_With_Given_Invalid_Vector_Should_Fail) {
    // Given vector (note that the second line has invalid shape)
    std::vector<std::vector<float>> givenVector = {{1, 5}, {7, 3, 5}, {8, 2}};

    // Creating matrix (should fail)
    EXPECT_DEATH(Math::Matrix matrix(givenVector), "Assertion*.*failed");
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Set_Values_Should_Work) {
    const int lines = 1000;
    const int columns = 1000;
    const int tests = 7;
    const float test_value = 199.92;

    // Create Matrix object and use the generated lines/columns to allocate it
    Math::Matrix matrix = Math::Matrix(lines, columns);

    // Set values in some positions
    const int lineIndexes[tests] = {2, 5, 8, 41, 102, 515, 999};
    const int columnIndexes[tests] = {5, 71, 98, 192, 495, 960, 999};

    // Set values
    for(int i = 0; i < tests; i++) {
        matrix.set(lineIndexes[i], columnIndexes[i], test_value);
    }

    // Check if the set values are set properly
    for(int i = 0; i < tests; i++) {
        EXPECT_FLOAT_EQ(matrix.get(lineIndexes[i], columnIndexes[i]), test_value);
    }
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Set_Values_OutRange_Should_Fail) {
    // Given matrix
    Math::Matrix matrix({{1, 5},
                         {7, 3},
                         {8, 2}});

    // Assert that gets should fail out of the specified shape
    EXPECT_DEATH(matrix.set(2, 3, 0), "Assertion*.*failed");
    EXPECT_DEATH(matrix.set(3, 3, 0), "Assertion*.*failed");
    EXPECT_DEATH(matrix.set(12, 12, 0), "Assertion*.*failed");
    EXPECT_DEATH(matrix.set(99, 99, 0), "Assertion*.*failed");
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Get_Values_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{1, 5},
                         {7, 3},
                         {8, 2}});

    // Assert that gets should work in the specified shape
    EXPECT_FLOAT_EQ(matrix.get(0, 0), 1);
    EXPECT_FLOAT_EQ(matrix.get(0, 1), 5);
    EXPECT_FLOAT_EQ(matrix.get(1, 0), 7);
    EXPECT_FLOAT_EQ(matrix.get(1, 1), 3);
    EXPECT_FLOAT_EQ(matrix.get(2, 0), 8);
    EXPECT_FLOAT_EQ(matrix.get(2, 1), 2);
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Get_Values_OutRange_Should_Fail) {
    // Given matrix
    Math::Matrix matrix({{1, 5},
                         {7, 3},
                         {8, 2}});

    // Assert that gets should fail out of the specified shape
    EXPECT_DEATH(matrix.get(2, 3), "Assertion*.*failed");
    EXPECT_DEATH(matrix.get(3, 3), "Assertion*.*failed");
    EXPECT_DEATH(matrix.get(12, 12), "Assertion*.*failed");
    EXPECT_DEATH(matrix.get(99, 99), "Assertion*.*failed");
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Get_Its_Transpose_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{1, 5},
                         {7, 3},
                         {8, 2}});

    // Generate its transpose
    Math::Matrix matrixTranspose = matrix.transposed();

    // Lines from A should be equal to the Columns from B and vice-versa
    EXPECT_EQ(matrix.lines(), matrixTranspose.columns());
    EXPECT_EQ(matrix.columns(), matrixTranspose.lines());

    // The transpose of the transposed matrix should be equal as the original matrix
    EXPECT_EQ(matrixTranspose.transposed() == matrix, true);

    // The transposed mult of the matrixes should be equal as the inverse multiplication of the transpose of each one
    EXPECT_EQ((matrix * matrixTranspose).transposed() == (matrixTranspose.transposed() * matrix.transposed()), true);
}

TEST(Math_Matrix_Test, When_Given_A_Square_Matrix_Get_Its_Determinant_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{2, 3, 4, 5, 6, 7},
                         {1, 2, -1, 4, 5, 9},
                         {1, 23, 4, 5, 9, 1},
                         {3, 1, 23, 45, 6, 0},
                         {9, 81, 2, 3, 4, 5},
                         {8, 7, 6, 5, 1, 4}});

    EXPECT_FLOAT_EQ(Math::Matrix::determinant(matrix, matrix.columns()), 3681068);
}

TEST(Math_Matrix_Test, When_Given_A_NonSquare_Matrix_Get_Its_Determinant_Should_Fail) {
    // Given matrix
    Math::Matrix matrix({{2, 3, 4, 5, 6},
                         {1, 2, -1, 4, 5},
                         {1, 23, 4, 5, 9},
                         {3, 1, 23, 45, 6},
                         {9, 81, 2, 3, 4},
                         {8, 7, 6, 5, 1}});

    EXPECT_DEATH(Math::Matrix::determinant(matrix, matrix.columns()), "Assertion*.*failed");
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_SetSize_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{2, 3, 4, 5, 6},
                         {1, 2, -1, 4, 5},
                         {1, 23, 4, 5, 9},
                         {3, 1, 23, 45, 6},
                         {9, 81, 2, 3, 4},
                         {8, 7, 6, 5, 1}});

    // Reshape
    const int newQtLines = 6;
    const int newQtColumns = 6;
    matrix.setSize(newQtLines, newQtColumns);

    // Assert new shape
    EXPECT_EQ(matrix.lines(), newQtLines);
    EXPECT_EQ(matrix.columns(), newQtColumns);

    // Assert that values are reseted
    for(int i = 0; i < newQtLines; i++) {
        for(int j = 0; j < newQtColumns; j++) {
            EXPECT_FLOAT_EQ(matrix.get(i, j), 0);
        }
    }
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Get_Its_Cofactor_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{2, 3, 4},
                         {1, 2, -1},
                         {1, 23, 4}});

    // Computed cofactors for p = 0 and q = 0
    Math::Matrix cofactor_0_0({{2, -1},
                               {23, 4}});

    // Check if matches
    EXPECT_EQ(matrix.cofactor(0, 0) == cofactor_0_0, true);

    // Computed cofactors for p = 1 and q = 1
    Math::Matrix cofactor_1_1({{2, 4},
                               {1, 4}});

    // Check if matches
    EXPECT_EQ(matrix.cofactor(1, 1) == cofactor_1_1, true);

    // Computed cofactors for p = 2 and q = 2
    Math::Matrix cofactor_2_2({{2, 3},
                               {1, 2}});

    // Check if matches
    EXPECT_EQ(matrix.cofactor(2, 2) == cofactor_2_2, true);
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Get_Its_Adjoint_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    // Computed adjoint
    Math::Matrix adjointMatrix({{2, -1, -2},
                                {2, -2, -2},
                                {6, -5, -8}});

    // Check if matches
    EXPECT_EQ(matrix.adjoint() == adjointMatrix, true);
}

TEST(Math_Matrix_Test, When_Creating_Diag_Matrix_Should_Work) {
    // Creating diag matrix
    const int size = 3;
    const float diagValue = 1.24;
    Math::Matrix diag = Math::Matrix::diag(size, diagValue);

    // Check if values are set
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(i != j) EXPECT_FLOAT_EQ(diag.get(i, j), 0);
            else       EXPECT_FLOAT_EQ(diag.get(i, j), diagValue);
        }
    }
}

TEST(Math_Matrix_Test, When_Creating_Identity_Matrix_Should_Work) {
    // Creating diag matrix
    const int size = 3;
    Math::Matrix diag = Math::Matrix::identity(size);

    // Check if values are set
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(i != j) EXPECT_FLOAT_EQ(diag.get(i, j), 0);
            else       EXPECT_FLOAT_EQ(diag.get(i, j), 1);
        }
    }
}

TEST(Math_Matrix_Test, When_Given_A_NonSingular_Matrix_Get_Its_Inverse_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    // Inverse of given matrix
    Math::Matrix inverseMatrix({{1, -0.5, -1},
                                {1, -1, -1},
                                {3, -2.5, -4}});

    // Assert the property AA^(-1) = I
    Math::Matrix identity = Math::Matrix::diag(3, 1);
    EXPECT_EQ(matrix * inverseMatrix == identity, true);

    // Computes inverse
    std::optional<Math::Matrix> inverse = matrix.inverse();

    // Expect that computed inverse has values
    EXPECT_EQ(inverse.has_value(), true);

    // Expect computed equal to answer
    EXPECT_EQ(inverse.value() == inverseMatrix, true);
}

TEST(Math_Matrix_Test, When_Given_A_Singular_Matrix_Get_Its_Inverse_Should_Fail) {
    // Given matrix
    Math::Matrix matrix({{3, 2},
                         {6, 4}});

    // Expect no results
    EXPECT_EQ(matrix.inverse().has_value(), false);
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_CopyFrom_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{3, 2},
                         {6, 4}});

    // Given an empty matrix
    Math::Matrix copy;
    EXPECT_EQ(copy.lines(), 0);
    EXPECT_EQ(copy.columns(), 0);

    // Copy from the given matrix
    copy.copyFrom(matrix);
    EXPECT_EQ(matrix == copy, true);
}

TEST(Math_Matrix_Test, When_Given_Two_Same_Shape_Matrixes_Operators_Should_Work) {
    // Given matrixes
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    Math::Matrix matrix_2({{1, -0.5, -1},
                           {1, -1, -1},
                           {3, -2.5, -4}});

    // Compute operators
    {
        SCOPED_TRACE("Sum of matrixes");

        Math::Matrix sum_ans({{4, 0.5, -2},
                              {3, -3, -1},
                              {4, -0.5, -5}});
        EXPECT_EQ((matrix + matrix_2) == sum_ans, true);
    }

    {
        SCOPED_TRACE("Sub of matrixes");

        Math::Matrix sub_ans({{2, 1.5, 0},
                              {1, -1, 1},
                              {-2, 4.5, 3}});
        EXPECT_EQ((matrix - matrix_2) == sub_ans, true);
    }

    {
        SCOPED_TRACE("Mult of matrixes");

        Math::Matrix mult_ans = Math::Matrix::identity(3);
        EXPECT_EQ((matrix * matrix_2) == mult_ans, true);
    }
}

TEST(Math_Matrix_Test, When_Given_Two_Different_Shape_Matrixes_Sum_And_Sub_Operators_Should_Fail) {
    // Given matrixes
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    Math::Matrix matrix_2({{1, -0.5},
                           {1, -1},
                           {3, -2.5}});

    // Compute operators
    {
        SCOPED_TRACE("Sum of matrixes");

        EXPECT_DEATH((matrix + matrix_2), "Assertion*.*failed");
    }

    {
        SCOPED_TRACE("Sub of matrixes");

        EXPECT_DEATH((matrix - matrix_2), "Assertion*.*failed");
    }
}

TEST(Math_Matrix_Test, When_Given_Two_Matrixes_Mult_Operator_Should_Work) {
    // For matrix multiplication, A.columns() == B.lines()
    // Given matrixes
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    Math::Matrix matrix_2({{1, -0.5},
                           {1, -1},
                           {3, -2.5}});

    // matrix * matrix_2 result
    Math::Matrix m1_m2_mult({{1, 0},
                             {0, 1},
                             {0, 0}});
    EXPECT_EQ((matrix * matrix_2) == m1_m2_mult, true);

    // matrix_2 * matrix should not work (matrix_2.columns() == 2 and matrix.lines() == 3)
    EXPECT_DEATH((matrix_2 * matrix), "Assertion*.*failed");
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Scalar_Operators_Should_Work) {
    // Given matrix
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    // Compute operators using scalars
    {
        SCOPED_TRACE("Matrix sum with scalar");

        Math::Matrix sum_ans({{4, 2, 0},
                              {3, -1, 1},
                              {2, 3, 0}});
        EXPECT_EQ((matrix + 1) == sum_ans, true);
    }

    {
        SCOPED_TRACE("Matrix sub with scalar");

        Math::Matrix sub_ans({{2, 0, -2},
                              {1, -3, -1},
                              {0, 1, -2}});
        EXPECT_EQ((matrix - 1) == sub_ans, true);
    }

    {
        SCOPED_TRACE("Matrix mult with scalar");

        Math::Matrix mult_ans({{6, 2, -2},
                              {4, -4, 0},
                              {2, 4, -2}});
        EXPECT_EQ((matrix * 2) == mult_ans, true);
    }

    {
        SCOPED_TRACE("Matrix div with scalar");

        Math::Matrix div_ans({{1.5, 0.5, -0.5},
                              {1, -1, 0},
                              {0.5, 1, -0.5}});
        EXPECT_EQ((matrix / 2) == div_ans, true);
    }
}

TEST(Math_Matrix_Test, When_Given_A_Matrix_Scalar_Division_With_Zero_Should_Fail) {
    // Given matrix
    Math::Matrix matrix({{3, 1, -1},
                         {2, -2, 0},
                         {1, 2, -1}});

    EXPECT_DEATH(matrix / 0.0f, "Assertion*.*failed");
}
