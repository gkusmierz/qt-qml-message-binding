QT += \
    quick \
    quickcontrols2

CONFIG += c++17

RESOURCES += \
    qml/qml.qrc

SOURCES += \
    src/main.cpp \
    src/message.cpp \
    src/messagemodel.cpp

HEADERS += \
    src/message.h \
    src/messagemodel.h
