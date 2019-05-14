package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.effect.PerspectiveTransform;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program creates a chessboard 
 * with a PerspectiveTransform effect.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class PerspectiveEx extends Application {

    private final int SIZE = 50;

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        StackPane root = new StackPane();
        
        Pane board = new Pane();
        
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                
                Rectangle r = new Rectangle(col * SIZE, row*SIZE, 
                        SIZE, SIZE);
                
                if ((col+row) % 2 == 0) {
                    r.setFill(Color.WHITE);
                } else {
                    r.setFill(Color.BLACK);
                }
                
                board.getChildren().add(r);
            }
        }

        PerspectiveTransform e = new PerspectiveTransform();
        e.setUlx(30);     // Upper-left point
        e.setUly(170);
        e.setUrx(370);    // Upper-right point
        e.setUry(170);
        e.setLlx(0);      // Lower-left point
        e.setLly(300); 
        e.setLrx(400);    // Lower-right point
        e.setLry(300);
        board.setEffect(e);
        
        root.getChildren().add(board);

        Scene scene = new Scene(root, Color.WHITESMOKE);

        stage.setTitle("ChessBoard");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
