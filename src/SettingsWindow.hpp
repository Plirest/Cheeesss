#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include "WindowImpl.hpp"

class SettingsWindow : public WindowImpl
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);

    int getActiveBlack() const noexcept { return ActiveBlack; }
    int getActiveWhite() const noexcept { return ActiveWhite; }

private:
    int ActiveBlack = 1;
    int ActiveWhite = 1;
    QPushButton* selectedButtonFirstPlayer = nullptr;
    QPushButton* selectedButtonSecondPlayer = nullptr;

    QVector<QPushButton*> Blacks;
    QVector<QPushButton*> Whites;
};

#endif // SETTINGSWINDOW_HPP
