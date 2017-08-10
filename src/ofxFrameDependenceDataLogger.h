//
//  ofxFrameDependenceDataLogger.h
//  datalog_test
//
//  Created by asai yuta on 2017/08/10.
//
//

#ifndef ofxFrameDependenceDataLogger_h
#define ofxFrameDependenceDataLogger_h
#include "ofMain.h"
#include <iostream>
#include <fstream>
enum class OFXFDDL{
    WRITE = 0,
    REED = 1,
    NOTHING = 2,
};

class ofxFrameDependenceDataLogger{
public:
    ofxFrameDependenceDataLogger()
    : mode(OFXFDDL::NOTHING)
    , modeNum(2)
    {
        repetitionFunction[0] = &ofxFrameDependenceDataLogger::updateWrite;
        repetitionFunction[1] = &ofxFrameDependenceDataLogger::updateReed;
        repetitionFunction[2] = &ofxFrameDependenceDataLogger::updateNothing;
    }
    
    void setFilePath(const std::string& path, const bool makeFull = true){
        setTargetFilePath(path, makeFull);
    }
    
    void setMode(OFXFDDL m){
        if(mode == m){
        }else{
            mode = m;
            changeMode();
        }
    }
    
    void update(){
        (this->*repetitionFunction[modeNum])();
    }
    
    template<typename T>
    void setArg(T& t){
        argHolder.emplace_back(t);
    }

    
private:
    void updateWrite(){
        writeCurrentToFile();
    }
    
    void updateReed(){
        readCurrentToFile();
        if(isAutoPlay) ++currentFrame;
    }
    
    void updateNothing(){
    }
    
    void (ofxFrameDependenceDataLogger::*repetitionFunction[3])();
    
    void changeMode(){
        switch (mode) {
            case OFXFDDL::WRITE:
                closeFile();
                if(openWriteFile()){
                    ofLogNotice("ofxFrameDependenceDataLogger") << "chenge mode write";
                    modeNum = 0;
                }else{
                    ofLogError("ofxFrameDependenceDataLogger") << "file cant opened";
                    mode = OFXFDDL::NOTHING;
                    changeMode();
                }
                break;
                
            case OFXFDDL::REED:
                closeFile();
                if(openReadFile()){
                    setEndPosition();
                    ofLogNotice("ofxFrameDependenceDataLogger") << "chenge mode read";
                    modeNum = 1;
                }else{
                    ofLogError("ofxFrameDependenceDataLogger") << "file cant opened";
                    mode = OFXFDDL::NOTHING;
                    changeMode();
                }
                break;
                
            case OFXFDDL::NOTHING:
                    ofLogNotice("ofxFrameDependenceDataLogger") << "chenge mode nothing";
                    modeNum = 2;
                break;
                
            default:
                break;
        }
    
    }
    
    void closeFile(){
        if(fout.is_open()){
            fout.close();
        }
        
        if(fin.is_open()){
            fin.close();
        }
    }
    
    const bool isEnd(){
        return (dataEndPosition < ((currentFrame + 1) * ofxFDDLArgHolder::totalSize()));
    }
    
    const bool openWriteFile(){

        fout.open(targetFilePath, std::ios::binary | std::ios::trunc);

        return fout.is_open();
    }
    
    const bool openReadFile(){
        fin.open(targetFilePath, std::ios::in | std::ios::binary);
        return fin.is_open();
    }
    
    void writeCurrentToFile(){
        for(auto& e : argHolder){
            fout.write(e.place, e.size);
        }
    }
    
    void readCurrentToFile(){
        if(isEnd()){
            if(isRepeat){
                currentFrame = 0;
                closeFile();
                openReadFile();
            }else{
                mode = OFXFDDL::NOTHING;
                changeMode();
            }
        }
        fin.seekg(currentFrame * ofxFDDLArgHolder::totalSize(),std::ios::beg);
        for(auto& e : argHolder){
            fin.read(e.place, e.size);
            fin.seekg(e.size, std::ios::cur);
        }
    }

    void setTargetFilePath(const std::string filePath, const bool isUseSetPath = true){
        if(isUseSetPath){
            targetFilePath = ofToDataPath(filePath,true);
        }else{
            targetFilePath = filePath;
        }
    }
    
    void setEndPosition(){
        fin.seekg(0, std::fstream::end);
        dataEndPosition = (uint64_t)fin.tellg();
        fin.seekg(0, std::ios::beg);
        std::cout << dataEndPosition;
    }
    
    
    
    struct ofxFDDLArgHolder{
        template<typename T>
        ofxFDDLArgHolder(T& arg)
        : place(reinterpret_cast<char*>(&arg))
        , size(sizeof(T))
        {
            totalSize() += size;
        }
        char *place;
        const std::size_t size;
        static std::size_t& totalSize(){
            static std::size_t _t = 0;
            return _t;
        };
    };
    
    bool isRepeat{true};
    bool isAutoPlay{true};
    
    std::vector<ofxFDDLArgHolder> argHolder;
    std::string targetFilePath;
    uint64_t currentFrame;
    uint64_t dataEndPosition;

    ofstream fout;
    ifstream fin;

    OFXFDDL mode;
    uint8_t modeNum;

};




#endif /* ofxFrameDependenceDataLogger_h */
