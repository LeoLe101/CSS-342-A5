/*
 CSS 342 Assignment 5
 Purpose:           Create a linked list header class
 Implementation     This class will initialize all the constructors, deconstructor
 and all the basic functions of a linked list needs
 Compilation:       To compile the project, make sure to include
                    all of these library before run:
                    #include <stdio.h>
                    #include <iostream>
                    #include "Node.hpp"
                    compile using this command:
                    g++ -std=c++11 *.cpp *.hpp
 
 @file LinkedList.hpp
 @author Leo Le
 @version 1.0   11/30/2017
 */

#include <stdio.h>
#include <iostream>
using namespace std;

/**
 Initialize the struct for Node and its data
 */
template <class Object>
struct Node
{
    Object data;    //data in the current Node
    Node* next;     //next Node in the list
};


/**
 Initialize the header class of the Linked List
 */
template <class Object>
class LinkedList{
public:
    //default constructor, deconstructor and copy constructor
    LinkedList();
    LinkedList(const LinkedList<Object>& copyList);
    ~LinkedList();
    
    //basic functions of linked list
    int insert(Object dat, int position);
    int append(Object dat);
    int remove(int position);
    bool isEmpty() const;
    void clear();
    
    //getter
    Node<Object>* getHeadNode() const;//Maybe not need
    int getSize() const;
    
    //featured functions
    void printMember() const;
    void ReverseIterative();
    void ReverseRecursive(Node<Object>* prevNode, Node<Object>* head);
    
    
private:
    //initialize private varaibles
    Node<Object>* headNode; //first node of the list
    Node<Object>* tailNode; //last noed of the list
    int size;               //size of the list
};



/* --------------------------------------------------------------------
 CSS 342 Assignment 5
 Purpose:           Create a linked list class
 Implementation     This class program all the functionality
                    of the constructors, deconstructor and all
                    the basic functions of the linked list
 Compilation:       To compile the project, make sure to include
                    all of these library before run:
                    #include <stdio.h>
                    #include <iostream>
                    compile using this command:
                    g++ -std=c++11 *.cpp *.hpp
 
 @file LinkedList.cpp
 @author Leo Le
 @version 1.0   11/30/2017
 */

//constructors and deconstructor
/**
 Default constructor of the LinkedList class
 */
template <class Object>
LinkedList<Object>::LinkedList()
{
    //initialize an empty linked list
    headNode = nullptr;
    tailNode = nullptr;
    size = 0;
}

/**
 Copy constructor of the LinkedList class
 Copy all elements from other list to this list
 */
template <class Object>
LinkedList<Object>::LinkedList(const LinkedList<Object>& copyList)
{
    int i = 1;
    Node<Object>* tempNode = copyList.getHeadNode();
    if (tempNode == nullptr)
        headNode = nullptr;
    else{
        //iterate through the copyList and append it to the current list
        while (i <= copyList.getSize())
        {
            Object dat = tempNode->data; //put the data from the copyList to a variable
            append(dat);                 //append the new data
            tempNode = tempNode->next;   //move to next node in the list
            i++;
        }
    }
}

/**
 Deconstructor of the LinkedList class
 */
template <class Object>
LinkedList<Object>::~LinkedList()
{
    //deconstruct the whole linked list by remove all element
    clear();
}


//Implementation of the list
/**
 Insert the data to the list
 
 @return result The result of the insert
 0 - success | 1 - fail
 */
template <class Object>
int LinkedList<Object>::insert(Object dat, int position)
{
    //initialize variables
    int result = 0;
    Node<Object>* prevNode = new Node<Object>;
    Node<Object>* insertNode = new Node<Object>;
    Node<Object>* nextNode = new Node<Object>;
    
    //check if the position to insert is valid or not
    if (position < 1 || position > size + 1)
    {
        cout << "Invalid position to insert! Please give another position to insert." << endl;
        result = 1;
    }
    //check if insert at the head of the linked list
    else if (position == 1)
    {
        //set the data and the next Node for the new created Node
        insertNode->data = dat;
        insertNode->next = headNode;
        headNode = insertNode;
    }
    
    //check if insert at the end of the linked list
    else if (position <= size)
    {
        //set the data and the next Node for the new created Node
        insertNode->data = dat;
        insertNode->next = NULL;
        tailNode->next = insertNode;
        tailNode = insertNode;
    }
    
    //insert at that particular position
    else
    {
        //start at the beggining of the linked list
        nextNode = headNode;
        //iterate to the previous Node of the position to be inserted and set as prevNode
        for (int advanceTo = 1; advanceTo < position; advanceTo++)
        {
            prevNode = nextNode; //the previous Node of the Node at the position
            nextNode = nextNode->next; //the Node at the position
        }
        //set the next Node of previous to the inserted Node
        prevNode->next = insertNode;
        //set the data and the next Node for the new created Node
        insertNode->data = dat;
        //set the next Node of the inserted Node to the next Node in the list
        insertNode->next = nextNode;
    }
    
    //increment the size of the list
    size++;
    
    //result = 0, the insert is successfully inserted
    //result = 1, the insert is failed
    return result;  //end function
}

/**
 Append the data to the list
 
 @return result The result of the append
 0 - success | 1 - fail
 */
template <class Object>
int LinkedList<Object>::append(Object dat)
{
    //initialize variables
    Node<Object>* appendNode = new Node<Object>;
    
    //set the data and the next Node for the new created Node at the end of the list
    appendNode->data = dat;
    appendNode->next = NULL; //next always null due to it is at the end of the list
    
    //check if the list is initialized or not
    if (headNode == NULL)
    {
        //initialize the first data in the list
        headNode = appendNode;
        tailNode = appendNode;
    }
    
    //append the data to the end of the list
    else
    {
        //point the next Node of the last Node to the appended Node instead of Null
        tailNode->next = appendNode;
        //set tail Node to the new appended Node
        tailNode = appendNode;
    }
    
    //increment the size of the list
    size++;
    return 0;       //end function
}

/**
 Remove the data from the list
 
 @return result The result of the remove
 0 - success | 1 - fail
 */
template <class Object>
int LinkedList<Object>::remove(int position)
{
    //initialize variables
    int result = 0;
    Node<Object>* prevNode = new Node<Object>;
    Node<Object>* removeNode = new Node<Object>;
    
    //check if the position to remove is valid or not
    if (position < 1 || position > size)
    {
        cout << "Invalid position to remove! Please give another position to remove." << endl;
        result = 1;
    }
    
    //remove at the begging of the list
    else if (position == 1)
    {
        removeNode = headNode;
        headNode = headNode->next;
        delete headNode;
    }
    //remove at the end of the list
    else if (position == size)
    {
        //start at the beggining of the linked list
        removeNode = headNode;
        //iterate to the previous Node of the position to be removed and set as prevNode
        for (int advanceTo = 1; advanceTo < position; advanceTo++)
        {
            prevNode = removeNode; //the previous Node of the Node at the position
            removeNode = removeNode->next; //the Node at the position
        }
        tailNode = prevNode;
        prevNode->next = nullptr;
    }
    
    //remove at that particular position
    else
    {
        //start at the beggining of the linked list
        removeNode = headNode;
        //iterate to the previous Node of the position to be inserted and set as prevNode
        for (int advanceTo = 1; advanceTo < position; advanceTo++)
        {
            prevNode = removeNode; //the previous Node of the Node at the position
            removeNode = removeNode->next; //the Node at the position
        }
        //set the next Node of previous Node to the next Node of the remove Node
        prevNode->next = removeNode->next;
    }
    
    //delete the Node on the position selected
    removeNode->next = nullptr;
    removeNode = nullptr;
    delete removeNode; //deallocate the memory for that Node
    
    //decrement the size of the list
    size--;
    
    //result = 0, the remove is successfully inserted
    //result = 1, the remove is failed
    return result;
}

/**
 Get the size of this linked list
 
 @return size the size of the linked list
 */
template <class Object>
int LinkedList<Object>::getSize() const
{
    return size;
}

/**
 Get the size of this linked list
 
 @return size the size of the linked list
 */
template <class Object>
Node<Object>* LinkedList<Object>::getHeadNode() const
{
    return headNode;
}

/**
 Check when the linked list is empty
 
 @return true or false depending on the linked list is empty of not
 */
template <class Object>
bool LinkedList<Object>::isEmpty() const
{
    return (size == 0);
}

/**
 Clear all the elements in the linked list
 */
template <class Object>
void LinkedList<Object>::clear()
{
    //iterate backward to remove all elements from the linked list
    for (int i = 1; i < size; i++)
    {
        remove(1);  //remove the first element every iteration
    }
}

/**
 Print all the members of the linked list
 */
template <class Object>
void LinkedList<Object>::printMember() const
{
    //make a Node that will iterate through the linked list
    Node<Object>* printNode = headNode;
    //check if the list is empty or not
    if (isEmpty())
    {
        cout << "The linked list is currently empty." << endl;
        return;
    }
    //print out all the members of the list if it is not empty
    while (printNode != NULL)
    {
        //print the data from the current Node
        cout << printNode->data << " | ";
        //move on to the next Node
        printNode = printNode->next;
    }
}

/**
 Iteratively rearrange the order of the nodes and make it reverse itself.
 Reverse the order of all the elements in the linked list
 */
template <class Object>
void LinkedList<Object>::ReverseIterative()
{
    //initialize variables
    Node<Object>* prevNode = new Node<Object>; 
    Node<Object>* currNode = new Node<Object>;
    Node<Object>* nextNode = new Node<Object>;
    
    //check if the list is empty or not
    if (isEmpty())
        return;
    
    //iteratively reverse the linked list
    else
    {
        prevNode = NULL;
        currNode = headNode;
        //move through the list
        while (currNode != nullptr) {
            //set tail Node at the end of the list to the head Node
            if (prevNode == headNode) {
                tailNode = prevNode;
            }
            //set the next Node of the current Node
            nextNode = currNode->next;
            //set the pointer of the current Node back to the previous Node
            //instead of pointing to the next Node
            currNode->next = prevNode;
            //set the previous Node to the current Node to iterate through the list
            prevNode = currNode;
            //move current Node to the next Node
            currNode = nextNode;
        }
        //set the head Node at the beginning of the list to the tail Node
        headNode = prevNode; //Note: currNode is now Null, so the previous Node
                             //      is the tail Node of the original linked list.
    }
}

/**
 Recursively rearrange the order of the nodes and make it reverse itself.
 Reverse the order of all the elements in the linked list
 
 @param prevNode The previous Node of the current Node
 @param head The head Node of the linked list to be reversed
 */
template <class Object>
void LinkedList<Object>::ReverseRecursive(Node<Object>* prevNode, Node<Object>* head)
{
    //end the recursive when it reaches Null or the list is not initialized
    if (head == nullptr)
    {
        //set the head Node to the previous node of
        //the current Node (which is Null)
        headNode = prevNode;
        return;
    }
    //recursively reverse through the list
    else
    {
        //set the first element in the list as the tail of the reversed list
        if (head == headNode) {
            tailNode = head;
        }
        //initialize variables
        Node<Object>* nextNode = head->next;
        head->next = prevNode;
        prevNode = head;
        //move to the next Node with the previous Node as current Node
        ReverseRecursive(prevNode, nextNode);
    }
    
}

// --------------------------------------------------------------------


