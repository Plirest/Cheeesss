#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "GameWindow.hpp"
#include "SettingsWindow.hpp"
#include "WindowImpl.hpp"

class MainWindow : public WindowImpl
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void openGameWindow();
    void openSettingsWindow();
    void confirmExit();

private:
    QPushButton* playButton = nullptr;
    QPushButton* settingsButton = nullptr;
    QPushButton* exitButton = nullptr;
    GameWindow* gameWindow = nullptr;
    SettingsWindow* settingsWindow = nullptr;
};

#endif // MAINWINDOW_HPP
