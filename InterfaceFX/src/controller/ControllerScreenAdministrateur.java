package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.CheckBox;
import javafx.stage.Stage;

import java.io.IOException;

public class ControllerScreenAdministrateur {

    public static Stage stage;
    private static CheckBox checkBoxPopup;

    @FXML
    public void handlerButtonAppliquer(ActionEvent actionEvent) {
    }

    @FXML
    public void handlerButtonRetour(ActionEvent actionEvent) {
        try {
            MenuController.root = FXMLLoader.load(getClass().getResource("/viewFX/screenPrincipal.fxml"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        MenuController.stage.setScene(new Scene(MenuController.root, 600, 400));
        MenuController.stage.show();
    }

    @FXML
    public void handlerCheckBox() {
        if (checkBoxPopup.isSelected()) {
            DataBaseWatcherThread.enablePopups();
        } else {
            DataBaseWatcherThread.disablePopups();
        }
    }

    public static void initialise() {
        Scene scene = stage.getScene();
        checkBoxPopup = ((CheckBox)scene.lookup("#checkBoxPopup"));

        if (DataBaseWatcherThread.isPopupEnable()) {
            checkBoxPopup.setSelected(true);
        } else {
            checkBoxPopup.setSelected(false);
        }
    }

}

