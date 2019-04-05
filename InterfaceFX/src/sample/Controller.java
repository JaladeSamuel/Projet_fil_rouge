package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;

public class Controller {

    @FXML
    protected void handlerButton(ActionEvent event) {
        System.out.println("salut");
    }

    @FXML
    protected void handlerComboBox(ActionEvent event) {
        System.out.println(event.toString());
    }

}
