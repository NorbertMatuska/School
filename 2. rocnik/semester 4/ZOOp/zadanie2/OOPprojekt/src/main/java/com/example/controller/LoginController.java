package com.example.controller;
import javafx.stage.Stage;
import model.User;
import util.Database;
import util.IFrame;
import view.LoginWindow;
import view.NewWindow;

public class LoginController {
    private IFrame _window;

    public LoginController(IFrame window) {
        this._window = window;
    }
    public void RegisterUser(String name, String pswd) {
        User newRegisteredUser = new User(name, pswd);
        Database.databaseOfUsers.add(newRegisteredUser);
        if(SaveDownCast()) {
            ((LoginWindow)_window).InfoLabel.setText("User registered.");
            ((LoginWindow)_window).InfoLabel.setVisible(true);
        }
        try {
            new NewWindow().start(new Stage());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private boolean SaveDownCast() {
        return this._window instanceof LoginWindow;
    }
}
