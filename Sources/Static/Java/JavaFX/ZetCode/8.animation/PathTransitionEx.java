package application;

import javafx.animation.PathTransition;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.CubicCurveTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * ZetCode JavaFX tutorial
 *
 * This program uses a PathTransition to move 
 * a circle along a path.
 * 
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class PathTransitionEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();

        Path path = new Path();
        path.getElements().add(new MoveTo(20, 120));
        path.getElements().add(new CubicCurveTo(180, 60, 250, 340, 420, 240));

        Circle circle = new Circle(20, 120, 10);
        circle.setFill(Color.CADETBLUE);
        
        PathTransition ptr = new PathTransition();

        ptr.setDuration(Duration.seconds(6));
        ptr.setDelay(Duration.seconds(2));
        ptr.setPath(path);
        ptr.setNode(circle);
        ptr.setCycleCount(2);
        ptr.setAutoReverse(true);
        ptr.play();     

        root.getChildren().addAll(path, circle);

        Scene scene = new Scene(root, 450, 300);

        stage.setTitle("PathTransition");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
