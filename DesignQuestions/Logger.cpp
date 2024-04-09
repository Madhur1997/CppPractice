#include<iostream>
#include<fstream>
#include<vector>
#include<yaml-cpp/yaml.h>

using namespace std;

/* Requirements:
1. Levels should be configurable.
2. Sink for each level should be configurablel.
3. For each log msg of level A, it should also log msgs to all the lower level sinks.
*/

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
        cout << getLevel().c_str() << ": " << msg << endl;
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
        file<< getLevel() << ": " << msg << endl;
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

    void init(string configFile) {
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

    void log(string level, string msg) {
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
};

GlobalLogger* GlobalLogger::logger = nullptr;

int main() {


    GlobalLogger* logger = GlobalLogger::getInstance();
    logger->init("config.yml");
    logger->log("Info", "This is an info message");
    logger->log("Fatal", "This is a fatal message");
    logger->log("Error", "This is an error message");
    return 0;
}