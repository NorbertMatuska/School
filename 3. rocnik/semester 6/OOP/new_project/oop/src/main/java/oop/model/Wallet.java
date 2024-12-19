package oop.model;

/**
 * The Wallet class represents a wallet for managing funds.
 */
public class Wallet {
    private double balance;

    /**
     * Constructs a new Wallet object with zero initial balance.
     */
    public Wallet() {
        this.balance = 0;
    }

    /**
     * Adds funds to the wallet.
     *
     * @param amount The amount to be added to the wallet balance.
     * @throws IllegalArgumentException If the amount is not greater than 0.
     */
    public void addFunds(double amount) {
        if (amount > 0) {
            balance += amount;
        } else {
            throw new IllegalArgumentException("Amount must be greater than 0");
        }
    }

    /**
     * Deducts funds from the wallet.
     *
     * @param amount The amount to be deducted from the wallet balance.
     * @return True if funds are successfully deducted, false otherwise.
     */
    public boolean deductFunds(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            return true;
        } else {
            return false;
        }
    }

    /**
     * Retrieves the balance of the wallet.
     *
     * @return The current balance of the wallet.
     */
    public double getBalance() {
        return balance;
    }
}
