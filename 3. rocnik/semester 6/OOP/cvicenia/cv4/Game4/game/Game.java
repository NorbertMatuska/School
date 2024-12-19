package com.example.game;
import com.example.characters.*;
import java.util.*;

public class Game {
	private Ogre[] ogres;
	private Knight[] knights;

	private int numberOfWarriors;

	private ArrayList<ClashFollower> clashFollowers = new ArrayList<>();
	
	public int getNumberOfWarriors() {
		return numberOfWarriors;
	}
	public Knight getKnight(int i) {
		return knights[i];
	}
	public Ogre getOgre(int i) {
		return ogres[i];
	}

	public void clash1on1(Knight knight, Ogre ogre) {
		knight.attack(ogre);
		informClashFollowers();
	}

	static int findEnergyDifference(Energy being1, Energy being2) {
		return being1.getEnergy() - being2.getEnergy();
	}

	public void createWarriors(int nKnights, int nBraveKnights, int nBadOgres, GameSetup gameSetup) {
		numberOfWarriors = nKnights + nBraveKnights;
		knights = new Knight[numberOfWarriors];
		ogres = new Ogre[numberOfWarriors];

		gameSetup.setup(knights, ogres, nKnights, nBraveKnights, nBadOgres);

		informClashFollowers();
	}
	
	public Game() {
	}

	public Game(int nKnights, int nBraveKnights, int nBadOgres, GameSetup gameSetup) {
		createWarriors(nKnights, nBraveKnights, nBadOgres, gameSetup);
	}

	public String clash() {
		String report = "";

		for (int i = 0; i < knights.length; ++i) {
			clash1on1(knights[i], ogres[i]);		
			report = report + (i + 1) + ":"
							+ "knight " + knights[i].getEnergy() + " / "
							+ "ogre " + ogres[i].getEnergy() + " / "
							+ knights[i].showSword()
							+ "\n";
		}

		informClashFollowers();

		return report;
	}
	
	public void followClash(ClashFollower clashFollower) {
		clashFollowers.add(clashFollower);
	}
	
	public void informClashFollowers() {
		for (ClashFollower clashFollower : clashFollowers)
			clashFollower.inform();
	}	
}
