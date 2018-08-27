package application;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.control.SeparatorMenuItem;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program creates a MenuBar with one
 * menu and four menu items.
 *
 * Author: Jan Bodnar
 * Website: zetcode.com
 * Last modified: June 2015
 */

public class MenuBarEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox();

        MenuBar mbar = new MenuBar();
        mbar.prefWidthProperty().bind(stage.widthProperty());

        MyMenuHandler handler = new MyMenuHandler();

        Menu fileMenu = new Menu("File");
        mbar.getMenus().add(fileMenu);

        MenuItem nmi = new MenuItem("New");
        nmi.setOnAction(handler);
        fileMenu.getItems().add(nmi);

        MenuItem omi = new MenuItem("Open");
        omi.setOnAction(handler);
        fileMenu.getItems().add(omi);

        MenuItem smi = new MenuItem("Save");
        smi.setOnAction(handler);
        fileMenu.getItems().add(smi);

        fileMenu.getItems().add(new SeparatorMenuItem());

        MenuItem emi = new MenuItem("Exit");
        emi.setOnAction((ActionEvent event) -> {
            Platform.exit();
        });

        fileMenu.getItems().add(emi);

        root.getChildren().add(mbar);

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("MenuBar");
        stage.setScene(scene);
        stage.show();
    }

    private class MyMenuHandler implements EventHandler<ActionEvent> {

        @Override
        public void handle(ActionEvent event) {
            
            doShowMessageDialog(event);
        }
        
        private void doShowMessageDialog(ActionEvent event) {

            MenuItem mi = (MenuItem) event.getSource();
            String item = mi.getText();
            Alert alert = new Alert(AlertType.INFORMATION);
            alert.setTitle("Information dialog");
            alert.setHeaderText("Menu item selection information");
            alert.setContentText(item + " menu item selected");

            alert.showAndWait();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
