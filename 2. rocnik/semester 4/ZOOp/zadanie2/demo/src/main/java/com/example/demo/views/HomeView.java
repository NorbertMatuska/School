package com.example.demo.views;

import com.example.demo.controllers.UserController;
import com.example.demo.models.TaskModel;
import com.example.demo.models.UserModel;
import com.example.demo.router.ROUTES;
import com.example.demo.router.Router;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

import java.util.ArrayList;

public class HomeView extends View {
    Stage window;
    ArrayList<UserModel> users = new ArrayList<>();
    UserController uc;


    public HomeView(Stage window) {
        uc = new UserController();
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp, 500, 500);
        this.window.setScene(this.scene);
    }

    @Override
    public void render() {
        Button btn = new Button("Go to login");
        btn.setOnAction(e->{
            UserModel model = uc.getByName("Danka");
            System.out.println("Yo: "+model.getUsername());
            Router.goTo(ROUTES.LOGIN);
        });
        this.gp.getChildren().add(btn);

        TextField auction1 = new TextField();
        Button btn_bid1 = new Button("Bid");
        this.gp.getChildren().add(btn_bid1);
        this.gp.getChildren().add(auction1);

        TextField auction2 = new TextField();
        Button btn_bid2 = new Button("Bid");
        this.gp.getChildren().add(btn_bid2);
        this.gp.getChildren().add(auction2);

        TextField auction3 = new TextField();
        Button btn_bid3 = new Button("Bid");
        this.gp.getChildren().add(btn_bid3);
        this.gp.getChildren().add(auction3);

        Button btn2 = new Button("Add task");
        btn2.setOnAction(e->{
            TaskModel model = uc.createTask("prva", 150);
            System.out.println("ID: "+ model.getID()+" Name: "+model.getName()+" Cas: "+model.getTime());
        });
        this.gp.getChildren().add(btn2);

        GridPane.setConstraints(btn, 0, 0 );
        GridPane.setConstraints(btn2, 0, 1);
        GridPane.setConstraints(auction1, 0,3);
        GridPane.setConstraints(btn_bid1,0,4);
        GridPane.setConstraints(auction2,0,5);
        GridPane.setConstraints(btn_bid2,0,6);
        GridPane.setConstraints(auction3,0,7);
        GridPane.setConstraints(btn_bid3,0,8);

        this.window.show();
    }
}
