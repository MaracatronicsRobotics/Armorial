#ifndef PARAMETER_H
#define PARAMETER_H

#include <QVariant>

#include <spdlog/spdlog.h>

namespace Utils {
    /*!
     * \brief The Utils::Parameter class provides a overloaded interface for the QVariant
     * class, in which a way we can use the [] and () operators to access its members in a
     * easier way integrated with the Utils::ParameterHandler class.
     */
    class Parameter : public QVariant
    {

    /*!
    * \brief ParameterMap is a synonym for QMap<QString, Parameter>.
    */
    typedef QMap<QString, Parameter> ParameterMap;

    public:
        /*!
         * \brief Parameter default constructor.
         */
        Parameter() = default;

        /*!
         * \brief Parameter constructor that receives a QVariant and copy
         * the data from it.
         * \param var The given QVariant.
         */
        Parameter(const QVariant& var) {
            setValue(var);
        }

        /*!
         * \brief Overload for the operator [] that allows to return a Parameter
         * instance given a key from this Parameter instance.
         * \param key The given key.
         * \return A Utils::Parameter instance.
         * \note This method will cast a spdlog::warn if the passed key is invalid, but
         * will return a default Utils::Parameter instance.
         */
        Parameter operator[](const QString& key) const {
            if(!toMap().contains(key)) {
                spdlog::warn("Invalid key '{}' passed to access Parameter instance.", key.toStdString());
                return Parameter();
            }

            return getAsMap()[key];
        }

        /*!
         * \brief Convert this Parameter to a ParameterMap instance.
         * \return A ParameterMap instance.
         */
        ParameterMap getAsMap() const {
            QVariantMap map = toMap();
            QList<QString> keys = map.keys();

            ParameterMap newMap;
            for (auto &k : keys) {
                newMap[k] = map[k];
            }

            return newMap;
        }

        /*!
         * \brief Get this Parameter instace associated keys.
         * \return A QList<String> instance containing this Parameter instance associated keys.
         */
        QList<QString> getKeys() const {
            return toMap().keys();
        }
    };
}

#endif // PARAMETER_H
