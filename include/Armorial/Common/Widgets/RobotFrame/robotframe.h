#ifndef ROBOTFRAME_H
#define ROBOTFRAME_H

#include <QFrame>
#include <QLabel>
#include <QProgressBar>

#include <spdlog/spdlog.h>
#include <fmt/color.h>

#include <Armorial/Common/Enums/Color/Color.h>

#define DEFAULT_MARGIN_BORDER 5
#define DEFAULT_ICON_SIZE 16
#define DEFAULT_PATTERN_SIZE 64
#define DEFAULT_FONT_SIZE 9

namespace Common {
namespace Widgets {

    /*!
     * \brief The Common::Widgets::RobotFrame class provides a QOpenGLWidget override that allows to display a field
     * and a lot of drawing methods using OpenGL.
     */
    class RobotFrame : public QFrame
    {
    public:
        /*!
         * \brief The default constructor for RobotFrame.
         */
        RobotFrame(QWidget *parent = nullptr);

        /*!
         * \brief Resets the RobotFrame to its default info.
         */
        void reset();

        /*!
         * \brief Sets the RobotFrame's data.
         * \param Color of the team.
         * \param Robot ID.
         * \param (Explain better pattern Size)
         */
        void setRobotData(Common::Enums::Color teamColor, quint8 robotId, int patternSize = DEFAULT_PATTERN_SIZE);
        void setRobotRadioStatus(bool status);
        void setRobotBattery(int value, int batteryWidth, int batteryHeight = DEFAULT_ICON_SIZE, int fontSize = DEFAULT_FONT_SIZE);
        void setRobotRole(QString roleName);

    private:
        QLabel *_robotPattern;
        QLabel *_robotId;

        QLabel *_radioStatus;

        QLabel *_robotBatteryIcon;
        QProgressBar *_robotBattery;

        QLabel *_roleIcon;
        QLabel *_roleName;
    };
}
}


#endif // ARMORIAL_COMMON_WIDGETS_ROBOTFRAME_H
