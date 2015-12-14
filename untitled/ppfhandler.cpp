#include "ppfhandler.h"

PPFHandler::PPFHandler(const char *fName, int num)
{
    fileName = fName;
    hasOneSpecialColor = false;
    hasMultiplePPFFiles = false;
    numOfMaxAllowedColorsForThisMachine = num;
    fileLength = 0;
    direction = -1;
    colorOrder = new BYTE[4];
    isCTFIdentity = false;
    isCTPIdentity = false;
}
PPFHandler::~PPFHandler()
{
    if (fileType == PPF_FILE){
        delete[] cyan;
        cyan = NULL;
        delete[] magenta;
        magenta = NULL;
        delete[] yellow;
        yellow = NULL;
        delete[] black;
        black = NULL;
        if (numberOfColors >= 5){
            delete []specialColor1;
            specialColor1 = NULL;
        }
        if (numberOfColors >= 6){
            delete []specialColor2;
            specialColor2 = NULL;
        }
        delete []CTF_int_x;
        CTF_int_x = NULL;
        delete []CTF_int_y;
        CTF_int_y = NULL;
        delete []CTF_k;
        CTF_k = NULL;
        delete []CTF_int_a;
        CTF_int_a = NULL;
        delete []CTP_int_x;
        CTP_int_x = NULL;
        delete []CTP_int_y;
        CTP_int_y = NULL;
        delete []CTP_k;
        CTP_k = NULL;
        delete []CTP_int_a;
        CTP_int_a = NULL;

        delete []CTF_x;
        CTF_x = NULL;
        delete []CTF_y;
        CTF_y = NULL;
        delete []CTF_a;
        CTF_a = NULL;
        delete []CTP_x;
        CTP_x = NULL;
        delete []CTP_y;
        CTP_y = NULL;
        delete [] CTP_a;
        CTP_a = NULL;
    }
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
    delete []cyan_RGBConversion;
    cyan_RGBConversion = NULL;
    delete []magenta_RGBConversion;
    magenta_RGBConversion = NULL;
    delete []yellow_RGBConversion;
    yellow_RGBConversion = NULL;
    delete []black_RGBConversion;
    black_RGBConversion = NULL;
    delete this->all_RGBConversion;
    all_RGBConversion = NULL;
    if (numberOfColors >= 5){
        delete []color1_RGBConversion;
        color1_RGBConversion = NULL;
    }
    if (numberOfColors >= 6){
        delete []color2_RGBConversion;
        color2_RGBConversion = NULL;
    }
    for (int i = 0; i < 48; i ++)
        inkValues[i] = NULL;

    delete[] cyanInkValue;
    cyanInkValue = NULL;
    delete[] magentaInkValue;
    magentaInkValue = NULL;
    delete[] yellowInkValue;
    yellowInkValue = NULL;
    delete[] blackInkValue;
    blackInkValue = NULL;
    if (numberOfColors >= 5){
        delete[] specialColor1InkValue;
        specialColor1InkValue = NULL;
    }
    if (numberOfColors >= 6){
        delete[] specialColor2InkValue;
        specialColor2InkValue = NULL;
    }

    delete[] cyanInkValue_90CW_noFlip;
    cyanInkValue_90CW_noFlip = NULL;
    delete[] magentaInkValue_90CW_noFlip;
    magentaInkValue_90CW_noFlip = NULL;
    delete[] yellowInkValue_90CW_noFlip;
    yellowInkValue_90CW_noFlip = NULL;
    delete[] blackInkValue_90CW_noFlip;
    blackInkValue_90CW_noFlip = NULL;
    if (numberOfColors >= 5){
        delete[] specialColor1InkValue_90CW_noFlip;
        specialColor1InkValue_90CW_noFlip = NULL;
    }
    if (numberOfColors >= 6){
        delete[] specialColor2InkValue_90CW_noFlip;
        specialColor2InkValue_90CW_noFlip = NULL;
    }

    delete[] cyanInkValue_180CW_noFlip;
    cyanInkValue_180CW_noFlip = NULL;
    delete[] magentaInkValue_180CW_noFlip;
    magentaInkValue_180CW_noFlip = NULL;
    delete[] yellowInkValue_180CW_noFlip;
    yellowInkValue_180CW_noFlip = NULL;
    delete[] blackInkValue_180CW_noFlip;
    blackInkValue_180CW_noFlip = NULL;
    if (numberOfColors >= 5){
        delete[] specialColor1InkValue_180CW_noFlip;
        specialColor1InkValue_180CW_noFlip = NULL;
    }
    if (numberOfColors >= 6){
        delete[] specialColor2InkValue_180CW_noFlip;
        specialColor2InkValue_180CW_noFlip = NULL;
    }

    delete[] cyanInkValue_270CW_noFlip;
    cyanInkValue_270CW_noFlip = NULL;
    delete[] magentaInkValue_270CW_noFlip;
    magentaInkValue_270CW_noFlip = NULL;
    delete[] yellowInkValue_270CW_noFlip;
    yellowInkValue_270CW_noFlip = NULL;
    delete[] blackInkValue_270CW_noFlip;
    blackInkValue_270CW_noFlip = NULL;
    if (numberOfColors >= 5){
        delete[] specialColor1InkValue_270CW_noFlip;
        specialColor1InkValue_270CW_noFlip = NULL;
    }
    if (numberOfColors >= 6){
        delete[] specialColor2InkValue_270CW_noFlip;
        specialColor2InkValue_270CW_noFlip = NULL;
    }

    delete []colorOrder;
    colorOrder = NULL;

    colorValues[0] = NULL;
    colorValues[1] = NULL;
    colorValues[2] = NULL;
    colorValues[3] = NULL;
}
int PPFHandler::getColorNameForSpecificPPFFile(int fileIndex)
{
    long location;
    char temp, tempChar1, tempChar2, tempChar3, tempChar4;
    int returnValue = 0;
    int numOfColorsInSelectedPPFFile = 0;
    char key[23] = {'/', 'C', 'I', 'P', '3', 'A', 'd', 'm', 'S', 'e', 'p', 'a', 'r', 'a', 't', 'i', 'o', 'n', 'N', 'a', 'm', 'e', 's'};
    FILE *PPFFile = fopen(file[fileIndex].fileName.toAscii().data(), "rb");

    location = searchKeyword(PPFFile, 0, key, 23, 1);
    if (location == -1){
        fclose(PPFFile);
        return -1;
    }

    fseek(PPFFile, location, SEEK_SET);
    temp = fgetc(PPFFile);
    while(temp != ']'){
        if (temp == '('){
            numOfColorsInSelectedPPFFile ++;
            tempChar1 = fgetc(PPFFile);
            tempChar2 = fgetc(PPFFile);
            tempChar3 = fgetc(PPFFile);
            tempChar4 = fgetc(PPFFile);
            if (tempChar1 == 'D' && tempChar2 == 'i' && tempChar3 == 'e' && tempChar4 == 'C')
                returnValue = DIECUT;
            else if (tempChar1 == 'C' && tempChar2 == 'y' && tempChar3 == 'a' && tempChar4 == 'n')
                returnValue =CYAN;
            else if (tempChar1 == 'M' && tempChar2 == 'a' && tempChar3 == 'g' && tempChar4 == 'e')
                returnValue = MAGENTA;
            else if (tempChar1 == 'Y' && tempChar2 == 'e' && tempChar3 == 'l' && tempChar4 == 'l')
                returnValue = YELLOW;
            else if (tempChar1 == 'B' && tempChar2 == 'l' && tempChar3 == 'a' && tempChar4 == 'c')
                returnValue = BLACK;
            else if (!hasOneSpecialColor){
                hasOneSpecialColor = true;
                returnValue = COLOR1;
            }
            else
                returnValue = COLOR2;
        }
        temp = fgetc(PPFFile);
    }
    fclose(PPFFile);
    if (numOfColorsInSelectedPPFFile > 1)
        return -1;
    return returnValue;

}
int PPFHandler::getColorOrder()
{
    char temp;
    int index = 0;
    long location;
    char key[23] = {'/', 'C', 'I', 'P', '3', 'A', 'd', 'm', 'S', 'e', 'p', 'a', 'r', 'a', 't', 'i', 'o', 'n', 'N', 'a', 'm', 'e', 's'};

    FILE *PPFFile = fopen(fileName, "rb");

    location = searchKeyword(PPFFile, 0, key, 23, 1);
    if (location == -1){
        fclose(PPFFile);
        return -1;
    }

    pageOfDieCut = -1;
    numberOfColors = 0;
    fseek(PPFFile, location, SEEK_SET);
    temp = fgetc(PPFFile);
    while(temp != ']'){
        if (temp == '('){
            numberOfColors ++;
            if (fgetc(PPFFile) == 'D' && fgetc(PPFFile) == 'i' && fgetc(PPFFile) == 'e' &&
                fgetc(PPFFile) == 'C' && fgetc(PPFFile) == 'u' && fgetc(PPFFile) == 't')
                pageOfDieCut = numberOfColors - 1;
        }
        temp = fgetc(PPFFile);
    }

    fseek(PPFFile, location, SEEK_SET);
    if (numberOfColors >= 4){
        while (index < 4){
            temp = fgetc(PPFFile);
            while(temp != 66 && (temp != 67) && (temp != 77) && (temp != 89))
                temp = fgetc(PPFFile);
            if (temp == 66)
                colorOrder[index] = 4;
            else if (temp == 67)
                colorOrder[index] = 1;
            else if (temp == 77)
                colorOrder[index] = 2;
            else if (temp == 89)
                colorOrder[index] = 3;
            index ++;
        }
        fclose(PPFFile);
        if (pageOfDieCut != -1){
            if ((numberOfColors - 1) > numOfMaxAllowedColorsForThisMachine){
                return -2;
            }
        }
        else{
            if (numberOfColors > numOfMaxAllowedColorsForThisMachine){
                return -2;
            }
        }
    }
    else if (numberOfColors == 1){
        int colorType = 0;
        QString firstFileName = fileName;
        int lengthOfDir = firstFileName.lastIndexOf("/");
        QString DirName = firstFileName.left(lengthOfDir);
        QDir tiffDir(DirName);
        QStringList nameFilters("*.ppf");
        QStringList filesInFolder = tiffDir.entryList(nameFilters);
        numberOfColors = filesInFolder.length();

        hasMultiplePPFFiles = true;
        for (int i = 0; i < numberOfColors; i ++){
            file[i].fileName = DirName + "/" + filesInFolder.at(i);
            colorType = getColorNameForSpecificPPFFile(i);
            if (colorType != -1){
                file[i].color = colorType;
                if (colorType == DIECUT){
                    if ((numberOfColors - 1) > numOfMaxAllowedColorsForThisMachine){
                        return -2;      //找到的色彩文件数量大于印刷机支持的最大色彩数量，报错返回
                    }
                    if ((numberOfColors - 1) < 4){
                        return -3;
                    }
                }
                else{
                    if (numberOfColors > numOfMaxAllowedColorsForThisMachine){
                        return -2;      //找到的色彩文件数量大于印刷机支持的最大色彩数量，报错返回
                    }
                    if (numberOfColors < 4){
                        return -3;
                    }
                }
            }
            else
                return -2;
        }
    }
    dataComponentSize = new int[numberOfColors];

    return numberOfColors;
}
int PPFHandler::getImagePlanarConfiguration()
{
    char temp;
    long location;
    char key[27] = {'/', 'C', 'I', 'P', '3', 'P', 'r', 'e', 'v', 'i', 'e', 'w', 'I', 'm', 'a', 'g', 'e', 'C', 'o', 'm', 'p', 'o', 'n', 'e', 'n', 't', 's'};

    FILE *PPFFile = fopen(fileName, "rb");
    location = searchKeyword(PPFFile, 0, key, 27, 1);

    if (location == -1){
        fclose(PPFFile);
        return -1;
    }


    fseek(PPFFile, location, SEEK_SET);
    temp = fgetc(PPFFile);
    while(temp == ' ')
        temp = fgetc(PPFFile);
    fclose(PPFFile);
    if (temp == '1')
        contiguous_or_separate = SEPARATE;
    else if (temp == '4')
        contiguous_or_separate = CONTIGUOUS;
    else{
        return - 1;
    }
    return 0;
}
long PPFHandler::searchKeyword(FILE *PPFFile, long startLocation, char* keywordTemplate, BYTE length, BYTE count)
{
    char temp;
    long i, j;
    long locTemp = 0;
    long location;
    BYTE numOfMatches = 0;
    location = -1;							//if -1 returns, meaning no keyword found

    if (fileLength == 0){
        fseek(PPFFile, SEEK_SET, SEEK_END);
        fileLength = ftell(PPFFile);
    }
    fseek(PPFFile, startLocation, 0);
    for (i = 0; i < (fileLength - startLocation - length) + 1; i ++){
        for (j = 0; j < length; j ++){
            temp = fgetc(PPFFile);
            locTemp ++;
            if (temp != keywordTemplate[j])
                break;
        }
        if (j == length){
            if (count == 1){
                location = startLocation + locTemp;
                break;
            }
            else {
                location = startLocation + locTemp;
                numOfMatches ++;
                if (numOfMatches == count){
                    break;
                }
            }
        }
    }

    return location;
}
int PPFHandler::getImageDataSize()
{
    char widthKeyword[22] = {'/','C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','W','i','d','t','h'};
    image_width = 0;
    char heightKeyword[23] = {'/','C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','H','e','i','g','h','t'};
    image_height = 0;
    long location;
    char temp;

    FILE *PPFFile = fopen(fileName, "rb");
    location = searchKeyword(PPFFile, 0, widthKeyword, 22, 1);
    if (location == -1){
        fclose(PPFFile);
        return -1;
    }

    fseek(PPFFile, location, SEEK_SET);
    temp = fgetc(PPFFile);
    while(temp == ' ')
        temp = fgetc(PPFFile);
    while (temp != ' '){
        image_width *= 10;
        image_width += temp - 48;
        temp = fgetc(PPFFile);
    }

    location = searchKeyword(PPFFile, 0, heightKeyword, 23, 1);
    if (location == -1){
        fclose(PPFFile);
        return -1;
    }

    fseek(PPFFile, location, SEEK_SET);
    temp = fgetc(PPFFile);
    while(temp == ' ')
        temp = fgetc(PPFFile);
    while(temp != ' '){
        image_height *= 10;
        image_height += temp - 48;
        temp = fgetc(PPFFile);
    }
    image_size = image_width * image_height;
    fclose(PPFFile);

    return 0;
}
int PPFHandler::getTransferMatrix()
{
    char matrixKeyword[23] = {'/','C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','M','a','t','r','i','x'};
    long location;
    char temp;
    int matrix[6] = {0, 0, 0, 0, 0, 0};
    int j;

    direction = 0;

    FILE *PPFFile = fopen(fileName, "rb");
    location = searchKeyword(PPFFile, 0, matrixKeyword, 23, 1);
    if (location == -1){
        fclose(PPFFile);
        return -1;
    }

    fseek(PPFFile, location, SEEK_SET);

    temp = fgetc(PPFFile);
    while(temp != '[')		//read until the start of the matrix
        temp = fgetc(PPFFile);
    while((temp == ' ') || (temp == '['))		//get rid of possible space character
        temp = fgetc(PPFFile);
    for (j = 0; j < 6; j ++){
        while ((temp != ' ') && (temp != ']')){
            if (temp == '-'){
                temp = fgetc(PPFFile);
            }
            matrix[j] *= 10;
            matrix[j] +=temp - 48;
            temp = fgetc(PPFFile);
        }
        while (temp == ' ')
            temp = fgetc(PPFFile);
        if (temp == ']')
            break;
    }
    if ((matrix[0] == image_width) && (matrix[3] == image_height)){
        if ((matrix[4] == 0) && (matrix[5] == 0)){
            direction = LEFT2RIGHT_BOTTOM2TOP;
        }
        else if ((matrix[4] == 0) && (matrix[5] == image_height)){
            direction = LEFT2RIGHT_TOP2BOTTOM;
        }
        else if ((matrix[4] == image_width) && (matrix[5] == 0)){
            direction = RIGHT2LEFT_BOTTOM2TOP;
        }
        else if ((matrix[4] == image_width) && (matrix[5] == image_height)){
            direction = RIGHT2LEFT_TOP2BOTTOM;
        }
    }
    else {
        if ((matrix[4] == 0) && (matrix[5] == 0)){
            direction = BOTTOM2TOP_LEFT2RIGHT;
        }
        else if ((matrix[4] == image_height) && (matrix[5] == 0)){
            direction = TOP2BOTTOM_LEFT2RIGHT;
        }
        else if ((matrix[4] == 0) && (matrix[5] == image_width)){
            direction = BOTTOM2TOP_RIGHT2LEFT;
        }
        else if ((matrix[4] == image_height) && (matrix[5] == image_width)){
            direction = TOP2BOTTOM_RIGHT2LEFT;
        }
    }
    if (direction == 0){
        fclose(PPFFile);
        return -1;
    }
    fclose(PPFFile);

    return 0;
}
int PPFHandler::getResolution()
{
    char resolutionKeyword[27] = {'/','C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','R','e','s','o','l','u','t','i','o','n'};
    BYTE numOfFractionPart = 0;
    char temp;
    long location;
    BYTE isFraction = 0;
    xResolution = 0;
    yResolution = 0;

    FILE *PPFFile = fopen(fileName, "rb");
    location =searchKeyword(PPFFile, 0, resolutionKeyword, 27, 1);
    if (location == -1){
        fclose(PPFFile);
        return -1;
    }

    fseek(PPFFile, location ,SEEK_SET);
    temp = fgetc(PPFFile);
    while ((temp == ' ') || (temp == '['))
        temp = fgetc(PPFFile);
    while (temp != ' '){
        if (temp == '.'){
            isFraction = 1;
            temp = fgetc(PPFFile);
        }
        if (!isFraction){
            xResolution *= 10;
            xResolution += temp - 48;
        }
        else{
            numOfFractionPart ++;
            xResolution += (temp - 48) * dividedByTen(numOfFractionPart);
        }
        temp = fgetc(PPFFile);
    }

    isFraction = 0;
    numOfFractionPart = 0;
    while (temp == ' ')
        temp = fgetc(PPFFile);
    while ((temp != ' ') && (temp != ']')){
        if (temp == '.'){
            isFraction = 1;
            temp = fgetc(PPFFile);
        }
        if (!isFraction){
            yResolution *= 10;
            yResolution += temp - 48;
        }
        else{
            numOfFractionPart ++;
            yResolution += (temp - 48) * dividedByTen(numOfFractionPart);
        }
        temp = fgetc(PPFFile);
    }
    fclose(PPFFile);
    return 0;
}
int PPFHandler::getTransferCurve()
{
    float tempResult;
    char temp;
    char key1[26] = {'/','C','I','P','3','T','r','a','n','s','f','e','r','F','i','l','m','C','u','r','v','e','D','a','t','a'};
    int validDigits;

    FILE *PPFFile = fopen(fileName, "rb");
    long location1 = searchKeyword(PPFFile, 0, key1, 26, 1);
    numOfCTFCurvePoints = 0;

    if (location1 == -1){
        fclose(PPFFile);
        return -1;
    }

    fseek(PPFFile, location1, SEEK_SET);

    temp = fgetc(PPFFile);
    while (temp != ']'){
        if (temp == '.')
            numOfCTFCurvePoints ++;
        temp = fgetc(PPFFile);
    }
    numOfCTFCurvePoints /= 2;
    if (numOfCTFCurvePoints != 0){
        CTF_x = new float[numOfCTFCurvePoints];
        CTF_y = new float[numOfCTFCurvePoints];
        CTF_k = new float[numOfCTFCurvePoints - 1];
        CTF_a = new float[numOfCTFCurvePoints - 1];

        CTF_int_x = new BYTE[numOfCTFCurvePoints];
        CTF_int_y = new BYTE[numOfCTFCurvePoints];
        CTF_int_a = new BYTE[numOfCTFCurvePoints];
    }
    else{
        CTF_x = new float[2];
        CTF_y = new float[2];
        CTF_k = new float[2 - 1];
        CTF_a = new float[2 - 1];

        CTF_int_x = new BYTE[2];
        CTF_int_y = new BYTE[2];
        CTF_int_a = new BYTE[2];
    }
    if (numOfCTFCurvePoints == 2 || numOfCTFCurvePoints == 0){
        isCTFIdentity = true;
        CTF_x[0] = 0;
        CTF_y[0] = 0;
        CTF_x[1] = 1;
        CTF_y[1] = 1;
    }
    else{
        fseek(PPFFile, location1, SEEK_SET);
        temp = fgetc(PPFFile);
        int i = 0;
        while(i < numOfCTFCurvePoints){
            while (temp != '.')
                temp = fgetc(PPFFile);
            validDigits = 0;
            temp = fgetc(PPFFile);
            CTF_x[i] = 0;
            CTF_y[i] = 0;
            while(temp != ' '){
                validDigits ++;
                CTF_x[i] += (temp - 48) * dividedByTen(validDigits);
                temp = fgetc(PPFFile);
            }

            while (temp != '.')
                temp = fgetc(PPFFile);
            validDigits = 0;
            temp = fgetc(PPFFile);
            while (temp != ' '){
                validDigits ++;
                CTF_y[i] += (temp - 48) * dividedByTen(validDigits);
                temp = fgetc(PPFFile);
            }
            tempResult = 255.0 * CTF_x[i];
            if (tempResult - (int)tempResult >= 0.5)
                CTF_int_x[i] = (int)tempResult + 1;
            else
                CTF_int_x[i] = (int)tempResult;
            tempResult = 255.0 * CTF_y[i];
            if (tempResult - (int)tempResult >= 0.5)
                CTF_int_y[i] = (int)tempResult + 1;
            else
                CTF_int_y[i] = (int)tempResult;
            i ++;
        }
        CTF_x[numOfCTFCurvePoints - 1] = 1;
        CTF_y[numOfCTFCurvePoints - 1] = 1;
        CTF_int_x[numOfCTFCurvePoints - 1] = 255;
        CTF_int_y[numOfCTFCurvePoints - 1] = 255;
        for (i = 0; i < numOfCTFCurvePoints - 1; i ++){
            CTF_k[i] = (CTF_y[i + 1] - CTF_y[i]) / (CTF_x[i + 1] - CTF_x[i]);
            if (i == 0){
                CTF_a[i] = 0;
                CTF_int_a[i] = 0;
            }
            else{
                CTF_a[i] = CTF_y[i + 1] -CTF_x[i + 1] * CTF_k[i];
                tempResult = CTF_a[i] * 255.0;
                if (tempResult - (int)tempResult >= 0.5)
                    CTF_int_a[i] = (int)tempResult + 1;
                else
                    CTF_int_a[i] = (int)tempResult;
            }
        }
    }

    char key2[27] = {'/','C','I','P','3','T','r','a','n','s','f','e','r','P','l','a','t','e','C','u','r','v','e','D','a','t','a'};
    long location2 = searchKeyword(PPFFile, 0, key2, 27, 1);

    if (location2 == -1){
        fclose(PPFFile);
        return -1;
    }

    numOfCTPCurvePoints = 0;
    fseek(PPFFile, location2, SEEK_SET);
    temp = fgetc(PPFFile);
    while (temp != ']'){
        if (temp == '.')
            numOfCTPCurvePoints ++;
        temp = fgetc(PPFFile);
    }
    numOfCTPCurvePoints /= 2;
    if (numOfCTPCurvePoints != 0){
        CTP_x = new float[numOfCTPCurvePoints];
        CTP_y = new float[numOfCTPCurvePoints];
        CTP_k = new float[numOfCTPCurvePoints - 1];
        CTP_a = new float[numOfCTPCurvePoints - 1];

        CTP_int_x = new BYTE[numOfCTPCurvePoints];
        CTP_int_y = new BYTE[numOfCTPCurvePoints];
        CTP_int_a = new BYTE[numOfCTPCurvePoints];
    }
    else{
        CTP_x = new float[2];
        CTP_y = new float[2];
        CTP_k = new float[2 - 1];
        CTP_a = new float[2 - 1];

        CTP_int_x = new BYTE[2];
        CTP_int_y = new BYTE[2];
        CTP_int_a = new BYTE[2];
    }
    if (numOfCTPCurvePoints == 2 || numOfCTPCurvePoints == 0){
        isCTPIdentity = true;
        CTP_x[0] = 0;
        CTP_y[0] = 0;
        CTP_x[1] = 1;
        CTP_y[1] = 1;
    }
    else{
        fseek(PPFFile, location2, SEEK_SET);
        temp = fgetc(PPFFile);
        int i = 0;
        while(i < numOfCTPCurvePoints){
            while (temp != '.')
                temp = fgetc(PPFFile);
            validDigits = 0;
            temp = fgetc(PPFFile);
            CTP_x[i] = 0;
            CTP_y[i] = 0;
            while(temp != ' '){
                validDigits ++;
                CTP_x[i] += (temp - 48) * dividedByTen(validDigits);
                temp = fgetc(PPFFile);
            }

            while (temp != '.')
                temp = fgetc(PPFFile);
            validDigits = 0;
            temp = fgetc(PPFFile);
            while (temp != ' '){
                validDigits ++;
                CTP_y[i] += (temp - 48) * dividedByTen(validDigits);
                temp = fgetc(PPFFile);
            }
            tempResult = 255.0 * CTP_x[i];
            if (tempResult - (int)tempResult >= 0.5)
                CTP_int_x[i] = (int)tempResult + 1;
            else
                CTP_int_x[i] = (int)tempResult;
            tempResult = 255.0 * CTP_y[i];
            if (tempResult - (int)tempResult >= 0.5)
                CTP_int_y[i] = (int)tempResult + 1;
            else
                CTP_int_y[i] = (int)tempResult;
            i ++;
        }
        CTP_x[numOfCTPCurvePoints - 1] = 1;
        CTP_y[numOfCTPCurvePoints - 1] = 1;
        CTP_int_x[numOfCTPCurvePoints - 1] = 255;
        CTP_int_y[numOfCTPCurvePoints - 1] = 255;

        for (i = 0; i < numOfCTPCurvePoints - 1; i ++){
            CTP_k[i] = (CTP_y[i + 1] - CTP_y[i]) / (CTP_x[i + 1] - CTP_x[i]);
            if (i == 0){
                CTP_a[i] = 0;
                CTP_int_a[i] = 0;
            }
            else{
                CTP_a[i] = CTP_y[i + 1] -CTP_x[i + 1] * CTP_k[i];
                tempResult = CTP_a[i] * 255.0;
                if (tempResult - (int)tempResult >= 0.5)
                    CTP_int_a[i] = (int)tempResult + 1;
                else
                    CTP_int_a[i] = (int)tempResult;
            }
        }
    }
    fclose(PPFFile);
    return 0;
}
int PPFHandler::getEncodingAndCompression()
{
    char encodingKeyword[24] = {'C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','E','n','c','o','d','i','n','g'};
    char temp;
    int encoding = -1;

    FILE *PPFFile = fopen(fileName, "rb");
    long location1 = searchKeyword(PPFFile, 0, encodingKeyword, 24, 1);
    if (location1 == -1){
        fclose(PPFFile);
        return -1;
    }
    fseek(PPFFile, location1, SEEK_SET);
    temp = fgetc(PPFFile);
    while (temp != '/')
        temp = fgetc(PPFFile);
    temp = fgetc(PPFFile);
    if (temp == 'B'){
        char compressionKeyword[27] = {'C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','C','o','m','p','r','e','s','s','i','o','n'};
        long location2 = searchKeyword(PPFFile, 0, compressionKeyword, 27, 1);

        fseek(PPFFile, location2, SEEK_SET);
        temp = fgetc(PPFFile);
        while (temp != '/')
            temp = fgetc(PPFFile);
        temp = fgetc(PPFFile);
        if (temp == 'R'){
            encoding = 1;       //Binary encoding and run length compresson
            char dataComponentSizeKeyword[25] = {'C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','D','a','t','a','S','i','z','e',' '};
            for (int inkCount = 0; inkCount < numberOfColors; inkCount ++){
                if (inkCount == 0){
                    location2 = searchKeyword(PPFFile, 0, dataComponentSizeKeyword, 25, 1);
                    if (location2 == -1){
                        fclose(PPFFile);
                        return -1;
                    }
                    fseek(PPFFile, location2, SEEK_SET);
                    temp = fgetc(PPFFile);
                    while (temp == ' ')
                        temp = fgetc(PPFFile);
                    dataComponentSize[inkCount] = 0;
                    while (temp != ' '){
                        dataComponentSize[inkCount] = dataComponentSize[inkCount] * 10 + (temp - 48);
                        temp = fgetc(PPFFile);
                    }
                }
                else{
                    location2 = searchKeyword(PPFFile, location2 + dataComponentSize[inkCount - 1], dataComponentSizeKeyword, 25, 1);
                    fseek(PPFFile, location2, SEEK_SET);
                    temp = fgetc(PPFFile);
                    while (temp == ' ')
                        temp = fgetc(PPFFile);
                    dataComponentSize[inkCount] = 0;
                    while (temp != ' '){
                        dataComponentSize[inkCount] = dataComponentSize[inkCount] * 10 + (temp - 48);
                        temp = fgetc(PPFFile);
                    }
                }
            }
        }
    }
    else if (temp == 'A'){
        char compressionKeyword[27] = {'C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e','C','o','m','p','r','e','s','s','i','o','n'};
        long location2 = searchKeyword(PPFFile, 0, compressionKeyword, 27, 1);

        fseek(PPFFile, location2, SEEK_SET);
        temp = fgetc(PPFFile);
        while (temp != '/')
            temp = fgetc(PPFFile);
        temp = fgetc(PPFFile);
        if (temp == 'N'){
            encoding = 2;       //ASCIIHexDecode encoding and run length compression
            for (int inkCount = 0; inkCount < numberOfColors; inkCount ++){
                dataComponentSize[inkCount] = image_size * 2;
            }
        }
    }

    fclose(PPFFile);
    return encoding;
}
int PPFHandler::getImageData(int inkFountainWidth, int plateHeight)
{
    float tempResult1, tempResult2;

    fileType = PPF_FILE;

    if (image_width > image_height){
        tempResult1 = (float)image_width / (float)MAX_THUMBNAIL_WIDTH;
        tempResult2 = (float)image_height / (float)MAX_THUMBNAIL_HEIGHT;
    }
    else{
        tempResult1 = (float)image_height / (float)MAX_THUMBNAIL_WIDTH;
        tempResult2 = (float)image_width / (float)MAX_THUMBNAIL_HEIGHT;
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
    //NOTE: the test ppf file was generated under windows os, meaning the next line characters contains
    //2 characters: '\r' and '\n'. In some cases, the ppf file could be generated under Mac os, meaning
    //the next line character contains only '\r'
    char imageDataKeyword[17] = {'C','I','P','3','P','r','e','v','i','e','w','I','m','a','g','e', '\r'};
    long location[15];   //Komori 6+1 has C,M,Y,K and two special colors and 1 Diecut;
    char temp, pixelValue;
    float tempResult;
    int i;
    double tempWidth, tempHeight;

    if (getTransferCurve() == -1)
        return -1;

    int encoding = getEncodingAndCompression();

    //calculate the ink fountain width and length in pixel based on the input of ink fountain width
    //and length in mm
    tempWidth = xResolution * (double)inkFountainWidth / 2.54;
    if (tempWidth - (int)tempWidth >= 0.5)
        fountainWidthInPixel = (int)tempWidth + 1;
    else
        fountainWidthInPixel = (int)tempWidth;
    if (fountainWidthInPixel % shrinkRatio != 0)
        thumbnailFountainWidth = fountainWidthInPixel / shrinkRatio + 1;
    else
        thumbnailFountainWidth = fountainWidthInPixel / shrinkRatio;

    if (fountainWidthInPixel >= image_width)
        image_location = (fountainWidthInPixel - image_width) / 2;
    else
        image_location = (image_width - fountainWidthInPixel) / 2;
    if (fountainWidthInPixel >= image_height)
        image_location_afterRotation = (fountainWidthInPixel - image_height) / 2;
    else
        image_location_afterRotation = (image_height - fountainWidthInPixel) / 2;

    thumbnailLocation = image_location / shrinkRatio;
    thumbnailLocationAfterRotation = image_location_afterRotation / shrinkRatio;

    tempHeight = yResolution * (double)plateHeight / 2.54;

    if (tempHeight - (int)tempHeight >= 0.5)
        plateHeightInPixel = (int)tempHeight + 1;
    else
        plateHeightInPixel = (int)tempHeight;
    if (plateHeightInPixel % shrinkRatio != 0)
        thumbnailFountainHeight = plateHeightInPixel / shrinkRatio + 1;
    else
        thumbnailFountainHeight = plateHeightInPixel / shrinkRatio;

    int originalImageWidth = image_width;
    int originalImageHeight = image_height;
    int widthLeftOver = image_width % shrinkRatio;
    int heightLeftOver = image_height % shrinkRatio;
    if (widthLeftOver != 0){
        thumbnailWidth = image_width / shrinkRatio + 1;
        image_width = thumbnailWidth * shrinkRatio;
    }
    else
        thumbnailWidth = image_width / shrinkRatio;
    if (heightLeftOver != 0){
        thumbnailHeight = image_height / shrinkRatio + 1;
        image_height = thumbnailHeight * shrinkRatio;
    }
    else
        thumbnailHeight = image_height / shrinkRatio;
qDebug() << "thumbnailWidth: " << thumbnailWidth;
qDebug() << "thumbnailHeight: " << thumbnailHeight;
    thumbnailSize = thumbnailWidth * thumbnailHeight;
    cyan = new unsigned char[thumbnailSize];
    magenta = new unsigned char[thumbnailSize];
    yellow = new unsigned char[thumbnailSize];
    black = new unsigned char[thumbnailSize];
    if (numberOfColors >= 5)
        specialColor1 = new unsigned char[thumbnailSize];
    if (numberOfColors >= 6)
        specialColor2 = new unsigned char[thumbnailSize];
    unsigned int *cyanTotal = new unsigned int[thumbnailSize];
    unsigned int *magentaTotal = new unsigned int[thumbnailSize];
    unsigned int *yellowTotal = new unsigned int[thumbnailSize];
    unsigned int *blackTotal = new unsigned int[thumbnailSize];
    unsigned int *specialColor1Total = NULL;
    if (numberOfColors >= 5)
        specialColor1Total = new unsigned int[thumbnailSize];
    unsigned int *specialColor2Total = NULL;
    if (numberOfColors >= 6)
        specialColor2Total = new unsigned int[thumbnailSize];

    unsigned int *inkTotal[6] = {cyanTotal, magentaTotal, yellowTotal, blackTotal};
    inkTotal[0] = cyanTotal;
    inkTotal[1] = magentaTotal;
    inkTotal[2] = yellowTotal;
    inkTotal[3] = blackTotal;
    if (numberOfColors >= 5)
        inkTotal[4] = specialColor1Total;
    if (numberOfColors >= 6)
        inkTotal[5] = specialColor2Total;

    i = thumbnailSize;
    while(i--){
        cyan[i] = 0;
        magenta[i] = 0;
        yellow[i] = 0;
        black[i] = 0;

        cyanTotal[i] = 0;
        magentaTotal[i] = 0;
        yellowTotal[i] = 0;
        blackTotal[i] = 0;
    }
    i = thumbnailSize;
    if (numberOfColors >= 5){
        while (i --){
            specialColor1[i] = 0;
            specialColor1Total[i] = 0;
        }
    }
    i = thumbnailSize;
    if (numberOfColors >= 6){
        while(i --){
            specialColor2[i] = 0;
            specialColor2Total[i] = 0;
        }
    }

    if (contiguous_or_separate == SEPARATE){
        //get the locations of the image data of the 4 color components
        for (i = 0; i < numberOfColors; i ++){
            if (!hasMultiplePPFFiles){
                FILE *PPFFile = fopen(fileName, "rb");
                if (i >= 1)
                    location[i] = searchKeyword(PPFFile, location[i - 1] + dataComponentSize[i - 1], imageDataKeyword, 17, 1);
                else
                    location[i] = searchKeyword(PPFFile, 0, imageDataKeyword, 17, 1);
                fclose(PPFFile);
            }
            else{
                FILE *PPFFile = fopen(file[i].fileName.toAscii().data(), "rb");
                location[i] = searchKeyword(PPFFile, 0, imageDataKeyword, 17, 1);
                fclose(PPFFile);
            }
        }
        if (!hasMultiplePPFFiles){
            if (pageOfDieCut != -1){
                for (i = pageOfDieCut; i < (numberOfColors - 1); i ++)
                    location[i] = location[i + 1];
            }
        }

        int currentIndexForThumbnail = 0;//currentIndexForThumbnail;
        int j;
        int x;
        //get the image data of cyan component
        //NOTE: in ppf 0xff represents 0%
        if (pageOfDieCut != -1){
            if (numberOfColors >= 7)
                numberOfColors = 6;
        }
        if (direction == BOTTOM2TOP_LEFT2RIGHT ||
            direction == BOTTOM2TOP_RIGHT2LEFT ||
            direction == TOP2BOTTOM_LEFT2RIGHT ||
            direction == TOP2BOTTOM_RIGHT2LEFT){
            BYTE *decodedLine = new BYTE[originalImageHeight];
            emit progressRange(5 * image_width);
            emit percentage(image_width / 2);

            for (int inkCount = 0; inkCount < numberOfColors; inkCount ++){
                FILE *PPFFile;
                if (!hasMultiplePPFFiles)
                    PPFFile = fopen(fileName, "rb");
                else{
                    if (file[inkCount].color != DIECUT)
                        PPFFile = fopen(file[inkCount].fileName.toAscii().data(), "rb");
                    else
                        continue;
                }
                fseek(PPFFile, location[inkCount], SEEK_SET);
                fgetc(PPFFile); // next line character
                if (encoding == 1){
                    unsigned char repeatLength = 0;
                    i = 0;
                    while (i < image_width){
                        if (i < originalImageWidth){
                            j = 0;
                            while (j < image_height){
                                if (j < originalImageHeight){
                                    repeatLength = fgetc(PPFFile);
                                    if (repeatLength > 128){
                                        repeatLength --;
                                        repeatLength = ~repeatLength;
                                        repeatLength ++;
                                        pixelValue = 255 - fgetc(PPFFile);
                                        if (!isCTFIdentity){
                                            for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                                if (pixelValue <= CTF_int_x[j]){
                                                    tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        if (!isCTPIdentity){
                                            for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                                if (pixelValue <= CTP_int_x[j]){
                                                    tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        for (int decodedLineIndex = j; decodedLineIndex < (j + repeatLength); decodedLineIndex ++){
                                            decodedLine[decodedLineIndex] = pixelValue;
                                        }
                                        j += repeatLength;
                                    }
                                    else if (repeatLength < 128){
                                        repeatLength ++;
                                        for (int decodedLineIndex = j; decodedLineIndex < (j + repeatLength); decodedLineIndex ++){
                                            pixelValue = 255 - fgetc(PPFFile);
                                            if (!isCTFIdentity){
                                                for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                                    if (pixelValue <= CTF_int_x[j]){
                                                        tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                                        if (tempResult - (int)tempResult >= 0.5)
                                                            pixelValue = (int)tempResult + 1;
                                                        else
                                                            pixelValue = (int)tempResult;
                                                        break;
                                                    }
                                                }
                                            }
                                            if (!isCTPIdentity){
                                                for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                                    if (pixelValue <= CTP_int_x[j]){
                                                        tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                                        if (tempResult - (int)tempResult >= 0.5)
                                                            pixelValue = (int)tempResult + 1;
                                                        else
                                                            pixelValue = (int)tempResult;
                                                        break;
                                                    }
                                                }
                                            }
                                            decodedLine[decodedLineIndex] = pixelValue;
                                        }
                                        j += repeatLength;
                                    }
                                }
                                else
                                    j ++;
                            }
                            x = i / shrinkRatio * thumbnailHeight;
                            j = 0;
                            while (j < image_height){
                                if (j < originalImageHeight){
                                    currentIndexForThumbnail = x + j / shrinkRatio;
                                    inkTotal[inkCount][currentIndexForThumbnail] += decodedLine[j];
                                }
                                j ++;
                            }
                        }
                        i ++;
                    }
                }
                else if (encoding == 2){
                    temp = fgetc(PPFFile);
                    i = 0;
                    if ((image_height != originalImageHeight) || (image_width != originalImageWidth)){
                        while (i < image_width){
                            if (i < originalImageWidth){
                                j = 0;
                                x = i / shrinkRatio * thumbnailHeight;
                                while (j < image_height){
                                    if (j < originalImageHeight){
                                        currentIndexForThumbnail = x + j / shrinkRatio;

                                        while((temp == '\r') || (temp == '\n'))
                                            temp = fgetc(PPFFile);
                                        if (temp <= 57)
                                            pixelValue = (temp - 48) << 4;
                                        else if (temp <= 70)
                                            pixelValue = (temp - 55) << 4;
                                        else
                                            pixelValue = (temp - 87) << 4;
                                        temp = fgetc(PPFFile);
                                        while ((temp == '\r') || (temp == '\n'))
                                            temp = fgetc(PPFFile);
                                        if (temp <= 57)
                                            pixelValue += (temp - 48);
                                        else if (temp <= 70)
                                            pixelValue += (temp - 55);
                                        else
                                            pixelValue += (temp - 87);
                                        pixelValue = 255 - pixelValue;
                                        if (!isCTFIdentity){
                                            for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                                if (pixelValue <= CTF_int_x[j]){
                                                    tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        if (!isCTPIdentity){
                                            for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                                if (pixelValue <= CTP_int_x[j]){
                                                    tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        inkTotal[inkCount][currentIndexForThumbnail] += pixelValue;
                                        temp = fgetc(PPFFile);
                                    }
                                    j ++;
                                }
                            }
                            i ++;
                        }
                    }
                    else{
                        while (i < originalImageWidth){
                            j = 0;
                            x = i / shrinkRatio * thumbnailHeight;
                            while (j < originalImageHeight){
                                currentIndexForThumbnail = x + j / shrinkRatio;

                                while((temp == '\r') || (temp == '\n'))
                                    temp = fgetc(PPFFile);
                                if (temp <= 57)
                                    pixelValue = (temp - 48) << 4;
                                else if (temp <= 70)
                                    pixelValue = (temp - 55) << 4;
                                else
                                    pixelValue = (temp - 87) << 4;
                                temp = fgetc(PPFFile);
                                while ((temp == '\r') || (temp == '\n'))
                                    temp = fgetc(PPFFile);
                                if (temp <= 57)
                                    pixelValue += (temp - 48);
                                else if (temp <= 70)
                                    pixelValue += (temp - 55);
                                else
                                    pixelValue += (temp - 87);
                                pixelValue = 255 - pixelValue;
                                if (!isCTFIdentity){
                                    for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                        if (pixelValue <= CTF_int_x[j]){
                                            tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                            if (tempResult - (int)tempResult >= 0.5)
                                                pixelValue = (int)tempResult + 1;
                                            else
                                                pixelValue = (int)tempResult;
                                            break;
                                        }
                                    }
                                }
                                if (!isCTPIdentity){
                                    for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                        if (pixelValue <= CTP_int_x[j]){
                                            tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                            if (tempResult - (int)tempResult >= 0.5)
                                                pixelValue = (int)tempResult + 1;
                                            else
                                                pixelValue = (int)tempResult;
                                            break;
                                        }
                                    }
                                }
                                inkTotal[inkCount][currentIndexForThumbnail] += pixelValue;
                                temp = fgetc(PPFFile);
                                j ++;
                            }
                            i ++;
                        }
                    }
                }

                emit percentage(image_width * (inkCount + 1));
                fclose(PPFFile);
            }
            delete []decodedLine;
            decodedLine = NULL;
        }
        else if (direction == LEFT2RIGHT_TOP2BOTTOM ||
                 direction == LEFT2RIGHT_BOTTOM2TOP ||
                 direction == RIGHT2LEFT_TOP2BOTTOM ||
                 direction == RIGHT2LEFT_BOTTOM2TOP){
            BYTE *decodedLine = new BYTE[originalImageWidth];
            emit progressRange(5 * image_height);
            emit percentage(image_height / 2);
            for (int inkCount = 0; inkCount < numberOfColors; inkCount ++){
                FILE *PPFFile;
                if (!hasMultiplePPFFiles)
                    PPFFile = fopen(fileName, "rb");
                else{
                    if (file[inkCount].color != DIECUT)
                        PPFFile = fopen(file[inkCount].fileName.toAscii().data(), "rb");
                    else
                        continue;
                }
                fseek(PPFFile, location[inkCount], SEEK_SET);
                fgetc(PPFFile);     //next line character
                if (encoding == 1){
                    unsigned char repeatLength = 0;
                    i = 0;
                    while (i < image_height){
                        if (i < originalImageHeight){
                            j = 0;
                            while (j < image_width){
                                if (j < originalImageWidth){
                                    repeatLength = fgetc(PPFFile);
                                    if (repeatLength > 128){
                                        repeatLength --;
                                        repeatLength = ~repeatLength;
                                        repeatLength ++;
                                        pixelValue = 255 - fgetc(PPFFile);
                                        if (!isCTFIdentity){
                                            for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                                if (pixelValue <= CTF_int_x[j]){
                                                    tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        if (!isCTPIdentity){
                                            for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                                if (pixelValue <= CTP_int_x[j]){
                                                    tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        for (int decodedLineIndex = j; decodedLineIndex < (j + repeatLength); decodedLineIndex ++){
                                            decodedLine[decodedLineIndex] = pixelValue;
                                        }
                                        j += repeatLength;
                                    }
                                    else if (repeatLength < 128){
                                        repeatLength ++;
                                        for (int decodedLineIndex = j; decodedLineIndex < (j + repeatLength); decodedLineIndex ++){
                                            pixelValue = 255 - fgetc(PPFFile);
                                            if (!isCTFIdentity){
                                                for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                                    if (pixelValue <= CTF_int_x[j]){
                                                        tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                                        if (tempResult - (int)tempResult >= 0.5)
                                                            pixelValue = (int)tempResult + 1;
                                                        else
                                                            pixelValue = (int)tempResult;
                                                        break;
                                                    }
                                                }
                                            }
                                            if (!isCTPIdentity){
                                                for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                                    if (pixelValue <= CTP_int_x[j]){
                                                        tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                                        if (tempResult - (int)tempResult >= 0.5)
                                                            pixelValue = (int)tempResult + 1;
                                                        else
                                                            pixelValue = (int)tempResult;
                                                        break;
                                                    }
                                                }
                                            }
                                            decodedLine[decodedLineIndex] = pixelValue;
                                        }
                                        j += repeatLength;
                                    }
                                }
                                else
                                    j ++;
                            }
                            x = i / shrinkRatio * thumbnailWidth;
                            j = 0;
                            while (j < image_width){
                                if (j < originalImageWidth){
                                    currentIndexForThumbnail = x + j / shrinkRatio;
                                    inkTotal[inkCount][currentIndexForThumbnail] += decodedLine[j];
                                }
                                j ++;
                            }
                        }
                        i ++;
                    }
                }
                else if (encoding == 2){
                    temp = fgetc(PPFFile);
                    i = 0;
                    if ((image_height != originalImageHeight) || (image_width != originalImageWidth)){
                        while (i < image_height){
                            if (i < originalImageHeight){
                                j = 0;
                                x = i / shrinkRatio * thumbnailWidth;
                                while (j < image_width){
                                    if (j < originalImageWidth){
                                        currentIndexForThumbnail = x + j / shrinkRatio;

                                        while((temp == '\r') || (temp == '\n'))
                                            temp = fgetc(PPFFile);
                                        if (temp <= 57)
                                            pixelValue = (temp - 48) << 4;
                                        else if (temp <= 70)
                                            pixelValue = (temp - 55) << 4;
                                        else
                                            pixelValue = (temp - 87) << 4;
                                        temp = fgetc(PPFFile);
                                        while ((temp == '\r') || (temp == '\n'))
                                            temp = fgetc(PPFFile);
                                        if (temp <= 57)
                                            pixelValue += (temp - 48);
                                        else if (temp <= 70)
                                            pixelValue += (temp - 55);
                                        else
                                            pixelValue += (temp - 87);
                                        pixelValue = 255 - pixelValue;
                                        if (!isCTFIdentity){
                                            for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                                if (pixelValue <= CTF_int_x[j]){
                                                    tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        if (!isCTPIdentity){
                                            for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                                if (pixelValue <= CTP_int_x[j]){
                                                    tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                                    if (tempResult - (int)tempResult >= 0.5)
                                                        pixelValue = (int)tempResult + 1;
                                                    else
                                                        pixelValue = (int)tempResult;
                                                    break;
                                                }
                                            }
                                        }
                                        inkTotal[inkCount][currentIndexForThumbnail] += pixelValue;
                                        temp = fgetc(PPFFile);
                                    }
                                    j ++;
                                }
                            }
                            i ++;
                            //if (i % (image_height / 100) == 0 && (i >= (image_width / 100)))
                            //    emit percentage(i + image_height * inkCount);
                        }
                    }
                    else{
                        while (i < originalImageHeight){
                            j = 0;
                            x = i / shrinkRatio * thumbnailWidth;
                            while (j < originalImageWidth){
                                currentIndexForThumbnail = x + j / shrinkRatio;

                                while((temp == '\r') || (temp == '\n'))
                                    temp = fgetc(PPFFile);
                                if (temp <= 57)
                                    pixelValue = (temp - 48) << 4;
                                else if (temp <= 70)
                                    pixelValue = (temp - 55) << 4;
                                else
                                    pixelValue = (temp - 87) << 4;
                                temp = fgetc(PPFFile);
                                while ((temp == '\r') || (temp == '\n'))
                                    temp = fgetc(PPFFile);
                                if (temp <= 57)
                                    pixelValue += (temp - 48);
                                else if (temp <= 70)
                                    pixelValue += (temp - 55);
                                else
                                    pixelValue += (temp - 87);
                                pixelValue = 255 - pixelValue;
                                if (!isCTFIdentity){
                                    for (int j = 1; j < numOfCTFCurvePoints; j ++){
                                        if (pixelValue <= CTF_int_x[j]){
                                            tempResult = CTF_int_a[j - 1] + CTF_k[j - 1] * pixelValue;
                                            if (tempResult - (int)tempResult >= 0.5)
                                                pixelValue = (int)tempResult + 1;
                                            else
                                                pixelValue = (int)tempResult;
                                            break;
                                        }
                                    }
                                }
                                if (!isCTPIdentity){
                                    for (int j = 1; j < numOfCTPCurvePoints; j ++){
                                        if (pixelValue <= CTP_int_x[j]){
                                            tempResult = CTP_int_a[j - 1] + CTP_k[j - 1] * pixelValue;
                                            if (tempResult - (int)tempResult >= 0.5)
                                                pixelValue = (int)tempResult + 1;
                                            else
                                                pixelValue = (int)tempResult;
                                            break;
                                        }
                                    }
                                }
                                inkTotal[inkCount][currentIndexForThumbnail] += pixelValue;
                                temp = fgetc(PPFFile);
                                j ++;
                            }
                            i ++;
                            //if (i % (image_height / 100) == 0 && (i >= (image_width / 100)))
                            //    emit percentage(i + image_height * inkCount);
                        }
                    }
                }

                emit percentage(image_height * (inkCount + 1));
                fclose(PPFFile);
            }
            delete []decodedLine;
            decodedLine = NULL;
        }
    }
    //if the color components are contiguously stored in the image data
    else if (contiguous_or_separate == CONTIGUOUS){
        return -1;
    }

    BYTE *color[numberOfColors];
    if (!hasMultiplePPFFiles){
        for (i = 0; i < 4; i ++){
            if (colorOrder[i] == 1)
                color[i] = cyan;
            else if (colorOrder[i] == 2)
                color[i] = magenta;
            else if (colorOrder[i] == 3)
                color[i] = yellow;
            else if (colorOrder[i] == 4)
                color[i] = black;
        }
    }
    else{
        for (i = 0; i < 4; i ++){
            if (file[i].color == CYAN)
                color[i] = cyan;
            else if (file[i].color == MAGENTA)
                color[i] = magenta;
            else if (file[i].color == YELLOW)
                color[i] = yellow;
            else if (file[i].color == BLACK)
                color[i] = black;
        }
    }
    if (numberOfColors == 5)
        color[numberOfColors - 1] = specialColor1;
    if (numberOfColors >= 6){
        color[numberOfColors - 2] = specialColor1;
        color[numberOfColors - 1] = specialColor2;
    }

    int q = shrinkRatio * shrinkRatio;
    for (i = 0; i < thumbnailSize; i ++){
        for (int j = 0; j < numberOfColors; j ++)
            color[j][i] = inkTotal[j][i] / q;
    }

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
    if (direction == BOTTOM2TOP_LEFT2RIGHT ||
        direction == BOTTOM2TOP_RIGHT2LEFT ||
        direction == TOP2BOTTOM_LEFT2RIGHT ||
        direction == TOP2BOTTOM_RIGHT2LEFT){
        int maxImageDimension = thumbnailWidth;
        if (thumbnailHeight > maxImageDimension)
            maxImageDimension = thumbnailHeight;

        cyan_RGBConversion = new BYTE[thumbnailSize * 4];
        magenta_RGBConversion = new BYTE[thumbnailSize * 4];
        yellow_RGBConversion = new BYTE[thumbnailSize * 4];
        black_RGBConversion = new BYTE[thumbnailSize * 4];
        all_RGBConversion = new BYTE[thumbnailSize * 4];
        if (numberOfColors >= 5)
            color1_RGBConversion = new BYTE[thumbnailSize * 4];
        if (numberOfColors >= 6)
            color2_RGBConversion = new BYTE[thumbnailSize * 4];

        i = 0;
        int j = 0;
        while (i < thumbnailSize){
            cyan_RGBConversion[j + 3] = 255;
            cyan_RGBConversion[j + 2] = 255 - cyan[i];
            cyan_RGBConversion[j + 1] = 255;
            cyan_RGBConversion[j] = 255;

            magenta_RGBConversion[j + 3] = 255;
            magenta_RGBConversion[j + 2] = 255;
            magenta_RGBConversion[j + 1] = 255 - magenta[i];
            magenta_RGBConversion[j] = 255;

            yellow_RGBConversion[j + 3] = 255;
            yellow_RGBConversion[j + 2] = 255;
            yellow_RGBConversion[j + 1] = 255;
            yellow_RGBConversion[j] = 255 - yellow[i];

            black_RGBConversion[j + 3] = 255;
            black_RGBConversion[j + 2] = QColor::fromCmyk(0, 0, 0, black[i]).red();
            black_RGBConversion[j + 1] = QColor::fromCmyk(0, 0, 0, black[i]).green();
            black_RGBConversion[j] = QColor::fromCmyk(0, 0, 0, black[i]).blue();

            if (numberOfColors >= 5){
                color1_RGBConversion[j + 3] = 255;
                color1_RGBConversion[j + 2] = 255 - specialColor1[i];
                color1_RGBConversion[j + 1] = 255 - specialColor1[i];
                color1_RGBConversion[j] = 255 - specialColor1[i];
            }
            if (numberOfColors >= 6){
                color2_RGBConversion[j + 3] = 255;
                color2_RGBConversion[j + 2] = 255 - specialColor2[i];
                color2_RGBConversion[j + 1] = 255 - specialColor2[i];
                color2_RGBConversion[j] = 255 - specialColor2[i];
            }

            all_RGBConversion[j + 3] = 255;
            all_RGBConversion[j + 2] = QColor::fromCmyk(cyan[i], magenta[i],
                                                        yellow[i], black[i]).red();
            all_RGBConversion[j + 1] = QColor::fromCmyk(cyan[i], magenta[i],
                                                        yellow[i], black[i]).green();
            all_RGBConversion[j] = QColor::fromCmyk(cyan[i], magenta[i],
                                                    yellow[i], black[i]).blue();
            i ++;
            j += 4;
        }
        cyanComponent_horizontal = new QImage(cyan_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        cyanComponent_vertical = new QImage(cyan_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        magentaComponent_horizontal = new QImage(magenta_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        magentaComponent_vertical = new QImage(magenta_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        yellowComponent_horizontal = new QImage(yellow_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        yellowComponent_vertical = new QImage(yellow_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        blackComponent_horizontal = new QImage(black_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        blackComponent_vertical = new QImage(black_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        thumbnailImage_horizontal = new QImage(all_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        thumbnailImage_vertical = new QImage(all_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);

        if (numberOfColors >= 5){
            specialColor1Component_horizontal = new QImage(color1_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
            specialColor1Component_vertical = new QImage(color1_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        }
        if (numberOfColors >= 6){
            specialColor2Component_horizontal = new QImage(color2_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
            specialColor2Component_vertical = new QImage(color2_RGBConversion, thumbnailHeight, thumbnailWidth, QImage::Format_RGB32);
        }

        if (maxImageDimension > MAX_THUMBNAIL_HEIGHT){
            if (thumbnailWidth > thumbnailHeight){
                *cyanComponent_vertical = cyanComponent_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *magentaComponent_vertical = magentaComponent_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *yellowComponent_vertical = yellowComponent_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *blackComponent_vertical = blackComponent_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *thumbnailImage_vertical = thumbnailImage_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                if (numberOfColors >= 5)
                    *specialColor1Component_vertical = specialColor1Component_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                if (numberOfColors >= 6)
                    *specialColor2Component_vertical = specialColor2Component_vertical->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
            }
            if (thumbnailWidth > MAX_THUMBNAIL_WIDTH){
                *cyanComponent_horizontal = cyanComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
                *magentaComponent_horizontal = magentaComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
                *yellowComponent_horizontal = yellowComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
                *blackComponent_horizontal = blackComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
                *thumbnailImage_horizontal = thumbnailImage_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
                if (numberOfColors >= 5)
                    *specialColor1Component_horizontal = specialColor1Component_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
                if (numberOfColors >= 6)
                    *specialColor2Component_horizontal = specialColor2Component_horizontal->scaledToHeight(MAX_THUMBNAIL_WIDTH);
            }
        }

    }
    else if (direction == LEFT2RIGHT_TOP2BOTTOM ||
             direction == LEFT2RIGHT_BOTTOM2TOP ||
             direction == RIGHT2LEFT_TOP2BOTTOM ||
             direction == RIGHT2LEFT_BOTTOM2TOP){
        int maxImageDimension = thumbnailWidth;
        if (thumbnailHeight > maxImageDimension)
            maxImageDimension = thumbnailHeight;
        cyan_RGBConversion = new BYTE[thumbnailSize * 4];
        magenta_RGBConversion = new BYTE[thumbnailSize * 4];
        yellow_RGBConversion = new BYTE[thumbnailSize * 4];
        black_RGBConversion = new BYTE[thumbnailSize * 4];
        if (numberOfColors >= 5)
            color1_RGBConversion = new BYTE[thumbnailSize * 4];
        if (numberOfColors >= 6)
            color2_RGBConversion = new BYTE[thumbnailSize * 4];
        all_RGBConversion = new BYTE[thumbnailSize * 4];

        i = 0;
        int j = 0;
        while (i < thumbnailSize){
            cyan_RGBConversion[j + 3] = 255;
            cyan_RGBConversion[j + 2] = 255 - cyan[i];
            cyan_RGBConversion[j + 1] = 255;
            cyan_RGBConversion[j] = 255;

            magenta_RGBConversion[j + 3] = 255;
            magenta_RGBConversion[j + 2] = 255;
            magenta_RGBConversion[j + 1] = 255 - magenta[i];
            magenta_RGBConversion[j] = 255;

            yellow_RGBConversion[j + 3] = 255;
            yellow_RGBConversion[j + 2] = 255;
            yellow_RGBConversion[j + 1] = 255;
            yellow_RGBConversion[j] = 255 - yellow[i];

            black_RGBConversion[j + 3] = 255;
            black_RGBConversion[j + 2] = QColor::fromCmyk(0, 0, 0, black[i]).red();
            black_RGBConversion[j + 1] = QColor::fromCmyk(0, 0, 0, black[i]).green();
            black_RGBConversion[j] = QColor::fromCmyk(0, 0, 0, black[i]).blue();

            if (numberOfColors >= 5){
                color1_RGBConversion[j + 3] = 255;
                color1_RGBConversion[j + 2] = 255 - specialColor1[i];
                color1_RGBConversion[j + 1] = 255 - specialColor1[i];
                color1_RGBConversion[j] = 255 - specialColor1[i];
            }
            if (numberOfColors >= 6){
                color2_RGBConversion[j + 3] = 255;
                color2_RGBConversion[j + 2] = 255 - specialColor2[i];
                color2_RGBConversion[j + 1] = 255 - specialColor2[i];
                color2_RGBConversion[j] = 255 - specialColor2[i];
            }

            all_RGBConversion[j + 3] = 255;
            all_RGBConversion[j + 2] = QColor::fromCmyk(cyan[i], magenta[i],
                                                        yellow[i], black[i]).red();
            all_RGBConversion[j + 1] = QColor::fromCmyk(cyan[i], magenta[i],
                                                        yellow[i], black[i]).green();
            all_RGBConversion[j] = QColor::fromCmyk(cyan[i], magenta[i],
                                                    yellow[i], black[i]).blue();
            i ++;
            j += 4;
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
        if (maxImageDimension > MAX_THUMBNAIL_HEIGHT){
            if (thumbnailHeight > MAX_THUMBNAIL_WIDTH){
                *cyanComponent_vertical = cyanComponent_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
                *magentaComponent_vertical = magentaComponent_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
                *yellowComponent_vertical = yellowComponent_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
                *blackComponent_vertical = blackComponent_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
                *thumbnailImage_vertical = thumbnailImage_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
                if (numberOfColors >= 5)
                    *specialColor1Component_vertical = specialColor1Component_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
                if (numberOfColors >= 6)
                    *specialColor2Component_vertical = specialColor2Component_vertical->scaledToWidth(MAX_THUMBNAIL_WIDTH);
            }
            if (thumbnailHeight > MAX_THUMBNAIL_HEIGHT){
                *cyanComponent_horizontal = cyanComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *magentaComponent_horizontal = magentaComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *yellowComponent_horizontal = yellowComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *blackComponent_horizontal = blackComponent_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                *thumbnailImage_horizontal = thumbnailImage_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                if (numberOfColors >= 5)
                    *specialColor1Component_horizontal = specialColor1Component_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
                if (numberOfColors >= 6)
                    *specialColor2Component_horizontal = specialColor2Component_horizontal->scaledToHeight(MAX_THUMBNAIL_HEIGHT);
            }
        }
    }

    colorValues[0] = cyan;
    colorValues[1] = magenta;
    colorValues[2] = yellow;
    colorValues[3] = black;

    return numberOfColors;
}
int PPFHandler::calculateInkCoverage(int num_of_ink_zones, int inkKeySteps)
{
    int i, j, index;

    if (fountainWidthInPixel == 0){
        return - 1;
    }
    else {
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

        if (thumbnailFountainWidth >= thumbnailWidth){
            sumOfCurrentColumnForCyan = new int[thumbnailFountainWidth];
            sumOfCurrentColumnForMagenta = new int[thumbnailFountainWidth];
            sumOfCurrentColumnForYellow = new int[thumbnailFountainWidth];
            sumOfCurrentColumnForBlack = new int[thumbnailFountainWidth];
            if (numberOfColors >= 5)
                sumOfCurrentColumnForSpecialColor1 = new int[thumbnailFountainWidth];
            if (numberOfColors >= 6)
                sumOfCurrentColumnForSpecialColor2 = new int[thumbnailFountainWidth];
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

        if (thumbnailFountainWidth >= thumbnailHeight){
            sumOfCurrentRowForCyan = new int[thumbnailFountainWidth];
            sumOfCurrentRowForMagenta = new int[thumbnailFountainWidth];
            sumOfCurrentRowForYellow = new int[thumbnailFountainWidth];
            sumOfCurrentRowForBlack = new int[thumbnailFountainWidth];
            if (numberOfColors >= 5)
                sumOfCurrentRowForSpecialColor1 = new int[thumbnailFountainWidth];
            if (numberOfColors >= 6)
                sumOfCurrentRowForSpecialColor2 = new int[thumbnailFountainWidth];
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
        double accurateZoneWidth = (double)thumbnailFountainWidth / (double)num_of_ink_zones;
        integerPartOfZoneWidth = (int)accurateZoneWidth;
        fractionPartOfZoneWidth = accurateZoneWidth - (int)accurateZoneWidth;
        /*******************************************************************************/
        if ((direction == BOTTOM2TOP_RIGHT2LEFT) || // this is the currently used direction
            (direction == TOP2BOTTOM_RIGHT2LEFT)){
            index = 0;
            if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
                i = thumbnailFountainWidth;
                while(i --){
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocation && i < (thumbnailLocation + thumbnailWidth)){
                        j = thumbnailHeight;
                        while (j --){
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
                    }
                }
            }
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
                i = thumbnailWidth;
                while(i --){
                    j = thumbnailHeight;
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    while (j --){
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
                }
            }
            else if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
                i = thumbnailFountainWidth;
                while(i --){
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocation && i < (thumbnailLocation + thumbnailWidth)){
                        j = thumbnailHeight;
                        while (j --){
                            if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
                                sumOfCurrentColumnForCyan[i] += cyan[index];
                                sumOfCurrentColumnForMagenta[i] += magenta[index];
                                sumOfCurrentColumnForYellow[i] += yellow[index];
                                sumOfCurrentColumnForBlack[i] += black[index];
                                if (numberOfColors >= 5)
                                    sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                                if (numberOfColors >= 6)
                                    sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                            }
                            index ++;
                        }
                    }
                }
            }
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){

                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
                i = thumbnailWidth;
                while(i --){
                    j = thumbnailHeight;
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    while (j --){
                        if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
                            sumOfCurrentColumnForCyan[i] += cyan[index];
                            sumOfCurrentColumnForMagenta[i] += magenta[index];
                            sumOfCurrentColumnForYellow[i] += yellow[index];
                            sumOfCurrentColumnForBlack[i] += black[index];
                            if (numberOfColors >= 5)
                                sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                            if (numberOfColors >= 6)
                                sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                        }
                        index ++;
                    }
                }
            }
        }
        else if ((direction == BOTTOM2TOP_LEFT2RIGHT) ||
                 (direction == TOP2BOTTOM_LEFT2RIGHT)){
            i = 0;
            index = 0;
            if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
                while(i < thumbnailFountainWidth){
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocation && i < (thumbnailLocation + thumbnailWidth)){
                        j = thumbnailHeight;
                        while (j --){
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
                    }
                    i ++;
                }
            }
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
                while(i < thumbnailWidth){
                    j = thumbnailHeight;
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    while (j --){
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
            }
            else if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
                while(i < thumbnailFountainWidth){
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocation && i < (thumbnailLocation + thumbnailWidth)){
                        j = thumbnailHeight;
                        while (j --){
                            if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
                                sumOfCurrentColumnForCyan[i] += cyan[index];
                                sumOfCurrentColumnForMagenta[i] += magenta[index];
                                sumOfCurrentColumnForYellow[i] += yellow[index];
                                sumOfCurrentColumnForBlack[i] += black[index];
                                if (numberOfColors >= 5)
                                    sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                                if (numberOfColors >= 6)
                                    sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                            }
                            index ++;
                        }
                    }
                    i ++;
                }
            }
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
                while(i < thumbnailWidth){
                    j = thumbnailHeight;
                    sumOfCurrentColumnForCyan[i] = 0;
                    sumOfCurrentColumnForMagenta[i] = 0;
                    sumOfCurrentColumnForYellow[i] = 0;
                    sumOfCurrentColumnForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentColumnForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentColumnForSpecialColor2[i] = 0;
                    while (j --){
                        if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
                            sumOfCurrentColumnForCyan[i] += cyan[index];
                            sumOfCurrentColumnForMagenta[i] += magenta[index];
                            sumOfCurrentColumnForYellow[i] += yellow[index];
                            sumOfCurrentColumnForBlack[i] += black[index];
                            if (numberOfColors >= 5)
                                sumOfCurrentColumnForSpecialColor1[i] += specialColor1[index];
                            if (numberOfColors >= 6)
                                sumOfCurrentColumnForSpecialColor2[i] += specialColor2[index];
                        }
                        index ++;
                    }
                    i ++;
                }
            }
        }
        else if ((direction == LEFT2RIGHT_BOTTOM2TOP) ||
                 (direction == LEFT2RIGHT_TOP2BOTTOM)){
            j = 0;
            index = 0;
            if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
                i = thumbnailFountainWidth;
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
                    while(i < thumbnailFountainWidth){
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
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
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
            else if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
                i = thumbnailFountainWidth;
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
                while (j < thumbnailFountainHeight){
                    i = 0;
                    while(i < thumbnailFountainWidth){
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
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
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
                index = heightOffset * thumbnailWidth;
                while (j < thumbnailFountainHeight){
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
        }
        else if ((direction == RIGHT2LEFT_BOTTOM2TOP) ||
                 (direction == RIGHT2LEFT_TOP2BOTTOM)){
            j = 0;
            index = 0;
            if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
                i = thumbnailFountainWidth;
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
                    i = thumbnailFountainWidth;
                    while(i --){
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
                    }
                    j ++;
                }
            }
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight >= thumbnailHeight){
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
                    i = thumbnailWidth;
                    while(i --){
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
                    j ++;
                }
            }
            else if (thumbnailFountainWidth >= thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
                i = thumbnailFountainWidth;
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
                while (j < thumbnailFountainHeight){
                    i = thumbnailFountainWidth;
                    while(i --){
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
                    }
                    j ++;
                }
            }
            else if (thumbnailFountainWidth < thumbnailWidth && thumbnailFountainHeight < thumbnailHeight){
                heightOffset = (thumbnailHeight - thumbnailFountainHeight) / 2;
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
                index = heightOffset * thumbnailWidth;
                while (j < thumbnailFountainHeight){
                    i = thumbnailWidth;
                    while(i --){
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
                    j ++;
                }
            }
        }
        /*******************************************************************************/

        /*******************************************************************************/
        if (direction == BOTTOM2TOP_RIGHT2LEFT ||
            direction == BOTTOM2TOP_LEFT2RIGHT){
            index = 0;
            if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
                for (i = 0; i < thumbnailFountainWidth; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                }
                for (j = 0; j < thumbnailWidth; j ++){
                    for (i = 0; i < thumbnailFountainWidth; i ++){
                        if (i >= thumbnailLocationAfterRotation && i < (thumbnailHeight + thumbnailLocationAfterRotation)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
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
                for (j = 0; j < thumbnailWidth; j ++){
                    for (i = 0; i < thumbnailHeight; i ++){
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
            else if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
                for (i = 0; i < thumbnailFountainWidth; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                }
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                index = thumbnailHeight * heightOffset;
                for (j = 0; j < thumbnailFountainHeight; j ++){
                    for (i = 0; i < thumbnailFountainWidth; i ++){
                        if (i >= thumbnailLocationAfterRotation && i < (thumbnailHeight + thumbnailLocationAfterRotation)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
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
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                index = thumbnailHeight * heightOffset;
                for (j = heightOffset; j < (thumbnailFountainHeight + heightOffset); j ++){
                    for (i = 0; i < thumbnailHeight; i ++){
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
        else if (direction == TOP2BOTTOM_RIGHT2LEFT ||
                 direction == TOP2BOTTOM_LEFT2RIGHT){
            index = 0;
            if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
                for (i = 0; i < thumbnailFountainWidth; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                }
                for (j = 0; j < thumbnailWidth; j ++){
                    i = thumbnailFountainWidth;
                    while(i --){
                        if (i >= thumbnailLocationAfterRotation && i < (thumbnailHeight + thumbnailLocationAfterRotation)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
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
                for (j = 0; j < thumbnailWidth; j ++){
                    i = thumbnailHeight;
                    while(i --){
                        sumOfCurrentRowForCyan[i] += cyan[index];
                        sumOfCurrentRowForMagenta[i] += magenta[index];
                        sumOfCurrentRowForYellow[i] += yellow[index];
                        sumOfCurrentRowForBlack[i] += black[index];
                        if (numberOfColors >= 5)
                            sumOfCurrentRowForSpecialColor1[i] +=specialColor1[index];
                        if (numberOfColors >= 6)
                            sumOfCurrentRowForSpecialColor2[i] += specialColor2[index];
                        index ++;
                    }
                }
            }
            else if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
                for (i = 0; i < thumbnailFountainWidth; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                }
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                index = thumbnailHeight * heightOffset;
                for (j = heightOffset; j < (thumbnailFountainHeight + heightOffset); j ++){
                    i = thumbnailFountainWidth;
                    while(i --){
                        if (i >= thumbnailLocationAfterRotation && i < (thumbnailHeight + thumbnailLocationAfterRotation)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
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
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                index = thumbnailHeight * heightOffset;
                for (j = heightOffset; j < (thumbnailFountainHeight + heightOffset); j ++){
                    i = thumbnailHeight;
                    while(i --){
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
        else if (direction == RIGHT2LEFT_BOTTOM2TOP ||
                 direction == LEFT2RIGHT_BOTTOM2TOP){
            index = 0;
            if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
                for (i = 0; i < thumbnailFountainWidth; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocationAfterRotation && i < (thumbnailLocationAfterRotation + thumbnailHeight)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
                for (i = 0; i < thumbnailHeight; i ++){
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
            else if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                for (i = 0; i < thumbnailFountainWidth; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocationAfterRotation && i < (thumbnailLocationAfterRotation + thumbnailHeight)){
                        for (j = 0; j < thumbnailWidth; j ++){
                            if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                for (i = 0; i < thumbnailHeight; i ++){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                    for (j = 0; j < thumbnailWidth; j ++){
                        if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
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
        else if (direction == RIGHT2LEFT_TOP2BOTTOM ||
                 direction == LEFT2RIGHT_TOP2BOTTOM){
            index = 0;
            if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
                i = thumbnailFountainWidth;
                while(i --){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocationAfterRotation && i < (thumbnailLocationAfterRotation + thumbnailHeight)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight >= thumbnailWidth){
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
            else if (thumbnailFountainWidth >= thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
                i = thumbnailFountainWidth;
                while(i --){
                    sumOfCurrentRowForCyan[i] = 0;
                    sumOfCurrentRowForMagenta[i] = 0;
                    sumOfCurrentRowForYellow[i] = 0;
                    sumOfCurrentRowForBlack[i] = 0;
                    if (numberOfColors >= 5)
                        sumOfCurrentRowForSpecialColor1[i] = 0;
                    if (numberOfColors >= 6)
                        sumOfCurrentRowForSpecialColor2[i] = 0;
                    if (i >= thumbnailLocationAfterRotation && i < (thumbnailLocationAfterRotation + thumbnailHeight)){
                        for (j = 0; j < thumbnailWidth; j ++){
                            if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
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
            else if (thumbnailFountainWidth < thumbnailHeight && thumbnailFountainHeight < thumbnailWidth){
                heightOffset = (thumbnailWidth - thumbnailFountainHeight) / 2;
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
                        if (j >= heightOffset && j < (thumbnailFountainHeight + heightOffset)){
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
        /*******************************************************************************/

        /***********calculate ink coverage values for original direction************/
        firstFraction = 0;
        lastFraction = fractionPartOfZoneWidth;
        i = 0;
        if (thumbnailFountainWidth >= thumbnailWidth)
            index = 0;
        else
            index = (thumbnailWidth - thumbnailFountainWidth) / 2;
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

            percentageValueForCyan[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);

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
        if (thumbnailFountainWidth >= thumbnailHeight)
            index = 0;
        else
            index = (thumbnailHeight - thumbnailFountainWidth) / 2;
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

            percentageValueForCyan[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i]  /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i]  /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);

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
        if (thumbnailFountainWidth >= thumbnailWidth){
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
        if (thumbnailFountainWidth >= thumbnailWidth)
            index = 0;
        else
            index = (thumbnailWidth - thumbnailFountainWidth) / 2;
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

            percentageValueForCyan[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);

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
        if (thumbnailFountainWidth >= thumbnailHeight){
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
                swapForRotatedSwap1[i] = rotatedSwap1[thumbnailHeight - 1 - i];
                swapForRotatedSwap2[i] = rotatedSwap2[thumbnailHeight - 1 - i];
                swapForRotatedSwap3[i] = rotatedSwap3[thumbnailHeight - 1 - i];
                swapForRotatedSwap4[i] = rotatedSwap4[thumbnailHeight - 1 - i];
                if (numberOfColors >= 5)
                    swapForRotatedSwap5[i] = rotatedSwap5[thumbnailHeight - 1 - i];
                if (numberOfColors >= 6)
                    swapForRotatedSwap6[i] = rotatedSwap6[thumbnailHeight - 1 - i];
            }
            for (i = 0; i < thumbnailHeight; i ++){
                sumOfCurrentRowForCyan[i + thumbnailLocationAfterRotation] = swapForRotatedSwap1[i];
                sumOfCurrentRowForMagenta[i + thumbnailLocationAfterRotation] = swapForRotatedSwap2[i];
                sumOfCurrentRowForYellow[i + thumbnailLocationAfterRotation] = swapForRotatedSwap3[i];
                sumOfCurrentRowForBlack[i + thumbnailLocationAfterRotation] = swapForRotatedSwap4[i];
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
        if (thumbnailFountainWidth >= thumbnailHeight)
            index = 0;
        else
            index = (thumbnailHeight - thumbnailFountainWidth) / 2;
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

            percentageValueForCyan[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForMagenta[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForYellow[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            percentageValueForBlack[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 5)
                percentageValueForSpecialColor1[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
            if (numberOfColors >= 6)
                percentageValueForSpecialColor2[i] /= (accurateZoneWidth * thumbnailFountainHeight * 2.55);
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
        if (numberOfColors >= 5)
            inkValues[10] = specialColor1InkValue_90CW_noFlip;
        else
            inkValues[10] = NULL;
        if (numberOfColors >= 6)
            inkValues[11] = specialColor2InkValue_90CW_noFlip;
        else
            inkValues[11] = NULL;

        inkValues[12] = cyanInkValue_180CW_noFlip;
        inkValues[13] = magentaInkValue_180CW_noFlip;
        inkValues[14] = yellowInkValue_180CW_noFlip;
        inkValues[15] = blackInkValue_180CW_noFlip;
        if (numberOfColors >= 5)
            inkValues[16] = specialColor1InkValue_180CW_noFlip;
        else
            inkValues[16] = NULL;
        if (numberOfColors >= 6)
            inkValues[17] = specialColor2InkValue_180CW_noFlip;
        else
            inkValues[17] = NULL;

        inkValues[18] = cyanInkValue_270CW_noFlip;
        inkValues[19] = magentaInkValue_270CW_noFlip;
        inkValues[20] = yellowInkValue_270CW_noFlip;
        inkValues[21] = blackInkValue_270CW_noFlip;
        if (numberOfColors >= 5)
            inkValues[22] = specialColor1InkValue_270CW_noFlip;
        else
            inkValues[22] = NULL;
        if (numberOfColors >= 6)
            inkValues[23] = specialColor2InkValue_270CW_noFlip;
        else
            inkValues[23] = NULL;

        inkValues[24] = cyanInkValue_180CW_noFlip;
        inkValues[25] = magentaInkValue_180CW_noFlip;
        inkValues[26] = yellowInkValue_180CW_noFlip;
        inkValues[27] = blackInkValue_180CW_noFlip;
        if (numberOfColors >= 5)
            inkValues[28] = specialColor1InkValue_180CW_noFlip;
        else
            inkValues[28] = NULL;
        if (numberOfColors >= 6)
            inkValues[29] = specialColor2InkValue_180CW_noFlip;
        else
            inkValues[29] = NULL;

        inkValues[30] = cyanInkValue_90CW_noFlip;
        inkValues[31] = magentaInkValue_90CW_noFlip;
        inkValues[32] = yellowInkValue_90CW_noFlip;
        inkValues[33] = blackInkValue_90CW_noFlip;
        if (numberOfColors >= 5)
            inkValues[34] = specialColor1InkValue_90CW_noFlip;
        else
            inkValues[34] = NULL;
        if (numberOfColors >= 6)
            inkValues[35] = specialColor2InkValue_90CW_noFlip;
        else
            inkValues[35] = NULL;

        inkValues[36] = cyanInkValue;
        inkValues[37] = magentaInkValue;
        inkValues[38] = yellowInkValue;
        inkValues[39] = blackInkValue;
        if (numberOfColors >= 5)
            inkValues[40] = specialColor1InkValue;
        else
            inkValues[40] = NULL;
        if (numberOfColors >= 6)
            inkValues[41] = specialColor2InkValue;
        else
            inkValues[41] = NULL;

        inkValues[42] = cyanInkValue_270CW_noFlip;
        inkValues[43] = magentaInkValue_270CW_noFlip;
        inkValues[44] = yellowInkValue_270CW_noFlip;
        inkValues[45] = blackInkValue_270CW_noFlip;
        if (numberOfColors >= 5)
            inkValues[46] = specialColor1InkValue_270CW_noFlip;
        else
            inkValues[46] = NULL;
        if (numberOfColors >= 6)
            inkValues[47] = specialColor2InkValue_270CW_noFlip;
        else
            inkValues[47] = NULL;

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
    if (this->contiguous_or_separate == SEPARATE){
        if (direction == BOTTOM2TOP_LEFT2RIGHT ||
            direction == BOTTOM2TOP_RIGHT2LEFT ||
            direction == TOP2BOTTOM_LEFT2RIGHT ||
            direction == TOP2BOTTOM_RIGHT2LEFT)
            emit percentage(5 * image_width);
        else
            emit percentage(5 * image_height);
    }
    else
        if (direction == BOTTOM2TOP_LEFT2RIGHT ||
            direction == BOTTOM2TOP_RIGHT2LEFT ||
            direction == TOP2BOTTOM_LEFT2RIGHT ||
            direction == TOP2BOTTOM_RIGHT2LEFT)
            emit percentage(image_width);
        else
            emit percentage(image_height);
    return 0;
}
int PPFHandler::powerOfTen(int n){
    int i = 0;
    int result = 1;
    for (; i < n; i ++)
        result = result * 10;
    return result;
}
double PPFHandler::dividedByTen(int n){
    double result = 1;
    int i;
    for (i = 0; i < n; i ++)
        result /= 10;
    return result;
}
