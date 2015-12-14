#ifndef FILESAVER_H
#define FILESAVER_H
#include "ppfhandler.h"
#include "tiffhandler.h"
#include <QDateTime>
#include <QFile>
#include <QApplication>

#define PPF_FORMAT 1
#define TIFF_FORMAT 2
//#define UDISK_LOCATION "/home/yangchuoxian/images/"
#define UDISK_LOCATION "/udisk/"
#define REMOTE_LOCATION "/mnt/i/"

class fileSaver
{
public:
    fileSaver(int, QString, QString, int, int, int);
    ~fileSaver();
    void saveGeneralFile();
    void saveAsPPF(int, void *, QString);

    int **inkValues;
private:
    int numOfPages;
    int machineModel;
    int inkKeyQuantity;
    int inkFraction;
    QString upper_fileName;
    QString lower_fileName;
};

#endif // FILESAVER_H
