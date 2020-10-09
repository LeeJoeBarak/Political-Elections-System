#ifndef RANDS_H_
#define RANDS_H_
#include<string>
#include <iostream>
#include "Politician.h"
using namespace std;

class RandS : public Politician
{
public:
	RandS(string firstName, string lastName, int ID, int strength);
	void printPolitician();
	virtual ~RandS();
	virtual bool RegisterToParty(Party* ptr_party);
	virtual int getPoliticianPower() { return (this->m_iPower * 2); }
	bool canBeLeader() { return false;}

};

#endif /* RANDS_H_ */


