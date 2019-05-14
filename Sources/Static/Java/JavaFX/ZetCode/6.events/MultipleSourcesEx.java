package application;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program plugs an EventHandler to multiple
 * controls.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class MultipleSourcesEx extends Application {
    
    private Label lbl;

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {
        
        AnchorPane root = new AnchorPane();

        VBox vbox = new VBox(5);
        
        Button btn1 = new Button("Close");
        Button btn2 = new Button("Open");
        Button btn3 = new Button("Find");
        Button btn4 = new Button("Save");
        
        MyButtonHandler mbh = new MyButtonHandler();
        
        btn1.setOnAction(mbh);
        btn2.setOnAction(mbh);
        btn3.setOnAction(mbh);
        btn4.setOnAction(mbh);
        
        vbox.getChildren().addAll(btn1, btn2, btn3, btn4);
        
        lbl = new Label("Ready");
        
        AnchorPane.setTopAnchor(vbox, 10d);
        AnchorPane.setLeftAnchor(vbox, 10d);
        AnchorPane.setBottomAnchor(lbl, 10d);
        AnchorPane.setLeftAnchor(lbl, 10d);

        root.getChildren().addAll(vbox, lbl);
        
        Scene scene = new Scene(root, 350, 200);

        stage.setTitle("Multiple sources");
        stage.setScene(scene);
        stage.show();
    }
    
    private class MyButtonHandler implements EventHandler<ActionEvent> {

        @Override
        public void handle(ActionEvent event) {
            
            Button btn = (Button) event.getSource();
            lbl.setText(String.format("Button %s fired", btn.getText()));
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
