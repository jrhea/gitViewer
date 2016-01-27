TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += src/main/main.cpp \
    src/main/branchmodel.cpp \
    src/main/gitcontroller.cpp \
    src/main/commitmodel.cpp \
    src/main/sortfilterproxymodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = . \

QML2_IMPORT_PATH = src/include \

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += src/include \
    3rd-Party/libGitWrap

HEADERS += \
    src/include/branchmodel.h \
    src/include/gitcontroller.h \
    src/include/commitmodel.h \
    src/include/sortfilterproxymodel.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rd-Party/libGitWrap/build/libGitWrap/release/ -lGitWrap.0.0.20
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rd-Party/libGitWrap/build/libGitWrap/debug/ -lGitWrap.0.0.20
else:unix: LIBS += -L$$PWD/3rd-Party/libGitWrap/build/libGitWrap/ -lGitWrap.0.0.20

INCLUDEPATH += $$PWD/3rd-Party/libGitWrap/build/libGitWrap
DEPENDPATH += $$PWD/3rd-Party/libGitWrap/build/libGitWrap
