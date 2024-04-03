#include<iostream>
#include<fstream>
#include<vector>
#include <yaml-cpp/yaml>

using namespace std;

class ILogger {
    string level;
public:
    ILogger(string level) : level(level) {

    }
    string getLevel() {
        return level;
    }
    virtual void log(string msg) = 0;
};

class ConsoleLogger : public ILogger {
    ConsoleLogger(string level) : ILogger(level) {}
    ConsoleLogger(const ConsoleLogger&) = delete;
public:

    void log(string msg) {
        cout << getLevel() << " " << msg << endl;
    }

    friend class GlobalLogger;
};

class FileLogger : public ILogger {
    string fileName;

    FileLogger(string fileName, string level) : fileName(fileName), ILogger(level) {}
    FileLogger(const FileLogger& cl) = delete;

public:
    void log(string msg) {
        ofstream file(fileName, ios::app);
        file<< getLevel() << " " << msg << endl;
        file.close();
    }

    friend class GlobalLogger;
};

class GlobalLogger {
    static GlobalLogger* logger;
    vector<ILogger*> levelToLoggerMap;
    vector<string> levels;

    // CTR
    GlobalLogger () {}

    // Delete Copy CTR
    GlobalLogger(const GlobalLogger&) = delete;

public:
    static GlobalLogger* getInstance() {
        if(logger == nullptr) {
            logger = new GlobalLogger();
        }
        return logger;
    }

    /*
    YAML file has the format
    LevelToSink:
      -Name: Info
       Sink: File
       FileName: Info.log
      -Name: Error
       Sink: Console
      -Name: Fatal
       Sink: File
       FileName: Fatal.log
    */
    void init(YAML::Node config) {
        for(auto level : config["LevelToSink"]) {
            string name = level["Name"].as<string>();
            string sink = level["Sink"].as<string>();
            string fileName = level["FileName"].as<string>();
            ILogger* logger = nullptr;
            if(sink == "Console") {
                logger = new ConsoleLogger(name);
            } else if(sink == "File") {
                logger = new FileLogger(fileName, name);
            }
            levelToLoggerMap.push_back(logger);
            levels.push_back(name);
        }    
    }

    void log(string msg, string level) {
        for(int i=0; i<levels.size(); i++) {
            if(levels[i] == level) {
                break;
            }
        }

        for(;i>=0; i--) {
            ILogger* logger = levelToLoggerMap[i];
            logger->log(msg);
        }
    }

};

int main() {

    return 0;
}