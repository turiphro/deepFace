#pragma once

#include "ofMain.h"

class Particle {
    public:

        Particle(ofVec2f (*f)(ofVec2f pos));
        void draw();
        void update();
        void applyForce(function<ofVec2f(ofVec2f)>);
        void increaseEntropy();
        void decreaseEntropy();
        void setColor(ofColor color);

        ofVec2f (*getForce)(ofVec2f);
        ofVec2f pos;
        ofVec2f speed;
        ofColor color;
        ofColor targetColor;
        int particleSize = 4;
        double entropy = 1.0;
        double damping = 0.8;
        double colorFader = 0;
};
