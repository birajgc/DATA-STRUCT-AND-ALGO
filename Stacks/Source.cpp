//************************************  PROGRAM IDENTIFICATION  **************************************
//*																									 *
//*   PROGRAM FILE NAME:  Project4.cpp          ASSIGNMENT #:  4            Grade: _________		 *
//*																									 *
//*   PROGRAM AUTHOR:																				 *
//*                   ___________________________________________________							 *
//*                                     Biraj Singh GC												 *
//*																									 *
//*   COURSE #:  CSC 36000 11                              DUE DATE: March 27, 2019			     	 *
//*																									 *
//****************************************************************************************************

//*************************************** PROGRAM DESCRIPTION ****************************************
//*   PROCESS:		   This program takes a mathematical expression in INFIXnotation, convert it     *
//*                    to POSTFIX notation, and then evaluate the POSTFIXnotation form of the        *
//*                    expression.                                                                   *
//*   USER DEFINED                                                                                   *
//*    MODULES     :   Header.........................Prints the output Header preamble              *
//*                    Footer.........................Prints the output footer Preamble              *
//*                    IntoPost.......................Convert Infix to PostFix                       * 
//*                    PostSoln.......................Evaluate the postfix expression                *
//*                                                                                                  *
//****************************************************************************************************
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

/* Create Node for the Stack*/
struct OperationNode {
	char OperatorData;						 //initialize variable for operator data
	int OperandData;						 //initialize variable for operand data
	OperationNode* next;					 //initialize pointer to link stack
};

//**************************************StackController Class ************************************//
class StackController {
	public:
		StackController() { Top = NULL; }		//construct the stack 
		~StackController();						//Deconstruct class and destroy the stact
		void push(OperationNode);				//Push node onto the stack
		void pop(OperationNode&);				//Pop Node from the stack
		bool RetrieveTop(OperationNode&);		//Get the top stack if it exists.
		bool IsEmpty() { return(Top == NULL);}  //See if the stack is empty.
		bool IsFull();							//See if stack is full.
	private:
		OperationNode* Top;						//point to top of the stack
};
//**********************************END of StackController Class************************************//

//**********************************Deconstructor for StackContoller********************************//
StackController::~StackController(){
   //Class:		StackController
   //Function:	DeConstructor Function
   //Receives:	None.
   //Tasks:		Deconstructs the stack. 
   //Returns:	none.
	OperationNode* temp;					//Initialie Temp variable for the OperationNode pointer
	while (Top != NULL){					//Loop through the stack and delete all the nodes.
		temp = Top;
		Top = Top->next;
		delete temp;
	}
}
//**********************************End of Deconstructor for StackContoller********************************//

//**********************************Push for StackContoller************************************************//
void StackController::push(OperationNode Datain) {
   //Class:		StackController
   //Function:	Push Function
   //Receives:	OpeationNode.
   //Tasks:		adds node to the stack. 
   //Returns:	none.
	if (IsFull()){									//Check if the stack is full.
		cout << "Push Operation Failed!" << endl;
		return;										//return if true.
	}
	//Push the new node on top of the stack and link it with the ther nodes.
	OperationNode* Temp;		
	Temp = new OperationNode;

	Temp->OperandData = Datain.OperandData;
	Temp->OperatorData = Datain.OperatorData;
	Temp->next = Top;

	Top = Temp;
	return;
}
//**********************************End of Push for StackContoller************************************************//

//**********************************POP for StackContoller********************************************************//
void StackController::pop(OperationNode& Dataout) {
   //Class:		StackController
   //Function:	Pop Function
   //Receives:	OperationNode.
   //Tasks:		Removes the top stack 
   //Returns:	removed node.
	OperationNode *Temp;
	if (IsEmpty()) {								//check if the Stack is empty.
		cout << " Stack is empty. " << endl;            
		cout << " Pop Operation Failed. " << endl;       
		return;
	}
	//Pop the top node from the stack and point top to the next node.
	Dataout.OperandData = Top->OperandData;
	Dataout.OperatorData = Top->OperatorData;

	Temp = Top;										//return the node that was poped
	Top = Top->next;

	delete Temp;
	return;
}
//*************************End of Pop for StackController********************************************************//

//*************************RetrieveTop for StackContoller********************************************************//
bool StackController::RetrieveTop(OperationNode& TopNode) {
   //Class:		StackController
   //Function:	RetrieveTop Function
   //Receives:	OperationNode.
   //Tasks:		Retrievs top node. 
   //Returns:	top node and boolean value of true if it exists.
	if (IsEmpty()) {                                   //Check to see if stack exists.
		cout << "Stack Does Not exist" << endl;
		return false;								   //Return False if true
	}
	else{
		//retrieve data from the top node of the stack and pass it by refrence.
		TopNode.OperandData=Top->OperandData;
		TopNode.OperatorData = Top->OperatorData;
		TopNode.next = Top->next;
		return true;
	}
}
//*********************End of RetrieveTop for StackContoller********************************************************//

//*********************************Isfull for StackContoller********************************************************//
bool StackController::IsFull() {
   //Class:		StackController
   //Function:	IsFull Function
   //Receives:	None.
   //Tasks:		Checks if any memory is remaining. 
   //Returns:	bool value.
	OperationNode* p;
	p = new OperationNode;								//create a node
	if (p == NULL) {									//check if the node was created					
		delete p;
		cout << "Out of Memory. " << endl;
		return true;									//if not created return true
	}
	return false;						
}
//**********************************RetrieveTop for StackContoller********************************************************//

/* Function prototypes*/
void Header(ofstream&);																	//print the header for the project.
void Footer(ofstream&);																	//print the footer for the project.
void IntoPost(ofstream&, char[], char[], StackController&);								//Convert Infix to PostFix
void PostSoln(ofstream&, char[], StackController&,int&);								//Evaluate the postfix expression

//************************************************ Main Fuction *********************************************************//
int main()
{
	StackController Stack1,Stack2;
	int finalsum;
	ifstream infile("data4.txt", ios::in);												//import the file 
	ofstream outfile("result.txt", ios::out);											//export the file

	if (infile.fail()) {																//Error catcher 
		cout << " The file was not found." << endl;
		exit(1);																		//Exit the program
	}
	Header(outfile);																	//print the header for the project.

	//loop through the data
	while (!infile.eof()){
		char temp[30] = {'\0'}, intemp[30] = {'\0'}, IsStop;							//temporary variables to store data.
		infile >> IsStop; 
		infile.unget();

		if (IsStop == 'X') {
			break;																		//break the loop if X is read.
		}
		infile.getline(temp, 30);														//store the data into temo.

		/*Format the outputfile*/
		outfile << "                                   CONVERSION DISPLAY" << endl << endl;
		outfile << setw(20) << right << "Infix Expression" << setw(15) << "" << setw(25)<<left<<"Postfix Expression" << left << "Stack Contents(Top to Bottom)" << endl<<endl;

		/*Convert the Infix to Postfix*/
		IntoPost(outfile, temp, intemp, Stack1);
		Stack1.~StackController();														//destroy the stack.
		outfile << endl<<endl<<endl;

		/*Format the outputfile*/
		outfile << "                                   EVALUATION DISPLAY" << endl << endl;
		outfile << setw(30) << right << "Postfix Expression" << setw(30) << "" << "Stack Contents(Top to Bottom)" << endl<<endl;

		/*Evaluate the post fix data*/
		PostSoln(outfile, intemp, Stack2, finalsum);
		Stack2.~StackController();														//destroy the stack.
		outfile << endl;
		outfile << "ORIGINAL EXPRESSION AND THE ANSWER:" << setw(20) << right << temp << " = " << finalsum;
		outfile << endl<<endl<<endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		outfile << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	}

	Footer(outfile);																	//print	 the footer for the project.
	return 0;
}
//********************************************** End of Main Fuction *******************************************************//

//********************************************** IntoPost Function ***********************************************************//
void IntoPost(ofstream& Outfile, char PostExp[], char InExp[], StackController& Stack){ 
	//Function: IntoPost
	//Receives – the output file, infix expression, array for postfix expression, stack
	//Task - Processes the infix data and converts into Postfix
	//Returns - Array of postfix, stack and outputfile

	int j = 0;													
	OperationNode temp;
	char temparray[30] = { '\0' }, exp[30] = { '\0' }, random;
	bool condition;
	//Format for the begining of expression
	Outfile << setw(20) << right << PostExp << setw(15) << "" << setw(25) << left << "Empty" << left << "Empty" << endl;
	//Loop through all input data 
	for (int i = 0; i < 30; i++){	
		if (PostExp[i] == '\0')							//if the data ends, break the loop 
			break;
		else {
			for (int k = 0; k < 30; k++) {
				exp[k] = PostExp[i + k + 1];			//remove the proccecing char from the array and copy it onto another array
			}
			switch (PostExp[i]){						//process each char using switch 
			case '(':
				//create a node to push the data in
				OperationNode leftBracket;				
				leftBracket.OperatorData = '(';
				Stack.push(leftBracket);				//if data reads left bracket push into the stack
				break;
			case ')':
				Stack.RetrieveTop(temp);
				while (temp.OperatorData != '('){		//loop through the stack to search lft bracket
					Stack.pop(temp);
					InExp[j] = temp.OperatorData;
					j++;
					Stack.RetrieveTop(temp);
				}
				Stack.pop(temp);						//if data reads right bracket pop all the items until the left bracket
				break;
			case '*':
				//create a node to push the data in
				OperationNode multiplication;
				multiplication.OperatorData = '*';
				//Push if the stack isempty
				if (Stack.IsEmpty())
					Stack.push(multiplication);
				else {                                  
					Stack.RetrieveTop(temp);
					while (temp.OperatorData != '+' && temp.OperatorData != '-' && temp.OperatorData != '(') {
						Stack.pop(temp);
						InExp[j] = temp.OperatorData;
						j++;
						if (!Stack.IsEmpty())
							Stack.RetrieveTop(temp);
						else
							break;
					}
					Stack.push(multiplication);		//if data reads multiplication push or pop  the stack following the rules.
				}
				break;
			case '/':
				//create a node to push the data in
				OperationNode division;
				division.OperatorData = '/';
				//Push if the stack isempty
				if (Stack.IsEmpty())
					Stack.push(division);
				else {
					Stack.RetrieveTop(temp);
					while (temp.OperatorData != '+' && temp.OperatorData != '-' && temp.OperatorData != '(') {
						Stack.pop(temp);
						InExp[j] = temp.OperatorData;
						j++;
						if (!Stack.IsEmpty())
							Stack.RetrieveTop(temp);
						else
							break;
					}
					Stack.push(division);			//if data reads division Push or pop  the stack following the rules.
				}
				break;
			case '+':
				//create a node to push the data in
				OperationNode Addition;
				Addition.OperatorData = '+';
				//Push if the stack isempty
				if (Stack.IsEmpty()) {
					Stack.push(Addition);
				}
				else {
					Stack.RetrieveTop(temp);
					while (temp.OperatorData != '(' && !(Stack.IsEmpty())){
						Stack.pop(temp);
						InExp[j] = temp.OperatorData;
						j++;
						if (!Stack.IsEmpty())
							Stack.RetrieveTop(temp);
						else
							break;
					}
					Stack.push(Addition);		//if data reads Addition Push or pop  the stack following the rules.
				}
				break;
			case '-':
				//create a node to push the data in
				OperationNode Subtraction;
				Subtraction.OperatorData = '-';
				//Push if the stack isempty
				if (Stack.IsEmpty()) {
					Stack.push(Subtraction);
				}
				else {
					Stack.RetrieveTop(temp);
					while (temp.OperatorData != '(' && !(Stack.IsEmpty())) {
						Stack.pop(temp);
						InExp[j] = temp.OperatorData;
						j++;
						if (!Stack.IsEmpty())
							Stack.RetrieveTop(temp);
						else
							break;
					}
					Stack.push(Subtraction);	//if data reads Subtraction Push or pop  the stack following the rules.
				}
				break;
			default:							//all int value goes to the Infix expression array
				InExp[j] = PostExp[i];
				j++;
				break;
			}
		}
		if (exp[0] != '\0')						//if data in post fix expression still resides
			Outfile << setw(20) << right << exp << setw(15) << "" << setw(25) <<left<<InExp<< left; 
		else                                    //if there is no data in postfix expression
			Outfile << setw(20) << right << "Empty" << setw(15) << ""<<setw(25)<<left<<InExp<< left;
		//Check if the tack is empty
		if (!(Stack.IsEmpty())) {
			Stack.RetrieveTop(temp);			// get the top data into temp
			condition = true;					//if not empty set bool true for further processing
		}
		else {
			Outfile << "Empty" << endl;			//if empty print out Empty
			condition = false;
		}
		while (condition) {						//loop through stack to print 
			random = temp.OperatorData;			
			Outfile <<random<<" ";
			if (temp.next == NULL) {			//set condition to false if the dtaa ends
				Outfile << endl;
				condition = false;
			}
			else {								//keep the loop running
				temp = *temp.next;
			}
		}
	}
	while (!(Stack.IsEmpty())) {			//loop until the stak is empty adding char to infix expression and popping char int from stack.
		Stack.pop(temp);					//pop the top data and store it into temp	
		InExp[j] = temp.OperatorData;		//add the char from temp into array
		j++;
		if (!(Stack.IsEmpty())) {
			Stack.RetrieveTop(temp);		
			random = temp.OperatorData;
			//format the outputfile
			Outfile << setw(20) << right << "Empty" << setw(15) << "" << setw(25) <<left <<InExp << left << random << endl;
		}
		else {
			//format the outputfile
			Outfile << setw(20) << right << "Empty" << setw(15) << "" << setw(25)<<left << InExp << left << "Empty" << endl;
		}
	}
	return;
}
//********************************************** End of IntoPost Function ****************************************************//
//********************************************** PostSoln Function ***********************************************************//
void PostSoln(ofstream& Outfile, char PostExp[], StackController& Stack,int& Finalsum){
	//Function: PostSoln
	//Receives – the output file, infix expression, array for postfix expression, stack
	//Task - Processes the postfix data and evaluates the result
	//Returns - Array of solved infix, stack and outputfile
	OperationNode temp,temp1,temp2;
	string info = { '\0' };
	char exp[30] = {'\0'};
	bool condition;
	int sum = 0;
	//format for the output file/
	Outfile << setw(30) << right << PostExp << setw(30)<<""<<"Empty" << endl;
	//loop throgh all of the postfix expression.
	for (int i = 0; i < 30; i++){	
		if (PostExp[i] == '\0')		//Break the loop if no more postfix expression remains.
			break;
		else {
			for (int j = 0; j < 30; j++) {
				exp[j] = PostExp[i+j+1]; //remove the char from the infix expression and copy it onto another array.
			}
			switch (PostExp[i]){
			case '+':					//add the top two stack if data reads +
				//pop both stack and store into temporary nodes
				Stack.pop(temp1);
				Stack.pop(temp2);
				//process the data
				sum = temp2.OperandData + temp1.OperandData;
				OperationNode SumToPush;
				SumToPush.OperandData = sum;
				//push the processed data into the node
				Stack.push(SumToPush);
				break;
			case '-':					//sub the top two stack if data reads -
				//pop both stack and store into temporary nodes
				Stack.pop(temp1);
				Stack.pop(temp2);
				//process the data
				sum = temp2.OperandData - temp1.OperandData;
				OperationNode SubToPush;
				SubToPush.OperandData = sum;
				//push the processed data into the node
				Stack.push(SubToPush);
				break;
			case '/':					//divide the top two stack if data reads /
				//pop both stack and store into temporary nodes
				Stack.pop(temp1);
				Stack.pop(temp2);
				//process the data
				sum = (temp2.OperandData / temp1.OperandData);
				OperationNode divToPush;
				divToPush.OperandData = sum;
				//push the processed data into the node
				Stack.push(divToPush);
				break;
			case '*':					//Multiply the top two stack if data reads *
				//pop both stack and store into temporary nodes
				Stack.pop(temp1);
				Stack.pop(temp2);
				//process the data
				sum = temp2.OperandData * temp1.OperandData;
				OperationNode MultToPush;
				MultToPush.OperandData = sum;
				//push the processed data into the node
				Stack.push(MultToPush);
				break;
			default:
				OperationNode IntToPush;
				IntToPush.OperandData = int(PostExp[i]) - 48;//convert the char into int
				Stack.push(IntToPush);						 // push the int read into the stack
				break;
			}
			if (Stack.IsEmpty()) {							//check to see if all the data in stack has been processed
				info = "Empty";
				condition = false;							
				Outfile << info << endl;
			}
			else {
				condition = true;							//if data remains, set condition to true for further processing 
				Stack.RetrieveTop(temp);					// get the top data into the temo
			}
			if(exp[0] == '\0')
				/*format output*/
				Outfile << setw(30) << right << "Empty" << setw(30)<<""; 
			else
				/*format output*/
				Outfile << setw(30) << right << exp << setw(30)<<"";
			while (condition) {								//Run the loop until data remains.
				Outfile << temp.OperandData <<" ";
				if (temp.next == NULL) {
					Finalsum = temp.OperandData;
					Outfile << endl;
					break;
				}
				else {
					temp = *temp.next;
				}
			}
		}
	}
	return;
}
//********************************************** End of PostSoln Function ****************************************************//


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
	Outfile << setw(20) << "Assignment #4" << endl;
	Outfile << setw(35) << "---------------------------------- - ";
	Outfile << setw(35) << "---------------------------------- -  " << endl << endl;
	return;
}
//******************************************* End of Header Function ********************************************************//
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