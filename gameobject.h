#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>

class gameObject : public QObject
{
    Q_OBJECT
public:
    explicit gameObject(QObject *parent = 0);

private:
    updateTime();

};

#endif // GAMEOBJECT_H
