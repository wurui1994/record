package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.ArcType;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program paints six different
 * shapes.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class ShapesEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();
        
        Canvas canvas = new Canvas(320, 300);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        drawShapes(gc);
        
        root.getChildren().add(canvas);        

        Scene scene = new Scene(root, 300, 200, Color.WHITESMOKE);

        stage.setTitle("Shapes");
        stage.setScene(scene);
        stage.show();
    }
    
    private void drawShapes(GraphicsContext gc) {
        
        gc.setFill(Color.GRAY);
        
        gc.fillOval(30, 30, 50, 50);
        gc.fillOval(110, 30, 80, 50);
        gc.fillRect(220, 30, 50, 50);
        gc.fillRoundRect(30, 120, 50, 50, 20, 20);
        gc.fillArc(110, 120, 60, 60, 45, 180, ArcType.OPEN);
        gc.fillPolygon(new double[]{220, 270, 220}, 
                new double[]{120, 170, 170}, 3);
    }

    public static void main(String[] args) {
        launch(args);
    }
}
