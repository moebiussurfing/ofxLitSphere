#pragma once

#include "ofMain.h"

//#define USE_FILE_BROWSER
#ifdef USE_FILE_BROWSER
#include "ofxImGui.h"
#endif

class ofxLitSphere {
    
public:
    
    ofImage texture;
    
    //--------------------------------------------------------------
    void setup();
    
    void loadAt(int number);
    
    void loadNext();
    
    void loadPrevious();
    
    //--------------------------------------------------------------
    void update();
	void draw();
    
    void begin();
    
    void end();
    
    void reload();
    
    int getCurrent();

	string pathGlobal = "ofxLitSphere";
	string pathFull;

    string matName;
    string getName()
    {
		pathFull = pathGlobal + "/" + "MatCapZBrush/Lib/";
		auto _names = ofSplitString(matName, pathFull);
		cout << "_names[1]: " << _names[1] << endl;
		return _names[1];
        //return matName;
    } 
	string getPath()
    {
		pathFull = pathGlobal + "/" + "MatCapZBrush/Lib/";
        return pathFull;
    }

protected:
    ofShader shader;
    ofDirectory dir;
    int current;

#ifdef USE_FILE_BROWSER

	//browser
public:
	void dirRefresh();

public:
	string mapCapName;
	
	string inputPath;
	bool bShowGuiBroser = false;
	bool bShowBrowser = true;
	void setVisibleGuiBrowser(bool b) {
		bShowGuiBroser = b;
	}
	ofTexture textureSource;
	GLuint textureSourceID;

private:

	void setupGuiBroser();
	void updateGuiBroser();
	void drawGuiBroser();
	void drawGuiBrowser(int x, int y, int w, int h);
	ofxImGui::Gui guiBrowser;
	//ofxImGui::Gui gui;
	ofImage imgMain;
	//string inputPath;
	string imgDescr = "";
	vector<string> imgNamesForListBox;
	stringstream tempStrStream;
	int indexImgFile = -1;
	int prevIndexImgFile = -1;

	string inputFilename;

	ofPixels pixelsButtonSource;
	GLuint pixelsButtonID;

	ofImage imageButtonSource;
	GLuint imageButtonID;

	void keyPressed(int key);
	#endif

};
