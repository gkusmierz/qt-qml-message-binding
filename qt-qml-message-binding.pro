QT += \
    quick \
    quickcontrols2 \
    sql

CONFIG += c++17

RESOURCES += \
    qml/qml.qrc

SOURCES += \
    src/libraryitem.cpp \
    src/librarymodel.cpp \
    src/main.cpp \
    src/playlistitem.cpp \
    src/playlistmodel.cpp

HEADERS += \
    src/libraryitem.h \
    src/librarymodel.h \
    src/playlistitem.h \
    src/playlistmodel.h
