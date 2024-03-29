QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RC_ICONS = favicon.ico

include(homepage.pri)
include(searchpage.pri)
include(main.pri)
include(detailpage.pri)
include(setting.pri)
include(library.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MM.qrc

DISTFILES += \
    detailpage.pri \
    homepage.pri \
    library.pri \
    main.pri \
    searchpage.pri \
    setting.pri
