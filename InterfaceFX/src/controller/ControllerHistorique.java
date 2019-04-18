package controller;

import javafx.scene.Scene;
import javafx.scene.control.TreeItem;
import javafx.scene.control.TreeView;
import javafx.stage.Stage;
import model.Requete;
import view.Application;
import java.util.List;

public class ControllerHistorique {

    private static TreeItem<String> imageRoot = new TreeItem<>();
    private static TreeItem<String> texteRoot = new TreeItem<>();
    private static TreeItem<String> sonRoot = new TreeItem<>();
    private static TreeItem<String> topRoot = new TreeItem<>();
    private static List<Requete> requeteImage;
    private static List<Requete> requeteTexte;
    private static List<Requete> requeteSon;
    public static Stage stage;

    public static void inititialize() {
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

        topRoot.getChildren().add(texteRoot);
        topRoot.getChildren().add(imageRoot);
        topRoot.getChildren().add(sonRoot);

        ((TreeView)scene.lookup("#treeViewHistorique")).setRoot(topRoot);
        ((TreeView)scene.lookup("#treeViewHistorique")).setShowRoot(false);
    }

}
