proi3.o: account.o bankelement.o atm.o teller.o bankbranch.o main.o
	g++ account.o bankelement.o atm.o teller.o bankbranch.o main.o -o proi3.o -I
account.o: account.h account.cpp basics.h
	g++ account.cpp -o account.o -I
bankelement.o: bankelement.h bankelement.cpp account.h basics.h
	g++ bankelement.cpp -o bankelement.o -I
atm.o: atm.h atm.cpp bankelement.h basics.h
	g++ atm.cpp -o atm.o -I
teller.o: teller.h teller.cpp bankelement.h basics.h
	g++ teller.cpp -o teller.o -I
bankbranch.o: bankbranch.h bankbranch.cpp teller.h account.h basics.h
	g++ bankbranch.cpp -o bankbranch.o -I
main.o: proi3.cpp bankbranch.h basics.h
	g++ proi3.cpp -o main.o -I
.PHONY: clean
clean:
	rm -f *.o