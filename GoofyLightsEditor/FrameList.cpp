/* Tim Sonnen       Lab #4
 * 9/25/2015
 *
 * FrameList.cpp
 *
 */

#include <iostream>

#include "FrameList.h"
#include "framestructure.h"
#include "FrameManipulation.h"  // for delete_RGB()

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
    }
    else{
        NodePtr temp = head;
        while (temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = p;
        // Previous pointer adjustment for new tail.
        p -> prev = temp;
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
    }
    else{
        head = p->next;
        p->next = NULL;
        delete_RGB(p->FrameData.data, this->row, this->col); // Delete Attached RGB structure
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
    
    if (pos == 0)
    {
        insert -> next = head;
        current = insert -> next;
        head = insert;
        // Adjustment of previous pointer for addition of a new head node.
        current -> prev = head;
        this->count++;
        return;
    }
    else
    {
        tempCount++;                                // Both tempCounter and current are refrencing
        current = current -> next;                  // position 1 in the list (head -> next)
        while (tempCount != pos)
        {
            current = current -> next;
            tempCount++;
        }
        insert -> next = current -> next;
        // Adjustment of previous pointer for addition of node x
        NodePtr p = current -> next;
        p -> prev = insert;
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
        delete_RGB(head->FrameData.data, this->row, this->col); // Delete Attached RGB structure
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
    delete_RGB(p->FrameData.data, this->row, this->col); // Delete Attached RGB structure
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
	t_FrameData *x = NULL;
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
			*x = head -> FrameData;
			return x;
		}
	}
	else
	{
		tempCount++;
		temp = temp -> next;
		while (tempCount != pos)
		{
			tempCount++;
			temp = temp -> next;
		}
			
		if (temp != NULL)
		{
			// Just checking to make sure no bounds have been crossed.
			*x = temp -> FrameData;
			return x;	
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
