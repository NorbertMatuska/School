package sample.woodvyber;


import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import sample.DataClass;
import sample.Location.ForestStock;
import sample.Worker.WoodCutter;
import sample.router.ROUTES;
import sample.router.Router;
import sample.views.View;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class VyberWood extends View {

    public VyberWood(Stage window, String Nabytok, DataClass Data){

        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,500,450);
        this.window.setScene(this.scene);
        window.setTitle("Vyber typ dreva produktu ktorýkupuješ");


    }


    public void render() throws ClassNotFoundException, IOException {


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

    int a =10;


        Button Oak = new Button ("Oak ("+ a + ")");
        Oak.setOnAction(e->{



            if (a>0)
            {
                try {
                    Router.goTo(ROUTES.LOGIN,this.data);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
                System.out.println("Les worker");

            }
            else
                System.out.println("Plny sklad");



        });
        GridPane.setConstraints(Oak,0,2);
        Oak.setMinSize(100,25);
        this.gp.getChildren().add(Oak);


        Button Birch = new Button ("Birch ("+ a + ")");
        Birch.setOnAction(e->{



            if (a>0)
            {
                try {
                    Router.goTo(ROUTES.LOGIN,this.data);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
                System.out.println("Les worker");

            }
            else
                System.out.println("Plny sklad");



        });
        GridPane.setConstraints(Birch,0,3);
        Birch.setMinSize(100,25);
        this.gp.getChildren().add(Birch);


        Button Spruce = new Button ("Spruce ("+ a + ")");
        Spruce.setOnAction(e->{



            if (a>0)
            {
                try {
                    Router.goTo(ROUTES.LOGIN,this.data);



                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
                System.out.println("Les worker");

            }
            else
                System.out.println("Plny sklad");



        });
        GridPane.setConstraints(Spruce,0,4);
        Spruce.setMinSize(100,25);
        this.gp.getChildren().add(Spruce);












        Button Logout = new Button("EXIT");
        Logout.setOnAction(e->{

            try {
                Router.goTo(ROUTES.WELCOME,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
            System.out.println("odhlas ma");
        });
        Logout.setFont(Font.font(25));
        Logout.setTextFill(Color.DARKRED);

        Logout.setMinSize(500,75);
        this.gp.getChildren().add(Logout);
        GridPane.setConstraints(Logout,0,20);

        this.window.show();




    }
}