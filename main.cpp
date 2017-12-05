/*
 CSS 342 Assignment 5
 Purpose:           Create the main/driver class
 Implementation     This class will test all the functionalities 
                    of the linked list created by the student
 Compilation:       To compile the project, make sure to include
                    all of these library before run:
                    #include <stdio.h>
                    #include <iostream>
                    #include "LinkedList.hpp"
                    #include "Node.hpp"
                    compile using this command:
                    g++ -std=c++11 *.cpp *.hpp
 
 @file LinkedList.cpp
 @author Leo Le
 @version 1.0   11/30/2017
 */

#include <iostream>
#include <stdio.h>
#include "LinkedList.hpp"
using namespace std;


int main() {
    //initialize variables
    LinkedList<int> list1;
    LinkedList<int> list2;
    
    
    //print the member of the list
    cout << "The member of list1 before initialize: " << endl;
    list1.printMember();
    cout << endl << endl;
    
    //insert all the member of the list1 and print the list
    for (int i = 1; i <= 20; i++) {
        list1.insert(i, 1); //insert at the start of the list
    }
    cout << "The member of list1 after the insertion: " << endl;
    list1.printMember();
    cout << endl << endl;
    
    //append all the member of the list2 and print the list
    for (int j = 1; j <= 10; j++) {
        list2.append(j);    //append at the end of the list
    }
    cout << "The member of list2 after the append: " << endl;
    list2.printMember();
    cout << endl << endl;

    //use the copy constructor and print the list out
    LinkedList<int> copyList = LinkedList<int>(list1);
    cout << "The member of list after using copy constructor: " << endl;
    copyList.printMember();
    cout << endl << endl;
    
    //remove some members of both lists and print them out
    list2.remove(1);
    list2.remove(9);
    cout << "The member of list2 after removing some data: " << endl;
    list2.printMember();
    cout << endl << endl;
    
    list1.remove(2);
    list1.remove(4);
    list1.remove(7);
    cout << "The member of list1 after removing some data: " << endl;
    list1.printMember();
    cout << endl << endl;
    
    //iteratively reverse all the member in both of the list
    list1.ReverseIterative();
    cout << "The member of list1 after iteratively reversing all the data: " << endl;
    list1.printMember();
    cout << endl << endl;
    
    list2.ReverseIterative();
    cout << "The member of list2 after iteratively reversing all the data: " << endl;
    list2.printMember();
    cout << endl << endl;
    
    //recursively reverse all the member in the list
    copyList.ReverseRecursive(nullptr, copyList.getHeadNode());
    cout << "The member of list1 after recursively reversing all the data: " << endl;
    list1.printMember();
    cout << endl << endl;
    
    return 0; //end of the program

}
