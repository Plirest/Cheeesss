TEMPLATE = app
TARGET = Chess

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

QT += widgets

SOURCES +=  main.cpp \
            MainWindow.cpp \
            SettingsWindow.cpp \
            GameWindow.cpp \
            WindowImpl.cpp \
            figures/Figure.cpp \
            figures/ChessButton.cpp \
            figures/PawnUp.cpp \
            figures/PawnDown.cpp \

HEADERS +=  MainWindow.hpp \
            SettingsWindow.hpp \
            GameWindow.hpp \
            WindowImpl.hpp \
            figures/Figure.hpp \
            figures/Figures.hpp \
            figures/ChessButton.hpp \
            figures/PawnUp.hpp \
            figures/PawnDown.hpp \