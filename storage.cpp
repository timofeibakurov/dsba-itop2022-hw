#include "storage.h"

#include <stdexcept>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>

Storage::Storage(QObject* parent)
    : QObject{parent}
{
    _model = new QStringListModel(this);
}

void Storage::loadFile(const QString& fileName)
{
    _fileName = fileName;
    if(readFile())
        emit onFileReaded(/*some potential parameters here*/);
}

bool Storage::readFile()
{
    if (_fileName.isEmpty())
        throw std::invalid_argument("File name not set");

    QFile file(_fileName);

    if(!file.open(QIODevice::ReadOnly))
    {

        QMessageBox box;
        box.setText("Can't open a file to read. So pity");
        box.exec();

        return false;
    }
    // here we use a local storage for reading lines from the file in

    // we use a special helper to exctract data in a convenient way
    QTextStream fStream(&file);
    QStringList storage;
    while (!fStream.atEnd())
    {
        QString line = fStream.readLine();
        if (!line.isNull())
        {
             storage << line;        // storage.append(line)
        }
    }

    file.close();

    _val = true;
    // now we can notify model that we have a string list for her
    _model->setStringList(storage);

    return true;
}
