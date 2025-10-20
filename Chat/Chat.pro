QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatdialog.cpp \
    chatuserlist.cpp \
    findfaileddialog.cpp \
    finduserdialog.cpp \
    friendrequestdialog.cpp \
    friendverifydialog.cpp \
    global.cpp \
    httpmgr.cpp \
    listwidget.cpp \
    loadingdialog.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    registerwidget.cpp \
    resetwidget.cpp \
    sigleton.cpp \
    tcpmgr.cpp \
    timerbutton.cpp \
    userinfowidget.cpp

HEADERS += \
    chatdialog.h \
    chatuserlist.h \
    findfaileddialog.h \
    finduserdialog.h \
    friendrequestdialog.h \
    friendverifydialog.h \
    global.h \
    httpmgr.h \
    listwidget.h \
    loadingdialog.h \
    loginwidget.h \
    mainwindow.h \
    registerwidget.h \
    resetwidget.h \
    sigleton.h \
    tcpmgr.h \
    timerbutton.h \
    userinfowidget.h

FORMS += \
    chatdialog.ui \
    findfaileddialog.ui \
    finduserdialog.ui \
    friendrequestdialog.ui \
    friendverifydialog.ui \
    listwidget.ui \
    loadingdialog.ui \
    loginwidget.ui \
    mainwindow.ui \
    registerwidget.ui \
    resetwidget.ui \
    userinfowidget.ui

RC_ICONS = favicon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
