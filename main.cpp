#include <QApplication>
#include <QGridLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <vector>
#include "sudoku_solver.h"

class SudokuGUI : public QWidget {
    Q_OBJECT

public:
    SudokuGUI(QWidget *parent = nullptr) : QWidget(parent) {
        QGridLayout *layout = new QGridLayout;
        setLayout(layout);

        // Create input fields for the Sudoku grid
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                QLineEdit *input = new QLineEdit;
                input->setFixedWidth(40);
                layout->addWidget(input, row, col);
                inputs[row][col] = input;
            }
        }

        QPushButton *solveButton = new QPushButton("Solve Sudoku");
        layout->addWidget(solveButton, 9, 0, 1, 9);
        connect(solveButton, &QPushButton::clicked, this, &SudokuGUI::solveSudoku);

        setWindowTitle("Sudoku Solver");
    }

private slots:
    void solveSudoku() {
        std::vector<std::vector<int>> grid(9, std::vector<int>(9, 0));
        
        // Read input values into the grid
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                bool ok;
                int num = inputs[row][col]->text().toInt(&ok);
                grid[row][col] = ok ? num : 0; // Store value in grid, or 0 if input was invalid
            }
        }

        SudokuSolver solver;
        if (solver.solveSudoku(grid, 0, 0)) {
            // Display the solved Sudoku grid
            for (int row = 0; row < 9; ++row) {
                for (int col = 0; col < 9; ++col) {
                    inputs[row][col]->setText(QString::number(grid[row][col]));
                }
            }
        } else {
            // Show error message if no solution exists
            QMessageBox::information(this, "No Solution", "No solution exists for the given Sudoku puzzle.");
        }
    }

private:
    QLineEdit *inputs[9][9]; // Array to hold input fields for Sudoku
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SudokuGUI window;
    window.show();
    return app.exec();
}
