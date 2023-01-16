#include <Armorial/Utils/ParameterHandler/ParameterHandler.h>

#include <spdlog/spdlog.h>

using namespace Utils;

bool ParameterHandler::loadFile(QString parameterFilePath) {
    // Open file
    _parameterFile.setFileName(parameterFilePath);
    bool openedFile = _parameterFile.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!openedFile) {
        return false;
    }

    // Read content to json document
    _document = QJsonDocument::fromJson(QString(_parameterFile.readAll()).toUtf8());
    _documentMap = _document.object().toVariantMap();

    // Return true (all went properly)
    return true;
}

QString ParameterHandler::fileName() {
    return _parameterFile.fileName();
}

Parameter ParameterHandler::operator[](QString key) const {
    if(!_documentMap.keys().contains(key)) {
        spdlog::warn("[{}] Requesting an invalid key '{}'.", typeid(*this).name(), key.toStdString());
    }

    return _documentMap[key];
}

QList<QString> ParameterHandler::getKeys() const {
    return _documentMap.keys();
}
