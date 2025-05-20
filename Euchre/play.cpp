#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "deal.hpp"
#include "hand.hpp"
#include "card.hpp"

using namespace std;

#define MAX_SIZE 4

void get_trump(string trump, vector<Card *> &trump_list) {
    //Reads the text files into vectors so that we can check the order of stuff
    ifstream input(trump);
    string text;
    if (input.fail()) {
        cout << "Cannot open input file." << endl;
        exit(1);
    }

    if (input.is_open()) {
        while (getline(input, text)) {
            stringstream s(text);
            string name, suit;

            if (getline(s, name, ' ') && getline(s,suit)) {
                Card * temp = new Card(name, suit);
                trump_list.push_back(temp);
            }
                
        }
    }
    input.close();
}
int getTrumpRank(Card* card, vector<Card*> trump_list) {
    for (int i = 0; i<(int)trump_list.size(); i++) {
        if (card->getName() == trump_list[i]->getName() && card->getSuit() == trump_list[i]->getSuit()) {
            return i;
        }
        
    }
    return -1;
}
int getRoundWinner(string suit, string trump, vector<Card *> &middle, vector<Card*> &deck, vector<Card*> &trump_list) {
    Card* Highestcard = NULL;
    Card* temp = NULL;
    int owner;
    while((int)middle.size() > 0){
        //Need to modify the card method "isTrump"
        
        if (middle.back()->getSuit() != suit && middle.back()->isTrump(trump, trump_list) == 0) {
            //What happens if the card is not the suit that was led or trump
            temp = middle.back();
            middle.pop_back();
            deck.push_back(temp);
        }
        else if (middle.back()->getSuit() == suit && suit != trump){
            //If card is the suit that was led
            if (Highestcard == NULL) {
                //If first card then set highestcard to it
                Highestcard = middle.back();
                middle.pop_back();
            }
            else if (middle.back()->getRank() > Highestcard->getRank() && Highestcard->isTrump(trump, trump_list) == 0) {
                //If card is higher than highest and the highest is not trump
                temp = Highestcard;
                deck.push_back(temp);
                Highestcard = middle.back();
                middle.pop_back();
            }
            else {
                //If the card is lower than Highest than get rid of card
                temp = middle.back();
                middle.pop_back();
                deck.push_back(temp);
            }
            
        }
        else if (middle.back()->isTrump(trump, trump_list) == 1) {
            if (Highestcard == NULL) {
                //If this is the first card you are looking at
                Highestcard = middle.back();
                middle.pop_back();
                
            }
            else if (Highestcard->isTrump(trump, trump_list) == 0) {
                //If the highestcard is not trump, then set the card as highest
                temp = Highestcard;
                Highestcard = middle.back();
                middle.pop_back();
                deck.push_back(temp);
            }
            else if (Highestcard->isTrump(trump, trump_list) == 1){
                //If highest is trump
                if (getTrumpRank(middle.back(), trump_list) > getTrumpRank(Highestcard, trump_list)) {
                    //If the card rank is higher than the highest rank, then card is highest
                    temp = Highestcard;
                    Highestcard = middle.back();
                    middle.pop_back();
                    deck.push_back(temp);
                }
                else {
                    //If card rank is lower than highest, get rid of highest
                    temp = middle.back();
                    middle.pop_back();
                    deck.push_back(temp);
                }
            }
        }
    }
    owner = Highestcard->getOwner();
    deck.push_back(Highestcard);
    return owner;
}

void printTable(Hand players[], int size, vector<Card*> &middle, int player, string trump) {
    //Print how many cards your teammate has
    cout << "Teammate:  ";
    for (int i = 0; i < 5; i++) {
        if (i < players[(player + 2) % 4].size()) {
            cout << "? ";
        }
        else {
            cout << "  ";
        }
    }
    cout << endl;
    for (int i = 0; i < 5; i++) {
        cout << "    ";
        if (i < players[(player + 3)%4].size()) {
            cout << "?";
        }
        else {
            cout << " ";
        }

        cout << "   ";
        if (i == 2) {
            if (middle.size() > 0) {
                cout << "   ";
                middle[0]->display();
                cout << " " << middle[0]->getOwner();
                cout << "     ";
            }
            else {
                cout << "                  ";
            }
        }
        else if (i == 3) {
            if (middle.size() > 1) {
            //Check if the middle has more than 1 card
            cout << middle[1]->getOwner();
            middle[1]->display();
            }
            if (middle.size() > 2) {
            //Check if the middle has more than 2 cards
            middle[2]->display();
            cout << middle[2]->getOwner();
            }
            if (middle.size() < 2) {
                cout << "                  ";
            }
            else if (middle.size() == 2) {
                cout << "         ";
            }
        }
        else {
            cout << "                  ";
        }
        
        if (i < players[(player + 1) % 4].size()) {
            cout << "?";
        }
        else {
            cout << " ";
        }
        cout << endl;

        
    }
    cout << "Trump: " << trump << endl;

}

int round(int &dealer, Hand players[], int size, vector<Card*> &deck, vector<Card*> &middle, vector<Card*> &trump_list, string trump, int first) {
    string led = "";
    string response;
    Card * temp;
    int winner = -1;
    bool chosen = false;
    for (int i = 0; i < size; i++) {
        chosen = false;
        response = "";
        //Print the board state so player can see how many cards are in players hand
        //Also, print the cards that have been played
        printTable(players, size, middle, (first + i) % 4, trump);

        chosen = false;
        while (chosen == false) {
            cout << endl;
            players[(first + i) % 4].print();
            cout << "Player " << (first + i) % 4 << endl;
            cout << "Pick a card to play (Example 9 of Hearts):" << endl;
            getline(cin, response);
            stringstream s(response);

            string suit, name, junk;
            //Need to not allow people to play cards that aren't led or trump
            if (getline (s, name, ' ') && getline(s, junk, ' ') && getline(s, suit)) {
                if (players[(first + i) % 4].checkSuit(led, suit, trump, trump_list, name) == 1) {
                    temp = players[(first + i) % 4].delete_node(name, suit);
                }
                else {
                    temp = NULL;
                    cout << "Error: Need to follow suit" << endl;
                }
                //If the delete_node was succesful put the card in the middle
                if (temp != NULL) {
                    temp->setOwner((first + i) % 4);
                    
                    middle.push_back(temp);
                    chosen = true;
                }
            }
            else if (response == "Quit" || response == "quit") {
                cout << "Quitting Game..." << endl;
                exit(1);
            }
            else {
                cout << "Error: Incorrect Format" << endl;
            }
            
        }
        //If it is the first person in a round the suit led is
        //the suit that the first card is
        if (i == 0) {
            led = temp->getSuit();
            cout << led << endl;
        }
    }
    cout << led << endl;
    //You should debug getRoundWinner
    winner = getRoundWinner(led, trump, middle, deck, trump_list);
    cout << "Player " << winner << " wins the trick" << endl;
    return winner;

}

void full_round(int &dealer, Hand players[], int size, vector<Card*> &deck, vector<Card*> &middle, vector<Card*> &trump_list, string trump, int ordered, int &even_points, int &odd_points) {
    //The first person to lead is the person to the right of the dealer
    int first = dealer + 1;
    int winner = -1;
    int odd_wins = 0;
    int even_wins = 0;
    while (players[1].size() != 0) {
        winner = round(dealer, players, size, deck, middle, trump_list, trump, first);
        if (winner % 2 == 0) {
            even_wins++;
        }
        else{
            odd_wins++;
        }
        cout << "Even team tricks: " << even_wins << endl;
        cout << "Odd team tricks: " << odd_wins << endl;
        //Change the person who leads to the person with the highest card
        first = winner;
    }
    if (ordered % 2 == 0) {
        if (odd_wins == 0) {
            //If the even team got all tricks
            even_points += 2;
        }
        else if (odd_wins < 3) {
            //If even team got the majority of tricks
            even_points += 1;
        }
        else if (even_wins < 3) {
            //If even team didn't get the majority of tricks
            odd_points += 2;
        }
    }
    else if (ordered % 2 == 1) {
        if (even_wins == 0) {
            //If the odd team got all tricks
            odd_points += 2;
        }
        else if (even_wins < 3) {
            //If odd team got the majority of tricks
            odd_points += 1;
        }
        else if (odd_wins < 3) {
            //If odd team didn't get the majority of tricks
            even_points += 2;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: Not enough arguments." << endl;
        exit(1);
    }
    string file = argv[1];
    vector<Card*> deck;
    deck.reserve(24);
    //All the text files that have the trump lists
    string hearts = "heart_trump.txt";
    string diamonds = "diamond_trump.txt";
    string clubs = "clubs_trump.txt";
    string spades = "spades_trump.txt";
    string trump_lists[MAX_SIZE] = {hearts, diamonds, clubs, spades};
    //Vectors that will hold the order of the trump
    vector<Card*> heart_trump, diamond_trump, club_trump, spade_trump;
    get_trump(hearts, heart_trump);
    get_trump(diamonds, diamond_trump);
    get_trump(clubs, club_trump);
    get_trump(spades, spade_trump);
    //Variable to contain what suit was led first
    string led = "";
    //Vector of the cards in the middle
    vector<Card*> middle;
    int dealer = 0;
    int ordered = 0;
    string trump = "";
    int odd_points = 0;
    int even_points = 0;


    get_deck(file, deck);
    shuffle(deck);

    Hand players[MAX_SIZE];

    while (odd_points < 10 && even_points < 10) {
        //Shuffle and deal
        shuffle(deck);
        deal_hand(deck, players, MAX_SIZE);
        sort_hands(players, MAX_SIZE);
        //Bid
        trump = bid(players, MAX_SIZE, deck, dealer, ordered);
        //Gameplay loop
        if (trump == "Hearts") {
            full_round(dealer, players, MAX_SIZE, deck, middle, heart_trump, trump, ordered, even_points, odd_points);
        }
        else if (trump == "Diamonds") {
            full_round(dealer, players, MAX_SIZE, deck, middle, diamond_trump, trump, ordered, even_points, odd_points);
        }
        else if (trump == "Spades") {
            full_round(dealer, players, MAX_SIZE, deck, middle, spade_trump, trump, ordered, even_points, odd_points);
        }
        else if (trump == "Clubs") {
            full_round(dealer, players, MAX_SIZE, deck, middle, club_trump, trump, ordered, even_points, odd_points);
        }
        //Print Points
        cout << "Points:" << endl;
        cout << "Odd team: " <<odd_points << endl;
        cout << "Even team: " <<even_points << endl;

        dealer = (dealer + 1) % 4;
        //Collect any left over cards just in case
        collect(players, deck, MAX_SIZE);
    }
    /*
    deal_hand(deck, players, MAX_SIZE);
    sort_hands(players, MAX_SIZE);

    trump = bid(players, MAX_SIZE, deck, 0, ordered);
    if (trump == "Hearts") {
        full_round(dealer, players, MAX_SIZE, deck, middle, heart_trump, trump, ordered, even_points, odd_points);
    }
    else if (trump == "Diamonds") {
        full_round(dealer, players, MAX_SIZE, deck, middle, diamond_trump, trump, ordered, even_points, odd_points);
    }
    else if (trump == "Spades") {
        full_round(dealer, players, MAX_SIZE, deck, middle, spade_trump, trump, ordered, even_points, odd_points);
    }
    else if (trump == "Clubs") {
        full_round(dealer, players, MAX_SIZE, deck, middle, club_trump, trump, ordered, even_points, odd_points);
    }
    cout << odd_points << endl;
    cout << even_points << endl;


    collect(players, deck, MAX_SIZE);
    */
    stow_deck(file, deck);
    
    

}