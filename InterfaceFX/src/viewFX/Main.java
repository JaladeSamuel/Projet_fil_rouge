package viewFX;

import controller.*;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import static view.Application.creationFichierBD;
import static view.Application.deserialisation;

public class Main extends Application {

    public static boolean administrateurConnecte = false;

    @Override
    public void start(Stage primaryStage) throws Exception {
        //historique
        creationFichierBD();
        deserialisation();

        Parent root = FXMLLoader.load(getClass().getResource("screenPrincipal.fxml"));
        primaryStage.setTitle("FoxIt - Moteur de recherche");
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show();

        Scene scene = primaryStage.getScene();
        scene.getStylesheets().add(getClass().getResource("style.css").toExternalForm());

        MenuController.root = root;
        MenuController.stage = primaryStage;
        ControllerScreenTexte.root = root;
        ControllerScreenTexte.stage = primaryStage;
        ControllerHistorique.stage = primaryStage;
        ControllerScreenImage.root = root;
        ControllerScreenImage.stage = primaryStage;
        ControllerSon.root = root;
        ControllerSon.stage = primaryStage;
    }

    public static void main(String[] args) {
        launch(args);
    }

}
