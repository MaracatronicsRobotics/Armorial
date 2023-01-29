#include <QString>

#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

#include <Armorial/Utils/ParameterHandler/Parameter.h>
#include <Armorial/Utils/ParameterHandler/ParameterHandler.h>

QString FILEPATH = QString(PROJECT_PATH) + "/src/Utils/ParameterHandler/rsc/constants.json";

TEST(Utils_Parameter_Test, When_Creating_Parameter_Should_Store_Correct_Value){
    QString str = "Parameter Test";
    QVariant var = QVariant(str);
    Utils::Parameter parameter = Utils::Parameter(var);

    EXPECT_EQ(var.toString(), parameter.toString());
}

TEST(Utils_ParameterHandler_Test, When_Load_File_Should_Be_Successfull) {
    Utils::ParameterHandler parameterHandler;
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[ParameterHandler] Utils::ParameterHandler::loadFile(QString parameterFilePath) did not return true."));
    EXPECT_TRUE(parameterHandler.loadFile(FILEPATH));
}

TEST(Utils_ParameterHandler_Test, When_Load_File_All_Parameters_Should_Be_Loaded){
    Utils::ParameterHandler parameterHandler;
    QFile file;

    file.setFileName(FILEPATH);
    bool openedFile = file.open(QIODevice::ReadOnly | QIODevice::Text);
    bool handlerResult = parameterHandler.loadFile(FILEPATH);

    if ((!openedFile) || (!handlerResult)) {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[ParameterHandler] Utils::ParameterHandler::loadFile(QString parameterFilePath) file could not be loaded."));
        EXPECT_EQ(openedFile, handlerResult);
    } else {
        QJsonDocument doc;
        QVariantMap docMap;
        doc = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
        docMap = doc.object().toVariantMap();
        QList<QString> parameters;

        for (auto k : docMap.keys()) {
            parameters = parameterHandler.getKeys();
            SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[ParameterHandler] Utils::ParameterHandler::loadFile(QString parameterFilePath) key %1 not loaded.").arg(k).toStdString()));
            EXPECT_TRUE(parameters.contains(k));
            if (!parameters.contains(k)) {
                break;
            }
        }
    }
}

TEST(Utils_ParameterHandler_Test, When_Accessing_Parameter_Should_Return_Correct_Value) {
    Utils::ParameterHandler parameterHandler;
    QFile file;

    file.setFileName(FILEPATH);
    bool openedFile = file.open(QIODevice::ReadOnly | QIODevice::Text);
    bool handlerResult = parameterHandler.loadFile(FILEPATH);

    if ((!openedFile) || (!handlerResult)) {
        SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[ParameterHandler] Utils::ParameterHandler::loadFile(QString parameterFilePath) file could not be loaded."));
        EXPECT_EQ(openedFile, handlerResult);
    } else {
        QJsonDocument doc;
        QVariantMap docMap;
        doc = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
        docMap = doc.object().toVariantMap();

        for (auto k : parameterHandler.getKeys()) {
            SCOPED_TRACE(fmt::format(fmt::emphasis::bold, QString("\n[ParameterHandler] Utils::ParameterHandler::operator[](QString key) key %1 returned %2 instead of %3").arg(k).arg(docMap[k].toString()).arg(parameterHandler[k].toString()).toStdString()));
            EXPECT_EQ(docMap[k], parameterHandler[k]);
            if (!(docMap[k] == parameterHandler[k])) {
                break;
            }
        }
    }
}

TEST(Utils_ParameterHandler_Test, When_Accessing_File_Name_Should_Return_Correct_Name) {
    Utils::ParameterHandler parameterHandler;
    QFile file;

    file.setFileName(FILEPATH);
    parameterHandler.loadFile(FILEPATH);
    SCOPED_TRACE(fmt::format(fmt::emphasis::bold, "\n[ParameterHandler] Utils::ParameterHandler::fileName() did not return correct file name."));
    EXPECT_EQ(file.fileName(), parameterHandler.fileName());
}
