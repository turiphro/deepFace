#include "ofMain.h"
#include "ofDeepFace.h"

//========================================================================
int main() {
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new ofDeepFace());
}
