package application;

import java.time.LocalDate;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program shows a date chosen from 
 * a DatePicker in a label.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class DatePickerEx extends Application {
    
    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {
        
        VBox root = new VBox(15);
        root.setPadding(new Insets(10));        
        
        Label lbl = new Label("...");
        
        DatePicker datePicker = new DatePicker();

        datePicker.setOnAction(e -> {
            LocalDate date = datePicker.getValue();
            lbl.setText(date.toString());
        });

        root.getChildren().addAll(datePicker, lbl);

        Scene scene = new Scene(root, 350, 200);
        
        stage.setTitle("Date picker");
        stage.setScene(scene);
        stage.show();        
    }

    
    public static void main(String[] args) {
        launch(args);
    }
}
