package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import java.io.File;

public class ControllerScreenTexte {

    private ControllerTexteMotCle controllerTexteMotCle = new ControllerTexteMotCle();
    private ControllerTexteFichier controllerTexteFichier = new ControllerTexteFichier();
    public static Stage stage;

    @FXML
    public void handlerPlusButton(ActionEvent actionEvent) {
        Scene scene = stage.getScene();
        TextField txt = (TextField)scene.lookup("#plus_area");
        String motCle = txt.getText();

        if (!controllerTexteMotCle.isMotCleNonCorrecte(motCle)) {
            controllerTexteMotCle.getSelectionMotARechercher().add(motCle);
            txt.setText("");
        } else {
            // TODO : Notifier l'utilisateur que le mot n'est pas correcte.
        }
    }

    @FXML
    public void handlerMinusButton(ActionEvent actionEvent) {
        Scene scene = stage.getScene();
        TextField txt = (TextField)scene.lookup("#minus_area");
        String motCle = txt.getText();

        if (!controllerTexteMotCle.isMotCleNonCorrecte(motCle)) {
            controllerTexteMotCle.getSelectionMotANePasRechercher().add(txt.getText());
            txt.setText("");
        } else {
            // TODO : Notifier l'utilisateur que le mot n'est pas correcte.
        }
    }

    @FXML
    public void handlerFileChoice(ActionEvent actionEvent) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Fichier à utiliser pour la comparaison");
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
            controllerTexteMotCle.clear();
        } else {
            // TODO : Notifier l'utilisateur qu'il doit ajouter au moins 1 mot clé à rechercher.
        }
    }


    // TODO : Afficher les mots clés utilisés dans la recherche + ajouter un bouton pour faire un clear de tous ces mots clés

}
