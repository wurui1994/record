package application;

import javafx.application.Application;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.scene.effect.Light;
import javafx.scene.effect.Lighting;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program applies a Lighting effect on 
 * a Text control. The azimuth of the light is 
 * controlled by a Slider.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class LightingEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {
        
        VBox root = new VBox(30);
        root.setPadding(new Insets(10));
        
        DoubleProperty azimuth = new SimpleDoubleProperty(0);        

        Light.Distant light = new Light.Distant();
        light.setAzimuth(0);

        Lighting lighting = new Lighting(light);
        lighting.setSurfaceScale(5.0);

        Text text = new Text();
        text.setText("ZetCode");
        text.setFill(Color.LIGHTSKYBLUE);
        text.setFont(Font.font(null, FontWeight.BOLD, 60));
        
        Slider slider = new Slider(1, 360, 0);
        azimuth.bind(slider.valueProperty());        
        
        slider.valueProperty().addListener(event -> {
            light.setAzimuth(azimuth.get());
            lighting.setLight(light);
            text.setEffect(lighting);
        });        

        text.setEffect(lighting);
        
        root.getChildren().addAll(slider, text);

        Scene scene = new Scene(root, 300, 250, Color.WHITESMOKE);

        stage.setTitle("Lighting");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
