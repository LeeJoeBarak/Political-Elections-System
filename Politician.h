#ifndef POLITICIAN_H_
#define POLITICIAN_H_

#include <iostream>
#include <string>
#include "Party.h"
using namespace std;
class Party;

class Politician
{
	string m_sFirstName;
	string m_sLastName;
	int m_iID;
	Party* m_ptrMyParty; //what is more "correct prog": Party* or Party const* ?
	Politician* m_ptrMyParty_chairman;
protected:
	int m_iPower;

public:
	Politician();
	Politician(string firstName, string lastName, int ID, int strength);
	virtual ~Politician();
	
	virtual bool RegisterToParty(Party* ptr_party) = 0;
	virtual void Update(Politician* new_chairman);	/* don't think it should be pure virtual... test later */
	virtual int getPoliticianPower() = 0;

	virtual bool canBeLeader() = 0;
	virtual void printPolitician() = 0;

	int getId();
	string getFirstName();
    string getChairmanFirstName();
	Party* getmyParty();
    void setMyParty(Party* myParty);

	Politician& operator=(const Politician& other);
	//friend bool operator<( Politician& lhs,  Politician& rhs);

};
#endif /* POLITICIAN_H_ */

