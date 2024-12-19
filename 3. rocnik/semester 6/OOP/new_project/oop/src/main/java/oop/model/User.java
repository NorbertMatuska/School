package oop.model;

/**
 * Represents a user within the application. Each user has a name, password,
 * and a wallet for handling transactions. This class also provides methods for
 * interacting with the user's wallet and casting votes within the voting system.
 */
public class User {
    public String Name;
    public String Password;
    private Wallet wallet;

    /**
     * Constructs a new {@code User} with the specified name and password.
     * Initializes a new wallet for the user.
     *
     * @param name the name of the user.
     * @param pass the password of the user.
     */
    public User(String name, String pass) {
        this.Name = name;
        this.Password = pass;
        this.wallet = new Wallet(); // Each user has their own wallet
    }

    /**
     * Attempts to deduct a specified amount of funds from the user's wallet.
     *
     * @param amount the amount of funds to deduct.
     * @return {@code true} if the funds were successfully deducted, {@code false} otherwise.
     */
    public boolean deductFundsFromWallet(double amount) {
        return wallet.deductFunds(amount);
    }

    /**
     * Retrieves the wallet associated with this user.
     *
     * @return the {@link Wallet} instance belonging to this user.
     */
    public Wallet getWallet() {
        return wallet;
    }

}
