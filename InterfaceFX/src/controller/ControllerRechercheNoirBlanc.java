package controller;

import model.*;
import view.Application;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class ControllerRechercheNoirBlanc {

    private List<Fichier> listeFichier = new ArrayList<>();

    public String rechercheParNiveau(int choix) {
        StringBuilder msg;
        msg = new StringBuilder(MoteurDeRecherche.rechercheNoirEtBlanc(choix));
        String[] attr = msg.toString().split(" ");
        for(String str : attr) {
            String[] s = str.split(":");
            listeFichier.add(new Fichier(Integer.parseInt(s[1]),s[0], TypeFichier.IMAGE_NB));
        }

        msg = new StringBuilder();
        for(Fichier fichier : listeFichier) {
            msg.append(fichier.toString());
        }

        Application.bdHistoriqueRequete.getListeRequeteImage().add(new Requete(TypeRecherche.IMAGE_NB_NIVEAU,  Integer.toString(choix), new Date(), msg.toString()));

        return msg.toString();
    }

    public String rechercheImageParFichier() {
        StringBuilder stringBuilder = new StringBuilder();
        for (String word : MoteurDeRecherche.rechercheImageNBParFichier().split(" ")) {
            int indiceDistance = word.indexOf(':');
            stringBuilder.append(word.substring(indiceDistance));
            stringBuilder.append("\n");
        }

        Application.bdHistoriqueRequete.getListeRequeteImage().add(new Requete(TypeRecherche.IMAGE_NB_FICHIER, "", new Date(), stringBuilder.toString()));

        return stringBuilder.toString();
    }

}
