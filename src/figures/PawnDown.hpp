#ifndef PAWNDOWN_HPP
#define PAWNDOWN_HPP

#include "Figure.hpp"

class PawnDown : public Figure
{
public:
    PawnDown(QGridLayout* _desk, bool isBlack) : Figure(_desk, isBlack) {}
    QVector<QPoint> getPossibleSteps() const override;
};

#endif // PAWNDOWN_HPP
