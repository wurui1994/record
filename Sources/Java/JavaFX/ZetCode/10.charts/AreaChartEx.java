package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.AreaChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

/*
 * ZetCode JavaFX tutorial
 *
 * This program creates an area chart.
 *
 * Author: Jan Bodnar 
 * Website: zetcode.com 
 * Last modified: August 2016
 */
public class AreaChartEx extends Application {

    @Override
    public void start(Stage stage) {

        initUI(stage);
    }

    private void initUI(Stage stage) {

        HBox root = new HBox();

        Scene scene = new Scene(root, 490, 350);

        CategoryAxis xAxis = new CategoryAxis();
        xAxis.setLabel("Time");

        NumberAxis yAxis = new NumberAxis();
        yAxis.setLabel("Thousand bbl/d");

        AreaChart areaChart = new AreaChart(xAxis, yAxis);
        areaChart.setTitle("Oil consumption");

        XYChart.Series data = new XYChart.Series();

        data.getData().add(new XYChart.Data("2004", 82502));
        data.getData().add(new XYChart.Data("2005", 84026));
        data.getData().add(new XYChart.Data("2006", 85007));
        data.getData().add(new XYChart.Data("2007", 86216));
        data.getData().add(new XYChart.Data("2008", 85559));
        data.getData().add(new XYChart.Data("2009", 84491));
        data.getData().add(new XYChart.Data("2010", 87672));
        data.getData().add(new XYChart.Data("2011", 88575));
        data.getData().add(new XYChart.Data("2012", 89837));
        data.getData().add(new XYChart.Data("2013", 90701));

        areaChart.getData().add(data);
        areaChart.setLegendVisible(false);

        root.getChildren().add(areaChart);

        stage.setTitle("AreaChart");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
