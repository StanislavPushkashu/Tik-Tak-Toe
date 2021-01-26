#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() { delete ui; };




private:
    Ui::MainWindow *ui;

    bool CurrentPlayer = true; // true - X | false - O
    bool StopGameClicked = false;

    bool TypeOPlayer = false, TypeXPlayer = false;

    int CheckGameArr[3][3] =
    {
        {4, 4, 4},
        {4, 4, 4},
        {4, 4, 4}
    };
    int PrivatedSlotAmount = 0;

    QVector <QPushButton *> Slot;

    void StartGame();
    void StopGame();
    void AboutGame();
    void Drawing(int index);
    int CheckResult();

    int CheckGameState();

    bool IsChosen();

};
#endif // MAINWINDOW_H
