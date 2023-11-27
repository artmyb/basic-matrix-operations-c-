// ceng301_hw02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

struct Node {
    int element;
    Node* next;
};

class List {
public:
    List() {
        head = nullptr;
        tail = nullptr;
    }
    bool isEmpty() const {
        if (head == nullptr) {
            return true;
        }
        return false;
    }
    void appendItem(int item) {
        Node* appended = new Node;
        appended->element = item;
        appended->next = nullptr;

        if (head != nullptr) {
            tail->next = appended;
        }
        else {
            head = appended;
        }
        tail = appended;
    }
    int getSize() {
        if (head == nullptr) {
            return 0;
        }
        else {
            int i = 0;
            Node* currentnode = head;
            while (currentnode != nullptr) {
                Node* tempnode = currentnode;
                currentnode = tempnode->next;
                i++;
            }
            return i;
        }
    }
    int getItem(int index) {
        if (index == 0) {
            return head->element;
        }
        else if (index == getSize()) {
            return tail->element;
        }
        else {
            int i = 0;
            Node* current = head;
            for (i;i < index; i++) {
                current = current->next;
            }
            return current->element;
        }
    }
    void removeOdds() {
        Node* current = head;
        Node* preceding = nullptr;
        Node* succeeding = nullptr;

        while (current != nullptr) {
            if (current->element % 2 == 1) {
                succeeding = current->next;

                if (preceding != nullptr) {
                    preceding->next = succeeding;
                }
                else {
                    head = succeeding;
                }

                delete current;
                current = succeeding;
            }
            else {
                preceding = current;
                current = current->next;
            }
        }

        // Update the tail pointer to the last element in the modified list
        tail = preceding;
    }

    bool isAscending() {
        Node* current = head;
        while (current->next != nullptr) {
            if (current->element > current->next->element) {
                return false;
            }
            current = current->next;
        }
        return true;
    }
    void grow2() {
        Node* current = head;
        int i = getSize();
        int k = 0;
        for (k; k < i;k++) {
            appendItem(current->element);
            current = current->next;
        }
        return;
    }
    void growNodeByNode(int n) {
        
        int size = getSize();
        for (size; size > 0; size--) {
            int i = 0;
            for (i; i < n;i++) {
                insertAt(size, getItem(size));
            }
        }
    }
    void insertAt(int index, int item) {
        int i = 0;
        Node* current = head;
        Node* temp = new Node;
        while (i < index) {
            i++;
            temp = current;
            current = temp->next;
        }
        Node* newone = new Node;
        temp->next = newone;
        newone->element = item;
        newone->next = current;
        return;
    }
    void fromFile(std::string fName) {
        std::ifstream thelist(fName);
        head = nullptr;
        tail = nullptr;
        int theitem;
        while (thelist>> theitem) {
            appendItem(theitem);
        }

    }
    void toFileR(std::string fName) {
        std::ofstream thelist(fName + ".txt");
        thelist << tail->element << std::endl;
        Node* currentlast = tail;
        Node* temp = nullptr;
        while (currentlast != head->next) {
            Node* current = head;
            while (current != currentlast) {

                temp = current;
                current = current->next;
            }
            
            thelist << temp->element << std::endl;
            currentlast = temp;
        }
        thelist << head->element << std::endl;
        return;
    }
    void toFile(std::string fName) {
        std::ofstream thelist(fName + ".txt");
        Node* current = head;
        while (current != nullptr) {
            thelist << current->element << std::endl;
            current = current->next;
        }
        return;
    }
    void printList() {
        Node* current = head;
        while (current != nullptr) {
            std::cout<< current->element << std::endl;
            current = current->next;
        }
        return;
    }
    void numToList(int num) {
        Node* current = head;
        Node* succeeding;
        while (current != nullptr) {
            succeeding = current->next;
            delete current;
            current = succeeding;
        }
        head = nullptr;

        int i = 0;
        std::string number = std::to_string(num);
        for (char c : number) {
            int figure = c - '0';
            appendItem(figure);
        }
        return;
    }
    void removeAt(int indexx) {
        int index = indexx - 1;
        if (head == nullptr) {
            return;
        }
        else if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            int i = 0;
            Node* current = head;
            Node* preceding = nullptr;
            Node* succeeding = nullptr;
            while (i < index) {
                i++;
                preceding = current;
                succeeding= current->next->next;
                current = current->next;
                
            }
            preceding->next = succeeding;
            delete current;
            
        }
    }
private:
    Node* tail;
    Node* head;
};

int main() {
    List mylinkedlist;

    
    mylinkedlist.fromFile("myLlist.txt");
    if (mylinkedlist.isEmpty() == true) {
        std::cout << "the list is empty." << std::endl;

    }
    else {
        std::cout << "the list is not empty." << std::endl;
    }
    std::cout << "size of the list: " << mylinkedlist.getSize() << std::endl;
    std::cout << "is the list ascending?: ";
    if (mylinkedlist.isAscending() == true) {
        std::cout << "yes" << std::endl;
    }
    else {
        std::cout << "no" << std::endl;
    }
    std::cout << "original list:" << std::endl;
    mylinkedlist.printList();
    //mylinkedlist.appendItem(12);
    //mylinkedlist.appendItem(25);

    //mylinkedlist.removeAt(5);
    //mylinkedlist.removeAt(6);
    //mylinkedlist.insertAt(3,36);
    //mylinkedlist.removeOdds();

    //mylinkedlist.grow2();
    //mylinkedlist.growNodeByNode(3);
    //mylinkedlist.numToList(13543521);
    // 
    // 
    std::cout << "final list:" << std::endl;
    //mylinkedlist.printList();
    //mylinkedlist.toFile("new");
    mylinkedlist.toFileR("newr");
    
    
    return 0;
}
