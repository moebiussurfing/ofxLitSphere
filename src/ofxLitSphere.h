#pragma once

#include "ofMain.h"

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
    
    void begin();
    
    void end();
    
    void reload();
    
    int getCurrent();

    string matName;
    string getName()
    {
        return matName;
    }

protected:
    ofShader shader;
    ofDirectory dir;
    int current;
};
