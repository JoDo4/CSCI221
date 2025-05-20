#include <iostream>
#include <string>
#include "card.hpp"

 using namespace std;
        //constructors
        Card::Card(string n, string s, int r) {
            name = n;
            suit = s;
            rank = r;
            owner = -1;
            next = NULL;
            previous = NULL;
        }

        Card::Card(string n, string s) {
            name = n;
            suit = s;
            rank = 0;
            owner = 0;
            next = NULL;
            previous = NULL;
        }

        Card::~Card() {
            cout << "Card deleted" << endl;
        }
        //Get Functions
        string Card :: getName() {
            return name;
        }

        string Card::getSuit() {
            return suit;
        }

        int Card::getRank() {
            return rank;
        }

        Card * Card :: getNext() {
            return next;
        }

        Card * Card :: getPrevious() {
            return previous;
        }

        int Card :: getOwner() {
            return owner;
        }

        bool Card::isTrump(string trump, vector<Card*> list) {
            if (suit == trump) {
                
                return 1;
            }
            else if (name == "Jack") {
                if (suit == list[5]->getSuit()) {
                    
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                return 0;
            }
        }

        

        //Setting Functions
        void Card::setName(string n) {
            name = n;
        }

        void Card::setSuit(string s) {
            suit = s;
        }

        void Card::setRank(int r) {
            rank = r;
        }

        void Card::setNext(Card * newNext) {
            next = newNext;
        }

        void Card::setPrevious(Card* newPrevious) {
            previous = newPrevious;
        }

        void Card :: setOwner(int o) {
            owner = o;
        }

        void Card::display() {
            if (rank > 2) {
                cout << "[" << name[0] << " of " << suit[0] << "]";

            }
            else {
                cout << "[" << name << " of " << suit[0] << "]";
            }
        }
        