#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentAction(NoAction),
    isEmpty(true)
{
    ui->setupUi(this);
    connect(ui->btnClear, SIGNAL(clicked(bool)), this, SLOT(clear()));
    connect(ui->btnPlus, SIGNAL(clicked(bool)), this, SLOT(negationClicked()));
    connect(ui->btnPer, SIGNAL(clicked(bool)), this, SLOT(percentageClicked()));
    connect(ui->btnDot, SIGNAL(clicked(bool)), this, SLOT(decimalPointClicked()));
    connect(ui->btnEqu, SIGNAL(clicked(bool)), this,  SLOT(evoluationClicked()));

    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));
    connect(ui->btnSub, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));
    connect(ui->btnMul, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));
    connect(ui->btnDiv, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));

    connect(ui->btn0, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn1, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn2, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn3, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn4, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn5, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn6, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn7, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn8, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));
    connect(ui->btn9, SIGNAL(clicked(bool)),this, SLOT(inputNumber()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear(){
    if(ui->btnClear->text() == "AC"){
        currentAction = NoAction;
        currentNumber = "0";
        lastNumber = "0";
        isEmpty = true;
    }
    else if(ui->btnClear->text() == "c"){
        currentNumber = "0";
        isEmpty = true;
        ui->btnClear->setText("AC");
    }
    displayNumber();
}

void MainWindow::actionChanged(){
    QPushButton *currentButton = qobject_cast<QPushButton *>(this->sender());
    // which one emit the signal  ↑ made it.
    if(currentButton){
        isEmpty = false;
        if(currentButton == ui->btnAdd){
            currentAction = AdditionFlag;
            statusBar()->showMessage(" plus", 3000);
        }else if(currentButton == ui->btnSub){
            currentAction = SubtractionFlag;
            statusBar()->showMessage(" sub", 3000);
        }else if(currentButton == ui->btnMul){
            currentAction = MultiplicationFlag;
            statusBar()->showMessage(" mul", 3000);
        }else if(currentButton == ui->btnDiv){
            currentAction = DivisionFlag;
            statusBar()->showMessage(" div", 3000);
        }else{
            currentAction = NoAction;
        }
    }
}

void MainWindow::inputNumber(){
    QPushButton *currentButton = qobject_cast<QPushButton *>(this->sender());
     if(currentButton){
        ui->btnClear->setText("c");
        if(!isEmpty){
            lastNumber = currentNumber;
            currentNumber.clear();
            isEmpty = true;
        }
        if(currentNumber == "0"){
            currentNumber.clear();
        }
        if(currentButton == ui->btn0){
            currentNumber.append("0");
            statusBar()->showMessage("0", 3000);
        }else if(currentButton == ui->btn1){
            currentNumber.append("1");
            statusBar()->showMessage("1", 3000);
        }else if(currentButton == ui->btn2){
            currentNumber.append("2");
            statusBar()->showMessage("2", 3000);
        }else if( currentButton == ui->btn3){
            currentNumber.append("3");
            statusBar()->showMessage("3", 3000);
        }else if(currentButton == ui->btn4){
            currentNumber.append("4");
            statusBar()->showMessage("4", 3000);
        }else if(currentButton == ui->btn5){
            currentNumber.append("5");
            statusBar()->showMessage("5", 3000);
        }else if(currentButton == ui->btn6){
            currentNumber.append("6");
            statusBar()->showMessage("6", 3000);
        }else if(currentButton == ui->btn7){
            currentNumber.append("7");
            statusBar()->showMessage("7", 3000);
        }else if(currentButton == ui->btn8){
            currentNumber.append("8");
            statusBar()->showMessage("8", 3000);
        }else if(currentButton == ui->btn9){
            currentNumber.append("9");
            statusBar()->showMessage("9", 3000);
        }else{
            qDebug() << "something wrong!";
            return;
        }
    }
    qDebug() <<currentNumber;
    displayNumber();
}

void MainWindow::displayNumber(){
    ui->label->setText(currentNumber);
}

void MainWindow::negationClicked(){
    if(!isEmpty || currentNumber.length() == 0){
        currentNumber = "0";
        isEmpty = true;
    }else{
        if(currentNumber.at(0) == "-"){
            currentNumber.remove(0, 1);
        }else{
            currentNumber.push_front("-");
        }
    }
    displayNumber();
    statusBar()->showMessage(" change ", 3000);
}

void MainWindow::percentageClicked(){
    if(!isEmpty){
        currentNumber = "0";
        isEmpty = true;
    }else{
        double number = currentNumber.toDouble()/100;
        currentNumber = QString::number(number);
    }
    displayNumber();
    statusBar()->showMessage(" % input", 3000);
}
void MainWindow::decimalPointClicked(){
    if(!isEmpty){
        currentNumber = "0.";
        isEmpty = true;
    }else if(currentNumber.indexOf("-") == -1){
        currentNumber.push_back(".");
    }
    displayNumber();
    statusBar()->showMessage(" . input", 3000);
}
void MainWindow::evoluationClicked(){
    if(currentAction == NoAction){
        statusBar()->showMessage(" chose one to calculate", 3000);
        return ;
    }else if(currentAction == AdditionFlag)
        currentNumber = QString::number(lastNumber.toDouble()+currentNumber.toDouble());
    else if(currentAction == SubtractionFlag)
        currentNumber = QString::number(lastNumber.toDouble()-currentNumber.toDouble());
    else if(currentAction == MultiplicationFlag)
        currentNumber = QString::number(lastNumber.toDouble()*currentNumber.toDouble());
    else if(currentAction == DivisionFlag)
        currentNumber = QString::number(lastNumber.toDouble()/currentNumber.toDouble());
    else
        return;
    currentAction = NoAction;
    displayNumber();
    statusBar()->showMessage("suc", 3000);
}
