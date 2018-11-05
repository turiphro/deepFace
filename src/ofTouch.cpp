# include "ofTouch.h"

void ofTouch::setup(string device) {
    int failure = touch.init(&device[0]);
    touchEnabled = !failure;

    if (touchEnabled) {
        ofHideCursor();
        cout << "Touchscreen device: " << touch.getName() << endl;
    }

}

void ofTouch::calibrate(bool swapXY, int minX, int maxX, int minY, int maxY) {
    this->swapXY = swapXY;
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
}

void ofTouch::update() {
}

bool ofTouch::isTouched() {
    // Is the touchscreen or mouse currently being touched?

    if (ofGetMousePressed()) {
        return true;
    }

    if (touchEnabled && touch.getButton()) {
        return true;
    }

    return false;
}

ofVec2f ofTouch::getCoordinates() {
    // Get coordinates of current press

    if (ofGetMousePressed()) {
        return ofVec2f(ofGetMouseX(), ofGetMouseY());
    }

    if (touchEnabled && touch.getButton()) {
        ofVec2f rawCoord = touch.getCoordTouch();
        float x = rawCoord.x;
        float y = rawCoord.y;
        if (swapXY) {
            swap(x, y);
        }
        ofVec2f coord(ofMap(x, minX, maxX, 0, ofGetWidth()),
                      ofMap(y, minY, maxY, 0, ofGetHeight()));
        return coord;
    }

    return ofVec2f();
}

void ofTouch::exit() {
    touch.exit();
}
