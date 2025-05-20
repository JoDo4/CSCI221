#include <iostream>
#include <fstream>
#include <vector>
#include "hand.hpp"
#include "card.hpp"

using namespace std;

    Hand::Hand(){
        head = NULL;
    }

    Hand :: ~Hand(){
        Card * current = head;
        Card * temp;

        while (current != NULL) {
            temp = current;
            current = current ->getNext();
            delete temp;
        }
        head = NULL;
    }

    bool Hand :: isEmpty() {
        if (head == NULL) return 1;
        else return 0;
    }

    void Hand :: push(Card * new_card) {
        Card * temp = new_card;
        if (head == NULL) {
            head = temp;
        }
        else {
            temp ->setNext(head);
            head ->setPrevious(temp);
            head = temp;
        }
    }

    int Hand :: size() {
        Card * current = head;
        int count = 0;
        while (current != NULL) {
            count++;
            current = current->getNext();
        }

        return count;
    }

    Card * Hand :: delete_node(string name, string suit) {
        Card * current = head;

        bool found = false;
        bool loop = true;

        if (head == NULL) {
            cout << "There are no cards in hand." << endl;
            return head;
        }
        else if (head->getNext() == NULL) {
            head = NULL;
            return current;
        }
        else {
            while (loop == true) {
                if (current ->getName() == name && current ->getSuit() == suit) {
                    found = true;
                    loop = false;
                }
                else if (current -> getNext() == NULL) {
                    loop = false;
                }
                else {
                    current = current ->getNext();
                }
            }
            if (found == false) {
                cout << "Cound not find the card." << endl;
                return NULL;
            }
            else if (current ->getPrevious() == NULL) {
                head = current -> getNext();
                current->setNext(NULL);
                head->setPrevious(NULL);
                return current;
            }
            else if (current -> getNext() == NULL) {
                Card * temp = current ->getPrevious();
                temp ->setNext(NULL);
                current->setPrevious(NULL);
                return current;
            }
            else {
                Card * temp = current;
                Card * previous = current ->getPrevious();
                current = current->getNext();

                temp->setPrevious(NULL);
                temp->setNext(NULL);

                previous->setNext(current);
                current->setPrevious(previous);
                return temp;
            }
        }
    }

    Card * Hand :: pop() {
        if (head == NULL) {
            cout << "There are no cards in the hand." << endl;
            return NULL;
        }

        if (head->getNext() == NULL) {
            Card * current = head;
            head = NULL;
            return current;
        }

        Card * current = head;
        head = current->getNext();
        head->setPrevious(NULL);
        current->setNext(NULL);
        return current;


    }

    void Hand :: print() {
        Card * current = head;
        if (head == NULL) {
            cout << "There are no cards" << endl;
        }
        else {
            while (current != NULL) {
                current ->display();
                cout << " ";
                current = current ->getNext();
            }
            cout << endl;
        }
    }

    void Hand :: sort() {
        Card * current = head -> getNext();
        Card * previous = current -> getPrevious();
        Card * temp;
        Card * val = new Card(current->getName(), current->getSuit(), current->getRank());
        //Sort the ranks first
        for (current = head->getNext(); current != NULL; current = current ->getNext()) {
            previous = current -> getPrevious();
            temp = current;

            val->setName(current->getName());
            val->setSuit(current->getSuit());
            val->setRank(current->getRank());
            while (temp != head && previous->getRank() > val -> getRank()) {
                //Draw a diagram and actually visually do the sort
                //Maybe just change the ranks, not the actual nodes!

                //Moves the values of the previous card up ot the current one
                temp->setRank(previous->getRank());
                temp->setName(previous->getName());
                temp->setSuit(previous->getSuit());
                
                //Moves the position back one card
                temp = previous;
                if (temp != NULL) {
                    previous = temp ->getPrevious();
                }
                
            }
            //Assign the value of the current card to the new position
            temp->setName(val->getName());
            temp->setSuit(val->getSuit());
            temp->setRank(val->getRank());

        }

        //Sort the cards by suit
        //Reset the variables
        current = head -> getNext();
        previous = current -> getPrevious();
        val->setName(current->getName());
        val->setSuit(current->getSuit());
        val->setRank(current->getRank());

        for (current = head->getNext(); current != NULL; current = current ->getNext()) {
            previous = current -> getPrevious();
            temp = current;

            val->setName(current->getName());
            val->setSuit(current->getSuit());
            val->setRank(current->getRank());
            while (temp != head && previous->getSuit() > val -> getSuit()) {
                //Draw a diagram and actually visually do the sort
                //Maybe just change the ranks, not the actual nodes!

                //Moves the values of the previous card up ot the current one
                temp->setRank(previous->getRank());
                temp->setName(previous->getName());
                temp->setSuit(previous->getSuit());
                
                //Moves the position back one card
                temp = previous;
                if (temp != NULL) {
                    previous = temp ->getPrevious();
                }
                
            }
            //Assign the value of the current card to the new position
            temp->setName(val->getName());
            temp->setSuit(val->getSuit());
            temp->setRank(val->getRank());

        }
        // See if you can sort it with trump in mind
        
    }

    bool Hand::checkSuit(string led, string suit, string trump, vector<Card*> &list, string name) {
            Card * current = head;
            bool valid = true;
            if (led == "") {
                return valid;
            }
            if (suit == led) {
                return valid;
            }
            else if (suit != led){
                if (led == trump && suit == list[5]->getSuit() && name == "Jack") {
                    return true;
                }
                while (current != NULL) {
                    if (current->getSuit() == led) {
                        valid = false;
                        return valid;
                    }
                    current = current->getNext();
                }
                return valid;
            }
            return false;
        }
