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
enum ClientType {individual, business};
enum ClientState {notBusy, busy, loanEval};
inline std::mt19937& gen(){
	static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 generator(seed);
	return generator;
}
#endif
