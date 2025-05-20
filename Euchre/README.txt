Welcome to my final project! You will be playing a simplified version
of Euchre!!!!! When navigating the folder, you will see different driver
programs that I used to test my code. I will explaing the function of each
below.

1. card_hand_test.cpp - This drvier programs purpose was to test my custom data structure
which is a doubly linked list. This was very early on in the project so the methods that 
I test are adding and deleting cards, sorting hands, and printing the hand. This program 
does not use any additional input or output files. compile by doing make card_hand_test and
to run it, it needs no outside files.

2. deal_hand.cpp - This program was the testing ground in which I figured out how I wanted
to implement shuffling and getting the deck. This needs to have a the deck_list.txt to work.
To compile do make deal_hand and include deck_list.txt to run the program.

3. bid_driver.cpp - After testing dealing I made a hpp file called deal.cpp to do bidding and dealing
and this driver program is to test this functionality. To test this I just kept on running the program
simulating doing the bid step. To compile just do make bid_driver and you need to include deck_list.txt
to run the program.

The main program is play.cpp and the user plays as all four players. For this project I was not enable
to do all the functions of Euchre so the user can not go alone, but everything else should be good.
The program has two main parts to play euchre, the bidding and the main gameplay. Bidding goes around 
to make trump, which makes a suit trump over other suits. The main gameplay is about placing down cards to 
get the highest. If their is no trump the order is normal with aces high. The order of trump is 9, 10, Queen,
King, Ace, Jack of the same color, and Jack of the suit. To test this program I ran it numerous times and
intentionally played cards that would edge cases.

