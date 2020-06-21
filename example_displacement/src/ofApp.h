#pragma once

#include "ofMain.h"
#include "ofxLitSphere.h"
#include "ofxGui.h"
#include "DisplacementSphereMesh.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    ofxLitSphere litSphere;
    ofxLitSphere litSphere02;
    DisplacementSphereMesh displacement;
    ofMaterial material;
    ofLight light;

    ofEasyCam cam;

	ofxPanel gui;

	ofParameter<bool> bmat1;
	ofParameter<bool> bmat2;
	ofParameter<int> mat1;
	ofParameter<int> mat2;
	
	ofParameter<float> mod;

};
