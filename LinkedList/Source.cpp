//************************************  PROGRAM IDENTIFICATION  **************************************
//*																									 *
//*   PROGRAM FILE NAME:  Project2.cpp          ASSIGNMENT #:  2            Grade: _________		 *
//*																									 *
//*   PROGRAM AUTHOR:																				 *
//*                   ___________________________________________________							 *
//*                                     Biraj Singh GC												 *
//*																									 *
//*   COURSE #:  CSC 36000 11                              DUE DATE: February 21, 2019				 *
//*																									 *
//****************************************************************************************************

//*************************************** PROGRAM DESCRIPTION ****************************************
//*   PROCESS: This program reads the fileand executes command. if command is add then data is added *
//*   if datais to be deleted then data is deleted. if the data is to changed then it chnages the    *
//*   data. this program uses linked list and classes. this also uses search method.                 *
//*   USER DEFINED                                                                                   *
//*    MODULES     :   Header.........................Prints the output Header preamble              *
//*                    Footer.........................Prints the output footer Preamble              *
//*                    ReadAndProcess.................Reads the Data File and stores the data into   * 
//*                                                   Linked List                                    *
//*                    CustomerLList Class........... Class that contains Linked list of CustomerNode*
//*                                                   structure and the data                         *
//*                                                                                                  *
//****************************************************************************************************
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//********************************************** CustomerNode Structure ***************************************************//
struct CustomerNode {
    // Customer data
    string firstName, lastName, address, city, state, zip;
    // Pointer to next customer in list
    CustomerNode* next;
};

//********************************************** End Of CustomerNode Structure ********************************************//
//-------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList Class Declaration ***************************************************//
class CustomerLList {
public:
    CustomerLList();                                            //CustomerList constructor
    bool IsExistingNode(string, string);                        //Test to see if node exists.
    void InsertNode(CustomerNode);                              //Adds Nodes according to LastName
    void ChangeNode(string, string, int, string);          //Update a field within a specified node
    void PrintList(ofstream&);                                  //Print the entire list
    void RecordError(char,string,string);                       //Record all error into a string 
    void PrintError(ofstream&);                                 //Prints the list of recorded error 
    CustomerNode DeleteNode(string , string);                   //Delete specified node from the list
private:
    CustomerNode* listStart;                                    // Starting point of the list
    string ErrorRecord;                                         // Error log
};
//********************************************** End of CustomerLList Class Declaration ***************************************************//

/* Function prototypes*/

void Header(ofstream&);												//print the header for the project.
void Footer(ofstream&);												//print the footer for the project.
void ReadandProcess(ifstream&, CustomerLList, ofstream&);           //read and process data from data file into linked list.

/* End of Function prototypes*/


//********************************************** CustomerLList Constructor Function ************************************************//
CustomerLList::CustomerLList(){
    //Class:    CustomerLList
    //Function:	Constructor Function
    //Receives: None.
    //Tasks:	Initializes the starting point for list as NULL. 
    //Returns:  Initalized starting point of list.
    listStart = NULL;                       
}
//********************************************** End of CustomerLList Constructor Function *******************************************//
//----------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList IsExistingNode Function ************************************************//
bool CustomerLList::IsExistingNode(string FirstName, string LastName){
    //Class:    CustomerLList
    //Function:	IsExistingNode Function
    //Receives: The first and last name of customer .
    //Tasks:	Searches for the specified record in the list. 
    //Returns:  Returns TRUE if the record is found; Returns FALSE otherwise
        
    bool TestAlphabet = true;                              //initalize boolean for alphabet test.
    CustomerNode *CurrentNode;                             //intitalize search pointer.
    CurrentNode = listStart;                               //Search from the strat of the list.

    //Go through list until a match is found or list is exhausted
    while ((CurrentNode != NULL) && TestAlphabet) {
        if (((CurrentNode->lastName).compare(LastName) == 0) && (CurrentNode->firstName).compare(FirstName)==0){
            TestAlphabet = false;                         //Stop search if found
            break;
        }
        //Procceed onto next node
        else {
            CurrentNode = CurrentNode->next;
        }
    }
    return (!TestAlphabet);                               // If a match was found, return TRUE else False.
}
//********************************************** End of CustomerLList IsExistingNode Function *******************************************//
//----------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList InsertNode Function ************************************************//
void CustomerLList::InsertNode(CustomerNode NewCustomer){
    //Class:    CustomerLList
    //Function:	InsertNode Function
    //Receives: The structure or ne customer to be added.
    //Tasks:	Adds Customer into the list according to last name 
    //Returns:  Updated Linked List
    bool TestAlphabet = true;                            //initalize boolean for alphabet test.
    CustomerNode *NewNode, *CurrentNode, *PreviousNode;  //intitalize search pointer.

    NewNode = new(CustomerNode);                         //Create New Node
    if (NewNode != NULL)                                 //Check if memory is available 
    {//transfer the data into new node.
        NewNode->firstName = NewCustomer.firstName;      
        NewNode->lastName = NewCustomer.lastName;
        NewNode->address = NewCustomer.address;
        NewNode->city = NewCustomer.city;
        NewNode->state = NewCustomer.state;
        NewNode->zip = NewCustomer.zip;

        //initialize the search nodes.
        PreviousNode = NULL;
        CurrentNode = listStart;

        if (CurrentNode == NULL) {                       //check if linked list is empty.
            NewNode->next = NULL;                        //start the list.
            listStart = NewNode;
        }
        else {
            while (CurrentNode != NULL && TestAlphabet){  //loop through the list to find appropriate links
                if ((CurrentNode->lastName).compare(NewNode->lastName) > 0) { // according to last name
                    TestAlphabet = false;                 //stop search
                }
                    //according to last Name
                else if (((CurrentNode->lastName).compare(NewNode->lastName) == 0)&&((CurrentNode->firstName).compare(NewNode->firstName) < 0)){
                    TestAlphabet = false;                 //stop search
                }
                else {
                    // proceed to next node
                    PreviousNode = CurrentNode;
                    CurrentNode = CurrentNode->next;
                }
            }
            if (PreviousNode == NULL) {
                // Insert new node into the first place of the list
                NewNode->next = listStart;
                listStart = NewNode;

            }
            //Insert the node between with appropriate link
            else{
                PreviousNode->next = NewNode;
                NewNode->next = CurrentNode;
            }
        }
    }
    else{
        cout << "Error! Out of memory!";// Print error message if out of memory to console
    }
    return;
}
//********************************************** End of InsertNode Function *******************************************//
//---------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList DeleteNode Function ************************************//
CustomerNode CustomerLList::DeleteNode(string FirstName, string LastName) {
    //Class:    CustomerLList
    //Function:	DeleteNode Function
    //Receives: The first and last name of customer to be deleted
    //Tasks:	Attempts to remove specified record from the list
    //Returns:  Updated List, and the data from the deleted node is returned

    CustomerNode* tempNode = NULL, * PreviousNode, * CurrentNode;               // Initialize search Pointers

    // Check if first node is removed, and adjust.
    if ((LastName == listStart->lastName) && (FirstName == listStart->firstName)){
        // set next node as starting point
        tempNode = listStart;
        listStart = listStart->next;
        //Return data from deleted node
        return *tempNode;
    }
    // Find the node to delete
    else{
        // Initialize search pointers
        PreviousNode = listStart;
        CurrentNode = listStart->next;

        //  Search list until match is made.
        while ((CurrentNode != NULL) && ((CurrentNode->lastName).compare(LastName) != 0) && (CurrentNode->firstName).compare(FirstName) != 0){
            //Procced to the next node
            PreviousNode = CurrentNode;
            CurrentNode = CurrentNode->next;
        }
        // If found, remove it from the list
        if (CurrentNode != NULL) {
            // adjust list
            tempNode = CurrentNode;
            PreviousNode->next = CurrentNode->next;
            tempNode->next = NULL;
            // Return data from deleted node
            return *tempNode;
        }
    }
    // If the node was not found, return NULL
    return *tempNode;
}
//********************************************** End of DeleteNode Function *******************************************//
//---------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList ChangeNode Function ************************************//

void CustomerLList::ChangeNode(string FName, string LName, int code, string change)
{   //Class:    CustomerLList
    //Function:	ChangeNode Function
    //Receives: The first and last name of customer to be deleted, field code, change to be made
    //Tasks:	Applies change of new value to the specified field in the specified record
    //Returns:  The specified node is edited accordingly

    CustomerNode* CurrentNode,*PreviousNode, movingNode;               //initialize search pointers.
    CurrentNode = listStart;                                           //start searching from the begining.

    //search through the list
    while ((CurrentNode != NULL) && ((CurrentNode->lastName).compare(LName) == 0) && ((CurrentNode->firstName).compare(FName) == 0)) {
        //proceed until found.
        PreviousNode = CurrentNode;
        CurrentNode = CurrentNode->next;        
    }
    if (CurrentNode != NULL){ 
        // if found Apply change according to the specified field
        switch (code) {
        case 1:
            // Change first name and readjust position in list
            movingNode = DeleteNode(FName, LName);
            movingNode.firstName = change;
            InsertNode(movingNode);
            break;
        case 2:
            //Change last name and readjust position in list
            movingNode = DeleteNode(FName, LName);
            movingNode.lastName = change;
            InsertNode(movingNode);
            break;
        case 3:
            // Change the address
            CurrentNode->address = change;
            break;
        case 4:
            // Change the city
            CurrentNode->city = change;
            break;
        case 5:
            // Change the state
            CurrentNode->state = change;
            break;
        case 6:
            // Change the zip code
            CurrentNode->zip = change;
            break;
        default:
            // If the specified field is not valid, print error message for error debugging;
            cout << "Error: Change error - Unknown field."<< endl;
            break;
        }
    }
    // If the node was not found in the list, print a error message
    else {
        cout << "Error: An error ocurred while atempting to change node." << endl;
    }
    return;
    
}
//********************************************** End of ChangeNode Function *******************************************//
//---------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList PrintList Function ************************************//

void CustomerLList::PrintList(ofstream& outfile) {
    //Class:    CustomerLList
    //Function:	PrintList Function
    //Receives: The output file
    //Tasks:	Prints list of data records to the output file
    //Returns:  The output file is updated

    CustomerNode* CurrentPtr;               //Initialize temporatry
    CurrentPtr = listStart;                 // Initialize a current pointer to the start of the linked list
    // Check if the list is empty
    if (CurrentPtr == NULL){
        outfile << "The list is empty." << endl;
        return;
    }
    else {
        outfile << "                                ";
        outfile << "MAILING LIST" << endl;
        outfile << "Last Name    First Name   Address               City         State   Zip Code" << endl;
        outfile << "=============================================================================" << endl;
        // Process the list
        while (CurrentPtr != NULL){
            //  Print the data for the node
            outfile<<CurrentPtr->lastName<<" "<<CurrentPtr->firstName<<" "<<CurrentPtr->address<<"  "<<CurrentPtr->city<<"  "<<CurrentPtr->state<<"     "<<CurrentPtr->zip<<endl;
            //  Move to the next NODE
            CurrentPtr = CurrentPtr->next;
        }
        outfile << endl;
    }
    return;
}
//********************************************** End of PrintList Function *******************************************//
//---------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList RecordError Function ************************************//
void CustomerLList::RecordError(char mode, string fname, string lname) {
   //Class:    CustomerLList
   //Function:	RecordError Function
   //Receives:  The error type (mode) and the first and last name of offending record
   //Tasks:	Creates an error report for specified error and appends it to the list error log
   //Returns:  The error log for the customer list is updated
    
    //remove whitespace from names
    fname.erase(remove(fname.begin(), fname.end(), ' '), fname.end());
    lname.erase(remove(lname.begin(), lname.end(), ' '), lname.end());

        // Initialize new error message
    string newError = "\n";

    // Determine error type and compose new message
    switch (mode) {
    case 'A':   // Add error
        newError += fname;
        newError += " ";
        newError += lname;
        newError += " is already in the list. Attempt to add duplicate record failed!\n";
        break;
    case 'C':   // Change error
        newError += "Record of ";
        newError += fname;
        newError += " ";
        newError += lname;
        newError += " not found. Attempt to change record failed!\n";
        break;
    case 'D':   // Delete error
        newError += "Record of ";
        newError += fname;
        newError += " ";
        newError += lname;
        newError += " not found. Attempt to delete record failed!\n";
        break;
    default:    // Error error: Invalid error
        cout << "Error: An error occured while recording an error.";
        break;
    }
    // Append new error message to the list error log
    ErrorRecord += newError;
}
//********************************************** End of Record Function *******************************************//
//---------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerLList PrintError Function ************************************//
void CustomerLList::PrintError(ofstream& outfile) {
    //Class:    CustomerLList
    //Function:	PrintError Function
    // Receives - The output file
    // Task - Print error log to the output file
    // Returns - The error log is printed to the output file

        // Print the error log to the output file
    outfile << ErrorRecord << endl;
    outfile << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    ErrorRecord = " ";
    return;
}

//********************************************** End of printError Function *******************************************//
//---------------------------------------------------------------------------------------------------------------------//
//**********************************************Main Function *********************************************************//
int main() {

    ifstream infile("DATA2.txt", ios::in);													//import file.
    ofstream outfile("result.txt", ios::out);												//export file.
    CustomerLList ListClass;

    if (infile.fail())																		//Error catcher 
    {
        cout << " The file was not found." << endl;
        exit(1);																			//Exit the program
    }
    Header(outfile);                                                                        //Add header
    ReadandProcess(infile, ListClass, outfile);                                             //read and process the data
    Footer(outfile);                                                                        //add footer
    return 0;
}
//********************************************** End of Main Fuction *******************************************************//

//---------------------------------------------------------------------------------------------------------------------------//

//********************************************** Header Function ***********************************************************//
void Header(ofstream& Outfile) {
    //Function: Header
    //Receives – the output file
    //Task - Prints the output preamble
    //Returns - Nothing
    Outfile << setw(30) << "Biraj Singh GC";
    Outfile << setw(17) << "CSC 36400";
    Outfile << setw(15) << "Section 11" << endl;
    Outfile << setw(30) << "Spring 2020";
    Outfile << setw(20) << "Assignment #2" << endl;
    Outfile << setw(35) << "---------------------------------- - ";
    Outfile << setw(35) << "---------------------------------- -  " << endl << endl;
    return;
}
//******************************************* End of Header Function ********************************************************//

//---------------------------------------------------------------------------------------------------------------------------//

//********************************************** Footer Function ************************************************************//
void Footer(ofstream& Outfile) {
    //Function:	 Footer
    //Receives – the output file
    //Task -	 Prints the output salutation
    //Returns -	 Nothing
    Outfile << endl;
    Outfile << setw(35) << "-------------------------------- - " << endl;
    Outfile << setw(35) << " | END OF PROGRAM OUTPUT | " << endl;
    Outfile << setw(35) << "-------------------------------- - " << endl;
    return;
}
//********************************************** End of footer Function ***************************************************//

//-------------------------------------------------------------------------------------------------------------------------//

//********************************************** ReadandProcess Function ******************************************************//

void ReadandProcess(ifstream& infile, CustomerLList List, ofstream& outfile)
{
    //Function:	FileReader
    //Receives: Input file, objects of CustomerLList, outputfile
    //Tasks:	Reads the input file and stores data in linked list
    //Returns:  Updated outputfile.

    //initialize temporary variables.
    int FieldNumber;
    string Act, LastName, FirstName, address, city, state, zip, field, change;
    char mode;
    CustomerNode temp;

    getline(infile, Act);                  //read the first action
    stringstream ss1(Act);    
    ss1 >> mode;                           //convert into char
    while (!infile.eof()){
        // loop until the end
        if (Act.compare("Q") == 0){
            break;                        // break of action is quit
        }
        else if (Act.compare("A") == 0){
            //if act is A
            getline(infile, temp.firstName);
            getline(infile, temp.lastName);
            getline(infile, temp.address);
            getline(infile, temp.city);
            getline(infile, temp.state);
            getline(infile, temp.zip);
            // check to see if Node exists.
            if (List.IsExistingNode(temp.firstName,temp.lastName) == false){
                List.InsertNode(temp);                                                 //add node
            }
            else{
                List.RecordError(mode, temp.firstName, temp.lastName);                 //add to error
            }
        }
        else if (Act.compare("C")==0){
            //if act is C
            getline(infile, FirstName);
            getline(infile, LastName);

            getline(infile, field);
            stringstream ss2(field);                                                    // convert field into int.
            ss2 >> FieldNumber;                                                         

            getline(infile, change);
            //check if node exists
            if (List.IsExistingNode(FirstName, LastName) == true){
                List.ChangeNode(FirstName, LastName, FieldNumber, change);              //change node
            }
            else{
                List.RecordError(mode, FirstName, LastName);                            //add to error              
            }
        }
        else if (Act.compare("D")==0){
            //if act is D
            getline(infile, FirstName);
            getline(infile, LastName);
            //check if node exists
            if (List.IsExistingNode(FirstName, LastName) == true){
                List.DeleteNode(FirstName, LastName);                                   //delete node
            }
            else{
                List.RecordError(mode, FirstName, LastName);                            //add to error
            }
        }
        else if (Act.compare("P")==0){
            //if act is P
            List.PrintList(outfile);                                                    //print the list
            List.PrintError(outfile);                                                   //print the error
        }
        getline(infile, Act);
        stringstream ss1(Act);
        ss1 >> mode;
    }
}
//********************************************** End of ReadAndProcess Function ***************************************************//
