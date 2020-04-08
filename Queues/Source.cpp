//************************************* PROGRAM IDENTIFICATION ***************************************
//*                                                                                                  *
//*     PROGRAM FILE NAME: Project 3.cpp               ASSIGNMENT #: 3             GRADE: _____      *
//*                                                                                                  *
//*     PROGRAM AUTHOR:     ______________________________                                           *
//*                                Biraj Singh GC                                                    *
//*                                                                                                  *
//*     COURSE #: CSC 36000	                                            DUE DATE: Mar 06, 2020       *
//*                                                                                                  *
//****************************************************************************************************
//*																									 *
//*************************************** PROGRAM DESCRIPTION ****************************************
//*                                                                                                  *
//*  PROCESS:         This program is designed to read in customer information and assign            *
//*                   them to checkout lanes according to their processing time, and remaining lane  *
//*					  times.																		 *
//*  USER DEFINED                                                                                    *
//*    MODULES     :   Header				-	Prints output header								 *
//*                    Footer				-	Prints output footer								 *
//*                    loadCust				-	Loads customer data into a queue					 *
//*                    pHeaders				-	Prints table headers to output						 *
//*                    PrintResults			-	Prints program results to output					 *
//*                                                                                                  *
//*                                                                                                  *
//****************************************************************************************************

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define PAGEWIDTH 95;       //Set constant page width.
#define PAGEHEIGHT 76;      //Set constant page height.

using namespace std;

//********************************************** CustomerNode Structure ***************************************************//
struct CustomerNode {
	//variable for customer information.
	char name[25];          //Customer full name.
	int arrivalTime;        //Time of customer arrival.
	int processingTime;     //Time required for processing customer.
	bool queued;            //Whether or not the customer has been assigned to a checkout line.
	//pointer to link the customer.
	CustomerNode* next;
};

//********************************************** End Of CustomerNode Structure ********************************************//
//-------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue Class Declaration ******************************************//
class CustomertQueue {
public:
	CustomertQueue();										//CustomertQueue constructor.
	int getCount();										    //Return the number of elements in queue.
	int getWait();										    //Return the wait time for queue.
	bool isEmpty();										    //Return true if the queue is empty; otherwise false.
	bool isFull();										    //Return true if there is no memory left; otherwise false.
	void incWait(int);									    //Increase wait time by given value.
	void decWait(int);									    //Decrease wait time by given value.
	CustomerNode* First();									//Return the first node in queue.
	CustomerNode* Last();									//Return the last node in queue.
	void Add(CustomerNode, int&);							//Add a customer node the end of the queue.
	void Remove(CustomerNode&, int&);						//Remove a customer node from the front of the queue.
private:
	int count;												//The number of nodes in the queue.
	int wait;												//The wait time for the queue.
	CustomerNode* front;									//Point to the frontmost node in the queue.
	CustomerNode* rear;										//Point to the last node in the queue.
};
//**************************************** End of CustomerQueue Class Declaration ****************************************//
//------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue Constructor Function **************************************//
CustomertQueue::CustomertQueue(){		
	//Class:    CustomertQueue
	//Function:	Constructor Function
	//Receives: None.
	//Tasks:	Initializes the count, wait, front and rear variable
	//Returns:  Initalized count, wait, front and rear variable

	count = 0;		
	wait = 0;
	front = NULL;
	rear = NULL;
}
//********************************************** End of CustomerQueue Constructor Function *******************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue First Function ********************************************************//
CustomerNode* CustomertQueue::First() {		
	//Class:    CustomertQueue
	//Function:	Last Function
	//Receives: None.
	//Tasks:	Checks to see if the function is empty and returs the first position of the queue
	//Returns:  Returns the address of the first element in queue.

	if (isEmpty()) {																//Return NULL if the queue is empty.
		cout << "Error: Attempted to access element from an empty queue." << endl;	//Print error message to console.
		return NULL;
	}	
	return front;																	//Otherwise, return the first element.

}
//********************************************** End of CustomerQueue First Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue Last Function *********************************************************//
CustomerNode* CustomertQueue::Last() {																
	//Last - Returns the address of the last element in queue.	
	//Class:    CustomertQueue
	//Function:	last Function
	//Receives: None.
	//Tasks:	checks to see if the function is empty and returs the last position of the queue
	//Returns:  Returns the address of the last element in queue.

	if (isEmpty())																	//Return NULL if the queue is empty.
	{		
		cout << "Error: Attempted to access element from an empty queue." << endl;	//Print error message to console.
		return NULL;
	}	
	return rear;																	//Otherwise, return the last element.
}
//********************************************** End of CustomerQueue Last Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue getCount Function *********************************************************//

int CustomertQueue::getCount() {		
	//GetCount - Returns the number of nodes in the queue.
	//Class:    CustomertQueue
	//Function:	getCount Function
	//Receives: None.
	//Tasks:	returns Count
	//Returns:  Count.

	return count;
}

//********************************************** End of CustomerQueue getCount Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue getWait Function *********************************************************//

int CustomertQueue::getWait() {		
	//Class:    CustomertQueue
	//Function:	getWait Function
	//Receives: None.
	//Tasks:	Returns Wait
	//Returns:  Wait

	return wait;
}

//********************************************** End of CustomerQueue getWait Function *************************************************//

//------------------------------------------------------------------------------------------------------------------------------------//

//********************************************** CustomerQueue IsEmpty Function *********************************************************//

bool CustomertQueue::isEmpty() {		
	//Class:    CustomertQueue
	//Function:	isEmpty Function
	//Receives: None.
	//Tasks:	checks to see if the function is empty
	//Returns:  Boolean value of true if the queue is empty.

	return (count == 0);		//Return true if the queue is empty; returns false otherwise.
}

//********************************************** End of CustomerQueue IsEmpty Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue IsFull Function *********************************************************//

bool CustomertQueue::isFull() {		
	//Class:    CustomertQueue
	//Function:	isFull Function
	//Receives: None.
	//Tasks:	checks to see if the function is full
	//Returns:  boolean true if the queue is full.
						
	CustomerNode* test;					//Create a test node.
	test = new (CustomerNode);
	if (test == NULL) {					//If a node cannot be created, the queue is full.
		delete test;
		cout << "Error: Out of Memory." << endl;
		return true;
	}	
	return false;						//Otherwise the queue is not full.
}

//********************************************** End of CustomerQueue IsFull Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue incWait Function *********************************************************//

void CustomertQueue::incWait(int increment) {
	//Class:    CustomertQueue
	//Receives: A value to increment the wait time by.
	//Task:		Increase the queue wait time by the given value.
	//Returns:  The wait time is updated.
	wait = (wait + increment);
}

//********************************************** End of CustomerQueue incWait Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue decWait Function *********************************************************//

void CustomertQueue::decWait(int decrement) {
	//Class:    CustomertQueue
	//Receives: A value to decrement the wait time by.
	//Task:		Decrease the queue wait time by the given value.
	//Returns:	The wait time is updated.
	wait = (wait - decrement);
}

//********************************************** End of CustomerQueue decWait Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue Add Function *********************************************************//

void CustomertQueue::Add(CustomerNode NewData, int& stat) {
	//Class:    CustomertQueue
	//Receives: Customer data and a status indicator.
	//Task:     Add the customer data to the checkout queue.
	//Returns:  The checkout queue is updated accordingly, and status is changed

	stat = 1;												//Initialize status.
	CustomerNode* nCust;									//Reserve space for new customer node.
	nCust = new (CustomerNode);
	if (isFull()) {											//Make sure the queue is not full.		
		stat = 0;											//Indicate an error if so.
		return;
	}
	
	nCust->arrivalTime = NewData.arrivalTime;				//Copy customer data to the new node.
	nCust->processingTime = NewData.processingTime;
	strcpy(nCust->name, NewData.name);
	nCust->next = NULL;
	if (front == NULL) {									//If the queue is empty, append new node to the front.
		front = nCust;
	}
	
	else {													//Otherwise, append new node to the rear of the queue
		rear->next = nCust;
	}	
	rear = nCust;											//Append new customer node.
	count++;												//Increment number of nodes in the queue.
	return;
}

//********************************************** End of CustomerQueue Add Function ***************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** CustomerQueue Remove Function *******************************************************//

void CustomertQueue::Remove(CustomerNode& ToDelete, int& stat) {
	//Class:    CustomertQueue
	//Receives: Reference to customer node and a status indicator.
	//Task:		Remove the front element from the list.
	//Returns:	The removed node is saved in the node reference parameter, and the status indicator is updated if necessary.

	stat = 1;											//Initialize status indicator.
	CustomerNode* temp;											//Reserve space for temporary node.	
	if (isEmpty()) {									//Make sure the queue is not empty.
		stat = 0;										//If so, indicate an error.
		return;
	}	
	ToDelete.arrivalTime = front->arrivalTime;			//Save removed node data for passing back.
	ToDelete.processingTime = front->processingTime;
	strcpy(ToDelete.name, front->name);
	temp = front;										//Remove first node from the queue.
	front = front->next;
	delete temp;
	count--;											//Update the number of nodes in the queue.
	return;
}

//********************************************** End of CustomerQueue Remove Function *************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//******************************************* MAIN Function **************************************************************************//

/* function prototypes */
void Header(ofstream&);
void Footer(ofstream&);
void LoadCustomers(ifstream&, CustomertQueue&, int);
void PrintHeaders(ofstream&);
void PrintResults(ofstream&, CustomertQueue, CustomertQueue);
/* End offunction prototypes */

int main() {
	int stat = 1;												//Program status indicator.
	int currentTime = 0;										//Store time keeper.
	CustomerNode curCust;										//Currently processed customer.
	CustomerNode depCust;										//Customer that is leaving.
	CustomertQueue arrList;										//List of customers arrived.
	CustomertQueue depList;										//List of customers departed.
	CustomertQueue line1;										//Checkout line for line 1.
	CustomertQueue line2;										//Checkout for line 2.
	CustomertQueue line3;										//Checkout for line 3.
	CustomertQueue checkout[3] = { line1, line2, line3 };		//Array of checkout lines 1-3.
	int shortest;												//Index of shortest checkout line.	

	ifstream inputFile("data3.txt", ios::in);					//Get input file.
	ofstream outputFile("output.txt", ios::out);				//Get output file.

	LoadCustomers(inputFile, arrList, stat);					//Load customer data from the input file to the arrival list.

	currentTime = 0;											//Initialize counter.

	while (depList.getCount() < arrList.getCount()) {			//Process customers until all have left.		
		if (arrList.First()->arrivalTime == currentTime) {		//If a customer is currently arriving.			
			arrList.Remove(curCust, stat);						//Remove customer from the arrival queue, receiving customer data.
			shortest = 0;										//Initialize shortest line index so far.
			for (int i = 0; i < 3; i++) {						//Compare all checkout line wait times.
				if (checkout[i].getWait() < checkout[shortest].getWait()) {
					shortest = i;
				}
			}				
			curCust.queued = true;								//Mark customer as queued.			
			checkout[shortest].Add(curCust, stat);				//Add customer to the shortest checkout line queue.			
			checkout[shortest].incWait(curCust.processingTime);	//Increment wait time of the checkout line accordingly.
			
			arrList.Add(curCust, stat);							//Append customer to the end of the arrival list.
		}

			
		for (int i = 0; i < 3; i++) {							//Update checkout lines from 1 to 3.		
			if (!checkout[i].isEmpty()) {						//If the line is not empty, check for finished customers.				
				if (checkout[i].First()->processingTime <= 0) {	//If a customer is done being processed, remove from line.					
					checkout[i].Remove(depCust, stat);			//Remove customer from checkout line.					
					depList.Add(depCust, stat);					//Place customer in the list of departed customers.
				}
			}			
			if (!checkout[i].isEmpty()) {						//If the line is still not empty, process customer at the head.				
				checkout[i].First()->processingTime--;			//Update processing time of front customer.				
				checkout[i].decWait(1);							//Update total processing time for checkout line.
			}
		}			
		currentTime++;											//Update counter.
	}	
	Header(outputFile);											//Print output heading.	
	PrintHeaders(outputFile);									//Print output table headers.	
	PrintResults(outputFile, arrList, depList);					//Print results	.
	Footer(outputFile);											//Print output closing.
	inputFile.close();
	outputFile.close();
	return 0;													//Return to operating system.
}
//********************************************** End of Main Function ***************************************************//
//-----------------------------------------------------------------------------------------------------------------------//
//********************************************** LoadCustomers Function *************************************************//
void LoadCustomers(ifstream& inputFile, CustomertQueue& queue, int stat) {
	//Receives	- Reference to an input file, reference to a queue, and a status indicator.
	//Task		- Load data from the input file into the queue.
	//Returns	- The queue is updated accordingly, and the status is updated if necessary.

	int aTime, pTime;												//Arrival time and processing time.
	char custName[26];												//Full name of a customer.
	CustomerNode newCust;															
	for (inputFile >> aTime; aTime != -99; inputFile >> aTime) {	//Process input file until the end is reached.		
		inputFile >> ws;											//Read in customer data.
		inputFile.get(custName, 26);
		inputFile >> pTime;		
		strcpy(newCust.name, custName);								//Save data to a new customer node.
		newCust.arrivalTime = aTime;
		newCust.processingTime = pTime;
		newCust.queued = false;	
		queue.Add(newCust, stat);									//Add customer node to the arrival queue.
	}
}
//********************************************** End of LoadCustomer  Function ***************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** PrintHeaders Function *******************************************************//
void PrintHeaders(ofstream& outfile) {
	//Receives	- Reference to the output file.
	//Task		- Print table headers to the output file.
	//Returns	- The output file is updated accordingly.

	outfile << "The order of customer arrival is:      The order of customer departure is:";
	outfile << endl;
	outfile << "---------------------------------      -----------------------------------";
	outfile << endl;
}
//********************************************** End of PrintHeaders Function ***************************************************//
//------------------------------------------------------------------------------------------------------------------------------------//
//********************************************** PrintResults Function *******************************************************//
void PrintResults(ofstream& outfile, CustomertQueue arrivals, CustomertQueue departures) {
	//Receives	- Reference to the output file, a queue of arrivals and a queue of departures.
	//Task		- Print the arrival queue and departure queue as side-by-side lists.
	//Returns	- The data is printed to the output file.

	int stat = 1;							//Initialize the status indicator.
	int numRecords;							//Number of records to be printed from each list.
	CustomerNode customer;							
	numRecords = arrivals.getCount();		//Initialize number of records to print, based on the length of the first list.	
	for (int i = 0; i < numRecords; i++) {	//Print both lists side-by-side		
		arrivals.Remove(customer, stat);	//Get and print a value from list 1
		outfile << customer.name;
		outfile << "         |    ";		//Print spacing and divider		
		departures.Remove(customer, stat);	//Get and print a value from list 2
		outfile << customer.name;		
		outfile << endl;					//Drop down a line
	}
	return;
}
//********************************************** End of printResults Function ***************************************************//
//-------------------------------------------------------------------------------------------------------------------------------//
//********************************************** Header Function ****************************************************************//
void Header(ofstream& Outfile)
{
	//Receives - The output file
	//Task - Prints the output preamble
	//Returns - Nothing

	Outfile << setw(30) << "Biraj Singh GC";
	Outfile << setw(17) << "CSC 36000";
	Outfile << setw(15) << endl;
	Outfile << setw(30) << "Spring 2020";
	Outfile << setw(20) << "Assignment #3" << endl;
	Outfile << setw(35) << "-----------------------------------";
	Outfile << setw(35) << "-----------------------------------\n\n";

	return;
}
//********************************************** End of Header Function ***************************************************//
//-------------------------------------------------------------------------------------------------------------------------//
//********************************************** Footer Function *******************************************************//
void Footer(ofstream& Outfile)
{
	//Receives - The output file
	//Task - Prints the output salutation
	//Returns - Nothing

	Outfile << endl;
	Outfile << setw(35) << " --------------------------------- " << endl;
	Outfile << setw(35) << "|      END OF PROGRAM OUTPUT      |" << endl;
	Outfile << setw(35) << " --------------------------------- " << endl;

	return;
}
//********************************************** End of Footer Function ***************************************************//