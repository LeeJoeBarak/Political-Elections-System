#ifndef RANDL_H_
#define RANDL_H_
#include<iostream>
#include<string>
#include "Politician.h"
using namespace std;


class RandL: public Politician
{
public:
	RandL(string firstName, string lastName, int ID, int strength);
	void printPolitician();
	virtual ~RandL();
	virtual bool RegisterToParty(Party* ptr_party);
	virtual int getPoliticianPower() { return this->m_iPower; };
	bool canBeLeader() { return true; }

};
#endif /* RANDL_H_ */

