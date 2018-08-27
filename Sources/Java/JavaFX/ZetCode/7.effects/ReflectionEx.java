package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.effect.Reflection;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program applies a Reflection effect
 * on a Text node.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class ReflectionEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        StackPane root = new StackPane();
        
        Text text = new Text();
        text.setText("ZetCode");
        text.setFill(Color.STEELBLUE);
        text.setFont(Font.font("Serif", FontWeight.BOLD, 60));

        Reflection ref = new Reflection();
        text.setEffect(ref);
        
        root.getChildren().add(text);        

        Scene scene = new Scene(root, 300, 250, Color.WHITESMOKE);

        stage.setTitle("Reflection");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
