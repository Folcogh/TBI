QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ContextMenuAction.cpp \
    DlgHelp.cpp \
    DlgSettings.cpp \
    DlgTB.cpp \
    LineEditNoFocus.cpp \
    Settings.cpp \
    TechnicalBulletin.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    ContextMenuAction.hpp \
    DlgHelp.hpp \
    DlgSettings.hpp \
    DlgTB.hpp \
    Global.hpp \
    LineEditNoFocus.hpp \
    MainWindow.hpp \
    Settings.hpp \
    TechnicalBulletin.hpp

FORMS += \
    DlgHelp.ui \
    DlgSettings.ui \
    DlgTB.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BUGS.txt \
    TODO.txt
