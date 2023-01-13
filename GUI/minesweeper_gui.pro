QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameboard.cpp \
    main.cpp \
    mainwindow.cpp \
    square.cpp

HEADERS += \
    gameboard.hh \
    mainwindow.hh \
    square.hh

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../fruit_resource/Resources/License.txt \
    ../fruit_resource/Resources/apple.png \
    ../fruit_resource/Resources/bananas.png \
    ../fruit_resource/Resources/cherries.png \
    ../fruit_resource/Resources/eggplant.png \
    ../fruit_resource/Resources/grapes.png \
    ../fruit_resource/Resources/orange.png \
    ../fruit_resource/Resources/pear.png \
    ../fruit_resource/Resources/strawberry.png \
    ../fruit_resource/Resources/tomato.png \
    Resources/0.png \
    Resources/1.png \
    Resources/2.png \
    Resources/3.png \
    Resources/4.png \
    Resources/5.png \
    Resources/6.png \
    Resources/7.png \
    Resources/8.png \
    Resources/License.txt \
    Resources/apple.png \
    Resources/bananas.png \
    Resources/bomb.png \
    Resources/cherries.png \
    Resources/eggplant.png \
    Resources/explosion.png \
    Resources/flag.png \
    Resources/grapes.png \
    Resources/orange.png \
    Resources/pear.png \
    Resources/strawberry.png \
    Resources/tomato.png
