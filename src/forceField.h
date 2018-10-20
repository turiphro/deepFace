#pragma once

#include "ofMain.h"

ofVec2f getForceCenter(ofVec2f pos);
ofVec2f getForceCircle(ofVec2f pos);
ofVec2f attractToMouse(ofVec2f pos);

function<ofVec2f(ofVec2f)> createReactToSound(double volume);