package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

/*
 * ZetCode JavaFX tutorial
 *
 * This program creates a bar chart.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: August 2016
 */
public class BarChartEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {
        
        HBox root = new HBox();  

        Scene scene = new Scene(root, 480, 330);
        CategoryAxis xAxis = new CategoryAxis();

        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("Gold medals");

        BarChart barChart = new BarChart(xAxis, yAxis);
        barChart.setTitle("Olympic gold medals in London");

        XYChart.Series data = new XYChart.Series();

        data.getData().add(new XYChart.Data("USA", 46));
        data.getData().add(new XYChart.Data("China", 38));
        data.getData().add(new XYChart.Data("UK", 29));
        data.getData().add(new XYChart.Data("Russia", 22));
        data.getData().add(new XYChart.Data("South Korea", 13));
        data.getData().add(new XYChart.Data("Germany", 11));

        barChart.getData().add(data);
        barChart.setLegendVisible(false);

        root.getChildren().add(barChart);

        stage.setTitle("BarChart");
        stage.setScene(scene);
        stage.show();

    }

    public static void main(String[] args) {
        launch(args);
    }
}
