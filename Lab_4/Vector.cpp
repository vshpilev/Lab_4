template <typename T>
class Vector : public Matrix<T> {
public:
    Vector(int size, T value) : Matrix<T>(1, size, value) {}

    T dotProduct(const Vector<T>& other) const {
        if (this->getCols() != other.getRows()) {
            std::cerr << "Ќевозможно выполнить векторное произведение - неправильные размеры" << std::endl;
            return T();
        }

        T result = T();
        for (int i = 0; i < this->getCols(); ++i) {
            result += (*this)(0, i) * other(0, i);
        }

        return result;
    }

    T scalarProduct(const Vector<T>& other) const {
        if (this->getCols() != other.getCols()) {
            std::cerr << "Ќевозможно выполнить скал€рное произведение - неправильные размеры" << std::endl;
            return T();
        }

        T result = T();
        for (int i = 0; i < this->getCols(); ++i) {
            result += (*this)(0, i) * other(0, i);
        }

        return result;
    }
};

int main() {
    Vector<int> intVector(3, 1);
    intVector(0, 0) = 1;
    intVector(0, 1) = 2;
    intVector(0, 2) = 3;

    Vector<int> intVector2(3, 2);
    intVector2(0, 0) = 4;
    intVector2(0, 1) = 5;
    intVector2(0, 2) = 6;

    std::cout << "¬екторное произведение: " << intVector.dotProduct(intVector2) << std::endl;
    std::cout << "—кал€рное произведение: " << intVector.scalarProduct(intVector2) << std::endl;

    return 0;
}