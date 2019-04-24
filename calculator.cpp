// Shane Spangenberg
// Section 2
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

class digit
{
    public:
    int data;
    digit *next = nullptr;
};

// Suggested functions
digit * loadNumber(ifstream & file);
int digcmp(digit * left, digit *right);
char getOperator(ifstream & file);
void writeNumber(digit * num, ofstream & file);
void deleteNumber(digit * num);
digit * addNumbers(digit * left, digit * right);
digit * subNumbers(digit * left, digit * right);
void writeNumRecurse(digit * num, ofstream & file);
void setNeg(digit * num);
void printNum(digit * num);
void printNumrecurse(digit * num);
void subCarry(digit * head, digit * prev);
int addCarry(digit * left, digit * right, int carry);
digit * addNode(int num, digit * head);
int getSizeDifference(digit * left, digit * right);
digit * addTail(digit * head, int num);
int getSize(digit * head);

int main() {
    digit * left, * right, * result;
    ifstream inFile ("largeNumbers.txt");
    ofstream outFile ("output.txt");
    char anOperator;
    while (!inFile.eof()){
        left=loadNumber(inFile);
        right=loadNumber(inFile);
        anOperator=getOperator(inFile);
        if(anOperator=='+')
        {
            result=addNumbers(left, right);
            writeNumRecurse(result, outFile);
        }
    }

    outFile.close();
    inFile.close();
deleteNumber(left);
deleteNumber(right);
deleteNumber(result);

    return 0;
}

/*
*  returns a number <0 || 0 || >0
*  <0 right number is larger
*  0  the numbers are equal
*  >0 left number is larger
*  only works if the number is stored in reverse order
*/
int digcmp(digit * left, digit * right){
    int result = 0;
    do
    {
        if (left->data - right->data == 0){
        } // take no action
        else {
            result = left->data - right->data;
        }
        left = left->next;
        right = right->next;

    } while (left != nullptr && right != nullptr);

    if (left == nullptr && right != nullptr) {
        // right number is larger
        result = -1;
    }

    if (left != nullptr && right == nullptr) {
        // left number is larger
        result = 1;
    }
    return result;
}

digit * loadNumber(ifstream & file){
  digit * head=nullptr;
  char number;
  int num;

while(file.get(number))  //while we can get the character in the text file...
{
  if(number=='\n')   //If the number in the text file is a new line then break.
  break;
  num=(int)number-'0';  //Casts the character from ASCII to int by subtracting
      //the '0' character decimal value from the character value inside number.
      //EX: Our first number is 1...in ASCII '1' is 49 as a decimal. Since '0'
      //in ASCII is 48 as decimal...49-48=1...Then '2' is 50 so 50-48=2. So on...

  digit * node = new digit;   //Creating the linked list node here.
  node->data=num; //set the data value for the newly created node as num.
  node->next=head;  //point the next ptr of the node to the head.
  head=node;    //set the head as the newly created node.
}
    return head;  //return the pointer that points to the
                          //first element in the linked list
}

char getOperator(ifstream & file){
char oper;
string line;
file.get(oper);
getline(file, line); //get the rest of the line
return oper;
}

void printNumrecurse(digit * num){
if(num==nullptr)  //Base Case: If our node is null, end the function.
{
  cout<<endl;
  return;
}
else      //Otherwise print the data value in the node.
{
  cout<<num->data;
  num=num->next;  //go to the next node.
  printNumrecurse(num); //call the function again.
}
}
//The print numrecurse does the same as printNum...
void printNum(digit * num){
    while(!num)
    {
      cout<<num->data;
      num=num->next;
    }
}

//This function is the same as printNumrecurse except it writes the numbers
//instead of printing them.
void writeNumRecurse(digit * num, ofstream & file) {
if(num==NULL)
{
  file<<endl;
  return;
}
else
{
  file<<num->data;
  num=num->next;
  writeNumRecurse(num, file);
}
}

void writeNumber(digit * num, ofstream & file){
    return;
}

//While our pointer is not NULL we delete the node.
//We also could've done this recursively.
void deleteNumber(digit * num){
  while(num!=NULL)
  {
    delete num;
    num=num->next;
  }
    return;
}

digit * addNumbers(digit * left, digit * right){
  int result, carry=0, sizedifference, size1, size2;
  digit * head=nullptr;

sizedifference=getSizeDifference(left, right);
//Gets the difference in size of the two linked lists.
if(getSize(left) < getSize(right))
{ //If the first linked list is smaller than the second...
  for(int i=0; i<sizedifference; i++)
  { //We add a however many 0s we need to make the two linked lists the same size.
      left=addTail(left, 0);
  }
}
else if(getSize(right)<getSize(left))
{
  for(int i=0; i<sizedifference; i++)
  {
    right=addTail(right, 0);
  }
}
//While we haven't reached the end of both of the linked lists...
  while(left!=NULL && right!=NULL)
  {
    digit * newnode=new digit;  //create a new linked list which will contain
                                //the result of adding the two numbers.
    if(((left->data)+(right->data))>9)
    { //If the two numbers needed to be added are greater than 9..Carry
      //the number.
      result=addCarry(left, right, carry);
      carry=(left->data+right->data)/10;  //We need to carry the remainder to
                                          //the next node.
      head=addNode(result, head);
    }
    else
    {
      //If the two numbers don't need to carry, add it to the linked list.
      result=left->data+right->data+carry;
      head=addNode(result, head);
      carry=0;  //Important to reset carry to 0 because we don't carry
                //another number in this case.
    }
    left=left->next;
    right=right->next;
  }

//Here we are checking if we need to carry the LAST number.
  if(carry==0)
  {
    return head;
  }
  else
  {
    head=addNode(carry, head);
    return head;
  }
}

//Gets the size of the linked list.
int getSize(digit * head)
{
  int count=0;
  while(head!=NULL)
  {
    count++;
    head=head->next;
  }
  return count;
}

//Adding a node to the tail.
digit * addTail(digit * head, int num)
{
  digit * node = new digit; //Declare a new node.
  node->data=num;         //Set the data field of the new node to num.
  digit * tail=head;  //Declare a new pointer and set it to the head of the list.
  if(head==NULL)  //If the linked list is empty just add the new node.
  {
    head=node;
  }
  else
  { //Otherwise loop to the end of the linked list and add the node to the end.
    while(tail->next!=NULL)
    {
      tail=tail->next;
    }
    tail->next=node;
  }
  return head;
}

//Returns the difference in size between the two linked lists.
int getSizeDifference(digit * left, digit * right)
{
  int size1=0, size2=0;
  while(left!=NULL)
  {
    size1++;
    left=left->next;
  }
  while(right!=NULL)
  {
    size2++;
    right=right->next;
  }
  if(size1>size2)
  {
    return(size1-size2);
  }
  else if(size2>size1)
  {
    return(size2-size1);
  }
  else
  {
    return 0;
  }
}

//Adds the node to the head of the linked list.
digit * addNode(int num, digit * head)
{
  digit * node=new digit;
  node->data=num;
  node->next=head;
  head=node;
  return head;
}

int addCarry(digit * left, digit * right, int carry)
{
  int result=left->data+right->data+carry;
  result=result-10; //Our result needs to be 1 number.
  return result;
}

void subCarry(digit * head, digit * prev){
    return;
}

digit * subNumbers(digit * left, digit * right){
    return nullptr;
}

void setNeg(digit * num){
    return;
}
