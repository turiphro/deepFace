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