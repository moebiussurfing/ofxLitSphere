#pragma once

#include "ofMain.h"
#include "ofxLitSphere.h"
#include "ofxGui.h"
#include "DisplacementSphereMesh.h"

//#define USE_FILE_BROWSER -> to run this example you must comment/disable this into the addon or to add ImGui to the project

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    ofEasyCam cam;

	ofxPanel gui;
    
    ofxLitSphere litSphere;
    ofxLitSphere litSphere02;
    DisplacementSphereMesh displacement;
    ofMaterial material;
    ofLight light;

	//params
	ofParameter<bool> bmat1;
	ofParameter<bool> bmat2;
	ofParameter<int> mat1;
	ofParameter<int> mat2;
	ofParameter<float> mod;
};
