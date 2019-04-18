package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class ControllerSon {

    private ControllerTexteMotCle controllerTexteMotCle = new ControllerTexteMotCle();
    private ControllerTexteFichier controllerTexteFichier = new ControllerTexteFichier();
    private TreeItem<String> topRoot = new TreeItem<>();
    public static Parent root;
    public static Stage stage;

    @FXML
    public void handlerFileChoice(ActionEvent actionEvent) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Fichier à utiliser pour comparaison");
        File file = fileChooser.showOpenDialog(stage);

        if (file != null) {
            String resultat = controllerTexteFichier.rechercheParFichier(file.getPath());
            Scene scene = stage.getScene();
            TextArea txt = (TextArea)scene.lookup("#results_area");
            txt.setText(txt.getText() + resultat + "\n");
        }
    }

    @FXML
    public void handlerButtonRechercher(ActionEvent actionEvent) {
        if (!controllerTexteMotCle.getSelectionMotARechercher().isEmpty()) {
            String resultat = controllerTexteMotCle.rechercheParMotCle();
            Scene scene = stage.getScene();
            TextArea txt = (TextArea)scene.lookup("#results_area");

            txt.setText(txt.getText() + resultat + "\n");
        } else {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Attention");
            alert.setHeaderText("Vous devez au moins ajouter un mot pour lancer une recherche.");
            alert.showAndWait();
        }
    }

    @FXML
    public void handlerButtonRetour(ActionEvent actionEvent) throws IOException {
        root = FXMLLoader.load(getClass().getResource("/viewFX/screenPrincipal.fxml"));
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }

    @FXML
    public void handlerVider(ActionEvent actionEvent) {
        controllerTexteMotCle.clear();
        topRoot.getChildren().clear();
    }
}
