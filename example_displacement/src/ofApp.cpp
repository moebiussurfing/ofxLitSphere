#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //ofSetDataPathRoot("../../../../../data/");
    //ofDisableArbTex();
    //ofEnableDepthTest();

    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofSetConeResolution(40, 40, 40);

	//--

    litSphere.setup();
    litSphere.loadAt(2);

    litSphere02.setup();
    litSphere02.loadAt(2);
        
    displacement.setup();
    
    light.setAmbientColor(ofColor(200));
    light.setDiffuseColor(ofColor(200));
    light.setSpecularColor(ofColor(200));
    ofSetSmoothLighting(true);
    
    material.setAmbientColor(ofColor(150));
    material.setDiffuseColor(ofColor(150));
    material.setSpecularColor(ofColor(150));
    material.setEmissiveColor(ofFloatColor(10.0));
    material.setShininess(0.8);

	//--

	gui.setup();
	gui.add(mod.set("mod", 0.8, 0, 2));
	gui.add(bmat1.set("mat1",true));
	gui.add(bmat2.set("mat2",false));
	//gui.add(mat1.set("mat1", 0, 0, 20));
	//gui.add(mat2.set("mat2", 0, 0, 20));
	gui.add(displacement.params);
	gui.setPosition(10, 100);
}

//--------------------------------------------------------------
void ofApp::update(){
	displacement.setMod(mod);
    displacement.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofEnableDepthTest();

    //ofClear(0);
    //ofPushMatrix();
    //ofScale(2, 2);
    //ofBackgroundGradient(ofColor(180), ofColor(70), OF_GRADIENT_CIRCULAR);
    //ofPopMatrix();
	
    cam.begin();
    cam.lookAt(glm::vec3(0,0,0));

	//ofEnableAlphaBlending();
    //ofEnableDepthTest();
    //ofDisableNormalizedTexCoords();
    
    //light.enable();

    // first
	if (bmat1) {
		litSphere.begin();
		displacement.draw();
		litSphere.end();
	}

    // second
	if (bmat2) {
		litSphere02.begin();
		//glPushMatrix();
		ofDrawSphere(0, 0, 180);
		//ofPopMatrix();
		litSphere02.end();
	}

    //light.disable();

    cam.end();

    //ofPopMatrix();

	//ofDisableDepthTest();
    //ofEnableAlphaBlending();

	//-

	ofEnableArbTex();

	ofDisableDepthTest();
	ofSetColor(255);
    ofDrawBitmapString("PRESS SPACE TO CHANGE MATERIAL", ofPoint(20, 20));

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') ofToggleFullscreen();
    if (key == ' ') litSphere.loadNext();
    if (key == ',') litSphere.loadPrevious();
    if (key == ' ') ofLogVerbose(ofToString(litSphere.getCurrentIndex()) + " " + ofToString(litSphere02.getCurrentIndex()) + " " + ofToString(ofGetMouseY()));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
