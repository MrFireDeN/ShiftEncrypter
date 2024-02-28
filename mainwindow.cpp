
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

// Создание QList с ключами
QList<int> MainWindow::getKeys(QString textKeys) {
    QStringList strList = textKeys.split(", ");

    QList<int> keysList;

    for (const QString &str : strList){
        keysList.append(str.toInt());
    }

    return keysList;
}

// Создание блоков
QStringList MainWindow::getBlocks(QString text, int blockLength) {
    QStringList blockList;

    // Заполнение блоков
    for (int i = 0; i < text.length(); i += blockLength) {
        blockList.append(text.mid(i, blockLength));
    }

    // Заполнение последнего блока пробелами
    while (blockList.last().length() < blockLength) {
        blockList.last().append(' ');
    }

    return blockList;
}

void MainWindow::encrypt() {
    // Дополнительные переменные
    QString textKeys = ui->keysToCrypt->text();
    QString text = ui->textUnencrypted->text();

    // Создание QList с ключами
    QList<int> keysList = getKeys(textKeys);
    // Создание блоков
    QStringList blockList = getBlocks(text, keysList.length());

    // Шифрование сообщения
    QString message = "";
    for (QString block : blockList) {
        QString newBlock = block;

        for (int i = 0; i < block.length(); ++i) {
            newBlock[i] = block[keysList[i] - 1];
        }

        block = newBlock;
        message += block;
    }

    ui->messageEncrypted->setText(message);
}

void MainWindow::unencrypt() {
    // Дополнительные переменные
    QString textKeys = ui->keysToUnencrypt->text();
    QString text = ui->textEncrypted->text();

    // Создание QList с ключами
    QList<int> keysList = getKeys(textKeys);
    // Создание блоков
    QStringList blockList = getBlocks(text, keysList.length());

    // Расшивровка сообщения
    QString message = "";
    for (QString block : blockList) {
        QString newBlock = block;

        for (int i = 0; i < block.length(); ++i) {
            newBlock[keysList[i] - 1] = block[i];
        }

        block = newBlock;
        message += block;
    }

    ui->messageUnencrypted->setText(message);
}


void MainWindow::on_btnEncrypt_clicked()
{
    encrypt();
}


void MainWindow::on_btnUnencrypt_clicked()
{
    unencrypt();
}

