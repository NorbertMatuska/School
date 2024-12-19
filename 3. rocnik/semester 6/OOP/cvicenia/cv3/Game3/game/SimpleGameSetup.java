package game;

import characters.*;

public class SimpleGameSetup implements GameSetup {
	public void setup(Knight[] knights, Ogre[] ogres, int nKnights, int nBraveKnights, int nBadOgres) {
		int numberOfWarriors = nKnights + nBraveKnights;
		
		for (int i = 0; i < nKnights; ++i){
			knights[i] = new Knight(80, new IronSword(i));
		}

		for (int i = nKnights; i < numberOfWarriors; ++i){
			knights[i] = new BraveKnight(100, new LightSword(i));
		}

		for (int i = 0; i < nBadOgres; ++i){
			ogres[i] = new BadOgre(100);
		}
		
		for (int i = nBadOgres; i < numberOfWarriors; ++i){
			ogres[i] = new Ogre(100);
		}
	}
}
