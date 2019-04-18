package viewFX;

import controller.*;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.stage.Stage;

import static view.Application.creationFichierBD;
import static view.Application.deserialisation;

public class Main extends Application {

    public static boolean administrateurConnecte = false;
    private DataBaseWatcherThread dataBaseWatcherThread;

    public static void alert(Alert.AlertType alertType, String message) {
        Alert alert = new Alert(alertType);
        alert.setTitle("Attention");
        alert.setHeaderText(message);
        alert.showAndWait();
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        //historique
        creationFichierBD();
        deserialisation();
        view.Application.enregistrerRequete = true;
        Parent root = FXMLLoader.load(getClass().getResource("screenPrincipal.fxml"));
        primaryStage.setTitle("FoxIt - Moteur de recherche");
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show();

        Scene scene = primaryStage.getScene();
        scene.getStylesheets().add(getClass().getResource("style.css").toExternalForm());

        // TODO : je suis un bolosse, en Java faut faire des setters parce que c'est plus propre gna gna gna mais j'ai pas envie yolo
        MenuController.root = root;
        MenuController.stage = primaryStage;
        ControllerScreenTexte.root = root;
        ControllerScreenTexte.stage = primaryStage;
        ControllerHistorique.stage = primaryStage;
        ControllerHistorique.root = root;
        ControllerScreenImage.root = root;
        ControllerScreenImage.stage = primaryStage;
        ControllerSon.root = root;
        ControllerSon.stage = primaryStage;
        ControllerScreenAdministrateur.stage = primaryStage;

        dataBaseWatcherThread = new DataBaseWatcherThread();
        dataBaseWatcherThread.start();
        primaryStage.setOnCloseRequest(event -> dataBaseWatcherThread.stopThread());
    }

    public static void main(String[] args) {
        launch(args);
    }

}
