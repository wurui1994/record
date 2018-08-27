package application;

import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.scene.effect.GaussianBlur;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program applies a GaussianBlur effect on 
 * a Text control. The radius of the blur is 
 * controlled by a Slider.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class GaussianBlurEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        VBox root = new VBox(30);
        root.setPadding(new Insets(10));
        
        DoubleProperty radius = new SimpleDoubleProperty(0);
        
        Text blurredText = new Text("Inception");
        blurredText.setFont(Font.font(38));        
        
        Slider slider = new Slider(1, 20, 1);
        radius.bind(slider.valueProperty());        
        
        slider.valueProperty().addListener(event -> {
            blurredText.setEffect(new GaussianBlur(radius.get()));
        });

        root.getChildren().addAll(slider, blurredText);
        
        Scene scene = new Scene(root, 300, 250, Color.WHITESMOKE);

        stage.setTitle("Blur effect");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
