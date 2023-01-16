#ifndef ARMORIAL_UTILS_PARAMETERHANDLER_H
#define ARMORIAL_UTILS_PARAMETERHANDLER_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>

#include "Parameter.h"

namespace Utils {
    /*!
     * \brief The Utils::ParameterHandler class provides a interface to load JSON parameter files.
     */
    class ParameterHandler
    {
    public:
        /*!
         * \brief ParameterHandler default constructor
         */
        ParameterHandler() = default;

        /*!
         * \brief Load a JSON file in a given path.
         * \param parameterFilePath The given path.
         * \return True if loaded the file succesfully and False otherwise.
         */
        [[nodiscard]] bool loadFile(QString parameterFilePath);

        /*!
         * \return The loaded file name.
         */
        [[nodiscard]] QString fileName();

        /*!
         * \brief Overload for the operator [] that receives a key and returns the
         * document map associated with it.
         * \param key The given key.
         * \return A QVariant object stored by the given key.
         * \note If a given key is invalid (does not exists in the document map, it will
         * raise a warning in the terminal).
         */
        Parameter operator[](QString key) const;

        /*!
         * \brief Get this ParameterHandler instace associated keys.
         * \return A QList<String> instance containing this ParameterHandler instance associated keys.
         */
        QList<QString> getKeys() const;

    private:
        // File
        QFile _parameterFile;

        // Internal json parse vars
        QJsonDocument _document;
        QVariantMap _documentMap;
    };
}

#endif // ARMORIAL_UTILS_PARAMETERHANDLER_H
