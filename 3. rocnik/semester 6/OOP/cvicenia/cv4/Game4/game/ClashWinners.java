package com.example.game;

public class ClashWinners implements ClashFollower {
	Game game;
	
	public ClashWinners(Game game) {
		this.game = game;
	}
	
	public void inform() {
		int knightsEnergy = 0;
		int ogresEnergy = 0;

		for (int i = 0; i < game.getNumberOfWarriors(); ++i) {
			knightsEnergy += game.getKnight(i).getEnergy();
			ogresEnergy += game.getOgre(i).getEnergy();
		}
		
		if (knightsEnergy > ogresEnergy) 
			System.out.println("*** Knights are winninig. ***");
		else
			System.out.println("*** Ogres are winninig. ***");			
	}
}
