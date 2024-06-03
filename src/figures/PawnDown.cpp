#include "PawnDown.hpp"
#include "ChessButton.hpp"

QVector<QPoint> PawnDown::getPossibleSteps() const
{
    QVector<QPoint> possibleSteps;
    int x = position.x();
    int y = position.y();

    if (x <= 0) return possibleSteps;

    if (ChessButton* btn = getButtonFromLayout(x - 1, y); !btn->hasFigure())
    {
        possibleSteps.push_back(QPoint(x - 1, y));

        if (x == 6 && !getButtonFromLayout(x - 2, y)->hasFigure())
        {
            possibleSteps.push_back(QPoint(x - 2, y));
        }
    }

    if (y < 7)
    {
        ChessButton* leftDiagonal = getButtonFromLayout(x - 1, y + 1);
        if (leftDiagonal->hasFigure() && this->isBlack() != leftDiagonal->figure->isBlack())
        {
            possibleSteps.push_back(QPoint(x - 1, y + 1));
        }
    }

    if (y > 0)
    {
        ChessButton* rightDiagonal = getButtonFromLayout(x - 1, y - 1);
        if (rightDiagonal->hasFigure() && this->isBlack() != rightDiagonal->figure->isBlack())
        {
            possibleSteps.push_back(QPoint(x - 1, y - 1));
        }
    }

    return possibleSteps;
}
