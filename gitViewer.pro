TEMPLATE = app

QT += qml quick concurrent widgets
CONFIG += c++11

SOURCES += src/main/main.cpp \
    src/main/branchmodel.cpp \
    src/main/commitmodel.cpp \
    src/main/sortfilterproxymodel.cpp \
    src/main/filesystemmodel.cpp \
    src/main/gitadapter.cpp \
    src/main/commitcontroller.cpp \
    src/main/branchcontroller.cpp \
    src/main/gitviewer.cpp

RESOURCES += qml.qrc

#QT_ANGLE_PLATFORM (introduced in Qt 5.4) can be used to control the render backend.
#Possible values are d3d11, d3d9 and warp.

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = . \

QML2_IMPORT_PATH = src/include \

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += src/include \
    3rd-Party/libgit2/include

HEADERS += \
    src/include/branchmodel.h \
    src/include/commitmodel.h \
    src/include/sortfilterproxymodel.h \
    src/include/filesystemmodel.h \
    src/include/gitadapter.h \
    src/include/branchcontroller.h \
    src/include/commitcontroller.h \
    src/include/gitviewer.h



win32: LIBS += -L$$PWD/3rd-Party/libgit2/lib/ -llibgit2.dll
INCLUDEPATH += $$PWD/3rd-Party/libgit2/include
DEPENDPATH += $$PWD/3rd-Party/libgit2/include

