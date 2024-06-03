#ifndef CHESSBUTTON_HPP
#define CHESSBUTTON_HPP

#include <QPushButton>

class Figure;

inline QString CHESS_BUTTON_STYLE_ODD = "border: 5px solid black; background-color: white;";
inline QString CHESS_BUTTON_STYLE_EVEN = "border: 5px solid black; background-color: black;";

class ChessButton : public QPushButton
{
    Q_OBJECT

public:
    ChessButton(QWidget* parent = nullptr) : QPushButton(parent) {}
    ChessButton(QPoint _position, QWidget* parent = nullptr);
    bool hasFigure() { return figure != nullptr; }
    void destroyFigure();
    void attack(ChessButton* other);
    void clearIcon();
    void setChessColor();

    QPoint position;
    Figure* figure = nullptr; // TODO: incapsulate
};

#endif // CHESSBUTTON_HPP
