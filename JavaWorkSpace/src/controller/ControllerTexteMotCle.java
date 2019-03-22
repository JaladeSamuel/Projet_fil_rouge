package controller;

import model.*;

import java.util.*;

public class ControllerTexteMotCle {

    private List<FichierTexte> listeFichierTexte = new ArrayList<>();
    private List<String> selectionMotARechercher = new ArrayList<>();
    private List<String> selectionMotANePasRechercher = new ArrayList<>();
    private BDHistoriqueRequete bdHistoriqueRequete = new BDHistoriqueRequete();

    public List<String> getSelectionMotARechercher() {
        return selectionMotARechercher;
    }

    public List<String> getSelectionMotANePasRechercher() {
        return selectionMotANePasRechercher;
    }

    public void clear() {
        listeFichierTexte = new ArrayList<>();
        selectionMotANePasRechercher = new ArrayList<>();
        selectionMotARechercher = new ArrayList<>();
    }

    @Override
    public String toString() {
        return "ControllerTexteMotCle{" +
                "listeFichierTexte=" + listeFichierTexte +
                ", selectionMotARechercher=" + selectionMotARechercher +
                ", selectionMotANePasRechercher=" + selectionMotANePasRechercher +
                '}';
    }

    private String resultatRequete() {
        StringBuilder msg;
        if(listeFichierTexte.isEmpty()) {
            return  "Aucun fichier dans la base ne correspond à votre recherche.";
        }

        msg = new StringBuilder("Liste des fichiers correspondant à votre recherche : \n");
        for (FichierTexte fichier : listeFichierTexte) {
            msg.append(fichier.getNom()).append("\n");
        }
        return msg.toString();
    }

    public String rechercheParMotCle() {

        Map<String,ArrayList<FichierTexte>> map = new HashMap<>();

        for(String motCle : selectionMotARechercher) {
            String str = MoteurDeRecherche.rechercheParMotCle(motCle);
            map.put(motCle,new ArrayList<>());
            if (!str.contains("Aucun resultat n'a été trouvé.")) {
                String[] arrOfStr = str.split(" ");
                for (String s : arrOfStr) {
                    String[] attr = s.split(":");
                    map.get(motCle).add(new FichierTexte(Integer.parseInt(attr[1]),attr[0]));
                }
            }
        }


        for (FichierTexte fichier : map.get(selectionMotARechercher.get(0))) {
            boolean isInAllLists = true;
            for (String motCle : map.keySet()) {
                if (!map.get(motCle).contains(fichier)) {
                    isInAllLists = false;
                    break;
                }
            }

            if (isInAllLists && !listeFichierTexte.contains(fichier)) {
                listeFichierTexte.add(fichier);
            }
        }



        if(!selectionMotANePasRechercher.isEmpty()) {
            for (String s1 : selectionMotANePasRechercher) {
                ArrayList<FichierTexte> tamp = new ArrayList<>();
                String str = MoteurDeRecherche.rechercheParMotCle(s1);
                if (!str.contains("Aucun resultat n'a été trouvé.")) {
                    String[] arrOfStr = str.split(" ");
                    for (String s : arrOfStr) {
                        String[] attr = s.split(":");
                        for (FichierTexte fichier : listeFichierTexte) {
                            if (fichier.getNom().equals(attr[0])) {
                                tamp.add(fichier);
                            }
                        }
                    }
                    listeFichierTexte.removeAll(tamp);
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
        bdHistoriqueRequete.getListeRequeteTexte().add(new Requete(TypeRecherche.TEXTE_MOT_CLE, requete.toString(),new Date()));
        return resultatRequete();
    }
}
