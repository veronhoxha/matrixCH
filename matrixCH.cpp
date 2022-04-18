//Author:    Veron Hoxha
//Title:     Chessboard Matrix

#include "matrixCH.h"
#include <iostream>
#include <iomanip>

using namespace std;

matrixCH::matrixCH (int n, int u) {

    if ( n <= 0 || n % 2 == 1 || u <= 0 || u % 2 == 1)
    {
         throw INVALID;
    }

    this->m = n;
    this->n = u;

    v.clear();
    v.resize ((n*u)/2, 0);

}

matrixCH::matrixCH(const vector<int> &_v)
{
    v = _v;
}

void matrixCH::reSize(int n, int u)
{
    if ( n <= 0 || n % 2 == 1 || u <= 0 || u % 2 == 1)
    {
         throw INVALID;
    }

    this->m = n;
    this->n = u;

    v.clear();
    v.resize ((n*u)/2, 0);

}

ostream& operator<< (std::ostream& s, const matrixCH& m) {
    std::vector<int> size = m.getMatSize();
    cout << "The size of the matrix is: " << size[0] << "x" << size[1] << endl;

    for (int i = 0; i < size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {
           s << setw(5) << m(i,j);
        }
        s << endl;
    }
    return s;
}


istream& operator>> (istream& s, matrixCH& m) {
    int r, c;
    s >> r;
    s >> c;
    m.reSize(r, c);

    cout << "Please write the numbers in row-major order: " << endl;
    int j;
    for (int i = 0; i < r; i++) {
        if (i % 2 == 0) {
            j = 0;
        } else {
            j = 1;
        }
        for (; j < c; j += 2) {
            s >> m(i, j);
        }
    }
    return s;
}

matrixCH operator+ (const matrixCH& m, const matrixCH& n) {

    std::vector<int> sizeM = m.getMatSize();
    std::vector<int> sizeN = n.getMatSize();
    int p = m.getVecSize();

    if(sizeM[0] != sizeN[0] || sizeM[1] != sizeN[1]) throw matrixCH::DIFFERENT;

    matrixCH c(sizeM[0], sizeM[1]);

    for (int i = 0; i < p; i++) {
        c.v[i] = m.v[i] + n.v[i];
    }
    return c;
}

matrixCH operator* (const matrixCH& m, const matrixCH& n) {

    std::vector<int> sizeM = m.getMatSize();
    std::vector<int> sizeN = n.getMatSize();

    if(sizeM[1] != sizeN[0]) throw matrixCH::DIFFERENT;

    matrixCH c(sizeM[0], sizeN[1]);

    for (int i = 0; i < sizeM[0]; i++) {
        for (int j = 0; j < sizeN[1];j++) {
                if (m(i, j) != 0) {
                    for (int k = 0; k < sizeN[0]; k++) {
                        c(i, j) += (m(i, k) * n(k, j));
                    }
                }
          }
    }
    return c;
}

int matrixCH::operator () (int i, int j) const  {
    std::vector<int> size = getMatSize();
    if ((i >= size[0] || i < 0 ) || (j >= size[1] || j < 0 )) throw OVERINDEXED;

    if (i % 2 == 0 && j % 2 == 0) {
        return v[(size[1] / 2) * i + j/2];
    } else if (i % 2 == 1 && j % 2 == 1) {
        return v[(size[1] / 2) * i + (j - 1)/2];
    }
    return 0;
}

int& matrixCH::operator () (int i, int j) {
    std::vector<int> size = getMatSize();
    if ((i >= size[0] || i < 0 ) || (j >= size[1] || j < 0 )) throw OVERINDEXED;

    if (i % 2 == 0 && j % 2 == 0) {
        return v[(size[1] / 2) * i + j/2];
    } else if (i % 2 == 1 && j % 2 == 1) {
        return v[(size[1] / 2) * i + (j - 1)/2];
    }
throw NULLPART;
}


