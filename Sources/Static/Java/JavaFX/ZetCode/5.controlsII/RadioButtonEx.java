package application;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program presents the RadioButton
 * control.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class RadioButtonEx extends Application {
    
    private final double BORDER = 10d;
    private Label lbl2;

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        AnchorPane root = new AnchorPane();
        
        VBox vbox = new VBox(10);
        vbox.setPadding(new Insets(10));
        
        Label lbl1 = new Label("Difficulty");
        
        lbl2 = new Label("");
        lbl2.setStyle("-fx-background-color:wheat; -fx-padding: 0 0 0 5");
        lbl2.prefWidthProperty().bind(stage.widthProperty().subtract(2*BORDER));

        ToggleGroup tg =  new ToggleGroup();
        tg.selectedToggleProperty().addListener(new MyToggleListener());

        RadioButton rb1 = new RadioButton("Easy");
        rb1.setToggleGroup(tg);
        rb1.setSelected(true);

        RadioButton rb2 = new RadioButton("Medium");
        rb2.setToggleGroup(tg);

        RadioButton rb3 = new RadioButton("Hard");
        rb3.setToggleGroup(tg);
        
        vbox.getChildren().addAll(lbl1, rb1, rb2, rb3);
        
        root.getChildren().addAll(vbox, lbl2);
        
        AnchorPane.setTopAnchor(vbox, BORDER);
        AnchorPane.setBottomAnchor(lbl2, BORDER);
        AnchorPane.setLeftAnchor(lbl2, BORDER);

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("RadioButton");
        stage.setScene(scene);
        stage.show();
    }
    
    private class MyToggleListener implements ChangeListener<Toggle> {

        @Override
        public void changed(ObservableValue<? extends Toggle> observable, 
                Toggle oldValue, Toggle newValue) {
            
            RadioButton rb = (RadioButton) newValue;
            String txt = rb.getText();
            lbl2.setText(txt);
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
