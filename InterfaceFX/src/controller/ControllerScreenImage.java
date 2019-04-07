package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;

public class ControllerScreenImage {

    private ControllerRechercheCouleur controllerRechercheCouleur = new ControllerRechercheCouleur();
    private ControllerRechercheNoirBlanc controllerRechercheNoirBlanc = new ControllerRechercheNoirBlanc();
    public static Stage stage;


    @FXML
    public void handlerRadioCouleur(ActionEvent actionEvent) {
        Scene scene = stage.getScene();
        ChoiceBox txt = (ChoiceBox)scene.lookup("#typeImage_choiceBox");
        // TODO : changer la liste en fonction du type de l'image recherchée
    }

    @FXML
    public void handlerFileChoice(ActionEvent actionEvent) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Fichier à utiliser pour la comparaison");
        File file = fileChooser.showOpenDialog(stage);

        if (file != null) {
            String resultat = controllerRechercheCouleur.rechercheImageParFichier();
            Scene scene = stage.getScene();
            TextArea txt = (TextArea)scene.lookup("#results_area");
            txt.setText(txt.getText() + resultat + "\n");
        }
    }

    @FXML
    public void handlerButtonRechercher(ActionEvent actionEvent) {
        /*if (!controllerTexteMotCle.getSelectionMotARechercher().isEmpty()) {
            String resultat = controllerTexteMotCle.rechercheParMotCle();
            Scene scene = stage.getScene();
            TextArea txt = (TextArea)scene.lookup("#results_area");

            txt.setText(txt.getText() + resultat + "\n");
            controllerTexteMotCle.clear();
        } else {
            // TODO : Notifier l'utilisateur qu'il doit ajouter au moins 1 mot clé à rechercher.
        }*/
    }

}
