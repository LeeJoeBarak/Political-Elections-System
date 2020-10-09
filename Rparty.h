
#ifndef R_H_
#define R_H_
#include <string>
#include "Party.h"
using namespace std;

class Rparty : public Party
{

public:
	//param constructor
	Rparty(string name);
	virtual ~Rparty();

	virtual bool registerDemocraticPolitician(Politician* demicratic_politician) { return false; }//Input: Observer
	virtual bool registerRepublicanPolitician(Politician* republican_politician) { this->m_vecMyPoliticians.push_back(republican_politician); return true; }
	void printAllParty();

	



};

#endif /* R_H_ */
