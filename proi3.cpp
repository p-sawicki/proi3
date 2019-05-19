#include "test.h"
#define DEBUG
int main(int argc, char **argv){
#ifdef DEBUG
    Test t;
    t.test1();
    t.test2();
    t.test3();
    t.test4();
    t.test5();
#endif
	std::stringstream conv;
	for(int i = 1; i < argc; ++i)
		conv << argv[i] << "\n";
	unsigned int clientsAmount = 100;
	unsigned int tellersAmount = 5;
	unsigned int duration = 60;
    if(conv.str()[0] < '0' || conv.str()[0] > '9'){
        std::fstream file;
        std::string fileName;
        conv >> fileName;
        file.open(fileName, std::ios::in);
        file >> clientsAmount >> tellersAmount >> duration;
    }
    else
	    conv >> clientsAmount >> tellersAmount >> duration;
	BankBranch bb(clientsAmount, tellersAmount, duration);
	bool simComplete = false;
	while(!simComplete){
		try{
			simComplete = bb.simulate();
		}
		catch(std::runtime_error err){
            if(err.what()[3] == '1'){
			    std::stringstream message;
			    long long govtLoan = 10'000'000;
			    message << err.what() << "Depositing government bailout of $" << govtLoan - bb.getBalance() <<" into the bank branch. Reopening branch.\n";
			    bb.setBalance(govtLoan);
			    logBoth(message.str());
	    	}
            else 
                std::cout << err.what();
            
        }
    }
}
