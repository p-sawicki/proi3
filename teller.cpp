#include "teller.h"
Teller::Teller(int tid) : BankElement(tid, "Teller ") {}
void Teller::getInfo(Account &client){
void Teller::changePIN(Account &client){
}
void Teller::withdrawMoney(Account &client){
void Teller::depositMoney(Account &client){
void Teller::takeLoan(Account &client){
}
void Teller::evalLoan(long long &branchBalance){
void Teller::simulate(long long &branchBalance){
