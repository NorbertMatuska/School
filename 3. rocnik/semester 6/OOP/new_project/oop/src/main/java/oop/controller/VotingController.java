package oop.controller;

import javafx.scene.control.Alert;
import javafx.stage.Stage;
import oop.model.*;
import oop.utils.UserSession;
import oop.view.DashboardView;
import oop.view.LoginView;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;

/**
 * The {@code VotingController} class manages the voting process within the application.
 * It interacts with the {@code VotingSystem} to cast votes for wines, initializes wines for voting
 * from a CSV file, and handles user wallet transactions related to voting.
 */
public class VotingController {
    private VotingSystem votingSystem;
    private DashboardView view;

    /**
     * Constructs a new {@code VotingController} with the specified view.
     * Initializes the voting system and the wines available for voting.
     *
     * @param view the {@code DashboardView} used to display voting results and messages to the user.
     */
    public VotingController(DashboardView view) {
        this.votingSystem = new VotingSystem(10.0);
        this.view = view;
        initializeWines();
    }

    /**
     * Initializes the list of wines available for voting from a predefined CSV file.
     */
    public void initializeWines() {
        this.initializeWinesFromCSV("wines.csv");
    }

    /**
     * Casts a vote for a specified wine by a user. Updates the view based on the success
     * or failure of the voting attempt.
     *
     * @param user the {@code User} attempting to cast a vote.
     * @param wineName the name of the wine the user is voting for.
     */
    public void castVote(User user, String wineName) {
        boolean success = votingSystem.castVote(user, wineName);
        if (success) {
            view.displaySuccess("Vote successful for " + wineName);
            view.updateWineList(votingSystem.getWines());

        } else {
            view.displayError("Vote failed for " + wineName + ". Check balance in your wallet.");
        }
    }


    /**
     * Returns the current map of wines available for voting.
     *
     * @return a {@code Map} where keys are wine names and values are {@code Wine} objects.
     */
    public Map<String, Wine> getWines() {
        return votingSystem.getWines();
    }

    /**
     * Initializes the wines available for voting by reading from a CSV file.
     * This method is designed to be used internally within the class.
     *
     * @param csvFilePath the path to the CSV file containing the list of wines.
     */
    public void initializeWinesFromCSV(String csvFilePath) {
        try (BufferedReader br = new BufferedReader(new FileReader(csvFilePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");

                votingSystem.addWine(values[0]);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Adds funds to the current user's wallet.
     * Displays a message indicating the success or failure of the operation.
     *
     * @param amount the amount to add to the user's wallet.
     */
    public void addFundsToUserWallet(double amount) {
        try {
            User currentUser = UserSession.getInstance().getCurrentUser();
            if (currentUser != null) {
                Wallet wallet = currentUser.getWallet();
                wallet.addFunds(amount);
                // Show confirmation message
                Alert alert = new Alert(Alert.AlertType.INFORMATION, "Funds added successfully!");
                alert.showAndWait();
            }
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Error adding funds: " + ex.getMessage());
            alert.showAndWait();
        }
    }

    /**
     * Displays the current balance of the user's wallet in an alert dialog.
     */
    public void showCurrentUserBalance() {
        try {
            User currentUser = UserSession.getInstance().getCurrentUser();
            if (currentUser != null) {
                Wallet wallet = currentUser.getWallet();
                double balance = wallet.getBalance();
                Alert alert = new Alert(Alert.AlertType.INFORMATION, "Current Balance: " + balance + "€");
                alert.showAndWait();
            }
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, "Error retrieving balance: " + ex.getMessage());
            alert.showAndWait();
        }
    }

    public boolean isPremium() {
        User currentUser = UserSession.getInstance().getCurrentUser();
        return currentUser instanceof PremiumUser;
    }

    public void evaluateVotes() {
        Map<String, Wine> wines = votingSystem.getWines();

        String wineWithMostVotes = null;
        int maxVotes = 0;

        for (Map.Entry<String, Wine> entry : wines.entrySet()) {
            String wineName = entry.getKey();
            Wine wine = entry.getValue();

            if (wine.getVotes() > maxVotes) {
                maxVotes = wine.getVotes();
                wineWithMostVotes = wineName;
            }
        }
        if (wineWithMostVotes != null) {
            view.displaySuccess("Wine with the most votes: " + wineWithMostVotes + "\nNumber of votes: " + maxVotes);
        } else {
            view.displayError("No votes recorded yet");
        }
    }

    public void premiumUserAddsWines(String wineName) {
        if (isPremium()) {
            PremiumUser currentUser = (PremiumUser) UserSession.getInstance().getCurrentUser();
            currentUser.premiumUserAddWine(wineName, votingSystem);
        }
        else {
            view.displayError("User is not on a premium account");
        }
    }
    /**
     * Logs out the current user and returns to the login view.
     *
     * @param stage the current stage that should be closed upon logging out.
     */
    public void logoutUser(Stage stage) {
        UserSession.getInstance().logout();
        stage.close();

        LoginView loginView = new LoginView();
        Stage loginStage = new Stage();
        loginView.start(loginStage);

    }

    /**
     * Initiates the process for a user to buy a premium account.
     * This method is a placeholder for future implementation.
     */
    public void buyPremium() {
        User currentUser = UserSession.getInstance().getCurrentUser();

    }
}

