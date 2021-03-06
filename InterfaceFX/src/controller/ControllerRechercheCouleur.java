package controller;

import model.*;
import view.Application;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ControllerRechercheCouleur {

    private List<Fichier> listeFichier = new ArrayList<>();

    public String rechercheCouleurDominanante(int choix) {
        StringBuilder msg;
        msg = new StringBuilder(MoteurDeRecherche.rechercheParCouleur(choix));
        String[] attr = msg.toString().split(" ");
        for(String str : attr) {
            String[] s = str.split(":");
            listeFichier.add(new Fichier(Integer.parseInt(s[1]),s[0], TypeFichier.IMAGE_RGB));
        }

        msg = new StringBuilder();
        for(Fichier fichier : listeFichier) {
            msg.append(fichier.toString());
        }

        Application.bdHistoriqueRequete.getListeRequeteImage().add(new Requete(TypeRecherche.IMAGE_COULEUR_DOMINANTE,  Integer.toString(choix),new Date(), msg.toString()));

        return msg.toString();
    }

    public String rechercheImageParFichier() {
        StringBuilder stringBuilder = new StringBuilder();
        for (String word : MoteurDeRecherche.rechercheImageRGBParFichier().split(" ")) {
            int indiceDistance = word.indexOf(':');
            stringBuilder.append(word.substring(indiceDistance));
            stringBuilder.append("\n");
        }

        Application.bdHistoriqueRequete.getListeRequeteImage().add(new Requete(TypeRecherche.IMAGE_COULEUR_FICHIER, "", new Date(), stringBuilder.toString()));

        return stringBuilder.toString();
    }

}
