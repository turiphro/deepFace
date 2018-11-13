#include "ofDeepFace.h"
#include "forceField.h"

//--------------------------------------------------------------
void ofDeepFace::setup(){
    ofSetFrameRate(60);

    ofSetBackgroundColor(0, 0, 0);

    touch.setup("/dev/input/event2");
    touch.calibrate(true, 150, 4000, 175, -3450);

    api.setup("192.168.0.201", "", "", 1883);

    // add particles for inner eye circle
    for (int p=0; p<particleCountInner; p++) {
        Particle particle(getForceCenter);
        particles.push_back(particle);
    }

    // add particles for outer eye circle
    for (int p=0; p<particleCountOuter; p++) {
        Particle particle(getForceCircle);
        particles.push_back(particle);
    }

    // setup sound
    soundStream.printDeviceList();
    ofSoundStreamSettings settings;
    auto devices = soundStream.getMatchingDevices("", 1);
    if (!devices.empty()) {
        cout << "Selecting audio: " << devices[0] << endl;
        settings.setInDevice(devices[0]);
        audioEnabled = true;

        settings.setInListener(this);
        settings.sampleRate = 44100;
        settings.bufferSize = 256;
        settings.numOutputChannels = 0;
        settings.numInputChannels = 1;
        soundStream.setup(settings);
    }
}

//--------------------------------------------------------------
void ofDeepFace::update(){
    // process mouse or touch
    bool touching = touch.isTouched();
    if (touching) {
        auto reactToTouch = createReactToTouch(touch.getCoordinates());
        for (auto &particle : particles) {
            particle.applyForce(reactToTouch);
        }
    }

    // process sound
    // (disabled when touching, which makes sound)
    if (audioEnabled && !touching) {
        scaledVol = ofMap(smoothedVol, 0.0, maxVol, 0.0, 1.0, true);
        maxVol *= 0.9999999; // slow decay
        if (scaledVol > 0.1) {
            auto reactToSound = createReactToSound(scaledVol);
            for (auto &particle : particles) {
                particle.applyForce(reactToSound);
            }
        }
    }

    // process api messages
    api.update();
    while (!api.messages.empty()) {
        auto &msg = api.messages.front();
        api.messages.pop();
        string topic = get<0>(msg);
        string payload = get<1>(msg);

        processMessage(topic, payload);
    }

    // apply regular particle movement
    for (auto &particle : particles) {
        particle.update();
    }
}

//--------------------------------------------------------------
void ofDeepFace::draw(){
    for (Particle particle : particles) {
        particle.draw();
    }
}

//--------------------------------------------------------------
void ofDeepFace::keyPressed(int key){
    switch (key) {
        case '-':
            cout << "Decreased entropy" << endl;
            decreaseEntropy();
            break;
        case '+':
            increaseEntropy();
            break;
        case 'a':
            // turn audio processing on or off
            audioEnabled = !audioEnabled;
            cout << "Audio processing set to " << audioEnabled << endl;
            if (audioEnabled) {
                soundStream.start();
            } else {
                soundStream.stop();
            }
            break;
        case 'm':
            // change 'mood' to random colour
            ofColor colour;
            colour.setHsb(ofRandom(255), 255, 255);
            setColour(colour);
            break;
    }
}

//--------------------------------------------------------------
void ofDeepFace::keyReleased(int key){

}

//--------------------------------------------------------------
void ofDeepFace::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofDeepFace::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofDeepFace::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofDeepFace::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofDeepFace::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofDeepFace::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofDeepFace::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofDeepFace::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofDeepFace::dragEvent(ofDragInfo dragInfo){ 

}

void ofDeepFace::audioIn(ofSoundBuffer & input) {
    if (!audioEnabled) {
        return;
    }

    double curVol = 0.0;

    int count = 0;
    for  (size_t i = 0; i < input.getNumFrames(); i++) {
        double left = input[i];
        curVol += left * left;
        count += 1;
    }

    curVol /= (double)count;
    curVol = sqrt(curVol);
    smoothedVol = 0.8 * smoothedVol + 0.2 * curVol;
    maxVol = max(maxVol, smoothedVol);
}

void ofDeepFace::processMessage(string topic, string payload) {
    if (topic.compare("decreaseEntropy") == 0) {

        decreaseEntropy();

    } else if (topic.compare("increaseEntropy") == 0) {

        increaseEntropy();

    } else if (topic.compare("colour") == 0) {

        // parse "r g b" from string
        stringstream ss(payload);
        int number;
        vector<int> numbers;
        while (ss >> number) {
            numbers.push_back(number);
        }

        if (numbers.size() == 3) {
            ofColor colour(numbers[0], numbers[1], numbers[2]);
            setColour(colour);
        } else {
            cout << "! setColour: cannot parse string as 3 numbers: " << payload << endl;
        }

    } else {

        cout << "! unknown message topic: " << topic << endl;

    }
}

void ofDeepFace::decreaseEntropy() {
    for (auto &particle : particles) {
        particle.decreaseEntropy();
    }
    cout << "Decreased entropy" << endl;
}

void ofDeepFace::increaseEntropy() {
    for (auto &particle : particles) {
        particle.increaseEntropy();
    }
    cout << "Increased entropy" << endl;
}

void ofDeepFace::setColour(ofColor colour) {
    for (auto &particle : particles) {
        particle.setColor(colour);
    }
    cout << "Changed colour to " << colour << endl;
}

void ofDeepFace::exit() {
    touch.exit();
    api.exit();
}
