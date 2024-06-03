#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include "WindowImpl.hpp"
#include "figures/ChessButton.hpp"

class GameWindow : public WindowImpl
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = nullptr, int ActiveBlack = 1, int ActiveWhite = 1);

private slots:
    void showNotification(const QString& message);
    void handleButtonClick();

private:
    bool checkMat(bool isBlackTurn);
    bool checkShax(bool isBlackTurn);
    void promotePawn(ChessButton* button);
    void fillFigures();
    void highlightPossibleSteps(const QVector<QPoint>& steps);
    void clearHighlightedSteps();
    void removeInvalidSteps(QVector<QPoint>& possibleSteps, ChessButton* selectedButton, bool isBlackTurn);
    ChessButton* getButtonFromLayout(int row, int column);

    ChessButton* selectedButton = nullptr;
    QVector<ChessButton*> highlightedButtons;
    QVector<ChessButton*> figuresWhite;
    QVector<ChessButton*> figuresBlack;
    bool isBlackTurn = false;

    int ActiveBlack;
    int ActiveWhite;

    Figure* KingFirst = nullptr;
    Figure* KingSecond = nullptr;
};

#endif // GAMEWINDOW_HPP
