#include <iostream>
#include <cstdlib>
#include <ctime>

// Класс Matrix для представления матрицы
template <typename T>
class Matrix {
private:
    T** data;          // Двумерный массив для хранения данных матрицы
    unsigned int m;    // Количество строк
    unsigned int n;    // Количество столбцов

public:
    // Конструктор, создающий матрицу заданного размера
    Matrix(unsigned int m, unsigned int n);

    // Деструктор для освобождения памяти
    ~Matrix();

    // Перегрузка оператора [] для доступа к строкам матрицы
    T* operator[](int i);

    // Заполнение матрицы случайными значениями
    void fillRandom();

    // Дружественная функция для перегрузки оператора вывода
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; i++) {
            for (unsigned int j = 0; j < matrix.n; j++) {
                out << matrix.data[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }

    // Вывод размеров матрицы
    void printSize() const;

    // Сравнение двух матриц на равенство
    bool isEqual(const Matrix& other) const;

    // Перегрузка оператора += для сложения матриц
    Matrix& operator+=(const Matrix& matrix);

    // Перегрузка оператора + для сложения матриц
    Matrix operator+(const Matrix& matrix) const;

    // Перегрузка оператора -= для вычитания матриц
    Matrix& operator-=(const Matrix& matrix);

    // Перегрузка оператора - для вычитания матриц
    Matrix operator-(const Matrix& matrix) const;

    // Перегрузка оператора *= для умножения матриц
    Matrix& operator*=(const Matrix& matrix);

    // Перегрузка оператора * для умножения матриц
    Matrix operator*(const Matrix& matrix) const;

    // Перегрузка оператора != для сравнения матриц на неравенство
    bool operator!=(const Matrix& matrix) const;

    // Перегрузка оператора == для сравнения матриц на равенство
    bool operator==(const Matrix& matrix) const;
};

// Класс Vector для представления вектора
template <typename T>
class Vector {
private:
    T* data;          // Массив для хранения данных вектора
    unsigned int size; // Размер вектора

public:
    // Конструктор, создающий вектор заданного размера
    Vector(unsigned int size);

    // Деструктор для освобождения памяти
    ~Vector();

    // Метод для вычисления скалярного произведения с другим вектором
    T dotProduct(const Vector& other) const;

    // Метод для вычисления скалярного произведения с другим вектором
    T scalarProduct(const Vector& other) const;

    // Заполнение вектора случайными значениями
    void fillRandom();

    // Вывод размера вектора
    void printSize() const;

    // Сравнение двух векторов на равенство
    bool isEqual(const Vector& other) const;
};

// Реализация методов класса Matrix

template <typename T>
Matrix<T>::Matrix(unsigned int m, unsigned int n) : m(m), n(n) {
    data = new T * [m];
    for (unsigned int i = 0; i < m; i++) {
        data[i] = new T[n];
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    for (unsigned int i = 0; i < m; i++) {
        delete[] data[i];
    }
    delete[] data;
}

template <typename T>
void Matrix<T>::printSize() const {
    std::cout << "Размер матрицы: " << m << "x" << n << std::endl;
}

template <typename T>
bool Matrix<T>::isEqual(const Matrix& other) const {
    if (m != other.m || n != other.n) {
        return false;
    }
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
T* Matrix<T>::operator[](int i) {
    return data[i];
}

template <typename T>
void Matrix<T>::fillRandom() {
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            data[i][j] = rand() % 10;
        }
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix) {
    if (m != matrix.m || n != matrix.n) {
        std::cerr << "Матрицы должны быть одинакового размера" << std::endl;
        return *this;
    }
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            data[i][j] += matrix.data[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix) const {
    Matrix<T> result(m, n);
    result = *this;
    result += matrix;
    return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix) {
    if (m != matrix.m || n != matrix.n) {
        std::cerr << "Матрицы должны быть одинакового размера" << std::endl;
        return *this;
    }
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            data[i][j] -= matrix.data[i][j];
        }
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix) const {
    Matrix<T> result(m, n);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            result.data[i][j] = data[i][j] - matrix.data[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& matrix) {
    if (n != matrix.m) {
        std::cerr << "Матрицы должны иметь совместимые размеры для умножения" << std::endl;
        return *this;
    }
    Matrix<T> result(m, matrix.n);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < matrix.n; j++) {
            result.data[i][j] = 0;
            for (unsigned int k = 0; k < n; k++) {
                result.data[i][j] += data[i][k] * matrix.data[k][j];
            }
        }
    }
    *this = result;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) const {
    if (n != matrix.m) {
        std::cerr << "Матрицы должны иметь совместимые размеры для умножения" << std::endl;
        return Matrix<T>(0, 0);
    }
    Matrix<T> result(m, matrix.n);
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < matrix.n; j++) {
            result.data[i][j] = 0;
            for (unsigned int k = 0; k < n; k++) {
                result.data[i][j] += data[i][k] * matrix.data[k][j];
            }
        }
    }
    return result;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& matrix) const {
    if (m != matrix.m || n != matrix.n) {
        return true;
    }
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            if (data[i][j] != matrix.data[i][j]) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& matrix) const {
    return !(*this != matrix);
}

// Реализация методов класса Vector

template <typename T>
Vector<T>::Vector(unsigned int size) : size(size) {
    data = new T[size];
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
void Vector<T>::printSize() const {
    std::cout << "Размер вектора: " << size << std::endl;
}

template <typename T>
bool Vector<T>::isEqual(const Vector& other) const {
    if (size != other.size) {
        return false;
    }
    for (unsigned int i = 0; i < size; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void Vector<T>::fillRandom() {
    for (unsigned int i = 0; i < size; i++) {
        data[i] = rand() % 10;
    }
}

template <typename T>
T Vector<T>::dotProduct(const Vector<T>& other) const {
    if (size != other.size) {
        std::cerr << "Векторы должны быть одинакового размера" << std::endl;
        return T();
    }

    T result = T();
    for (unsigned int i = 0; i < size; ++i) {
        result += data[i] * other.data[i];
    }
    return result;
}

template <typename T>
T Vector<T>::scalarProduct(const Vector<T>& other) const {
    if (size != other.size) {
        std::cerr << "Векторы должны быть одинакового размера" << std::endl;
        return T();
    }

    T result = T();
    for (unsigned int i = 0; i < size; ++i) {
        result += data[i] * other.data[i];
    }
    return result;
}

// Главная функция для тестирования классов Matrix и Vector
int main() {
    srand(time(0));  // Инициализация генератора случайных чисел
    setlocale(LC_ALL, "Russian");
    // Тестирование класса Matrix
    Matrix<int> mat1(3, 3);
    mat1.fillRandom();
    mat1.printSize();
    std::cout << mat1;

    Matrix<int> mat2(3, 3);
    mat2.fillRandom();
    mat2.printSize();
    std::cout << mat2;

    std::cout << "Матрицы mat1 и mat2 равны? " << (mat1.isEqual(mat2) ? "Да" : "Нет") << std::endl;

    // Тестирование класса Vector
    Vector<int> vec1(5);
    vec1.fillRandom();
    vec1.printSize();

    Vector<int> vec2(5);
    vec2.fillRandom();
    vec2.printSize();

    std::cout << "Векторы vec1 и vec2 равны? " << (vec1.isEqual(vec2) ? "Да" : "Нет") << std::endl;

    return 0;
}
