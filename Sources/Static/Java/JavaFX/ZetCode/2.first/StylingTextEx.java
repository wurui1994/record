//package com.zetcode;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program styles a Text control with CSS.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class StylingTextEx extends Application {

//    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox();
        root.setPadding(new Insets(20));

        Text text = new Text("ZetCode");
        text.setFont(Font.font("Serif", FontWeight.BOLD, 76));

        text.setId("text");
        root.setId("root");

        root.getChildren().addAll(text);

        Scene scene = new Scene(root);
        scene.getStylesheets().add(this.getClass().getResource("text.css")
                .toExternalForm());

        stage.setTitle("Styling text");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
