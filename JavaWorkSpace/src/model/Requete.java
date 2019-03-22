package model;

import java.io.Serializable;
import java.util.Date;

public class Requete implements Serializable {

    private TypeRecherche typeRecherche;
    private Date date;
    private String requete;

    public Requete (TypeRecherche typeRecherche, String requete, Date date) {
        this.requete = requete;
        this.typeRecherche = typeRecherche;
        this.date = date;
    }

    public TypeRecherche getTypeRecherche() {
        return typeRecherche;
    }

    Date getDate() {
        return date;
    }

    String getRequete() {
        return requete;
    }

}
