package view;

import javafx.application.Platform;
import model.BDHistoriqueRequete;

import java.io.*;

public class Application {
    public static BDHistoriqueRequete bdHistoriqueRequete;
    public static boolean enregistrerRequete = false;

    public static void main(String[] arg) {
        creationFichierBD();
        deserialisation();
        int choix = -1;
        while (choix > 2 || choix < 1) {
            System.out.println("Enregistrer les requetes qui vont être effectuées durant cette session ? : \n" +
                    "1 - OUI\n" +
                    "2 - NON\n" +
                    "Choix : ");
            choix = Clavier.entrerClavierInt();
        }
        enregistrerRequete = choix == 1;
        ViewAccueil viewAccueil = new ViewAccueil();
        viewAccueil.run();

    }
    public static void enregistrerHistorique() {
        if(bdHistoriqueRequete.getListeRequeteTexte().isEmpty() && bdHistoriqueRequete.getListeRequeteImage().isEmpty() && bdHistoriqueRequete.getListeRequeteSon().isEmpty()) {
            return;
        }
        if(!enregistrerRequete) {
            return;
        }
        System.out.println("Sauvegarde de l'historique ...");
        serialisation();
        System.out.println("Sauvegarde terminé");
    }

    public static void quitterApp() {
        if(bdHistoriqueRequete.getListeRequeteTexte().isEmpty() && bdHistoriqueRequete.getListeRequeteImage().isEmpty() && bdHistoriqueRequete.getListeRequeteSon().isEmpty()) {
            System.exit(1);
        }
        if(!enregistrerRequete) {
            System.exit(1);
        }
        System.out.println("Sauvegarde de l'historique ...");
        serialisation();
        System.out.println("Fermeture du programme");
        Platform.exit();
        System.exit(1);
    }

    private static void clearHistorique() {
        File fichier = new File("../BDHistorique/historique.ser");
        if(fichier.exists()) {
            fichier.delete();
        }
    }

    public static void serialisation() {
        File fichier = new File("../BDHistorique/historique.ser");
        //Serialization
        // ouverture d'un flux sur un fichier
        ObjectOutputStream oos;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(fichier));
            // sérialization de l'objet
            oos.writeObject(bdHistoriqueRequete) ;
            // fermeture du flux dans le bloc finally
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void deserialisation() {
        File fichier = new File("../BDHistorique/historique.ser");
        // ouverture d'un flux sur un fichier
        if (fichier.length() < 1) {
            bdHistoriqueRequete = new BDHistoriqueRequete();
            return;
        }
        ObjectInputStream bd = null;
        try {
            bd = new ObjectInputStream(new FileInputStream(fichier));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // désérialization de l'objet
        try {
            assert bd != null;
            bdHistoriqueRequete = (BDHistoriqueRequete) bd.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("Historique non fonctionnel : " +e);
            clearHistorique();
            creationFichierBD();
            deserialisation();
           // e.printStackTrace();
        }
        //fermeture
        try {
            bd.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void creationFichierBD() {
        File fichier = new File("../BDHistorique/historique.ser");

        //Si le fichier n'existe pas on le crée et on sort de la fonction ( historique vide )
        if (!fichier.exists()) {
            try {
                fichier.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public static void coucou() {
        System.out.println("coucou");
    }

}
