#ifndef PREDESTROY_SIGNALLER_H
#define PREDESTROY_SIGNALLER_H

#include <QObject>

class PreDestroy_Signaller : public QObject
{
    Q_OBJECT
public:
    explicit PreDestroy_Signaller(QObject *parent = 0);
    static PreDestroy_Signaller* getSingleInstance();
    ~PreDestroy_Signaller();

signals:
	void preDestroyed();

public slots:
};

#endif // PREDESTROY_SIGNALLER_H
