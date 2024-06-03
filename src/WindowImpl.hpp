#ifndef WINDOWIMPL_HPP
#define WINDOWIMPL_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "figures/ChessButton.hpp"

inline QString DEFAULT_BUTTON_STYLE = "QPushButton { border: 3px solid black; background-color: #BBA0BB; color: solid black; font-size: 30px; font-weight: bold; }"
                                      "QPushButton:hover { border: 10px solid #FF00FF; }";

class WindowImpl : public QMainWindow
{
    Q_OBJECT
public:
    explicit WindowImpl(QWidget* parent = nullptr);
    bool SetBackground(QWidget* window, const QString& ImagePath);
    bool setButtonBackgroundImage(QPushButton* button, const QString& imagePath);

private slots:
    void goBack();
    void moveToCenter();

protected:
    QWidget* centralWidget = nullptr;
    QVBoxLayout* layout = nullptr;
    QPushButton* backButton = nullptr;
    QGridLayout* gridLayout = nullptr;
};

#endif // WINDOWIMPL_HPP
