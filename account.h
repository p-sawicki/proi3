//author: Piotr Sawicki
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "basics.h"
class Account{
    int id;
    ClientType type;
    ClientState state;
    long long balance;

    public:
    Account(int aid = -1);
    int getID() const;
    ClientState getState() const;
    void setState(const ClientState &s);
    ClientType getType() const;
    long long getBalance() const;
    void setBalance(const long long &b);
    Account& operator+=(const long long &b);
    Account& operator-=(const long long &b);
};
#endif