
#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <iostream>
#include <exception>
#include <climits>
using namespace std;


class Invalid_RemovePolitician_Params : public std::exception
{
/*
	1. ID is negative
	2. ID doesn't exist
*/
public:
	virtual char const* what() const throw() { return "Please enter valid id"; }

}; //
//Invalid_Id_Exception



class Invalid_Insert_Params : public std::exception
{

/*
	1. Power is negative
	2. ID is negative
	3. politician type is not "L" or "S"
	4. politician party type is not "R" or "D"
	5. ID already exists 
	6. Party name already exist
*/
public:

    virtual char const* what() const throw() { return "Please enter valid details"; }

}; //Invalid_Insert_Exception


class Invalid_RemoveParty_Params : public std::exception {
/*
	1.

*/
public:
	virtual char const* what() const throw(){ return "Please enter valid name"; }

}; //Invalid_Name_Exception



class validate_numeric_input{
public:
    void validateInt(std::istream& in, int& flag){
        if(in.fail()){ ///check if not int
            in.clear();
            //    cin.ignore(numeric_limits<streamsize>::max(),"\n");
            in.ignore(INT_MAX, '\n');
            flag = -1;
        }
    }

};


#endif //MYEXCEPTION_H