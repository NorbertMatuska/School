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
import sample.Location.MonternaStock;
import sample.router.ROUTES;
import sample.router.Router;

import java.io.IOException;
import java.util.ArrayList;

import static sample.Main.ArrayPridaj;

public class Sklad extends View{

    Stage window;

    public Sklad(Stage window, DataClass Data){

        this.data=Data;
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,500,450);
        this.window.setScene(this.scene);
        window.setTitle("Sklad");

    }


    @Override
    public void render() {

        Button Login = new Button("Back");

        ArrayList<String> Sklad = new ArrayList<String>();

        ArrayPridaj (Sklad, ForestStock.skladVypis());
        ArrayPridaj (Sklad, DielnaStock.skladVypis());


        int i=0;
        for(String str:Sklad)
        {
            Label SKLAD = new Label(str);
        this.gp.getChildren().add(SKLAD);

        GridPane.setConstraints((SKLAD),0,1+i);
        i++;
        }




        Login.setOnAction(e->{

            System.out.println("->Back");
            try {
                Router.goTo(ROUTES.LOGIN,this.data);
            } catch (IOException ioException) {
                ioException.printStackTrace();
            } catch (ClassNotFoundException classNotFoundException) {
                classNotFoundException.printStackTrace();
            }

        });

        Login.setFont(Font.font(25));
        Login.setTextFill(Color.GREEN);


        Login.setMinSize(500,75);
        this.gp.getChildren().add(Login);

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
