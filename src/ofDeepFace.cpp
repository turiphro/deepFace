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
}

//--------------------------------------------------------------
void ofDeepFace::update(){
    for (auto &particle : particles) {
        particle.update();

        if (ofGetMousePressed()) {
            particle.applyForce(attractToMouse);
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
            for (auto &particle : particles) {
                particle.decreaseEntropy();
            }
            break;
        case '+':
            for (auto &particle : particles) {
                particle.increaseEntropy();
            }
            break;
        case 'm':
            // change 'mood' to random color
            ofColor color;
            color.setHsb(ofRandom(255), 255, 255);
            for (auto &particle : particles) {
                particle.setColor(color);
            }
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
