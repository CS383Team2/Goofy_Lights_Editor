/*  Tim Sonnen        Lab #5
 *  9/24/2015
 *
 *  FrameList.h
 *  Class that holds a linked list
 */

#ifndef LINK_H
#define LINK_H

#include <iostream>
#include "framestructure.h"
class FrameList{
private:
    struct Node{
        t_FrameData FrameData;
        struct Node *next;
        struct Node *prev;
    };
    typedef struct Node* NodePtr;

    NodePtr head;
    NodePtr tail;
    int row, col;
    int count;

public:
    // Constructor
    FrameList(int r, int c){
        head = NULL;
        row = r;
        col = c;
        count = 0;
    }

    // Destructor
    ~FrameList(){
      FrameList::DeleteList();
    }                                                                                                                      
    // Add a node onto the end of the linked list.
    void AddTail(t_FrameData x);
	
    // Function will call DeleteNode for every item in the Linked List, and delete
    // the head node until all items in the linked list have been deleted.
    void DeleteList();
	
    // Delete the first node in the list.
    void DeleteNode();
	
    // Add node at position x
    // 0 will be the first node. 1 would be the 2nd node in the list.
    void AddNode_Middle(t_FrameData x, int pos);
	
    // Delete node at position x in the list
    // If pos == 0 this refers to the head node, and
    // If pos == count - 1 this refers to the tail node.
    void DeleteNode_Middle(int pos);

    // retrieve node at given position x.
    // If pos == 0 this refers to the head node and,
    // If pos == count - 1 this refers to the tail node.
    t_FrameData * RetrieveNode_Middle(int pos);
 
    // Return the first node found in the list
    t_FrameData FirstNode();

    // Advance one node in the list
    int AdvanceList();

    // Get the row count
    int GetRowCount();

    // Get the column count
    int GetColCount();
 
    // Output the values in the nodes, one integer per line. 
    void PrintNode();
 
    //Returns a value if the list is empty
    int IsEmpty();
 
    // Return a count of the number of nodes in the list.
	int Size();
	    
    // Updates frame data
    void UpdateNode(t_FrameData d, int position);
};
#endif
