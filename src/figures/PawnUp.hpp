#ifndef PAWNUP_HPP
#define PAWNUP_HPP

#include "Figure.hpp"

class PawnUp : public Figure
{
public:
    PawnUp(QGridLayout* _desk, bool isBlack) : Figure(_desk, isBlack) {}
    QVector<QPoint> getPossibleSteps() const override;
};

#endif // PAWNUP_HPP
