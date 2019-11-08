#include "webServer.h"

ESP8266WebServer server(80);

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Title of the document</title>
</head>

<body>
Content of the document......
</body>

</html>
)=====";

void startWebServer() {
    Serial.println("Starting web server");
    server.on("/", handleRoot);

    server.begin();
}

void handleClient() {
    server.handleClient();
}

void handleRoot() {
    Serial.println("Opening root");

    server.send(200, "text/html", webpage);
}