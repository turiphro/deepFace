#pragma once

#include "ofMain.h"
#include "ofTouch.h"
#include "ofMqtt.h"
#include "ofFaceFinder.h"
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

		vector<Particle> particles;
		int particleCountInner = 500;
		int particleCountOuter = 1000;
        enum particleGroups {
            INNER = 0,
            OUTER = 1
        };

        ofTouch touch;
        ofMqtt api;

        bool faceEnabled = true;
        ofFaceFinder faceFinder;
        float faceForceInner = 0.5;
        float faceForceOuter = 0.3;

		bool audioEnabled = false;
		ofSoundStream soundStream;
		double smoothedVol;
		double scaledVol;
		double maxVol = 0.1;
};
