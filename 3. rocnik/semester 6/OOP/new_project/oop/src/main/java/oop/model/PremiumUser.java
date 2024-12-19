package oop.model;

/**
 * The PremiumUser class represents a user with premium privileges in the system.
 * It inherits from the User class.
 */
public class PremiumUser extends User {
    /**
     * Constructs a new PremiumUser object with the specified name and password.
     *
     * @param name The name of the premium user.
     * @param pass The password of the premium user.
     */
    public PremiumUser(String name, String pass) {
        super(name, pass);
    }

    public boolean deductFundsFromWallet(double amount) {
        return true;
    }

    public void premiumUserAddWine(String wineName, VotingSystem votingSystem) {
        votingSystem.addWine(wineName);
    }

}
