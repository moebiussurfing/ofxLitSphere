#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "ofxLitSphere.h"
#include "DisplacementSphereMesh.h"

#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void mousePressed(int x, int y, int button);
	void keyPressed(int key);
	void keyReleased(int key);

	ofEasyCam cam;
	bool bEnableMouseCam;
	bool bDrawFloor;
	bool bHelp;

	ofxLitSphere litSphere;

	ofParameter<int> indexScene{ "SCENE", 0, 0, 2 };

	//model
	ofxAssimpModelLoader model;
	//mesh
	//ofMesh meshForm;

	//--

	//displacement example
	void setupDisplacement();
	void updateDisplacement();

	DisplacementSphereMesh displacement;
	ofMaterial material;
	ofLight light;

	//params
	ofParameterGroup params_Displacement;
	ofParameter<bool> bmat1;
	ofParameter<bool> bmat2;
	ofParameter<int> mat1;
	ofParameter<int> mat2;
	ofParameter<bool> bLights;
	ofParameter<float> mod;

	ofxPanel gui;

	//--

};
