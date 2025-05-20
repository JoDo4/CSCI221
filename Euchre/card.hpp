#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>
using namespace std;

class Card {
    private:
        string name;
        string suit;
        int rank;
        int owner;
        Card * next;
        Card * previous;

        const int num_ranks = 6;

    public:
        Card(string n, string s, int r);

        Card(string n, string s);

        ~Card();
        //Get Functions
        string getName();

        string getSuit();

        int getRank();

        Card * getNext();

        Card * getPrevious();

        int getOwner();


        bool isTrump(std::string trump, vector<Card*> list);

        //Setting Functions
        void setName(std::string n);

        void setSuit(std::string s);

        void setRank(int r);

        void setNext(Card* newNext);

        void setPrevious(Card* newPrevious);

        void setOwner(int o);


        void display();





};

#endif