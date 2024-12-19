package oop.view;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import oop.model.User;
import oop.model.Wine;
import oop.controller.VotingController;
import java.util.Map;
import oop.utils.UserSession;
import oop.utils.UserSessionNotifier;
import oop.utils.UserSessionObserver;
import java.util.stream.Collectors;

/**
 * The {@code DashboardView} class is the main user interface for the application.
 * It extends {@link javafx.application.Application} and implements {@link oop.utils.UserSessionObserver}
 * to react to user session changes. It displays a list of wines available for voting,
 * allows users to cast votes, add funds, view their balance, buy premium features, and log out.
 */
public class DashboardView extends Application implements UserSessionObserver {
    private VotingController votingController;
    private ListView<String> wineListView = new ListView<>();
    private VBox layout = new VBox(10); // Use VBox for layout, with 10px spacing

    /**
     * Starts the primary stage of the application, setting up the layout and initializing components.
     *
     * @param primaryStage the primary stage for this application, onto which the application scene can be set.
     * @throws Exception if there is an issue starting the application.
     */
    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("Dashboard");

        votingController = new VotingController(this);

        votingController.initializeWines();

        Button addFundsButton = new Button("Add Funds");
        addFundsButton.setOnAction(e -> votingController.addFundsToUserWallet(20));

        Button showBalanceButton = new Button("Show Balance");
        showBalanceButton.setOnAction(e -> votingController.showCurrentUserBalance());

        Button buyPremiumButton = new Button("Buy Premium");
        buyPremiumButton.setOnAction(event -> votingController.buyPremium());

        Button evaluateVotesButton = new Button("Evaluate Votes");
        evaluateVotesButton.setOnAction(e -> votingController.evaluateVotes());

        TextField addWineField = new TextField();

        Button addWineButton = new Button("Add wine");
        addWineButton.setOnAction(e -> {
            votingController.premiumUserAddsWines(addWineField.getText());
            updateWineDisplay();
        });

        Button logoutButton = new Button("Log out");
        logoutButton.setOnAction(e -> {
            try {
                stop();
                votingController.logoutUser(primaryStage);
                
            } catch (Exception ex) {
                throw new RuntimeException(ex);
            }
        });

        Scene scene = new Scene(layout, 1200, 700);
        primaryStage.setScene(scene);
        primaryStage.show();

        layout.getChildren().addAll(wineListView, addFundsButton, showBalanceButton, buyPremiumButton, logoutButton);
        if (votingController.isPremium()) {
            layout.getChildren().addAll(evaluateVotesButton, addWineField, addWineButton);
        }

        setupWineListViewListener();
        updateWineDisplay();
        UserSessionNotifier.addObserver(this);
    }

    /**
     * Updates the view in response to changes in the user session, such as login or logout events.
     * This method is defined as part of the {@link UserSessionObserver} interface.
     */
    @Override
    public void update() {
        User currentUser = UserSession.getInstance().getCurrentUser();
        if(currentUser != null) {
            // TODO: Update the dashboard for the logged-in user
        } else {
            // TODO: Handle the case where no user is logged in
        }
    }

    /**
     * Called when the application is stopped, ensuring that this view is removed as an observer of the user session.
     * @throws Exception if there is an issue stopping the application.
     */
    @Override
    public void stop() throws Exception {
        super.stop();
        UserSessionNotifier.removeObserver(this);
    }

    /**
     * Updates the display of wines in the view. This method retrieves the current list of wines from
     * the voting controller and updates the wine list view.
     */
    public void updateWineDisplay() {
        Map<String, Wine> wines = votingController.getWines();

        updateWineList(wines);
    }

    /**
     * Updates the list of wines shown in the ListView component.
     * This method is responsible for converting the wine information into a format suitable for display.
     *
     * @param wines a map of wine names to {@link Wine} objects.
     */
    public void updateWineList(Map<String, Wine> wines) {
        Platform.runLater(() -> {
            wineListView.getSelectionModel().clearSelection();

            ObservableList<String> wineNamesAndVotes = FXCollections.observableArrayList(
                    wines.values().stream()
                            .map(wine -> wine.getName() + ", votes: " + wine.getVotes())
                            .collect(Collectors.toList()));
            wineListView.setItems(wineNamesAndVotes);
        });
    }

    /**
     * Sets up a listener for the wine list view. When a wine is selected, it prompts the user to confirm their vote
     * for the selected wine.
     */
    public void setupWineListViewListener() {
        wineListView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                String wineName = newValue.split(",")[0].trim();
                Alert alert = new Alert(Alert.AlertType.CONFIRMATION, "Vote for " + wineName + "?");
                alert.showAndWait().ifPresent(response -> {
                    if (response == ButtonType.OK) {
                        votingController.castVote(UserSession.getInstance().getCurrentUser(), wineName);
                    }
                });
            }
        });
    }

    /**
     * Displays a success message to the user in an alert dialog.
     *
     * @param message the success message to be displayed.
     */
    public void displaySuccess(String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Success");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }


    /**
     * Displays an error message to the user in an alert dialog.
     *
     * @param message the error message to be displayed.
     */
    public void displayError(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    /**
     *
     * @param args
     */
    public static void main(String[] args) {
        launch(args);
    }
}
