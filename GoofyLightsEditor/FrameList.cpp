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
void FrameList::AddNode( t_FrameData n ){
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

        delete p;
    }
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
        head = insert;
    }
    else
    {
        tempCount++;                                // Both tempCounter and current are refrencing
        current = current -> next;                  // position 1 in the list
        while (tempCount != pos)
        {
            current = current -> next;
            tempCount++;
        }
        insert -> next = current -> next;
        current -> next = insert;
        return;
    }
}

void FrameList::DeleteNode_Middle(int pos){
    int temp = 0;
    
    if (head == NULL){
        // Error list is empty, do nothing and return.
        return;
    }
    
    NodePtr current = head;
    
    if (pos == 0){
        // Delete the head node.
        head = current -> next;
        delete(current);
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
    delete (current -> next);
    current -> next = p;
}

/*Returns the first node in the list */
t_FrameData FrameList::FirstNode(){
    return head->FrameData;
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
