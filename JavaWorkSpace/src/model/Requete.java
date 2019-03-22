package model;

import java.util.Date;

public class Requete {

    private TypeRecherche typeRecherche;
    private Date date;
    private String requete;

    public Requete (TypeRecherche typeRecherche, String requete, Date date) {
        this.requete = requete;
        this.typeRecherche = typeRecherche;
        this.date = date;
    }

}
