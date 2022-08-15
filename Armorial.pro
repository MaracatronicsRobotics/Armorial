# Application info
TEMPLATE = lib
DESTDIR  = lib
TARGET   = Armorial
VERSION  = 1.0.0
CONFIG  += c++17

# Qt info
QT += network opengl widgets

# Libs
LIBS += -lQt5Core -lprotobuf -lgrpc -lgrpc++ -lfmt -lGLU

# Temporary dirs
OBJECTS_DIR = tmp/obj

# Compilation flags
QMAKE_CXXFLAGS_RELEASE = -O2 -Wfloat-equal -Wshadow -Woverloaded-virtual

# -Wold-style-cast
count(arch, 1) {
    QMAKE_CXXFLAGS_RELEASE += -march=$$arch
}

# Project files
INCLUDEPATH *= include

HEADERS     += \
    include/Armorial/Base/Base.h \
    include/Armorial/Base/Client/Client.h \
    include/Armorial/Base/Service/Service.h \
    include/Armorial/Common/Enums/Color/Color.h \
    include/Armorial/Common/Enums/Enums.h \
    include/Armorial/Common/Packet/Packet.h \
    include/Armorial/Common/Widgets/Widgets.h \
    include/Armorial/Common/Widgets/FieldView/FieldView.h \
    include/Armorial/Common/Widgets/GLText/GLText.h \
    include/Armorial/Geometry/Angle/Angle.h \
    include/Armorial/Geometry/Arc/Arc.h \
    include/Armorial/Geometry/Circle/Circle.h \
    include/Armorial/Geometry/Line/Line.h \
    include/Armorial/Geometry/LineSegment/LineSegment.h \
    include/Armorial/Geometry/Polygon/Polygon.h \
    include/Armorial/Geometry/Rectangle/Rectangle.h \
    include/Armorial/Geometry/Triangle/Triangle.h \
    include/Armorial/Geometry/Vector2D/Vector2D.h \
    include/Armorial/Libs/magic_enum/include/magic_enum.hpp \
    include/Armorial/Libs/nameof/include/nameof.hpp \
    include/Armorial/Math/Math.h \
    include/Armorial/Math/Matrix/Matrix.h \
    include/Armorial/Threaded/Entity/Entity.h \
    include/Armorial/Geometry/Geometry.h \
    include/Armorial/Threaded/EntityManager/EntityManager.h \
    include/Armorial/Threaded/Threaded.h \
    include/Armorial/Common/Types/Field/Field.h \
    include/Armorial/Common/Types/Object/Object.h \
    include/Armorial/Common/Types/Traits/Traits.h \
    include/Armorial/Common/Types/Types.h \
    include/Armorial/Utils/ExitHandler/ExitHandler.h \
    include/Armorial/Utils/ParameterHandler/Parameter.h \
    include/Armorial/Utils/ParameterHandler/ParameterHandler.h \
    include/Armorial/Utils/Timer/Timer.h \
    include/Armorial/Utils/Utils.h

SOURCES     += \
    src/Armorial/Base/Client/Client.cpp \
    src/Armorial/Base/Service/Service.cpp \
    src/Armorial/Common/Enums/Color/Color.cpp \
    src/Armorial/Common/Packet/Packet.cpp \
    src/Armorial/Common/Widgets/FieldView/FieldView.cpp \
    src/Armorial/Common/Widgets/GLText/GLText.cpp \
    src/Armorial/Geometry/Angle/Angle.cpp \
    src/Armorial/Geometry/Arc/Arc.cpp \
    src/Armorial/Geometry/Circle/Circle.cpp \
    src/Armorial/Geometry/Line/Line.cpp \
    src/Armorial/Geometry/LineSegment/LineSegment.cpp \
    src/Armorial/Geometry/Polygon/Polygon.cpp \
    src/Armorial/Geometry/Rectangle/Rectangle.cpp \
    src/Armorial/Geometry/Triangle/Triangle.cpp \
    src/Armorial/Geometry/Vector2D/Vector2D.cpp \
    src/Armorial/Math/Matrix/Matrix.cpp \
    src/Armorial/Threaded/Entity/Entity.cpp \
    src/Armorial/Geometry/Geometry.cpp \
    src/Armorial/Threaded/EntityManager/EntityManager.cpp \
    src/Armorial/Common/Types/Field/Field.cpp \
    src/Armorial/Common/Types/Object/Object.cpp \
    src/Armorial/Common/Types/Traits/Traits.cpp \
    src/Armorial/Utils/ExitHandler/ExitHandler.cpp \
    src/Armorial/Utils/ParameterHandler/ParameterHandler.cpp \
    src/Armorial/Utils/Timer/Timer.cpp


# Installation path
count(install_path, 0) {
    target.path = /usr/lib64/
}

count(install_path, 1) {
    target.path = $$install_path
}

INSTALLS += target

# Debug messages configuration
count(debug_msg, 0):        DEFINES += GSDEBUGMSG
contains(debug_msg, true):  DEFINES += GSDEBUGMSG
contains(debug_msg, false): DEFINES -= GSDEBUGMSG

# Thread-safe configuration
DEFINES -= GSTHREADSAFE
