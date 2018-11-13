#pragma once

#include "ofMain.h"
#include "ofxMQTT.h"

class ofMqtt {
    public:
        ofxMQTT client;
        void setup(string host, string username, string password, int port = 1883);
        void update();
        void exit();

        void onOnline();
        void onOffline();
        void onMessage(ofxMQTTMessage &msg);

        bool connected;
        queue<tuple<string, string>> messages;

    private:
        string clientId;
        string host;
        int port;
        string username;
        string password;

        uint64_t lastTry;
        uint64_t waitingTime = 500;
};
