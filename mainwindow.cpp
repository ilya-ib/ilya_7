#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if ((ui->Xa->text().toDouble() == 0) and (ui->Xb->text().toDouble() == 0)) {
        QMessageBox::warning(this, "WARNING", "Интервал не может быть равен 0");
    }
    else if ( ((ui->Xa->text().toDouble() == false) and (ui->Xa->text() != "0")) or ((ui->Xb->text().toDouble() == false) and (ui->Xb->text() != "0"))
              or ((ui->A->text().toDouble() == false) and (ui->A->text() != "0")) or ((ui->B->text().toDouble() == false) and (ui->B->text() != "0"))) {
        QMessageBox::warning(this, "WARNING", "Неправильный ввод");
    }
    else if ( (ui->Xa->text().toDouble() < -300) or (ui->Xa->text().toDouble() > 300) ) {
        QMessageBox::warning(this,"WARNING","Введенное число > или < - 300");
    }
    else if ( (ui->Xb->text().toDouble() < -300) or (ui->Xb->text().toDouble() > 300) ) {
        QMessageBox::warning(this,"WARNING","Введенное число > или < - 300");
    }
    else if ( (ui->Xa->text().toDouble() >= ui->Xb->text().toInt()) or (ui->Xb->text().toDouble() <= ui->Xa->text().toDouble() )) {
        QMessageBox::warning(this, "WARNING","Неправильный интервал");
    }
    else if ( (ui->A->text().toDouble() < -300) or (ui->A->text().toDouble() > 300)) {
        QMessageBox::warning(this, "Ошибка!","Введенное число < или > - 300");
    }
    else if ( (ui->B->text().toDouble() < -300) or (ui->B->text().toDouble() > 300)) {
        QMessageBox::warning(this, "Ошибка!","Введенное число < или > - 300");
    }

    else {
        A = ui->A->text().toDouble();
        Xa = ui->Xa->text().toDouble();
        Xb = ui->Xb->text().toDouble();
        h = 0.1;


        N = (Xb - Xa) / h + 2;
        QVector<double> x(N), y(N);

        Z = 0.1*((double)(rand()%10)/(double)10+(double)(rand()%10));

        int i = 0;
        for (double X = Xa; X <= Xb; X += h) {
          x[i] = X;
          y[i] = A * sin(pow(X,4)) + B*cos(X) + Z; // формула функции
          i++;
        }

        ui->widget->clearGraphs();
        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x, y);

        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("y");

        ui->widget->xAxis->setRange(Xa, Xb);

        double minY = y[0], maxY = y[0];
        for (int i = 1; i < N; i++) {
          if (y[i] < minY) minY = y[i];
          if (y[i] > maxY) maxY = y[i];
        }

        ui->widget->yAxis->setRange(minY, maxY);


        ui->widget->replot();
        x.clear();
        y.clear();
    }
}

