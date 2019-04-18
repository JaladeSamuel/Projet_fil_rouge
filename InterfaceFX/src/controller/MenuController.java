package controller;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.util.Pair;
import view.Application;
import viewFX.Main;

import java.io.IOException;
import java.util.Optional;

public class MenuController {

    public static Parent root;
    public static Stage stage;

    public void handleKeyInput(KeyEvent keyEvent) {
    }

    public void handleAboutActionQuitterEnregistrer(ActionEvent actionEvent) {
        Application.enregistrerHistorique();
        Platform.exit();
        System.exit(1);
    }

    public void handleAboutActionQuitter(ActionEvent actionEvent) {
        Platform.exit();
        System.exit(1);
    }

    public void notifyClickedExit(Event event) {
        System.out.println(event);
    }

    @FXML
    public void runInterfaceTexte(ActionEvent actionEvent) throws Exception {
        root = FXMLLoader.load(getClass().getResource("/viewFX/screenTexte.fxml"));
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }

    @FXML
    public void runInterfaceImage(ActionEvent actionEvent) throws Exception {
        root = FXMLLoader.load(getClass().getResource("/viewFX/screenImage.fxml"));
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }

    @FXML
    public void runInterfaceSon(ActionEvent actionEvent) {
        try {
            root = FXMLLoader.load(getClass().getResource("/viewFX/screenSon.fxml"));
            stage.setScene(new Scene(root, 600, 400));
            stage.show();
        }
        catch(IOException e) {
            e.printStackTrace();
        }
    }

    public void handlerMenuItemAdministrateur(ActionEvent actionEvent) {
        if(!Main.administrateurConnecte) {
            //Dialog
            Dialog<Pair<String,String>> dialog = new Dialog<>();
            dialog.setTitle("Adminsitrateur");
            dialog.setHeaderText("Connexion administrateur (username : admin)");

            ButtonType loginButtonType = new ButtonType("Login", ButtonBar.ButtonData.OK_DONE);
            dialog.getDialogPane().getButtonTypes().addAll(loginButtonType, ButtonType.CANCEL);

            dialog.setGraphic(new ImageView(this.getClass().getResource("../image/loginAdmin.png").toString()));

            // Création username et password
            GridPane grid = new GridPane();
            grid.setHgap(10);
            grid.setVgap(10);
            grid.setPadding(new Insets(20, 150, 10, 10));

            TextField username = new TextField();
            username.setPromptText("Username");
            PasswordField password = new PasswordField();
            password.setPromptText("Password");

            grid.add(new Label("Username:"), 0, 0);
            grid.add(username, 1, 0);
            grid.add(new Label("Password:"), 0, 1);
            grid.add(password, 1, 1);

            Node loginButton = dialog.getDialogPane().lookupButton(loginButtonType);
            loginButton.setDisable(true);

            username.textProperty().addListener((observable, oldValue, newValue) -> {
                loginButton.setDisable(newValue.trim().isEmpty());
            });

            dialog.getDialogPane().setContent(grid);

            // Requete sur l'username par defaut
            Platform.runLater(() -> username.requestFocus());

            // On créer la paire
            dialog.setResultConverter(dialogButton -> {
                if (dialogButton == loginButtonType) {
                    return new Pair<>(username.getText(), password.getText());
                }
                return null;
            });

            Optional<Pair<String, String>> result = dialog.showAndWait();

            result.ifPresent(usernamePassword -> {
                if(usernamePassword.getKey().equals("admin") && usernamePassword.getValue().equals("123upssitech")){
                    Main.administrateurConnecte = true;
                    try {
                        root = FXMLLoader.load(getClass().getResource("/viewFX/screenAdministrateur.fxml"));
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    stage.setScene(new Scene(root, 800, 400));
                    stage.show();
                } else {
                    handlerMenuItemAdministrateur(actionEvent);
                }
            });
        } else {
            try {
                root = FXMLLoader.load(getClass().getResource("/viewFX/screenAdministrateur.fxml"));
            } catch (IOException e) {
                e.printStackTrace();
            }
            stage.setScene(new Scene(root, 800, 600));
            stage.show();
        }

    }

    public void handlerVisualiserHistorique(ActionEvent actionEvent) {
        try {
            root = FXMLLoader.load(getClass().getResource("/viewFX/screenHistorique.fxml"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        stage.setScene(new Scene(root, 600, 400));
        stage.show();
    }
}
