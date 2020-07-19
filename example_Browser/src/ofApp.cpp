#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetDataPathRoot("../../../../../data/");//put data outisde the project to share data folder between all example projects

	ofDisableArbTex();
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	litSphere.setup();

	//-

	//scene

	//0:prims or 1:obj : 
	//set manualy by yourself here
	indexScene = 1;

	//0
	ofSetConeResolution(40, 40, 40);

	//1A
	model.loadModel("head.obj", 10);

	////1B
	//meshForm.load("basic_form.ply");
	////meshForm.load("head.obj");//not loading

	//primFloor.set(1000, 1000);
	////primFloor.setPosition(0, -500, 0);
	//primFloor.rotateDeg(90, { 1,0,0 });

	//-

	//cam
	
	//cam.lookAt(glm::vec3(0, 0, 0));
	//cam.setPosition(glm::vec3(0, 2000, 0));
	rView = ofRectangle(ofGetWidth() / 3.f, 0, ofGetWidth() * (2/ 3.f), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
	if (ofGetFrameNum() == 5) {//reset cam bc bug..
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}

	//--

#ifdef USE_FILE_BROWSER
	litSphere.update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofClear(32);
	//ofPushMatrix();
	//ofScale(2, 2);
	//ofBackgroundGradient(ofColor(32), ofColor(0), OF_GRADIENT_CIRCULAR);
	//ofPopMatrix();

	//-

	ofEnableDepthTest();

	cam.begin(rView);
	{
		//test lights
		//ofLight light; // also works with ofNode
		//light.setPosition(glm::vec3(4, 2.8, 5));
		//light.lookAt(glm::vec3(0, 0, 0));

		litSphere.begin();
		{
			//draw your scene here!...

			//--

			if (indexScene == 0) {
				ofPushMatrix();
				{
					//ofTranslate(0, 300, 0);
					ofRotateX(ofGetFrameNum());
					ofDrawCone(100, 140);
					ofDrawSphere(200, 0, 70);
					ofDrawBox(-200, 0, 0, 80);
				}
				ofPopMatrix();
			}

			else if (indexScene == 1) {

				//1B
				////ofTranslate(0, 500);
				//primFloor.draw();

				ofPushMatrix();
				
				//1B
				{
					//float scale = 250;
					//ofScale(scale, scale, scale);
					//ofRotateYDeg(75);
					//meshForm.draw();
				}

				//1A
				{
					float scale = 0.5f;
					ofTranslate(0, -250, 0);
					ofScale(scale, scale, scale);
					ofRotateXDeg(180);
					ofRotateY(ofGetFrameNum());
					//ofRotateYDeg(180);
					// draws all the other file types which are loaded into model.
					model.drawFaces();
				}

				ofPopMatrix();
			}
		}
		litSphere.end();
	}
	cam.end();

	//-

	ofDisableDepthTest();

	//gui browser
#ifdef USE_FILE_BROWSER
	litSphere.drawGui();
#endif

	if (!litSphere.isVisibleGui()) ofDrawBitmapStringHighlight("CLICK TO CHANGE SOURSE", ofPoint(0, -200));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (!litSphere.isVisibleGui()) litSphere.loadNext();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == OF_KEY_CONTROL) {//press control to move camera
		bEnableMouseCam = true;
		cam.enableMouseInput();
	}

	else if (key == ' ') litSphere.loadNext();
	
	//hide gui to enable disable gui and browse by keys and mouse clicks
	else if (key == 'g') litSphere.setToggleVisibleGui();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == OF_KEY_CONTROL) {//press control to move camera
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}
}

