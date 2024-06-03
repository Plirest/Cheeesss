#include "Figure.hpp"
#include "ChessButton.hpp"

ChessButton* Figure::getButtonFromLayout(int row, int column) const
{
    if (QLayoutItem* layoutItem = desk->itemAtPosition(row, column))
        if (QWidget* widget = layoutItem->widget())
            return qobject_cast<ChessButton*>(widget);
    return nullptr;
}

QVector<QPoint> FigureImplLong::getPossibleSteps() const
{
    QVector<QPoint> possibleSteps;
    for (const auto& dir : directions)
    {
        int newX = position.x() + dir.x();
        int newY = position.y() + dir.y();
        bool stop = false;
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {
            if (ChessButton* btn = getButtonFromLayout(newX, newY))
            {
                if (stop || (btn->hasFigure() && this->isBlack() == btn->figure->isBlack())) break;
                if (btn->hasFigure() && this->isBlack() != btn->figure->isBlack())
                {
                    stop = true;
                }
                possibleSteps.push_back(QPoint(newX, newY));
                newX += dir.x();
                newY += dir.y();
            }
        }
    }

    return possibleSteps;
}

QVector<QPoint> FigureImplShort::getPossibleSteps() const
{
    QVector<QPoint> possibleSteps;
    for (const auto& dir : directions)
    {
        int newX = position.x() + dir.x();
        int newY = position.y() + dir.y();
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {
            if (ChessButton* btn = getButtonFromLayout(newX, newY))
            {
                if (!(btn->hasFigure() && this->isBlack() == btn->figure->isBlack()))
                {
                    possibleSteps.push_back(QPoint(newX, newY));
                }
            }
        }
    }

    return possibleSteps;
}
