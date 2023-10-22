#ifndef ARMORIAL_BASE_CLIENT_H
#define ARMORIAL_BASE_CLIENT_H

#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <QList>
#include <QMutex>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QNetworkInterface>

#include <optional>

#include <Armorial/Libs/nameof/include/nameof.hpp>

#include <spdlog/spdlog.h>

namespace Base {
    namespace GRPC {
       /*!
        * \tparam T The type of the service obtained through the protobuf headers.
        * \brief The GRPC::Client class is the responsible to make the connections with the gRPC.
        * services created by the Service class.
        * @deprecated Unnused due to it's natural tendency of causing delay on modules connection.
        */
        template <typename T>
        class Client
        {
        public:
            /*!
             * \brief GRPC::Client constructor that initializes the network variables.
             * \param serviceAddress The address which the client will listen to.
             * \param servicePort The port which the client will listen to.
             */
            Client(QString serviceAddress, quint16 servicePort) {
                _serviceAddress = serviceAddress;
                _servicePort = servicePort;
                _stub = nullptr;
                _channel = nullptr;
            }

            /*!
             * \return A QString object containing the name of the implemented client.
             */
            virtual inline QString clientName() {
                return NAMEOF_TYPE_RTTI(*this).data();
            }

        protected:
            /*!
             * \brief Takes the state from the gRPC channel and check if it
             * is connected to the gRPC service.
             * \return A boolean that indicates the connection with the gRPC service.
             */
            [[nodiscard]] bool isConnectedToServer() {
                if(_stub == nullptr || _channel == nullptr) return false;

                return (  _channel->GetState(false) == GRPC_CHANNEL_READY
                       || _channel->GetState(false) == GRPC_CHANNEL_IDLE
                       || _channel->GetState(false) == GRPC_CHANNEL_CONNECTING);
            }

            /*!
             * \brief Connects to a new network data using the given network parameters and
             * update the network parameters internally.
             * \param serviceAddress, servicePort The given network parameters.
             * \return A boolean that shows if the client is connected or not.
             * \note This method just make a single call on 'connectToServer' method waiting for it.
             */
            [[nodiscard]] bool setClientNetworkData(QString serviceAddress, quint16 servicePort) {
                _serviceAddress = serviceAddress;
                _servicePort = servicePort;
                return connectToServer(true);
            }

            /*!
             * \brief Connects to the service using the network parameters
             * defined in the GRPC::Client constructor.
             * \param waitForConnected A boolean that indicates if is needed to wait for the connection
             * to occur.
             * \note This method *needs* to be used for the childs of this class using this boolean
             * as true.
             */
            [[nodiscard]] bool connectToServer(bool waitForConnected) {
                // Creating gRPC channel related network vars
                QString serviceAddress = QString("%1:%2").arg(_serviceAddress).arg(_servicePort);
                _channel = grpc::CreateChannel(serviceAddress.toStdString(), grpc::InsecureChannelCredentials());
                _stub = T::NewStub(_channel);

                // Wait for connection with gRPC server
                if(waitForConnected) {
                    if (!_channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(5, GPR_TIMESPAN)))) {
                        return false;
                    }
                }

                return true;
            }

            /*!
             * \brief Returns the shared pointer to the stub generated from
             * the connectToServer(bool) method.
             * \return A std::shared_ptr<T::Stub> object that points to the gRPC client stub.
             */
            std::shared_ptr<typename T::Stub> getStub() {
                return _stub;
            }

            /*!
             * \return The service address.
             */
            [[nodiscard]] QString getServiceAddress() {
                return _serviceAddress;
            }

            /*!
             * \return The service port.
             */
            quint16 getServicePort() {
                return _servicePort;
            }

        private:
            // GRPC Pointers
            std::shared_ptr<typename T::Stub> _stub;
            std::shared_ptr<grpc::Channel> _channel;

            // Network address
            QString _serviceAddress;
            quint16 _servicePort;
        };
    }

    namespace UDP {
        /*!
         * \brief The UDP::Client class is the responsible to make the connections with the
         * servers (such as vision) using sockets.
         */
        class Client
        {
        public:
            /*!
             * \brief UDP::Client constructor that initialize the network variables.
             * \param serverAddress The server address which the UDP::Client will listen to.
             * \param serverPort The port which the UDP::Client will listen to.
             * \param serverNetworkInterface The network interface which the UDP::Client will listen to.
             * \note By default the network interface will be set as 'lo'.
             */
            Client(QString serverAddress, quint16 serverPort, QString serverNetworkInterface = "lo")
            {
                _serverAddress = serverAddress;
                _serverPort = serverPort;
                _serverControlPort = 9999;
                _serverNetworkInterface = serverNetworkInterface;
                _socket = nullptr;
                _controlSocket = nullptr;
            }

            /*!
             * \brief UDP::Client constructor that initialize the network variables.
             * \param serverAddress The server address which the UDP::Client will listen to.
             * \param serverPort The port which the UDP::Client will listen to.
             * \param serverNetworkInterface The network interface which the UDP::Client will listen to.
             * \note By default the network interface will be set as 'lo'.
             */
            Client(QString serverAddress,
                   quint16 serverPort,
                   quint16 serverControlPort,
                   QString serverNetworkInterface = "lo")
            {
                _serverAddress = serverAddress;
                _serverPort = serverPort;
                _serverControlPort = serverControlPort;
                _serverNetworkInterface = serverNetworkInterface;
                _socket = nullptr;
                _controlSocket = nullptr;
            }

            /*!
             * \return A QString object containing the name of the implemented client.
             */
            virtual inline QString clientName() const {
                return NAMEOF_TYPE_RTTI(*this).data();
            }

        protected:
            /*!
             * \brief Update the network address that was previously defined in the constructor.
             * \param serverAddress The address which the UDP::Client socket will listen to.
             * \param serverPort The port which the UDP::Client socket will listen to.
             * \param isMulticast If it is a multicast connection.
             * \return
             */
            [[nodiscard]] bool updateNetworkAddress(QString serverAddress,
                                                    quint16 serverPort,
                                                    QString serverNetworkInterface,
                                                    bool isMulticast)
            {
                _mutex.lock();

                // Setup network addresses
                _serverAddress = serverAddress;
                _serverPort = serverPort;
                _serverControlPort = 9999;
                _serverNetworkInterface = serverNetworkInterface;

                // Perform connection
                // If is a multicast, bind and connect to multicast address
                // If it is not multicast, just connecto to required host
                bool connected = false;
                if (isMulticast) {
                    connected = bindAndConnectToMulticastNetwork();
                } else {
                    connected = connectToNetwork();
                }

                _mutex.unlock();

                return connected;
            }

            /*!
             * \brief Update the network address that was previously defined in the constructor.
             * \param serverAddress The address which the UDP::Client socket will listen to.
             * \param serverPort The port which the UDP::Client socket will listen to.
             * \param isMulticast If it is a multicast connection.
             * \return
             */
            [[nodiscard]] bool updateNetworkControlAddress(QString serverAddress,
                                                           quint16 serverPort,
                                                           quint16 serverControlPort,
                                                           QString serverNetworkInterface,
                                                           bool isMulticast)
            {
                _mutex.lock();

                // Setup network addresses
                _serverAddress = serverAddress;
                _serverPort = serverPort;
                _serverControlPort = serverControlPort;
                _serverNetworkInterface = serverNetworkInterface;

                // Perform connection
                // If is a multicast, bind and connect to multicast address
                // If it is not multicast, just connecto to required host
                bool connected = false;
                if(isMulticast) {
                    connected = bindAndConnectToMulticastNetwork();
                }
                else {
                    connected = connectToNetwork();
                }

                _mutex.unlock();

                return connected;
            }

            /*!
             * \brief Performs the bind and connection to a multicast network.
             * \return A boolean that contains the status of the connection process.
             */
            [[nodiscard]] bool bindAndConnectToMulticastNetwork() {
                // Check if socket is nullptr and create it
                if(_socket == nullptr) {
                    _socket = std::make_shared<QUdpSocket>(new QUdpSocket());
                }

                // Binding in defined network address / port
                if(_socket->bind(QHostAddress(_serverAddress), _serverPort, QUdpSocket::ShareAddress) == false) {
                    return false;
                }

                // Joining multicast group
                if(_socket->joinMulticastGroup(QHostAddress(_serverAddress), QNetworkInterface::interfaceFromName(_serverNetworkInterface)) == false) {
                    return false;
                }

                if (_serverControlPort != 9999) {
                    if (_controlSocket == nullptr) {
                        _controlSocket = std::make_shared<QUdpSocket>(new QUdpSocket());
                    }

                    if (_controlSocket->bind(QHostAddress(_serverAddress),
                                             _serverControlPort,
                                             QUdpSocket::ShareAddress)
                        == false) {
                        return false;
                    }

                    if (_controlSocket->joinMulticastGroup(QHostAddress(_serverAddress),
                                                           QNetworkInterface::interfaceFromName(
                                                               _serverNetworkInterface))
                        == false) {
                        return false;
                    }
                }

                return true;
            }

            /*!
             * \brief Perform a simple connection to a host server.
             * \param openMode The mode (OnlyRead, OnlyWrite, ReadWrite) that the socket will perform.
             * \param networkProtocol The protocol (IPV4 or IPV6) that the socket will use to perform the connection.
             * \return A boolean containing the status of the connection process.
             */
            [[nodiscard]] bool connectToNetwork(QIODevice::OpenModeFlag openMode = QIODevice::ReadWrite, QAbstractSocket::NetworkLayerProtocol networkProtocol = QAbstractSocket::AnyIPProtocol) {
                // Check if socket is nullptr and create it
                if(_socket == nullptr) {
                    _socket = std::make_shared<QUdpSocket>(new QUdpSocket());
                }

                if (_serverControlPort != 9999) {
                    if (_controlSocket == nullptr) {
                        _controlSocket = std::make_shared<QUdpSocket>(new QUdpSocket());
                    }
                }

                // Disconnect from network
                disconnectFromNetwork();

                // Connect to required host
                _socket->connectToHost(_serverAddress, _serverPort, openMode, networkProtocol);
                // Connect to specific network interface
                _socket->setMulticastInterface(
                    QNetworkInterface::interfaceFromName(_serverNetworkInterface));

                if (_serverControlPort != 9999) {
                    _controlSocket->connectToHost(_serverAddress,
                                                  _serverControlPort,
                                                  openMode,
                                                  networkProtocol);
                    _controlSocket->setMulticastInterface(
                        QNetworkInterface::interfaceFromName(_serverNetworkInterface));
                }

                return true;
            }

            /*!
             * \brief Disconnect from the previous connected network and wait until the
             * socket reaches the unconnected state.
             */
            void disconnectFromNetwork() {
                // If socket is nullptr, can not disconnect, so skip function
                if (_socket == nullptr) {
                    if (_controlSocket != nullptr) {
                        if (_controlSocket->isOpen()) {
                            _controlSocket->close();
                        }

                        _controlSocket->disconnectFromHost();

                        while (_controlSocket->state() != QUdpSocket::UnconnectedState) {
                        }
                    }
                    return;
                }
                // Close if socket is already open
                if (_socket->isOpen()) {
                    _socket->close();
                }

                // Disconnect from host
                _socket->disconnectFromHost();

                // Block until reach unconnected state
                while (_socket->state() != QUdpSocket::UnconnectedState) {
                }
            }

            /*!
             * \brief Check if has pending datagrams in the socket.
             * \return A boolean that informs if the socket has pending datagrams to be read.
             */
            [[nodiscard]] bool hasPendingDatagrams() {
                _mutex.lock();

                // If socket is nullptr it has no pending datagrams, so return false
                if(_socket == nullptr) {
                    _mutex.unlock();
                    return false;
                }

                // Check pending datagrams
                bool pendingDatagrams = _socket->hasPendingDatagrams();

                _mutex.unlock();

                return pendingDatagrams;
            }

            /*!
             * \brief Check if has pending datagrams in the control socket.
             * \return A boolean that informs if the control socket has pending datagrams to be read.
             */
            [[nodiscard]] bool hasPendingControlDatagrams()
            {
                _mutex.lock();

                // If socket is nullptr it has no pending datagrams, so return false
                if (_controlSocket == nullptr) {
                    _mutex.unlock();
                    return false;
                }

                // Check pending datagrams
                bool pendingDatagrams = _controlSocket->hasPendingDatagrams();

                _mutex.unlock();

                return pendingDatagrams;
            }

            /*!
             * \brief Take the upcoming datagram from the socket.
             * \return A std::optional object that can contains a QNetworkDatagram or not.
             */
            [[nodiscard]] std::optional<QNetworkDatagram> receiveDatagram() {
                _mutex.lock();

                // If socket is nullptr can not take any datagram, so return a empty one (invalid)
                if(_socket == nullptr) {
                    _mutex.unlock();
                    return std::nullopt;
                }

                // Take network datagram
                QNetworkDatagram datagram = _socket->receiveDatagram();

                // Check if is valid
                if(!datagram.isValid()) {
                    _mutex.unlock();
                    return std::nullopt;
                }

                _mutex.unlock();

                return datagram;
            }

            /*!
             * \brief Send a given datagram to_serverControlPort the socket.
             * \param The given datagram.
             * \return True if the given datagram could be sent through the socket and False otherwise.
             */
            [[nodiscard]] bool sendDatagram(const QNetworkDatagram &datagram)
            {
                _mutex.lock();

                // If socket is nullptr can not send any datagram, so return false
                bool sentDatagram = false;
                if(_socket != nullptr) {
                    // Try to send datagram
                    if(_socket->writeDatagram(datagram) != -1) {
                        sentDatagram = true;
                    }
                }

                _mutex.unlock();

                return sentDatagram;
            }

            /*!
             * \brief Send a given datagram to the control socket.
             * \param The given datagram.
             * \return True if the given datagram could be sent through the cnotrol socket and False otherwise.
             */
            [[nodiscard]] bool sendControlDatagram(const QNetworkDatagram &datagram)
            {
                _mutex.lock();

                // If socket is nullptr can not send any datagram, so return false
                bool sentDatagram = false;
                if (_controlSocket != nullptr) {
                    // Try to send datagram
                    if (_controlSocket->writeDatagram(datagram) != -1) {
                        sentDatagram = true;
                    }
                }

                _mutex.unlock();

                return sentDatagram;
            }

            /*!
             * \return The server address.
             */
            [[nodiscard]] QString getServerAddress() {
                _mutex.lock();
                QString serverAddress = _serverAddress;
                _mutex.unlock();

                return serverAddress;
            }

            /*!
             * \return The server network interface.
             */
            QString getServerNetworkInterface() {
                _mutex.lock();
                QString serverNetworkInterface = _serverNetworkInterface;
                _mutex.unlock();

                return serverNetworkInterface;
            }

            /*!
             * \return The server port.
             */
            [[nodiscard]] quint16 getServerPort() {
                _mutex.lock();
                quint16 serverPort = _serverPort;
                _mutex.unlock();

                return serverPort;
            }

            /*!
             * \return The server control port.
             */
            [[nodiscard]] quint16 getServerControlPort()
            {
                _mutex.lock();
                quint16 serverControlPort = _serverControlPort;
                _mutex.unlock();

                return serverControlPort;
            }

            /*!
             * \return The socket shared pointer.
             */
            std::shared_ptr<QUdpSocket> getSocket() { return _socket; }

            /*!
            * \return The control socket shared pointer
            */
            std::shared_ptr<QUdpSocket> getControlSocket() { return _controlSocket; }

        private:
            // Pointer to socket
            std::shared_ptr<QUdpSocket> _socket;

            // Pointer to control socket
            std::shared_ptr<QUdpSocket> _controlSocket;

            // Mutex for socket management
            QMutex _mutex;

            // Network address
            QString _serverAddress;
            QString _serverNetworkInterface;
            quint16 _serverPort;
            quint16 _serverControlPort;
        };
    }
}

#endif // ARMORIAL_BASE_CLIENT_H
