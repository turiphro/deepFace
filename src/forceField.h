#pragma once

#include "ofMain.h"

function<ofVec2f(ofVec2f)> createCenterForce(ofVec2f pos);
function<ofVec2f(ofVec2f)> createCircleForce(ofVec2f pos);
function<ofVec2f(ofVec2f)> createReactToTouch(ofVec2f mousePos);
function<ofVec2f(ofVec2f)> createReactToSound(double volume);
