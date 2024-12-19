package game;

public class ClashReport implements ClashFollower {
	Game game;
	
	public ClashReport(Game game) {
		this.game = game;
	}
	
	public void inform() {
		int knightsEnergy = 0;
		int ogresEnergy = 0;

		for (int i = 0; i < game.numberOfWarriors; ++i) {
			knightsEnergy += game.knights[i].getEnergy();
			ogresEnergy += game.ogres[i].getEnergy();
		}
		
		System.out.println("!!! Knights - Ogres " + knightsEnergy + ":" + ogresEnergy + " !!!");
	}
}
