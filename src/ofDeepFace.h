#pragma once

#include "ofMain.h"
#include "ofTouch.h"
#include "ofMqtt.h"
#include "particle.h"

class ofDeepFace : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();

		void audioIn(ofSoundBuffer & input);

        void processMessage(string topic, string payload);
        void decreaseEntropy();
        void increaseEntropy();
        void setColour(ofColor colour);

		int particleCountInner = 500;
		int particleCountOuter = 1000;
		vector<Particle> particles;

        ofTouch touch;
        ofMqtt api;

		bool audioEnabled = false;
		ofSoundStream soundStream;
		double smoothedVol;
		double scaledVol;
		double maxVol = 0.1;
};
