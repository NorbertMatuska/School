package oop.controller;

import javafx.stage.Stage;
import oop.model.LoginVerificationException;
import oop.model.PremiumUser;
import oop.model.User;
import oop.utils.Database;
import oop.utils.IFrame;
import oop.utils.UserSession;
import oop.view.DashboardView;
import oop.view.LoginView;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;

/**
 * The {@code LoginController} class is responsible for managing user authentication,
 * including registering new users and verifying login credentials. It interacts with
 * the application's view and the database to perform these tasks.
 */
public class LoginController {
    private IFrame _window;
    /**
     * Constructs a new {@code LoginController} with a reference to the application's initial frame.
     *
     * @param window the initial frame of the application, used for updating the UI based on authentication results.
     */
    public LoginController(IFrame window) {
        this._window = window;
    }

    /**
     * Registers a new user with the provided username and password.
     * The new user is added to the database and saved to a CSV file.
     * Updates the UI with registration status.
     *
     * @param name the username of the new user.
     * @param pass the password of the new user.
     */
    public void RegisterUser(String name, String pass) {
        User newRegisteredUser = new User(name, pass);
        Database.DatabaseOfUsers.add(newRegisteredUser);
        saveUserToCSV(newRegisteredUser);
        if(SaveDownCast()) {
            ((LoginView)_window).infoLabel.setText("Register successfully!");
            ((LoginView)_window).infoLabel.setVisible(true);
        }
    }

    /**
     * Saves the specified user's information to a CSV file.
     * This method is private and used internally by the {@code RegisterUser} method.
     *
     * @param user the user to save to the CSV file.
     */
    private void saveUserToCSV(User user) {
        try (FileWriter fw = new FileWriter("users.csv", true);
             PrintWriter out = new PrintWriter(fw)) {
            out.println(user.Name + "," + user.Password);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Verifies if the provided username and password match an existing user.
     * If a match is found, the user is set as the current user in the session.
     *
     * @param name the username to verify.
     * @param pass the password to verify.
     * @return {@code true} if the credentials match an existing user, {@code false} otherwise.
     * @throws LoginVerificationException if there is an error during the login verification process.
     */
    public boolean verifyLogin(String name, String pass) throws LoginVerificationException {
        try (BufferedReader br = new BufferedReader(new FileReader("users.csv"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");
                if (values[0].equals(name) && values[1].equals(pass)) {
                    User newLogin = new User(name, pass);
                    UserSession.getInstance().setCurrentUser(newLogin);
                    return true;
                }
            }
        } catch (IOException e) {
            throw new LoginVerificationException("Failed to verify login due to IO error.", e);
        }
        return false;
    }

    public boolean verifyPremiumLogin(String name, String pass) throws LoginVerificationException {
        try (BufferedReader br = new BufferedReader(new FileReader("users.csv"))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");
                if (values[0].equals(name) && values[1].equals(pass)) {
                    PremiumUser newLogin = new PremiumUser(name, pass);
                    UserSession.getInstance().setCurrentUser(newLogin);
                    return true;
                }
            }
        } catch (IOException e) {
            throw new LoginVerificationException("Failed to verify login due to IO error.", e);
        }
        return false;
    }

    /**
     * Opens the dashboard view and closes the current login stage.
     * This method is called after a successful login.
     *
     * @param stage the current login stage that should be closed.
     */
    public void openDashboard(Stage stage) {
        try {
            stage.close();

            DashboardView dashboardView = new DashboardView();
            Stage dashboardStage = new Stage();
            dashboardView.start(dashboardStage);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    /**
     * Checks if the current frame is an instance of {@code LoginView}.
     * This method is private and used internally to determine if a downcast is safe.
     *
     * @return {@code true} if the current frame is an instance of {@code LoginView}, {@code false} otherwise.
     */
    private boolean SaveDownCast() {
        return this._window instanceof LoginView;
    }
}
