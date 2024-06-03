#pragma once

#include "Figure.hpp"

#include "PawnUp.hpp"
#include "PawnDown.hpp"

class Bishop : public FigureImplLong
{
public:
    Bishop(QGridLayout* _desk, bool isBlack) : FigureImplLong(_desk, isBlack, {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}) {}
};

class Knight : public FigureImplShort
{
public:
    Knight(QGridLayout* _desk, bool isBlack) : FigureImplShort(_desk, isBlack, {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}}) {}
};

class King : public FigureImplShort
{
public:
    King(QGridLayout* _desk, bool isBlack) : FigureImplShort(_desk, isBlack, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}) {}
};

class Queen : public FigureImplLong
{
public:
    Queen(QGridLayout* _desk, bool isBlack) : FigureImplLong(_desk, isBlack, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}) {}
};

class Rook : public FigureImplLong
{
public:
    Rook(QGridLayout* _desk, bool isBlack) : FigureImplLong(_desk, isBlack, {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}) {}
};
