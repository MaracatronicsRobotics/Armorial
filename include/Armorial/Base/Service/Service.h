#ifndef ARMORIAL_BASE_SERVICE_H
#define ARMORIAL_BASE_SERVICE_H

#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <grpc/support/time.h>

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <Armorial/Libs/nameof/include/nameof.hpp>

#include <QString>

namespace Base {
    namespace GRPC {
        /*!
         * \tparam T The protobuf service protobuf type that GRPC::Service class will be responsible to provide.
         * \brief The GRPC::Service class is the responsible to create and manage gRPC services.
         */
        template <typename T>
        class Service : public T::Service
        {
        public:
            /*!
             * \brief Constructor for the GRPC::Service class.
             * \param serviceAddress The address which the service will serve.
             * \param servicePort The port which the service will serve.
             */
            Service(QString serviceAddress, quint16 servicePort) {
                _serviceAddress = serviceAddress;
                _servicePort = servicePort;
                _server = nullptr;
            }

            /*!
             * \brief Virtual destructor for the GRPC::Service class.
             */
            virtual ~Service() {
                shutdownService();
            }

            /*!
             * \return A QString object containing the name of the implemented service.
             */
            virtual inline QString serviceName() const {
                return NAMEOF_TYPE_RTTI(*this).data();
            }

        protected:
            /*!
             * \brief Initialize the service T in the provided address and port.
             * \return A boolean containing the status of the initialization process.
             */
            [[nodiscard]] bool initializeService() {
                // Create address for the service in the format 'address:port'
                QString serviceAddress = QString("%1:%2").arg(_serviceAddress).arg(_servicePort);

                // Use ServerBuilder object to serve the required address:port and register the service into the network
                _serverBuilder.AddListeningPort(serviceAddress.toStdString(), grpc::InsecureServerCredentials());
                _serverBuilder.RegisterService(this);

                // Create server object using the server builder
                _server = _serverBuilder.BuildAndStart();

                // Check if server was created
                if(_server == nullptr) {
                    return false;
                }

                return true;
            }

            /*!
             * \brief Shutdown and wait until the service finishes.
             * \return A boolean that returns true when the operations have finished.
             * \note This method needs to be called in the children class to finish the service.
             */
            [[nodiscard]] bool shutdownService() {
                if(_server == nullptr) {
                    return true;
                }

                // Shutdown and wait for the shutdown
                _server->Shutdown();
                _server->Wait();

                return true;
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
            grpc::ServerBuilder _serverBuilder;
            std::unique_ptr<grpc::Server> _server;

            // Network address
            QString _serviceAddress;
            quint16 _servicePort;
        };
    }
}

#endif // ARMORIAL_BASE_SERVICE_H
