#ifndef TABLEMODELTALKER_H
#define TABLEMODELTALKER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QSqlDatabase>

class DBTalker : public QObject
{
    Q_OBJECT
public:
    explicit DBTalker(QObject *parent = 0);
    void talk();

private:
    QSqlDatabase db;

signals:
	void fireTableData(QVector<QVector<QString>>);

public slots:
};

#endif // TABLEMODELTALKER_H
