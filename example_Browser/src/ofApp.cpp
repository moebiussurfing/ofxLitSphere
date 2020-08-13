#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	//ofSetDataPathRoot("../../../../../data/");//put data outisde the project to share data folder between all example projects

	ofDisableArbTex();
	ofEnableDepthTest();
	ofSetVerticalSync(true);
	litSphere.setup();

	bHelp = false;

	//-

	//scene

	bDrawFloor = true;

	//press return to switch scene
	//0:prims 1:displacement 2:models
	indexScene = 1;

	//mesh
	setupDisplacement();

	//prims
	ofSetConeResolution(40, 40, 40);

	//models

	//object
	model.loadModel("obj_free_base_female_head.OBJ", 10);
	//model.loadModel("head.obj", 10);
	//model.loadModel("young_boy_head_obj.obj", 10);

	////mesh
	//meshForm.load("basic_form.ply");
	////meshForm.load("head.obj");//not loading
}

//--------------------------------------------------------------
void ofApp::update() {
	//workaround to bug
	if (ofGetFrameNum() == 5) {
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}

	//#ifdef USE_FILE_BROWSER
	//	litSphere.update();
	//#endif

	updateDisplacement();
}

//--------------------------------------------------------------
void ofApp::draw() {
	//background
	ofBackgroundGradient(ofColor(40, 40, 40), ofColor(0, 0, 0), OF_GRADIENT_CIRCULAR);

	//-

	ofEnableDepthTest();

	cam.begin();
	{
		//test lights
		//ofLight light; // also works with ofNode
		//light.setPosition(glm::vec3(4, 2.8, 5));
		//light.lookAt(glm::vec3(0, 0, 0));

		//draw a grid on the floor
		if (bDrawFloor) {
			ofPushMatrix();
			ofPushStyle();
			ofTranslate(0, -250, 0);
			ofRotate(90, 0, 0, -1);
			ofSetColor(96, 128);
			ofDrawGridPlane(500, 1, false);
			ofSetColor(64, 128);
			ofDrawGridPlane(250, 2, false);
			ofPopStyle();
			ofPopMatrix();
		}

		//--

		litSphere.begin();
		{
			//draw your scene here!...

			//--

			float speedRot = 0.25f;
			ofRotateY(ofGetFrameNum() * speedRot);


			//prims
			if (indexScene == 0) {
				ofPushMatrix();

				//ofTranslate(0, 300, 0);
				ofRotateX(ofGetFrameNum() * speedRot);
				ofDrawCone(100, 140);
				ofDrawSphere(200, 0, 70);
				ofDrawBox(-200, 0, 0, 80);

				ofPopMatrix();
			}

			//displacement
			else if (indexScene == 1) {
				//if (bLights) light.enable();

				//first
				if (bmat1) {
					displacement.draw();
				}
				//second
				if (bmat2) {
					ofDrawSphere(0, 0, 180);
				}

				//if (bLights) light.disable();
			}

			//models
			else if (indexScene == 2) {

				ofPushMatrix();

				//mesh
				//float scale = 250;
				//ofScale(scale, scale, scale);
				//ofRotateYDeg(75);
				//meshForm.draw();

				//object
				float scale = 0.5f;
				//ofTranslate(0, -250, 0);
				ofScale(scale, scale, scale);
				ofRotateXDeg(180);
				//ofRotateYDeg(180);
				model.drawFaces();

				ofPopMatrix();
			}
		}
		litSphere.end();

		//--
	}
	cam.end();

	ofDisableDepthTest();

	//--

	//gui

#ifdef USE_FILE_BROWSER
	litSphere.drawGui();
#endif

	if (bHelp) {
		string str = "";
		str += "KEY G: SHOW GUI\n";
		str += "KEY S: SWITCH SCENE\n";
		str += "KEY RETURN: CHANGE SCENE PRIMS/MODEL\n";
		str += "KEY CONTROL: ENABLE MOUSE CAMERA\n";
		if (!litSphere.isVisibleGui()) {
			str += "KEY SPACE: NEXT MatCap FILE " + litSphere.getName();
		}
		ofDrawBitmapStringHighlight(str, ofPoint(300, 20));
	}

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	//if (!litSphere.isVisibleGui()) litSphere.loadNext();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	litSphere.keyPressed(key);

	//-

	////switch scene
	//if (key == 's' || key == 'S') {
	//	indexScene++;
	//	if (indexScene == 3) indexScene = 0;
	//}

	//press control to move camera
	if (key == OF_KEY_CONTROL) {
		bEnableMouseCam = true;
		cam.enableMouseInput();
	}

	////load next cap
	//else if (key == ' ') litSphere.loadNext();

	//enable draw floor
	else if (key == 'f') bDrawFloor = !bDrawFloor;

	//return to change scene
	else if (key == OF_KEY_RETURN) {
		if (indexScene != 2) indexScene++;
		else indexScene = 0;
	}

	//hide gui to enable disable gui and browse by keys and mouse clicks
	else if (key == 'g' || key == 'G') litSphere.setToggleVisibleGui();

	//hide help
	else if (key == 'h' || key == 'H') bHelp = !bHelp;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	//press control to move camera
	if (key == OF_KEY_CONTROL) {
		bEnableMouseCam = false;
		cam.disableMouseInput();
	}
}

//--------------------------------------------------------------
void ofApp::setupDisplacement() {
	ofSetConeResolution(40, 40, 40);

	//--

	displacement.setup();

	//light.setAmbientColor(ofColor(200));
	//light.setDiffuseColor(ofColor(200));
	//light.setSpecularColor(ofColor(200));
	//ofSetSmoothLighting(true);

	//material.setAmbientColor(ofColor(150));
	//material.setDiffuseColor(ofColor(150));
	//material.setSpecularColor(ofColor(150));
	//material.setEmissiveColor(ofFloatColor(10.0));
	//material.setShininess(0.8);

	//--

	params_Displacement.setName("DISPLACEMENT");
	params_Displacement.add(mod.set("MODULATE", 1, 0, 2));
	params_Displacement.add(bmat1.set("MAT 1", true));
	params_Displacement.add(bmat2.set("MAT 2", false));
	//params_Displacement.add(mat1.set("MAT 1", 0, 0, 20));
	//params_Displacement.add(mat2.set("MAT 2", 0, 0, 20));
	//params_Displacement.add(bLights.set("LIGHTS", false));
	params_Displacement.add(displacement.params);

	gui.setup();
	gui.add(indexScene);
	gui.add(params_Displacement);
	gui.setPosition(20, 500);
}

//--------------------------------------------------------------
void ofApp::updateDisplacement() {
	displacement.setMod(mod);
	displacement.update();
}
