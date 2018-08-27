package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program draws six circles in six 
 * different colours.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class ColoursEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();
        
        Canvas canvas = new Canvas(300, 300);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        drawShapes(gc);
        
        root.getChildren().add(canvas);         

        Scene scene = new Scene(root, 280, 200, Color.WHITESMOKE);

        stage.setTitle("Colours");
        stage.setScene(scene);
        stage.show();
    }

    private void drawShapes(GraphicsContext gc) {
        
        gc.setFill(Color.CADETBLUE);
        gc.fillOval(30, 30, 50, 50);
        
        gc.setFill(Color.DARKRED);
        gc.fillOval(110, 30, 50, 50);
        
        gc.setFill(Color.STEELBLUE);
        gc.fillOval(190, 30, 50, 50);    
        
        gc.setFill(Color.BURLYWOOD);
        gc.fillOval(30, 110, 50, 50); 
        
        gc.setFill(Color.LIGHTSEAGREEN);
        gc.fillOval(110, 110, 50, 50);  
        
        gc.setFill(Color.CHOCOLATE);
        gc.fillOval(190, 110, 50, 50);          
    }
    
    public static void main(String[] args) {
        launch(args);
    }
}


