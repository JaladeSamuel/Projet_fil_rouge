package viewFX;

import controller.ControllerScreenTexte;
import controller.MenuController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import static view.Application.creationFichierBD;
import static view.Application.deserialisation;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception {
        //historique
        creationFichierBD();
        deserialisation();

        Parent root = FXMLLoader.load(getClass().getResource("screenPrincipal.fxml"));
        primaryStage.setTitle("FoxIt - Moteur de recherche");
        primaryStage.setScene(new Scene(root, 600, 400));
        primaryStage.show();

        MenuController.root = root;
        MenuController.stage = primaryStage;
        ControllerScreenTexte.stage = primaryStage;
    }


    public static void main(String[] args) {
        launch(args);
    }
}
