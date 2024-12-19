package com.example.game;

import com.example.characters.*;


// Strategy: differnet strategies of setting up a game
public interface GameSetup {
	void setup(Knight[] knights, Ogre[] ogres, int nKnights, int nBraveKnights, int nBadOgres);	
}
