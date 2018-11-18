#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"

class ofFaceFinder {
    public:
        void setup(int deviceId = 0);
        void update();
        void draw();
        void exit();
        ofVec2f getCurrentFace();
        ofVec2f getCenterCoordinate(ofVec2f faceCoord, float strength);

        ofVideoGrabber video;
        ofxCvHaarFinder finder;
        int camWidth = 320;
        int camHeight = 240;

        bool enabled = true;
        bool debug = false;

        vector<ofVec2f> faceCenters;

    private:
        ofxCvColorImage colourImg;
        ofxCvGrayscaleImage greyImg;
        int offsetX;
        int offsetY;
};
