package application;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program uses a Slider control to 
 * manipulate the images of an ImageView.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class SliderEx extends Application {

    private ImageView iview;
    private Image muteImg;
    private Image minImg;
    private Image maxImg;
    private Image medImg;

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox(10);
        root.setAlignment(Pos.CENTER);
        root.setPadding(new Insets(15));

        loadImages();

        iview = new ImageView(muteImg);

        Slider slider = new Slider(0, 100, 0);
        slider.valueProperty().addListener(new MyChangeListener());

        Scene scene = new Scene(root);

        root.getChildren().addAll(slider, iview);

        stage.setTitle("Slider");
        stage.setScene(scene);
        stage.show();
    }

    private void loadImages() {

        muteImg = new Image("file:mute.png");
        minImg = new Image("file:min.png");
        maxImg = new Image("file:max.png");
        medImg = new Image("file:med.png");
    }

    private class MyChangeListener implements ChangeListener<Number> {

        @Override
        public void changed(ObservableValue<? extends Number> observable,
                Number oldValue, Number newValue) {

            Double value = newValue.doubleValue();

            if (value == 0) {
                iview.setImage(muteImg);
            } else if (value > 0 && value <= 30) {
                iview.setImage(minImg);
            } else if (value > 30 && value < 80) {
                iview.setImage(medImg);
            } else {
                iview.setImage(maxImg);
            }
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
