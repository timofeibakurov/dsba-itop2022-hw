#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QStringListModel>

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = nullptr);

public:
    // Opens a file by the given fileName and reads data from it to the ..model..
    void loadFile(const QString& fileName);

    QStringListModel* getModel() const { return _model; }

    bool getVal() {return _val;}

    QStringList getLabels() const {return _labels;}

    void setLabels(QStringList labels) {_labels = labels;}

protected:
    bool readFile();            ///< read a file actually

protected:
    QString _fileName;          ///< stores a given filename
    QStringListModel* _model;   ///< stores a ptr to our model
    bool _val = false;
    QStringList _labels;

signals:
    void onFileReaded();        ///< sinal is emit when a file with model data is read succesfully.
};

#endif // STORAGE_H
