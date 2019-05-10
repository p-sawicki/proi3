#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

class BankBranch{
    std::vector<Account> clients;
    std::vector<Teller> tellers;
    InputTM itm;
    OutputTM otm;

    public:
    BankBranch(const unsigned int &clientsAmount, const unsigned int &tellersAmount){
        clients = std::vector<Account>(clientsAmount);
        tellers = std::vector<Tellers>(tellersAmount);
        unsigned int max = clientsAmount > tellersAmount ? clientsAmount : tellersAmount;
        unsigned int i = 0;
        for(; i < max; ++i){
            if(i < clientsAmount)
                clients.push_back(Client(i));
            if(i < tellersAmount)
                tellers.push_back(Client(i));
        }
        itm(i++);
        otm(i);
    }
}

class BankElement{
    unsigned int id;
    std::queue<std::tuple<Account, unsigned int>> queue;
    unsigned int timeRemaining;

    public:
    virtual void getInfo(const Account &client) = 0;
};

class Teller : public BankElement{
    public:
    Teller(const unsigned int &tid) : id(tid) {}
    virtual void getInfo(const Account &client){
        queue.push({client, 5});
        std::cout << "Client " << client.id << "joins queue to teller " << id << std::endl;
    }
};

class ATM : public BankElement{
    public:
    ATM(const unsigned int &aid) : id(aid) {}
    virtual void getInfo(const Account &client){
        queue.push({client, 3});
        std::cout << "Client " << client.id << "joins queue to ATM " << id << std::endl;
    }
};

class InputTM : public ATM{
    public:
    InputTM(const unsigned int &iid) : id(iid) {}
};

class OutputTM : public ATM{
    public:
    OutputTM(const unsigned int &oid) : id(oid) {}
};

enum ClientType {individual, business};
class Account{
    unsigned int id;
    ClientType type;
    long long balance;

    public:
    Account(const unsigned int &aid) : id(aid){
        type = ClienType::individual; //todo: randomize
        balance = 0; //todo: randomize
    }
};

int main(){
    BankBranch bb(5, 5);
    bb.tellers[0].getInfo(bb.clients[0]);
}