package sample.views;

import javafx.geometry.HPos;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;

import sample.DataClass;
import sample.router.ROUTES;
import sample.router.Router;

import java.io.IOException;


public class Welcome extends View{

    Stage window ;


    public Welcome(Stage window, DataClass Data){

        this.data=Data;
        this.window = window;
        this.gp = new GridPane();
        this.scene = new Scene(this.gp,500,450);
        this.window.setScene(this.scene);
        window.setTitle("L O G I N");

    }

   public void render() {

       Button btn = new Button("LOGIN");
       btn.setOnAction(e->{

           System.out.println("WELCOME");
           try {
               Router.goTo(ROUTES.LOGIN,this.data);
           } catch (IOException ioException) {
               ioException.printStackTrace();
           } catch (ClassNotFoundException classNotFoundException) {
               classNotFoundException.printStackTrace();
           }
       });

       btn.setFont(Font.font(25));
       btn.setTextFill(Color.RED);

       btn.setMinSize(500, 75);
       GridPane.setConstraints(btn,0,0);
       this.gp.getChildren().add(btn);



       Label plat = new Label();
       GridPane.setConstraints(plat,0,10);


     //  SledovatelPenazi(data);





        plat.setText("Observer"  );


       this.gp.getChildren().add(plat);









       this.window.show();
   }
   }


