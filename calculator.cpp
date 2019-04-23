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
        // implement program logic here
        left=loadNumber(inFile);
        right=loadNumber(inFile);
        anOperator=getOperator(inFile);
        if(anOperator=='+')
        {
            result=addNumbers(left, right);
        }
    }
    writeNumRecurse(result, outFile);
    outFile.close();
    inFile.close();
deleteNumber(left);
deleteNumber(right);
deleteNumber(result);
cout<<"test";
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
  if(number=='\n')   //If the number in the text file is a new line then break from the while loop.
  break;
  num=(int)number-'0';  //Casts the character from ASCII to int by subtracting the '0' character decimal value from the character value
                            // inside number.
                            //EX: Our first number is 1...in ASCII '1' is 49 as a decimal. Since '0' in ASCII is 48 as decimal...49-48=1.
                            //This should work for all numbers from 0-9.

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
file.get(oper);
return oper;
}

void printNumrecurse(digit * num){
if(num==nullptr)
{
  cout<<endl;
  return;
}
else
{
  cout<<num->data;
  num=num->next;
  printNumrecurse(num);
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

void writeNumRecurse(digit * num, ofstream & file) {
if(num==NULL)
{
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

void deleteNumber(digit * num){
  while(num->next!=NULL)
  {
    delete num;
    num->next=NULL;
    num=num->next;
  }
  num=NULL;
    return;
}

digit * addNumbers(digit * left, digit * right){
  int result, carry=0, sizedifference, size1, size2;
  digit * head=nullptr;

sizedifference=getSizeDifference(left, right);
if(getSize(left) < getSize(right))
{
  for(int i=0; i<sizedifference; i++)
  {
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

  while(left!=NULL && right!=NULL)
  {
    digit * newnode=new digit;  //create a new linked list which will contain
                                //the result of adding the two numbers.
    if(((left->data)+(right->data))>9)
    {
      result=addCarry(left, right, carry);
      carry=(left->data+right->data)/10;
      head=addNode(result, head);
    }
    else
    {
      result=left->data+right->data+carry;
      head=addNode(result, head);
      carry=0;
    }
    left=left->next;
    right=right->next;
  }

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

digit * addTail(digit * head, int num)
{
  digit * node = new digit;
  node->data=num;
  digit * tail=head;
  if(head==NULL)
  {
    head=node;
  }
  else
  {
    while(tail->next!=NULL)
    {
      tail=tail->next;
    }
    tail->next=node;
  }
  return head;
}

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
  result=result-10;
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
