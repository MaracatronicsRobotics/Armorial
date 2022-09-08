#ifndef ARMORIAL_MATH_MATRIX_H
#define ARMORIAL_MATH_MATRIX_H

#include <optional>

namespace Math {
    /*!
     * \brief The Math::Matrix class provides a interface for floating-point matrixes,
     * providing custom constructors and methods for matrix computations.
     */
    class Matrix {
    public:
        /*!
         * \brief Matrix constructor that allocates a matrix with given lines and columns.
         * \param lines The given lines.
         * \param columns The given columns.
         */
        Matrix(unsigned lines = 0, unsigned columns = 0);

        /*!
         * \brief Matrix constructor that receives another matrix as argument (makes copy).
         * \param M The given matrix.
         */
        Matrix(const Matrix &M);

        /*!
         * \brief Matrix destructor, which deallocate the matrix.
         */
        ~Matrix();

        /*!
         * \brief Set the matrix size, deallocating and reallocating another one.
         * \param lines The given new number of lines.
         * \param columns The given new number of columns.
         * \note This method erases all the previous data.
         */
        void setSize(unsigned lines, unsigned columns);

        /*!
         * \return The number of lines in this Matrix instance.
         */
        unsigned lines() const { return _lines; }

        /*!
         * \return The number of columns in this Matrix instance.
         */
        unsigned columns() const { return _columns; }

        /*!
         * \param i The given line number.
         * \param j The given column number.
         * \return A float containing the value at the given line and column.
         */
        float get(unsigned i, unsigned j) const;

        /*!
         * \brief Set a given value in the given line and column.
         * \param i The given line.
         * \param j The given column.
         * \param value The given value.
         */
        void set(unsigned i, unsigned j, float value);

        /*!
         * \return The transposed Matrix of this instance.
         */
        Matrix transposed() const;

        /*!
         * \brief Computes the matrix cofactor ignoring 'p' line and 'q' column.
         * \param p The given line number to ignore.
         * \param q The given column number to ignore.
         * \return A Matrix instance containing the cofactor for the given arguments.
         */
        Matrix cofactor(unsigned p, unsigned q) const;

        /*!
         * \return Returns the computed adjoint Matrix from this instance.
         */
        Matrix adjoint();

        /*!
         * \brief Computes the inverse of this Matrix instance.
         * \return A std::optional<Matrix> object which contains a Matrix instance if the
         * determinant value of this Matrix instance differs from zero.
         */
        std::optional<Matrix> inverse();

        /*!
         * \param size The given size.
         * \return A Matrix instance containing a identity matrix for a given size.
         */
        static Matrix identity(unsigned size);

        /*!
         * \brief Computes the determinant of a given matrix.
         * \param m The given matrix.
         * \param columns The given number of columns of the given matrix.
         * \return A integer containing the determinant value for the given matrix.
         */
        static float determinant(Matrix m, unsigned columns);

        /*!
         * \param size The size of the matrix.
         * \param diagValue The given value to set in the diagonal.
         * \return A Matrix instance containing 'diagValue' value on its diagonal.
         */
        static Matrix diag(unsigned size, float diagValue);

        /*!
         * \brief Makes a copy for this Matrix instance given another Matrix instance.
         * \param M The given Matrix instance.
         */
        void copyFrom(const Matrix &M);

        /*!
         * \brief Prints the content of this Matrix instance.
         */
        void print();

        /*!
         * \brief Operators between this Matrix instance and a given Matrix instance.
         * \param M The given Matrix instance.
         */
        void operator=(const Matrix &M);
        Matrix operator+(const Matrix &M) const;
        Matrix operator-(const Matrix &M) const;
        Matrix operator*(const Matrix &M) const;
        void operator+=(const Matrix &M);
        void operator-=(const Matrix &M);

        /*!
         * \brief Operators between this Matrix instance and a given scalar.
         * \param k The given scalar.
         * \return A new Matrix instance containing the result of the operation.
         */
        Matrix operator+(float k) const;
        Matrix operator-(float k) const;
        Matrix operator*(float k) const;
        Matrix operator/(float k) const;

        /*!
         * \brief Operators between this Matrix instance and a given scalar.
         * \param k The given scalar.
         * \note This methods computes and store the result directly on this Matrix instance.
         */
        void operator+=(float k);
        void operator-=(float k);
        void operator*=(float k);
        void operator/=(float k);

    private:
        /*!
         * \brief Allocate into this Matrix instance using the _lines and _columns params.
         */
        void allocate();

        /*!
         * \brief Deallocate this Matrix instance.
         */
        void deallocate();

        /*!
         * \brief Initialize all elements of this Matrix instance with zeros.
         */
        void initialize();

        unsigned _lines;
        unsigned _columns;
        float **_matrix;
    };
}

#endif // ARMORIAL_MATH_MATRIX_H
