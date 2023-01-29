TEMPLATE = app
DESTDIR  = ../bin
TARGET   = Armorial-Test
VERSION  = 1.0.0

# Temporary dirs
OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
UI_DIR = tmp/moc
RCC_DIR = tmp/rc

CONFIG += c++17 console
CONFIG -= app_bundle
QT += core network

DEFINES += QT_DEPRECATED_WARNINGS
LIBS += -lfmt -lArmorial -lgtest -lgmock

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += APP_NAME=\\\"$$TARGET\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += PROJECT_PATH=\\\"$${PWD}\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/Geometry/Angle/Angle.cpp \
    src/Geometry/Arc/Arc.cpp \
    src/Geometry/Circle/Circle.cpp \
    src/Geometry/Line/Line.cpp \
    src/Geometry/LineSegment/LineSegment.cpp \
    src/Geometry/Polygon/Polygon.cpp \
    src/Geometry/Rectangle/Rectangle.cpp \
    src/Geometry/Triangle/Triangle.cpp \
    src/Geometry/Vector2D/Vector2D.cpp \
    src/Math/Matrix/Matrix.cpp \
    src/Common/Enums/Enums.cpp \
    src/Common/Types/Field/Field.cpp \
    src/Common/Types/Object/Object.cpp \
    src/Threaded/Entity/Entity.cpp \
    src/Threaded/EntityCommons.cpp \
    src/Threaded/EntityManager/EntityManager.cpp \
    src/Utils/ParameterHandler/ParameterHandler.cpp \
    src/Utils/Timer/Timer.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/Threaded/EntityCommons.h

DISTFILES += \
    src/Utils/ParameterHandler/rsc/constants.json
