package application;

import javafx.application.Application;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.Label;
import javafx.scene.control.SingleSelectionModel;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 * ZetCode JavaFX tutorial
 *
 * This program uses a ChoiceBox. The chosen
 * item is shown in a label.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: June 2015
 */

public class ChoiceBoxEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        VBox root = new VBox(35);
        root.setPadding(new Insets(10));

        Label lbl = new Label();

        ChoiceBox chbox = new ChoiceBox(FXCollections.observableArrayList(
                "Ubuntu", "Redhat", "Arch", "Debian", "Mint"));

        SingleSelectionModel model = chbox.getSelectionModel();

        model.selectedItemProperty().addListener((ObservableValue observable, 
                Object oldValue, Object newValue) -> {

            lbl.setText(newValue.toString());
        });

        root.getChildren().addAll(chbox, lbl);

        Scene scene = new Scene(root, 300, 250);

        stage.setTitle("ChoiceBox");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
