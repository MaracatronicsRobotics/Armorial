#ifndef ARMORIAL_COMMON_PACKET_H
#define ARMORIAL_COMMON_PACKET_H

#include <Armorial/Common/Types/Traits/Traits.h>

#include <vector>
#include <cstdint>

namespace Common {
    /*!
     * \brief The Common::Packet class provides a interface to serialize bytes in such a way to produce
     * the radio communication protocol message that is defined by each category.
     * \note This class provides at the end a std::vector<uint8_t> instance which can be passed through
     * a serial port.
     */
    class Packet
    {
    public:
        /*!
         * \brief Packet default constructor
         */
        Packet() = default;

        /*!
         * \tparam T The type of the message that will be inserted.
         * \brief Insert the bytes of the given message in this packet.
         * \note This method needs that the type T is unsigned.
         */
        template<typename T>
        std::enable_if_t<std::is_unsigned_v<T>, void> insertBytes(const T& message) {
            int size_bytes = sizeof(T) * 8;
            for(int shift = size_bytes - 8; shift >= 0; shift -= 8) {
                uint8_t byte = message >> shift;
                _message.push_back(byte);
            }
        }

        /*!
         * \tparam T The type of the message that will be inserted.
         * \brief Insert the bytes of the given message in this packet.
         * \note This operator overload needs that the type T is unsigned.
         */
        template<typename T>
        std::enable_if_t<std::is_unsigned_v<T>, void> operator<< (const T& message) {
            this->insertBytes(message);
        }

        /*!
         * \return A std::vector<uint8_t> instance which stores a copy of the message.
         */
        std::vector<uint8_t> message() {
            return _message;
        }

        /*!
         * \brief Declaration for the operator (char *) which allows this class to be passed
         * as argument for the `QSerialPort::write(char*, size_t)` method.
         */
        operator char*() {
            return (char*)(&_message[0]);
        }

        /*!
         * \return The message size in bytes.
         */
        size_t size() {
            return _message.size();
        }

        /*!
         * \brief Clear the packet message.
         */
        void clearMessage() {
            _message.clear();
        }

    private:
        /*!
         * \brief Instance of std::vector<uint8_t> which stores the message.
         */
        std::vector<uint8_t> _message;
    };
}

#endif // ARMORIAL_COMMON_PACKET_H
