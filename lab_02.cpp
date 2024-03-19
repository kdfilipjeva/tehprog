#include <iostream>
#include <vector>

class vect {
public:
    int dim;
    double* b;
    static int count;

    vect(int dim, double* b) : dim(dim), b(b) {
        count++;
        std::cout << "������ ������ ����� " << count << std::endl;
    }

    ~vect() {
        std::cout << "������ ������ ����� " << count << std::endl;
        count--;
    }

    vect operator+(const vect& v) {
        std::cout << "����������� �������� �������� ��������" << std::endl;
        double* result = new double[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = this->b[i] + v.b[i];
        }
        vect res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            std::cout << res.b[i] << " ";
        }
        std::cout << std::endl;
        return res;
    }

    vect operator-(const vect& v) {
        std::cout << "����������� �������� ��������� ��������" << std::endl;
        double* result = new double[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = this->b[i] - v.b[i];
        }
        vect res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            std::cout << res.b[i] << " ";
        }
        std::cout << std::endl;
        return res;
    }

    vect operator-() {
        std::cout << "����������� �������� ���������� ������� �� -1" << std::endl;
        double* result = new double[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = -this->b[i];
        }
        vect res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            std::cout << res.b[i] << " ";
        }
        std::cout << std::endl;
        return res;
    }

    vect operator*(double k) {
        std::cout << "����������� �������� ��������� ������� �� �����" << std::endl;
        double* result = new double[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = this->b[i] * k;
        }
        vect res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            std::cout << res.b[i] << " ";
        }
        std::cout << std::endl;
        return res;
    }

    vect& operator=(const vect& v) {
        std::cout << "����������� �������� ������������ ��������" << std::endl;
        if (this != &v) {
            delete[] b;
            dim = v.dim;
            b = new double[dim];
            for (int i = 0; i < dim; i++) {
                b[i] = v.b[i];
            }
        }
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            std::cout << b[i] << " ";
        }
        std::cout << std::endl;
        return *this;
    }

};

int vect::count = 0;

class matr {
public:
    int dim;
    double** a;
    static int count;

    matr(int dim, double** a) : dim(dim), a(a) {
        count++;
        std::cout << "������� ������� ����� " << count << std::endl;
    }

    ~matr() {
        std::cout << "������� ������� ����� " << count << std::endl;
        count--;
    }

    matr operator+(const matr& m) {
        std::cout << "����������� �������� �������� ������" << std::endl;
        double** result = new double*[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = new double[dim];
            for (int j = 0; j < dim; j++) {
                result[i][j] = this->a[i][j] + m.a[i][j];
            }
        }
        matr res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                std::cout << res.a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return res;
    }

    matr operator-(const matr& m) {
        std::cout << "����������� �������� ��������� ������" << std::endl;
        double** result = new double*[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = new double[dim];
            for (int j = 0; j < dim; j++) {
                result[i][j] = this->a[i][j] - m.a[i][j];
            }
        }
        matr res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                std::cout << res.a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return res;
    }

    matr operator-() {
        std::cout << "����������� �������� ���������� ������� �� -1" << std::endl;
        double** result = new double*[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = new double[dim];
            for (int j = 0; j < dim; j++) {
                result[i][j] = -this->a[i][j];
            }
        }
        matr res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                std::cout << res.a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return res;
    }

    matr operator*(double k) {
        std::cout << "����������� �������� ��������� ������� �� �����" << std::endl;
        double** result = new double*[dim];
        for (int i = 0; i < dim; i++) {
            result[i] = new double[dim];
            for (int j = 0; j < dim; j++) {
                result[i][j] = this->a[i][j] * k;
            }
        }
        matr res(dim, result);
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                std::cout << res.a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return res;
    }

    matr& operator=(const matr& m) {
        std::cout << "����������� �������� ������������ ������" << std::endl;
        if (this != &m) {
            for (int i = 0; i < dim; i++) {
                delete[] a[i];
            }
            delete[] a;
            dim = m.dim;
            a = new double*[dim];
            for (int i = 0; i < dim; i++) {
                a[i] = new double[dim];
                for (int j = 0; j < dim; j++) {
                    a[i][j] = m.a[i][j];
                }
            }
        }
        std::cout << "���������: ";
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                std::cout << a[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return *this;
    }

};

int matr::count = 0;

int main() {
	setlocale(LC_ALL, "Russian");
    // �������� ��������
    int dim;
        std::cout << "������� ����������� ��������: ";
    std::cin >> dim;
    double* b1 = new double[dim];
    std::cout << "������� �������� ������� �������: ";
    for (int i = 0; i < dim; i++) {
        std::cin >> b1[i];
    }
    vect v1(dim, b1);
    double* b2 = new double[dim];
    std::cout << "������� �������� ������� �������: ";
    for (int i = 0; i < dim; i++) {
        std::cin >> b2[i];
    }
    vect v2(dim, b2);

    // �������� ��� ���������
    vect v3 = v1 + v2;
    vect v4 = v1 - v2;
    vect v5 = -v1;
    vect v6 = v1 * 2;
    v1 = v2;

    // �������� ������
    std::cout << "������� ����������� ������: ";
    std::cin >> dim;
    double** a1 = new double*[dim];
    std::cout << "������� �������� ������ �������: ";
    for (int i = 0; i < dim; i++) {
        a1[i] = new double[dim];
        for (int j = 0; j < dim; j++) {
            std::cin >> a1[i][j];
        }
    }
    matr m1(dim, a1);
    double** a2 = new double*[dim];
    std::cout << "������� �������� ������ �������: ";
    for (int i = 0; i < dim; i++) {
        a2[i] = new double[dim];
        for (int j = 0; j < dim; j++) {
            std::cin >> a2[i][j];
        }
    }
    matr m2(dim, a2);

    // �������� ��� ���������
    matr m3 = m1 + m2;
    matr m4 = m1 - m2;
    matr m5 = -m1;
    matr m6 = m1 * 2;
    m1 = m2;

    return 0;
}

