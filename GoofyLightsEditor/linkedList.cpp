/* Tim Sonnen       Lab #4
 * 9/25/2015
 *
 * linkedList.cpp
 *
 */

#include <iostream>

#include "linkedList.h"
#include "framestructure.h"

using namespace std;

/* Add an item to the front of the list*/
void LinkedList::AddNode( t_FrameData n ){
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
        p->next=head;
        head = p;
    }
}

/*Deletes the first node in the list*/
void LinkedList::DeleteNode(){
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

/*Returns the first node in the list */
t_FrameData LinkedList::FirstNode(){
    return head->FrameData;
}

/*Returns if the list is empty or not*/
int LinkedList::IsEmpty(){
    if(head == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void LinkedList::PrintNode(){
    NodePtr p = head;

    while(p != NULL){
        cout << "ID: " << p->FrameData.ID << "\tDur: " << p->FrameData.durration << endl;
        p = p->next;
    }
}
