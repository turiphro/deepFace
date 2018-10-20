#include "ofDeepFace.h"
#include "forceField.h"

//--------------------------------------------------------------
void ofDeepFace::setup(){
    ofSetFrameRate(60);

    ofSetBackgroundColor(0, 0, 0);

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
    auto devices = soundStream.getMatchingDevices("default");
    if (!devices.empty()) {
        settings.setInDevice(devices[0]);
        audioEnabled = true;
    }
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.bufferSize = 256;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofDeepFace::update(){
    // apply regular particle movement
    for (auto &particle : particles) {
        particle.update();
    }

    // process mouse
    if (ofGetMousePressed()) {
        for (auto &particle : particles) {
            particle.applyForce(attractToMouse);
        }
    }

    // process sound
    if (audioEnabled) {
        scaledVol = ofMap(smoothedVol, 0.0, maxVol, 0.0, 1.0, true);
        auto reactToSound = createReactToSound(scaledVol);
        if (scaledVol > 0.1) {
            for (auto &particle : particles) {
                particle.applyForce(reactToSound);
            }
        }
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
    double curVol = 0.0;

    int count = 0;
    for  (size_t i = 0; i < input.getNumFrames(); i++) {
        double left = input[i*2]*0.5;
        double right = input[i*2+1]*0.5;
        curVol += left * left + right * right;
        count += 2;
    }

    curVol /= (double)count;
    curVol = sqrt(curVol);
    smoothedVol = 0.93 * smoothedVol + 0.07 * curVol;
    maxVol = 0.5 * maxVol + 0.5 * max(maxVol, smoothedVol);
}