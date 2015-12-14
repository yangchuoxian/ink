#include "filesaver.h"

fileSaver::fileSaver(int n, QString u, QString l, int m, int f, int k)
{
    numOfPages = n;
    machineModel = m;

    upper_fileName = u;
    lower_fileName = l;
    inkKeyQuantity = k;
    inkFraction = f;
    inkValues = new int*[8];
    for (int i = 0; i < 8; i ++)
        inkValues[i] = new int[inkKeyQuantity];
}
fileSaver::~fileSaver()
{
    for (int i = 0; i < 8; i ++)
        delete []inkValues[i];
    delete []inkValues;
}
void fileSaver::saveGeneralFile()
{
    QString saveFilePath(UDISK_LOCATION);
    saveFilePath.append(upper_fileName.toAscii());
    if (numOfPages == 2)
        saveFilePath.append(lower_fileName.toAscii());
    saveFilePath.remove(".ppf");
    saveFilePath.remove(".tif");
    saveFilePath.append(".InkValue.txt");
    QFile saveFile(saveFilePath);
    saveFile.open(QIODevice::WriteOnly);

    QDateTime *now = new QDateTime();
    saveFile.write("Current printing job ------ ");
    saveFile.write(now->currentDateTime().toString().toAscii());
    saveFile.write("\n");

    QString exportFilePath(UDISK_LOCATION);
    exportFilePath.append(upper_fileName.toAscii());
    if (numOfPages == 2)
        exportFilePath.append(lower_fileName.toAscii());
    exportFilePath.append(".export.txt");
    QFile exportFile(exportFilePath);
    exportFile.open(QIODevice::WriteOnly);

    QString temp, tempFraction;

    if (numOfPages == 1){
        upper_fileName.remove(".ppf", Qt::CaseInsensitive);
        upper_fileName.remove(".tif", Qt::CaseInsensitive);
        upper_fileName.remove(".cyan", Qt::CaseInsensitive);
        upper_fileName.remove(".magenta", Qt::CaseInsensitive);
        upper_fileName.remove(".yellow", Qt::CaseInsensitive);
        upper_fileName.remove(".black", Qt::CaseInsensitive);

        saveFile.write("Image file name      ------ ");
        saveFile.write(upper_fileName.toAscii());
        saveFile.write("\n");
        saveFile.write("            upper image file ink zone value:\n");
        saveFile.write("=======================================================\n");
        saveFile.write("               C          M          Y          K      \n");
        saveFile.write("ink zone\n");
        saveFile.write("--------------------------------------------------------\n");

        for (int i = 0; i < inkKeyQuantity; i ++){
            qApp->processEvents();

            temp.setNum(i + 1);                     //ink zone #
            saveFile.write(temp.toAscii());
            saveFile.write("            ");
            for (int j = 0; j < 4; j ++){
                temp.setNum(inkValues[j][i] / inkFraction);      //cyan ink value
                tempFraction.setNum(inkValues[j][i] % inkFraction);
                temp.append(".").append(tempFraction);
                saveFile.write(temp.toAscii());
                saveFile.write("        ");
            }
            saveFile.write("\n");
            if (i < (inkKeyQuantity - 1))
                saveFile.write("-------------------------------------------------------\n");
            else
                saveFile.write("=======================================================\n");
        }
        exportFile.write("upper image file: ");
        exportFile.write(upper_fileName.toAscii());
        exportFile.write("\n");
        for (int j = 0; j < 4; j ++){
            switch(j + 1){
            case CYAN:
                exportFile.write("C\n");
                break;
            case MAGENTA:
                exportFile.write("M\n");
                break;
            case YELLOW:
                exportFile.write("Y\n");
                break;
            case BLACK:
                exportFile.write("K\n");
                break;
            }
            for (int i = 0; i < inkKeyQuantity; i ++){
                temp.setNum(inkValues[j][i]);
                exportFile.write(temp.toAscii());
                exportFile.write("\n");
            }
        }
    }
    if (numOfPages == 2){
        saveFile.write("Image file name      ------ ");
        saveFile.write(lower_fileName.toAscii());
        saveFile.write("\n");
        saveFile.write("            lower image file ink zone value:\n");
        saveFile.write("=======================================================\n");
        saveFile.write("            C           M           Y           K      \n");
        saveFile.write("ink zone\n");
        saveFile.write("--------------------------------------------------------\n");
        for (int i = 0; i < inkKeyQuantity; i ++){
            qApp->processEvents();

            temp.setNum(i + 1);                     //ink zone #
            saveFile.write(temp.toAscii());
            saveFile.write("            ");

            for (int j = 4; j < 8; j ++){
                temp.setNum(inkValues[j][i] / inkFraction);      //cyan ink value
                tempFraction.setNum(inkValues[j][i] % inkFraction);
                temp.append(".").append(tempFraction);
                saveFile.write(temp.toAscii());
                saveFile.write("        ");
            }
            saveFile.write("      \n");
            if (i < (inkKeyQuantity - 1))
                saveFile.write("-------------------------------------------------------\n");
            else
                saveFile.write("=======================================================\n");
        }

        exportFile.write("lower image file: ");
        exportFile.write(lower_fileName.toAscii());
        exportFile.write("\n");
        for (int j = 0; j < 4; j ++){
            switch(j + 1){
            case CYAN:
                exportFile.write("C\n");
                break;
            case MAGENTA:
                exportFile.write("M\n");
                break;
            case YELLOW:
                exportFile.write("Y\n");
                break;
            case BLACK:
                exportFile.write("K\n");
                break;
            }
            for (int i = 0; i < inkKeyQuantity; i ++){
                temp.setNum(inkValues[j][i]);      //cyan ink value
                exportFile.write(temp.toAscii());
                exportFile.write("\n");
            }
        }
    }

    saveFile.close();
    exportFile.close();
}
void fileSaver::saveAsPPF(int format, void *fh, QString fileName)
{
    QString temp, num;

    QString saveFilePath(UDISK_LOCATION);
    saveFilePath.append(fileName.toAscii());
    saveFilePath.remove(".ppf", Qt::CaseInsensitive);
    saveFilePath.remove(".tif", Qt::CaseInsensitive);
    saveFilePath.append(".ppf");
    QFile ppf(saveFilePath);
    ppf.open(QIODevice::WriteOnly);

    ppf.write("%!PS-Adobe-3.0\n");
    ppf.write("%%CIP3-File Version 2.1\n");

    temp = "/CIP3AdmJobName (";
    temp.append(fileName);
    temp.append(") def\n");
    ppf.write(temp.toAscii());

    ppf.write("/CIP3AdmSheetName (Sheet 1) def\n");

    if (format == PPF_FORMAT){
        PPFHandler *ph = (PPFHandler *)fh;

        temp = "/CIP3AdmPSExtent [";
        float width = (float)ph->image_width / ph->xResolution;
        width *= 2.54;
        float height = (float)ph->image_height / ph->yResolution;
        height *= 2.54;
        temp.append(num.setNum(width)).append(" cm ");
        temp.append(num.setNum(height)).append(" cm] def\n");
        ppf.write(temp.toAscii());

        ppf.write("/CIP3TransferFilmCurveData  [0.000 0.000 1.000 1.000 ] def\n");
        ppf.write("/CIP3TransferPlateCurveData [0.000 0.000 1.000 1.000 ] def\n");

        ppf.write("CIP3BeginFront\n");
        ppf.write("/CIP3AdmSeparationNames [ (Cyan) (Magenta) (Yellow) (Black) ] def\n");
        ppf.write("CIP3BeginPreviewImage\n");

        for (int color = 0; color < 4; color ++){
            ppf.write("CIP3BeginSeparation\n");
            ppf.write("/CIP3PreviewImageComponents 1 def\n");

            temp = "/CIP3PreviewImageWidth ";
            temp.append(num.setNum(ph->thumbnailWidth)).append(" def\n");
            ppf.write(temp.toAscii());

            temp = "/CIP3PreviewImageHeight ";
            temp.append(num.setNum(ph->thumbnailHeight)).append(" def\n");
            ppf.write(temp.toAscii());

            temp = "/CIP3PreviewImageMatrix [";
            switch(ph->direction){
            case LEFT2RIGHT_BOTTOM2TOP:
                temp.append(num.setNum(ph->thumbnailWidth)).append(" 0 0 ");
                temp.append(num.setNum(ph->thumbnailHeight)).append(" 0 0]\n");
                break;
            case LEFT2RIGHT_TOP2BOTTOM:
                temp.append(num.setNum(ph->thumbnailWidth)).append(" 0 0 ");
                temp.append(num.setNum(-(ph->thumbnailHeight))).append(" 0 ");
                temp.append(num.setNum(ph->thumbnailHeight)).append("]\n");
                break;
            case RIGHT2LEFT_BOTTOM2TOP:
                temp.append(num.setNum(-(ph->thumbnailWidth))).append(" 0 0 ");
                temp.append(num.setNum(ph->thumbnailHeight)).append(" ");
                temp.append(num.setNum(ph->thumbnailWidth)).append(" 0]\n");
                break;
            case RIGHT2LEFT_TOP2BOTTOM:
                temp.append(num.setNum(-(ph->thumbnailWidth))).append(" 0 0 ");
                temp.append(num.setNum(-(ph->thumbnailHeight))).append(" ");
                temp.append(num.setNum(ph->thumbnailWidth)).append(" ");
                temp.append(num.setNum(ph->thumbnailHeight)).append("]\n");
                break;
            case BOTTOM2TOP_LEFT2RIGHT:
                temp.append("0 ").append(num.setNum(ph->thumbnailHeight));
                temp.append(" ").append(num.setNum(ph->thumbnailWidth)).append(" 0 0 0]\n");
                break;
            case TOP2BOTTOM_LEFT2RIGHT:
                temp.append("0 ").append(num.setNum(ph->thumbnailHeight)).append(" ");
                temp.append(num.setNum(-(ph->thumbnailWidth))).append(" 0 ");
                temp.append(num.setNum(ph->thumbnailHeight)).append(" 0]\n");
            case BOTTOM2TOP_RIGHT2LEFT:
                temp.append("0 ").append(num.setNum(-(ph->thumbnailHeight))).append(" ");
                temp.append(num.setNum(ph->thumbnailWidth)).append(" 0 0 ");
                temp.append(num.setNum(ph->thumbnailWidth)).append("]\n");
                break;
            case TOP2BOTTOM_RIGHT2LEFT:
                temp.append("0 ").append(num.setNum(-(ph->thumbnailHeight))).append(" ");
                temp.append(num.setNum(-(ph->thumbnailWidth))).append(" 0 ");
                temp.append(num.setNum(ph->thumbnailHeight)).append(" ");
                temp.append(num.setNum(ph->thumbnailWidth)).append("]\n");
                break;
            }
            ppf.write(temp.toAscii());

            float xRes = ((float)ph->thumbnailWidth) / ((float)width / 2.54);
            xRes = (int)(xRes * 10) / 10.0;
            float yRes = ((float)ph->thumbnailHeight) / ((float)width / 2.54);
            yRes = (int)(yRes * 10) / 10.0;

            temp = "/CIP3PreviewImageResolution [";
            temp.append(num.setNum(xRes)).append(" ");
            temp.append(num.setNum(yRes)).append("] def\n");
            ppf.write(temp.toAscii());

            ppf.write("/CIP3PreviewImageBitsPerComp 8 def\n");
            ppf.write("/CIP3PreviewImageCompression /None def\n");
            ppf.write("/CIP3PreviewImageEncoding /ASCIIHexDecode def\n");
            ppf.write("CIP3PreviewImage\r\n");

            QByteArray colorStr;
            int w = ph->thumbnailWidth;
            int h = ph->thumbnailHeight;
            for (int i = 0; i < h; i ++){
                qApp->processEvents();
                for (int j = 0; j < w; j ++){
                    colorStr.append(255 - ph->colorValues[color][i * w + j]);
                }
                ppf.write(colorStr.toHex());
                ppf.write("\n");
                colorStr.clear();
            }

            ppf.write("CIP3EndSeparation\n");
        }
        ppf.write("CIP3EndPreviewImage\n");
        ppf.write("CIP3EndFront\n");
        ppf.write("CIP3EndSheet\n");
        ppf.write("%%CIP3EndOfFile\n");
    }
    else if (format == TIFF_FORMAT){
        TIFFHandler *th = (TIFFHandler *)fh;

        temp = "/CIP3AdmPSExtent [";
        float width = (float)th->image_width / th->x_resolution;
        float height = (float)th->image_length / th->y_resolution;
        if (th->resolutionUnit == INCH){
            width *= 2.54;
            height *= 2.54;
        }
        temp.append(num.setNum(width)).append(" cm ");
        temp.append(num.setNum(height)).append(" cm] def\n");
        ppf.write(temp.toAscii());

        ppf.write("/CIP3TransferFilmCurveData  [0.000 0.000 1.000 1.000 ] def\n");
        ppf.write("/CIP3TransferPlateCurveData [0.000 0.000 1.000 1.000 ] def\n");

        ppf.write("CIP3BeginFront\n");
        ppf.write("/CIP3AdmSeparationNames [ (Cyan) (Magenta) (Yellow) (Black) ] def\n");
        ppf.write("CIP3BeginPreviewImage\n");

        for (int color = 0; color < 4; color ++){
            ppf.write("CIP3BeginSeparation\n");
            ppf.write("/CIP3PreviewImageComponents 1 def\n");

            temp = "/CIP3PreviewImageWidth ";
            temp.append(num.setNum(th->thumbnailWidth)).append(" def\n");
            ppf.write(temp.toAscii());

            temp = "/CIP3PreviewImageHeight ";
            temp.append(num.setNum(th->thumbnailHeight)).append(" def\n");
            ppf.write(temp.toAscii());

            temp = "/CIP3PreviewImageMatrix [";

            temp.append(num.setNum(th->thumbnailWidth)).append(" 0 0 ");
            temp.append(num.setNum(-(th->thumbnailHeight))).append(" 0 ");
            temp.append(num.setNum(th->thumbnailHeight)).append("]\n");

            ppf.write(temp.toAscii());

            float xRes = ((float)th->thumbnailWidth) / ((float)width / 2.54);
            xRes = (int)(xRes * 10) / 10.0;
            float yRes = ((float)th->thumbnailHeight) / ((float)width / 2.54);
            yRes = (int)(yRes * 10) / 10.0;

            temp = "/CIP3PreviewImageResolution [";
            temp.append(num.setNum(xRes)).append(" ");
            temp.append(num.setNum(yRes)).append("] def\n");
            ppf.write(temp.toAscii());

            ppf.write("/CIP3PreviewImageBitsPerComp 8 def\n");
            ppf.write("/CIP3PreviewImageCompression /None def\n");
            ppf.write("/CIP3PreviewImageEncoding /ASCIIHexDecode def\n");
            ppf.write("CIP3PreviewImage\r\n");

            QByteArray colorStr;
            int w = th->thumbnailWidth;
            int h = th->thumbnailHeight;
            for (int i = 0; i < h; i ++){
                qApp->processEvents();
                for (int j = 0; j < w; j ++){
                    colorStr.append(255 - th->colorValues[color][i * w + j]);
                }
                ppf.write(colorStr.toHex());
                ppf.write("\n");
                colorStr.clear();
            }

            ppf.write("CIP3EndSeparation\n");
        }
        ppf.write("CIP3EndPreviewImage\n");
        ppf.write("CIP3EndFront\n");
        ppf.write("CIP3EndSheet\n");
        ppf.write("%%CIP3EndOfFile\n");
    }

    ppf.close();
}
