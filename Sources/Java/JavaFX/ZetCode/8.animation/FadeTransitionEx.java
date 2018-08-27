package application;

import javafx.animation.Animation;
import javafx.animation.FadeTransition;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.input.MouseEvent;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;

/**
 * ZetCode JavaFX tutorial
 *
 * This program uses a FadeTransition. A rectangle
 * fades out after we click into its area.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class FadeTransitionEx extends Application {

    private FadeTransition ft;
    private Rectangle rect;

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }
    
    private void initUI(Stage stage) {
        
        Group root = new Group();

        rect = new Rectangle(20, 20, 150, 150);
        rect.setOnMouseClicked(new RectClickHandler());

        ft = new FadeTransition(Duration.millis(5000), rect);
        ft.setFromValue(1.0);
        ft.setToValue(0.0);

        root.getChildren().add(rect);

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("Fading transition");
        stage.setScene(scene);
        stage.show();        
    }

    private class RectClickHandler implements EventHandler<MouseEvent> {

        @Override
        public void handle(MouseEvent event) {
            
            doHandle();
        }
        
        private void doHandle() {
            
            Double opa = rect.getOpacity();
            
            if (opa.intValue() == 0) {
                return;
            }
            
            Animation.Status as = ft.getStatus();
            
            if (as == Animation.Status.RUNNING) {
                return;
            }

            if (as == Animation.Status.STOPPED) {
                ft.play();
            }            
        }

    }

    public static void main(String[] args) {
        Application.launch(args);
    }
}
