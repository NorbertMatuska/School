package sample.views;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import sample.DataClass;
import sample.Location.DielnaStock;
import sample.Location.ForestStock;
import sample.router.ROUTES;
import sample.router.Router;

import java.io.IOException;

public class Dielna extends View{

    public Dielna(Stage window, DataClass Data){

        this.data=Data;
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,500,450);
        this.window.setScene(this.scene);
        window.setTitle("Dielna");

    }

    @Override
    public void render() {

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

        Label Sklad = new Label();
        Sklad.setText(DielnaStock.skladVypis());

        GridPane.setConstraints(Sklad,0,1);
        Login.setMinSize(500,75);
        this.gp.getChildren().add(Login);
        this.gp.getChildren().add(Sklad);
        Login.setFont(Font.font(25));
        Login.setTextFill(Color.GREEN);




        Button Oak = new Button ("Oak + 50");
        Oak.setOnAction(e->{

            int pocet = DielnaStock.getOak();
            int pocet2 =ForestStock.getOak();

            if (pocet <2000 && pocet2 > 0)
            {
                try {
                    Router.goTo(ROUTES.DIELNAWORKEROAK,this.data);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
                System.out.println("Dielna worker");

            }
            else
                System.out.println("Plny sklad dielna alebo prázdny forest");



        });
        GridPane.setConstraints(Oak,0,2);
        Oak.setMinSize(100,25);
        this.gp.getChildren().add(Oak);


        Button Birch = new Button ("Birch + 50");
        Birch.setOnAction(e->{
            int pocet = DielnaStock.getBirch();
            int pocet2 = ForestStock.getBirch();

            if (pocet <2000 && pocet2 > 0)
            {
                try {
                    Router.goTo(ROUTES.DIELNAWORKERBIRCH,this.data);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }
                System.out.println("dielna worker");

            }
            else
                System.out.println("Plny sklad dielna ... dačo");



        });
        GridPane.setConstraints(Birch,0,3);
        Birch.setMinSize(100,25);
        this.gp.getChildren().add(Birch);


        Button Spruce = new Button ("Spruce + 50");
        Spruce.setOnAction(e->{

            int pocet2 = ForestStock.getSpruce();
            int pocet = DielnaStock.getSpruce();

            if (pocet <2000 && pocet2 >0)
            {
                try {
                    Router.goTo(ROUTES.DIELNAWORKERSPRUCE,this.data);

                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }


            }



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
