package view;

import com.example.controller.LoginController;
import javafx.application.Application;
import javafx.scene.control.PasswordField;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import util.IFrame;
import util.LayoutStyler;

import java.util.jar.Attributes;

public class LoginWindow extends Application implements IFrame {
    public static LoginController controller = null;
    public Button RegisterButton = new Button("Register");
    public Button LoginButton = new Button("Login");
    public Stage PageStage = null;
    public TextField NameField = new TextField();
    public TextField PswdField = new TextField();
    public Label NameLabel = new Label("Name:");
    public Label PswdLabel = new Label("Password:");
    public Label InfoLabel = new Label("");

    @Override
    public void start(Stage primaryStage) {
        try {
            PageStage = primaryStage;
            //scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
            PageStage.setScene(scene);
            SetAndInitialize();
            InitializeController();
            PageStage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
        RegisterButton.setOnAction(e -> controller.RegisterUser(NameField.getText(), PswdField.getText()));
    }

    @Override
    public void SetAndInitialize() {
        this.PageStage.setTitle("Login");
        LayoutStyler.SetLayout(this,NameLabel, 60, 140, 100, 30, true);
        LayoutStyler.SetLayout(this, NameField, 125, 140, 100, 30, true);
        LayoutStyler.SetLayout(this, PswdLabel, 60, 170, 100, 30, true);
        LayoutStyler.SetLayout(this, PswdField, 125, 170, 100, 30, true);
        LayoutStyler.SetLayout(this, RegisterButton, 125, 200, 100, 30, true);
        LayoutStyler.SetLayout(this, LoginButton, 200, 200, 100, 30, true);
        LayoutStyler.SetLayout(this, InfoLabel, 150, 250, 100, 30, false);

    }

    @Override
    public void InitializeController() {
        controller = new LoginController(this);
    }

    public static void main(String[] args) {
        Application.launch(args);
    }
}

