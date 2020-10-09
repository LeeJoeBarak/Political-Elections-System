#ifndef DANDL_H_
#define DANDL_H_
#include <iostream>
#include<string>
#include "Politician.h"
using namespace std;

class DandL : public Politician
{
public:
	DandL(string firstName, string lastName, int ID, int strength);
	void printPolitician();
	virtual ~DandL();
	virtual bool RegisterToParty(Party* ptr_party);
	virtual int getPoliticianPower() { return this->m_iPower; }
	bool canBeLeader() { return true; }

};


#endif /* DANDL_H_ */