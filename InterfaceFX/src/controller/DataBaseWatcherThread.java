package controller;

import javafx.application.Platform;
import javafx.scene.control.Alert;
import viewFX.Main;

import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class DataBaseWatcherThread extends Thread {

    private WatchService watchService;
    private static boolean isPopupEnabled = true;
    private List<String> filesText;

    @Override
    public void run() {
        init();
        try {
            watchService = FileSystems.getDefault().newWatchService();

            Path pathText = Paths.get("../noyau_c/Base_de_donnees/TEXTES");
            Path pathImageRGB = Paths.get("../noyau_c/IMG_et_AUDIO/TEST_RGB");
            Path pathImageNB = Paths.get("../noyau_c/IMG_et_AUDIO/TEST_RGB");
            Path pathSound = Paths.get("../noyau_c/IMG_et_AUDIO/TEST_SON");

            pathText.register(watchService, StandardWatchEventKinds.ENTRY_CREATE, StandardWatchEventKinds.ENTRY_DELETE);
            pathImageRGB.register(watchService, StandardWatchEventKinds.ENTRY_CREATE, StandardWatchEventKinds.ENTRY_DELETE);
            pathImageNB.register(watchService, StandardWatchEventKinds.ENTRY_CREATE, StandardWatchEventKinds.ENTRY_DELETE);
            pathSound.register(watchService, StandardWatchEventKinds.ENTRY_CREATE, StandardWatchEventKinds.ENTRY_DELETE);

            WatchKey key;
            while ((key = watchService.take()) != null) {
                for (WatchEvent<?> event : key.pollEvents()) {
                    if (event.kind() == StandardWatchEventKinds.ENTRY_CREATE && isPopupEnabled) {
                        Platform.runLater(() -> Main.alert(Alert.AlertType.WARNING,"Mise à jours de la liste des fichiers de la base, indexation du nouveau fichier : " + event.context() + "."));
                        filesText.add(event.context().toString());
                    } else if (event.kind() == StandardWatchEventKinds.ENTRY_DELETE && isPopupEnabled) {
                        Platform.runLater(() -> Main.alert(Alert.AlertType.WARNING,"Mise à jours de la liste des fichiers de la base, suppréssion du fichier : " + event.context() + "."));
                    }
                }
                key.reset();
            }
        } catch (IOException | InterruptedException  e) {
            Platform.runLater(() -> Main.alert(Alert.AlertType.ERROR, e.toString()));
        } catch (ClosedWatchServiceException e) {
            System.out.println("Fermeture de l'application.");
        }
    }

    private void init() {
        File folderText = new File("../noyau_c/Base_de_donnees/TEXTES");
        filesText = new ArrayList<>();

        for (File f : Objects.requireNonNull(folderText.listFiles())) {
            filesText.add(f.toString());
        }
    }

    public void stopThread() {
        try {
            watchService.close();
        } catch(IOException e) {
            Platform.runLater(() -> Main.alert(Alert.AlertType.ERROR,e.toString()));
        }
    }

    public static void enablePopups() {
        isPopupEnabled = true;
    }

    public static void disablePopups() {
        isPopupEnabled = false;
    }

    public static boolean isPopupEnable() {
        return isPopupEnabled;
    }

}
