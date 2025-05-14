#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include <cstring>
#include <vector>

struct student {
    char name[10];
    double grade;
    int num;

    student() : name{}, grade(0), num(0) {}

    student(const student &x) {
        strncpy(name, x.name, sizeof(name));
        name[sizeof(name) - 1] = '\0';
        grade = x.grade;
        num   = x.num;
    }

    student& operator=(const student &x) {
        if (this != &x) {
            strncpy(name, x.name, sizeof(name));
            name[sizeof(name) - 1] = '\0';
            grade = x.grade;
            num   = x.num;
        }
        return *this;
    }

    bool operator<(const student &x) const {
        if (num != x.num)
            return num < x.num;
        return strcmp(name, x.name) < 0;
    }

    bool operator==(const student &x) const {
        return (strcmp(name, x.name) == 0) &&
               (grade == x.grade) &&
               (num   == x.num);
    }

    bool operator!=(const student &x) const {
        return !(*this == x);
    }

    friend QTextStream& operator<<(QTextStream &out, const student &x) {
        out << x.name << " " << x.grade << " " << x.num;
        return out;
    }

    friend QTextStream& operator>>(QTextStream &in, student &x) {
        QString nameStr;
        in >> nameStr >> x.grade >> x.num;
        QByteArray ba = nameStr.toLocal8Bit();
        strncpy(x.name, ba.constData(), sizeof(x.name));
        x.name[sizeof(x.name) - 1] = '\0';
        return in;
    }
};

template <typename T>
class MyUnion {
    T* a;
    int n;
public:
    MyUnion() : a(nullptr), n(0) {}

    MyUnion(int n_) : a(nullptr), n(n_) {
        a = new T[n];
    }

    MyUnion(const MyUnion<T>& x) {
        n = x.n;
        a = new T[n];
        for (int i = 0; i < n; i++)
            a[i] = x.a[i];
    }

    MyUnion(MyUnion<T>&& other) noexcept : a(other.a), n(other.n) {
        other.a = nullptr;
        other.n = 0;
    }

    ~MyUnion() {
        delete[] a;
    }

    MyUnion<T>& operator=(const MyUnion<T>& x) {
        if (this != &x) {
            delete[] a;
            n = x.n;
            a = new T[n];
            for (int i = 0; i < n; i++)
                a[i] = x.a[i];
        }
        return *this;
    }

    MyUnion<T>& operator=(MyUnion<T>&& x) noexcept {
        if (this != &x) {
            delete[] a;
            a = x.a;
            n = x.n;
            x.a = nullptr;
            x.n = 0;
        }
        return *this;
    }

    friend QTextStream& operator>>(QTextStream &in, MyUnion<T>& x) {
        in >> x.n;
        delete[] x.a;
        x.a = new T[x.n];
        for (int i = 0; i < x.n; i++) {
            in >> x.a[i];
        }
        std::sort(x.a, x.a + x.n, [](const T& a, const T& b) {
            return a < b;
        });
        return in;
    }

    friend QTextStream& operator<<(QTextStream &out, const MyUnion<T>& x) {
        out << "moshnost'= " << x.n << "\n";
        for (int i = 0; i < x.n; i++) {
            out << x.a[i];
            if (i + 1 < x.n) out << " ";
        }
        out << "\n";
        return out;
    }

    friend bool operator==(const MyUnion<T>& x, const MyUnion<T>& y) {
        if (x.n != y.n) return false;
        for (int i = 0; i < x.n; i++) {
            if (x.a[i] != y.a[i])
                return false;
        }
        return true;
    }

    friend bool operator!=(const MyUnion<T>& x, const MyUnion<T>& y) {
        return !(x == y);
    }

    friend bool operator<(const MyUnion<T>& x, const MyUnion<T>& y) {
        int min_n = std::min(x.n, y.n);
        for (int i = 0; i < min_n; ++i) {
            if (x.a[i] < y.a[i])
                return true;
            if (y.a[i] < x.a[i])
                return false;
        }
        return x.n < y.n;
    }

    friend MyUnion<T> operator+(const MyUnion<T>& x, const MyUnion<T>& y) {
        std::vector<T> result;
        int i = 0, j = 0;
        while (i < x.n && j < y.n) {
            if (x.a[i] < y.a[j])
                result.push_back(x.a[i++]);
            else if (y.a[j] < x.a[i])
                result.push_back(y.a[j++]);
            else {
                result.push_back(x.a[i]);
                ++i; ++j;
            }
        }
        while (i < x.n)
            result.push_back(x.a[i++]);
        while (j < y.n)
            result.push_back(y.a[j++]);
        MyUnion<T> z(result.size());
        std::copy(result.begin(), result.end(), z.a);
        return z;
    }

    friend MyUnion<T> operator-(const MyUnion<T>& x, const MyUnion<T>& y) {
        std::vector<T> result;
        int i = 0, j = 0;
        while (i < x.n && j < y.n) {
            if (x.a[i] < y.a[j])
                result.push_back(x.a[i++]);
            else if (y.a[j] < x.a[i])
                ++j;
            else {
                ++i; ++j;
            }
        }
        while (i < x.n)
            result.push_back(x.a[i++]);
        MyUnion<T> z(result.size());
        std::copy(result.begin(), result.end(), z.a);
        return z;
    }

    friend MyUnion<T> operator/(const MyUnion<T>& x, const MyUnion<T>& y) {
        std::vector<T> result;
        int i = 0, j = 0;
        while (i < x.n && j < y.n) {
            if (x.a[i] < y.a[j])
                ++i;
            else if (y.a[j] < x.a[i])
                ++j;
            else {
                result.push_back(x.a[i]);
                ++i; ++j;
            }
        }
        MyUnion<T> z(result.size());
        std::copy(result.begin(), result.end(), z.a);
        return z;
    }

    friend MyUnion<T> operator*(const MyUnion<T>& x, const MyUnion<T>& y) {
        return (x + y) - (x / y);
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QFile fin("input.txt");
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open input.txt";
        return 1;
    }
    QTextStream in(&fin);

    QFile fout("output.txt");
    if (!fout.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open output.txt";
        return 1;
    }
    QTextStream out(&fout);

    MyUnion<student> X, Y, Z;
    in >> X >> Y;

    Z = X + Y;
    out << Z;

    Z = X - Y;
    out << Z;

    Z = X / Y;
    out << Z;

    Z = X * Y;
    out << Z;

    return 0;
}
