QT += gui widgets charts multimedia

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11


CONFIG(debug, debug|release) {
    DESTDIR = ../../debug/App/plugin
    OBJECTS_DIR = ../../debug/App/plugin
    MOC_DIR = ../../debug/App/plugin
    RCC_DIR = ../../debug/App/plugin
    UI_DIR = ../../debug/App/plugin
} else {
    DESTDIR = ../../release/App/plugin
    OBJECTS_DIR = ../../release/App/plugin
    MOC_DIR = ../../release/App/plugin
    RCC_DIR = ../../release/App/plugin
    UI_DIR = ../../release/App/plugin
}

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
    ../MyApplication/myplugininterface.cpp \
    audioplugin.cpp \
    audiowidget.cpp

HEADERS += \
    ../MyApplication/myplugininterface.h \
    audioplugin.h \
    audiowidget.h

DISTFILES += FisrtWidnow.json

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
