#ifndef BASICS_H
#define BASICS_H
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <thread>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <limits.h>
enum ClientType {individual, business};
enum ClientState {notBusy, busy, loanEval};
template <class T = std::ostream>
class Logger{
    private:
    T *stream;
    public:
    Logger(T *s) : stream(s) {}
    void open(std::string name){
        stream->open(name, std::ios::out | std::ios::trunc);
    }
    T& getStream() const{
        return *stream;
    }
    void write(std::string message){
        *stream << message;
        if(!*stream){
            std::string message("ERR2 - An error with the log file occurred. Try restarting the program.\n");
            std::runtime_error err(message);
            throw err;
        }
    }
};
inline std::mt19937& gen(){
	static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 generator(seed);
	return generator;
}
inline Logger<std::fstream>& file(){
    static std::fstream stream;
    static Logger<std::fstream> logFile(&stream);
    if(!logFile.getStream().is_open())
        logFile.open("log.txt");
    return logFile;
}
inline Logger<>& console(){
    static Logger<> logConsole(&std::cout);
    return logConsole;
}
inline void logBoth(const std::string &message){
    file().write(message);
    console().write(message);
}
#endif
