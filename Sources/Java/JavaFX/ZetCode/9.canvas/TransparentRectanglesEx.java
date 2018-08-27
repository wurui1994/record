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
 * This program draws ten rectangles with different
 * levels of transparency.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class TransparentRectanglesEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        Pane root = new Pane();

        Canvas canvas = new Canvas(600, 300);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        drawRectangles(gc);

        root.getChildren().add(canvas);

        Scene scene = new Scene(root, 600, 100, Color.WHITESMOKE);

        stage.setTitle("Transparent rectangles");
        stage.setScene(scene);
        stage.show();
    }

    private void drawRectangles(GraphicsContext gc) {

        for (int i = 1; i <= 10; i++) {

            float alpha = i * 0.1f;
            
            gc.setFill(Color.FORESTGREEN);
            gc.setGlobalAlpha(alpha);
            gc.fillRect(50 * i, 20, 40, 40);
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
