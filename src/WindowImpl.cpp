#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include "SettingsWindow.hpp"
#include "MainWindow.hpp"

#include <QDebug>
#include <QBuffer>

#include "figures/ChessButton.hpp"
#include "WindowImpl.hpp"

WindowImpl::WindowImpl(QWidget* parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    layout = new QVBoxLayout(centralWidget);
    gridLayout = new QGridLayout(this); // ?

    QWidget* gridWidget = new QWidget(this);
    gridWidget->setLayout(gridLayout);
    layout->addWidget(gridWidget, 0, Qt::AlignCenter);
    backButton = new QPushButton("Back", this);
    backButton->setFixedSize(80, 80);
    backButton->setStyleSheet(DEFAULT_BUTTON_STYLE);
    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    buttonLayout->addWidget(backButton, 0, Qt::AlignRight);
    layout->addLayout(buttonLayout);
    connect(backButton, &QPushButton::clicked, this, &WindowImpl::goBack);
    setCentralWidget(centralWidget);
    resize(1024, 720);
    moveToCenter();
}

void WindowImpl::goBack()
{
    this->hide();
    parentWidget()->show();
}

void WindowImpl::moveToCenter()
{
    QDesktopWidget* desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();
    int x = (screenWidth - width()) / 2;
    int y = (screenHeight - height()) / 2;
    move(x, y);
}

bool WindowImpl::SetBackground(QWidget* window, const QString& ImagePath)
{
    QPixmap bkgnd(ImagePath);
    bkgnd = bkgnd.scaled(window->size(), Qt::IgnoreAspectRatio);
    QPalette p = window->palette();
    p.setBrush(QPalette::Window, bkgnd);
    window->setPalette(p);
    return bkgnd.isNull();
}

bool WindowImpl::setButtonBackgroundImage(QPushButton* button, const QString& imagePath)
{
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) { return false; }

    QPixmap scaledPixmap = pixmap.scaled(button->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QIcon icon(scaledPixmap);
    button->setIcon(icon);
    button->setIconSize(button->size() - QSize(20, 20));
    // button->setStyleSheet("border: 3px solid black; background-color: white;");
    return true;
}
