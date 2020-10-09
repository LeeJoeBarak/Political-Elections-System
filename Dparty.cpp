
#include <string>
#include "Dparty.h"
#include "Party.h"
using namespace std;



Dparty::Dparty(string name) : Party(name) {}

void Dparty::printAllParty() {
/*
	Party's Print function implementation:

	cout << "Party: " << this->m_sPartyName << ", chairman:" << this->m_sChairman_FirstName
	<< ", Size:" << this->m_vecMyPoliticians.size() << endl;

	Plus, for all politicians in party: \t + PrintPolitician
*/

	cout << "Democrat ";
	this->Party::printAllParty();

}//printAllParty



Dparty::~Dparty() {}