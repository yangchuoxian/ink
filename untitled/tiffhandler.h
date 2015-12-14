#ifndef TIFFHANDLER_H
#define TIFFHANDLER_H

#include <QDebug>
#include <QObject>
#include <QColor>
#include <QDir>
#include <QImage>
#include <QByteArray>
#include <tiffio.h>
#include "sys/time.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <QApplication>
#define TIFF_LITTLE_ENDIAN 1
#define TIFF_BIG_ENDIAN 2
#define INCH 2
#define CENTIMETER 3
#define CYAN 1
#define MAGENTA 2
#define YELLOW 3
#define BLACK 4
#define COLOR1 5
#define COLOR2 6
#define DIECUT 7
#define NOCOMPRESSION 1
#define MAXIMUM_THUMBNAIL_WIDTH 590
#define MAXIMUM_THUMBNAIL_HEIGHT 430

typedef unsigned char BYTE;

class TIFFHandler:public QObject
{
    Q_OBJECT
public:
    TIFFHandler(QString, int);
    ~TIFFHandler();
    int getImageInfo();
    int getImageData(float, float);
    void calculateInkCoverage(int, int);

    struct fileInfo{
        QString fileName;
        int color;
    }file[8];
    QString choseFileName;
    int numberOfColors;
    int numOfMaxAllowedColorsForThisMachine;

    unsigned int rowsPerStrip;
    int byte_order;
    int offset_of_the_1st_IFD;
    int numberOfStrips;
    unsigned int image_width;
    unsigned int image_length;
    unsigned short samplesPerPixel;
    int thumbnailSize;
    int thumbnailWidth;
    int thumbnailHeight;
    int thumbnailLocation;
    int thumbnailLocationAfterRotation;
    int shrinkRatio;
    float x_resolution;
    float y_resolution;
    unsigned short resolutionUnit;
    int actualWidthInPixel;
    int actualHeightInPixel;
    int actualSizeInPixel;

    BYTE* cyan;
    BYTE* magenta;
    BYTE* yellow;
    BYTE* black;
    BYTE* specialColor1;
    BYTE* specialColor2;
    BYTE* cyan_RGBConversion;
    BYTE* magenta_RGBConversion;
    BYTE* yellow_RGBConversion;
    BYTE* black_RGBConversion;
    BYTE* all_RGBConversion;
    BYTE* color1_RGBConversion;
    BYTE* color2_RGBConversion;

    BYTE *colorValues[4];

    QImage *cyanComponent_horizontal;
    QImage *magentaComponent_horizontal;
    QImage *yellowComponent_horizontal;
    QImage *blackComponent_horizontal;
    QImage *thumbnailImage_horizontal;
    QImage *specialColor1Component_horizontal;
    QImage *specialColor2Component_horizontal;

    QImage *cyanComponent_vertical;
    QImage *magentaComponent_vertical;
    QImage *yellowComponent_vertical;
    QImage *blackComponent_vertical;
    QImage *thumbnailImage_vertical;
    QImage *specialColor1Component_vertical;
    QImage *specialColor2Component_vertical;

    int* cyanInkValue;
    int* magentaInkValue;
    int* yellowInkValue;
    int* blackInkValue;
    int* specialColor1InkValue;
    int* specialColor2InkValue;

    int* cyanInkValue_90CW_noFlip;
    int* magentaInkValue_90CW_noFlip;
    int* yellowInkValue_90CW_noFlip;
    int* blackInkValue_90CW_noFlip;
    int* specialColor1InkValue_90CW_noFlip;
    int* specialColor2InkValue_90CW_noFlip;

    int* cyanInkValue_180CW_noFlip;
    int* magentaInkValue_180CW_noFlip;
    int* yellowInkValue_180CW_noFlip;
    int* blackInkValue_180CW_noFlip;
    int* specialColor1InkValue_180CW_noFlip;
    int* specialColor2InkValue_180CW_noFlip;

    int* cyanInkValue_270CW_noFlip;
    int* magentaInkValue_270CW_noFlip;
    int* yellowInkValue_270CW_noFlip;
    int* blackInkValue_270CW_noFlip;
    int* specialColor1InkValue_270CW_noFlip;
    int* specialColor2InkValue_270CW_noFlip;

    int *inkValues[48];
signals:
    void progressRange(qint64);
    void percentage(qint64);
};

#endif // TIFFHANDLER_H
