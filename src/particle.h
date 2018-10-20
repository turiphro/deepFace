#pragma once

#include "ofMain.h"

class Particle {
    public:

        Particle(ofVec2f (*f)(ofVec2f pos));
        void draw();
        void update();
        void increaseEntropy();
        void decreaseEntropy();
        void setColor(ofColor color);

        ofVec2f (*getForce)(ofVec2f);
        ofVec2f pos;
        ofVec2f speed;
        ofColor color;
        ofColor targetColor;
        double entropy = 1.0;
        double damping = 0.8;
        double colorFader = 0;
};