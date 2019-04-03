package model;

import java.io.Serializable;
import java.util.Date;

public class Requete implements Serializable {

    private TypeRecherche typeRecherche;
    private Date date;
    private String requete;
    private String resultat;

    public String getResultat() {
        return resultat;
    }

    public Requete (TypeRecherche typeRecherche, String requete, Date date, String resultat) {
        this.requete = requete;
        this.typeRecherche = typeRecherche;
        this.date = date;
        this.resultat = resultat;
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
