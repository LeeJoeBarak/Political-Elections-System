#ifndef DANDS_H_
#define DANDS_H_
#include <iostream>
#include<string>
#include "Politician.h"
using namespace std;

class DandS: public Politician
{

public:
	DandS(string firstName, string lastName, int ID, int strength);
	void printPolitician();
	virtual ~DandS();
	virtual bool RegisterToParty(Party* ptr_party);
	virtual int getPoliticianPower() { return (this->m_iPower * 2); }
	bool canBeLeader() { return false; }


};

#endif /* DANDS_H_ */

