package characters;

public class BraveKnight extends Knight {

	public BraveKnight() {
		super();
	}
	public BraveKnight(int energy) {
		super(energy);
	}
	public BraveKnight(int energy, Sword sword) {
		super(energy, sword);
	}

/*
	public void hitByIronSword(Ogre ogre) {
		ogre.setEnergy((int) (0.8 * ogre.getEnergy()));

		System.out.println("Brave Knight - iron sword");
	}

	public void hitByLightSword(Ogre ogre) {
		ogre.setEnergy((int) (0.3 * ogre.getEnergy()));
		
		System.out.println("Brave Knight - light sword");
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
	}
}
