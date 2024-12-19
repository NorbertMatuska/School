
public class Ogre {
	boolean hungry;
	int energy;
	
	void revenge(Knight knight) {
		if (energy > knight.energy)
			knight.energy = (int) (0.9 * knight.energy);
	}
}
