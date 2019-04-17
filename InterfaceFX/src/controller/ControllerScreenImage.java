package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class ControllerScreenImage {

    private ControllerRechercheCouleur controllerRechercheCouleur = new ControllerRechercheCouleur();
    private ControllerRechercheNoirBlanc controllerRechercheNoirBlanc = new ControllerRechercheNoirBlanc();
    private Map<String, Integer> choixCouleurs = new HashMap<>();
    private Map<String, Integer> choixNoirBlanc = new HashMap<>();
    public static Parent root;
    public static Stage stage;

    public ControllerScreenImage() {
        choixCouleurs.put("Rouge", 1);
        choixCouleurs.put("Rose", 2);
        choixCouleurs.put("Bleu", 3);
        choixCouleurs.put("Vert", 4);
        choixCouleurs.put("Jaune", 5);
        choixCouleurs.put("Orange", 6);
        choixCouleurs.put("Noir", 7);
        choixCouleurs.put("Blanc", 8);
        choixNoirBlanc.put("Noir", 7);
        choixNoirBlanc.put("Blanc", 8);
    }

    @FXML
    public void handlerRadioCouleur(ActionEvent actionEvent) {
        Scene scene = stage.getScene();
        ChoiceBox choiceBox = (ChoiceBox)scene.lookup("#typeImage_choiceBox");
        choiceBox.getItems().clear();
        for (String couleur : choixCouleurs.keySet()) {
            choiceBox.getItems().add(couleur);
        }
        choiceBox.setValue("Rouge");
    }

    @FXML
    public void handlerRadioNoirBlanc(ActionEvent actionEvent) {
        Scene scene = stage.getScene();
        ChoiceBox choiceBox = (ChoiceBox)scene.lookup("#typeImage_choiceBox");
        choiceBox.getItems().clear();
        for (String couleur : choixNoirBlanc.keySet()) {
            choiceBox.getItems().add(couleur);
        }
        choiceBox.setValue("Noir");
    }

    @FXML
    public void handlerFileChoice(ActionEvent actionEvent) {
        // TODO
    }

    @FXML
    public void handlerButtonRechercher(ActionEvent actionEvent) {
        String resultat;
        Scene scene = stage.getScene();
        RadioButton radioButtonCouleur = (RadioButton)scene.lookup("#couleur_radio");
        ChoiceBox choiceBox = (ChoiceBox)scene.lookup("#typeImage_choiceBox");
        if (radioButtonCouleur.isSelected()) {
            String choix = (String)choiceBox.getValue();
            resultat = controllerRechercheCouleur.rechercheCouleurDominanante(choixCouleurs.get(choix));
        } else {
            String choix = (String)choiceBox.getValue();
            resultat = controllerRechercheNoirBlanc.rechercheParNiveau(choixNoirBlanc.get(choix));
        }

        if (resultat != null) {
            TextArea txt = (TextArea)scene.lookup("#results_area");
            txt.setText(txt.getText() + resultat + "\n");
        }
    }

    @FXML
    public void handlerButtonRetour(ActionEvent actionEvent) throws IOException {
        root = FXMLLoader.load(getClass().getResource("/viewFX/screenPrincipal.fxml"));
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }


}
