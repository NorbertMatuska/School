package com.example.game;

import com.example.characters.*;

public class AlternateSwordsGameSetup implements GameSetup {
	public void setup(Knight[] knights, Ogre[] ogres, int nKnights, int nBraveKnights, int nBadOgres) {
		int numberOfWarriors = nKnights + nBraveKnights;
		
		for (int i = 0; i < nKnights; ++i){
			if (i % 2 == 0) // we evenly alternate kinds of swords
				knights[i] = new Knight(100, new LightSword(i));
			else
				knights[i] = new Knight(100, new IronSword(i));				
		}
		
		for (int i = nKnights; i < numberOfWarriors; ++i){
			if (i % 2 == 0)
				knights[i] = new BraveKnight(100, new LightSword(i));
			else
				knights[i] = new BraveKnight(100, new IronSword(i));				
		}
		
		for (int i = 0; i < nBadOgres; ++i){
			ogres[i] = new BadOgre(100);
		}
		
		for (int i = nBadOgres; i < numberOfWarriors; ++i){
			ogres[i] = new Ogre(100);
		}
		
	}
}
