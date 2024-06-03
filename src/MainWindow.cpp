#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

#include "MainWindow.hpp"
#include "GameWindow.hpp"
#include "SettingsWindow.hpp"
                                     
MainWindow::MainWindow(QWidget *parent) : WindowImpl(parent)
{
    playButton = new QPushButton("Play", this);
    playButton->setFixedSize(300, 100);
    playButton->setStyleSheet(DEFAULT_BUTTON_STYLE);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::openGameWindow);

    settingsButton = new QPushButton("Setting", this);
    settingsButton->setFixedSize(300, 100);
    settingsButton->setStyleSheet(DEFAULT_BUTTON_STYLE);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettingsWindow);

    exitButton = new QPushButton("Exit", this);
    exitButton->setFixedSize(300, 100);
    exitButton->setStyleSheet(DEFAULT_BUTTON_STYLE);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::confirmExit);

    gridLayout->addWidget(playButton, 0, 0, Qt::AlignCenter);
    gridLayout->addWidget(settingsButton, 1, 0, Qt::AlignCenter);
    gridLayout->addWidget(exitButton, 2, 0, Qt::AlignCenter);

    settingsWindow = new SettingsWindow(this);

    setWindowTitle("Главное Меню");
    SetBackground(this, "../Design/BackGround4.jpg");

    delete backButton;
    backButton = nullptr;
}


void MainWindow::openGameWindow()
{
    delete gameWindow;
    gameWindow = new GameWindow(this, settingsWindow->getActiveBlack(), settingsWindow->getActiveWhite());
    this->hide();
    gameWindow->show();
}

void MainWindow::openSettingsWindow()
{
    this->hide();
    settingsWindow->show();
}

void MainWindow::confirmExit()
{
    QMessageBox confirmBox(this);
    confirmBox.setWindowTitle("Exit");
    confirmBox.setText("Are you sure?");
    confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmBox.setDefaultButton(QMessageBox::No);
    confirmBox.setStyleSheet(
        "QMessageBox {"
        "background-color: #BBA0BB;"
        "}"
        "QPushButton {"
        "background-color: pink;"
        "border: 1px solid black;"
        "padding: 5px;"
        "}"
        "QPushButton:hover {"
        "background-color: lightpink;"
        "}"
        "QPushButton:pressed {"
        "background-color: deeppink;"
        "}"
    );

    int ret = confirmBox.exec();
    if (ret == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
