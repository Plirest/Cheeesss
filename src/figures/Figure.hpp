#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <QGridLayout>
#include <QVector>

class ChessButton;

class Figure
{
public:
    Figure(QGridLayout* _desk, bool _isBlack) : desk(_desk), m_isBlack(_isBlack) {}
    bool isBlack() const noexcept { return m_isBlack; }
    virtual QVector<QPoint> getPossibleSteps() const = 0;
    virtual ~Figure() = default;

    QPoint position;
protected:
    ChessButton* getButtonFromLayout(int row, int column) const;

    QGridLayout* desk;
    bool const m_isBlack;
};


class FigureImplLong : public Figure
{
public:
    FigureImplLong(QGridLayout* _desk, bool isBlack, const QVector<QPoint>& _directions) : Figure(_desk, isBlack), directions(_directions) {}
    QVector<QPoint> getPossibleSteps() const override;

private:
    const QVector<QPoint> directions;
};

class FigureImplShort : public Figure
{
public:
    FigureImplShort(QGridLayout* _desk, bool isBlack, const QVector<QPoint>& _directions) : Figure(_desk, isBlack), directions(_directions) {}
    QVector<QPoint> getPossibleSteps() const override;

private:
    const QVector<QPoint> directions;
};

#endif // FIGURE_HPP
