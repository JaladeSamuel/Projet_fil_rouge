package view;

import java.util.Scanner;

public class Clavier {
    private static Scanner scanner = new Scanner(System.in);

    public static int entrerClavierInt() { //
        return scanner.nextInt();
    }

    public static String entrerClavierString() {
        return scanner.next();
    }

    public static int getIntRange(String message, int min, int max) {
        int choix = -1;
        while (choix < min || choix > max) {
            System.out.print(message + "Choix : ");
            choix = entrerClavierInt();
            if(choix < 1 || choix > 3) {
                System.out.println("Erreur veuillez entrer un chiffre entre " + min + " et " + max + " ...");
            }
        }

        System.out.println();
        return choix;
    }

}


