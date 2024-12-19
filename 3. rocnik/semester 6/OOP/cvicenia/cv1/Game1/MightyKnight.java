public class MightyKnight extends Knight {

    void attack(Ogre ogre) {
        ogre.energy = (int) (0.6 * ogre.energy); // (int) just casts a float result into an int
        ogre.revenge(this); // this represents a reference to the current knight object

    }
}
