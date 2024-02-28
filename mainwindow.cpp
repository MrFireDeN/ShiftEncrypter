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

    if (!keysValidator(strList)) {
        QMessageBox::information(nullptr, "Ошибка", "Неверные ключи");
        return {1};
    }

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

    if (text == "" or textKeys == "")
        return;

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

    qDebug() << text << " " << message;
    calculateFrequancy(text, message);
    ui->messageEncrypted->setText(message);
}

void MainWindow::unencrypt() {
    // Дополнительные переменные
    QString textKeys = ui->keysToUnencrypt->text();
    QString text = ui->textEncrypted->text();

    if (text == "" or textKeys == "")
        return;

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

    calculateFrequancy(message, text);
    ui->messageUnencrypted->setText(message);
}

// Валидатор для ключей
bool MainWindow::keysValidator(QStringList keysList) {
    keysList.sort();

    for (int i = 0; i < keysList.length(); ++i) {
        if (keysList[i] != QString::number(i+1))
            return false;
    }

    return true;
}

void MainWindow::calculateFrequancy(QString unencrytedText, QString encrytedText) {
    unencryptedMap.clear();
    for (QChar letter: unencrytedText) {
        if (!unencryptedMap.contains(letter)) {
            unencryptedMap.insert(letter, 1);
        }
        else{
            unencryptedMap[letter]++;
        }
    }

    QString result1  = "";
    for (auto i = unencryptedMap.begin(); i != unencryptedMap.end(); ++i) {
        result1 += QString("\'") + i.key() + "\': " + QString::number(i.value()) + " ";
    }
    ui->frequencyUnencrypted->setText(result1);

    encryptedMap.clear();
    for (QChar letter: encrytedText) {
        if (!encryptedMap.contains(letter)) {
            encryptedMap.insert(letter, 1);
        }
        else{
            encryptedMap[letter]++;
        }
    }

    QString result2 = "";
    for (auto i = encryptedMap.begin(); i != encryptedMap.end(); ++i) {
        result2 += QString("\'") + i.key() + "\': " + QString::number(i.value()) + " ";
    }
    ui->frequencyEncrypted->setText(result2);
}

void MainWindow::on_btnEncrypt_clicked()
{
    encrypt();
}


void MainWindow::on_btnUnencrypt_clicked()
{
    unencrypt();
}

