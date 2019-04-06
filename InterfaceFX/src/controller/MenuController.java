package controller;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.scene.input.KeyEvent;
import view.Application;

public class MenuController {
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

    public void runInterfaceTexte(ActionEvent actionEvent) {
    }

    public void runInterfaceImage(ActionEvent actionEvent) {
    }

    public void runInterfaceSon(ActionEvent actionEvent) {
    }
}
