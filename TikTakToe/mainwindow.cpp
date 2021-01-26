#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Making Grid
    Slot.resize(9);

    PrivatedSlotAmount = 0;

    for(int i = 0; i < 9; i++) {
        Slot[i] = new QPushButton(this);
        Slot[i]->setIcon(QIcon::fromTheme("C:/Users/Orange/Documents/QTProjects/TikTakToe/Resources/EmptyPhoto.png"));
        Slot[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        Slot[i]->setIconSize(QSize(250, 250));
        Slot[i]->setEnabled(false);
    }

    ui->TikTakGrid->addWidget(Slot[0], 0, 0);
    ui->TikTakGrid->addWidget(Slot[1], 0, 1);
    ui->TikTakGrid->addWidget(Slot[2], 0, 2);
    ui->TikTakGrid->addWidget(Slot[3], 1, 0);
    ui->TikTakGrid->addWidget(Slot[4], 1, 1);
    ui->TikTakGrid->addWidget(Slot[5], 1, 2);
    ui->TikTakGrid->addWidget(Slot[6], 2, 0);
    ui->TikTakGrid->addWidget(Slot[7], 2, 1);
    ui->TikTakGrid->addWidget(Slot[8], 2, 2);

    // Start and stop game connecting
    connect(ui->StartGameAction, &QAction::triggered, [=]() {
        if(IsChosen())
            StartGame();
        else
            QMessageBox::information(this, "Oops", "You need to chose all the parameters before starting the game!", QMessageBox::Ok);
    });
    connect(ui->StopGameAction, &QAction::triggered, [=]() {
        StopGameClicked = true;
        StopGame(); });

    // Player type connecting
    connect(ui->OPlayerAction, &QAction::triggered, [=]() {
        TypeOPlayer = true;
        TypeXPlayer = false;
    });
    connect(ui->XPlayerAction, &QAction::triggered, [=]() {
        TypeXPlayer = true;
        TypeOPlayer = false;
    });

    // exit connecting
    connect(ui->ExitGameAction, &QAction::triggered, [=]() { QApplication::exit(); });

    // about connecting
    connect(ui->AboutQTAction, &QAction::triggered, [=]() { QApplication::aboutQt(); });
}

void MainWindow::StartGame() {
    ui->PlayerTypeMenu->setEnabled(false);

    if(TypeOPlayer)
        CurrentPlayer = false;
    else
        CurrentPlayer = true;

    PrivatedSlotAmount = 0;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            CheckGameArr[i][j] = 4;

    for (int i = 0; i < Slot.size(); i++)
        Slot[i]->setEnabled(true);


    connect(Slot[0], &QPushButton::clicked, [=](){ Drawing(0); });
    connect(Slot[1], &QPushButton::clicked, [=](){ Drawing(1); });
    connect(Slot[2], &QPushButton::clicked, [=](){ Drawing(2); });
    connect(Slot[3], &QPushButton::clicked, [=](){ Drawing(3); });
    connect(Slot[4], &QPushButton::clicked, [=](){ Drawing(4); });
    connect(Slot[5], &QPushButton::clicked, [=](){ Drawing(5); });
    connect(Slot[6], &QPushButton::clicked, [=](){ Drawing(6); });
    connect(Slot[7], &QPushButton::clicked, [=](){ Drawing(7); });
    connect(Slot[8], &QPushButton::clicked, [=](){ Drawing(8); });
}

void MainWindow::StopGame() {

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            CheckGameArr[i][j] = 4;

    PrivatedSlotAmount = 0;

    for(int i = 0; i < 9; i++)
        delete Slot[i];

    for(int i = 0; i < 9; i++) {
        Slot[i] = new QPushButton(this);
        Slot[i]->setIcon(QIcon::fromTheme("C:/Users/Orange/Documents/QTProjects/TikTakToe/Resources/EmptyPhoto.png"));
        Slot[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        Slot[i]->setIconSize(QSize(250, 250));
        Slot[i]->setEnabled(false);
    }

    ui->TikTakGrid->addWidget(Slot[0], 0, 0);
    ui->TikTakGrid->addWidget(Slot[1], 0, 1);
    ui->TikTakGrid->addWidget(Slot[2], 0, 2);
    ui->TikTakGrid->addWidget(Slot[3], 1, 0);
    ui->TikTakGrid->addWidget(Slot[4], 1, 1);
    ui->TikTakGrid->addWidget(Slot[5], 1, 2);
    ui->TikTakGrid->addWidget(Slot[6], 2, 0);
    ui->TikTakGrid->addWidget(Slot[7], 2, 1);
    ui->TikTakGrid->addWidget(Slot[8], 2, 2);


    for(int i = 0; i < Slot.size(); i++)
        Slot[i]->setEnabled(false);

    CurrentPlayer = true;

    if (StopGameClicked == true) {
        QMessageBox::information(this, "STOP", "The game was stopped!");
        StopGameClicked = false;
    }
    ui->PlayerTypeMenu->setEnabled(true);
}

void MainWindow::Drawing(int index) {
        if(CurrentPlayer == true) {
            Slot[index]->setIcon(QIcon::fromTheme("C:/Users/Orange/Documents/QTProjects/TikTakToe/Resources/X.png"));
            Slot[index]->setEnabled(false);
            if (index == 0)
                CheckGameArr[0][0] = 1;
            else
                CheckGameArr[index / 3][index % 3] = 1;
        } else {
            Slot[index]->setIcon(QIcon::fromTheme("C:/Users/Orange/Documents/QTProjects/TikTakToe/Resources/O2.png"));
            Slot[index]->setEnabled(false);
            if (index == 0)
                CheckGameArr[0][0] = 0;
            else
                CheckGameArr[index / 3][index % 3] = 0;
        }


        PrivatedSlotAmount++;
        CurrentPlayer = !CurrentPlayer;

    if (CheckGameState() == 1) {
        QMessageBox::information(this, "WIN", "X Player WON!", QMessageBox::Ok);
        StopGame();
    } else if (CheckGameState() == 0) {
        QMessageBox::information(this, "DRAW", "NONE OF YOU WON!");
        StopGame();
    } else if (CheckGameState() == -1) {
        QMessageBox::information(this, "LOSE", "O Player WON!");
        StopGame();
    }
}

int MainWindow::CheckGameState()
{
//  ||||| WIN STATE |||||

    // check all rows
    if ((CheckGameArr[0][0] + CheckGameArr[0][1] + CheckGameArr[0][2]) == 3) {
        return 1;
    }
    else if ((CheckGameArr[1][0] + CheckGameArr[1][1] + CheckGameArr[1][2]) == 3) {
        return 1;
    }
    else if ((CheckGameArr[2][0] + CheckGameArr[2][1] + CheckGameArr[2][2]) == 3) {
        return 1;
    }

    // check all columns

    else if ((CheckGameArr[0][0] + CheckGameArr[1][0] + CheckGameArr[2][0]) == 3) {
        return 1;
    }
    else if ((CheckGameArr[0][1] + CheckGameArr[1][1] + CheckGameArr[2][1]) == 3) {
        return 1;
    }
    else if ((CheckGameArr[0][2] + CheckGameArr[1][2] + CheckGameArr[2][2]) == 3) {
        return 1;
    }

    // check diagonals

    else if ((CheckGameArr[0][0] + CheckGameArr[1][1] + CheckGameArr[2][2]) == 3)
        return 1;
    else if ((CheckGameArr[2][0] + CheckGameArr[1][1] + CheckGameArr[0][2]) == 3)
        return 1;




// ||||| LOSE STATE |||||

    // check all rows
    if ((CheckGameArr[0][0] + CheckGameArr[0][1] + CheckGameArr[0][2]) == 0) {
        return -1;
    }
    else if ((CheckGameArr[1][0] + CheckGameArr[1][1] + CheckGameArr[1][2]) == 0) {
        return -1;
    }
    else if ((CheckGameArr[2][0] + CheckGameArr[2][1] + CheckGameArr[2][2]) == 0) {
        return -1;
    }

    // check all columns

    else if ((CheckGameArr[0][0] + CheckGameArr[1][0] + CheckGameArr[2][0]) == 0) {
        return -1;
    }
    else if ((CheckGameArr[0][1] + CheckGameArr[1][1] + CheckGameArr[2][1]) == 0) {
        return -1;
    }
    else if ((CheckGameArr[0][2] + CheckGameArr[1][2] + CheckGameArr[2][2]) == 0) {
        return -1;
    }

    // check diagonals

    else if ((CheckGameArr[0][0] + CheckGameArr[1][1] + CheckGameArr[2][2]) == 0)
        return -1;
    else if ((CheckGameArr[2][0] + CheckGameArr[1][1] + CheckGameArr[0][2]) == 0)
        return -1;



//  ||||| DRAW STATE |||||

    else if (PrivatedSlotAmount == 9)
            return 0;

//  ||||| 2 == none state |||||
    else
        return 2;
}

bool MainWindow::IsChosen() {
    if (TypeOPlayer || TypeXPlayer)
        return true;
    return false;
}
