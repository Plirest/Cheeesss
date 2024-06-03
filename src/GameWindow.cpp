#include <QMessageBox>
#include <QTimer>

#include "GameWindow.hpp"
#include "figures/Figures.hpp"

inline QString CHESS_BUTTON_STYLE_ATTACKED = "border: 5px solid black; background-color: red;";

GameWindow::GameWindow(QWidget* parent, int _ActiveBlack, int _ActiveWhite) : WindowImpl(parent), ActiveBlack(_ActiveBlack), ActiveWhite(_ActiveWhite)
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            ChessButton* button = new ChessButton({row, col}, this);
            button->setFixedSize(60, 60);
            gridLayout->addWidget(button, row, col);
            connect(button, &ChessButton::clicked, this, &GameWindow::handleButtonClick);
        }
    }

    fillFigures();

    setWindowTitle("Game");
    SetBackground(this, "../Design/BackGround.png");
}

ChessButton* GameWindow::getButtonFromLayout(int row, int column)
{
    if (QLayoutItem* layoutItem = gridLayout->itemAtPosition(row, column))
    {
        if (QWidget* widget = layoutItem->widget())
        {
            return qobject_cast<ChessButton*>(widget);
        }
    }

    return nullptr;
}

void GameWindow::promotePawn(ChessButton* button)
{
    button->destroyFigure();

    // TODO: choose between any figure
    if (button->position.x() == 7)
    {
        button->figure = new Queen(gridLayout, /*isBlack*/ false);
        button->figure->position = button->position;
        setButtonBackgroundImage(button, QString("../Design/White/Queen%1.jpg").arg(ActiveWhite));
    }
    else if (button->position.x() == 0)
    {
        button->figure = new Queen(gridLayout, /*isBlack*/ true);
        button->figure->position = button->position;
        setButtonBackgroundImage(button, QString("../Design/Black/Queen%1.jpg").arg(ActiveBlack));
    }
}

bool validateMove(ChessButton const& clickedButton, bool isBlackTurn)
{
    if ((isBlackTurn && clickedButton.figure->isBlack()) ||
        (!isBlackTurn && !clickedButton.figure->isBlack())) return true;
    return false;
}

void GameWindow::showNotification(const QString& message)
{
    QMessageBox* notification = new QMessageBox(this);
    notification->setWindowTitle("Attention");
    notification->setText(message);
    // TODO: remove Ok
    notification->setStandardButtons(QMessageBox::Ok);
    notification->setStyleSheet(
        "QMessageBox { background-color: #BBA0BB; }"
        "QLabel { color: black; }"
    );

    notification->setGeometry(width() / 2.0, height() / 2.0, notification->width(), notification->height());
    notification->show();

    QTimer::singleShot(3000, notification, &QMessageBox::close);
}

void GameWindow::removeInvalidSteps(QVector<QPoint>& possibleSteps, ChessButton* selectedButton, bool isBlackTurn)
{
    possibleSteps.erase(std::remove_if(possibleSteps.begin(), possibleSteps.end(),
        [this, selectedButton, isBlackTurn](const QPoint& step)
        {
            // Simulate turn
            auto* attackedButton = getButtonFromLayout(step.x(), step.y());
            auto* attackedFigure = attackedButton->figure;
            auto attackedIcon = attackedButton->icon();
            attackedButton->figure = nullptr;
            selectedButton->attack(attackedButton);

            // Check if move leads to check
            bool leadsToCheck = checkShax(!isBlackTurn);

            // Revert the simulated turn
            attackedButton->attack(selectedButton);
            attackedButton->figure = attackedFigure;
            attackedButton->setIcon(attackedIcon);

            return leadsToCheck;
        }), possibleSteps.end());
}

bool GameWindow::checkMat(bool isBlackTurn)
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            // if Blacks has shax we must find black figures, that can help king
            if (ChessButton* button = getButtonFromLayout(row, col); button->hasFigure() && button->figure->isBlack() == isBlackTurn)
            {
                QVector<QPoint> possibleSteps = button->figure->getPossibleSteps();
                removeInvalidSteps(possibleSteps, button, isBlackTurn);

                // we have a solve!
                if (!possibleSteps.empty()) return false;
            }
        }
    }

    return true;
}

bool GameWindow::checkShax(bool isBlackTurn)
{
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            // if Blacks turn we find white figures
            if (ChessButton* button = getButtonFromLayout(row, col); button->hasFigure())// && button->figure->isBlack() != isBlackTurn)
            {
                QVector<QPoint> possibleSteps = button->figure->getPossibleSteps();

                if (isBlackTurn && possibleSteps.contains(KingFirst->position)) return true;
                if (!isBlackTurn && possibleSteps.contains(KingSecond->position)) return true;
            }
        }
    }

    return false;
}

void GameWindow::handleButtonClick()
{
    ChessButton* clickedButton = qobject_cast<ChessButton*>(sender());
    if (!clickedButton) return;

    // Go
    if (selectedButton && highlightedButtons.contains(clickedButton))
    {
        bool isKill = clickedButton->hasFigure();
        selectedButton->attack(clickedButton);

        clearHighlightedSteps();

        // check pawn -> queen
        if (clickedButton->position.x() == 0 || clickedButton->position.x() == 7)
        {
            if (clickedButton->figure && (dynamic_cast<PawnUp*>(clickedButton->figure) ||
                                            dynamic_cast<PawnDown*>(clickedButton->figure)))
            {
                promotePawn(clickedButton);
            }
        }

        if (clickedButton->figure->isBlack())
        {
            // TODO: erase + push_back = replace
            figuresBlack.removeOne(selectedButton);
            figuresBlack.push_back(clickedButton);
            if (isKill) figuresWhite.removeOne(clickedButton); // Now it's useless
        }
        else
        {
            // TODO: erase + push_back = replace
            figuresWhite.removeOne(selectedButton);
            figuresWhite.push_back(clickedButton);
            if (isKill) figuresBlack.removeOne(clickedButton);
        }

        if (checkShax(isBlackTurn))
        {
            if (checkMat(!isBlackTurn))
            {
                showNotification("SHAX AND MAT!");
            }
            else
            {
                showNotification("SHAAAAAX!");
            }
        }

        isBlackTurn = !isBlackTurn;
        return;
    }

    // Show possible steps
    if (clickedButton->hasFigure())
    {
        if (validateMove(*clickedButton, isBlackTurn))
        {
            if (selectedButton)
            {
                clearHighlightedSteps();
            }

            selectedButton = clickedButton;
            QVector<QPoint> possibleSteps = selectedButton->figure->getPossibleSteps();
            removeInvalidSteps(possibleSteps, selectedButton, isBlackTurn);
            highlightPossibleSteps(possibleSteps);
        }
    }
}

void GameWindow::highlightPossibleSteps(const QVector<QPoint>& steps)
{
    foreach (const QPoint& step, steps)
    {
        if (ChessButton* button = getButtonFromLayout(step.x(), step.y()))
        {
            button->setStyleSheet(CHESS_BUTTON_STYLE_ATTACKED);
            highlightedButtons.append(button);
        }
    }
}

void GameWindow::clearHighlightedSteps()
{
    foreach (ChessButton *button, highlightedButtons)
    {
        button->setChessColor();
    }
    highlightedButtons.clear();
}

void GameWindow::fillFigures()
{
    // Pawn
    for (int column = 0; column < 8; ++column)
    {
        ChessButton* buttonFirstPlayer = getButtonFromLayout(1, column);
        buttonFirstPlayer->figure = new PawnUp(gridLayout, /*isBlack*/ false);
        buttonFirstPlayer->figure->position = {1, column};
        setButtonBackgroundImage(buttonFirstPlayer, QString("../Design/White/Pawn%1.jpg").arg(ActiveWhite));
        buttonFirstPlayer->setIconSize(buttonFirstPlayer->size() - QSize(10, 10));
        figuresBlack.push_back(buttonFirstPlayer);

        ChessButton* buttonSecondPlayer = getButtonFromLayout(6, column);
        buttonSecondPlayer->figure = new PawnDown(gridLayout, /*isBlack*/ true);
        buttonSecondPlayer->figure->position = {6, column};
        setButtonBackgroundImage(buttonSecondPlayer, QString("../Design/Black/Pawn%1.jpg").arg(ActiveBlack));
        buttonSecondPlayer->setIconSize(buttonSecondPlayer->size() - QSize(10, 10));
        figuresWhite.push_back(buttonSecondPlayer);
    }

    // Rook
    ChessButton* firstRookFirstPlayer = getButtonFromLayout(0, 0);
    firstRookFirstPlayer->figure = new Rook(gridLayout, /*isBlack*/ false);
    firstRookFirstPlayer->figure->position = {0, 0};
    setButtonBackgroundImage(firstRookFirstPlayer, QString("../Design/White/Rook%1.jpg").arg(ActiveWhite));
    firstRookFirstPlayer->setIconSize(firstRookFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(firstRookFirstPlayer);

    ChessButton* secondRookFirstPlayer = getButtonFromLayout(0, 7);
    secondRookFirstPlayer->figure = new Rook(gridLayout, /*isBlack*/ false);
    secondRookFirstPlayer->figure->position = {0, 7};
    setButtonBackgroundImage(secondRookFirstPlayer, QString("../Design/White/Rook%1.jpg").arg(ActiveWhite));
    secondRookFirstPlayer->setIconSize(secondRookFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(secondRookFirstPlayer);

    ChessButton* firstRookSecondPlayer = getButtonFromLayout(7, 0);
    firstRookSecondPlayer->figure = new Rook(gridLayout, /*isBlack*/ true);
    firstRookSecondPlayer->figure->position = {7, 0};
    setButtonBackgroundImage(firstRookSecondPlayer, QString("../Design/Black/Rook%1.jpg").arg(ActiveBlack));
    firstRookSecondPlayer->setIconSize(firstRookSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(firstRookSecondPlayer);

    ChessButton* secondRookSecondPlayer = getButtonFromLayout(7, 7);
    secondRookSecondPlayer->figure = new Rook(gridLayout, /*isBlack*/ true);
    secondRookSecondPlayer->figure->position = {7, 7};
    setButtonBackgroundImage(secondRookSecondPlayer, QString("../Design/Black/Rook%1.jpg").arg(ActiveBlack));
    secondRookSecondPlayer->setIconSize(secondRookSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(secondRookSecondPlayer);

    // Knight
    ChessButton* firstKnightFirstPlayer = getButtonFromLayout(0, 1);
    firstKnightFirstPlayer->figure = new Knight(gridLayout, /*isBlack*/ false);
    firstKnightFirstPlayer->figure->position = {0, 1};
    setButtonBackgroundImage(firstKnightFirstPlayer, QString("../Design/White/KnightR%1.jpg").arg(ActiveWhite));
    firstKnightFirstPlayer->setIconSize(firstKnightFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(firstKnightFirstPlayer);

    ChessButton* secondKnightFirstPlayer = getButtonFromLayout(0, 6);
    secondKnightFirstPlayer->figure = new Knight(gridLayout, /*isBlack*/ false);
    secondKnightFirstPlayer->figure->position = {0, 6};
    setButtonBackgroundImage(secondKnightFirstPlayer, QString("../Design/White/KnightR%1.jpg").arg(ActiveWhite));
    secondKnightFirstPlayer->setIconSize(secondKnightFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(secondKnightFirstPlayer);

    ChessButton* firstKnightSecondPlayer = getButtonFromLayout(7, 1);
    firstKnightSecondPlayer->figure = new Knight(gridLayout, /*isBlack*/ true);
    firstKnightSecondPlayer->figure->position = {7, 1};
    setButtonBackgroundImage(firstKnightSecondPlayer, QString("../Design/Black/KnightL%1.jpg").arg(ActiveBlack));
    firstKnightSecondPlayer->setIconSize(firstKnightSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(firstKnightSecondPlayer);

    ChessButton* secondKnightSecondPlayer = getButtonFromLayout(7, 6);
    secondKnightSecondPlayer->figure = new Knight(gridLayout, /*isBlack*/ true);
    secondKnightSecondPlayer->figure->position = {7, 6};
    setButtonBackgroundImage(secondKnightSecondPlayer, QString("../Design/Black/KnightL%1.jpg").arg(ActiveBlack));
    secondKnightSecondPlayer->setIconSize(secondKnightSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(secondKnightSecondPlayer);

    // Bishop
    ChessButton* firstBishopFirstPlayer = getButtonFromLayout(0, 2);
    firstBishopFirstPlayer->figure = new Bishop(gridLayout, /*isBlack*/ false);
    firstBishopFirstPlayer->figure->position = {0, 2};
    setButtonBackgroundImage(firstBishopFirstPlayer, QString("../Design/White/Bishop%1.jpg").arg(ActiveWhite));
    firstBishopFirstPlayer->setIconSize(firstBishopFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(firstBishopFirstPlayer);

    ChessButton* secondBishopFirstPlayer = getButtonFromLayout(0, 5);
    secondBishopFirstPlayer->figure = new Bishop(gridLayout, /*isBlack*/ false);
    secondBishopFirstPlayer->figure->position = {0, 5};
    setButtonBackgroundImage(secondBishopFirstPlayer, QString("../Design/White/Bishop%1.jpg").arg(ActiveWhite));
    secondBishopFirstPlayer->setIconSize(secondBishopFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(secondBishopFirstPlayer);

    ChessButton* firstBishopSecondPlayer = getButtonFromLayout(7, 2);
    firstBishopSecondPlayer->figure = new Bishop(gridLayout, /*isBlack*/ true);
    firstBishopSecondPlayer->figure->position = {7, 2};
    setButtonBackgroundImage(firstBishopSecondPlayer, QString("../Design/Black/Bishop%1.jpg").arg(ActiveBlack));
    firstBishopSecondPlayer->setIconSize(firstBishopSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(firstBishopSecondPlayer);

    ChessButton* secondBishopSecondPlayer = getButtonFromLayout(7, 5);
    secondBishopSecondPlayer->figure = new Bishop(gridLayout, /*isBlack*/ true);
    secondBishopSecondPlayer->figure->position = {7, 5};
    setButtonBackgroundImage(secondBishopSecondPlayer, QString("../Design/Black/Bishop%1.jpg").arg(ActiveBlack));
    secondBishopSecondPlayer->setIconSize(secondBishopSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(secondBishopSecondPlayer);

    // Queen
    ChessButton* QueenFirstPlayer = getButtonFromLayout(0, 3);
    QueenFirstPlayer->figure = new Queen(gridLayout, /*isBlack*/ false);
    QueenFirstPlayer->figure->position = {0, 3};
    setButtonBackgroundImage(QueenFirstPlayer, QString("../Design/White/Queen%1.jpg").arg(ActiveWhite));
    QueenFirstPlayer->setIconSize(QueenFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(QueenFirstPlayer);

    ChessButton* QueenSecondPlayer = getButtonFromLayout(7, 3);
    QueenSecondPlayer->figure = new Queen(gridLayout, /*isBlack*/ true);
    QueenSecondPlayer->figure->position = {7, 3};
    setButtonBackgroundImage(QueenSecondPlayer, QString("../Design/Black/Queen%1.jpg").arg(ActiveBlack));
    QueenSecondPlayer->setIconSize(QueenSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(QueenSecondPlayer);

    // King
    ChessButton* KingFirstPlayer = getButtonFromLayout(0, 4);
    KingFirstPlayer->figure = new King(gridLayout, /*isBlack*/ false);
    KingFirstPlayer->figure->position = {0, 4};
    setButtonBackgroundImage(KingFirstPlayer, QString("../Design/White/Queen%1.jpg").arg(ActiveWhite));
    KingFirstPlayer->setIconSize(KingFirstPlayer->size() - QSize(10, 10));
    figuresBlack.push_back(KingFirstPlayer);
    KingFirst = KingFirstPlayer->figure;

    ChessButton* KingSecondPlayer = getButtonFromLayout(7, 4);
    KingSecondPlayer->figure = new King(gridLayout, /*isBlack*/ true);
    KingSecondPlayer->figure->position = {7, 4};
    setButtonBackgroundImage(KingSecondPlayer, QString("../Design/Black/Queen%1.jpg").arg(ActiveBlack));
    KingSecondPlayer->setIconSize(KingSecondPlayer->size() - QSize(10, 10));
    figuresWhite.push_back(KingSecondPlayer);
    KingSecond = KingSecondPlayer->figure;
}
