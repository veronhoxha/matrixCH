//Author:    Veron Hoxha
//Title:     Chessboard Matrix

#include <iostream>
#include "matrixCH.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

class Menu {
public:

      Menu (): m(2,2) {}
      void run ();

private:

    matrixCH m;
    matrixCH s;

    void menuWrite();
    void get() const;
    void set();
    void read();
    void write();
    void sum();
    void mul();
};

int main()
{
    Menu m;
    m.run();

    return 0;
}

void Menu::run () {
    int n = 0;
    do {
        menuWrite();
        cout << endl << " Choose one operation from the list above: ";
        cin >> n;
        cout << endl;

        switch (n) {
            case 1:
                get();
                break;
            case 2:
                set();
                break;
            case 3:
                read();
                break;
            case 4:
                write();
                break;
            case 5:
                sum();
                break;
            case 6:
                mul();
                break;
        }
    } while (n != 0);
}

void Menu::menuWrite() {
    cout << endl << endl;
    cout << "/////////////////////////////////////////////////////////" << endl;
    cout << " 0. - Quit" << endl;
    cout << " 1. - Get an element of the Chessboard matrix" << endl;
    cout << " 2. - Overwrite an element of the Chessboard matrix" << endl;
    cout << " 3. - Read matrix" << endl;
    cout << " 4. - Write matrix" << endl;
    cout << " 5. - Add matrices" << endl;
    cout << " 6. - Multiply matrices" << endl;
    cout << "/////////////////////////////////////////////////////////" << endl;
}

void Menu::get() const {
    int i, j;
    cout << "Give the index of the row: ";
    cin >> i;

    cout << "Give the index of the column: ";
    cin >> j;

    try {
        cout << "a[" << i << ", " << j<< "] = " << m(i-1, j-1) << endl;
    }
    catch (matrixCH::exception ex) {
        if (ex == matrixCH::OVERINDEXED) {
            cout << "Overindexing!" << endl;
        } else {
            cout << "Unhandled exception!" << endl;
        }
    }
}

void Menu::set() {
    int i, j, e;
    cout << "Give the index of the row: ";
    cin >> i;

    cout << "Give the index of the column: ";
    cin >> j;

    cout << "Give the value/number: ";
    cin >> e;

    try {
        m(i-1, j-1) = e;
    }
    catch (matrixCH::exception ex) {
        if(ex == matrixCH::OVERINDEXED)
            cout << "Overindexing!" << endl;
        if (ex == matrixCH::NULLPART)
            cout << "These indexes do not point to matrix part!" << endl;
    }
}

void Menu::read() {
    try {
        cout << "Give the size of the matrix: ";
        cin >> m;
    }
    catch (matrixCH::exception ex) {
        if (ex == matrixCH::INVALID) {
            cout << "The size is invalid!" << endl;
        } else {
            cout << "Unhandled exception!" << endl;
        }
    }
}

void Menu::write() {
      cout << m << endl;
}

void Menu::sum() {
    try {
        matrixCH n (2, 2);
        cout << "Give the size of the second matrix: "<< endl;
        cin >> n;

        cout << "Sum of the matrices is: " << endl;
        cout << m + n << endl;
    }
    catch (matrixCH::exception ex) {
        if (ex == matrixCH::INVALID) {
            cout << "The size is invalid!" << endl;
        }
        if (ex == matrixCH::DIFFERENT) {
            cout << "Different sizes of matrices!" << endl;
        }
    }
}

void Menu::mul() {
    try {
        matrixCH n (2,2);
        cout << "Give the size of the second matrix: " << endl;
        cin >> n;

        cout << "Product of the matrices is: "  << endl;
        cout << m * n << endl;
    }
    catch (matrixCH::exception ex) {
        if (ex == matrixCH::INVALID) {
            cout << "The size is invalid!" << endl;
        }
        if (ex == matrixCH::DIFFERENT) {
            cout << "Different sizes of matrices!" << endl;
        }
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("create", "input1.txt")
{
    const string fileName = "input1.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    matrixCH c;
    in >> c; // 4x4
    CHECK(c(0,0) == 3);
    CHECK(c(0,2) == 4);
    CHECK(c(1,1) == 5);
    CHECK(c(1,3) == 6);
    CHECK(c(2,0) == 7);
    CHECK(c(2,2) == 8);
    CHECK(c(3,1) == 9);
    CHECK(c(3,3) == 10);

    matrixCH b;
    in >> b; // 2x4
    CHECK(b(0,0) == 1);
    CHECK(b(0,2) == 2);
    CHECK(b(1,1) == 3);
    CHECK(b(1,3) == 4);

    matrixCH a;
    in >> a; // 2x2
    CHECK(a(0,0)==9);
    CHECK(a(1,1)==2);
}

TEST_CASE("getting and changing an element of the matrix", "input1.txt")
{
    const string fileName = "input1.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    matrixCH a;
    in >> a;
    CHECK(a(0,0) == 3);
    a(0,0) = 0;
    CHECK(a(0,0) == 0);

    matrixCH b;
    in >> b;
    CHECK(b(0,2) == 2);
    b(0,2) = 3;
    CHECK(b(0,2) == 3);

}

TEST_CASE("add", "input.txt")
{
    const string fileName = "input.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    matrixCH a (2,2);
    matrixCH b (2,2);
    matrixCH c (2,2);
    matrixCH d (2,2);
    matrixCH e (2,2);
    matrixCH f (2,2);
    matrixCH g (2,2);
    matrixCH s (2,2);
    matrixCH p (2,2);
    matrixCH k (2,2);
    matrixCH z (2,2);

    in >> a >> b >> z >> g >> e >> k >> s >> p;

    c = a + b; // check every non-zero item
    CHECK(c(0,0) == 9);
    CHECK(c(0,2) == 9);
    CHECK(c(1,1) == 9);
    CHECK(c(1,3) == 9);
    CHECK(c(2,0) == 13);
    CHECK(c(2,2) == 11);
    CHECK(c(3,1) == 9);
    CHECK(c(3,3) == 7);

    c = b + a; // check every non-zero item
    CHECK(c(0,0) == 9);
    CHECK(c(0,2) == 9);
    CHECK(c(1,1) == 9);
    CHECK(c(1,3) == 9);
    CHECK(c(2,0) == 13);
    CHECK(c(2,2) == 11);
    CHECK(c(3,1) == 9);
    CHECK(c(3,3) == 7);

    d = (a + b) + z;
    f = a + (b + z); // check every non-zero item
    CHECK(d(0,0) == f(0,0));
    CHECK(d(0,2) == f(0,2));
    CHECK(d(1,1) == f(1,1));
    CHECK(d(1,3) == f(1,3));
    CHECK(d(2,0) == f(2,0));
    CHECK(d(2,2) == f(2,2));
    CHECK(d(3,1) == f(3,1));
    CHECK(d(3,3) == f(3,3));

    c = a + z; // check every non-zero item
    CHECK(c(0,0) == 5);
    CHECK(c(0,2) == 7);
    CHECK(c(1,1) == 11);
    CHECK(c(1,3) == 14);
    CHECK(c(2,0) == 11);
    CHECK(c(2,2) == 9);
    CHECK(c(3,1) == 9);
    CHECK(c(3,3) == 15);

    c = b + g; // check every non-zero item
    CHECK(c(0,0) == 12);
    CHECK(c(0,2) == 11);
    CHECK(c(1,1) == 10);
    CHECK(c(1,3) == 9);
    CHECK(c(2,0) == 8);
    CHECK(c(2,2) == 7);
    CHECK(c(3,1) == 6);
    CHECK(c(3,3) == 5);

    c = k + e; // check every non-zero item
    CHECK(c(0,0) == 3); // sum by null matrix
    CHECK(c(0,2) == 4);
    CHECK(c(1,1) == 1);
    CHECK(c(1,3) == 2);
    CHECK(c(2,0) == 3);
    CHECK(c(2,2) == 8);
    CHECK(c(3,1) == 7);
    CHECK(c(3,3) == 6);

    try {
        c = a + p;
    }
    catch (matrixCH:: exception ex) {
         CHECK(ex == matrixCH::DIFFERENT);
    }
}

TEST_CASE("multiply", "input.txt")
{
    const string fileName = "input.txt";

    ifstream in(fileName.c_str());
    if(in.fail())
    {
        cout << "File name error!" << endl;
        exit(1);
    }

    matrixCH a (2,2);
    matrixCH b (2,2);
    matrixCH c (2,2);
    matrixCH d (2,2);
    matrixCH e (2,2);
    matrixCH f (2,2);
    matrixCH g (2,2);
    matrixCH s (2,2);
    matrixCH p (2,2);
    matrixCH k (2,2);
    matrixCH z (2,2);

    in >> a >> b >> z >> g >> e >> k >> s >> p;

    c = a * b; // check every non-zero item
    CHECK(c(0,0) == 16);
    CHECK(c(0,2) == 13);
    CHECK(c(1,1) == 26);
    CHECK(c(1,3) == 19);
    CHECK(c(2,0) == 104);
    CHECK(c(2,2) == 87);
    CHECK(c(3,1) == 54);
    CHECK(c(3,3) == 41);

    c = b * a; // check every non-zero item
    CHECK(c(0,0) == 71);
    CHECK(c(0,2) == 72);
    CHECK(c(1,1) == 53);
    CHECK(c(1,3) == 54);
    CHECK(c(2,0) == 31);
    CHECK(c(2,2) == 32);
    CHECK(c(3,1) == 13);
    CHECK(c(3,3) == 14);

    c = a * a; // check every non-zero item
    CHECK(c(0,0) == 19);
    CHECK(c(0,2) == 18);
    CHECK(c(1,1) == 37);
    CHECK(c(1,3) == 36);
    CHECK(c(2,0) == 81);
    CHECK(c(2,2) == 82);
    CHECK(c(3,1) == 63);
    CHECK(c(3,3) == 64);

    c = b * b; // check every non-zero item
    CHECK(c(0,0) == 92);
    CHECK(c(0,2) == 77);
    CHECK(c(1,1) == 46);
    CHECK(c(1,3) == 35);
    CHECK(c(2,0) == 44);
    CHECK(c(2,2) == 37);
    CHECK(c(3,1) == 14);
    CHECK(c(3,3) == 11);

    d = (a * b) * z; // check every non-zero item
    f = a * (b * z); // check every non-zero item
    CHECK(d(0,0) == f(0,0));
    CHECK(d(0,2) == f(0,2));
    CHECK(d(1,1) == f(1,1));
    CHECK(d(1,3) == f(1,3));
    CHECK(d(2,0) == f(2,0));
    CHECK(d(2,2) == f(2,2));
    CHECK(d(3,1) == f(3,1));
    CHECK(d(3,3) == f(3,3));

    d = a * s; // check every non-zero item
    CHECK(d(0,0) == 1); // multiply by identity matrix (s)
    CHECK(d(0,2) == 2);
    CHECK(d(1,1) == 3);
    CHECK(d(1,3) == 4);
    CHECK(d(2,0) == 9);
    CHECK(d(2,2) == 8);
    CHECK(d(3,1) == 7);
    CHECK(d(3,3) == 6);

    d = g * e; // check every non-zero item
    CHECK(d(0,0) == 0); // multiply by null matrix (e)
    CHECK(d(0,2) == 0);
    CHECK(d(1,1) == 0);
    CHECK(d(1,3) == 0);
    CHECK(d(2,0) == 0);
    CHECK(d(2,2) == 0);
    CHECK(d(3,1) == 0);
    CHECK(d(3,3) == 0);

    try {
        c = a * p;
    }
    catch (matrixCH:: exception ex) {
         CHECK(ex == matrixCH::DIFFERENT);
    }
}

TEST_CASE("exceptions", "")
{
    matrixCH a(8,8);

    try
    {
        a(9,5) = 16;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::OVERINDEXED);
    }

    try
    {
        a(-1,4) = 6;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::OVERINDEXED);
    }

    try
    {
        a(9,12) = 62;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::OVERINDEXED);
    }

    matrixCH b(2,4);
    matrixCH c(6,2);
    matrixCH d(10,10);

    try
    {
        c = a + b;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::DIFFERENT);
    }

    try
    {
        c = b + d;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::DIFFERENT);
    }

    try
    {
        c = a * b;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::DIFFERENT);
    }

    try
    {
        c = a * d;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::DIFFERENT);
    }

    try
    {
        a(3,0) = 3;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::NULLPART);
    }

        try
    {
        a(2,3) = 45;
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::NULLPART);
    }

    try
    {
        int l = a(1,2);
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::NULLPART);
    }

    try
    {
        int r = a(0,3);
    }
    catch(matrixCH::exception ex)
    {
        CHECK(ex == matrixCH::NULLPART);
    }
}

#endif

