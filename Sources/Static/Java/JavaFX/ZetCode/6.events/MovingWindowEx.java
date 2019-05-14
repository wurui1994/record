package application;

import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program shows the screen coordinates
 * of the application window in two labels.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class MovingWindowEx extends Application {

    int x = 0;
    int y = 0;
    Label lblx;
    Label lbly;
    
    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        VBox root = new VBox(10);
        root.setPadding(new Insets(10));
        
        String txt1 = String.format("x: %d", x);
        lblx = new Label(txt1);
        
        String txt2 = String.format("y: %d", y);
        lbly = new Label(txt2);        
        
        root.getChildren().addAll(lblx, lbly);
        
        stage.xProperty().addListener(new ChangeListener<Number>() {

            @Override
            public void changed(ObservableValue<? extends Number> observable, 
                    Number oldValue, Number newValue) {
                
                doChange(newValue);
            }
            
            private void doChange(Number newValue) {
                
                x = newValue.intValue();
                updateXLabel();                
            }
            
        });
        
        stage.yProperty().addListener(new ChangeListener<Number>() {

            @Override
            public void changed(ObservableValue<? extends Number> observable, 
                    Number oldValue, Number newValue) {
                
                doChange(newValue);
            }
            
            private void doChange(Number newValue) {
                
                y = newValue.intValue();
                updateYLabel();                
            }
            
        });        

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("Moving window");
        stage.setScene(scene);
        stage.show();
    }
    
    private void updateXLabel() {
        
        String txt = String.format("x: %d", x);
        lblx.setText(txt);
    }
    
    private void updateYLabel() {
        
        String txt = String.format("y: %d", y);
        lbly.setText(txt);        
    }

    public static void main(String[] args) {
        launch(args);
    }
}
