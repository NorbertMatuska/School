package sample.viewsworkers;

import javafx.scene.Scene;
import javafx.scene.control.*;
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

import java.io.IOException;
import java.util.ArrayList;

public class LesWorkerOak extends View {


        ArrayList<WoodCutter> osoby ;

   // public LesWorkerOak(Stage window, ArrayList<WoodCutter> Data){
    public LesWorkerOak(Stage window, DataClass Data) {

        this.data=Data;
        this.osoby =  Data.getDrevorubaci();
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,550,450);
        this.window.setScene(this.scene);
        window.setTitle("Lesworkers");


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



      //  StringBuilder retazec = new StringBuilder();

    int i=0;

        for(WoodCutter w : osoby)
        {
            i++;


            Label clovek = new Label();
            clovek.setText(w.getName()+ " " +w.getSurname());
            GridPane.setConstraints(clovek,0,2+i);
            clovek.setFont(Font.font(25));
            this.gp.getChildren().add(clovek);


            Button push = new Button("X");

            push.setOnAction(e->{


                w.setPeniaze(5);

                w.Pracuj(50,"Oak");



                try {
                    Router.goTo(ROUTES.LES,this.data);
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