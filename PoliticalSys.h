#ifndef POLITICALSYS_H_
#define POLITICALSYS_H_

#include "PoliticalSysDefs.h"
#include "Politician.h"
#include "Party.h"
#include "RandL.h"
#include "RandS.h"
#include "DandL.h"
#include "DandS.h"
#include "Rparty.h"
#include "Dparty.h"
#include "myExceptions.h"


using namespace std;

class Party;
class Politician;


class PoliticalSys
{

	vector<Politician*> m_vecPoliticians;
	vector<Party*> m_vecParties;
	multimap<Key_biggest, Party*, KeyComparator> m_mmBiggestParty;
//	int m_iNumOfRepPartys;
//	int m_iNumOfDemoPartys;

public:

	PoliticalSys() {}
	PoliticalSys(char* link);
	void removePolitician();
	void removeParty();
	void elections();
	void addPolitician();
	void addParty();
	void printPoliticians();
	void printParties();
	void BiggestParty();
	virtual ~PoliticalSys();

    void checkIfChairmanAndUpdate(Politician* politician, Party* myFormerParty);
    void findPartyForPoliticians(vector<Politician *> poli_vec); //specific helper for removeParty
    void initOrTransferParty(vector<Politician*>& poli_vec, Party* new_party);
};



#endif /* POLITICALSYS_H_ */


