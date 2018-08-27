package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.CycleMethod;
import javafx.scene.paint.RadialGradient;
import javafx.scene.paint.Stop;
import javafx.stage.Stage;

/*
 * ZetCode JavaFX tutorial
 *
 * This program draws a radial gradient.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: August 2016
 */
public class RadialGradientEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }
    
    private void initUI(Stage stage) {

        Pane root = new Pane();
        
        Canvas canvas = new Canvas(300, 300);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        doDrawing(gc);
        
        root.getChildren().add(canvas);    

        Scene scene = new Scene(root, 300, 250, Color.WHITESMOKE);

        stage.setTitle("Radial gradient");
        stage.setScene(scene);
        stage.show();
    }
    
    private void doDrawing(GraphicsContext gc) {
        
        Stop[] stops1 = new Stop[] { new Stop(0, Color.RED), 
            new Stop(1, Color.BLACK)};
        RadialGradient lg1 = new RadialGradient(0, 0, 0.5, 0.5, 0.8, true, 
                CycleMethod.NO_CYCLE, stops1);
        gc.setFill(lg1);
        gc.fillOval(30, 30, 150, 150);
    }


    public static void main(String[] args) {
        launch(args);
    }
}
