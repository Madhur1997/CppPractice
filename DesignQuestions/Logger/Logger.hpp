#include<iostream>
#include<vector>

using namespace std;

/* Requirements:
1. Levels should be configurable.
2. Sink for each level should be configurablel.
3. For each log msg of level A, it should also log msgs to all the lower level sinks.
*/

class ILogger {
    string level;
public:
    ILogger(string level) : level(level) {}
    string getLevel();
    virtual void log(string msg) = 0;
};

class ConsoleLogger : public ILogger {
    ConsoleLogger(string level) : ILogger(level) {}
    ConsoleLogger(const ConsoleLogger&) = delete;
public:

    void log(string msg);

    friend class GlobalLogger;
};

class FileLogger : public ILogger {
    string fileName;

    FileLogger(string fileName, string level) : fileName(fileName), ILogger(level) {}
    FileLogger(const FileLogger& cl) = delete;

public:
    void log(string msg);

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
    static GlobalLogger* getInstance();

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

    void init(string configFile);

    void log(string level, string msg);
};
