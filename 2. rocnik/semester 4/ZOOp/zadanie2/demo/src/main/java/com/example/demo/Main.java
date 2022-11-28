package com.example.demo;

import com.example.demo.models.UserModel;
import com.example.demo.router.ROUTES;
import com.example.demo.router.Router;
import com.example.demo.services.UserManager;
import com.example.demo.views.LoginView;
import com.example.demo.views.View;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;


import java.util.ArrayList;

public class Main extends Application{
    public static UserModel loggedUser;

    @Override
    public void start(Stage primaryStage){
        Router.window = primaryStage;
        UserManager um = UserManager.getInstance();
        um.save(new UserModel("Bob", "Heslo"));
        um.save(new UserModel("Danka", "heslo1"));
        loggedUser = um.get(0);
        Router.goTo(ROUTES.LOGIN);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
