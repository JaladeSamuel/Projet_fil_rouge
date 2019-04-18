package controller;

import model.*;
import view.Application;

import java.util.*;

public class ControllerTexteMotCle {

    private List<Fichier> listeFichier = new ArrayList<>();
    private List<String> selectionMotARechercher = new ArrayList<>();
    private List<String> selectionMotANePasRechercher = new ArrayList<>();

    public List<String> getSelectionMotARechercher() {
        return selectionMotARechercher;
    }

    public List<String> getSelectionMotANePasRechercher() {
        return selectionMotANePasRechercher;
    }

    public void clear() {
        listeFichier = new ArrayList<>();
        selectionMotANePasRechercher = new ArrayList<>();
        selectionMotARechercher = new ArrayList<>();
    }

    @Override
    public String toString() {
        return "ControllerTexteMotCle{" +
                "listeFichier=" + listeFichier +
                ", selectionMotARechercher=" + selectionMotARechercher +
                ", selectionMotANePasRechercher=" + selectionMotANePasRechercher +
                '}';
    }

    private String resultatRequete() {
        StringBuilder msg;
        if(listeFichier.isEmpty()) {
            return  "Aucun fichier dans la base ne correspond à votre recherche.";
        }

        msg = new StringBuilder("Liste des fichiers correspondant à votre recherche : \n");
        for (Fichier fichier : listeFichier) {
            msg.append(fichier.getNom()).append("\n");
        }
        return msg.toString();
    }

    public String rechercheParMotCle() {

        Map<String,ArrayList<Fichier>> map = new HashMap<>();

        for(String motCle : selectionMotARechercher) {
            // TODO : make this work !! String str = MoteurDeRecherche.rechercheParMotCle(motCle);
            String str = MoteurDeRecherche.simulationRechercheParMotCle(motCle, true);
            map.put(motCle, new ArrayList<>());
            if (!str.contains("Aucun resultat n'a été trouvé.")) {
                String[] arrOfStr = str.split(" ");
                for (String s : arrOfStr) {
                    String[] attr = s.split(":");
                    map.get(motCle).add(new Fichier(Integer.parseInt(attr[1]),attr[0],TypeFichier.TEXTE));
                }
            }
        }


        for (Fichier fichier : map.get(selectionMotARechercher.get(0))) {
            boolean isInAllLists = true;
            for (String motCle : map.keySet()) {
                if (!map.get(motCle).contains(fichier)) {
                    isInAllLists = false;
                    break;
                }
            }

            if (isInAllLists && !listeFichier.contains(fichier)) {
                listeFichier.add(fichier);
            }
        }



        if(!selectionMotANePasRechercher.isEmpty()) {
            for (String s1 : selectionMotANePasRechercher) {
                ArrayList<Fichier> tamp = new ArrayList<>();
                // TODO : make this work !! String str = MoteurDeRecherche.rechercheParMotCle(motCle);
                String str = MoteurDeRecherche.simulationRechercheParMotCle(s1, true);
                if (!str.contains("Aucun resultat n'a été trouvé.")) {
                    String[] arrOfStr = str.split(" ");
                    for (String s : arrOfStr) {
                        String[] attr = s.split(":");
                        for (Fichier fichier : listeFichier) {
                            if (fichier.getNom().equals(attr[0])) {
                                tamp.add(fichier);
                            }
                        }
                    }
                    listeFichier.removeAll(tamp);
                }
            }

        }

        StringBuilder requete = new StringBuilder();
        for(String mot : selectionMotARechercher) {
            requete.append("+").append(mot);
        }
        requete.append(" | ");
        for(String mot : selectionMotANePasRechercher) {
            requete.append("-").append(mot);
        }
        Application.bdHistoriqueRequete.getListeRequeteTexte().add(new Requete(TypeRecherche.TEXTE_MOT_CLE, requete.toString(),new Date(),resultatRequete()));
        return resultatRequete();
    }

    public boolean isMotCleNonCorrecte(String motCle) {
        if (motCle.length() < 3) {
            System.out.println("La longueur du mot doit être supérieur à 3 charactères.");
            return true;
        } else if (!motCle.matches("[a-zA-Z0-9]+")) {
            System.out.println("Le mot clé contient un caractère spécial.");
            return true;
        }

        return false;
    }

}
