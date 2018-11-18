#include "ofFaceFinder.h"

void ofFaceFinder::setup(int deviceId) {

    vector<ofVideoDevice> devices = video.listDevices();
    cout << "Webcams:" << endl;
    for (size_t i = 0; i < devices.size(); i++) {
        cout << " * " << devices[i].id << ": " << devices[i].deviceName << endl;
    }

    video.setDeviceID(deviceId);

    video.setDesiredFrameRate(10);
    video.initGrabber(camWidth, camHeight);

    if (devices.size() == 0 || !video.isInitialized()) {
        // some kind of failure
        enabled = false;
    }

    finder.setScaleHaar(1.12); // default: 1.08
    finder.setNeighbors(3); // default: 2
    finder.setup("haarcascade_frontalface_default.xml");

    greyImg.allocate(camWidth, camHeight);
    colourImg.allocate(camWidth, camHeight);
}

void ofFaceFinder::update() {
    if (!enabled) {
        return;
    }

    video.update();

    if (video.isFrameNew()) {
        colourImg.setFromPixels(video.getPixels());
        colourImg.mirror(false, true);
        greyImg = colourImg; // converts image type
        finder.findHaarObjects(greyImg);
    }
}

void ofFaceFinder::draw() {
    if (!enabled) {
        return;
    }

    if (debug) {
        offsetX = ofGetWidth() / 2 - camWidth / 2;
        offsetY = ofGetHeight() / 2 - camHeight / 2;

        ofSetColor(255, 255, 255, 100);
        colourImg.draw(offsetX, offsetY);
        finder.draw(offsetX, offsetY);

        /*
        if (finder.blobs.size() > 0) {
            cout << "found faces: " << finder.blobs.size() << endl;
        }
        */
    }

    // update faces; for now simply replace list with current faces
    // could be changed to tracking instead
    faceCenters.clear();
    for (unsigned int i = 0; i < finder.blobs.size(); i++) {
        ofRectangle rect = finder.blobs[i].boundingRect;
        ofVec2f center((float)(rect.x + rect.width/2.0) / camWidth,
                       (float)(rect.y + rect.height/2.0) / camHeight);
        faceCenters.push_back(center);
    }
}

void ofFaceFinder::exit() {
    video.close();
}

ofVec2f ofFaceFinder::getCurrentFace() {
    // circles through faces, gives current one
    if (faceCenters.size() == 0) {
        ofVec2f null(0, 0);
        return null;
    }

    // return first face for now;
    // could be changed to rotating between them over time
    return faceCenters[0];
}

ofVec2f ofFaceFinder::getCenterCoordinate(ofVec2f faceCoord, float strength) {
    /*
     * Calculate pixel coordinates from the center of a detected face,
     * mapping from webcam coordinates to screen coordinates with a strength
     * strength: force of the face pulling the coordinate
     */
    ofVec2f faceCoordCentered(faceCoord.x - 0.5, faceCoord.y - 0.5);

    ofVec2f screenCenter(ofGetWidth() / 2.0, ofGetHeight() / 2.0);
    ofVec2f faceOffset(ofGetWidth() / 2.0 * faceCoordCentered.x,
                       ofGetHeight() / 2.0 * faceCoordCentered.y);
    ofVec2f newCenter = screenCenter + strength * faceOffset;
    return newCenter;
}
