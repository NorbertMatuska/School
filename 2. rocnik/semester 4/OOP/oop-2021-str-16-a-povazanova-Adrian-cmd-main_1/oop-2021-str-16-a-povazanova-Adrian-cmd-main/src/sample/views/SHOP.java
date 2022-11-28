package sample.views;

import javafx.scene.Scene;


import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import sample.DataClass;
import sample.Location.MonternaStock;

import sample.Produkt.Produkt;
import sample.Worker.WoodMonter;
import sample.router.ROUTES;
import sample.router.Router;

import java.io.IOException;
import java.util.ArrayList;


public class SHOP extends View {
    Stage window;

    ArrayList<Produkt> cislo1 ;
    ArrayList<Produkt> cislo2 ;
    ArrayList<Produkt> cislo3 ;

    public SHOP(Stage window, DataClass Data){
        this.cislo1= Data.getStvol();
        this.cislo2= Data.getStolicka();
        this.cislo3= Data.getPostel();
        this.data =Data;
        this.window = window;
        this.gp= new GridPane();
        this.scene = new Scene(this.gp, 500,600);
        this.window.setScene(this.scene);
        window.setTitle("SHOP");
    }

    @Override
    public void render() {
        Button btn = new Button("Back");
        btn.setOnAction(e->{

            System.out.println("->Login");
            try {
                Router.goTo(ROUTES.LOGIN,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
        });


        btn.setMinSize(500,75);

        btn.setFont(Font.font(25));



        this.gp.getChildren().add(btn);


int a =60;

        Button btn_stvol = new Button("Stvol ");
        btn_stvol.setOnAction(e->{

            try {
                Router.goTo(ROUTES.VYBERWOOD,"Stvol",this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }


    });

        Button btn_stolicka = new Button("Stolička ");
        btn_stolicka.setOnAction(e->{

        });
        Button btn_postel = new Button("Postel ");
        btn_postel.setOnAction(e->{
            System.out.println("Zaklikol si postel");
        });








        GridPane.setConstraints(btn_stvol,0,2);
        GridPane.setConstraints(btn_stolicka,0,3);
        GridPane.setConstraints(btn_postel,0,4);

        this.gp.getChildren().add(btn_stvol);
        this.gp.getChildren().add(btn_stolicka);
        this.gp.getChildren().add(btn_postel);



        btn_stvol.setMinSize(500,75);
        btn_stolicka.setMinSize(500,75);
        btn_postel.setMinSize(500,75);

        btn_stvol.setFont(Font.font(25));
        btn_stolicka.setFont(Font.font(25));
        btn_postel.setFont(Font.font(25));


        Button Logout = new Button("EXIT");
        Logout.setOnAction(e->{

            try {
                Router.goTo(ROUTES.WELCOME,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }
            System.out.println("Odhlas ma");
        });
        Logout.setFont(Font.font(25));
        Logout.setTextFill(Color.DARKRED);

        Logout.setMinSize(500,75);
        this.gp.getChildren().add(Logout);
        GridPane.setConstraints(Logout,0,20);

        this.window.show();
    }
}