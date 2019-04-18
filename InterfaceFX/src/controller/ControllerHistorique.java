package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.stage.Stage;
import model.Requete;
import view.Application;

import java.io.IOException;
import java.util.List;


public class ControllerHistorique {

    private static TreeItem<String> imageRoot;
    private static TreeItem<String> texteRoot;
    private static TreeItem<String> sonRoot;
    private static TreeItem<String> topRoot;
    private static List<Requete> requeteImage;
    private static List<Requete> requeteTexte;
    private static List<Requete> requeteSon;
    public static Stage stage;
    public static Parent root;


    public static void inititialize() {
        topRoot = new TreeItem<>();
        imageRoot = new  TreeItem<>("Image");
        texteRoot = new  TreeItem<>("Texte");
        sonRoot = new  TreeItem<>("Son");

        Scene scene = stage.getScene();
        requeteImage = Application.bdHistoriqueRequete.getListeRequeteImage();
        requeteTexte = Application.bdHistoriqueRequete.getListeRequeteTexte();
        requeteSon = Application.bdHistoriqueRequete.getListeRequeteSon();

        for(Requete requete : requeteTexte) {
            texteRoot.getChildren().add(new TreeItem<>(requete.toString()));
        }

        for(Requete requete : requeteImage) {
            imageRoot.getChildren().add(new TreeItem<>(requete.toString()));
        }

        for(Requete requete : requeteSon) {
            sonRoot.getChildren().add(new TreeItem<>(requete.toString()));
        }

        if(!requeteTexte.isEmpty()) {
            topRoot.getChildren().add(texteRoot);
        } else {
            topRoot.getChildren().add(new TreeItem<>("Aucunne requête texte"));
        }

        if(!requeteImage.isEmpty()) {
            topRoot.getChildren().add(imageRoot);
        } else {
            topRoot.getChildren().add(new TreeItem<>("Aucunne requête image"));
        }

        if(!requeteSon.isEmpty()) {
            topRoot.getChildren().add(sonRoot);
        } else {
            topRoot.getChildren().add(new TreeItem<>("Aucunne requête son"));
        }

        ((TreeView)scene.lookup("#treeViewHistorique")).setRoot(topRoot);
        ((TreeView)scene.lookup("#treeViewHistorique")).setShowRoot(false);
    }

    public void handlerRetour(ActionEvent actionEvent) throws IOException {
        root = FXMLLoader.load(getClass().getResource("/viewFX/screenPrincipal.fxml"));
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }

    public void handlerRechercher(ActionEvent actionEvent) {
        //todo
    }
}
