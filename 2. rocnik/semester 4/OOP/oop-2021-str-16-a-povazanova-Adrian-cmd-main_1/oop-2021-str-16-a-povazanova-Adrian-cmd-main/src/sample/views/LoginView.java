package sample.views;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;

import sample.DataClass;
import sample.router.ROUTES;
import sample.router.Router;

import java.io.IOException;


public class LoginView extends View{
    Stage window;


    public LoginView(Stage window, DataClass Data){

        this.data =Data;
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,500,450);
        this.window.setScene(this.scene);
        window.setTitle("LOBBY");


    }

    @Override
    public void render() {
        Button btn = new Button("Shop");
        btn.setOnAction(e->{
/*

            try {
                Router.goTo(ROUTES.SHOP,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
            */

        });

        Button btn_Sklad = new Button ("Sklad");
        btn_Sklad.setOnAction(e->{

            try {
                Router.goTo(ROUTES.SKLAD,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }


        });

        Button Les = new Button ("Les");


        Les.setOnAction(e->{

            try {
                Router.goTo(ROUTES.LES,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }


        });

        Button Dielna = new Button ("Dielna");


        Dielna.setOnAction(e->{

            try {
                Router.goTo(ROUTES.DIELNA,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }

        });

        Button Monterna = new Button ("Monterna");


        Monterna.setOnAction(e->{


            try {
                Router.goTo(ROUTES.MONTERNA,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }

        });


        Button Tovar = new Button("Tovar");

        Tovar.setOnAction(e->{


            try {
                Router.goTo(ROUTES.TOVAR,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }

        });






        GridPane.setConstraints(btn_Sklad,0,1);
        GridPane.setConstraints(Les,0,2);
        GridPane.setConstraints(Dielna,0,3);
        GridPane.setConstraints(Monterna,0,4);

        btn.setMinSize(500,75);
        btn_Sklad.setMinSize(500,75);
        Les.setMinSize(500,75);
        Dielna.setMinSize(500,75);
        Monterna.setMinSize(500,75);

        Monterna.setFont(Font.font(25));
        Dielna.setFont(Font.font(25));
        Les.setFont(Font.font(25));
        btn_Sklad.setFont(Font.font(25));
        btn.setFont(Font.font(25));

        Monterna.setTextFill(Color.GREEN);
        Dielna.setTextFill(Color.GREEN);
        Les.setTextFill(Color.GREEN);
        btn_Sklad.setTextFill(Color.GREEN);
        btn.setTextFill(Color.GREEN);

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








        this.gp.getChildren().add(Monterna);
        this.gp.getChildren().add(btn_Sklad);
        this.gp.getChildren().add(Dielna);
        this.gp.getChildren().add(btn);
        this.gp.getChildren().add(Les);
        this.window.show();

    }



}
