package com.example.gui;

import com.example.game.*;
import javafx.application.*;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.*;
import javafx.event.*;

public class GameGUI extends Application {
	private Button createWarriors = new Button("Create Warriors");
	private Button startClash = new Button("Start Clash");
	private Button removeText = new Button("Remove Text");
	private TextField knights = new TextField();
	private TextField braveKnights = new TextField();
	private TextField badOgres = new TextField();
	private Label knightsLabel = new Label("Knights");
	private Label braveKnightsLabel = new Label("Brave knights");
	private Label badOgresLabel = new Label("Bad ogres");
	private TextArea output = new TextArea();
	private ScrollPane scroll = new ScrollPane();
	
	private EnergyOfWarriors energyOfWarriors;
	
	public void start(Stage mainWindow) {
		mainWindow.setTitle("Clash");
		
		FlowPane pane = new FlowPane();
		
		Game game = new Game();
		
		pane.getChildren().add(createWarriors);
		pane.getChildren().add(startClash);
		pane.getChildren().add(removeText);
		pane.getChildren().add(knights);
		pane.getChildren().add(knightsLabel);
		pane.getChildren().add(braveKnights);
		pane.getChildren().add(braveKnightsLabel);
		pane.getChildren().add(badOgres);
		pane.getChildren().add(badOgresLabel);
		pane.getChildren().add(output);
		
		scroll.setContent(pane);		
		
/*
		class ClashHandler implements EventHandler<ActionEvent> {
			@Override
			public void handle(ActionEvent event) {
				game.createWarriors(Integer.parseInt(knights.getText()),
						Integer.parseInt(braveKnights.getText()),
						Integer.parseInt(badOgres.getText()),
						new AlternateSwordsGameSetup());

				output.appendText(game.clash());
			}
		}
			    	
		startClash.setOnAction(new ClashHandler());
*/
/*	
		// a listener implemented using an anonymous method
		startClash.setOnAction(new EventHandler<ActionEvent>() { // an anonymous class derived from the EventHandler interface
	    	@Override // an annotation that indicated overriding; annotations are information intended for humans, but they are usable programmatically, too
	    	public void handle(ActionEvent event) { // in the anonymous class, we override the handle() method
				game.createWarriors(Integer.parseInt(knights.getText()),
						Integer.parseInt(braveKnights.getText()),
						Integer.parseInt(badOgres.getText()),
						new AlternateSwordsGameSetup());

				output.appendText(game.clash());
			}
	    });
*/
/*
		// a listener implemented using a method reference
	    EventHandler<ActionEvent> a = new EventHandler<ActionEvent>() {
			public void handle(ActionEvent e) {
				game.createWarriors(Integer.parseInt(knights.getText()),
						Integer.parseInt(braveKnights.getText()),
						Integer.parseInt(badOgres.getText()),
						new AlternateSwordsGameSetup());

				output.appendText(game.clash());
			}
		};

   		startClash.setOnAction(a::handle);
*/
/*
		// a listener implemented using a lambda expression
		//startClash.setOnAction((ActionEvent e) -> { // a lambda expression with a type introduced
		startClash.setOnAction(e -> { // a lambda expression with type inference
				game.createWarriors(Integer.parseInt(knights.getText()),
					Integer.parseInt(braveKnights.getText()),
					Integer.parseInt(badOgres.getText()),
					new AlternateSwordsGameSetup());

				output.appendText(game.clash());
			}
		);
*/
 		createWarriors.setOnAction(e -> {
 				game.createWarriors(Integer.parseInt(knights.getText()),
					Integer.parseInt(braveKnights.getText()),
					Integer.parseInt(badOgres.getText()),
					new AlternateSwordsGameSetup());

 				output.appendText("Warriors created.\n");
			}
		);
		removeText.setOnAction(e -> output.clear());
 		startClash.setOnAction(e -> output.appendText(game.clash()));

		energyOfWarriors = new EnergyOfWarriors(game);
		game.followClash(energyOfWarriors);
		pane.getChildren().add(energyOfWarriors);

//		mainWindow.setScene(new Scene(pane, 500, 300));
		mainWindow.setScene(new Scene(scroll, 500, 300)); // with scrollbars
		mainWindow.show();
	}

	// the main() method will help if the standard way JavaFX application activation fails
	// but otherwise it's unnecessary
	public static void main(String[] args) {
		launch(args);
	}
}
