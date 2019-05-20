//author: Piotr Sawicki
#include "test.h"
void Test::accountMethodsTest(){
    Account acc(10);
    assert(acc.getID() == 10);
    assert(acc.getState() == ClientState::notBusy);
    acc.setState(ClientState::loanEval);
    assert(acc.getState() == ClientState::loanEval);
    assert(acc.getType() == ClientType::individual || acc.getType() == ClientType::business);
    assert(acc.getBalance() > 0 && acc.getBalance() < 10'000'001);
    acc.setBalance(10'000);
    assert(acc.getBalance() == 10'000);
    acc -= 100'000;
    assert(acc.getBalance() == -90'000);
    acc += 1;
    assert(acc.getBalance() == -89'999);
}
void Test::logicErrorCatchTestITM(){
    InputTM itm;
    Account acc(10);
    long long balance = 0;
    bool caught = false;
    try{
        itm.withdrawMoney(acc, balance);
    }
    catch(std::logic_error err){
        caught = true;
    }
    assert(caught);
}
void Test::logicErrorCatchTestOTM(){
    OutputTM otm;
    Account acc(10);
    long long balance = 0;
    bool caught = false;
    try{
        otm.depositMoney(acc, balance);
    }
    catch(std::logic_error err){
        caught = true;
    }
    assert(caught);
}
void Test::tellerMethodsTest(){
    Teller tel(15);
    assert(tel.getID() == 15);
    assert(tel.getName() == std::string("Teller "));
    assert(tel.getQueueFront() == -1);
    assert(tel.getQueueSize() == 0);
    assert(tel.getTimeRemaining() == 0);
    Account acc(12);
    tel.takeLoan(acc);
    assert(acc.getState() == ClientState::loanEval);
    assert(tel.getQueueFront() == 12);
    assert(tel.getQueueSize() == 1);
    assert(tel.getTimeRemaining() == 15 || tel.getTimeRemaining() == 20);
}
void Test::branchBankruptExceptionCatchTest(){
    BankBranch bb(1, 10, 60);
    assert(bb.getBalance() >= 10'000'000);
    bb.setBalance(-20'000'000);
    assert(bb.getBalance() == -20'000'000);
    bool caught = false;
    try{
        bb.simulate();
    }
    catch(std::runtime_error err){
        caught = true;
    }
    assert(caught);
}
