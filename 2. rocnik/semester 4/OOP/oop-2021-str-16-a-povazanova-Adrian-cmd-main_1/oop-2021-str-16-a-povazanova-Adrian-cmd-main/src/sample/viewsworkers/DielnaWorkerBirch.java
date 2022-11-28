package sample.viewsworkers;

import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import sample.DataClass;
import sample.Location.DielnaStock;
import sample.Location.ForestStock;
import sample.Worker.WoodCutter;
import sample.Worker.WoodPilcik;
import sample.router.ROUTES;
import sample.router.Router;
import sample.views.View;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;

public class DielnaWorkerBirch extends View {
    ArrayList<WoodPilcik> osoby ;


    public DielnaWorkerBirch(Stage window, DataClass Data){

        this.data=Data;
        this.osoby= Data.getPilcici();
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,550,450);
        this.window.setScene(this.scene);
        window.setTitle("dworkersB");


    }


    public void render()  {


        Button Login = new Button("Back");
        Login.setOnAction(e->{

            System.out.println("->Login");
            try {
                Router.goTo(ROUTES.LOGIN,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }

        });
        Login.setFont(Font.font(25));
        Login.setTextFill(Color.DARKRED);
        Login.setMinSize(500,75);
        this.gp.getChildren().add(Login);

        int i=0;

        for(WoodPilcik w : osoby)
        {
            i++;

            Label clovek = new Label();
            clovek.setText(w.getName()+ " " +w.getSurname());
            GridPane.setConstraints(clovek,0,2+i);
            clovek.setFont(Font.font(25));
            this.gp.getChildren().add(clovek);


            Button push = new Button("X");

            push.setOnAction(e->{

                w.setPeniaze(10);
                w.Pracuj(50,"Birch");




                try {
                    Router.goTo(ROUTES.DIELNA,this.data);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }


            });

            GridPane.setConstraints(push,1,2+i);
            push.setFont(Font.font(25));
            this.gp.getChildren().add(push);



            Button Logout = new Button("EXIT");
        Logout.setOnAction(e->{

            try {
                Router.goTo(ROUTES.WELCOME,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }

        });
        Logout.setFont(Font.font(25));
        Logout.setTextFill(Color.DARKRED);

        Logout.setMinSize(500,75);
        this.gp.getChildren().add(Logout);
        GridPane.setConstraints(Logout,0,20);

        this.window.show();




    }
}
}


