#include "account.h"
class Account{
    int id;
    ClientType type;
    ClientState state;
    long long balance;

    public:
    Account(int aid = -1) : id(aid), state(ClientState::notBusy){
	    std::uniform_int_distribution<unsigned int> typeDistribution(0, 1);
	    std::uniform_int_distribution<long long> balanceDistribution(0, 10000);
	    typeDistribution(gen()) ? type = ClientType::individual : type = ClientType::business;
	    balance = balanceDistribution(gen());
	    if(type == ClientType::business)
		    balance *= 1000;
    }
    int getID() const{
	    return id;
    }
    ClientState getState() const{
	    return state;
    }
    void setState(const ClientState &s){
	    state = s;
    }
    ClientType getType() const{
	    return type;
    }
    long long getBalance() const{
	    return balance;
    }
    void setBalance(const long long &b){
	    balance = b;
    }
};