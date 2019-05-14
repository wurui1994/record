package application;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.ColorPicker;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program uses the ColorPicker 
 * dialog to choose a colour value.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class ColorPickerEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox(25);
        root.setAlignment(Pos.BASELINE_CENTER);
        root.setPadding(new Insets(10));

        Text txt = new Text("ZetCode");

        Font font = Font.font(20);
        txt.setFont(font);

        ColorPicker cp = new ColorPicker();
        cp.setOnAction((ActionEvent event) -> {
            txt.setFill(cp.getValue());
        });

        root.getChildren().addAll(cp, txt);

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("ColorPicker");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
