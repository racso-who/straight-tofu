#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "Card.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "CompPlayer.h"

using namespace std;

class Game{
    public:
        void start();
    private:
		void initDeck();
		bool playersHaveCards();
        void shuffleDeck();
        void initPlayers(Player* list[]);
        vector<Card> deck_;
        vector<Card> table_;



};
