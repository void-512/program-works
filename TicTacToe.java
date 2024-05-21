import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class TicTacToe extends Application {
    private boolean xTurn = true;
    private Button[][] board = new Button[3][3];

    public static void main() {
        launch();
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Tic Tac Toe");

        GridPane grid = new GridPane();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = new Button();
                board[i][j].setPrefSize(100, 100);
                board[i][j].setOnAction(e -> buttonClick((Button) e.getSource()));
                grid.add(board[i][j], j, i);
            }
        }

        Scene scene = new Scene(grid, 400, 400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void buttonClick(Button button) {
        if (button.getText().equals("")) {
            if (xTurn) {
                button.setText("X");
            } else {
                button.setText("O");
            }
            xTurn = !xTurn;

            checkWinner();
        }
    }

    private void checkWinner() {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (!board[i][0].getText().equals("") &&
                board[i][0].getText().equals(board[i][1].getText()) &&
                board[i][1].getText().equals(board[i][2].getText())) {
                showWinner(board[i][0].getText());
                return;
            }
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (!board[0][j].getText().equals("") &&
                board[0][j].getText().equals(board[1][j].getText()) &&
                board[1][j].getText().equals(board[2][j].getText())) {
                showWinner(board[0][j].getText());
                return;
            }
        }

        // Check diagonals
        if (!board[0][0].getText().equals("") &&
            board[0][0].getText().equals(board[1][1].getText()) &&
            board[1][1].getText().equals(board[2][2].getText())) {
            showWinner(board[0][0].getText());
            return;
        }

        if (!board[0][2].getText().equals("") &&
            board[0][2].getText().equals(board[1][1].getText()) &&
            board[1][1].getText().equals(board[2][0].getText())) {
            showWinner(board[0][2].getText());
            return;
        }

        // Check for draw
        boolean draw = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j].getText().equals("")) {
                    draw = false;
                    break;
                }
            }
        }
        if (draw) {
            showDraw();
        }
    }

    private void showWinner(String winner) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Game Over");
        alert.setContentText(winner + " wins.");
        alert.showAndWait();
        resetBoard();
    }

    private void showDraw() {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Game Over");
        alert.setHeaderText("It's a draw!");
        alert.setContentText("No winner this time.");
        alert.showAndWait();
        resetBoard();
    }

    private void resetBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j].setText("");
            }
        }
        xTurn = true;
    }
}