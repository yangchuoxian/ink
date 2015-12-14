#ifndef BATTERYDRIVER_H
#define BATTERYDRIVER_H
#include <QThread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

class BatteryDriver : public QThread
{
    Q_OBJECT
public:
    BatteryDriver();
    void run();
signals:
    void batteryPercentage(int);
    void chargingStatus(bool);
};

#endif // BATTERYDRIVER_H
