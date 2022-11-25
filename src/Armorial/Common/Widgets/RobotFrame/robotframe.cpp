#include <Armorial/Common/Widgets/RobotFrame/robotframe.h>

using namespace Common::Widgets;

RobotFrame::RobotFrame(QWidget *parent) : QFrame(parent) {
    // Setting default info
    setFixedSize(230, 80);

    // Setting pointers
    _robotPattern = nullptr;
    _robotId = nullptr;
    _radioStatus = nullptr;
    _robotBatteryIcon = nullptr;
    _robotBattery = nullptr;
    _roleIcon = nullptr;
    _roleName = nullptr;

    reset();
}

void RobotFrame::reset() {
    setRobotData(Common::Enums::BLUE, 0, DEFAULT_PATTERN_SIZE);
    setRobotRadioStatus(false);
    setRobotBattery(0, width() - (DEFAULT_PATTERN_SIZE + 2 * DEFAULT_MARGIN_BORDER) - DEFAULT_ICON_SIZE - (DEFAULT_MARGIN_BORDER * 2), DEFAULT_ICON_SIZE, DEFAULT_FONT_SIZE);
    setRobotRole("No Role");
}

void RobotFrame::setRobotData(Common::Enums::Color teamColor, quint8 robotId, int patternSize) {
    if (_robotPattern == nullptr) {
        _robotPattern = new QLabel(this);
    }

    QString path = QString(""); // bring back GUI resources images
    QPixmap pixMap(path);

    if (pixMap.isNull()) {
        spdlog::error("{}", fmt::format(fmt::emphasis::bold, "[setRobotData] Failed to load QPixMap at RobotFrame::RobotData"));
        return;
    }

    _robotPattern->setGeometry(DEFAULT_MARGIN_BORDER, (height() - patternSize)/2 + DEFAULT_MARGIN_BORDER, patternSize, patternSize);
    _robotPattern->setPixmap(pixMap);
    _robotPattern->setScaledContents(true);

    if (_robotId == nullptr) {
        _robotId = new QLabel(this);
    }

    _robotId->setText(QString("Robot %1").arg(robotId));
    _robotId->setFont(QFont("Ubuntu", 11));
    _robotId->setAlignment(Qt::AlignLeft | Qt::AlignCenter);

    _robotId->setGeometry(DEFAULT_MARGIN_BORDER, DEFAULT_MARGIN_BORDER, width() - DEFAULT_MARGIN_BORDER, DEFAULT_ICON_SIZE);
}

void RobotFrame::setRobotRadioStatus(bool status) {
    if (_radioStatus == nullptr) {
        _radioStatus = new QLabel(this);
    }

    QString path = QString(""); // bring back GUI resources images
    QPixmap pixMap(path);

    if (pixMap.isNull()) {
        spdlog::error("{}", fmt::format(fmt::emphasis::bold, "[setRobotData] Failed to load QPixMap at RobotFrame::RobotRadioStatus"));
        return;
    }

    _radioStatus->setGeometry(width() - DEFAULT_ICON_SIZE - DEFAULT_MARGIN_BORDER, DEFAULT_MARGIN_BORDER, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE);
    _radioStatus->setPixmap(pixMap);
    _radioStatus->setScaledContents(true);
}

void RobotFrame::setRobotBattery(int value, int batteryWidth, int batteryHeight, int fontSize) {
    if (_robotBattery == nullptr) {
        _robotBattery = new QProgressBar(this);
        _robotBattery->setGeometry(DEFAULT_PATTERN_SIZE + DEFAULT_ICON_SIZE + 2 * DEFAULT_MARGIN_BORDER + DEFAULT_MARGIN_BORDER, (height() - DEFAULT_PATTERN_SIZE)/2 + (DEFAULT_ICON_SIZE * 2) + DEFAULT_MARGIN_BORDER/2 + DEFAULT_MARGIN_BORDER, batteryWidth, batteryHeight);
        _robotBattery->setFont(QFont("Ubuntu", fontSize));
    }

    if (_robotBatteryIcon == nullptr) {
        _robotBatteryIcon = new QLabel(this);
        _robotBatteryIcon->setGeometry(DEFAULT_PATTERN_SIZE + 2 * DEFAULT_MARGIN_BORDER, (height() - DEFAULT_PATTERN_SIZE)/2 + (DEFAULT_ICON_SIZE * 2) + DEFAULT_MARGIN_BORDER/2 + DEFAULT_MARGIN_BORDER, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE);
        _robotBatteryIcon->setPixmap(QPixmap("")); // bring back GUI resources images
        _robotBatteryIcon->setScaledContents(true);
    }

    _robotBattery->setValue(value);
}

void RobotFrame::setRobotRole(QString roleName) {
    if (_roleIcon == nullptr) {
        _roleIcon = new QLabel(this);
    }

    QString path = QString(""); // bring back GUI resources images
    QPixmap pixMap(path);

    if (pixMap.isNull()) {
        path = QString(""); // bring back GUI resources images
        pixMap = QPixmap(path);
    }

    _roleIcon->setGeometry(DEFAULT_PATTERN_SIZE + 2 * DEFAULT_MARGIN_BORDER, (height() - DEFAULT_PATTERN_SIZE)/2 + DEFAULT_ICON_SIZE + DEFAULT_MARGIN_BORDER, DEFAULT_ICON_SIZE, DEFAULT_ICON_SIZE);
    _roleIcon->setPixmap(pixMap);
    _roleIcon->setScaledContents(true);

    if (_roleName == nullptr) {
        _roleName = new QLabel(this);
    }

    _roleName->setText(roleName);
    _roleName->setFont(QFont("Ubuntu", DEFAULT_FONT_SIZE));
    _roleName->setAlignment(Qt::AlignLeft);

    _roleName->setGeometry(DEFAULT_PATTERN_SIZE + DEFAULT_ICON_SIZE + 3 * DEFAULT_MARGIN_BORDER, (height() - DEFAULT_PATTERN_SIZE)/2 + DEFAULT_ICON_SIZE + DEFAULT_MARGIN_BORDER, width()/2, DEFAULT_ICON_SIZE);
}
