package viewFX;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.awt.*;
import java.io.File;

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
    }


    public static void main(String[] args) {
        launch(args);
    }
}
