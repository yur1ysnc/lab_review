#include <iostream>
#include <fstream>
template <typename T>
class Matrix {
private:
	int rows, cols;
    T** data;

public:
    Matrix() : rows(0), cols(0), data(nullptr) {}
    Matrix(int rows, int cols, T** data2) : rows(rows), cols(cols) {
		std::cout << "C-tor\n";
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = data2[i][j];
            }
        }
    }
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    ~Matrix() {
		std::cout << "D-tor\n";
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix& operator=(const Matrix& other) {
        if (&other == this) {
            return *this;
        }
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        rows = other.rows;
        cols = other.cols;
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }
    T* operator[](int row) {
        return data[row];
    }
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                T sum = T();
                for (int k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }
	Matrix operator+(const Matrix& other) const {
        if (cols != other.cols || rows != other.cols) {
            throw std::invalid_argument("Matrices have incompatible dimensions");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = data[i][j] + other.Getdata()[i][j];
            }
        }
        return result;
    }
    Matrix operator*(const T& scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    friend Matrix operator*(const T& scalar, const Matrix& matrix) {
        return matrix * scalar;
    }
	int Getrows() const{
		return rows;
	}
	int Getcols() const{
		return cols;
	}
	T** Getdata() const { return data;}

};
template<typename c>
std::ostream& operator<<(std::ostream &os,const Matrix<c>& matr){
		for (int i = 0; i < matr.Getrows();++i){
			for (int j = 0; j < matr.Getcols();++j){
				os << matr.Getdata()[i][j];
			}
			os << "\n";
		}
		return os;
	}
int main () {
	int **data;
	int c = 0;
	data = new int*[2];
	for (int i = 0; i < 2; ++i){
		data[i] = new int[2];
		for (int j = 0; j < 2; ++j){
			data[i][j] = c;
			c++;
		}
	}
	Matrix<int> matr1(2,2,data);
	std::cout << matr1;
	for (int i=0;i<2;i++){
		delete[] data[i];
    }
    delete[] data;
    return 0;
}