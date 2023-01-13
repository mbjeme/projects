/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package fi.tuni.prog3.calc;

import javafx.application.Application;
import static javafx.application.Application.launch;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.Background;
import java.awt.Color;
import java.awt.Insets;
import javafx.scene.layout.CornerRadii;



/**
 * JavaFX App
 */
public class Calculator extends Application {

    @Override
    public void start(Stage stage) {
        stage.setTitle("Calculator");
        GridPane grid = new GridPane();
        Scene scene = new Scene(grid, 350, 275);
        stage.setScene(scene);
        
        // Labelit tekstikentille
        Label label1 = new Label("First operand:");
        grid.add(label1, 0, 1);
        label1.setId("labelOp1");
        Label label2 = new Label("Second operand:");
        grid.add(label2, 0, 2);
        label2.setId("labelOp2");
        
        //Tekstikentät
        TextField textField1 = new TextField();
        grid.add(textField1, 1, 1);
        textField1.setId("fieldOp1");
        TextField textField2 = new TextField();
        grid.add(textField2, 1, 2);
        textField2.setId("fieldOp2");
        
        // Rakenne nappuloille vaakasuoraan
        HBox hbBtn = new HBox(10);
        grid.add(hbBtn, 0, 3);
        
        // Nappulat
        Button btnAdd = new Button("Add");
        hbBtn.getChildren().add(btnAdd);
        btnAdd.setId("btnAdd");
        
        Button btnSub = new Button("Subtract");
        hbBtn.getChildren().add(btnSub);
        btnSub.setId("btnSub");
        
        Button btnMul = new Button("Multiply");
        hbBtn.getChildren().add(btnMul);
        btnMul.setId("btnMul");
        
        Button btnDiv = new Button("Divide");
        hbBtn.getChildren().add(btnDiv);
        btnDiv.setId("btnDiv");
        
        // Tuloskentän label
        Label labelResult = new Label("Result:");
        grid.add(labelResult, 0, 4);
        labelResult.setId("labelRes");
        //labelResult.setBackground(new Background(new BackgroundFill(Color.WHITE, CornerRadii.EMPTY, Insets.EMPTY)));
        
        // Tekstikenttä
        Label resultField = new Label();
        grid.add(resultField, 1, 4);
        resultField.setId("fieldRes");
        //resultField.setBackground(new Background(new BackgroundFill(Color.WHITE, new CornerRadii(0), new Insets(0))));
        
        btnAdd.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                var value1 = Double.parseDouble(textField1.getText());
                var value2 = Double.parseDouble(textField2.getText());
                var r = value1 + value2;
                resultField.setText(String.format("%.1f", r));

            }
        });
        
        btnSub.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                var value1 = Double.parseDouble(textField1.getText());
                var value2 = Double.parseDouble(textField2.getText());
                var r = value1 - value2;
                resultField.setText(String.format("%.1f", r));

            }
        });
        
        btnMul.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                var value1 = Double.parseDouble(textField1.getText());
                var value2 = Double.parseDouble(textField2.getText());
                var r = value1 * value2;
                resultField.setText(String.format("%.1f", r));

            }
        });
        
        btnDiv.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent e) {
                var value1 = Double.parseDouble(textField1.getText());
                var value2 = Double.parseDouble(textField2.getText());
                var r = value1 / value2;
                resultField.setText(String.format("%.1f", r));

            }
        });
        
        
        
        stage.show();
    }

    
    public static void main(String args[]) {
        launch();
    }
}

