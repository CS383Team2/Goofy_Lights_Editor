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
		NodePtr newHead = head;
		// p -> next = NULL 
		// The line above should be the cause of the seg faults, cannot assign
		// head = p -> next, and then assign p -> next = NULL, as this sets the new head to NULL.
		// which is also why the "if (head != NULL)" was not hitting correctly. 
		
        if (head != NULL)
            newHead -> prev = NULL; //this is causing a seg fault when I close -P
        // Delete Attached RGB structure here
        delete p;
    }
    this->count--;
}

void FrameList::AddNode_Middle(t_FrameData x, int pos){
    // indexing scheme to start at 0 to n where n == items in linked list
    // Node 0 is the head of the list while node (count - 1) is the tail
    int tempCount = 0;
	//unsigned int timeLinePos = 0;				// variable to store the nodes position in the time line, and adjust all successive time line positions after inserting a node in the list.
	//int i = 0;									// For loop counter.
    
    NodePtr current = head;
    NodePtr insert = new Node;
    insert -> FrameData = x;
    insert -> next = NULL;
    insert -> prev = NULL;
    
    if (head == NULL)
    {
        head = insert;
		//insert -> FrameData.Position = timeLinePos;
		UpdateTimeLine();
		// this -> count++;				NEEDED HERE????????????????
		return;
    }
    else if (pos == 0)
    {
		//timeLinePos = head -> FrameData.ID;

        insert -> next = head;
        insert -> prev = NULL;
        head  -> prev = insert;
        head = insert;
		
		current = head;
/*
		timeLinePos = 0;
		current -> FrameData.Position = timeLinePos;
		while (current -> next != NULL)
		{
			current = current -> next;
			timeLinePos = timeLinePos + 1;
			current -> FrameData.Position = timeLinePos;
		}
*/
		UpdateTimeLine();
        this->count++;
        return;
    }
	else if (pos > count)								// if pos > count, ADD NODE to the TAIL of the list, as pos is any number greater than the number of nodes in the linked list.
	{
		while (current -> next != NULL)
		{
			current = current -> next;
		}
		//timeLinePos = (current -> FrameData.Position) + 1;
		current -> next = insert;
		insert -> prev = current;
		//insert -> FrameData.Position = timeLinePos;
		UpdateTimeLine();
		return;
	}
    else
    {
        while (tempCount != pos - 1 && current != NULL)
        {
            current = current -> next;
            tempCount++;
        }
		//timeLinePos = current -> FrameData.Position;
        insert -> next = current -> next;
        // Adjustment of previous pointer for addition of node x
        if (current -> next != NULL)
        {
            NodePtr p = current -> next;
            p -> prev = insert;
        }
        // else if current -> next == null then insert == null (from above)

        // Adjustment of prev pointer for node added at position x
        current -> next = insert;
        insert -> prev = current;
		
/*
		while (current -> next != NULL)
		{
			current = current -> next;					// current is equal to insert (the new node) on the first iteration
			timeLinePos = timeLinePos + 1;
			current -> FrameData.Position = timeLinePos;
		}
*/
		UpdateTimeLine();
        this->count++;
        return;
    }
}

void FrameList::DeleteNode_Middle(int pos){
    
	//unsigned int timeLinePos = 0;					// variable used to updte the nodes position in the time line after a node is deleted.
    int i = 0;                              		// For loop counter.
	
    NodePtr current = head;

    if (head == NULL){
        // Error list is empty, do nothing and return.
        return;
    }
	
	if (pos > count)						// Return error, can't delete any mode greater then the total number of nodes in the linked list.
    {
		return;
	}
	else if (pos == count)					// Delete the tail node and return. NOTE No time line position updates are needed here.
	{
		for (i = 0; i <= pos - 1 &&  current != NULL; i++)
		{
			current = current -> next;
		}
		NodePtr p = current -> next;
		current -> next = NULL;
		// Delete attached RGB structures here.
		delete(p);
		return;
	}
    
    if (pos == 0){
        // Delete the head node.
		// Current = head here.
		
        head = current -> next;
        if (head != NULL)
		{
            head -> prev = NULL;
		}
		
        // Delete Attached RGB structure here
		//timeLinePos = current -> FrameData.Position;
        delete(current);
		
/*
		current = head;
		current -> FrameData.Position = timeLinePos;
		
		while (current -> next != NULL)
		{
			current = current -> next;
			timeLinePos = timeLinePos + 1;
			current -> FrameData.Position = timeLinePos;
		}
*/
		UpdateTimeLine();
        this->count--;
        return;
    }
    
    for (i = 0; current != NULL && i <= pos - 1; i++){
        current = current -> next;
    }
    
    if (current == NULL || current -> next == NULL){
        // the position given is greater than total number of nodes in the list.
		// Calling UpdateTimeLine here just in case, but I don't believe it is needed	-Kevin
		UpdateTimeLine();
        return;
    }
	i = 0;
    
    // if this point has been reached and the function has not returned, current -> next holds
    // the node to be deleted from the list.
    NodePtr p = current -> next -> next;
    // Adjustment of previous pointers.
    p -> prev = current;
	
	//timeLinePos = current -> FrameData.Position;					// Assign timeLinePos, to adjust the time line positions of all successive nodes.
	
    // Delete Attached RGB Structure here
    delete (current -> next);
    current -> next = p;
	
/*
	// Unique Time Line Position adjustments done after a node is deleted.
	while (current -> next != NULL)
	{
		current = current -> next;
		//timeLinePos = timeLinePos + 1;
		//current -> FrameData.Position = timeLinePos;
	}
*/
	UpdateTimeLine();
    this->count--;
    return;
}

// Added this function to do all of the time line adjustments in a stand alone function.
// This function will be called from the AddNode_Middle(), and DeleteNode_Middle(), before return.
// This function iterates through the FrameList and updates the Time Line Position index(s)
// after every add or delete.
void FrameList::UpdateTimeLine(){
	
	unsigned int timeLinePos = 0;
	NodePtr UpdatePositions = head;
	
	if (head == NULL)
	{
		// Error case, no need to update time line positions for an empty list.
		return;
	}
	else
	{
		if (UpdatePositions -> next == NULL)
		{
			// The head node is the only node in the list
			//only update the time line position of the head node and return.
			UpdatePositions -> FrameData.Position = timeLinePos;
			return;
		}
		else if (UpdatePositions -> next != NULL)
		{
			// There is at least 2 nodes, maybe more, in the list.
			//traverse  the list and update all time line positions.
			UpdatePositions -> FrameData.Position = timeLinePos;
			timeLinePos++;
			while (UpdatePositions -> next != NULL)
			{
				UpdatePositions = UpdatePositions -> next;
				UpdatePositions -> FrameData.Position = timeLinePos;
				timeLinePos++;
			}
			return;
		}
	}	
}

// Added function to search the lined list for node at position x
// same indexing scheme as before, passing 0 to this function refers to the head
// passing count - 1 to this function refers to the tail.
t_FrameData * FrameList::RetrieveNode_Middle(int pos){
	int tempCount = 0;
    t_FrameData *rtnVal = NULL;
    NodePtr current = head;

    // If list is empty
    if (head == NULL)
        return NULL;
	
	if (pos == 0)
    {
        rtnVal = &(head -> FrameData);
        return rtnVal;
	}
	else
    {
        while (tempCount != pos && current != NULL)
		{
			tempCount++;
            current = current -> next;
		}
			
        if (current != NULL)  // if exists and we are at pos
		{
			// Just checking to make sure no bounds have been crossed.
            rtnVal = &(current -> FrameData);
            return rtnVal;
		}
        else                  // If it does not exist and we overran our list size.
        {                     // List smaller than pos count
            return NULL;
		}
	}
}

/*Returns the first node in the list */
t_FrameData FrameList::FirstNode(){
    return head->FrameData;
}

/* Sets internal advance pointer back to head */
void FrameList::AdvanceListReset(){
    this->advPtr = head;
    return;
}

/* Advance one node through the list & return Framedata pointer*/
t_FrameData * FrameList::AdvanceList(){
    if (advPtr == NULL)
        return NULL;
    else {
        t_FrameData * rtnVal = &advPtr->FrameData; // Pointer to the address of FrameData
        this->advPtr = this->advPtr->next;        // Advance pointer
        return rtnVal;                            // return FrameData pointer
    }
}

/* Sets the row count */
void FrameList::SetRowCount(int r) {
    this->row = r;
}

/* Sets the column count */
void FrameList::SetColCount(int c){
    this->col = c;
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
        cout << "ID: " << p->FrameData.ID << "\tDur: " << p->FrameData.duration << endl;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << p->FrameData.squareData[i][j].square_RGB.red() << "," << p->FrameData.squareData[i][j].square_RGB.green()
                     << "," << p->FrameData.squareData[i][j].square_RGB.blue() << " : ";
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
