#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

enum ActionFlag{
    //  which button you clicked
    NoAction,
    AdditionFlag,
    SubtractionFlag,
    MultiplicationFlag,
    DivisionFlag
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ActionFlag currentAction;
    QString lastNumber;
    QString currentNumber;
    bool isEmpty;
public slots:
    void clear();
    void actionChanged();
    void inputNumber();
    void displayNumber();
    void negationClicked();
    void percentageClicked();
    void decimalPointClicked();
    void evoluationClicked();
};

#endif // MAINWINDOW_H
