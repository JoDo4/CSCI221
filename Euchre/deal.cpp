#include <iostream>
#include <fstream>
#include <sstream>
#include "hand.hpp"
#include "card.hpp"
#include "deal.hpp"

using namespace std;
//Reads in the deck list and gets all the cards
bool get_deck(string deck_name,vector<Card *> &deck) {
    ifstream input(deck_name);
    string text;
    if (input.fail()) {
        cout << "Cannot open input file." << endl;
        exit(1);
    }

    if (input.is_open()) {
        while (getline(input, text)) {
            stringstream s(text);

            string name, suit, srank;
            if (getline(s, name, ' ') && getline(s, suit, ' ') && getline(s, srank)) {
                int rank = stoi(srank);
                Card * temp = new Card(name, suit, rank);
                deck.push_back(temp);
            }
            else {
                cout << "No cards left" << endl;
            }
        }
    }
    input.close();
    return 1;
}

void stow_deck(string deck_name, vector<Card *> &deck) {
    ofstream output(deck_name);
    if (output.fail()) {
        cout << "Cannot open output file." << endl;
        exit(1);
    }
    for (int i = 0; i < (int)deck.size(); i++) {
        output << deck[i] -> getName() << " " << deck[i]->getSuit() << " " << deck[i]->getRank();
        if (i != ((int)deck.size()-1)) {
            output << endl;
        }
    }

    output.close();
}

//Shuffles deck
void shuffle(vector<Card *> &deck) {
    srand(time(0));

    for (int i = 0; i < (int)deck.size(); i++) {
        int r = i + (rand() % (deck.size() - i));

        swap(deck[i], deck[r]);
    }
}

void sort_hands(Hand hands[], int size) {
    for (int i = 0; i < size; i++) {
        hands[i].sort();
    }
}

//Deals cards to 4 players until there are 5 cards in hand
void deal_hand(vector<Card *> &deck, Hand hands[], int size) {
    shuffle(deck);
    while (hands[3].size() < 5){
        for (int i = 0; i < size; i++){
            hands[i].push(deck.back());
            deck.pop_back();
        }
    }
}
//Retrieves all the cards from the hands so that the deck has everything
void collect(Hand hands[], vector<Card *> &deck, int size) {
    for (int i = 0; i < size; i++) {
        while (!hands[i].isEmpty()) {
        deck.push_back(hands[i].pop());
    }
    }
}
//Prints the table to cout showing the current player's hand
void print_for_bidding(Hand hands[], int size, int player, vector<Card*> &deck, int dealer) {
    if ((player + 2) % 4 == dealer) {
        cout << " D";
    }
    cout << " Team ";
    for (int i = 0; i<hands[(player+2)%4].size(); i++) {
        cout << "?";
    }
    cout << "    " << endl;
    if ((player + 3) % 4 == dealer) {
        cout << "D" << endl;
    }
    else if ((player + 1) % 4 == dealer) {
        cout << "               D" << endl;
    }
    for (int i = 0; i<hands[(player+1)%4].size();i++) {
        cout << "?";
        if (i == (hands[(player+1%4)].size()/2)) {
            cout << "   ";
            deck.back()->display();
            cout << "   ";
        }
        else {
            cout << "              ";
        }
        cout << "?" << endl;
    }
    cout << "Player " << player << "'s hand: ";
    hands[player].print();

}

//Goes around the table to pick what the trump is
string bid(Hand hands[], int size, vector<Card *> &deck, int dealer, int &ordered) {
    string trump = deck.back()->getSuit();
    string response = "";
    bool bid = false;


    for (int i = 0; i < 4; i++) {
        response = "";
        //Go around table asking players if they should order or pass
        print_for_bidding(hands, size, ((dealer + 1 + i) % 4), deck, dealer);

        //Get whether the player wants to pass or order
        bid = false;
        while (bid == false) {
            cout << "Pass or Order it?" << endl;
            getline(cin, response);
            if (response == "Order" || response == "order") {
                bid = true;
            }
            else if (response == "Pass" || response == "pass") {
                bid = true;
            }
            else if (response == "Quit" || response == "quit") {
                cout << "Quitting game..." << endl;
                exit(1);
            }
            else {
                cout << "Incorrect input" << endl;
            }
        }
        //check if they ordered
        if (response == "Order" || response == "order") {
            //Display the card that needs to be put into dealers hand
            deck.back()->display();
            cout << endl;
            //Display the dealer's hand
            hands[dealer].print();

            string card;
            bool swapped = false;
            //Get what the dealer wants to swap with
            while (swapped == false) {
                
                cout << "Player " << dealer << ": What card do you want to swap?" << endl;
                cout << "Example: 9 of Hearts" << endl;
                getline(cin, card);
                stringstream s(card);

                string suit, name, discard;
                Card * temp = deck.back();
                Card * removal;
                
                
                if(getline (s,name, ' ') && getline(s, discard, ' ') && getline(s, suit)){
                    removal = hands[dealer].delete_node(name, suit);
                    if (removal != NULL) {
                        deck.pop_back();
                        deck.push_back(removal);
                        hands[dealer].push(temp);
                        swapped = true;
                        hands[dealer].sort();
                        
                    }
                    
                }
                else {
                    cout << "Error: Incorrect format" <<endl;
                }
            }
            ordered = dealer + i + 1;
            return trump;
        }
        //Pass to next player
        else if ( (response == "Pass" || response == "pass")) {
            cout << "Passing to Player " << (dealer + 1 + i) % 4 << "..." << endl;

        }
        

    }
    //Second round if nobody ordered it
    
    for (int i = 0; i < size; i++) {
        response = "";
        //Print the table
        print_for_bidding(hands, size, ((dealer + 1 + i) % 4), deck, dealer);

        //See if player wants to pick the suit
        bid = false;
        while (bid == false) {
            cout << "Pass or Order a suit to make Trump?" << endl;
            cout << "Type Pass or Order" << endl;
            getline(cin, response);
            if ((dealer + 1 + i) % 4 == dealer) {
                if (response == "Order" || response == "order") {
                bid = true;
                }
                else if (response == "Pass" || response == "pass") {
                    cout << "Dealer can't pass if forced to pick a suit." << endl;
                }
                else if (response == "Quit" || response == "quit") {
                    cout << "Quitting Game..." << endl;
                    exit(1);
                }
                else {
                    cout << "Incorrect Input" << endl;
                }
            }
            else if ((dealer + 1 +i) % 4 != dealer) {
                if (response == "Order" || response == "order") {
                    bid = true;
                }
                else if (response == "Pass" || response == "pass") {
                    bid = true;
                }
                else if (response == "Quit" || response == "quit") {
                    cout << "Quitting Game..." << endl;
                    exit(1);
                }
                else {
                    cout << "Incorrect Input" << endl;
                }
            }
        }

        if (response == "Order" || response == "order") {
            bool pick = false;

            while (pick == false) {
                cout << "Player" << (dealer + 1 + i) << ": What suit should be trump?" << endl;
                cout << "Example: \"Spades\"" << endl;
                getline(cin, response);

                if (response == trump) {
                    cout << "You can't pick the suit you turned down" << endl;
                }
                else if (response == "Spades" || response == "Clubs" || response == "Hearts" || response == "Diamonds") {
                    cout << response << " is Trump" << endl;
                    trump = response;
                    pick = true;
                }
                else {
                    cout << "Error: Incorrect Input" << endl;
                }
            }
            ordered = dealer + i + 1;
            return trump;
        }
        else if (response == "Pass" || "pass"){
            cout << "Passing to Player" << (dealer + 1 + i) % 4 << "..." << endl;
        }


    }
    
    return "Error";
}