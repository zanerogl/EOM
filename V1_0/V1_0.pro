QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    angle_detector.cpp \
    color_detector.cpp \
    contourwithdata.cpp \
    img_template_widget.cpp \
    ip_camera_setting.cpp \
    main.cpp \
    mainwindow.cpp \
    mylabel.cpp

HEADERS += \
    angle_detector.h \
    color_detector.h \
    contourwithdata.h \
    img_template_widget.h \
    ip_camera_setting.h \
    mainwindow.h \
    mylabel.h

FORMS += \
    img_template_widget.ui \
    ip_camera_setting.ui \
    mainwindow.ui

INCLUDEPATH += D:\ProgramFiles\Qt\Qt5.14.2\Tools\build\install\include
LIBS += D:\ProgramFiles\Qt\Qt5.14.2\Tools\build\lib\libopencv_*.a


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
