package oop.model;

/**
 * The Wine class represents a wine that can be voted on.
 */
public class Wine {
    private String name;
    private int votes;

    /**
     * Constructs a new Wine object with the specified name and zero initial votes.
     *
     * @param name The name of the wine.
     */
    public Wine(String name) {
        this.name = name;
        this.votes = 0;
    }

    /**
     * Retrieves the name of the wine.
     *
     * @return The name of the wine.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Retrieves the number of votes for the wine.
     *
     * @return The number of votes for the wine.
     */
    public int getVotes() {
        return this.votes;
    }

    /**
     * Increases the vote count for the wine by one.
     */
    public void addVote() {
        this.votes++;
    }
}

