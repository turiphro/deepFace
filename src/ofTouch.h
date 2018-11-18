/*
 * Abstraction around touch interfaces
 * Currently supports the mouse and 5inch touchscreens on the raspberry pi
 */

#pragma once

#include "ofMain.h"
#include "ofxRPiTouch.h"

class ofTouch {
    public:

        void setup(string device = "/dev/input/event0");
        void calibrate(bool swapXY, int minX, int maxX, int minY, int maxY);
        void update();
        void draw();
        void exit();

        bool isTouched();
        ofVec2f getCoordinates();

        bool swapXY = true;
        int minX = 0;
        int maxX = 800;
        int minY = 0;
        int maxY = 480;

        bool touchEnabled;
        ofxRPiTouch touch;
};
