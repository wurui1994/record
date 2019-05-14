package application;

import javafx.application.Application;
import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program adds a generic event 
 * handler to a button control.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class GenericHandlerEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        StackPane root = new StackPane();
        
        Button btn = new Button("Button");
        btn.addEventHandler(EventType.ROOT, new GenericHandler());
        
        root.getChildren().add(btn);

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("Generic handler");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }

    private class GenericHandler implements EventHandler<Event> {

        @Override
        public void handle(Event event) {
            System.out.println(event.getEventType());
        }
    }
}
