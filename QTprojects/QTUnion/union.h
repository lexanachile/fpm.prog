#ifndef UNION_H
#define UNION_H
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include <cstring>
#include <vector>

class QStudent {
    QString name;
    QString grade;
    QString num;
public:
    QStudent(){
        name = grade = num = "";
    }

    QStudent(const QString &name1, const QString &grade1, const QString &num1){
        name = name1;
        grade = grade1;
        num = num1;
    }

    QStudent(const QStudent &x) {
        name = x.name;
        grade = x.grade;
        num = x.num;
    }

    QStudent& operator=(const QStudent &x) {
        if (this != &x) {
            name = x.name;
            grade = x.grade;
            num = x.num;
        }
        return *this;
    }

    bool operator<(const QStudent &x) const {
        if (num != x.num)
            return num.toInt() < x.num.toInt();
        if(name != x.name)
            return name < x.name;
        return grade < x.grade;
    }

    bool operator==(const QStudent &x) const {
        return (name == x.name) &&
               (grade == x.grade) &&
               (num   == x.num);
    }

    bool operator!=(const QStudent &x) const {
        return !(*this == x);
    }

    friend QTextStream& operator<<(QTextStream &out, const QStudent &x) {
        out << x.name << "\n";
        out << x.grade << "\n";
        out << x.num;
        return out;
    }

    friend QTextStream& operator>>(QTextStream &in, QStudent &x) {
        x.name = in.readLine();
        x.grade = in.readLine();
        x.num = in.readLine();
        return in;
    }

    QString getName(){
        return name;
    }
    QString getGrade(){
        return grade;
    }
    QString getMark(){
        return num;
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

    MyUnion(const T& x){
        n = 1;
        a = new T[1];
        a[0] = x;
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
        QString countStr = in.readLine();
        x.n = countStr.toInt();
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
        out << x.n << "\n";
        for (int i = 0; i < x.n; i++) {
            out << x.a[i];
            if (i < x.n - 1) {
                out << "\n";
            }
        }
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

    MyUnion<T>& operator+=(const MyUnion<T>& x) {
        if (this != &x) *this = *this + x;
        return *this;
    }
    int getLenth() const {
        return n;
    }
    T* getArray() const {
        return a;
    }
};
#endif // UNION_H
