#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QHBoxLayout>

#include <QDebug>
#include <QBuffer>

#include "SettingsWindow.hpp"

QString const HIGHTLIGHTED_SETTINGS_BUTTON_STYLE = "border: 10px solid green; background-color: white;";
QString const DEFAULT_SETTINGS_BUTTON_STYLE = "border: 4px solid black; background-color: white;";

SettingsWindow::SettingsWindow(QWidget *parent) : WindowImpl(parent)
{
    // Blacks
    for (int col = 0; col < 3; ++col)
    {
        QPushButton* button = new QPushButton(this);
        button->setFixedSize(300, 300);
        gridLayout->addWidget(button, 0, col);
        setButtonBackgroundImage(button, QString("../Design/Black/BlackFigures%1.jpg").arg(col + 1));
        Blacks.push_back(button);
    }

    // Whites
    for (int col = 0; col < 3; ++col)
    {
        QPushButton* button = new QPushButton(this);
        button->setFixedSize(300, 300);
        gridLayout->addWidget(button, 1, col);
        setButtonBackgroundImage(button, QString("../Design/White/WhiteFigures%1.jpg").arg(col + 1));
        Whites.push_back(button);
    }

    selectedButtonFirstPlayer = Blacks[0];
    selectedButtonFirstPlayer->setStyleSheet(HIGHTLIGHTED_SETTINGS_BUTTON_STYLE);
    selectedButtonSecondPlayer = Whites[0];
    selectedButtonSecondPlayer->setStyleSheet(HIGHTLIGHTED_SETTINGS_BUTTON_STYLE);

    for (int i = 0; i < 3; ++i)
    {
        QObject::connect(Blacks[i], &QPushButton::clicked, [this, i]() {
            this->selectedButtonFirstPlayer->setStyleSheet(DEFAULT_SETTINGS_BUTTON_STYLE);
            this->selectedButtonFirstPlayer = this->Blacks[i];
            this->ActiveBlack = i + 1;
            this->selectedButtonFirstPlayer->setStyleSheet(HIGHTLIGHTED_SETTINGS_BUTTON_STYLE);
        });

        QObject::connect(Whites[i], &QPushButton::clicked, [this, i]() {
            this->selectedButtonSecondPlayer->setStyleSheet(DEFAULT_SETTINGS_BUTTON_STYLE);
            this->selectedButtonSecondPlayer = this->Whites[i];
            this->ActiveWhite = i + 1;
            this->selectedButtonSecondPlayer->setStyleSheet(HIGHTLIGHTED_SETTINGS_BUTTON_STYLE);
        });
    }

    backButton->setText("Ok");
    setWindowTitle("Settings");
    SetBackground(this, "../Design/BackGround3.jpg");
}
