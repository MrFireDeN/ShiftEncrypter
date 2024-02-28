
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QList<int> getKeys(QString);
    QStringList getBlocks(QString, int);

    void encrypt();
    void unencrypt();

    void on_btnEncrypt_clicked();
    void on_btnUnencrypt_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
