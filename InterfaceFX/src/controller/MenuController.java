package controller;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import view.Application;

public class MenuController {

    public static Parent root;
    public static Stage stage;

    public void handleKeyInput(KeyEvent keyEvent) {
    }

    public void handleAboutActionQuitterEnregistrer(ActionEvent actionEvent) {
        Application.enregistrerHistorique();
        Platform.exit();
        System.exit(1);
    }

    public void handleAboutActionQuitter(ActionEvent actionEvent) {
        Platform.exit();
        System.exit(1);
    }

    public void notifyClickedExit(Event event) {
        System.out.println(event);
    }

    @FXML
    public void runInterfaceTexte(ActionEvent actionEvent) throws Exception {
        root = FXMLLoader.load(getClass().getResource("/viewFX/screenTexte.fxml"));
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }

    public void runInterfaceImage(ActionEvent actionEvent) {
    }

    public void runInterfaceSon(ActionEvent actionEvent) {
    }
}
