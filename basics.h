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
inline std::mt19937& gen(){
	static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 generator(seed);
	return generator;
}
inline std::fstream& file(){
    static std::fstream stream;
    if(!stream.is_open())
        stream.open("log.txt", std::ios::out | std::ios::trunc);
    if(!stream){
        std::string message("ERR2 - An error with the log file occurred. Try restarting the program.\n");
        std::runtime_error err(message);
        throw err;
    }
    return stream;
}
#endif
