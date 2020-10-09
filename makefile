PoliticalSys: main.o PoliticalSys.o PoliticalSysDefs.o \
 Politician.o Party.o RandL.o RandS.o DandL.o DandS.o Rparty.o Dparty.o 
	g++ main.o PoliticalSys.o PoliticalSysDefs.o Politician.o Party.o RandL.o RandS.o DandL.o DandS.o Rparty.o Dparty.o -o run 

DandL.o: DandL.cpp DandL.h Politician.h Party.h
	 g++ -c DandL.cpp

DandS.o: DandS.cpp DandS.h Politician.h Party.h
	g++ -c DandS.cpp

Dparty.o: Dparty.cpp Dparty.h Party.h Politician.h
	g++ -c Dparty.cpp

main.o: main.cpp PoliticalSys.h PoliticalSysDefs.h Politician.h Party.h RandL.h RandS.h DandL.h DandS.h Rparty.h Dparty.h myExceptions.h 
	g++ -c main.cpp

Party.o: Party.cpp Party.h Politician.h
	g++ -c Party.cpp

PoliticalSysDefs.o: PoliticalSysDefs.cpp PoliticalSysDefs.h
	g++ -c PoliticalSysDefs.cpp

Politician.o: Politician.cpp Politician.h Party.h
	g++ -c Politician.cpp

RandL.o: RandL.cpp RandL.h Politician.h Party.h
	g++ -c RandL.cpp

RandS.o: RandS.cpp RandS.h Politician.h Party.h
	g++ -c RandS.cpp

Rparty.o: Rparty.cpp Rparty.h Party.h Politician.h
	g++ -c Rparty.cpp

PoliticalSys.o: PoliticalSys.cpp PoliticalSys.h PoliticalSysDefs.h \
 Politician.h Party.h RandL.h RandS.h DandL.h DandS.h Rparty.h Dparty.h \
 myExceptions.h
	g++ -c PoliticalSys.cpp

clean: 
	rm -f *.o run	
