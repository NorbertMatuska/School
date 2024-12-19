package oop.view;

import javafx.application.Application;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;
import javafx.stage.Stage;
import oop.controller.LoginController;
import oop.model.LoginVerificationException;
import oop.utils.IFrame;
import oop.utils.LayoutStyler;

/**
 * The {@code LoginView} class serves as the user interface for user authentication,
 * including both login and registration processes. It implements {@link IFrame} to define its
 * layout and initialize its components according to the application's style.
 */
public class LoginView extends Application implements IFrame {
    public static LoginController controller = null;
    public Button RegisterButton = new Button("Register");
    public Button LoginButton = new Button("Login");
    public Button PremiumLoginButton = new Button("Premium Login");
    public Stage pageStage = null;
    public TextField nameField = new TextField();
    public TextField passField = new PasswordField();
    public Label nameLabel = new Label("Name:");
    public Label passLabel = new Label("Password:");
    public Label infoLabel = new Label("");

    /**
     * Starts the primary stage for the login view, initializing the layout, styles,
     * and event handlers associated with the login and registration process.
     *
     * @param stage The primary stage for this view.
     */
    @Override
    public void start(Stage stage) {
        try {
            pageStage = stage;
            String css = this.getClass().getResource("stylesheet.css").toExternalForm();
            System.out.println(css);
            scene.getStylesheets().add(css);
            pageStage.setScene(scene);
            SetAndInitialize();
            InitializeController();
            pageStage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
        RegisterButton.setOnAction(e->controller.RegisterUser(nameField.getText(), passField.getText()));

        LoginButton.setOnAction(e -> {
            try {
                if (controller.verifyLogin(nameField.getText(), passField.getText())) {
                    infoLabel.setText("Login successful!");
                    infoLabel.setVisible(true);
                    controller.openDashboard(stage);
                } else {
                    infoLabel.setText("Login failed. Please check your credentials.");
                    infoLabel.setVisible(true);
                }
            } catch (LoginVerificationException ex) {
                System.err.println("Login failed: " + ex.getMessage());
            }

        });

        PremiumLoginButton.setOnAction(e -> {
            try {
                if (controller.verifyPremiumLogin(nameField.getText(), passField.getText())) {
                    infoLabel.setText("Premium login successful!");
                    infoLabel.setVisible(true);
                    controller.openDashboard(stage);
                } else {
                    infoLabel.setText("Login failed. Please check your credentials.");
                    infoLabel.setVisible(true);
                }
            } catch (LoginVerificationException ex) {
                System.err.println("Login failed: " + ex.getMessage());
            }
        });
    }

    /**
     * Initializes and sets the layout for the login form components using the {@link LayoutStyler}.
     * This method is called during the start-up process to configure the visual structure of the UI.
     */
    @Override
    public void SetAndInitialize() {
        this.pageStage.setTitle("Login");
        LayoutStyler.SetLayout(this, nameLabel, 60, 140, 100, 30, true);
        LayoutStyler.SetLayout(this, nameField, 125, 140, 100, 30, true);
        LayoutStyler.SetLayout(this, passLabel, 60, 170, 100, 30, true);
        LayoutStyler.SetLayout(this, passField, 125, 170, 100, 30, true);
        LayoutStyler.SetLayout(this, RegisterButton, 125, 200, 100, 30, true);
        LayoutStyler.SetLayout(this, LoginButton, 200, 200, 100, 30, true);
        LayoutStyler.SetLayout(this, PremiumLoginButton, 135, 240, 100, 30, true);
        LayoutStyler.SetLayout(this, infoLabel, 100, 300, 100, 30, false);
    }

    /**
     * Initializes the {@link LoginController} for this view, allowing the view to interact
     * with the application's authentication logic. This method is called during the start-up
     * process to prepare the controller for handling user actions.
     */
    @Override
    public void InitializeController() {
        controller = new LoginController(this);
    }

    /**
     *
     * @param args
     */
    public static void main(String[] args) {
        launch(args);
    }
}