#include "particle.h"

Particle::Particle(ofVec2f (*getForce)(ofVec2f pos)) {
    int x = (int)ofRandom(ofGetWidth());
    int y = (int)ofRandom(ofGetHeight());
    pos.set(x, y);
    color.set(0, 0, 0);
    targetColor.set(255, 0, 0);
    this->getForce = getForce;
}

void Particle::update() {
    // update speed
    ofVec2f force = getForce(pos); // get force vector
    ofVec2f wiggle(ofRandom(2) - 1.0, ofRandom(2) - 1.0);
    speed = damping * speed + (1 - damping) * force + entropy * wiggle;

    // update position
    pos += speed;

    // update appearance
    color = (1 - colorFader) * color + colorFader * targetColor;
    colorFader = min(1.0, colorFader + 0.001);
}

void Particle::applyForce(function<ofVec2f(ofVec2f)> getForce) {
    // apply force to particles
    ofVec2f force = getForce(pos);
    speed += force;
}

void Particle::draw() {
    ofSetColor(color);
    ofDrawEllipse(pos, particleSize, particleSize);
}

void Particle::increaseEntropy() {
    entropy *= 1.1;
}

void Particle::decreaseEntropy() {
    entropy = max(0.1, entropy*0.9);
}

void Particle::setColor(ofColor color) {
    targetColor = color;
    colorFader = 0;
}
