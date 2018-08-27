package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.ScatterChart;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;


/*
 * ZetCode JavaFX tutorial
 *
 * This program creates a scatter chart.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: August 2016
 */
public class ScatterChartEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox();

        CategoryAxis xAxis = new CategoryAxis();

        NumberAxis yAxis = new NumberAxis("USD/kg", 30, 50, 2);

        ScatterChart scatterChart = new ScatterChart(xAxis, yAxis);

        XYChart.Series data = new XYChart.Series();

        data.getData().add(new XYChart.Data("Mar 14", 43));
        data.getData().add(new XYChart.Data("Nov 14", 38.5));
        data.getData().add(new XYChart.Data("Jan 15", 41.8));
        data.getData().add(new XYChart.Data("Mar 15", 37));
        data.getData().add(new XYChart.Data("Dec 15", 33.7));
        data.getData().add(new XYChart.Data("Feb 16", 39.8));

        scatterChart.getData().add(data);
        scatterChart.setLegendVisible(false);

        Scene scene = new Scene(root, 450, 330);

        root.getChildren().add(scatterChart);

        stage.setTitle("Gold price");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
