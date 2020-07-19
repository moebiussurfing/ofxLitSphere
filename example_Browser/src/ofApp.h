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
	
	ofEasyCam cam;
	ofRectangle rView;
	bool bEnableMouseCam;
    
    ofxLitSphere litSphere;

	int indexScene;

	//1A
	ofxAssimpModelLoader model;
	//1B
	//ofMesh meshForm;

	bool bDrawFloor = false;
	ofPlanePrimitive primFloor; // just using a primitive as floor
};
