
#include "PoliticalSys.h"
using namespace std;

//ALL "new" STATEMENTS SHOULD BE INSIDE A TRY-CATCH BLOCK

/**  Notice: 1. Politicians can be left without parties so ALWAYS check that politician has party before accessing his/hers party attributes
 *           2. If there are 0 politicians/parties in cases 3 and 4, respectively, PRINT MENU ! (no message)
 *           3. in case 5 (and Primaries() in general) - if there are 0 politicians/parties - PRINT MENU! (no message)
 *              */
PoliticalSys::PoliticalSys(char* link) {

	trimClass trm;
	int falgPoli = 0;
	int falgParty = 0;
	string myvars[6];
	string firstName;
	string lastName;
	string RorD;
	string LorS;
    Party* newParty =NULL;
    Politician* newPolitician =NULL;
	int k;

	std::ifstream file(link);

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
            line =  trm.trim(line, "\r\t\b\n");
			if (falgPoli == 0) {
				//get rid of junk before "POliticians:"
				while (!strstr(line.c_str(), "Politicians:")) {
					continue;
				}
				falgPoli = 1;
				continue;
			}

			if (falgParty == 0 && falgPoli == 1){
				if (strstr(line.c_str(), "Parties:")) {
					falgParty = 1;
					continue;
				}
				else {
                    //string s = line.c_str();
                    string s = line;
                    string delimiter = " ";
                    size_t pos = 0;
                    std::string token;
                    k = 0;
                    while ((pos = s.find(delimiter)) != std::string::npos) {
                        myvars[k] = s.substr(0, pos);
                        //cout << myvars[k] << endl;
                        k++;
                        s.erase(0, pos + delimiter.length());
                    }
                    myvars[k] = s.substr(0, pos);

                    stringstream strValue;
                    strValue << myvars[2];

                    //int intId = stoi(myvars[2]);
                    int intId;
                    strValue >> intId;

                    stringstream strValue2;
                    strValue2 << myvars[3];

                    //int intPower = stoi(myvars[3]);
                    int intPower;
                    strValue2 >> intPower;
                    try{
                    /** Create New Politician (don't forget to call delete at the end....)*/
                    if (myvars[5] == "L" && myvars[4] == "D") {
                        newPolitician = new DandL(myvars[0], myvars[1], intId, intPower);
                        m_vecPoliticians.push_back(newPolitician);
                    } else if (myvars[5] == "L" && myvars[4] == "R") {
                        newPolitician = new RandL(myvars[0], myvars[1], intId, intPower);
                        m_vecPoliticians.push_back(newPolitician);
                    } else if (myvars[5] == "S" && myvars[4] == "D") {
                        newPolitician = new DandS(myvars[0], myvars[1], intId, intPower);
                        m_vecPoliticians.push_back(newPolitician);
                    } else {
                        newPolitician = new RandS(myvars[0], myvars[1], intId, intPower);
                        m_vecPoliticians.push_back(newPolitician);
                    }

                }//try
                catch(bad_alloc& e){/** if bad_alloc --> free memory already allocated...*/
//                    int size = this->m_vecParties.size();
//                    for (int i = 0; i<  size; ++i) {
//
//                        delete m_vecParties[i];
//                        m_vecParties[i] = NULL;
//
//                    }
//                    m_vecParties.clear();
//
//                    size = this->m_vecPoliticians.size();
//                    for (int i = 0; i<  size; ++i) {
//                        m_vecPoliticians[i]->setMyParty(NULL);
//                        delete m_vecPoliticians[i];
//                        m_vecPoliticians[i] = NULL;
//
//                    }
//                    m_vecPoliticians.clear();
//                    this->m_mmBiggestParty.clear();
                    cerr << e.what() << endl;
                    terminate();
                }///catch

				}//else

			}//end read Politicians

			if (falgParty == 1) {
				string s = line.c_str();
				string delimiter = " ";
				size_t pos = 0;
				std::string token;
				k = 0;
				while ((pos = s.find(delimiter)) != std::string::npos) {
					myvars[k] = s.substr(0, pos);
					k++;
					s.erase(0, pos + delimiter.length());
				}
				myvars[k] = s.substr(0, pos);

				//myvars[1] = myvars[1].substr(0, myvars[1].length() - 1);//?

				if (myvars[1] == "D") {
					newParty = new Dparty(myvars[0]);
					if(newParty == NULL){
						terminate();
					}
				}
				else {
					newParty = new Rparty(myvars[0]);
					if(newParty == NULL){
							terminate();
						}
				}

                m_vecParties.push_back(newParty);
                m_mmBiggestParty.emplace(Key_biggest(newParty->getSize(), newParty->getName()), newParty); //TODO CHECK THAT LAB COMPUTERS ARE OK WITH THIS
                initOrTransferParty(m_vecPoliticians, newParty);
            }//end read Parties
		}//end while loop
		file.close();

	}//end if(is_open)
}// param constructor (link)



void PoliticalSys::initOrTransferParty(vector<Politician*>& poli_vec, Party* new_party) {
    /** this func moves politicians to new_party  */
	if(new_party == NULL){
			terminate();
		}
    Party *myCurrParty = NULL;

    if (poli_vec.size() == 0) {
        return;
    }else {
        vector<Politician *>::iterator itPoli;
    //    int i = 0;
        string name;
        for (itPoli = poli_vec.begin(); itPoli != poli_vec.end(); ++itPoli){
               // name = (*itPoli)->getFirstName();
                /** currPolitician's Party is NULL */
            if ((*itPoli)->getmyParty() == NULL) { //if poli's party is null -->init politician's party with new_party

                Key_biggest old_key((new_party)->getSize(), (new_party)->getName());

                if ((*itPoli)->RegisterToParty(new_party)) { //curr poli was registered to receive updates from current party
                    (*itPoli)->setMyParty(new_party);
                    mypair<multimap<Key_biggest, Party *, KeyComparator>> mp;
                    mp.replace_key(m_mmBiggestParty, old_key,Key_biggest((new_party)->getSize(), (new_party)->getName()));
                }
                //continue; //TODO maybe err
            }//end politician with null party

            else {    /**  transfer politician to smallest party */
                if ((*itPoli)->getmyParty()->getSize() > (new_party)->getSize()) {
                    myCurrParty = (*itPoli)->getmyParty();
                    Key_biggest old_key((new_party)->getSize(), (new_party)->getName());
                    Key_biggest old_key_curr(myCurrParty->getSize(), myCurrParty->getName());

                    if ((*itPoli)->RegisterToParty(new_party)) {    ///Notice! RegisterToParty also changes the Politician's Party (pointer to party)
                            myCurrParty->unregister(*itPoli);
                            mypair<multimap<Key_biggest, Party *, KeyComparator>> mp;
                            mp.replace_key(m_mmBiggestParty, old_key, Key_biggest(new_party->getSize(), new_party->getName()));
                            mp.replace_key(m_mmBiggestParty, old_key_curr, Key_biggest(myCurrParty->getSize(), myCurrParty->getName()));
                    }
                }
            }
          //  i++;
        }
    }
}//fileReadJoin


void PoliticalSys::findPartyForPoliticians(vector<Politician *> poli_vec) {
    Party *myCurrParty = NULL;
    if(poli_vec.size() == 0){
    	return;
    }
//    else if (poli_vec.size() == 0) {
//        return;
//    }
    else {

		 vector<Politician *>::iterator itPoli;
		 string name;
		 for (itPoli = poli_vec.begin(); itPoli != poli_vec.end(); ++itPoli){
    	 vector<Party *>::iterator itParty;
    	 	 for (itParty = m_vecParties.begin(); itParty != m_vecParties.end(); ++itParty)
    	 	 {
    	 	     /** find party for: A Politician that was freshly created OR politicians that their party was deleted   */
    			 if ((*itPoli)->getmyParty() == NULL) {

    				 Key_biggest old_key((*(itParty))->getSize(), ((*(itParty))->getName()));
    				 if ((*itPoli)->RegisterToParty(*itParty)) { //curr poli was registered to receive updates from current party
						    (*itPoli)->setMyParty(*itParty);
                            //continue; <-- no good here
                            mypair<multimap<Key_biggest, Party *, KeyComparator>> mp;
                            mp.replace_key(m_mmBiggestParty, old_key,Key_biggest((*(itParty))->getSize(), (*(itParty))->getName()));
                             continue;
    				 }
    			 }//end politician with null party

    			 else {    /**  transfer politician to smallest party */
    				 if ((*itPoli)->getmyParty()->getSize() > (*itParty)->getSize()) {

						myCurrParty = (*itPoli)->getmyParty();
						Key_biggest old_key((*itParty)->getSize(), (*itParty)->getName());
						Key_biggest old_key_curr(myCurrParty->getSize(), myCurrParty->getName());

                    if ((*itPoli)->RegisterToParty(*itParty)) {    ///Notice! RegisterToParty also changes the Politician's Party (pointer to party)
                            myCurrParty->unregister(*itPoli);
                            mypair<multimap<Key_biggest, Party *, KeyComparator>> mp;
                            mp.replace_key(m_mmBiggestParty, old_key, Key_biggest((*(itParty))->getSize(), (*(itParty))->getName()));
                            mp.replace_key(m_mmBiggestParty, old_key_curr, Key_biggest(myCurrParty->getSize(), myCurrParty->getName()));
                    }
                }
            }
          //  i++;
        }
    	 }
    }
}//findPartyForPartilessPoliticians


PoliticalSys::~PoliticalSys() {
    int size = this->m_vecParties.size();
    for (int i = 0; i<  size; ++i) {

        delete m_vecParties[i];
        m_vecParties[i] = NULL;

    }
    m_vecParties.clear();

    size = this->m_vecPoliticians.size();
    for (int i = 0; i<  size; ++i) {
        m_vecPoliticians[i]->setMyParty(NULL);
        delete m_vecPoliticians[i];
        m_vecPoliticians[i] = NULL;

    }
    m_vecPoliticians.clear();
    this->m_mmBiggestParty.clear();

} //destructor


void PoliticalSys::addPolitician()
{
	/*  two possible scenarios:  
		1. the politician's party is NULL
		2. the politician's curr party's size > next party in vector's size

		If User passed INVALID parameters: handle using exceptions - DO NOT TERMINATE PROGRAM!
	*/
	
	string firstName;
	string lastName;
	int id;
	int power;
	string RorD;
	string LorS;
	int flag;
	int& flagRef = flag;
	validate_numeric_input exceptionObj;//TODO find out if there's need to call constructor explicitly with () operator
    cout << "---Create Politician---" << endl;
	do {
		/*
            1. Power is negative
            2. ID is negative
            3. politician type is not "L" or "S"
            4. politician party type is not "R" or "D"
            5. ID already exists
            6. Party name already exist
		*/
		flag = 0;
		cout << "First name:" << endl;
		cin >> firstName;

		cout << "Last name:" << endl;
		cin >> lastName;

		cout << "ID:" << endl;
		cin >> id;
		exceptionObj.validateInt(cin, flagRef); //if type(id)!=int --> flag == -1
        if (id < 0) { //2. ID is negative
			flag = -1;
		}

        // 5. ID already exists
		for (vector<Politician*>::iterator it = m_vecPoliticians.begin() ; it != m_vecPoliticians.end(); ++it) {
			if ((*it)->getId() == id) {
				flag = -1;
			}
		}
		cout << "Power:" << endl;
		cin >> power;
		exceptionObj.validateInt(cin, flagRef); //if type(id)!=int --> flag == -1
		if (power < 0) { // 1. Power is negative
			flag = 1;
		}
        //  4. politician party type is not "R" or "D"
        cout << "Republican or Democratic person" << endl;
		cin >> RorD;
		if (RorD.compare("R") != 0 && RorD.compare("D") != 0) {
			flag = 1;
		}
        // 3. politician type is not "L" or "S"
        cout << "Leader or Social" << endl;
		cin >> LorS;
		if (LorS.compare("L") != 0 && LorS.compare("S") != 0) {
			flag = 1;
		}

		try{
            if (flag != 0) {
                throw Invalid_Insert_Params();
            }
        }
		catch (exception& e){
           cout << e.what() << endl;
        }

	} while (flag != 0);

	Politician *newPolitician = NULL;
	try {
		if (LorS == "L" && RorD == "D") {
			newPolitician = new DandL(firstName, lastName, id, power);
			//m_vecPoliticians.push_back(newPolitician);
		} else if (LorS == "L" && RorD == "R") {
			newPolitician = new RandL(firstName, lastName, id, power);
			//m_vecPoliticians.push_back(newPolitician);
		} else if (LorS == "S" && RorD == "D") {
			newPolitician = new DandS(firstName, lastName, id, power);
			//m_vecPoliticians.push_back(newPolitician);
		} else {
			newPolitician = new RandS(firstName, lastName, id, power);
			//m_vecPoliticians.push_back(newPolitician);
		}
	}
	catch(bad_alloc&  e){
         cerr << e.what() << endl;
         terminate();

	}
	this->m_vecPoliticians.push_back(newPolitician);
	/* Insert new politician to party */
    vector<Politician*> dummy_vec(1, newPolitician);
    findPartyForPoliticians(dummy_vec);

}//addPolitician


void PoliticalSys::removePolitician() {
/*
	1. ID is negative
	2. ID doesn't exist
*/
    int id;
    int n = m_vecPoliticians.size();
	int flag;
	int& flagRef = flag;
    mypair<multimap<Key_biggest, Party *, KeyComparator>> mp;
	validate_numeric_input exceptionObj;
	Party* myCurrParty =NULL;
	if (n != 0)
	{
        cout << "---Remove Politician---" << endl;
        do {
            flag = -1;
            cout << "Enter the ID:" << endl;
            cin >> id;
            exceptionObj.validateInt(cin, flagRef);//if type(id)!=int --> flag == -1
            if (id < 0) {  //1. ID is negative
                flag = -1;
            }

            vector<Politician *>::iterator it;
            for (it = m_vecPoliticians.begin(); it != m_vecPoliticians.end(); ++it)
            {
                if (id == (*it)->getId()) {//politician exists
                    flag =0;
                    myCurrParty = (*it)->getmyParty();
                    ///NOTE: check that this politician isn't chairman of his/her party --> is done in Unregister()
                    if(myCurrParty != NULL) {
                        ///unregister from party and then call the destructor of Politician
                        Key_biggest old_key_curr(myCurrParty->getSize(), myCurrParty->getName());

                        if ((*it)->getmyParty()) { (*it)->getmyParty()->unregister(*it); }
                        mp.replace_key(m_mmBiggestParty, old_key_curr,
                                       Key_biggest(myCurrParty->getSize(), myCurrParty->getName()));
                    }
                        delete *it;
                        m_vecPoliticians.erase(it);
                        break;//important: if we didn't break and continued the loop-> iterator invalidation

                }//BIG IF

            }//end of for loop




            try{
                if (flag != 0) {
                        throw Invalid_RemovePolitician_Params();
                }
            }
            catch (exception& e){   //TODO check pitfalls
                cout << e.what() << endl;
            }


        }while (flag != 0);
    }

}//removePolitician


void PoliticalSys::removeParty() { //todo think about the possibility of NULL PTR as vector elem? is it possible? should not happen - make sure
    int flag;
	string name;
	int size;
	int n = m_vecParties.size();
    vector<Politician*> vec_PartylessPoliticians;
	if (n != 0)
	{
	    cout << "---Remove Party---" << endl;
        vector<Party*>::iterator itParty;
		do {
		    flag = -1;
			cout << "Enter party name:" << endl;
			cin >> name;
			for (itParty = m_vecParties.begin(); itParty != m_vecParties.end(); ++itParty) {

			    if (name == (*itParty)->getName()) { /**  found party to remove */
				    flag = 0;
				    size = (*itParty)->getSize();
                    vec_PartylessPoliticians = (*itParty)->getPoliticians();
                    /** set politicians' party to NULL */
                    vector<Politician*>::iterator itPoli;
                    for(itPoli = vec_PartylessPoliticians.begin(); itPoli != vec_PartylessPoliticians.end(); ++itPoli){
                        (*itPoli)->setMyParty(NULL);
                    }
                    delete *itParty;      //TODO check that i freed correctly
                    m_mmBiggestParty.erase(Key_biggest(size, name));
                    m_vecParties.erase(itParty);
                    /** find new home for party less politicians*/
                    findPartyForPoliticians(vec_PartylessPoliticians);
                    /**  delete the Party Object  (dynamically allocated in CreateParty/fileRead) */
                    break;
				}
			}//end of for loop

            try{
                if (flag != 0) {
                    throw Invalid_RemoveParty_Params();
                }
            }
            catch (exception& e){   //TODO check pitfalls
                cout << e.what() << endl;
            }
        } while (flag != 0);

	}
}//removeParty



void PoliticalSys::addParty() {
    //TODO check that buffer is clean after each input read(could be source for bugs)
    //int n = m_vecParties.size();
	string Name;
	string RorD;
	int flag;
    cout << "---Create Party---" << endl;
	do {
		flag = 0;
		cout << "Name:" << endl;
		cin >> Name;
		for(vector<Party*>::iterator it = m_vecParties.begin(); it != m_vecParties.end(); ++it) {
			if (Name == (*it)->getName()) {
				flag = -1;
			}
		}

		cout << "Republican or Democratic party" << endl;
		cin >> RorD;
		if (RorD != "R" && RorD != "D") {
			flag = -1;
		}

        try{
            if (flag != 0) {
                throw Invalid_Insert_Params();
            }
        }
        catch (exception& e){   //TODO check pitfalls
            cout << e.what() << endl;
        }

    } while (flag != 0);

    Party* newParty = NULL;
	try {
            if (RorD == "R") {
                newParty = new Rparty(Name);
            }
            else {
                newParty = new Dparty(Name);
            }
    }
    catch(bad_alloc&  e){ //TODO check how to do this properly! (find out if catching this system.err also frees up all memory used by the process) probably not...

        //TODO the prog should terminate ->free up all memory allocated on heap (all containers [if not empty])
        cerr << e.what() << endl;
    }

    m_vecParties.push_back(newParty);
    m_mmBiggestParty.emplace(Key_biggest(newParty->getSize(), newParty->getName()), newParty);
    initOrTransferParty(m_vecPoliticians, newParty);

}//addParty




void PoliticalSys::elections() {

    if (m_vecParties.size() != 0 && m_vecPoliticians.size() != 0) {
        vector<Party *>::iterator itParty;

        /* Primaries: each party chooses the most powerful Leader (and the oldest among the most powerful) to be chairman */
        cout << "----Primaries----" << endl;
        for (itParty = m_vecParties.begin(); itParty != m_vecParties.end(); ++itParty) {
            (*itParty)->primaries();
        }

        /* Elections: calc total power for each party + print to cout */
        int totalPower;
        cout << "----Elections----" << endl;
        for (itParty = m_vecParties.begin(); itParty != m_vecParties.end(); ++itParty) {
            totalPower = (*itParty)->getPartyPower();
            cout << "Party: " << (*itParty)->getName() << ",Power: " << totalPower << endl;
        }

        /*  calc elections results and print winner */
        cout << "----Elections Results----" << endl;
        Party *theStrongest = NULL;

        itParty = m_vecParties.begin();
        theStrongest = (*itParty);
        while (itParty != m_vecParties.end()) {
            if ((*itParty)->getPartyPower() > theStrongest->getPartyPower()) {
                theStrongest = (*itParty);
            }
            ++itParty;
        }

        if(theStrongest != NULL) {
            //format: Republicans_party party won the elections and Dunald is the prime minister
            cout << theStrongest->getName() << " party won the elections and " << theStrongest->getChairmanFirstName();
            cout << " is the prime minister" << endl;
        }
    }//elses prompt main menu
}//elections



void PoliticalSys::printPoliticians() {
    cout << "----Politicians----" << endl;
    for (vector<Politician*>::iterator it = m_vecPoliticians.begin() ; it != m_vecPoliticians.end(); ++it) {
        (*it)->printPolitician();
        cout << endl;
	}
}


void PoliticalSys::printParties() {
    cout << "----Parties----" << endl;
    vector<Party *>::iterator itParty;
    for (itParty = m_vecParties.begin(); itParty != m_vecParties.end(); ++itParty) {
        (*itParty)->printAllParty();
        cout<< endl;
	}
}

void PoliticalSys::BiggestParty() {

    cout << "----Biggest Party----" << endl;
    if(this->m_vecParties.size() != 0){
        multimap<Key_biggest, Party*, KeyComparator>::iterator iter = m_mmBiggestParty.begin();
        cout << "[" << iter->second->getName() << "," << iter->second->getSize() << "]" << endl;
    }
    else{
        cout << "[" << "None" << "," << "0" << "]" << endl;
    }


}//BiggestParty
