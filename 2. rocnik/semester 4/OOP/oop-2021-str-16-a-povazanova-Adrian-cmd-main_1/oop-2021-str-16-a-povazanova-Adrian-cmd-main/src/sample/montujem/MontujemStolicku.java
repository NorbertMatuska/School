package sample.montujem;

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
import sample.Worker.WoodMonter;
import sample.Worker.WoodPilcik;
import sample.router.ROUTES;
import sample.router.Router;
import sample.views.View;

import java.io.IOException;
import java.util.ArrayList;

public class MontujemStolicku extends View {

    ArrayList<WoodMonter> osoby ;
    String wood;
    public MontujemStolicku(Stage window, DataClass Data, String wood) {
        this.wood = wood;
        this.data=Data;
        this.osoby= Data.getMonter();
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,550,450);
        this.window.setScene(this.scene);
        window.setTitle("dersB");
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

        for(WoodMonter w : osoby)
        {
            i++;

            Label clovek = new Label();
            clovek.setText(w.getName()+ " " +w.getSurname());
            GridPane.setConstraints(clovek,0,2+i);
            clovek.setFont(Font.font(25));
            this.gp.getChildren().add(clovek);


            Button push = new Button("X");

            push.setOnAction(e->{

                String a=("Stolicka");

                w.setPeniaze(5);
                w.Pracuj(wood,a);
                System.out.println(wood);




                try {
                    Router.goTo(ROUTES.MONTERNA,this.data);
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                } catch (ClassNotFoundException classNotFoundException) {
                    classNotFoundException.printStackTrace();
                }


            });

            GridPane.setConstraints(push,1,2+i);
            push.setFont(Font.font(25));
            this.gp.getChildren().add(push);


        }




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