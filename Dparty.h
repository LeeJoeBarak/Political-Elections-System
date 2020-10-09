
#ifndef D_H_
#define D_H_
#include <string>
#include "Party.h"
using namespace std;




class Dparty: public Party
{
public:
	//param constructor
	Dparty(string name);
	virtual ~Dparty();

	virtual bool registerDemocraticPolitician(Politician* democratic_politician) { this->m_vecMyPoliticians.push_back(democratic_politician); return true; }
	virtual bool registerRepublicanPolitician(Politician* republican_politician) { return false; }//Input: Observer
	void printAllParty();
	

};

#endif /* D_H_ */
