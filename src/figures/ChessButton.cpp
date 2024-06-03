#include "ChessButton.hpp"
#include "Figure.hpp"

ChessButton::ChessButton(QPoint _position, QWidget* parent) : QPushButton(parent), position(_position)
{
    setChessColor();
}

void ChessButton::destroyFigure()
{
    delete this->figure;
    this->figure = nullptr;
}

void ChessButton::attack(ChessButton* other)
{
    if (!other) return;

    other->destroyFigure();
    other->setIcon(icon());
    other->setIconSize(other->size() - QSize(10, 10));
    other->figure = this->figure;
    other->figure->position = other->position;
    this->figure = nullptr;
    this->clearIcon();
}

void ChessButton::clearIcon()
{
    setIcon(QIcon());
}

void ChessButton::setChessColor()
{
    if ((this->position.x() + this->position.y()) % 2 == 0)
    {
        this->setStyleSheet(CHESS_BUTTON_STYLE_EVEN);
    }
    else
    {
        this->setStyleSheet(CHESS_BUTTON_STYLE_ODD);
    }
}
