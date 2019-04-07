package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class ControllerScreenAdministrateur {

    public void handlerButtonAppliquer(ActionEvent actionEvent) {
    }

    public void handlerButtonRetour(ActionEvent actionEvent) {
        try {
            MenuController.root = FXMLLoader.load(getClass().getResource("/viewFX/screenPrincipal.fxml"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        MenuController.stage.setScene(new Scene(MenuController.root, 600, 400));
        MenuController.stage.show();
    }
}

