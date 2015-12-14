#ifndef PPFHANDLER_H
#define PPFHANDLER_H
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <QString>
#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QDir>
#define CONTIGUOUS 1
#define SEPARATE 2
#define PPF_FILE 1
#define INK_FILE 2

#define CYAN 1
#define MAGENTA 2
#define YELLOW 3
#define BLACK 4
#define COLOR1 5
#define COLOR2 6
#define DIECUT 7

#define LEFT2RIGHT_BOTTOM2TOP 1
#define LEFT2RIGHT_TOP2BOTTOM 2
#define RIGHT2LEFT_BOTTOM2TOP 3
#define RIGHT2LEFT_TOP2BOTTOM 4
#define BOTTOM2TOP_LEFT2RIGHT 5
#define TOP2BOTTOM_LEFT2RIGHT 6
#define BOTTOM2TOP_RIGHT2LEFT 7
#define TOP2BOTTOM_RIGHT2LEFT 8

#define MAX_THUMBNAIL_WIDTH 590
#define MAX_THUMBNAIL_HEIGHT 430

typedef unsigned char BYTE;

class PPFHandler:public QObject
{
    Q_OBJECT
public:
    PPFHandler(const char *, int);
    ~PPFHandler();
    bool hasOneSpecialColor;
    bool hasMultiplePPFFiles;
    int getImagePlanarConfiguration();
    int getImageDataSize();
    int getTransferMatrix();
    int getResolution();
    int getColorNameForSpecificPPFFile(int);
    int getColorOrder();
    int getTransferCurve();
    int getImageData(int, int);
    int getEncodingAndCompression();
    int calculateInkCoverage(int, int);
    long searchKeyword(FILE*, long, char*, BYTE, BYTE);
    int powerOfTen(int);
    double dividedByTen(int);

    struct fileInfo{
        QString fileName;
        int color;
    }file[8];
    const char *fileName;
    BYTE contiguous_or_separate;
    int numberOfColors;
    int pageOfDieCut;

    BYTE* cyan;
    BYTE* magenta;
    BYTE* yellow;
    BYTE* black;
    BYTE *specialColor1;
    BYTE *specialColor2;

    BYTE* cyan_RGBConversion;
    BYTE* magenta_RGBConversion;
    BYTE* yellow_RGBConversion;
    BYTE* black_RGBConversion;
    BYTE* all_RGBConversion;
    BYTE* color1_RGBConversion;
    BYTE* color2_RGBConversion;

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

    int numOfMaxAllowedColorsForThisMachine;

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

    int unit;
    long fileLength;
    int fountainWidthInPixel;
    int thumbnailFountainWidth;
    int plateHeightInPixel;
    int thumbnailFountainHeight;
    int image_width;
    int image_height;
    int thumbnailWidth;
    int thumbnailHeight;
    int image_size;
    int thumbnailSize;
    int image_location;
    int thumbnailLocation;
    int shrinkRatio;
    int image_location_afterRotation;
    int thumbnailLocationAfterRotation;
    double xResolution;
    double yResolution;
    BYTE direction;
    BYTE *colorOrder;

    int fileType;

    bool isCTFIdentity;
    bool isCTPIdentity;

    BYTE *CTF_int_x;
    BYTE *CTF_int_y;
    BYTE *CTP_int_x;
    BYTE *CTP_int_y;
    BYTE *CTF_int_a;
    BYTE *CTP_int_a;

    float *CTF_x;
    float *CTF_y;
    float *CTF_a;
    float *CTP_x;
    float *CTP_y;
    float *CTP_a;
    float *CTF_k;
    float *CTP_k;

    BYTE *colorValues[4];
    int *dataComponentSize;

    int numOfCTFCurvePoints;
    int numOfCTPCurvePoints;
signals:
    void progressRange(qint64);
    void percentage(qint64);
};
#endif // PPFHANDLER_H
