#include <Armorial/Math/Matrix/Matrix.h>

#include <Armorial/Utils/Utils.h>

#include <iostream>
#include <assert.h>

using namespace Math;

Matrix::Matrix(unsigned lines, unsigned columns) {
    _lines = lines;
    _columns = columns;

    // Create matrix
    _matrix = NULL;
    allocate();
    initialize();
}

Matrix::Matrix(const std::vector<std::vector<float>>& matrix) {
    _lines = matrix.size();
    _columns = (_lines == 0) ? 0 : matrix[0].size();

    // Create matrix
    _matrix = NULL;
    allocate();

    assert(matrix.size() == lines());
    for(unsigned i = 0; i < lines(); i++) {
        assert(matrix[i].size() == columns());
    }

    for (unsigned i = 0; i < lines(); i++) {
        for (unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] = matrix[i][j];
        }
    }
}

Matrix::Matrix(const Matrix &M) {
    // Create matrix by copy
    _matrix = NULL;
    copyFrom(M);
}

Matrix::~Matrix() {
    deallocate();
}

void Matrix::allocate() {
    if(lines() != 0 && columns() != 0) {
        _matrix = new float*[lines()];
        for(unsigned i = 0; i < lines(); i++) {
            _matrix[i] = new float[_columns];
        }
    }
}

void Matrix::deallocate() {
    if(_matrix != NULL) {
        for(unsigned i = 0; i < lines(); i++) {
            delete[] _matrix[i];
        }

        delete[] _matrix;
        _matrix = NULL;
    }
}

void Matrix::initialize() {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] = 0;
        }
    }
}

void Matrix::setSize(unsigned lines, unsigned columns) {
    deallocate();
    _lines = lines;
    _columns = columns;
    allocate();
    initialize();
}

float Matrix::get(unsigned i, unsigned j) const {
    assert(i < lines() && j < columns());
    return _matrix[i][j];
}

void Matrix::set(unsigned i, unsigned j, float value) {
    assert(i < lines() && j < columns());
    _matrix[i][j] = value;
}

void Matrix::copyFrom(const Matrix &M) {
    deallocate();
    _lines = M.lines();
    _columns = M.columns();
    allocate();

    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] = M.get(i, j);
        }
    }
}

void Matrix::print() {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix Matrix::identity(unsigned size) {
    return diag(size, 1);
}

Matrix Matrix::diag(unsigned size, float diagValue) {
    Matrix M(size, size);
    for(unsigned i = 0; i < size; i++) {
        M.set(i, i, diagValue);
    }

    return M;
}

Matrix Matrix::transposed() const {
    Matrix temp(columns(), lines());
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            temp.set(j, i, _matrix[i][j]);
        }
    }

    return temp;
}

Matrix Matrix::cofactor(unsigned p, unsigned q) const {
    Matrix cof(lines() - 1, columns() - 1);

    unsigned i = 0, j = 0;

    for(unsigned row = 0; row < lines(); row++) {
        for(unsigned col = 0; col < columns(); col++) {
            if(row != p && col != q) {
                cof.set(i, j++, get(row, col));

                if(j == _columns - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }

    return cof;
}

float Matrix::determinant(Matrix m, unsigned columns) {
    assert(m.columns() == m.lines());

    float D = 0;
    int sign = 1;

    // Base case of recursion
    if(columns == 1) {
        return m.get(0, 0);
    }

    // Iterate over all elements of first row
    for(unsigned f = 0; f < columns; f++) {
        Matrix cof = m.cofactor(0, f);
        D += sign * m.get(0, f) * determinant(cof, columns - 1);
        sign = -sign;
    }

    return D;
}

Matrix Matrix::adjoint() {
    // Base case
    if(lines() == 1 && columns() == 1) {
        Matrix adj(1, 1);
        adj.set(0, 0, 1);
        return adj;
    }

    int sign = 1;
    Matrix adj(lines(), columns());

    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            Matrix cof = cofactor(i, j);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj.set(j, i, (sign) * (determinant(cof, _columns - 1)));
        }
    }

    return adj;
}

std::optional<Matrix> Matrix::inverse() {
    // Get determinant
    Matrix thisMat = (*this);
    float det = Matrix::determinant(thisMat, thisMat.columns());

    // Check not possible case (det == 0)
    if(Utils::Compare::isEqual(det, 0.0f)) {
        return std::nullopt;
    }

    // Get adjoint
    Matrix adj = adjoint();
    Matrix inv(lines(), columns());

    // Find inverse
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            inv.set(i, j, adj.get(i, j) / float(det));
        }
    }

    return inv;
}

void Matrix::operator=(const Matrix &M) {
    deallocate();
    _lines = M._lines;
    _columns = M._columns;
    allocate();
    copyFrom(M);
}

Matrix Matrix::operator+(const Matrix &M) const {
    assert(lines() == M.lines() && columns() == M.columns());
    Matrix temp(lines(), columns());
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            temp.set(i, j, _matrix[i][j] + M.get(i,j));
        }
    }

    return temp;
}

Matrix Matrix::operator-(const Matrix &M) const {
    assert(lines() == M.lines() && columns() == M.columns());
    Matrix temp(lines(), columns());
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            temp.set(i, j, _matrix[i][j] - M.get(i,j));
        }
    }

    return temp;
}

Matrix Matrix::operator+(float k) const {
    Matrix temp(lines(), columns());
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            temp.set(i, j, _matrix[i][j] + k);
        }
    }

    return temp;
}

Matrix Matrix::operator-(float k) const {
    return (*this)+(-k);
}

Matrix Matrix::operator*(const Matrix &M) const {
    assert(columns()==M.lines());
    Matrix temp(lines(), M.columns());

    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < M.columns(); j++) {
            temp.set(i, j, 0);
            for(unsigned k = 0; k < M.lines(); k++) {
                temp.set(i, j, temp.get(i,j) + _matrix[i][k] * M.get(k,j));
            }
        }
    }

    return temp;
}

Matrix Matrix::operator*(float k) const {
    Matrix temp(lines(), columns());
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            temp.set(i, j, _matrix[i][j] * k);
        }
    }

    return temp;
}

Matrix Matrix::operator/(float k) const {
    assert(!Utils::Compare::isEqual(k, 0.0f));

    Matrix temp(lines(), columns());
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            temp.set(i, j, _matrix[i][j] / k);
        }
    }

    return temp;
}

void Matrix::operator+=(const Matrix &M) {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] += M.get(i,j);
        }
    }
}

void Matrix::operator+=(float k) {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] += k;
        }
    }
}

void Matrix::operator-=(const Matrix &M) {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] -= M.get(i,j);
        }
    }
}

bool Matrix::operator==(const Matrix &M) {
    assert(columns() == M.columns());
    assert(lines() == M.lines());

    bool eq = true;
    for(unsigned i = 0; i < lines() && eq; i++) {
        for(unsigned j = 0; j < columns() && eq; j++) {
            eq = Utils::Compare::isEqual(this->get(i, j), M.get(i, j));
        }
    }

    return eq;
}

void Matrix::operator-=(float k) {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] -= k;
        }
    }
}

void Matrix::operator*=(float k) {
    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j = 0; j < columns(); j++) {
            _matrix[i][j] *= k;
        }
    }
}

void Matrix::operator/=(float k) {
    assert(!Utils::Compare::isEqual(k, 0.0f));

    for(unsigned i = 0; i < lines(); i++) {
        for(unsigned j =0; j < columns(); j++) {
            _matrix[i][j] /= k;
        }
    }
}
