package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextArea;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class ControllerScreenAdministrateur {

    public static Stage stage;
    @FXML
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

    @FXML
    public void handlerIndexerTexte() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Fichier texte à indexer");
        File file = fileChooser.showOpenDialog(stage);

        if (file != null && !file.getName().contains(".xml")) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erreur");
            alert.setHeaderText("Vous devez ajouter un fichier '.xml'.");
            alert.showAndWait();
        } else if (file != null) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Fichier ajouté");
            alert.setHeaderText("Le fichier " + file.getName() + " a bien était ajouté.");
            alert.showAndWait();
        }
    }

    @FXML
    public void handlerIndexerImage() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Fichier image à indexer");
        File file = fileChooser.showOpenDialog(stage);

        if (file != null && !file.getName().contains(".jgp")) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erreur");
            alert.setHeaderText("Vous devez ajouter un fichier '.jpg'.");
            alert.showAndWait();
        } else if (file != null) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Fichier ajouté");
            alert.setHeaderText("Le fichier " + file.getName() + " a bien était ajouté.");
            alert.showAndWait();
        }
    }

    @FXML
    public void handlerIndexerSon() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Fichier son à indexer");
        File file = fileChooser.showOpenDialog(stage);

        if (file != null && !file.getName().contains(".wav")) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Erreur");
            alert.setHeaderText("Vous devez ajouter un fichier '.wav'.");
            alert.showAndWait();
        } else if (file != null) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Fichier ajouté");
            alert.setHeaderText("Le fichier " + file.getName() + " a bien était ajouté.");
            alert.showAndWait();
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

