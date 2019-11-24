#ifndef WEB_SERVER_H
#define WEB_SERVER_H

class RestWebServer {
    public:
        bool shouldRestartConnection = false;

        void start();
};

extern RestWebServer WebServer;

#endif