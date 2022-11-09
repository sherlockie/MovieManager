QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = favicon.ico

include(homepage.pri)
include(searchpage.pri)
include(main.pri)

#SOURCES += \
#    graphicspixmap.cpp \
#    graphicsview.cpp \
#    homepage.cpp \
#    infowin.cpp \
#    main.cpp \
#    mainWin.cpp \
#    searchpage.cpp

#HEADERS += \
#    graphicspixmap.h \
#    graphicsview.h \
#    homepage.h \
#    infowin.h \
#    mainWin.h \
#    searchpage.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MM.qrc

DISTFILES += \
    homepage.pri \
    main.pri \
    searchpage.pri
