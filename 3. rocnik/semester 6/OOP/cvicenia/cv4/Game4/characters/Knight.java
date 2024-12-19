package com.example.characters;

public class Knight implements Energy {
	private int energy;
	private int additionalEnergy;
	
	protected Sword sword;

	public Knight() {
	}
	public Knight(int energy) {
		setEnergy(energy);
	}	
	public Knight(int energy, Sword sword) {
		setEnergy(energy);
		this.sword = sword;
	}

	public void setEnergy(int energy) {
		this.energy = energy;
	}
	public void increaseEnergy(int energy) {
		this.energy += energy;
	}
	public void decreaseEnergy(int energy) {
		this.energy -= energy;
	}
	public int getEnergy() {
		return energy + additionalEnergy;
	}
	
	public void attack(Ogre ogre) {
		sword.hit(this, ogre);
		ogre.revenge(this); 
	}
	
	public int showSword() {
		return sword.getProductNumber();
	}
}
