package com.example.game;

public class ClashReport implements ClashFollower {
	Game game;
	
	public ClashReport(Game game) {
		this.game = game;
	}
	
	public void inform() {
		int knightsEnergy = 0;
		int ogresEnergy = 0;

		for (int i = 0; i < game.getNumberOfWarriors(); ++i) {
			knightsEnergy += game.getKnight(i).getEnergy();
			ogresEnergy += game.getOgre(i).getEnergy();
		}
		
		System.out.println("!!! Knights - Ogres " + knightsEnergy + ":" + ogresEnergy + " !!!");
	}
}
