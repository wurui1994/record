package application;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program explores the properties of 
 * an event.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class EventSourceEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();
        
        Rectangle rect = new Rectangle(30, 30, 80, 80);
        rect.setOnMouseClicked(new EventHandler<MouseEvent>() {

            @Override
            public void handle(MouseEvent e) {
                
                System.out.println(e.getSource());
                System.out.println(e.getTarget());
                System.out.println(e.getEventType());
                System.out.format("x:%f, y:%f%n", e.getSceneX(), e.getSceneY());
                System.out.format("x:%f, y:%f%n", e.getScreenX(), e.getScreenY());
            }
        });
        
        root.getChildren().addAll(rect);

        Scene scene = new Scene(root, 300, 250);
        
        stage.setTitle("Event properties");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
