#include "ofDeepFace.h"
#include "forceField.h"

//--------------------------------------------------------------
void ofDeepFace::setup(){
    ofSetFrameRate(60);

    ofSetBackgroundColor(0, 0, 0);

    touch.setup("/dev/input/event2");
    touch.calibrate(true, 150, 4000, 175, -3450);

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
            for (auto &particle : particles) {
                particle.decreaseEntropy();
            }
            break;
        case '+':
            cout << "Increased entropy" << endl;
            for (auto &particle : particles) {
                particle.increaseEntropy();
            }
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
            // change 'mood' to random color
            ofColor color;
            color.setHsb(ofRandom(255), 255, 255);
            cout << "Changed colour to " << color << endl;
            for (auto &particle : particles) {
                particle.setColor(color);
            }
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

void ofDeepFace::exit() {
    touch.exit();
}
