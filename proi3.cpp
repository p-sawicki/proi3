#include "bankbranch.h"
int main(int argc, char **argv){
	std::stringstream conv;
	for(int i = 1; i < argc; ++i)
		conv << argv[i] << "\n";
	unsigned int clientsAmount = 100;
	unsigned int tellersAmount = 5;
	unsigned int duration = 60;
	conv >> clientsAmount >> tellersAmount >> duration;
	BankBranch bb(clientsAmount, tellersAmount, duration);
	bb.simulate();
}
