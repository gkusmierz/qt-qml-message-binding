QT += \
    quick \
    quickcontrols2 \
    sql

CONFIG += c++17

RESOURCES += \
    qml/qml.qrc

SOURCES += \
    src/main.cpp \
    src/playlistdao.cpp \
    src/playlistitem.cpp \
    src/playlistmodel.cpp

HEADERS += \
    src/playlistdao.h \
    src/playlistitem.h \
    src/playlistmodel.h
