#pragma once

#include "ofMain.h"
#include "ofxFrameDependenceDataLogger.h"


struct TestObj{
    TestObj(){
        target = ofVec3f(ofRandom(-3000,3000),ofRandom(-3000,3000),ofRandom(-3000,3000));
        size = ofRandom(3,20);
    }
    
    void reset(){
        pos = ofVec3f(0,0,0);
        target = ofVec3f(ofRandom(-3000,3000),ofRandom(-3000,3000),ofRandom(-3000,3000));
        size = ofRandom(3,20);
    }
    
    ofVec3f target;
    ofVec3f pos;
    float size;
    void update(){
        pos += (target - pos) * 0.001;
    }
    void draw(){
        ofDrawSphere(pos, size);
    }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        std::array<TestObj,10> objs;
        ofxFrameDependenceDataLogger logger;
        ofEasyCam cam;
        std::string config = " SPACE key  =  logging \n RETURN key  =  play \n n key  =  mode nothing \n r key  =  esetMotin";
        std::string mode;
};
