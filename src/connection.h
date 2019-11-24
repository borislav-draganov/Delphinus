#ifndef CONNECTION_H
#define CONNECTION_H

#include <ArduinoJson.h>

class Connection {
    public:
        void start();

    private:
        String apSsid = "Delphinus";
        String apPassword = "123456789";

        void attemptToConnect();

        void startAsAccessPoint();
};

extern Connection WifiConnection;

#endif