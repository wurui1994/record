package application;

import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ProgressBar;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * ZetCode JavaFX tutorial
 *
 * This program presents the ProgressBar control.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class ProgressBarEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox(15);
        root.setAlignment(Pos.CENTER);
        root.setPadding(new Insets(10));

        ProgressBar pbar = new ProgressBar(0);
        pbar.setPrefWidth(150);
        
        KeyFrame frame1 = new KeyFrame(Duration.ZERO, 
                new KeyValue(pbar.progressProperty(), 0));
        
        KeyFrame frame2 = new KeyFrame(Duration.seconds(3), 
                new KeyValue(pbar.progressProperty(), 1));        

        Timeline task = new Timeline(frame1, frame2);

        Button btn = new Button("Start");
        btn.setOnAction((ActionEvent actionEvent) -> {
            task.playFromStart();
        });

        root.getChildren().addAll(pbar, btn);

        Scene scene = new Scene(root);

        stage.setTitle("ProgressBar");
        stage.setScene(scene);
        stage.show();
    }
    
    public static void main(String[] args) {
        launch(args);
    }
}
