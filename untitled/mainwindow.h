#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QScrollBar>
#include <QTimer>
#include <QListWidget>
#include <sys/vfs.h>
#include <dirent.h>
#include <sys/mount.h>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QCursor>
#include "ppfhandler.h"
#include "tiffhandler.h"
#include "buttondriver.h"
#include "batterydriver.h"
#include "filesaver.h"
#include "sstream"
#include "math.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QListWidget>
#include <QDebug>
#include <QList>

#define ZOOMIN 11
#define ALL 10
#define UPPER 7
#define LOWER 8
#define CLEAR 9
#define PORT 1234
#define NUMBER_OF_TOTAL_WIDGET 73
#define NUMBER_OF_INK_PAPER_COMBINATIONS 16
#define MAXIMUM_NUMBER_OF_COLORS 6

#define MAXIMUM_FILE_SIZE 50000000  //maximum file size 50mb

#define MAXIMUM_BATTERY 920
#define MINIMUM_BATTERY 820

#define MAXIMUM_DISPLAY_HEIGHT 430
#define VALUE_START_Y_LOCATION 465
#define VALUE_DISPLAY_HEIGHT 135
#define TOOLBAR_HEIGHT 47
#define FULLSCREEN_WIDTH 800
#define FULLSCREEN_HEIGHT 600

#define NUMBER_OF_WIDGETS_ON_TOOLBAR 8
#define NUMBER_OF_WIDGETS_ON_PARAMETER_SETTING_PANEL 9
#define NUMBER_OF_WIDGETS_ON_DIGIT_INPUT_PANEL 13
#define NUMBER_OF_WIDGETS_ON_1STTAB 22
#define NUMBER_OF_WIDGETS_ON_2NDTAB 16
#define NUMBER_OF_WIDGETS_ON_3RDTAB 19
#define NUMBER_OF_WIDGETS_ON_4THTAB 8

#define HEIDELBER_CD_102_4 1
#define LITHRONE_LS440 2
#define HEIDELBER_CD_102 3
#define NUMBER_OF_MACHINE_MODELS 5

#define INK_KEY_GAP 0.02

#define ROUGH_ADJUSTMENT 1
#define SUBTLE_ADJUSTMENT 2

#define OPENING 1
#define DELETION 2

#define PARAMETER_INK_KEY_QUANTITY 1
#define PARAMETER_FOUNTAIN_WIDTH 2
#define PARAMETER_FOUNTAIN_HEIGHT 3
#define PARAMETER_MAX_INK_VALUE 4
#define PARAMETER_INK_FRACTION 5
#define PARAMETER_TOTAL_COLORS 6
#define PARAMETER_IP_ADDRESS 7

#define WIDGET_ID_OPEN_FILE             1
#define WIDGET_ID_MAKE_CONNECTION       2
#define WIDGET_ID_SAVE_FILE             3
#define WIDGET_ID_DELETE_FILE           4
#define WIDGET_ID_ZOOM_IN               5
#define WIDGET_ID_REVISE_PARAMETER      6
#define WIDGET_ID_SHUT_DOWN             7

#define WIDGET_ID_SHOW_HIDE_TABWIDGET   8
#define WIDGET_ID_ONE_SIDE              9
#define WIDGET_ID_TWO_SIDES             10
#define WIDGET_ID_INK_KEY_QUANTITY      11
#define WIDGET_ID_FOUNTAIN_WIDTH        12
#define WIDGET_ID_FOUNTAIN_HEIGHT       13
#define WIDGET_ID_MAX_INK_VALUE         14
#define WIDGET_ID_INK_FRACTION          15
#define WIDGET_ID_TOTAL_COLORS          16
#define WIDGET_ID_ENTER_PARAMETERS      17
#define WIDGET_ID_INPUT_ONE             18
#define WIDGET_ID_INPUT_TWO             19
#define WIDGET_ID_INPUT_THREE           20
#define WIDGET_ID_INPUT_FOUR            21
#define WIDGET_ID_INPUT_FIVE            22
#define WIDGET_ID_INPUT_SIX             23
#define WIDGET_ID_INPUT_SEVEN           24
#define WIDGET_ID_INPUT_EIGHT           25
#define WIDGET_ID_INPUT_NINE            26
#define WIDGET_ID_INPUT_ZERO            27
#define WIDGET_ID_INPUT_DOT             28
#define WIDGET_ID_DELETE                29
#define WIDGET_ID_ENTER                 30
#define WIDGET_ID_UPPER_SIDE            31
#define WIDGET_ID_LOWER_SIDE            32
#define WIDGET_ID_CYAN                  33
#define WIDGET_ID_MAGENTA               34
#define WIDGET_ID_YELLOW                35
#define WIDGET_ID_BLACK                 36
#define WIDGET_ID_COLOR1                37
#define WIDGET_ID_COLOR2                38
#define WIDGET_ID_DIRECTION1            39
#define WIDGET_ID_DIRECTION2            40
#define WIDGET_ID_DIRECTION3            41
#define WIDGET_ID_DIRECTION4            42
#define WIDGET_ID_DIRECTION5            43
#define WIDGET_ID_DIRECTION6            44
#define WIDGET_ID_DIRECTION7            45
#define WIDGET_ID_DIRECTION8            46
#define WIDGET_ID_LAST_INK_ZONE         47
#define WIDGET_ID_NEXT_INK_ZONE         48
#define WIDGET_ID_INCREASE_CYAN         49
#define WIDGET_ID_DECREASE_CYAN         50
#define WIDGET_ID_INCREASE_MAGENTA      51
#define WIDGET_ID_DECREASE_MAGENTA      52
#define WIDGET_ID_INCREASE_YELLOW       53
#define WIDGET_ID_DECREASE_YELLOW       54
#define WIDGET_ID_INCREASE_BLACK        55
#define WIDGET_ID_DECREASE_BLACK        56
#define WIDGET_ID_INCREASE_COLOR1       57
#define WIDGET_ID_DECREASE_COLOR1       58
#define WIDGET_ID_INCREASE_COLOR2       59
#define WIDGET_ID_DECREASE_COLOR2       60
#define WIDGET_ID_ADJUST_ROLLER_SPEED   61
#define WIDGET_ID_ADJUST_BASIC_INK      62
#define WIDGET_ID_ADJUST_SINGLE_INK     63
#define WIDGET_ID_ROUGH_ADJUST          64
#define WIDGET_ID_SUBTLE_ADJUST         65
#define WIDGET_ID_INK1                  66
#define WIDGET_ID_INK2                  67
#define WIDGET_ID_INK3                  68
#define WIDGET_ID_INK4                  69
#define WIDGET_ID_PAPER1                70
#define WIDGET_ID_PAPER2                71
#define WIDGET_ID_PAPER3                72
#define WIDGET_ID_PAPER4                73

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct curveUpdateInfo{
        int color;
        int indexOfPoint;
        signed int increasedQuantity;
    };
    QList<struct curveUpdateInfo> curveCollection;

    explicit MainWindow(QWidget *parent = 0);
    void processData(QByteArray& array);
    void deleteContentInRemoteFolder();
    void showStatusWidget();
    void showFilesAndFoldersFor(int);
    void showCurrentInkZone();
    void collectMemoryGarbage();
    int getAdjustedInkValue(int, int, int);
    void selectFileToDelete();
    void manipulateImageFile();
    void writeInkInfoToFile();
    void smoothCurve(struct curveUpdateInfo);
    void changeBasicInkQuantity(int, bool);
    void changeWidgetVisualEffect(int, int);
    bool isOtherInstructionInProcess();
    void addDigit(int);
    void changeInkValue(int, bool);
    void changeRollerSpeed(int, bool);
    void calculateInkRatio();
    void changeDirection(int, bool, int);
    void quickSort(short *, int, int);
    int partition(short *, int, int);

    void cleanUpAfterFileManipulationFailed(QString);
    ~MainWindow();
signals:
    void status(int);
    void percentage(qint64);
    void progressRange(qint64);
    void closeMessage();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void selectMachineModel();
    void cancelMachineModelSelection();
    void openFile();
    void receiveFile();
    void changeConnectionStatus();
    void deleteFile();
    void shutDownLinux();
    void selectFile();
    void cancelSelect();
    void setSelectedFileIndex(QListWidgetItem*);
    void statusHandler(int);
    void eliminateStatusWidget();
    void setProgressBar(qint64);
    void updateProgressBar(qint64);
    void saveInkValue();
    void makeConnection();
    void connectServer();
    void showCyanComponent();
    void showMagentaComponent();
    void showYellowComponent();
    void showBlackComponent();
    void showColor1Component();
    void showColor2Component();
    void showLastInkZone();
    void showNextInkZone();
    void increaseCyan();
    void increaseMagenta();
    void increaseYellow();
    void increaseBlack();
    void decreaseCyan();
    void decreaseMagenta();
    void decreaseYellow();
    void decreaseBlack();
    void increaseColor1();
    void decreaseColor1();
    void increaseColor2();
    void decreaseColor2();

    void zoomInInkValue();
    void showUpperSide();
    void showDownSide();
    void switchGroupBox();
    void setToOneSide();
    void setToTwoSides();
    void inputDot();
    void inputEnter();
    void inputNine();
    void inputEight();
    void inputSeven();
    void inputSix();
    void inputFive();
    void inputFour();
    void inputThree();
    void inputTwo();
    void inputOne();
    void inputZero();
    void inputDelete();
    int powerOfTen(int);
    double dividedByTen(int);
    void setParameter_inkKeyValues();
    void setParameter_fountainWidth();
    void setParameter_plateHeight();
    void setParameter_maxInkValue();
    void setParameter_inkFraction();
    void setParameter_totalColors();
    void reviseParameters();
    void enterParameters();

    void changeToNextTabWidgetIndex();
    void changeToLastTabWidgetIndex();
    void physicalSelectButtonPressed();
    void physicalCancelButtonPressed();
    void encoder_turnedLeft();
    void encoder_turnedRight();

    void changeBatteryPercentage(int);
    void changeChargingStatus(bool);

    void direction1();
    void direction2();
    void direction3();
    void direction4();
    void direction5();
    void direction6();
    void direction7();
    void direction8();

    void setRoughAdjustment();
    void setSubtleAdjustment();
    void setToBasicAdjustment();
    void setToSingleAdjustment();
    void setToRollerSpeedAdjustment();

    void setToInk1();
    void setToInk2();
    void setToInk3();
    void setToInk4();

    void setToPaper1();
    void setToPaper2();
    void setToPaper3();
    void setToPaper4();

    void show_hideTabWidget();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QString upper_fileName;
    QString lower_fileName;
    PPFHandler *ph1;
    PPFHandler *ph2;
    TIFFHandler *th1;
    TIFFHandler *th2;

    QStringList entryNamesInRemoteImageFolder;

    bool isTabWidgetVisible;
    int maximum_display_width;

    int paperType;
    int inkType;
    float ink_thickness[8];

    int totalColors;
    int numberOfColorsInPPF1;
    int numberOfColorsInPPF2;
    int numberOfColorsInTIF1;
    int numberOfColorsInTIF2;
    int *inkValues[8];

    QMessageBox *messageBox;
    QFont font;

    BYTE *zoomedInImage;

    QList<QList<short> > increasedInkQuantity;
    QList<QList<short> > inkCurve;
    QList<QList<short> > changedPoints;

    int adjustmentQuantity;

    QTcpSocket *socket;
    bool isSocketConnected;
    qint64 receivedFileSize;
    QString serverAddress;
    qint64 numOfCharactersReceived;
    int machineModel;
    int inkKeySteps;
    int numberOfSides;
    int upperFileFormat;
    int lowerFileFormat;
    int previousADCValue;
    bool isUpperFileOpened;
    bool isLowerFileOpened;
    bool toRemoveAllFiles;
    int maxInkValue;
    int numOfPagesOpened;
    int currentPage;
    int currentColorShowing;
    int inkKeyQuantity;
    float inkFountainWidth;
    float printingPlateHeight;
    int upper_inkFountainWidthInPixel;
    int lower_inkFountainWidthInPixel;
    int inkFraction;
    bool hasDotEntered;
    int digitsOfFractions;
    double inputValue;
    short whichParameterToSet;
    short paintEventId;
    short currentInkZone;

    int fountainStartXLocation;
    int fountainStartYLocation;
    int inkZoneWidth;

    QListWidget *fileList;
    bool isFileListInitialized;

    int currentBattery;
    int selectedButton;
    int previouslySelectedButton;
    int currentFileIndex;
    int selectedButtonBeforeDigitalInput;
    int tabIndex;
    bool isManipulatingImageFile;
    bool isIncreasedInkQuantityValid;
    bool isEnteringDigitalInput;
    bool isRevisingAllParameters;
    bool isSelectingFile;
    bool isDeletingFile;
    bool isEstablishingDeletion;
    bool isWaitingForUserResponse;
    bool isDecidingToStartNewPrintingJobOrNot;
    bool isShutingDownDevice;
    bool isStatusWidgetVisible;
    bool isCommunicating;
    bool isFileFromUSB;
    bool isFileFromREMOTE;

    bool isTransmittingFolder;

    bool isBasicAdjustment;
    bool isSingleAdjustment;
    bool isRollerSpeedAdjustment;

    bool isMemoryForColorOffsetValid;

    int numOfAvailableContents;
    int numOfContentsFromUSB;
    int numOfContentsFromREMOTE;

    int numOfFilesReceived;
    int numOfFilesToBeTransmit;

    signed int basicInkValue[8];
    int inkRollerSpeed[8];
    float inkRatio[8];  //based upon roller speed, ink fountain width, plate height and etc.

    int previousXCoord;
    int previousYCoord;
    int currentXCoord;
    int currentYCoord;
    int upperLeftImageXCoord;
    int upperLeftImageYCoord;

    int shrinkedImageWidth;
    int shrinkedImageHeight;
    float shrinkedRatio;

    int fdForADC;
    int numOfADCValueRead;

    int rotateAngle_upper;
    bool horizontallyFlipped_upper;
    int rotateAngle_lower;
    bool horizontallyFlipped_lower;

    QFile files[6];
    int fileSizes[6];
    qint64 blockSize;
    Qt::WindowFlags flags;
};

#endif // MAINWINDOW_H
