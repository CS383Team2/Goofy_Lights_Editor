/* Tim Sonnen       Lab #4
 * 9/25/2015
 *
 * FrameList.cpp
 *
 */

#include <iostream>

#include "FrameList.h"
#include "framestructure.h"

using namespace std;

/* Add an item to the end of the list*/
void FrameList::AddTail( t_FrameData n ){
    NodePtr p;

    //Allocate the node
    p = new Node;
    p->FrameData = n;
    p->next = NULL;

    //Check if the list is empty
    if(head == NULL ){
        head = p;
        tail = p;
        p->prev = NULL;
    }
    else{
        // next/prev pointers
        tail -> next = p;
        p -> prev = tail;

        // update tail pointer
        tail = p;
    }
    this->count++;
}

/*Function to delete all the entries in the Linked List upon program termination */
void FrameList::DeleteList(){
    while (head != NULL)
    {
        DeleteNode();
    }
}

/*Deletes the first node in the list*/
void FrameList::DeleteNode(){
    NodePtr p = head;

    if( p == NULL){
        /*Nothing. Error case.*/
        return;
    }
    else{
        head = p->next;
        p->next = NULL;
        head->prev = NULL;
        // Delete Attached RGB structure here
        delete p;
    }
    this->count--;
}

void FrameList::AddNode_Middle(t_FrameData x, int pos){
    // indexing scheme to start at 0 to n where n == items in linked list
    // Node 0 is the head of the list while node (count - 1) is the tail
    int tempCount = 0;
    
    NodePtr current = head;
    NodePtr insert = new Node;
    insert -> FrameData = x;
    insert -> next = NULL;
    insert -> prev = NULL;
    
    if (head == NULL)
    {
        head = insert;
    }

    else if (pos == 0)
    {
        insert -> next = head;
        insert -> prev = NULL;
        head  -> prev = insert;
        head = insert;
        this->count++;
        return;
    }
    else
    {
        while (tempCount != pos-1 && current != NULL)
        {
            current = current -> next;
            tempCount++;
        }
        insert -> next = current -> next;
        // Adjustment of previous pointer for addition of node x
        if (current -> next != NULL)
        {
            NodePtr p = current -> next;
            p -> prev = insert;
        }
        // else if current -> next == null then insert == null above

        // Adjustment of prev pointer for node added at position x
        current -> next = insert;
        insert -> prev = current;

        this->count++;
        return;
    }
}

void FrameList::DeleteNode_Middle(int pos){
    
    if (head == NULL){
        // Error list is empty, do nothing and return.
        return;
    }
    
    NodePtr current = head;
    
    if (pos == 0){
        // Delete the head node.
        head = current -> next;
        head -> prev = NULL;
        // Delete Attached RGB structure here 
        delete(current);
        this->count--;
        return;
    }
    
    for (int i = 0; current != NULL && i < pos - 1; i++){
        current = current -> next;
    }
    
    if (current == NULL || current -> next == NULL){
        // the position given is greater than total number of nodes in the list.
        return;
    }
    
    // if this point has been reached and the function has not returned, current -> next holds
    // the node to be deleted from the list.
    NodePtr p = current -> next -> next;
    // Adjustment of previous pointers.
    p -> prev = current;
    // Delete Attached RGB Structure here
    delete (current -> next);
    current -> next = p;
    this->count--;
    return;
}

// Added function to search the lined list for node at position x
// same indexing scheme as before, passing 0 to this function refers to the head
// passing count - 1 to this function refers to the tail.
t_FrameData * FrameList::RetrieveNode_Middle(int pos){
	int tempCount = 0;
    t_FrameData *rtnVal = NULL;
	NodePtr temp = head;
	
	if (pos == 0)
	{
		// return pointer to the head node's FrameData.
		if (head == NULL)
		{
			// no pointer to return Error.
            		return NULL;
		}
		else
		{
            *rtnVal = head -> FrameData;
            return rtnVal;
		}
	}
	else
    {
        while (tempCount != pos && temp != NULL)
		{
			tempCount++;
			temp = temp -> next;
		}
			
		if (temp != NULL)
		{
			// Just checking to make sure no bounds have been crossed.
            *rtnVal = temp -> FrameData;
            return rtnVal;
		}
		else
		{
            return NULL;
		}
	}
}

/*Returns the first node in the list */
t_FrameData FrameList::FirstNode(){
    return head->FrameData;
}

/* Advance one node through the list */
int FrameList::AdvanceList(){
    this->head = this->head->next;

    /* If we are out of the list return 0, else return 1 */
    if (this->head == NULL)
        return 0;
    else
        return 1;
}

/* Get the row count */
int FrameList::GetRowCount(){
    return this->row;
}

/* Get the column count */
int FrameList::GetColCount(){
    return this->col;
}

/*Returns if the list is empty or not*/
int FrameList::IsEmpty(){
    if(head == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void FrameList::PrintNode(){
    NodePtr p = head;
    /* sample output
        ID: 0	Dur: 123
        0,1,2 : 3,4,5 : 6,7,8 :
        9,10,11 : 12,13,14 : 15,16,17 :
        18,19,20 : 21,22,23 : 24,25,26 :
        27,28,29 : 30,31,32 : 33,34,35 :
        36,37,38 : 39,40,41 : 42,43,44 :
    */

    while(p != NULL){
        cout << "ID: " << p->FrameData.ID << "\tDur: " << p->FrameData.durration << endl;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << p->FrameData.data[i][j].R << "," << p->FrameData.data[i][j].G
                     << "," << p->FrameData.data[i][j].B << " : ";
            }
            cout << endl;
        }
        cout << endl;
        p = p->next;
    }
}

int FrameList::Size(){
    return this->count;
}

void FrameList::UpdateNode(t_FrameData d, int position)
{
   int pcount = 0;
   NodePtr current = head;
   NodePtr temp = new Node;
   NodePtr old;
   temp -> FrameData = d;
   temp -> next = NULL;
   if (position == 0)
      {
      if (head == NULL)
         head = temp;
      else if (head -> next == NULL)
         {
         head = temp;
         delete current;
         }
      else
     {
         old = current;
         current = current -> next;
         temp -> next = current;
     delete old;
         }
      }
   else
      {
      current = current -> next;
      pcount++;
      while (pcount != position-1)
         {
         current = current -> next;
         pcount++;
         }
      temp -> next = current -> next -> next;
      old = current -> next;
      current -> next = temp;
      delete old;
      }
   return;
}
