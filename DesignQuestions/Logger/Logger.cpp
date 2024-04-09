#include "Logger.hpp"
#include<iostream>
#include<fstream>
#include<vector>
#include<yaml-cpp/yaml.h>

using namespace std;

string ILogger::getLevel() {
    return level;
}

void ConsoleLogger::log(string msg) {
    cout << getLevel().c_str() << ": " << msg << endl;
}

void FileLogger::log(string msg) {
    ofstream file(fileName, ios::app);
    file<<getLevel() << ": " << msg << endl;
    file.close();
}

GlobalLogger* GlobalLogger::logger = nullptr;
GlobalLogger* GlobalLogger::getInstance() {
    if(logger == nullptr) {
        logger = new GlobalLogger();
    }
    return logger;
}

void GlobalLogger::init(string configFile) {
    YAML::Node config = YAML::LoadFile(configFile);
    for(auto level:config["LevelToSink"]) {
        string levelName = level["Name"].as<string>();
        string sinkName = level["Sink"].as<string>();

        string fileName = sinkName == "File"? level["FileName"].as<string>(): "";
        ILogger* logger = nullptr;
        levels.push_back(levelName);
        if(sinkName == "Console") {
            logger = new ConsoleLogger(levelName);
        } else {
            logger = new FileLogger(fileName, levelName);
        }
        levelToLoggerMap.push_back(logger);
    }
}

void GlobalLogger::log(string level, string msg) {
    int i;
    for(i=0; i<levels.size(); i++) {
        if(levels[i] == level) {
            break;
        }
    }

    for(i;i>=0; i--) {
        ILogger* logger = levelToLoggerMap[i];
        logger->log(msg);
    }
}

int main() {


    GlobalLogger* logger = GlobalLogger::getInstance();
    logger->init("config.yml");
    logger->log("Info", "This is an info message");
    logger->log("Fatal", "This is a fatal message");
    logger->log("Error", "This is an error message");
    return 0;
}