#pragma once

#include "ofMain.h"
#include "ofxLitSphere.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    
    ofxLitSphere litSphere;
	
	ofEasyCam cam;

	bool indexScene;
	ofMesh meshForm;
	ofPlanePrimitive primFloor; // just using a primitive as floor

	bool bEnableMouseCam;

	ofxAssimpModelLoader model;

	ofRectangle rView;
};
