#ifndef UNION_H
#define UNION_H
#include <QCoreApplication>
#include <QTextStream>
#include <QDataStream>
#include <QFile>
#include <algorithm>
#include <cstring>

using namespace std;
using namespace Qt;

struct student
{
    char name[10];
    double grade;
    int num;

    student() : name{}, grade(0), num(0) {}
    student(const student& x)
    {
        strncpy(name, x.name, sizeof(name));
        grade = x.grade;
        num = x.num;
    }
    student& operator=(const student& x)
    {
        if(this != &x)
        {
            strncpy(name, x.name, sizeof(name));
            grade = x.grade;
            num = x.num;
        }
        return *this;
    }
    // bool operator<(const student& x) const
    // {
    //     if (num != x.num)
    //         return num < x.num;
    //     return strcmp(name, x.name) < 0;
    // }
    bool operator==(const student& x) const
    {
        return (strcmp(name, x.name) == 0) &&
               (grade == x.grade) &&
               (num == x.num);
    }
    bool operator!=(const student& x) const
    {
        return !(*this == x);
    }
    friend QTextStream& operator<<(QTextStream& out, const student& x)
    {
        out << x.name << " " << x.grade << " " << x.num << endl;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, student& x)
    {
        in >> x.name >> x.grade >> x.num;

        return in;
    }

    friend QDataStream& operator<<(QDataStream& out, const student& x)
    {
        out.writeRawData(x.name, sizeof(x.name));
        out << x.grade;
        out << x.num;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, student& x)
    {
        in.readRawData(x.name, sizeof(x.name));
        in >> x.grade;
        in >> x.num;
        return in;
    }
};

template <typename T>
class MyUnion
{
    T* a;
    int n;
public:
    friend QTextStream & operator>>(QTextStream& in, MyUnion<T>& x)
    {
        in >> x.n;
        x.a = new T[x.n];
        for(int i = 0; i < x.n; i++)
        {
            in >> x.a[i];
        }
        sort(x.a, x.a + x.n, [](const T& a, const T& b) { return a < b; });
        return in;
    }
    friend QTextStream & operator<<(QTextStream& out, const MyUnion<T>& x)
    {
        out << "moshnost'= " << x.n <<endl;
        for(int i = 0; i < x.n; i++)
        {
            out << x.a[i] << " ";
        }
        out << endl;
        return out;
    }
    friend QDataStream & operator>>(QDataStream& in, MyUnion<T>& x)
    {
        in >> x.n;
        x.a = new T[x.n];
        for(int i = 0; i < x.n; i++)
        {
            in >> x.a[i];
        }
        sort(x.a, x.a + x.n, [](const T& a, const T& b) { return a < b; });
        return in;
    }
    friend QDataStream & operator<<(QDataStream& out, const MyUnion<T>& x)
    {
        out << x.n;
        for(int i = 0; i < x.n; i++)
        {
            out << x.a[i];
        }
        return out;
    }

    MyUnion() : a(nullptr), n(0) {}
    ~MyUnion()
    {
        delete[] a;
    }
    MyUnion(int n_)
    {
        a = new T[n_];
        this->n = n_;
    }
    MyUnion(const MyUnion<T>& x)
    {
        this->n = x.n;
        this->a = new T[x.n];
        for (int i = 0; i < this->n; i++)
            this->a[i] = x.a[i];
    }
    MyUnion(MyUnion<T>&& other) : a(other.a), n(other.n)
    {
        other.a = nullptr;
        other.n = 0;
    }

    MyUnion<T>& operator=(const MyUnion<T>& x)
    {
        if (this != &x)
        {
            delete[] a;

            n = x.n;
            a = new T[n];
            for (int i = 0; i < n; i++)
            {
                a[i] = x.a[i];
            }
        }
        return *this;
    }
    MyUnion<T>& operator=(MyUnion<T>&& x)
    {
        if (this != &x)
        {
            delete[] a;
            a = x.a;
            n = x.n;
            x.a = nullptr;
            x.n = 0;
        }
        return *this;
    }

    friend bool operator!=(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        return !(x == y);
    }
    friend bool operator==(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        if (x.n != y.n) return false;
        for (int i = 0; i < x.n; i++)
            if (x.a[i] != y.a[i])
                return false;
        return true;
    }
    friend bool operator<(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        int count = 0;
        if (x.n == y.n)
        {
            for (int i = 0; i < x.n; i++)
            {
                if (x.a[i] < y.a[i])
                    count--;
                else
                    count++;
            }
        }
        if (count >= 0)
            return false;
        else if (count < 0)
            return true;
    }
    friend MyUnion<T> operator+(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        int i = 0, j = 0, k = 0;
        MyUnion<T> z(x.n + y.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                z.a[k++] = x.a[i++];
            else if(x.a[i] == y.a[j])
            {
                z.a[k++] = x.a[i++];
                j++;
            }
            else
            {
                z.a[k++] = y.a[j++];
            }
        }
        while(i < x.n)
        {
            z.a[k++] = x.a[i++];
        }
        while(j < y.n)
        {
            z.a[k++] = y.a[j++];
        }
        z.n = k;
        return z;
    }
    friend MyUnion<T> operator/(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        int i = 0, j = 0, k = 0;
        MyUnion<T> z(x.n + y.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                i++;
            else if(x.a[i] == y.a[j])
            {
                z.a[k++] = x.a[i++];
                j++;
            }
            else
            {
                j++;
            }
        }
        z.n = k;
        return z;
    }
    friend MyUnion<T> operator*(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        int i = 0, j = 0, k = 0;
        MyUnion<T> z(x.n + y.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                z.a[k++] = x.a[i++];
            else if(x.a[i] == y.a[j])
            {
                i++;
                j++;
            }
            else
            {
                z.a[k++] = y.a[j++];
            }
        }
        while(i < x.n)
        {
            z.a[k++] = x.a[i++];
        }
        while(j < y.n)
        {
            z.a[k++] = y.a[j++];
        }
        z.n = k;
        return z;
    }
    friend MyUnion<T> operator-(const MyUnion<T>& x, const MyUnion<T>& y)
    {
        int i = 0, j = 0, k = 0;
        MyUnion<T> z(x.n);
        while(i < x.n && j < y.n)
        {
            if(x.a[i] < y.a[j])
                z.a[k++] = x.a[i++];
            else if(x.a[i] == y.a[j])
            {
                i++;
                j++;
            }
            else
            {
                j++;
            }
        }
        while(i < x.n)
        {
            z.a[k++] = x.a[i++];
        }
        z.n = k;
        return z;
    }
};

//+ это обьединение, / это пересечение, - это разность и * это xor

#endif // UNION_H
