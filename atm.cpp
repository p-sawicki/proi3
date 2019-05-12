class ATM : public BankElement{
    public:
    ATM(int aid = -1) : BankElement(aid, "ATM ") {}
    virtual void getInfo(Account &client){
	    add(client, 3);
    }
    virtual void changePIN(Account &client){
	    add(client, 4);
    }
};

class InputTM : public ATM{
    public:
    InputTM(int iid = -1) : ATM(iid){}
    virtual void withdrawMoney(Account &client){
	    std::cout << "can't do that here!\n"; //TODO: exception
    }
    virtual void depositMoney(Account &client){
	    add(client, 5);
	    deposit(client);
    }
};

class OutputTM : public ATM{
    public:
    OutputTM(int oid = -1) : ATM(oid){}
    virtual void withdrawMoney(Account &client){
	    add(client, 5);
	    withdraw(client);
    }
    virtual void depositMoney(Account &client){
	    std::cout << "can't do that here!\n"; //TODO: exception
    }
};