package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Control;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import org.tbee.javafx.scene.layout.MigPane;

/**
 * ZetCode JavaFX tutorial
 *
 * This program creates a Windows layout with 
 * a MigPane.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class MigLayoutWindowsEx extends Application {

    MigPane root;
    
    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        root = new MigPane("", "[grow][]", "[][][grow][]");
        Scene scene = new Scene(root);

        Label lbl = new Label("Windows");
        Button actBtn = new Button("Activate");
        Button closeBtn = new Button("Close");
        Button okBtn = new Button("OK");
        Button helpBtn = new Button("Help");
        ListView listView = new ListView();
        
        createLayout(lbl, listView, actBtn, closeBtn, helpBtn, okBtn);
        
        stage.setTitle("Windows");
        stage.setScene(scene);
        stage.show();
    }
    
    private void createLayout(Control...arg) {
        
        root.add(arg[0], "wrap");
        root.add(arg[1], "w 200, h 200, span 2 2, grow");
        root.add(arg[2], "wrap");
        root.add(arg[3], "top, wrap");
        root.add(arg[4]);
        root.add(arg[5], "skip");    
    }

    public static void main(String[] args) {
        launch(args);
    }
}
