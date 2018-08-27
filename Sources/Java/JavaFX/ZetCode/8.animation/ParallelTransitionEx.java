package application;

import javafx.animation.FillTransition;
import javafx.animation.ParallelTransition;
import javafx.animation.RotateTransition;
import javafx.animation.ScaleTransition;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * ZetCode JavaFX tutorial
 *
 * This program creates a parallel 
 * transition animation.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class ParallelTransitionEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();

        Rectangle rect = new Rectangle(50, 50, 30, 30);
        rect.setArcHeight(10);
        rect.setArcWidth(10);
        rect.setFill(Color.CADETBLUE);

        RotateTransition rottr
                = new RotateTransition(Duration.millis(2000), rect);
        rottr.setByAngle(180);
        rottr.setCycleCount(2);
        rottr.setAutoReverse(true);
        
        ScaleTransition sctr = new ScaleTransition(Duration.millis(2000), 
                rect);
        sctr.setByX(2);
        sctr.setByY(2);
        sctr.setCycleCount(2);
        sctr.setAutoReverse(true);
        
        FillTransition fltr = new FillTransition(Duration.millis(2000), 
                rect, Color.CADETBLUE, Color.STEELBLUE);
        fltr.setCycleCount(2);
        fltr.setAutoReverse(true);

        root.getChildren().add(rect);
        
        ParallelTransition ptr = new ParallelTransition();
        ptr.getChildren().addAll(rottr, sctr, fltr);
        
        ptr.play();    

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("ParallelTransition");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
