package application;

import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.effect.Lighting;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * ZetCode JavaFX tutorial
 *
 * This program uses a Timeline to 
 * move a rectangle.
 * 
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class TimelineEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();

        Rectangle rect = new Rectangle(20, 20, 60, 60);
        rect.setEffect(new Lighting());
        rect.setFill(Color.CADETBLUE);

        Timeline tl = new Timeline();

        tl.setCycleCount(2);
        tl.setAutoReverse(true);
        
        KeyValue kv = new KeyValue(rect.translateXProperty(), 200);
        KeyFrame kf = new KeyFrame(Duration.millis(2000), kv);
        tl.getKeyFrames().addAll(kf);

        tl.play();

        root.getChildren().addAll(rect);

        Scene scene = new Scene(root, 350, 250);

        stage.setTitle("Timeline");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
