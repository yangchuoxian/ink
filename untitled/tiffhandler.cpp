#include "tiffhandler.h"

TIFFHandler::TIFFHandler(QString name, int num)
{
    numberOfColors = 0;
    numOfMaxAllowedColorsForThisMachine = num;
    choseFileName = name;
}
TIFFHandler::~TIFFHandler()
{
    for (int i = 0; i < 48; i ++)
        inkValues[i] = NULL;

    delete[] cyan;
    cyan = NULL;
    delete[] cyanInkValue;
    cyanInkValue = NULL;
    delete[] cyan_RGBConversion;
    cyan_RGBConversion = NULL;
    delete[] magenta;
    magenta = NULL;
    delete[] magentaInkValue;
    magentaInkValue = NULL;
    delete[] magenta_RGBConversion;
    magenta_RGBConversion = NULL;
    delete[] yellow;
    yellow = NULL;
    delete[] yellowInkValue;
    yellowInkValue = NULL;
    delete[] yellow_RGBConversion;
    yellow_RGBConversion = NULL;
    delete[] black;
    black = NULL;
    delete[] blackInkValue;
    blackInkValue = NULL;
    delete[] black_RGBConversion;
    black_RGBConversion = NULL;
    delete[] all_RGBConversion;
    all_RGBConversion = NULL;
    if (numberOfColors >= 5){
        delete []specialColor1;
        specialColor1 = NULL;
        delete []color1_RGBConversion;
        color1_RGBConversion = NULL;

        delete[] specialColor1InkValue;
        specialColor1InkValue = NULL;
        delete[] specialColor1InkValue_90CW_noFlip;
        specialColor1InkValue_90CW_noFlip = NULL;
        delete[] specialColor1InkValue_180CW_noFlip;
        specialColor1InkValue_180CW_noFlip = NULL;
        delete[] specialColor1InkValue_270CW_noFlip;
        specialColor1InkValue_270CW_noFlip = NULL;
    }
    if (numberOfColors >= 6){
        delete []specialColor2;
        specialColor2 = NULL;
        delete[] color2_RGBConversion;
        color2_RGBConversion = NULL;

        delete[] specialColor2InkValue;
        specialColor2InkValue = NULL;
        delete[] specialColor2InkValue_90CW_noFlip;
        specialColor2InkValue_90CW_noFlip = NULL;
        delete[] specialColor2InkValue_180CW_noFlip;
        specialColor2InkValue_180CW_noFlip = NULL;
        delete[] specialColor2InkValue_270CW_noFlip;
        specialColor2InkValue_270CW_noFlip = NULL;
    }

    delete[] cyanInkValue_90CW_noFlip;
    cyanInkValue_90CW_noFlip = NULL;
    delete[] magentaInkValue_90CW_noFlip;
    magentaInkValue_90CW_noFlip = NULL;
    delete[] yellowInkValue_90CW_noFlip;
    yellowInkValue_90CW_noFlip = NULL;
    delete[] blackInkValue_90CW_noFlip;
    blackInkValue_90CW_noFlip = NULL;

    delete[] cyanInkValue_180CW_noFlip;
    cyanInkValue_180CW_noFlip = NULL;
    delete[] magentaInkValue_180CW_noFlip;
    magentaInkValue_180CW_noFlip = NULL;
    delete[] yellowInkValue_180CW_noFlip;
    yellowInkValue_180CW_noFlip = NULL;
    delete[] blackInkValue_180CW_noFlip;
    blackInkValue_180CW_noFlip = NULL;

    delete[] cyanInkValue_270CW_noFlip;
    cyanInkValue_270CW_noFlip = NULL;
    delete[] magentaInkValue_270CW_noFlip;
    magentaInkValue_270CW_noFlip = NULL;
    delete[] yellowInkValue_270CW_noFlip;
    yellowInkValue_270CW_noFlip = NULL;
    delete[] blackInkValue_270CW_noFlip;
    blackInkValue_270CW_noFlip = NULL;

    cyanComponent_horizontal->~QImage();
    cyanComponent_vertical->~QImage();
    magentaComponent_horizontal->~QImage();
    magentaComponent_vertical->~QImage();
    yellowComponent_horizontal->~QImage();
    yellowComponent_vertical->~QImage();
    blackComponent_horizontal->~QImage();
    blackComponent_vertical->~QImage();
    thumbnailImage_horizontal->~QImage();
    thumbnailImage_vertical->~QImage();
    if (numberOfColors >= 5){
        specialColor1Component_horizontal->~QImage();
        specialColor1Component_vertical->~QImage();
    }
    if (numberOfColors >= 6){
        specialColor2Component_horizontal->~QImage();
        specialColor2Component_vertical->~QImage();
    }
    colorValues[0] = NULL;
    colorValues[1] = NULL;
    colorValues[2] = NULL;
    colorValues[3] = NULL;
    numberOfColors = 0;
}
int TIFFHandler::getImageInfo()
{
    TIFF *TIFFFile = TIFFOpen(choseFileName.trimmed().toAscii(), "r");

    TIFFGetField(TIFFFile, TIFFTAG_IMAGEWIDTH, &image_width);
    TIFFGetField(TIFFFile, TIFFTAG_IMAGELENGTH, &image_length);
    TIFFGetField(TIFFFile, TIFFTAG_SAMPLESPERPIXEL, &samplesPerPixel);
    TIFFGetField(TIFFFile, TIFFTAG_RESOLUTIONUNIT, &resolutionUnit);
    TIFFGetField(TIFFFile, TIFFTAG_XRESOLUTION, &x_resolution);
    TIFFGetField(TIFFFile, TIFFTAG_YRESOLUTION, &y_resolution);

    TIFFClose(TIFFFile);
    if (samplesPerPixel == 4)
        numberOfColors = 4;
    if (samplesPerPixel == 1){
        int lengthOfDir = choseFileName.lastIndexOf("/");
        QString DirName = choseFileName.left(lengthOfDir);
        QDir tiffDir(DirName);
        QStringList nameFilters("*.tif");
        QStringList filesInFolder = tiffDir.entryList(nameFilters);
        numberOfColors = filesInFolder.length();

        if (numberOfColors > numOfMaxAllowedColorsForThisMachine)
            return -2;      //找到的色彩文件数量大于印刷机支持的最大色彩数量，报错返回
        if (numberOfColors < 4 && samplesPerPixel == 1)
            return -3;      //should be either 1 tif file or at least 4 tif files

        int specialColorFound = 0;
        for (int i = 0; i < numberOfColors; i ++){
            if (filesInFolder[i].contains("cyan", Qt::CaseInsensitive)){
                file[0].fileName = filesInFolder[i];
            }
            else if (filesInFolder[i].contains("magenta", Qt::CaseInsensitive)){
                file[1].fileName = filesInFolder[i];
            }
            else if (filesInFolder[i].contains("yellow", Qt::CaseInsensitive)){
                file[2].fileName = filesInFolder[i];
            }
            else if (filesInFolder[i].contains("black", Qt::CaseInsensitive)){
                file[3].fileName = filesInFolder[i];
            }

            else if (filesInFolder[i].contains("pantone", Qt::CaseInsensitive)){
                if (file[4].fileName != NULL){
                    file[5].fileName = file[4].fileName;
                }
                file[4].fileName = filesInFolder[i];
                specialColorFound ++;
            }
            else{
                file[4 + specialColorFound].fileName = filesInFolder[i];
                specialColorFound ++;
            }
        }
        for (int i = 0; i < numberOfColors; i ++){
            file[i].fileName.prepend("/");
            file[i].fileName.prepend(DirName);
        }
        unsigned int tempWidth, tempHeight;
        unsigned short tempSPP, tempRU;
        float tempXR, tempYR;
        for (int i = 0; i < numberOfColors; i ++){
            TIFF *tempTIFFFile = TIFFOpen(file[i].fileName.trimmed().toAscii(), "r");

            TIFFGetField(tempTIFFFile, TIFFTAG_IMAGEWIDTH, &tempWidth);
            TIFFGetField(tempTIFFFile, TIFFTAG_IMAGELENGTH, &tempHeight);
            TIFFGetField(tempTIFFFile, TIFFTAG_SAMPLESPERPIXEL, &tempSPP);
            TIFFGetField(tempTIFFFile, TIFFTAG_RESOLUTIONUNIT, &tempRU);
            TIFFGetField(tempTIFFFile, TIFFTAG_XRESOLUTION, &tempXR);
            TIFFGetField(tempTIFFFile, TIFFTAG_YRESOLUTION, &tempYR);

            TIFFClose(tempTIFFFile);

            if ((image_width != tempWidth) ||
                (this->image_length != tempHeight) ||
                (samplesPerPixel != tempSPP) ||
                (resolutionUnit != tempRU) ||
                (x_resolution != tempXR) ||
                (y_resolution != tempYR)){
                return -1;
            }
        }
    }
    else if (samplesPerPixel != 4)
        return -1;
    return 0;
}
int TIFFHandler::getImageData(float inkFountainWidth, float plateHeight)
{
    float tempResult1, tempResult2;

    if (image_width > image_length){
        tempResult1 = (float)image_width / (float)MAXIMUM_THUMBNAIL_WIDTH;
        tempResult2 = (float)image_length / (float)MAXIMUM_THUMBNAIL_HEIGHT;
    }
    else{
        tempResult1 = (float)image_length / (float)MAXIMUM_THUMBNAIL_WIDTH;
        tempResult2 = (float)image_width / (float)MAXIMUM_THUMBNAIL_HEIGHT;
    }
    if (tempResult1 >= tempResult2){
        if (tempResult1 >= 2){
            if (tempResult1 - (int)tempResult1 >= 0.5)
                shrinkRatio = (int)tempResult1 + 1;
            else
                shrinkRatio = (int)tempResult1;
        }
        else
            shrinkRatio = 1;
    }
    else{
        if (tempResult2 >= 2){
            if (tempResult2 - (int)tempResult2 >= 0.5)
                shrinkRatio = (int)tempResult2 + 1;
            else
                shrinkRatio = (int)tempResult2;
        }
        else
            shrinkRatio = 1;
    }
    thumbnailWidth = image_width / shrinkRatio;
    if (image_width % shrinkRatio != 0)
        thumbnailWidth ++;
    thumbnailHeight = image_length / shrinkRatio;
    if (image_length % shrinkRatio != 0)
        thumbnailHeight ++;

    register unsigned short i = 0;

    if (resolutionUnit == INCH){
        inkFountainWidth = x_resolution * inkFountainWidth / 2.54;
        plateHeight = y_resolution * plateHeight / 2.54;
        if (inkFountainWidth - (int)inkFountainWidth >= 0.5)
            actualWidthInPixel = (int)inkFountainWidth + 1;
        else
            actualWidthInPixel = (int)inkFountainWidth;
        if (plateHeight - (int)plateHeight >= 0.5)
            actualHeightInPixel = (int)plateHeight + 1;
        else
            actualHeightInPixel = (int)plateHeight;
    }
    else if (resolutionUnit == CENTIMETER){
        inkFountainWidth = x_resolution * inkFountainWidth;
        plateHeight = y_resolution * plateHeight;
        if (inkFountainWidth - (int)inkFountainWidth >= 0.5)
            actualWidthInPixel = (int)inkFountainWidth + 1;
        else
            actualWidthInPixel = (int)inkFountainWidth;
        if (plateHeight - (int)plateHeight >= 0.5)
            actualHeightInPixel = (int)plateHeight + 1;
        else
            actualHeightInPixel = (int)plateHeight;
    }

    if (actualWidthInPixel % shrinkRatio != 0)
        actualWidthInPixel = shrinkRatio * (actualWidthInPixel / shrinkRatio + 1);
    if (actualHeightInPixel % shrinkRatio != 0)
        actualHeightInPixel = shrinkRatio * (actualHeightInPixel / shrinkRatio + 1);

    thumbnailSize = thumbnailWidth * thumbnailHeight;
    unsigned int *cyanTotal = new unsigned int[thumbnailSize];
    unsigned int *magentaTotal = new unsigned int[thumbnailSize];
    unsigned int *yellowTotal = new unsigned int[thumbnailSize];
    unsigned int *blackTotal = new unsigned int[thumbnailSize];
    unsigned int *specialColor1Total = NULL;
    if (numberOfColors >= 5){
        specialColor1Total = new unsigned int[thumbnailSize];
        for (int count = 0; count < thumbnailSize; count ++)
            specialColor1Total[count] = 0;
    }
    unsigned int *specialColor2Total = NULL;
    if (numberOfColors >= 6){
        specialColor2Total = new unsigned int[thumbnailSize];
        for (int count = 0; count < thumbnailSize; count ++)
            specialColor2Total[count] = 0;
    }
    for (int count = 0; count < thumbnailSize; count ++){
        cyanTotal[count] = 0;
        magentaTotal[count] = 0;
        yellowTotal[count] = 0;
        blackTotal[count] = 0;
    }

    if (samplesPerPixel == 4){
        TIFF *TIFFFile = TIFFOpen(choseFileName.trimmed().toAscii(), "r");

        numberOfStrips = TIFFNumberOfStrips(TIFFFile);
        TIFFGetField(TIFFFile, TIFFTAG_ROWSPERSTRIP, &rowsPerStrip);
        emit progressRange(numberOfStrips);

        unsigned int index, k, j, x, currentIndexForThumbnail;
        unsigned int intLengthForStrip = rowsPerStrip * image_width;
        unsigned char *stripData = new unsigned char[intLengthForStrip * 4];
        for (i = 0; i < numberOfStrips; i ++){
            qApp->processEvents();

            if (i < (numberOfStrips - 1)){
                TIFFReadEncodedStrip(TIFFFile, i, stripData, -1);
                k = 0;
                index = 0;
                while (k < rowsPerStrip){
                    j = 0;
                    x = (k + i * rowsPerStrip) / shrinkRatio * thumbnailWidth;
                    while (j < image_width){
                        currentIndexForThumbnail = x + j / shrinkRatio;
                        cyanTotal[currentIndexForThumbnail] += stripData[index ++];
                        magentaTotal[currentIndexForThumbnail] += stripData[index ++];
                        yellowTotal[currentIndexForThumbnail] += stripData[index ++];
                        blackTotal[currentIndexForThumbnail] += stripData[index ++];
                        j ++;
                    }
                    k ++;
                }
            }
            else{
                TIFFReadEncodedStrip(TIFFFile, i, stripData, -1);
                unsigned int numberOfRowsLeft = image_length - rowsPerStrip * i;
                k = 0;
                index = 0;
                while(k < numberOfRowsLeft){
                    j = 0;
                    x = (k + i * rowsPerStrip) / shrinkRatio * thumbnailWidth;
                    while (j < image_width){
                        currentIndexForThumbnail = x + j / shrinkRatio;
                        cyanTotal[currentIndexForThumbnail] += stripData[index ++];
                        magentaTotal[currentIndexForThumbnail] += stripData[index ++];
                        yellowTotal[currentIndexForThumbnail] += stripData[index ++];
                        blackTotal[currentIndexForThumbnail] += stripData[index ++];
                        j ++;
                    }
                    k ++;
                }
            }
            emit percentage(i);
        }

        TIFFClose(TIFFFile);
    }
    else if (samplesPerPixel == 1){
        unsigned int *inkTotal[6] = {cyanTotal, magentaTotal, yellowTotal, blackTotal};
        inkTotal[0] = cyanTotal;
        inkTotal[1] = magentaTotal;
        inkTotal[2] = yellowTotal;
        inkTotal[3] = blackTotal;
        if (numberOfColors >= 5)
            inkTotal[4] = specialColor1Total;
        if (numberOfColors >= 6)
            inkTotal[5] = specialColor2Total;

        for (int color = 0; color < numberOfColors; color ++){
            TIFF *TIFFFile = TIFFOpen(file[color].fileName.trimmed().toAscii(), "r");

            numberOfStrips = TIFFNumberOfStrips(TIFFFile);
            TIFFGetField(TIFFFile, TIFFTAG_ROWSPERSTRIP, &rowsPerStrip);

            emit progressRange(numberOfStrips * numberOfColors);

            int tempSize = image_width >> 3;
            if (image_width % 8 != 0)
                tempSize ++;
            int lengthOfStripInBytes = rowsPerStrip * tempSize;
            char *oneBitData = new char[lengthOfStripInBytes];

            int z = 0;
            int y = 0;
            unsigned int j;
            register unsigned int k;
            int ratioCount = 0;

            int currentByte = 0;
            int currentBit = 0;
            for (i = 0; i < numberOfStrips; i ++){
                qApp->processEvents();
                TIFFReadEncodedStrip(TIFFFile, i, oneBitData, -1);

                currentByte = 0;
                currentBit = 8;
                if (i < (numberOfStrips - 1)){
                    j = 0;
                    while(j < rowsPerStrip){
                        if (image_width & 0x07){
                            currentBit = 8;
                            currentByte ++;
                        }
                        k = 0;
                        while(k < image_width){
                            currentBit --;
                            if (oneBitData[currentByte] >> currentBit & 1)
                                inkTotal[color][z + k / shrinkRatio] ++;
                            if (!currentBit){
                                currentBit = 8;
                                currentByte ++;
                            }
                            k ++;
                        }
                        ratioCount ++;
                        if (ratioCount == shrinkRatio){
                            ratioCount = 0;
                            z += thumbnailWidth;
                        }
                        j ++;
                    }
                }
                else{
                    unsigned int rowsInLastStrip = image_length - (numberOfStrips - 1) * rowsPerStrip;
                    j = 0;
                    while(j < rowsInLastStrip){
                        if (image_width & 0x07){
                            currentBit = 8;
                            currentByte ++;
                        }
                        k = 0;
                        while (k < image_width){
                            currentBit --;
                            if (oneBitData[currentByte] >> currentBit & 1)
                                inkTotal[color][z + k / shrinkRatio] ++;
                            if (!currentBit){
                                currentBit = 8;
                                currentByte ++;
                            }
                            k ++;
                        }
                        ratioCount ++;
                        if (ratioCount == shrinkRatio){
                            ratioCount = 0;
                            z += thumbnailWidth;
                        }
                        j ++;
                    }
                }
                y += rowsPerStrip;
                emit percentage(numberOfStrips * color + i);
            }

            TIFFClose(TIFFFile);

            delete []oneBitData;
            oneBitData = NULL;
        }
    }
    int q = shrinkRatio * shrinkRatio;
    cyan = new BYTE[thumbnailSize];
    magenta = new BYTE[thumbnailSize];
    yellow = new BYTE[thumbnailSize];
    black = new BYTE[thumbnailSize];
    if (numberOfColors >= 5)
        specialColor1 = new unsigned char[thumbnailSize];
    if (numberOfColors >= 6)
        specialColor2 = new unsigned char[thumbnailSize];
    unsigned int k = thumbnailSize;
    if (samplesPerPixel == 4){
        while (k--){
            cyan[k] = cyanTotal[k] / q;
            magenta[k] = magentaTotal[k] / q;
            yellow[k] = yellowTotal[k] / q;
            black[k] = blackTotal[k] / q;
        }
    }
    else if (samplesPerPixel == 1){
        while (k--){
            cyan[k] = cyanTotal[k] * 255 / q;
            magenta[k] = magentaTotal[k] * 255 / q;
            yellow[k] = yellowTotal[k] * 255 / q;
            black[k] = blackTotal[k] * 255 / q;
        }
        k = thumbnailSize;
        if (numberOfColors >= 5){
            while(k --){
                specialColor1[k] = specialColor1Total[k] * 255 / q;
            }
        }
        k = thumbnailSize;
        if (numberOfColors >= 6){
            while(k --){
                specialColor2[k] = specialColor2Total[k] * 255 / q;
            }
        }
    }

    colorValues[0] = cyan;
    colorValues[1] = magenta;
    colorValues[2] = yellow;
    colorValues[3] = black;

    delete []cyanTotal;
    cyanTotal = NULL;
    delete []magentaTotal;
    magentaTotal = NULL;
    delete []yellowTotal;
    yellowTotal = NULL;
    delete []blackTotal;
    blackTotal = NULL;
    if (numberOfColors >= 5){
        delete []specialColor1Total;
        specialColor1Total = NULL;
    }
    if (numberOfColors >= 6){
        delete []specialColor2Total;
        specialColor2Total = NULL;
    }

    cyan_RGBConversion = new BYTE[4 * thumbnailSize];
    magenta_RGBConversion = new BYTE[4 * thumbnailSize];
    yellow_RGBConversion = new BYTE[4 * thumbnailSize];
    black_RGBConversion = new BYTE[4 * thumbnailSize];
    all_RGBConversion = new BYTE[4 * thumbnailSize];
    if (numberOfColors >= 5)
        color1_RGBConversion = new BYTE[4 * thumbnailSize];
    if (numberOfColors >= 6)
        color2_RGBConversion = new BYTE[4 *thumbnailSize];

    int count = 0;
    int index = 0;
    while (count < thumbnailSize){
        cyan_RGBConversion[index + 3] = 255;
        cyan_RGBConversion[index + 2] = 255 - cyan[count];
        cyan_RGBConversion[index + 1] = 255;
        cyan_RGBConversion[index] = 255;


        magenta_RGBConversion[index + 3] = 255;
        magenta_RGBConversion[index + 2] = 255;
        magenta_RGBConversion[index + 1] = 255 - magenta[count];
        magenta_RGBConversion[index] = 255;

        yellow_RGBConversion[index + 3] = 255;
        yellow_RGBConversion[index + 2] = 255;
        yellow_RGBConversion[index + 1] = 255;
        yellow_RGBConversion[index] = 255 - yellow[count];

        black_RGBConversion[index + 3] = 255;
        black_RGBConversion[index + 2] = QColor::fromCmyk(0, 0, 0, black[count]).red();
        black_RGBConversion[index + 1] = QColor::fromCmyk(0, 0, 0, black[count]).green();
        black_RGBConversion[index] = QColor::fromCmyk(0, 0, 0, black[count]).blue();

        if (numberOfColors >= 5){
            color1_RGBConversion[index + 3] = 255;
            color1_RGBConversion[index + 2] = 255 - specialColor1[count];
            color1_RGBConversion[index + 1] = 255 - specialColor1[count];
            color1_RGBConversion[index] = 255 - specialColor1[count];
        }
        if (numberOfColors >= 6){
            color2_RGBConversion[index + 3] = 255;
            color2_RGBConversion[index + 2] = 255 - specialColor2[count];
            color2_RGBConversion[index + 1] = 255 - specialColor2[count];
            color2_RGBConversion[index] = 255 - specialColor2[count];
        }

        all_RGBConversion[index + 3] = 255;
        all_RGBConversion[index + 2] = QColor::fromCmyk(cyan[count], magenta[count],
                                                    yellow[count], black[count]).red();
        all_RGBConversion[index + 1] = QColor::fromCmyk(cyan[count], magenta[count],
                                                    yellow[count], black[count]).green();
        all_RGBConversion[index] = QColor::fromCmyk(cyan[count], magenta[count],
                                                yellow[count], black[count]).blue();
        count ++;
        index += 4;
    }
    cyanComponent_horizontal = new QImage(cyan_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    cyanComponent_vertical = new QImage(cyan_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    magentaComponent_horizontal = new QImage(magenta_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    magentaComponent_vertical = new QImage(magenta_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    yellowComponent_horizontal = new QImage(yellow_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    yellowComponent_vertical = new QImage(yellow_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    blackComponent_horizontal = new QImage(black_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    blackComponent_vertical = new QImage(black_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    thumbnailImage_horizontal = new QImage(all_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    thumbnailImage_vertical = new QImage(all_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    if (numberOfColors >= 5){
        specialColor1Component_horizontal = new QImage(color1_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
        specialColor1Component_vertical = new QImage(color1_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    }
    if (numberOfColors >= 6){
        specialColor2Component_horizontal = new QImage(color2_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
        specialColor2Component_vertical = new QImage(color2_RGBConversion, thumbnailWidth, thumbnailHeight, QImage::Format_RGB32);
    }

    if (thumbnailWidth > thumbnailHeight){
        if (thumbnailWidth > MAXIMUM_THUMBNAIL_WIDTH){
            *cyanComponent_horizontal = cyanComponent_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
            *magentaComponent_horizontal = magentaComponent_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
            *yellowComponent_horizontal = yellowComponent_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
            *blackComponent_horizontal = blackComponent_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
            *thumbnailImage_horizontal = thumbnailImage_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
            if (numberOfColors >= 5)
                *specialColor1Component_horizontal = specialColor1Component_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
            if (numberOfColors >= 6)
                *specialColor2Component_horizontal = specialColor2Component_horizontal->scaledToWidth(MAXIMUM_THUMBNAIL_WIDTH);
        }
        if (thumbnailWidth > MAXIMUM_THUMBNAIL_HEIGHT){
            *cyanComponent_vertical = cyanComponent_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
            *magentaComponent_vertical = magentaComponent_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
            *yellowComponent_vertical = yellowComponent_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
            *blackComponent_vertical = blackComponent_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
            *thumbnailImage_vertical = thumbnailImage_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
            if (numberOfColors >= 5)
                *specialColor1Component_vertical = specialColor1Component_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
            if (numberOfColors >= 6)
                *specialColor2Component_vertical = specialColor2Component_vertical->scaledToWidth(MAXIMUM_THUMBNAIL_HEIGHT);
        }
    }
    else{
        if (thumbnailHeight > MAXIMUM_THUMBNAIL_HEIGHT){
            *cyanComponent_horizontal = cyanComponent_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
            *magentaComponent_horizontal = magentaComponent_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
            *yellowComponent_horizontal = yellowComponent_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
            *blackComponent_horizontal = blackComponent_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
            *thumbnailImage_horizontal = thumbnailImage_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
            if (numberOfColors >= 5)
                *specialColor1Component_horizontal = specialColor1Component_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
            if (numberOfColors >= 6)
                *specialColor2Component_horizontal = specialColor2Component_horizontal->scaledToHeight(MAXIMUM_THUMBNAIL_HEIGHT);
        }
        if (thumbnailHeight > MAXIMUM_THUMBNAIL_WIDTH){
            *cyanComponent_vertical = cyanComponent_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
            *magentaComponent_vertical = magentaComponent_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
            *yellowComponent_vertical = yellowComponent_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
            *blackComponent_vertical = blackComponent_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
            *thumbnailImage_vertical = thumbnailImage_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
            if (numberOfColors >= 5)
                *specialColor1Component_vertical = specialColor1Component_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
            if (numberOfColors >= 6)
                *specialColor2Component_vertical = specialColor2Component_vertical->scaledToHeight(MAXIMUM_THUMBNAIL_WIDTH);
        }
    }
    return numberOfColors;
}
void TIFFHandler::calculateInkCoverage(int num_of_ink_zones, int inkKeySteps)
{
    int shrinkedWidthInPixel = actualWidthInPixel / shrinkRatio;
    int shrinkedHeightInPixel = actualHeightInPixel / shrinkRatio;

    if ((shrinkedWidthInPixel == 0) || (shrinkedHeightInPixel == 0)){
        return;
    }
    else {
        if (shrinkedWidthInPixel >= thumbnailWidth)
            thumbnailLocation = (shrinkedWidthInPixel - thumbnailWidth) / 2;
        else
            thumbnailLocation = (thumbnailWidth - shrinkedWidthInPixel) / 2;
        if (shrinkedWidthInPixel >= thumbnailHeight)
            thumbnailLocationAfterRotation = (shrinkedWidthInPixel - thumbnailHeight) / 2;
        else
            thumbnailLocationAfterRotation = (thumbnailHeight - shrinkedWidthInPixel) / 2;

        int i, j, index;

        int heightOffset = 0;

        int integerPartOfZoneWidth;
        int *sumOfCurrentColumnForCyan = NULL;
        int *sumOfCurrentColumnForMagenta = NULL;
        int *sumOfCurrentColumnForYellow = NULL;
        int *sumOfCurrentColumnForBlack = NULL;
        int *sumOfCurrentColumnForSpecialColor1 = NULL;
        int *sumOfCurrentColumnForSpecialColor2 = NULL;

        //for calculation when image direction rotated 90 degree clockwise
        int *sumOfCurrentRowForCyan = NULL;
        int *sumOfCurrentRowForMagenta = NULL;
        int *sumOfCurrentRowForYellow = NULL;
        int *sumOfCurrentRowForBlack = NULL;
        int *sumOfCurrentRowForSpecialColor1 = NULL;
        int *sumOfCurrentRowForSpecialColor2 = NULL;

        int *swap1 = NULL;
        int *swap2 = NULL;
        int *swap3 = NULL;
        int *swap4 = NULL;
        int *swap5 = NULL;
        int *swap6 = NULL;

        int *rotatedSwap1 = NULL;
        int *rotatedSwap2 = NULL;
        int *rotatedSwap3 = NULL;
        int *rotatedSwap4 = NULL;
        int *rotatedSwap5 = NULL;
        int *rotatedSwap6 = NULL;

        if (shrinkedWidthInPixel >= thumbnailWidth){
            sumOfCurrentColumnForCyan = new int[shrinkedWidthInPixel];
            sumOfCurrentColumnForMagenta = new int[shrinkedWidthInPixel];
            sumOfCurrentColumnForYellow = new int[shrinkedWidthInPixel];
            sumOfCurrentColumnForBlack = new int[shrinkedWidthInPixel];
            if (numberOfColors >= 5)
                sumOfCurrentColumnForSpecialColor1 = new int[shrinkedWidthInPixel];
            if (numberOfColors >= 6)
                sumOfCurrentColumnForSpecialColor2 = new int[shrinkedWidthInPixel];
        }
        else{
            sumOfCurrentColumnForCyan = new int[thumbnailWidth];
            sumOfCurrentColumnForMagenta = new int[thumbnailWidth];
            sumOfCurrentColumnForYellow = new int[thumbnailWidth];
            sumOfCurrentColumnForBlack = new int[thumbnailWidth];
            if (numberOfColors >= 5)
                sumOfCurrentColumnForSpecialColor1 = new int[thumbnailWidth];
            if (numberOfColors >= 6)
                sumOfCurrentColumnForSpecialColor2 = new int[thumbnailWidth];
        }

        swap1 = new int[thumbnailWidth];
        swap2 = new int[thumbnailWidth];
        swap3 = new int[thumbnailWidth];
        swap4 = new int[thumbnailWidth];
        if (numberOfColors >= 5)
            swap5 = new int[thumbnailWidth];
        if (numberOfColors >= 6)
            swap6 = new int[thumbnailWidth];

        if (shrinkedWidthInPixel >= thumbnailHeight){
            sumOfCurrentRowForCyan = new int[shrinkedWidthInPixel];
            sumOfCurrentRowForMagenta = new int[shrinkedWidthInPixel];
            sumOfCurrentRowForYellow = new int[shrinkedWidthInPixel];
            sumOfCurrentRowForBlack = new int[shrinkedWidthInPixel];
            if (numberOfColors >= 5)
                sumOfCurrentRowForSpecialColor1 = new int[shrinkedWidthInPixel];
            if (numberOfColors >= 6)
                sumOfCurrentRowForSpecialColor2 = new int[shrinkedWidthInPixel];
        }
        else{
            sumOfCurrentRowForCyan = new int[thumbnailHeight];
            sumOfCurrentRowForMagenta = new int[thumbnailHeight];
            sumOfCurrentRowForYellow = new int[thumbnailHeight];
            sumOfCurrentRowForBlack = new int[thumbnailHeight];
            if (numberOfColors >= 5)
                sumOfCurrentRowForSpecialColor1 = new int[thumbnailHeight];
            if (numberOfColors >= 6)
                sumOfCurrentRowForSpecialColor2 = new int[thumbnailHeight];
        }


        rotatedSwap1 = new int[thumbnailHeight];
        rotatedSwap2 = new int[thumbnailHeight];
        rotatedSwap3 = new int[thumbnailHeight];
        rotatedSwap4 = new int[thumbnailHeight];
        if (numberOfColors >= 5)
            rotatedSwap5 = new int[thumbnailHeight];
        if (numberOfColors >= 6)
            rotatedSwap6 = new int[thumbnailHeight];

        /***********************************************************************************/
        j = 0;
        index = 0;

        if (shrinkedWidthInPixel >= thumbnailWidth && shrinkedHeightInPixel >= thumbnailHeight){
            i = shrinkedWidthInPixel;
            while(i--){
                sumOfCurrentColumnForCyan[i] = 0;
                sumOfCurrentColumnForMagenta[i] = 0;
                sumOfCurrentColumnForYellow[i] = 0;
                sumOfCurrentColumnForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentColumnForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentColumnForSpecialColor2[i] = 0;
            }
            while (j < thumbnailHeight){
                i = 0;
                while(i < shrinkedWidthInPixel){
                    if (i >= thumbnailLocation && i < (thumbnailLocation + thumbnailWidth)){
                        sumOfCurrentColumnForCyan[i] += cyan[index];
                        sumOfCurrentColumnForMagenta[i] += magenta[index];
                        sumOfCurrentColumnForYellow[i] += yellow[index];
                        sumOfCurrentColumnForBlack[i] += black[index];
                        if (numberOfColors >= 5)
                            sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                        if (numberOfColors >= 6)
                            sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                        index ++;
                    }
                    i ++;
                }
                j ++;
            }
        }
        else if (shrinkedWidthInPixel < thumbnailWidth && shrinkedHeightInPixel >= thumbnailHeight){
            i = thumbnailWidth;
            while(i--){
                sumOfCurrentColumnForCyan[i] = 0;
                sumOfCurrentColumnForMagenta[i] = 0;
                sumOfCurrentColumnForYellow[i] = 0;
                sumOfCurrentColumnForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentColumnForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentColumnForSpecialColor2[i] = 0;
            }
            while (j < thumbnailHeight){
                i = 0;
                while(i < thumbnailWidth){
                    sumOfCurrentColumnForCyan[i] += cyan[index];
                    sumOfCurrentColumnForMagenta[i] += magenta[index];
                    sumOfCurrentColumnForYellow[i] += yellow[index];
                    sumOfCurrentColumnForBlack[i] += black[index];
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                    index ++;

                    i ++;
                }
                j ++;
            }
        }
        else if (shrinkedWidthInPixel >= thumbnailWidth && shrinkedHeightInPixel < thumbnailHeight){
            heightOffset = (thumbnailHeight - shrinkedHeightInPixel) / 2;
            i = shrinkedWidthInPixel;
            while(i--){
                sumOfCurrentColumnForCyan[i] = 0;
                sumOfCurrentColumnForMagenta[i] = 0;
                sumOfCurrentColumnForYellow[i] = 0;
                sumOfCurrentColumnForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentColumnForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentColumnForSpecialColor2[i] = 0;
            }
            index = heightOffset * thumbnailWidth;
            while (j < shrinkedHeightInPixel){
                i = 0;
                while(i < shrinkedWidthInPixel){
                    if (i >= thumbnailLocation && i < (thumbnailLocation + thumbnailWidth)){
                        sumOfCurrentColumnForCyan[i] += cyan[index];
                        sumOfCurrentColumnForMagenta[i] += magenta[index];
                        sumOfCurrentColumnForYellow[i] += yellow[index];
                        sumOfCurrentColumnForBlack[i] += black[index];
                        if (numberOfColors >= 5)
                            sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                        if (numberOfColors >= 6)
                            sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                        index ++;
                    }
                    i ++;
                }
                j ++;
            }
        }
        else if (shrinkedWidthInPixel < thumbnailWidth && shrinkedHeightInPixel < thumbnailHeight){
            heightOffset = (thumbnailHeight - shrinkedHeightInPixel) / 2;
            i = thumbnailWidth;
            while(i--){
                sumOfCurrentColumnForCyan[i] = 0;
                sumOfCurrentColumnForMagenta[i] = 0;
                sumOfCurrentColumnForYellow[i] = 0;
                sumOfCurrentColumnForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentColumnForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentColumnForSpecialColor2[i]  = 0;
            }
            index = heightOffset * thumbnailWidth;
            while (j < shrinkedHeightInPixel){
                i = 0;
                while(i < thumbnailWidth){
                    sumOfCurrentColumnForCyan[i] += cyan[index];
                    sumOfCurrentColumnForMagenta[i] += magenta[index];
                    sumOfCurrentColumnForYellow[i] += yellow[index];
                    sumOfCurrentColumnForBlack[i] += black[index];
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                    index ++;

                    i ++;
                }
                j ++;
            }
        }

        index = 0;
        if (shrinkedWidthInPixel >= thumbnailHeight && shrinkedHeightInPixel >= thumbnailWidth){
            i = shrinkedWidthInPixel;
            while(i --){
                sumOfCurrentRowForCyan[i] = 0;
                sumOfCurrentRowForMagenta[i] = 0;
                sumOfCurrentRowForYellow[i] = 0;
                sumOfCurrentRowForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentRowForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentRowForSpecialColor2[i] = 0;
                if (i >= thumbnailLocationAfterRotation && i < (thumbnailHeight + thumbnailLocationAfterRotation)){
                    for (j = 0; j < thumbnailWidth; j ++){
                        sumOfCurrentRowForCyan[i] += cyan[index];
                        sumOfCurrentRowForMagenta[i] += magenta[index];
                        sumOfCurrentRowForYellow[i] += yellow[index];
                        sumOfCurrentRowForBlack[i] += black[index];
                        if (numberOfColors >= 5)
                            sumOfCurrentRowForSpecialColor1[i] += specialColor1[index];
                        if (numberOfColors >= 6)
                            sumOfCurrentRowForSpecialColor2[i] += specialColor2[index];
                        index ++;
                    }
                }
            }
        }
        else if (shrinkedWidthInPixel < thumbnailHeight && shrinkedHeightInPixel >= thumbnailWidth){
            i = thumbnailHeight;
            while(i --){
                sumOfCurrentRowForCyan[i] = 0;
                sumOfCurrentRowForMagenta[i] = 0;
                sumOfCurrentRowForYellow[i] = 0;
                sumOfCurrentRowForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentRowForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentRowForSpecialColor2[i] = 0;
                for (j = 0; j < thumbnailWidth; j ++){
                    sumOfCurrentRowForCyan[i] += cyan[index];
                    sumOfCurrentRowForMagenta[i] += magenta[index];
                    sumOfCurrentRowForYellow[i] += yellow[index];
                    sumOfCurrentRowForBlack[i] += black[index];
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] += specialColor1[index];
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] += specialColor2[index];
                    index ++;
                }
            }
        }
        else if (shrinkedWidthInPixel >= thumbnailHeight && shrinkedHeightInPixel < thumbnailWidth){
            heightOffset = (thumbnailWidth - shrinkedHeightInPixel) / 2;
            index = 0;
            i = shrinkedWidthInPixel;
            while(i --){
                sumOfCurrentRowForCyan[i] = 0;
                sumOfCurrentRowForMagenta[i] = 0;
                sumOfCurrentRowForYellow[i] = 0;
                sumOfCurrentRowForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentRowForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentRowForSpecialColor2[i] = 0;
                if (i >= thumbnailLocationAfterRotation && i < (thumbnailHeight + thumbnailLocationAfterRotation)){
                    for (j = 0; j < thumbnailWidth; j ++){
                        if (j >= heightOffset && j < (heightOffset + thumbnailWidth)){
                            sumOfCurrentRowForCyan[i] += cyan[index];
                            sumOfCurrentRowForMagenta[i] += magenta[index];
                            sumOfCurrentRowForYellow[i] += yellow[index];
                            sumOfCurrentRowForBlack[i] += black[index];
                            if (numberOfColors >= 5)
                                sumOfCurrentRowForSpecialColor1[i] += specialColor1[index];
                            if (numberOfColors >= 6)
                                sumOfCurrentRowForSpecialColor2[i] += specialColor2[index];
                        }
                        index ++;
                    }
                }
            }
        }
        else if (shrinkedWidthInPixel < thumbnailHeight && shrinkedHeightInPixel < thumbnailWidth){
            for (i = 0; i < thumbnailHeight; i ++){
                sumOfCurrentRowForCyan[i] = 0;
                sumOfCurrentRowForMagenta[i] = 0;
                sumOfCurrentRowForYellow[i] = 0;
                sumOfCurrentRowForBlack[i] = 0;
                if (numberOfColors >= 5)
                    sumOfCurrentRowForSpecialColor1[i] = 0;
                if (numberOfColors >= 6)
                    sumOfCurrentRowForSpecialColor2[i] = 0;
            }
            heightOffset = (thumbnailWidth - shrinkedHeightInPixel) / 2;
            index = 0;
            i = thumbnailHeight;
            while(i --){
                for (j = 0; j < thumbnailWidth; j ++){
                    if (j >= heightOffset && j < (heightOffset + thumbnailWidth)){
                        sumOfCurrentRowForCyan[i] += cyan[index];
                        sumOfCurrentRowForMagenta[i] += magenta[index];
                        sumOfCurrentRowForYellow[i] += yellow[index];
                        sumOfCurrentRowForBlack[i] += black[index];
                        if (numberOfColors >= 5)
                            sumOfCurrentRowForSpecialColor1[i] += specialColor1[index];
                        if (numberOfColors >= 6)
                            sumOfCurrentRowForSpecialColor2[i] += specialColor2[index];
                    }
                    index ++;
                }
            }
        }

        /***********************************************************************************/

        double *percentageValueForCyan = new double[num_of_ink_zones];
        double *percentageValueForMagenta = new double[num_of_ink_zones];
        double *percentageValueForYellow = new double[num_of_ink_zones];
        double *percentageValueForBlack = new double[num_of_ink_zones];
        double *percentageValueForSpecialColor1 = NULL;
        double *percentageValueForSpecialColor2 = NULL;
        if (numberOfColors >= 5)
            percentageValueForSpecialColor1 = new double[num_of_ink_zones];
        if (numberOfColors >= 6)
            percentageValueForSpecialColor2 = new double[num_of_ink_zones];

        double fractionPartOfZoneWidth, firstFraction, lastFraction;
        double accurateZoneWidth = (double)shrinkedWidthInPixel / (double)num_of_ink_zones;
        integerPartOfZoneWidth = (int)accurateZoneWidth;
        fractionPartOfZoneWidth = accurateZoneWidth - (int)accurateZoneWidth;
        /***********calculate ink coverage values for original direction************/
        firstFraction = 0;
        lastFraction = fractionPartOfZoneWidth;
        i = 0;
        index = 0;
        if (shrinkedWidthInPixel >= thumbnailWidth)
            index = 0;
        else
            index = (thumbnailWidth - shrinkedWidthInPixel) / 2;
        while (i < num_of_ink_zones){
            percentageValueForCyan[i] = 0;
            percentageValueForMagenta[i] = 0;
            percentageValueForYellow[i] = 0;
            percentageValueForBlack[i] = 0;
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] = 0;
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] = 0;

            percentageValueForCyan[i] += firstFraction * sumOfCurrentColumnForCyan[index];
            percentageValueForMagenta[i] += firstFraction * sumOfCurrentColumnForMagenta[index];
            percentageValueForYellow[i] += firstFraction * sumOfCurrentColumnForYellow[index];
            percentageValueForBlack[i] += firstFraction * sumOfCurrentColumnForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += firstFraction * sumOfCurrentColumnForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += firstFraction * sumOfCurrentColumnForSpecialColor2[index];

            if (firstFraction != 0)
                index ++;
            if (firstFraction <= fractionPartOfZoneWidth){
                for (j = 0; j < integerPartOfZoneWidth; j ++){
                    percentageValueForCyan[i] += sumOfCurrentColumnForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentColumnForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentColumnForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentColumnForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentColumnForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentColumnForSpecialColor2[index];
                    index ++;
                }
            }
            else{
                for (j = 0; j < (integerPartOfZoneWidth - 1); j ++){
                    percentageValueForCyan[i] += sumOfCurrentColumnForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentColumnForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentColumnForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentColumnForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentColumnForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentColumnForSpecialColor2[index];
                    index ++;
                }
            }

            percentageValueForCyan[i] += lastFraction * sumOfCurrentColumnForCyan[index];
            percentageValueForMagenta[i] += lastFraction * sumOfCurrentColumnForMagenta[index];
            percentageValueForYellow[i] += lastFraction * sumOfCurrentColumnForYellow[index];
            percentageValueForBlack[i] += lastFraction * sumOfCurrentColumnForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += lastFraction * sumOfCurrentColumnForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += lastFraction * sumOfCurrentColumnForSpecialColor2[index];

            firstFraction = 1.0 - lastFraction;
            if (firstFraction > fractionPartOfZoneWidth)
                lastFraction = 1 + fractionPartOfZoneWidth - firstFraction;
            else
                lastFraction = fractionPartOfZoneWidth - firstFraction;

            percentageValueForCyan[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);

            i ++;
        }
        cyanInkValue = new int[num_of_ink_zones];
        magentaInkValue = new int[num_of_ink_zones];
        yellowInkValue = new int[num_of_ink_zones];
        blackInkValue = new int[num_of_ink_zones];
        if (numberOfColors >= 5)
            specialColor1InkValue = new int[num_of_ink_zones];
        if (numberOfColors >= 6)
            specialColor2InkValue = new int[num_of_ink_zones];
        for (i = 0; i < num_of_ink_zones; i ++){
            cyanInkValue[i] = 0.5 + percentageValueForCyan[i] * (float)inkKeySteps / 100;
            magentaInkValue[i] = 0.5 + percentageValueForMagenta[i] * (float)inkKeySteps / 100;
            yellowInkValue[i] = 0.5 + percentageValueForYellow[i] * (float)inkKeySteps / 100;
            blackInkValue[i] = 0.5 + percentageValueForBlack[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 5)
                specialColor1InkValue[i] = 0.5 + percentageValueForSpecialColor1[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 6)
                specialColor2InkValue[i] = 0.5 + percentageValueForSpecialColor2[i] * (float)inkKeySteps / 100;
        }
        /*******************************************************************************************/

        /*******calculate ink coverage values for 90 clockwise rotation and no horizontal flip******/
        firstFraction = 0;
        lastFraction = fractionPartOfZoneWidth;
        i = 0;
        if (shrinkedWidthInPixel >= thumbnailHeight)
            index = 0;
        else
            index = (thumbnailHeight - shrinkedWidthInPixel) / 2;
        while (i < num_of_ink_zones){
            percentageValueForCyan[i] = 0;
            percentageValueForMagenta[i] = 0;
            percentageValueForYellow[i] = 0;
            percentageValueForBlack[i] = 0;
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] = 0;
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] = 0;

            percentageValueForCyan[i] += firstFraction * sumOfCurrentRowForCyan[index];
            percentageValueForMagenta[i] += firstFraction * sumOfCurrentRowForMagenta[index];
            percentageValueForYellow[i] += firstFraction * sumOfCurrentRowForYellow[index];
            percentageValueForBlack[i] += firstFraction * sumOfCurrentRowForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += firstFraction * sumOfCurrentRowForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += firstFraction * sumOfCurrentRowForSpecialColor2[index];

            if (firstFraction != 0)
                index ++;
            if (firstFraction <= fractionPartOfZoneWidth){
                for (j = 0; j < integerPartOfZoneWidth; j ++){
                    percentageValueForCyan[i] += sumOfCurrentRowForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentRowForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentRowForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentRowForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentRowForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentRowForSpecialColor2[index];
                    index ++;
                }
            }
            else{
                for (j = 0; j < (integerPartOfZoneWidth - 1); j ++){
                    percentageValueForCyan[i] += sumOfCurrentRowForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentRowForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentRowForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentRowForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentRowForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentRowForSpecialColor2[index];
                    index ++;
                }
            }

            percentageValueForCyan[i] += lastFraction * sumOfCurrentRowForCyan[index];
            percentageValueForMagenta[i] += lastFraction * sumOfCurrentRowForMagenta[index];
            percentageValueForYellow[i] += lastFraction * sumOfCurrentRowForYellow[index];
            percentageValueForBlack[i] += lastFraction * sumOfCurrentRowForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += lastFraction * sumOfCurrentRowForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += lastFraction * sumOfCurrentRowForSpecialColor2[index];
            firstFraction = 1.0 - lastFraction;
            if (firstFraction > fractionPartOfZoneWidth)
                lastFraction = 1 + fractionPartOfZoneWidth - firstFraction;
            else
                lastFraction = fractionPartOfZoneWidth - firstFraction;

            percentageValueForCyan[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i]  /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i]  /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);

            i ++;
        }

        cyanInkValue_90CW_noFlip = new int[num_of_ink_zones];
        magentaInkValue_90CW_noFlip = new int[num_of_ink_zones];
        yellowInkValue_90CW_noFlip = new int[num_of_ink_zones];
        blackInkValue_90CW_noFlip = new int[num_of_ink_zones];
        if (numberOfColors >= 5)
            specialColor1InkValue_90CW_noFlip = new int[num_of_ink_zones];
        if (numberOfColors >= 6)
            specialColor2InkValue_90CW_noFlip = new int[num_of_ink_zones];
        for (i = 0; i < num_of_ink_zones; i ++){
            cyanInkValue_90CW_noFlip[i] = 0.5 + percentageValueForCyan[i] * (float)inkKeySteps / 100;
            magentaInkValue_90CW_noFlip[i] = 0.5 + percentageValueForMagenta[i] * (float)inkKeySteps / 100;
            yellowInkValue_90CW_noFlip[i] = 0.5 + percentageValueForYellow[i] * (float)inkKeySteps / 100;
            blackInkValue_90CW_noFlip[i] = 0.5 + percentageValueForBlack[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 5)
                specialColor1InkValue_90CW_noFlip[i] = 0.5 + percentageValueForSpecialColor1[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 6)
                specialColor2InkValue_90CW_noFlip[i] = 0.5 + percentageValueForSpecialColor2[i] * (float)inkKeySteps / 100;
        }
        /*******************************************************************************************/

        /******calculate ink coverage values for 180 clockwise rotation and no horizontal flip******/
        if (shrinkedWidthInPixel >= thumbnailWidth){
            for (i = 0; i < thumbnailWidth; i ++){
                swap1[i] = sumOfCurrentColumnForCyan[thumbnailLocation + i];
                swap2[i] = sumOfCurrentColumnForMagenta[thumbnailLocation + i];
                swap3[i] = sumOfCurrentColumnForYellow[thumbnailLocation + i];
                swap4[i] = sumOfCurrentColumnForBlack[thumbnailLocation + i];
                if (numberOfColors >= 5)
                    swap5[i] = sumOfCurrentColumnForSpecialColor1[thumbnailLocation + i];
                if (numberOfColors >= 6)
                    swap6[i] = sumOfCurrentColumnForSpecialColor2[thumbnailLocation + i];
            }
            int *swapForSwap1 = new int[thumbnailWidth];
            int *swapForSwap2 = new int[thumbnailWidth];
            int *swapForSwap3 = new int[thumbnailWidth];
            int *swapForSwap4 = new int[thumbnailWidth];
            int *swapForSwap5 = NULL;
            int *swapForSwap6 = NULL;
            if (numberOfColors >= 5)
                swapForSwap5 = new int[thumbnailWidth];
            if (numberOfColors >= 6)
                swapForSwap6 = new int[thumbnailWidth];
            for (i = 0; i < thumbnailWidth; i ++){
                swapForSwap1[i] = swap1[thumbnailWidth - i - 1];
                swapForSwap2[i] = swap2[thumbnailWidth - i - 1];
                swapForSwap3[i] = swap3[thumbnailWidth - i - 1];
                swapForSwap4[i] = swap4[thumbnailWidth - i - 1];
                if (numberOfColors >= 5)
                    swapForSwap5[i] = swap5[thumbnailWidth - i - 1];
                if (numberOfColors >= 6)
                    swapForSwap6[i] = swap6[thumbnailWidth - i - 1];
            }
            for (i = 0; i < thumbnailWidth; i ++){
                sumOfCurrentColumnForCyan[thumbnailLocation + i] = swapForSwap1[i];
                sumOfCurrentColumnForMagenta[thumbnailLocation + i] = swapForSwap2[i];
                sumOfCurrentColumnForYellow[thumbnailLocation + i] = swapForSwap3[i];
                sumOfCurrentColumnForBlack[thumbnailLocation + i] = swapForSwap4[i];
                if (numberOfColors >= 5)
                    sumOfCurrentColumnForSpecialColor1[thumbnailLocation + i] = swapForSwap5[i];
                if (numberOfColors >= 6)
                    sumOfCurrentColumnForSpecialColor2[thumbnailLocation + i] = swapForSwap6[i];
            }
            delete []swapForSwap1;
            swapForSwap1 = NULL;
            delete []swapForSwap2;
            swapForSwap2 = NULL;
            delete []swapForSwap3;
            swapForSwap3 = NULL;
            delete []swapForSwap4;
            swapForSwap4 = NULL;
            if (numberOfColors >= 5){
                delete []swapForSwap5;
                swapForSwap5 = NULL;
            }
            if (numberOfColors >= 6){
                delete []swapForSwap6;
                swapForSwap6 = NULL;
            }
        }
        else{
            for (i = 0; i < thumbnailWidth; i ++){
                swap1[i] = sumOfCurrentColumnForCyan[thumbnailWidth - i - 1];
                swap2[i] = sumOfCurrentColumnForMagenta[thumbnailWidth - i - 1];
                swap3[i] = sumOfCurrentColumnForYellow[thumbnailWidth - i - 1];
                swap4[i] = sumOfCurrentColumnForBlack[thumbnailWidth - i - 1];
                if (numberOfColors >= 5)
                    swap5[i] = sumOfCurrentColumnForSpecialColor1[thumbnailWidth - i - 1];
                if (numberOfColors >= 6)
                    swap6[i] = sumOfCurrentColumnForSpecialColor2[thumbnailWidth - i - 1];
            }
            for (i = 0; i < thumbnailWidth; i ++){
                sumOfCurrentColumnForCyan[i] = swap1[i];
                sumOfCurrentColumnForMagenta[i] = swap2[i];
                sumOfCurrentColumnForYellow[i] = swap3[i];
                sumOfCurrentColumnForBlack[i] = swap4[i];
                if (numberOfColors >= 5)
                    sumOfCurrentColumnForSpecialColor1[i] = swap5[i];
                if (numberOfColors >= 6)
                    sumOfCurrentColumnForSpecialColor2[i] = swap6[i];
            }
        }
        delete []swap1;
        swap1 = NULL;
        delete []swap2;
        swap2 = NULL;
        delete []swap3;
        swap3 = NULL;
        delete []swap4;
        swap4 = NULL;
        if (numberOfColors >= 5){
            delete [] swap5;
            swap5 = NULL;
        }
        if (numberOfColors >= 6){
            delete []swap6;
            swap6 = NULL;
        }
        firstFraction = 0;
        lastFraction = fractionPartOfZoneWidth;
        i = 0;
        if (shrinkedWidthInPixel >= thumbnailWidth)
            index = 0;
        else
            index = (thumbnailWidth - shrinkedWidthInPixel) / 2;
        while (i < num_of_ink_zones){
            percentageValueForCyan[i] = 0;
            percentageValueForMagenta[i] = 0;
            percentageValueForYellow[i] = 0;
            percentageValueForBlack[i] = 0;
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] = 0;
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] = 0;

            percentageValueForCyan[i] += firstFraction * sumOfCurrentColumnForCyan[index];
            percentageValueForMagenta[i] += firstFraction * sumOfCurrentColumnForMagenta[index];
            percentageValueForYellow[i] += firstFraction * sumOfCurrentColumnForYellow[index];
            percentageValueForBlack[i] += firstFraction * sumOfCurrentColumnForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += firstFraction * sumOfCurrentColumnForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += firstFraction * sumOfCurrentColumnForSpecialColor2[index];

            if (firstFraction != 0)
                index ++;
            if (firstFraction <= fractionPartOfZoneWidth){
                for (j = 0; j < integerPartOfZoneWidth; j ++){
                    percentageValueForCyan[i] += sumOfCurrentColumnForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentColumnForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentColumnForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentColumnForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentColumnForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentColumnForSpecialColor2[index];
                    index ++;
                }
            }
            else{
                for (j = 0; j < (integerPartOfZoneWidth - 1); j ++){
                    percentageValueForCyan[i] += sumOfCurrentColumnForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentColumnForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentColumnForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentColumnForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentColumnForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentColumnForSpecialColor2[index];
                    index ++;
                }
            }

            percentageValueForCyan[i] += lastFraction * sumOfCurrentColumnForCyan[index];
            percentageValueForMagenta[i] += lastFraction * sumOfCurrentColumnForMagenta[index];
            percentageValueForYellow[i] += lastFraction * sumOfCurrentColumnForYellow[index];
            percentageValueForBlack[i] += lastFraction * sumOfCurrentColumnForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += lastFraction * sumOfCurrentColumnForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += lastFraction * sumOfCurrentColumnForSpecialColor2[index];
            firstFraction = 1.0 - lastFraction;
            if (firstFraction > fractionPartOfZoneWidth)
                lastFraction = 1 + fractionPartOfZoneWidth - firstFraction;
            else
                lastFraction = fractionPartOfZoneWidth - firstFraction;

            percentageValueForCyan[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);

            i ++;
        }

        cyanInkValue_180CW_noFlip = new int[num_of_ink_zones];
        magentaInkValue_180CW_noFlip = new int[num_of_ink_zones];
        yellowInkValue_180CW_noFlip = new int[num_of_ink_zones];
        blackInkValue_180CW_noFlip = new int[num_of_ink_zones];
        if (numberOfColors >= 5)
            specialColor1InkValue_180CW_noFlip = new int[num_of_ink_zones];
        if (numberOfColors >= 6)
            specialColor2InkValue_180CW_noFlip = new int[num_of_ink_zones];

        for (i = 0; i < num_of_ink_zones; i ++){
            cyanInkValue_180CW_noFlip[i] = 0.5 + percentageValueForCyan[i] * (float)inkKeySteps / 100;
            magentaInkValue_180CW_noFlip[i] = 0.5 + percentageValueForMagenta[i] * (float)inkKeySteps / 100;
            yellowInkValue_180CW_noFlip[i] = 0.5 + percentageValueForYellow[i] * (float)inkKeySteps / 100;
            blackInkValue_180CW_noFlip[i] = 0.5 + percentageValueForBlack[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 5)
                specialColor1InkValue_180CW_noFlip[i] = 0.5 + percentageValueForSpecialColor1[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 6)
                specialColor2InkValue_180CW_noFlip[i] = 0.5 + percentageValueForSpecialColor2[i] * (float)inkKeySteps / 100;
        }
        /*******************************************************************************************/

        /*******calculate ink coverage values for 270 clockwise rotation and no horizontal flip*****/
        if (shrinkedWidthInPixel >= thumbnailHeight){
            for (i = 0; i < thumbnailHeight; i ++){
                rotatedSwap1[i] = sumOfCurrentRowForCyan[thumbnailLocationAfterRotation + i];
                rotatedSwap2[i] = sumOfCurrentRowForMagenta[thumbnailLocationAfterRotation + i];
                rotatedSwap3[i] = sumOfCurrentRowForYellow[thumbnailLocationAfterRotation + i];
                rotatedSwap4[i] = sumOfCurrentRowForBlack[thumbnailLocationAfterRotation + i];
                if (numberOfColors >= 5)
                    rotatedSwap5[i] = sumOfCurrentRowForSpecialColor1[thumbnailLocationAfterRotation + i];
                if (numberOfColors >= 6)
                    rotatedSwap6[i] = sumOfCurrentRowForSpecialColor2[thumbnailLocationAfterRotation + i];
            }
            int *swapForRotatedSwap1 = new int[thumbnailHeight];
            int *swapForRotatedSwap2 = new int[thumbnailHeight];
            int *swapForRotatedSwap3 = new int[thumbnailHeight];
            int *swapForRotatedSwap4 = new int[thumbnailHeight];
            int *swapForRotatedSwap5 = NULL;
            int *swapForRotatedSwap6 = NULL;
            if (numberOfColors >= 5)
                swapForRotatedSwap5 = new int[thumbnailHeight];
            if (numberOfColors >= 6)
                swapForRotatedSwap6 = new int[thumbnailHeight];
            for (i = 0; i < thumbnailHeight; i ++){
                swapForRotatedSwap1[i] = rotatedSwap1[thumbnailHeight - i - 1];
                swapForRotatedSwap2[i] = rotatedSwap2[thumbnailHeight - i - 1];
                swapForRotatedSwap3[i] = rotatedSwap3[thumbnailHeight - i - 1];
                swapForRotatedSwap4[i] = rotatedSwap4[thumbnailHeight - i - 1];
                if (numberOfColors >= 5)
                    swapForRotatedSwap5[i] = rotatedSwap5[thumbnailHeight - 1 - i];
                if (numberOfColors >= 6)
                    swapForRotatedSwap6[i] = rotatedSwap6[thumbnailHeight - 1 - i];
            }
            for (i = 0; i < thumbnailHeight; i ++){
                sumOfCurrentRowForCyan[thumbnailLocationAfterRotation + i] = swapForRotatedSwap1[i];
                sumOfCurrentRowForMagenta[thumbnailLocationAfterRotation + i] = swapForRotatedSwap2[i];
                sumOfCurrentRowForYellow[thumbnailLocationAfterRotation + i] = swapForRotatedSwap3[i];
                sumOfCurrentRowForBlack[thumbnailLocationAfterRotation + i] = swapForRotatedSwap4[i];
                if (numberOfColors >= 5)
                    sumOfCurrentRowForSpecialColor1[i + thumbnailLocationAfterRotation] = swapForRotatedSwap5[i];
                if (numberOfColors >= 6)
                    sumOfCurrentRowForSpecialColor2[i + thumbnailLocationAfterRotation] = swapForRotatedSwap6[i];
            }
            delete []swapForRotatedSwap1;
            swapForRotatedSwap1 = NULL;
            delete []swapForRotatedSwap2;
            swapForRotatedSwap2 = NULL;
            delete []swapForRotatedSwap3;
            swapForRotatedSwap3 = NULL;
            delete []swapForRotatedSwap4;
            swapForRotatedSwap4 = NULL;
            if (numberOfColors >= 5){
                delete []swapForRotatedSwap5;
                swapForRotatedSwap5 = NULL;
            }
            if (numberOfColors >= 6){
                delete []swapForRotatedSwap6;
                swapForRotatedSwap6 = NULL;
            }
        }
        else{
            for (i = 0; i < thumbnailHeight; i ++){
                rotatedSwap1[i] = sumOfCurrentRowForCyan[thumbnailHeight - i - 1];
                rotatedSwap2[i] = sumOfCurrentRowForMagenta[thumbnailHeight - i - 1];
                rotatedSwap3[i] = sumOfCurrentRowForYellow[thumbnailHeight - i - 1];
                rotatedSwap4[i] = sumOfCurrentRowForBlack[thumbnailHeight - i - 1];
                if (numberOfColors >= 5)
                    rotatedSwap5[i] = sumOfCurrentRowForSpecialColor1[thumbnailHeight - 1 - i];
                if (numberOfColors >= 6)
                    rotatedSwap6[i] = sumOfCurrentRowForSpecialColor2[thumbnailHeight - 1 - i];
            }
            for (i = 0; i < thumbnailHeight; i ++){
                sumOfCurrentRowForCyan[i] = rotatedSwap1[i];
                sumOfCurrentRowForMagenta[i] = rotatedSwap2[i];
                sumOfCurrentRowForYellow[i] = rotatedSwap3[i];
                sumOfCurrentRowForBlack[i] = rotatedSwap4[i];
                if (numberOfColors >= 5)
                    sumOfCurrentRowForSpecialColor1[i] = rotatedSwap5[i];
                if (numberOfColors >= 6)
                    sumOfCurrentRowForSpecialColor2[i] = rotatedSwap6[i];
            }
        }
        delete []rotatedSwap1;
        rotatedSwap1 = NULL;
        delete []rotatedSwap2;
        rotatedSwap2 = NULL;
        delete []rotatedSwap3;
        rotatedSwap3 = NULL;
        delete []rotatedSwap4;
        rotatedSwap4 = NULL;
        if (numberOfColors >= 5){
            delete []rotatedSwap5;
            rotatedSwap5 = NULL;
        }
        if (numberOfColors >= 6){
            delete []rotatedSwap6;
            rotatedSwap6 = NULL;
        }
        firstFraction = 0;
        lastFraction = fractionPartOfZoneWidth;
        i = 0;
        if (shrinkedWidthInPixel >= thumbnailHeight)
            index = 0;
        else
            index = (thumbnailHeight - shrinkedWidthInPixel) / 2;
        while (i < num_of_ink_zones){
            percentageValueForCyan[i] = 0;
            percentageValueForMagenta[i] = 0;
            percentageValueForYellow[i] = 0;
            percentageValueForBlack[i] = 0;
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] = 0;
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] = 0;

            percentageValueForCyan[i] += firstFraction * sumOfCurrentRowForCyan[index];
            percentageValueForMagenta[i] += firstFraction * sumOfCurrentRowForMagenta[index];
            percentageValueForYellow[i] += firstFraction * sumOfCurrentRowForYellow[index];
            percentageValueForBlack[i] += firstFraction * sumOfCurrentRowForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += firstFraction * sumOfCurrentRowForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += firstFraction * sumOfCurrentRowForSpecialColor2[index];

            if (firstFraction != 0)
                index ++;
            if (firstFraction <= fractionPartOfZoneWidth){
                for (j = 0; j < integerPartOfZoneWidth; j ++){
                    percentageValueForCyan[i] += sumOfCurrentRowForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentRowForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentRowForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentRowForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentRowForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentRowForSpecialColor2[index];
                    index ++;
                }
            }
            else{
                for (j = 0; j < (integerPartOfZoneWidth - 1); j ++){
                    percentageValueForCyan[i] += sumOfCurrentRowForCyan[index];
                    percentageValueForMagenta[i] += sumOfCurrentRowForMagenta[index];
                    percentageValueForYellow[i] += sumOfCurrentRowForYellow[index];
                    percentageValueForBlack[i] += sumOfCurrentRowForBlack[index];
                    if (numberOfColors >= 5)
                        percentageValueForSpecialColor1[i] += sumOfCurrentRowForSpecialColor1[index];
                    if (numberOfColors >= 6)
                        percentageValueForSpecialColor2[i] += sumOfCurrentRowForSpecialColor2[index];

                    index ++;
                }
            }

            percentageValueForCyan[i] += lastFraction * sumOfCurrentRowForCyan[index];
            percentageValueForMagenta[i] += lastFraction * sumOfCurrentRowForMagenta[index];
            percentageValueForYellow[i] += lastFraction * sumOfCurrentRowForYellow[index];
            percentageValueForBlack[i] += lastFraction * sumOfCurrentRowForBlack[index];
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] += lastFraction * sumOfCurrentRowForSpecialColor1[index];
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] += lastFraction * sumOfCurrentRowForSpecialColor2[index];

            firstFraction = 1.0 - lastFraction;
            if (firstFraction > fractionPartOfZoneWidth)
                lastFraction = 1 + fractionPartOfZoneWidth - firstFraction;
            else
                lastFraction = fractionPartOfZoneWidth - firstFraction;

            percentageValueForCyan[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] /= (accurateZoneWidth * shrinkedHeightInPixel * 2.55);

            i ++;
        }

        cyanInkValue_270CW_noFlip = new int[num_of_ink_zones];
        magentaInkValue_270CW_noFlip = new int[num_of_ink_zones];
        yellowInkValue_270CW_noFlip = new int[num_of_ink_zones];
        blackInkValue_270CW_noFlip = new int[num_of_ink_zones];
        if (numberOfColors >= 5)
            specialColor1InkValue_270CW_noFlip = new int[num_of_ink_zones];
        if (numberOfColors >= 6)
            specialColor2InkValue_270CW_noFlip = new int[num_of_ink_zones];

        for (i = 0; i < num_of_ink_zones; i ++){
            cyanInkValue_270CW_noFlip[i] = 0.5 + percentageValueForCyan[i] * (float)inkKeySteps / 100;
            magentaInkValue_270CW_noFlip[i] = 0.5 + percentageValueForMagenta[i] * (float)inkKeySteps / 100;
            yellowInkValue_270CW_noFlip[i] = 0.5 + percentageValueForYellow[i] * (float)inkKeySteps / 100;
            blackInkValue_270CW_noFlip[i] = 0.5 + percentageValueForBlack[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 5)
                specialColor1InkValue_270CW_noFlip[i] = 0.5 + percentageValueForSpecialColor1[i] * (float)inkKeySteps / 100;
            if (numberOfColors >= 6)
                specialColor2InkValue_270CW_noFlip[i] = 0.5 + percentageValueForSpecialColor2[i] * (float)inkKeySteps / 100;

        }
        /*******************************************************************************************/

        inkValues[0] = cyanInkValue;
        inkValues[1] = magentaInkValue;
        inkValues[2] = yellowInkValue;
        inkValues[3] = blackInkValue;
        if (numberOfColors >= 5)
            inkValues[4] = specialColor1InkValue;
        else
            inkValues[5] = NULL;
        if (numberOfColors >= 6)
            inkValues[5] = specialColor2InkValue;
        else
            inkValues[5] = NULL;

        inkValues[6] = cyanInkValue_90CW_noFlip;
        inkValues[7] = magentaInkValue_90CW_noFlip;
        inkValues[8] = yellowInkValue_90CW_noFlip;
        inkValues[9] = blackInkValue_90CW_noFlip;
        inkValues[10] = specialColor1InkValue_90CW_noFlip;
        inkValues[11] = specialColor2InkValue_90CW_noFlip;

        inkValues[12] = cyanInkValue_180CW_noFlip;
        inkValues[13] = magentaInkValue_180CW_noFlip;
        inkValues[14] = yellowInkValue_180CW_noFlip;
        inkValues[15] = blackInkValue_180CW_noFlip;
        inkValues[16] = specialColor1InkValue_180CW_noFlip;
        inkValues[17] = specialColor2InkValue_180CW_noFlip;

        inkValues[18] = cyanInkValue_270CW_noFlip;
        inkValues[19] = magentaInkValue_270CW_noFlip;
        inkValues[20] = yellowInkValue_270CW_noFlip;
        inkValues[21] = blackInkValue_270CW_noFlip;
        inkValues[22] = specialColor1InkValue_270CW_noFlip;
        inkValues[23] = specialColor2InkValue_270CW_noFlip;

        inkValues[24] = cyanInkValue_180CW_noFlip;
        inkValues[25] = magentaInkValue_180CW_noFlip;
        inkValues[26] = yellowInkValue_180CW_noFlip;
        inkValues[27] = blackInkValue_180CW_noFlip;
        inkValues[28] = specialColor1InkValue_180CW_noFlip;
        inkValues[29] = specialColor2InkValue_180CW_noFlip;

        inkValues[30] = cyanInkValue_90CW_noFlip;
        inkValues[31] = magentaInkValue_90CW_noFlip;
        inkValues[32] = yellowInkValue_90CW_noFlip;
        inkValues[33] = blackInkValue_90CW_noFlip;
        inkValues[34] = specialColor1InkValue_90CW_noFlip;
        inkValues[35] = specialColor2InkValue_90CW_noFlip;

        inkValues[36] = cyanInkValue;
        inkValues[37] = magentaInkValue;
        inkValues[38] = yellowInkValue;
        inkValues[39] = blackInkValue;
        inkValues[40] = specialColor1InkValue;
        inkValues[41] = specialColor2InkValue;

        inkValues[42] = cyanInkValue_270CW_noFlip;
        inkValues[43] = magentaInkValue_270CW_noFlip;
        inkValues[44] = yellowInkValue_270CW_noFlip;
        inkValues[45] = blackInkValue_270CW_noFlip;
        inkValues[46] = specialColor1InkValue_270CW_noFlip;
        inkValues[47] = specialColor2InkValue_270CW_noFlip;

        if (samplesPerPixel == 4)
            emit percentage(numberOfStrips);

        else if (samplesPerPixel == 1)
            emit percentage(numberOfStrips * numberOfColors);

        delete []sumOfCurrentColumnForCyan;
        sumOfCurrentColumnForCyan = NULL;
        delete []sumOfCurrentColumnForMagenta;
        sumOfCurrentColumnForMagenta = NULL;
        delete []sumOfCurrentColumnForYellow;
        sumOfCurrentColumnForYellow = NULL;
        delete []sumOfCurrentColumnForBlack;
        sumOfCurrentColumnForBlack = NULL;
        if (numberOfColors >= 5){
            delete []sumOfCurrentColumnForSpecialColor1;
            sumOfCurrentColumnForSpecialColor1 = NULL;
        }
        if (numberOfColors >= 6){
            delete []sumOfCurrentColumnForSpecialColor2;
            sumOfCurrentColumnForSpecialColor2 = NULL;
        }

        delete []sumOfCurrentRowForCyan;
        sumOfCurrentRowForCyan = NULL;
        delete []sumOfCurrentRowForMagenta;
        sumOfCurrentRowForMagenta = NULL;
        delete []sumOfCurrentRowForYellow;
        sumOfCurrentRowForYellow = NULL;
        delete []sumOfCurrentRowForBlack;
        sumOfCurrentRowForBlack = NULL;
        if (numberOfColors >= 5){
            delete []sumOfCurrentRowForSpecialColor1;
            sumOfCurrentRowForSpecialColor1 = NULL;
        }
        if (numberOfColors >= 6){
            delete []sumOfCurrentRowForSpecialColor2;
            sumOfCurrentRowForSpecialColor2 = NULL;
        }

        delete []percentageValueForCyan;
        percentageValueForCyan = NULL;
        delete []percentageValueForMagenta;
        percentageValueForMagenta = NULL;
        delete []percentageValueForYellow;
        percentageValueForYellow = NULL;
        delete []percentageValueForBlack;
        percentageValueForBlack = NULL;
        if (numberOfColors >= 5){
            delete []percentageValueForSpecialColor1;
            percentageValueForSpecialColor1 = NULL;
        }
        if (numberOfColors >= 6){
            delete []percentageValueForSpecialColor2;
            percentageValueForSpecialColor2 = NULL;
        }
    }
}
