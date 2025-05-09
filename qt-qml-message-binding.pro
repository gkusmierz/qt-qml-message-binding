QT += \
    quick \
    quickcontrols2

CONFIG += c++17

RESOURCES += \
    qml/qml.qrc

SOURCES += \
    src/main.cpp \
    src/playlistitem.cpp \
    src/playlistmodel.cpp

HEADERS += \
    src/playlistitem.h \
    src/playlistmodel.h
