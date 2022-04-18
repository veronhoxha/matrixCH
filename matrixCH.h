//Author:    Veron Hoxha
//Title:     Chessboard Matrix

#ifndef MATRIXCH_H
#define MATRIXCH_H

#pragma once
#include <iostream>
#include <vector>

class matrixCH{

public:
    enum exception {OVERINDEXED, NULLPART, DIFFERENT, INVALID};

    matrixCH(int n, int u);
    matrixCH(const std::vector<int> &_v);
    matrixCH(const matrixCH& m);
    matrixCH(){ v.clear(); }
    //~matrixCH() {}

    int operator() (int i, int j) const;
    int& operator() (int i, int j);
    int getVecSize() const {return v.size();}

    std::vector<int> getMatSize() const {std::vector<int> v = {m, n}; return v;}

    friend matrixCH operator+ (const matrixCH& m, const matrixCH& n);
    friend matrixCH operator* (const matrixCH& m, const matrixCH& n);
    friend std::istream& operator>> (std::istream& s, matrixCH& m);
    friend std::ostream& operator<< (std::ostream& s, const matrixCH& m);

private:

    int m,n;
    std::vector <int> v;
    void reSize(int n, int u);

};
#endif // MATRIXCH_H
