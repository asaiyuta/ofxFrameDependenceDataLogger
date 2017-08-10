#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    logger.setArg(objs);
    logger.setFilePath("example.dat");
    mode = "NOTHING";
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(auto& e : objs){
        e.update();
    }
    logger.update();
    ofSetWindowTitle(std::to_string(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofNoFill();
    for(auto& e : objs){
        e.draw();
    }
    cam.end();
    ofDrawBitmapString(mode, 10, 20);
    ofDrawBitmapString(config,10,40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        for(auto& e : objs){
            e.reset();
        }
    }
    
    if(key == ' '){
        logger.setMode(OFXFDDL::WRITE);
        mode = "WRITE";
    }else if(key == OF_KEY_RETURN){
        logger.setMode(OFXFDDL::REED);
        mode = "REED";
    }else if(key == 'n'){
        logger.setMode(OFXFDDL::NOTHING);
        mode = "NOTHING";
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
