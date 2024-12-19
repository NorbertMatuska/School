package characters;

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

	// if the responsibility to hit by a sword is on a knight, we have to provide the corresponding methods
	// and then make a decision according to the type of the sword in the attack() method
/*
	public void hitByIronSword(Ogre ogre) {
		if (getEnergy() >= ogre.getEnergy())
			ogre.setEnergy((int) (0.9 * ogre.getEnergy()));

		System.out.println("Knight - iron sword");
	}

	public void hitByLightSword(Ogre ogre) {
		if (getEnergy() >= ogre.getEnergy())
			ogre.setEnergy((int) (0.5 * ogre.getEnergy()));
		
		System.out.println("Knight - light sword");
	}
*/
	
	public void attack(Ogre ogre) {
/*
		if (sword instanceof IronSword)
			hitByIronSword(ogre);
		else if (sword instanceof LightSword)
			hitByLightSword(ogre);
		else {
		}
*/
		sword.hit(this, ogre);
		
		ogre.revenge(this); 
	}
		
	public int showSword() {
		return sword.getProductNumber();
	}
}
