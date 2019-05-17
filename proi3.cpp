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
	bool simComplete = false;
	while(!simComplete){
		try{
			simComplete = bb.simulate();
		}
		catch(std::runtime_error err){
			std::stringstream message;
			long long govtLoan = 10'000'000;
			message << err.what() << "Depositing government bailout of $" << govtLoan - bb.getBalance() <<" into the bank branch. Reopening branch.\n";
			bb.setBalance(govtLoan);
			std::cout << message.str();
			file() << message.str();
		}
	}
}
