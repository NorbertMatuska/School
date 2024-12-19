package oop.model;

import java.util.HashMap;
import java.util.Map;

/**
 * The VotingSystem class manages the voting process for wines.
 */
public class VotingSystem {
    private Map<String, Wine> wines;
    private double costPerVote;

    /**
     * Constructs a new VotingSystem object with the specified cost per vote.
     *
     * @param costPerVote The cost per vote for the voting system.
     */
    public VotingSystem(double costPerVote) {
        wines = new HashMap<>();
        this.costPerVote = costPerVote;
    }

    /**
     * Adds a new wine to the voting system.
     *
     * @param wineName The name of the wine to be added.
     */
    public void addWine(String wineName) {
        if (!wines.containsKey(wineName)) {
            wines.put(wineName, new Wine(wineName));
        }
    }

    /**
     * Registers a vote for a wine, deducting the vote cost from the user's wallet.
     *
     * @param user     The user casting the vote.
     * @param wineName The name of the wine being voted for.
     * @return True if the vote is successfully cast, false otherwise.
     */
    public boolean castVote(User user, String wineName) {
        Wine wine = wines.get(wineName);
        if (wine != null && user.deductFundsFromWallet(costPerVote)) {
            wine.addVote();
            return true;
        }
        return false;
    }

    /**
     * Retrieves the map of wines managed by the voting system.
     *
     * @return A map containing the wines managed by the voting system.
     */
    public Map<String, Wine> getWines() {
        return wines;
    }
}
