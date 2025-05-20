#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "card.hpp"
#include "hand.hpp"

using namespace std;

void shuffle(vector<Card *> &deck) {
    srand(time(0));

    for (int i = 0; i < (int)deck.size(); i++) {
        int r = i + (rand() % (deck.size() - i));

        swap(deck[i], deck[r]);
    }
}

void collect(Hand &hand, vector<Card *> &deck) {
    while (!hand.isEmpty()) {
        deck.push_back(hand.pop());
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Not enough arguments." << endl;
        exit(1);
    }

    ifstream input(argv[1]);
    string text;
    if (input.fail()) {
        cout << "Cannot open input file." << endl;
        exit(1);
    }
    //Create the deck
    vector<Card *> vec;
    vec.reserve(24);

    //Create the players
    Hand player1;
    Hand player2;
    Hand player3;
    Hand player4;

    if (input.is_open()) {
        while (getline(input, text)) {
            stringstream s(text);

            string name, suit, srank;
            if (getline (s, name, ' ') && getline (s, suit, ' ') && getline (s, srank)) {
                int rank = stoi(srank);
                Card * temp = new Card(name, suit, rank);
                vec.push_back(temp);
            }
            else {
                cout << "No cards left" << endl;
            }
        }
    }
    input.close();
    //Shuffle deck
    shuffle(vec);
    for (int i = 0; i < 5; i++) {
        player1.push(vec.back());
        vec.pop_back();
        player2.push(vec.back());
        vec.pop_back();
        player3.push(vec.back());
        vec.pop_back();
        player4.push(vec.back());
        vec.pop_back();
    }
    //Display the deck
    for (int i = 0; i < (int)vec.size();i++) {
        vec[i]->display();
    }
    cout << endl;
    player1.print();
    player2.print();
    player3.print();
    player4.print();

    ofstream output(argv[1]);
    if (output.fail()) {
        cout << "Cannot open output file." << endl;
        exit(1);
    }

    if(output.fail()) {
        cout << "Cannot open output file." << endl;
    }
    //Put the players' hands into the deck
    collect(player1, vec);
    collect(player2, vec);
    collect(player3, vec);
    collect(player4, vec);

    cout << "Printing deck:" << endl;
    for (int i = 0; i < (int)vec.size();i++) {
        vec[i]->display();
    }
    //Put deck back into text file
    for (int i = 0; i < (int)vec.size(); i++) {
        output << vec[i]->getName() << " " << vec[i]->getSuit() << " " << vec[i]->getRank();
        if (i != ((int)vec.size()-1)) {
            output << endl;
        }
    }

    output.close();

    return 0;

}