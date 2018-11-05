#include "forceField.h"

ofVec2f getForceCenter(ofVec2f pos) {
    // Move towards a filled circle; no force when within
    ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);
    double radiusInner = ofGetWidth()/15.0;

    ofVec2f difference = center - pos;
    double distance = difference.length();
    ofVec2f zero(0, 0);
    if (distance > radiusInner) {
        return difference * (distance - radiusInner) / ofGetWidth();
    } else {
        return zero;
    }
}

ofVec2f getForceCircle(ofVec2f pos) {
    // Move towards the contour of a circle
    ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);
    double circleRadius = ofGetWidth()/15.0*4.0;
    double circleWidth = circleRadius/15.0;

    ofVec2f difference = center - pos;
    double distance = difference.length();
    ofVec2f zero(0, 0);
    if (distance > circleRadius + circleWidth) {
        return difference * (distance - circleRadius - circleWidth) / ofGetWidth();
    } else if (distance < circleRadius - circleWidth) {
        return difference * (distance - circleRadius + circleWidth) / ofGetWidth();
    } else {
        return zero;
    }
}

function<ofVec2f(ofVec2f)> createReactToTouch(ofVec2f mousePos) {
    return [mousePos] (ofVec2f pos) -> ofVec2f {
        // apply attraction to mouse position
        double minDistance = ofGetWidth()/15.0*2;
        double strengthMouse = 1;       // magic constant
        double strengthExcitement = 8;  // magic constant

        ofVec2f difference = (mousePos - pos);
        double distance = max(minDistance, (double)difference.length()); // prevent extreme black-hole animation
        ofVec2f force = ofGetWidth() / (distance * distance) * difference;
        ofVec2f wiggle(ofRandom(2) - 1.0, ofRandom(2) - 1.0);

        return strengthMouse * force + strengthExcitement * wiggle;
    };
}

function<ofVec2f(ofVec2f)> createReactToSound(double volume) {
    return [volume] (ofVec2f pos) -> ofVec2f {
        // apply animation to sound
        double strengthExcitement = ofGetWidth()/15.0;  // magic constant

        ofVec2f center(ofGetWidth()/2, ofGetHeight()/2);
        ofVec2f difference = (center - pos);
        ofVec2f force = difference / ofGetWidth();

        return -1 * strengthExcitement * volume * force;
    };
}
