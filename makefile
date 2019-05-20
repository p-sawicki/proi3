proi3: account.o bankelement.o atm.o teller.o bankbranch.o test.o main.o
	g++ account.o bankelement.o atm.o teller.o bankbranch.o test.o main.o -o proi3.o -I -Wall
account.o: account.h account.cpp basics.h
	g++ -c account.cpp -o account.o -I -Wall
bankelement.o: bankelement.h bankelementinterface.h bankelement.cpp account.h basics.h
	g++ -c bankelement.cpp -o bankelement.o -I -Wall
atm.o: atm.h atm.cpp bankelement.h 
	g++ -c atm.cpp -o atm.o -I -Wall
teller.o: teller.h teller.cpp bankelement.h
	g++ -c teller.cpp -o teller.o -I -Wall
bankbranch.o: bankbranch.h bankbranch.cpp teller.h atm.h account.h
	g++ -c bankbranch.cpp -o bankbranch.o -I -Wall	
test.o: test.h test.cpp bankbranch.h 
	g++ -c test.cpp -o test.o -I -Wall
main.o: proi3.cpp test.h 
	g++ -c proi3.cpp -o main.o -I -Wall
.PHONY: clean
clean:
	rm -f *.o log.txt
