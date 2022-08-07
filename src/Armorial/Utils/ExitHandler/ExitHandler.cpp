#include <Armorial/Utils/ExitHandler/ExitHandler.h>

#include <signal.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace Utils;

QCoreApplication* ExitHandler::_app = nullptr;
int ExitHandler::_counter = 0;

void ExitHandler::setApplication(QCoreApplication *app) {
    ExitHandler::_app = app;
}

void ExitHandler::setup() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = ExitHandler::run;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

void ExitHandler::run(int s) {
    ExitHandler::_counter++;
    switch(ExitHandler::_counter) {
        case 1: {
            ExitHandler::_app->exit();
        }
        break;
        case 2: {
            // Force exit
            exit(EXIT_FAILURE);
        }
        break;
    }
}
