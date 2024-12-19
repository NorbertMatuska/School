package com.example.demo.views;

import com.example.demo.controllers.UserController;
import com.example.demo.models.UserModel;
import com.example.demo.router.ROUTES;
import com.example.demo.router.Router;
import com.example.demo.services.UserManager;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class LoginView extends View {
    Stage window;
    ArrayList<UserModel> users = new ArrayList<>();
    UserController uc;

    public LoginView(Stage window) {
        uc = new UserController();
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp, 500, 500);
        this.window.setScene(this.scene);
    }


    @Override
    public void render() {
        Button btn_Login = new Button("Login");
        Button btn_Register = new Button("Register");

        this.gp.getChildren().add(btn_Login);
        this.gp.getChildren().add(btn_Register);

        TextField NameField = new TextField();
        this.gp.getChildren().add(NameField);
        Label NameLabel = new Label("Name: ");
        this.gp.getChildren().add(NameLabel);
        TextField PasswordField = new TextField();
        this.gp.getChildren().add(PasswordField);
        Label PasswordLabel = new Label("Password: ");
        this.gp.getChildren().add(PasswordLabel);
        Label InfoLabel = new Label("Successfully registered!");

        GridPane.setConstraints(NameLabel, 0, 0);
        GridPane.setConstraints(NameField,1,0);
        GridPane.setConstraints(PasswordLabel, 0, 1);
        GridPane.setConstraints(PasswordField,1,1);
        GridPane.setConstraints(btn_Login,1,2);
        GridPane.setConstraints(btn_Register, 1, 3);

        btn_Register.setOnAction(e->{
            UserModel model = uc.getFirstUser();
            System.out.println("Hello: "+model.getUsername());
            UserManager um = UserManager.getInstance();
            //this.uc.saveUserAccount(NameField.getText(), PasswordField.getText());
            try {
                PrintWriter out = new PrintWriter("filename.txt");
                out.println(NameField.getText());
                out.println(PasswordField.getText());
                out.println("-");
                out.close();
            } catch (FileNotFoundException ex) {
                ex.printStackTrace();
            }
            um.save(new UserModel(NameField.getText(),PasswordField.getText()));
            this.gp.getChildren().add(InfoLabel);
            GridPane.setConstraints(InfoLabel,0, 4);
            Router.goTo(ROUTES.LOGIN);
        });

        btn_Login.setOnAction(e->{
            try {
                File file = new File("filename.txt");
                Scanner scanner = new Scanner(file);
                while (scanner.hasNextLine()) {
                    String data = scanner.nextLine();
                    boolean equals = NameField.getText().equals(data);
                    if (equals) {
                        data = scanner.nextLine();
                        boolean equals1 = PasswordField.getText().equals(data);
                        if (equals1) {
                            Router.goTo(ROUTES.HOME);
                        }
                    }

                }
            } catch (FileNotFoundException ex) {
                ex.printStackTrace();
            }
        });

        this.window.show();
    }
}
