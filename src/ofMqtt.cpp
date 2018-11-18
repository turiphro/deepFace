#include "ofMqtt.h"

void ofMqtt::setup(string host, string username, string password, int port) {
    this->host = host;
    this->port = port;
    this->username = username;
    this->password = password;
    this->clientId = "deepface-" + to_string(ofRandom(0, 100));
    client.begin(this->host, this->port);

    ofAddListener(client.onOnline, this, &ofMqtt::onOnline);
    ofAddListener(client.onOffline, this, &ofMqtt::onOffline);
    ofAddListener(client.onMessage, this, &ofMqtt::onMessage);
}

void ofMqtt::update() {
    // try connecting using exponential back-off
    // note: client.connected() doesn't seem to work
    if (!connected && ofGetSystemTimeMillis() - lastTry > waitingTime) {
        cout << "ofMxtt: reconnecting to " << host << ":" << port << endl;
        lastTry = ofGetSystemTimeMillis();
        waitingTime = min((uint64_t)5*60000, waitingTime * 2);

        connected = client.connect(clientId, username, password);
    }

    if (connected) {
        waitingTime = 500;

        client.update();
    }
}

void ofMqtt::draw() {
}

void ofMqtt::exit() {
    client.disconnect();
}

void ofMqtt::onOnline() {
    cout << "mqtt online" << endl;

    client.subscribe("increaseEntropy");
    client.subscribe("decreaseEntropy");
    client.subscribe("colour");
}

void ofMqtt::onOffline() {
    cout << "mqtt offline" << endl;
    connected = false;
}

void ofMqtt::onMessage(ofxMQTTMessage &msg) {
    cout << "mqtt message: " << msg.topic << " | " << msg.payload << endl;
    messages.push(make_tuple(msg.topic, msg.payload));
}
