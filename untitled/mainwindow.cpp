#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    flags = Qt::Window;
    flags |= Qt::CustomizeWindowHint;
    setWindowFlags(flags);
    currentInkZone = 0;
    numOfCharactersReceived = 0;
    socket = new QTcpSocket(this);
    blockSize = 0;
    isUpperFileOpened = false;
    isLowerFileOpened = false;
    hasDotEntered = false;
    inkKeySteps = 0;
    numOfPagesOpened = 0;
    currentPage = 0;
    currentColorShowing = 0;
    inkKeyQuantity = 0;
    inkFountainWidth = 0;
    printingPlateHeight = 0;
    upper_inkFountainWidthInPixel = 0;
    lower_inkFountainWidthInPixel = 0;
    inkFraction = 0;
    inputValue = 0;
    toRemoveAllFiles = false;
    machineModel = 0;
    for (int i = 0; i < 8; i ++){
        basicInkValue[i] = 0;
        inkRollerSpeed[i] = 30;     //all the ink roller speed are set to 30 by default
        inkRatio[i] = 1.0;
    }

    numOfADCValueRead = 0;
    currentBattery = 0;

    digitsOfFractions = -1;
    whichParameterToSet = 0;
    paintEventId = 0;
    numberOfColorsInPPF1 = 0;
    numberOfColorsInPPF2 = 0;

    ui->setupUi(this);

    ui->widget_deleteFileList->setVisible(false);
    ui->widget_status->setVisible(false);
    ui->widget_fileList->setVisible(false);
    ui->widget_machineModel->setVisible(false);
    ui->widget_ip->setVisible(false);

    ui->radioButton_oneSide->setChecked(true);
    numberOfSides = 1;

    adjustmentQuantity = ROUGH_ADJUSTMENT;
    selectedButton = 0;
    tabIndex = 0;
    isManipulatingImageFile = false;
    isIncreasedInkQuantityValid = false;
    isEnteringDigitalInput = false;
    isSelectingFile = false;
    isDeletingFile = false;
    isEstablishingDeletion = false;
    isWaitingForUserResponse = false;
    isRevisingAllParameters = false;
    isDecidingToStartNewPrintingJobOrNot = false;
    isShutingDownDevice = false;
    isStatusWidgetVisible = false;
    isCommunicating = false;
    isSocketConnected = false;
    isBasicAdjustment = false;
    isSingleAdjustment = true;
    isRollerSpeedAdjustment = false;

    ui->pushButton_roughAdjust->setDown(true);
    ui->pushButton_adjustSingleInk->setEnabled(false);
    ui->pushButton_adjustBasicInk->setEnabled(true);
    ui->pushButton_adjustRollerSpeed->setEnabled(true);

    numOfAvailableContents = 0;
    numOfContentsFromUSB = 0;
    numOfContentsFromREMOTE = 0;

    previousADCValue = 0;

    isFileFromUSB = false;
    isFileFromREMOTE = false;
    isFileListInitialized = false;

    isMemoryForColorOffsetValid = false;

    inkType = 1;
    paperType = 1;
    for (int i = 0; i < 8; i ++){
        ink_thickness[i] = 0.001;
    }

    ui->verticalSlider_cyanInkThickness->setValue(10);
    ui->label_cyanInkThickness->setText("33");
    ui->verticalSlider_magentaInkThickness->setValue(10);
    ui->label_magentaInkThickness->setText("40");
    ui->verticalSlider_yellowInkThickness->setValue(10);
    ui->label_yellowInkThickness->setText("40");
    ui->verticalSlider_blackInkThickness->setValue(10);
    ui->label_blackInkThickness->setText("25");

    totalColors = 4;

    previousXCoord = 0;
    previousYCoord = 0;
    currentXCoord = 0;
    currentYCoord = 0;
    upperLeftImageXCoord = 0;
    upperLeftImageYCoord = 0;

    rotateAngle_upper = 0;
    horizontallyFlipped_upper = false;
    rotateAngle_lower = 0;
    horizontallyFlipped_lower = false;

    fileName.clear();

    ButtonDriver *keys = new ButtonDriver();
    connect(keys, SIGNAL(buttonNextPage_pressed()), this, SLOT(changeToNextTabWidgetIndex()));
    connect(keys, SIGNAL(buttonLastPage_pressed()), this, SLOT(changeToLastTabWidgetIndex()));
    connect(keys, SIGNAL(buttonYes_pressed()), this, SLOT(physicalSelectButtonPressed()));
    connect(keys, SIGNAL(buttonNo_pressed()), this, SLOT(physicalCancelButtonPressed()));
    connect(keys, SIGNAL(encoder_turnLeft()), this, SLOT(encoder_turnedLeft()));
    connect(keys, SIGNAL(encoder_turnRight()), this, SLOT(encoder_turnedRight()));
    keys->start();

    BatteryDriver *battery = new BatteryDriver();
    connect(battery, SIGNAL(batteryPercentage(int)), this, SLOT(changeBatteryPercentage(int)));
    connect(battery, SIGNAL(chargingStatus(bool)), this, SLOT(changeChargingStatus(bool)));
    battery->start();

    FILE *fileOfMachineModelNumber = fopen("/opt/PDA/bin/machineModel", "rb");
    if (fileOfMachineModelNumber == NULL){
        machineModel = 0;
    }
    else{
        machineModel = fgetc(fileOfMachineModelNumber);
        fclose(fileOfMachineModelNumber);
    }

    FILE *configFile = NULL;
    int j, k, l, size;
    switch(machineModel)
    {
    case 0:
        configFile = fopen("/opt/PDA/bin/ink0.configure", "rb");
        break;
    case 1:
        configFile = fopen("/opt/PDA/bin/ink1.configure", "rb");
        break;
    case 2:
        configFile = fopen("/opt/PDA/bin/ink2.configure", "rb");
        break;
    case 3:
        configFile = fopen("/opt/PDA/bin/ink3.configure", "rb");
        break;
    case 4:
        configFile = fopen("/opt/PDA/bin/ink4.configure", "rb");
        break;
    }

    if (configFile == NULL){
        ui->radioButton_Ink1->setChecked(true);
        ui->radioButton_paper1->setChecked(true);
    }
    else{
        totalColors = fgetc(configFile);
        if (totalColors <= 4){
            ui->color1->setEnabled(false);
            ui->color2->setEnabled(false);
            ui->pushButton_increaseColor1->setEnabled(false);
            ui->pushButton_decreaseColor1->setEnabled(false);
            ui->pushButton_increaseColor2->setEnabled(false);
            ui->pushButton_decreaseColor2->setEnabled(false);
            ui->horizontalSlider_color1InkValue->setEnabled(false);
            ui->horizontalSlider_color2InkValue->setEnabled(false);
        }
        else if (totalColors == 5){
            ui->color1->setEnabled(true);
            ui->color2->setEnabled(false);
            ui->pushButton_increaseColor1->setEnabled(true);
            ui->pushButton_decreaseColor1->setEnabled(true);
            ui->pushButton_increaseColor2->setEnabled(false);
            ui->pushButton_decreaseColor2->setEnabled(false);
            ui->horizontalSlider_color1InkValue->setEnabled(true);
            ui->horizontalSlider_color2InkValue->setEnabled(false);
        }
        else if (totalColors == 6){
            ui->color1->setEnabled(true);
            ui->color2->setEnabled(true);
            ui->pushButton_increaseColor1->setEnabled(true);
            ui->pushButton_decreaseColor1->setEnabled(true);
            ui->pushButton_increaseColor2->setEnabled(true);
            ui->pushButton_decreaseColor2->setEnabled(true);
            ui->horizontalSlider_color1InkValue->setEnabled(true);
            ui->horizontalSlider_color2InkValue->setEnabled(true);
        }
        inkType = fgetc(configFile);
        paperType = fgetc(configFile);
        numberOfSides = fgetc(configFile);
        if (numberOfSides == 1)
            ui->radioButton_oneSide->setChecked(true);
        else if (numberOfSides == 2)
            ui->radioButton_twoSides->setChecked(true);
        switch(inkType){
        case 1:
            ui->radioButton_Ink1->setChecked(true);
            break;
        case 2:
            ui->radioButton_Ink2->setChecked(true);
            break;
        case 3:
            ui->radioButton_Ink3->setChecked(true);
            break;
        case 4:
            ui->radioButton_Ink4->setChecked(true);
            break;
        }

        switch(paperType){
        case 1:
            //高光涂料纸
            if (numberOfSides == 1){
                ink_thickness[0] = 0.001;       //cyan
                ink_thickness[1] = 0.001;       //magenta
                ink_thickness[2] = 0.001;       //yellow
                ink_thickness[3] = 0.001;       //black
                ink_thickness[4] = 0.001;       //special color1
                ink_thickness[5] = 0.001;       //special color2
            }
            else{
                ink_thickness[0] = 0.001;       //upper cyan
                ink_thickness[1] = 0.001;       //upper magenta
                ink_thickness[2] = 0.001;       //upper yellow
                ink_thickness[3] = 0.001;       //upper black

                ink_thickness[4] = 0.001;       //lower cyan
                ink_thickness[5] = 0.001;       //lower magenta
                ink_thickness[6] = 0.001;       //lower yellow
                ink_thickness[7] = 0.001;       //lower black
            }
            ui->verticalSlider_cyanInkThickness->setValue(10);
            ui->label_cyanInkThickness->setText("33");
            ui->verticalSlider_magentaInkThickness->setValue(10);
            ui->label_magentaInkThickness->setText("40");
            ui->verticalSlider_yellowInkThickness->setValue(10);
            ui->label_yellowInkThickness->setText("40");
            ui->verticalSlider_blackInkThickness->setValue(10);
            ui->label_blackInkThickness->setText("25");

            ui->radioButton_paper1->setChecked(true);
            break;
        case 2:
            //哑光涂料纸
            if (numberOfSides == 1){
                ink_thickness[0] = 0.0014;      //cyan
                ink_thickness[1] = 0.0013;      //magenta
                ink_thickness[2] = 0.0012;      //yellow
                ink_thickness[3] = 0.002;       //black
                ink_thickness[4] = 0.002;       //special color1
                ink_thickness[5] = 0.002;       //special color2
            }
            else{
                ink_thickness[0] = 0.0014;      //upper cyan
                ink_thickness[1] = 0.0013;      //upper magenta
                ink_thickness[2] = 0.0012;      //upper yellow
                ink_thickness[3] = 0.002;       //upper black

                ink_thickness[4] = 0.0014;      //lower cyan
                ink_thickness[5] = 0.0013;      //lower magenta
                ink_thickness[6] = 0.0012;      //lower yellow
                ink_thickness[7] = 0.002;       //lower black
            }
            ui->verticalSlider_cyanInkThickness->setValue(14);
            ui->label_cyanInkThickness->setText("46");
            ui->verticalSlider_magentaInkThickness->setValue(13);
            ui->label_magentaInkThickness->setText("52");
            ui->verticalSlider_yellowInkThickness->setValue(12);
            ui->label_yellowInkThickness->setText("48");
            ui->verticalSlider_blackInkThickness->setValue(20);
            ui->label_blackInkThickness->setText("50");

            ui->radioButton_paper2->setChecked(true);
            break;
        case 3:
            //非涂料纸
            if (numberOfSides == 1){
                ink_thickness[0] = 0.0023;       //cyan
                ink_thickness[1] = 0.0018;       //magenta
                ink_thickness[2] = 0.0017;       //yellow
                ink_thickness[3] = 0.0032;       //black
                ink_thickness[4] = 0.0032;       //special color1
                ink_thickness[5] = 0.0032;       //special color2
            }
            else {
                ink_thickness[0] = 0.0023;       //upper cyan
                ink_thickness[1] = 0.0018;       //upper magenta
                ink_thickness[2] = 0.0017;       //upper yellow
                ink_thickness[3] = 0.0032;       //upper black

                ink_thickness[4] = 0.0023;       //lower cyan
                ink_thickness[5] = 0.0018;       //lower magenta
                ink_thickness[6] = 0.0017;       //lower yellow
                ink_thickness[7] = 0.0032;       //lower black
            }
            ui->verticalSlider_cyanInkThickness->setValue(23);
            ui->label_cyanInkThickness->setText("76");
            ui->verticalSlider_magentaInkThickness->setValue(18);
            ui->label_magentaInkThickness->setText("72");
            ui->verticalSlider_yellowInkThickness->setValue(17);
            ui->label_yellowInkThickness->setText("68");
            ui->verticalSlider_blackInkThickness->setValue(32);
            ui->label_blackInkThickness->setText("80");

            ui->radioButton_paper3->setChecked(true);
            break;
        case 4:
            //新闻纸
            if (numberOfSides == 1){
                ink_thickness[0] = 0.003;       //cyan
                ink_thickness[1] = 0.0025;      //magenta
                ink_thickness[2] = 0.0025;      //yellow
                ink_thickness[3] = 0.004;       //black
                ink_thickness[4] = 0.004;       //special color1
                ink_thickness[5] = 0.004;       //special color2
            }
            else {
                ink_thickness[0] = 0.003;       //upper cyan
                ink_thickness[1] = 0.0025;      //upper magenta
                ink_thickness[2] = 0.0025;      //upper yellow
                ink_thickness[3] = 0.004;       //upper black

                ink_thickness[4] = 0.003;       //lower cyan
                ink_thickness[5] = 0.0025;      //lower magenta
                ink_thickness[6] = 0.0025;      //lower yellow
                ink_thickness[7] = 0.004;       //lower black
            }
            ui->verticalSlider_cyanInkThickness->setValue(30);
            ui->label_cyanInkThickness->setText("100");
            ui->verticalSlider_magentaInkThickness->setValue(25);
            ui->label_magentaInkThickness->setText("100");
            ui->verticalSlider_yellowInkThickness->setValue(25);
            ui->label_yellowInkThickness->setText("100");
            ui->verticalSlider_blackInkThickness->setValue(40);
            ui->label_blackInkThickness->setText("100");

            ui->radioButton_paper4->setChecked(true);
            break;
        }
        inkKeyQuantity = fgetc(configFile);
        inkFountainWidth = (float)(fgetc(configFile) * 256 + fgetc(configFile)) / 10.0;
        printingPlateHeight = (float)(fgetc(configFile) * 256 + fgetc(configFile)) / 10.0;
        maxInkValue = fgetc(configFile);
        inkFraction = fgetc(configFile);
        inkKeySteps = inkFraction * maxInkValue;
        for (int i = 0; i < 8; i ++)
            inkRollerSpeed[i] = fgetc(configFile);

        calculateInkRatio();

        int sign = 0;
        for (int i = 0; i < 8; i ++){
            sign = fgetc(configFile);
            basicInkValue[i] = fgetc(configFile) + (fgetc(configFile) << 8);
            if (sign == 2)
                basicInkValue[i] = -basicInkValue[i];
        }
        if (inkKeyQuantity != 0){
            QList<short> qlist1;
            for (int i = 0; i <= inkKeySteps; i ++)
                qlist1.append(i);

            for(int i = 0; i < totalColors * numberOfSides; i ++)
                inkCurve.append(qlist1);

            QList<short> qlist3;

            for(int i = 0; i < totalColors * numberOfSides; i ++)
                changedPoints.append(qlist3);
            isMemoryForColorOffsetValid = true;

            short tempCurveValue = 0;
            short tempChangedPoints = 0;
            for (k = 0; k < totalColors * numberOfSides; k ++){
                for (j = 0; j <= inkKeySteps; j ++){
                    tempCurveValue = fgetc(configFile) + (fgetc(configFile) << 8);
                    inkCurve[k][j] = tempCurveValue;
                }
                size = fgetc(configFile);
                for (l = 0; l < size; l ++){
                    tempChangedPoints = fgetc(configFile) + (fgetc(configFile) << 8);
                    changedPoints[k].append(tempChangedPoints);
                }
            }
            QString numStr;
            numStr.setNum(totalColors);
            ui->text_totalColors->setText(numStr);
            numStr.setNum(inkKeyQuantity);
            ui->text_numOfInkKeys->setText(numStr);
            numStr.setNum(inkFountainWidth);
            numStr.append(" cm");
            ui->text_fountainWidth->setText(numStr);
            numStr.setNum(printingPlateHeight);
            numStr.append(" cm");
            ui->text_plateHeight->setText(numStr);
            numStr.setNum(maxInkValue);
            ui->text_maxInkValue->setText(numStr);
            numStr.setNum(inkFraction);
            ui->text_inkFraction->setText(numStr);

            ui->horizontalSlider_cyanInkValue->setMaximum(inkKeySteps);
            ui->horizontalSlider_magentaInkValue->setMaximum(inkKeySteps);
            ui->horizontalSlider_yellowInkValue->setMaximum(inkKeySteps);
            ui->horizontalSlider_blackInkValue->setMaximum(inkKeySteps);
            if (totalColors == 5){
                ui->horizontalSlider_color1InkValue->setMaximum(inkKeySteps);
            }
            else if (totalColors == 6){
                ui->horizontalSlider_color1InkValue->setMaximum(inkKeySteps);
                ui->horizontalSlider_color2InkValue->setMaximum(inkKeySteps);
            }

            ui->radioButton_oneSide->setEnabled(false);
            ui->radioButton_twoSides->setEnabled(false);
            ui->pushButton_totalColors->setEnabled(false);
            ui->pushButton_KeyNumbers->setEnabled(false);
            ui->pushButton_fountainWidth->setEnabled(false);
            ui->pushButton_plateHeight->setEnabled(false);
            ui->pushButton_maxInkValue->setEnabled(false);
            ui->pushButton_inkFraction->setEnabled(false);
            ui->pushButton_enterParameters->setEnabled(false);

            QList<short> qlist5;
            for (int i = 0; i < inkKeyQuantity; i ++)
                qlist5.append(0);

            for(int i = 0; i < totalColors * numberOfSides; i ++)
                increasedInkQuantity.append(qlist5);

            isIncreasedInkQuantityValid = true;
        }
        fclose(configFile);
    }
    font.setFamily(QString::fromUtf8("WenQuanYi Zen Hei"));
    font.setPointSize(8);

    messageBox = new QMessageBox(this);
    messageBox->setWindowFlags(flags);
    messageBox->addButton(QMessageBox::Ok);
    connect(this, SIGNAL(closeMessage()), messageBox, SLOT(accept()));
    connect(messageBox->button(QMessageBox::Ok), SIGNAL(clicked()), this, SLOT(physicalSelectButtonPressed()));
    messageBox->setFont(font);
    messageBox->setIcon(QMessageBox::Warning);

    isTabWidgetVisible = false;
    maximum_display_width = 800;
    ui->tabWidget->setVisible(false);
    ui->pushButton_showTabWidget->setGeometry(768, 55, 26, 26);

    ui->text_numOfInkKeys->setStyleSheet("border:1px solid;"
                                         "border-color:black;"
                                         "background-color:white");
    ui->text_fountainWidth->setStyleSheet("border:1px solid;"
                                          "border-color:black;"
                                          "background-color:white");
    ui->text_plateHeight->setStyleSheet("border:1px solid;"
                                        "border-color:black;"
                                        "background-color:white");
    ui->text_maxInkValue->setStyleSheet("border:1px solid;"
                                        "border-color:black;"
                                        "background-color:white");
    ui->text_inkFraction->setStyleSheet("border:1px solid;"
                                        "border-color:black;"
                                        "background-color:white");

    ui->text_totalColors->setStyleSheet("border:1px solid;"
                                        "border-color:black;"
                                        "background-color:white");
    ui->text_ValueOfInput->setStyleSheet("border:1px solid;"
                                         "border-color:black;"
                                         "background-color:white");
    ui->lineEdit_currentInkZone->setStyleSheet("border:1px solid;"
                                               "border-color:black;"
                                               "background-color:white");
    ui->lineEdit_ipAddress->setStyleSheet("border:1px solid;"
                                          "border-color:black;"
                                          "background-color:white");
    ui->progressBar->setStyleSheet("border:1px solid;"
                                   "border-color:black;"
                                   "background-color:white");
}
void MainWindow::show_hideTabWidget()
{
    if (isOtherInstructionInProcess())
        return;
    if (isTabWidgetVisible){
        ui->tabWidget->setVisible(false);
        isTabWidgetVisible = false;
        ui->pushButton_showTabWidget->setGeometry(768, 55, 26, 26);
        ui->pushButton_showTabWidget->setText("<");
        maximum_display_width = 800;
        paintEventId = currentColorShowing;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
    else{
        ui->tabWidget->setVisible(true);
        isTabWidgetVisible = true;
        ui->pushButton_showTabWidget->setGeometry(556, 55, 26, 26);
        ui->pushButton_showTabWidget->setText(">");
        maximum_display_width = 590;
        paintEventId = currentColorShowing;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
    selectedButton = WIDGET_ID_SHOW_HIDE_TABWIDGET;
}
void MainWindow::changeBatteryPercentage(int batteryPercentage)
{
    ui->progressBar_battery->setValue(batteryPercentage);
}
void MainWindow::changeChargingStatus(bool isCharging)
{
    if (isCharging){
        ui->progressBar_battery->setStyleSheet("QProgressBar{background-color:rgb(255,255,255);border:1px inset rgb(200,200,200);} QProgressBar::chunk{background-color:qlineargradient(spread:reflect, x1:1, y1:0.506, x2:1, y2:0, stop:0 rgba(0, 191, 0, 255), stop:1 rgba(255, 255, 255, 255))}");
    }
    else{
        ui->progressBar_battery->setStyleSheet("QProgressBar{background-color:rgb(255,255,255);border:1px inset rgb(200,200,200);} QProgressBar::chunk{background-color:qlineargradient(spread:reflect, x1:1, y1:0.506, x2:1, y2:0, stop:0 rgba(243, 0, 0, 255), stop:1 rgba(255, 255, 255, 255))}");
    }
}
void MainWindow::changeWidgetVisualEffect(int previousButton, int currentButton)
{
    switch(previousButton){
    case WIDGET_ID_OPEN_FILE:
        ui->actionOpen->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_MAKE_CONNECTION:
        ui->actionSync->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_SAVE_FILE:
        ui->actionSave->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_DELETE_FILE:
        ui->actionDelete->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_ZOOM_IN:
        ui->actionZoomIn->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_REVISE_PARAMETER:
        ui->actionSettings->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_SHUT_DOWN:
        ui->actionShutDown->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_SHOW_HIDE_TABWIDGET:
        ui->pushButton_showTabWidget->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");;
        break;
    case WIDGET_ID_ONE_SIDE:
        ui->radioButton_oneSide->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_TWO_SIDES:
        ui->radioButton_twoSides->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK_KEY_QUANTITY:
        ui->pushButton_KeyNumbers->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_FOUNTAIN_WIDTH:
        ui->pushButton_fountainWidth->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_FOUNTAIN_HEIGHT:
        ui->pushButton_plateHeight->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_MAX_INK_VALUE:
        ui->pushButton_maxInkValue->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INK_FRACTION:
        ui->pushButton_inkFraction->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_TOTAL_COLORS:
        ui->pushButton_totalColors->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_ENTER_PARAMETERS:
        ui->pushButton_enterParameters->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_ONE:
        ui->pushButton_one->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_TWO:
        ui->pushButton_two->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_THREE:
        ui->pushButton_three->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_FOUR:
        ui->pushButton_four->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_FIVE:
        ui->pushButton_five->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_SIX:
        ui->pushButton_six->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_SEVEN:
        ui->pushButton_seven->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_EIGHT:
        ui->pushButton_eight->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_NINE:
        ui->pushButton_nine->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_ZERO:
        ui->pushButton_zero->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INPUT_DOT:
        ui->pushButton_dot->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DELETE:
        ui->pushButton_delete->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_ENTER:
        ui->pushButton_enter->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_UPPER_SIDE:
        ui->radioButton_upperSide->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_LOWER_SIDE:
        ui->radioButton_lowerSide->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_CYAN:
        ui->cyan->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_MAGENTA:
        ui->magenta->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_YELLOW:
        ui->yellow->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_BLACK:
        ui->black->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_COLOR1:
        ui->color1->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_COLOR2:
        ui->color2->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION1:
        ui->pushButton_direction1->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION2:
        ui->pushButton_direction2->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION3:
        ui->pushButton_direction3->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION4:
        ui->pushButton_direction4->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION5:
        ui->pushButton_direction5->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION6:
        ui->pushButton_direction6->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION7:
        ui->pushButton_direction7->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DIRECTION8:
        ui->pushButton_direction8->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_LAST_INK_ZONE:
        ui->pushButton_lastInkZone->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_NEXT_INK_ZONE:
        ui->pushButton_nextInkZone->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INCREASE_CYAN:
        ui->pushButton_increaseCyan->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DECREASE_CYAN:
        ui->pushButton_decreaseCyan->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INCREASE_MAGENTA:
        ui->pushButton_increaseMagenta->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DECREASE_MAGENTA:
        ui->pushButton_decreaseMagenta->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INCREASE_YELLOW:
        ui->pushButton_increaseYellow->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DECREASE_YELLOW:
        ui->pushButton_decreaseYellow->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INCREASE_BLACK:
        ui->pushButton_increaseBlack->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DECREASE_BLACK:
        ui->pushButton_decreaseBlack->setStyleSheet("QWidget {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INCREASE_COLOR1:
        ui->pushButton_increaseColor1->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DECREASE_COLOR1:
        ui->pushButton_decreaseColor1->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INCREASE_COLOR2:
        ui->pushButton_increaseColor2->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_DECREASE_COLOR2:
        ui->pushButton_decreaseColor2->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_ADJUST_ROLLER_SPEED:
        ui->pushButton_adjustRollerSpeed->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_ADJUST_BASIC_INK:
        ui->pushButton_adjustBasicInk->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_ADJUST_SINGLE_INK:
        ui->pushButton_adjustSingleInk->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_ROUGH_ADJUST:
        ui->pushButton_roughAdjust->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_SUBTLE_ADJUST:
        ui->pushButton_subtleAdjust->setStyleSheet("QPushButton {background-color:rgb(200, 200, 200);}");
        break;
    case WIDGET_ID_INK1:
        ui->radioButton_Ink1->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK2:
        ui->radioButton_Ink2->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK3:
        ui->radioButton_Ink3->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK4:
        ui->radioButton_Ink4->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER1:
        ui->radioButton_paper1->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER2:
        ui->radioButton_paper2->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER3:
        ui->radioButton_paper3->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER4:
        ui->radioButton_paper4->setStyleSheet("QWidget{border:0px solid rgb(0,0,0)}");
    }
    switch(currentButton){
    case WIDGET_ID_OPEN_FILE:
        ui->actionOpen->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_MAKE_CONNECTION:
        ui->actionSync->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_SAVE_FILE:
        ui->actionSave->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_DELETE_FILE:
        ui->actionDelete->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_ZOOM_IN:
        ui->actionZoomIn->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_REVISE_PARAMETER:
        ui->actionSettings->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_SHUT_DOWN:
        ui->actionShutDown->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_SHOW_HIDE_TABWIDGET:
        ui->pushButton_showTabWidget->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ONE_SIDE:
        ui->radioButton_oneSide->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_TWO_SIDES:
        ui->radioButton_twoSides->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK_KEY_QUANTITY:
        ui->pushButton_KeyNumbers->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_FOUNTAIN_WIDTH:
        ui->pushButton_fountainWidth->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_FOUNTAIN_HEIGHT:
        ui->pushButton_plateHeight->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_MAX_INK_VALUE:
        ui->pushButton_maxInkValue->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INK_FRACTION:
        ui->pushButton_inkFraction->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_TOTAL_COLORS:
        ui->pushButton_totalColors->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ENTER_PARAMETERS:
        ui->pushButton_enterParameters->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_ONE:
        ui->pushButton_one->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_TWO:
        ui->pushButton_two->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_THREE:
        ui->pushButton_three->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_FOUR:
        ui->pushButton_four->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_FIVE:
        ui->pushButton_five->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_SIX:
        ui->pushButton_six->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_SEVEN:
        ui->pushButton_seven->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_EIGHT:
        ui->pushButton_eight->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_NINE:
        ui->pushButton_nine->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_ZERO:
        ui->pushButton_zero->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INPUT_DOT:
        ui->pushButton_dot->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DELETE:
        ui->pushButton_delete->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ENTER:
        ui->pushButton_enter->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_UPPER_SIDE:
        ui->radioButton_upperSide->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_LOWER_SIDE:
        ui->radioButton_lowerSide->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_CYAN:
        ui->cyan->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_MAGENTA:
        ui->magenta->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_YELLOW:
        ui->yellow->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_BLACK:
        ui->black->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_COLOR1:
        ui->color1->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_COLOR2:
        ui->color2->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION1:
        ui->pushButton_direction1->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION2:
        ui->pushButton_direction2->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION3:
        ui->pushButton_direction3->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION4:
        ui->pushButton_direction4->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION5:
        ui->pushButton_direction5->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION6:
        ui->pushButton_direction6->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION7:
        ui->pushButton_direction7->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DIRECTION8:
        ui->pushButton_direction8->setStyleSheet("QWidget {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_LAST_INK_ZONE:
        ui->pushButton_lastInkZone->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_NEXT_INK_ZONE:
        ui->pushButton_nextInkZone->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INCREASE_CYAN:
        ui->pushButton_increaseCyan->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DECREASE_CYAN:
        ui->pushButton_decreaseCyan->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INCREASE_MAGENTA:
        ui->pushButton_increaseMagenta->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DECREASE_MAGENTA:
        ui->pushButton_decreaseMagenta->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INCREASE_YELLOW:
        ui->pushButton_increaseYellow->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DECREASE_YELLOW:
        ui->pushButton_decreaseYellow->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INCREASE_BLACK:
        ui->pushButton_increaseBlack->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DECREASE_BLACK:
        ui->pushButton_decreaseBlack->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INCREASE_COLOR1:
        ui->pushButton_increaseColor1->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DECREASE_COLOR1:
        ui->pushButton_decreaseColor1->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INCREASE_COLOR2:
        ui->pushButton_increaseColor2->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_DECREASE_COLOR2:
        ui->pushButton_decreaseColor2->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ADJUST_ROLLER_SPEED:
        ui->pushButton_adjustRollerSpeed->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ADJUST_BASIC_INK:
        ui->pushButton_adjustBasicInk->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ADJUST_SINGLE_INK:
        ui->pushButton_adjustSingleInk->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_ROUGH_ADJUST:
        ui->pushButton_roughAdjust->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_SUBTLE_ADJUST:
        ui->pushButton_subtleAdjust->setStyleSheet("QPushButton {background-color:rgb(255, 255, 255);}");
        break;
    case WIDGET_ID_INK1:
        ui->radioButton_Ink1->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK2:
        ui->radioButton_Ink2->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK3:
        ui->radioButton_Ink3->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_INK4:
        ui->radioButton_Ink4->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER1:
        ui->radioButton_paper1->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER2:
        ui->radioButton_paper2->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER3:
        ui->radioButton_paper3->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
        break;
    case WIDGET_ID_PAPER4:
        ui->radioButton_paper4->setStyleSheet("QWidget{border:1px solid rgb(0,0,0)}");
    }
}
bool MainWindow::isOtherInstructionInProcess()
{
    if (isWaitingForUserResponse ||
        isEnteringDigitalInput ||
        isSelectingFile ||
        isCommunicating ||
        isManipulatingImageFile ||
        isDecidingToStartNewPrintingJobOrNot ||
        isShutingDownDevice ||
        isStatusWidgetVisible ||
        isDeletingFile ||
        isEstablishingDeletion ||
        isRevisingAllParameters){
        if (isEnteringDigitalInput){
            switch(whichParameterToSet){
            case PARAMETER_INK_KEY_QUANTITY:
                ui->pushButton_KeyNumbers->setDown(true);
                break;
            case PARAMETER_FOUNTAIN_WIDTH:
                ui->pushButton_fountainWidth->setDown(true);
                break;
            case PARAMETER_FOUNTAIN_HEIGHT:
                ui->pushButton_plateHeight->setDown(true);
                break;
            case PARAMETER_MAX_INK_VALUE:
                ui->pushButton_maxInkValue->setDown(true);
                break;
            case PARAMETER_INK_FRACTION:
                ui->pushButton_inkFraction->setDown(true);
                break;
            case PARAMETER_TOTAL_COLORS:
                ui->pushButton_totalColors->setDown(true);
            }
        }
        return true;
    }

    return false;
}
void MainWindow::changeToNextTabWidgetIndex()
{
    if (isOtherInstructionInProcess())
        return;
    if (!isTabWidgetVisible)
        return;
    if (tabIndex < 3)
        tabIndex ++;
    ui->tabWidget->setCurrentIndex(tabIndex);
    switchGroupBox();
}
void MainWindow::changeToLastTabWidgetIndex()
{
    if (isOtherInstructionInProcess())
        return;
    if (!isTabWidgetVisible)
        return;
    if (tabIndex > 0)
        tabIndex --;
    ui->tabWidget->setCurrentIndex(tabIndex);
    switchGroupBox();
}
void MainWindow::physicalCancelButtonPressed()
{
    previouslySelectedButton = selectedButton;
    if (isSelectingFile){
        cancelSelect();
        isSelectingFile = false;
        if (isFileListInitialized){
            delete fileList;
            fileList = NULL;
            isFileListInitialized = false;
        }
        fileName.clear();

        selectedButton = WIDGET_ID_OPEN_FILE;
    }
    else if (isRevisingAllParameters){
        isRevisingAllParameters = false;
        cancelMachineModelSelection();
        emit closeMessage();
    }
    else if (isDeletingFile){
        ui->widget_deleteFileList->setVisible(false);
        isDeletingFile = false;
        toRemoveAllFiles = false;
        if (isFileListInitialized){
            delete fileList;
            fileList = NULL;
            isFileListInitialized = false;
        }
        selectedButton = WIDGET_ID_DELETE_FILE;
    }
    else if (isEstablishingDeletion){
        emit closeMessage();
        toRemoveAllFiles = false;
        isEstablishingDeletion = false;
        selectedButton = WIDGET_ID_DELETE_FILE;
    }
    else if (isDecidingToStartNewPrintingJobOrNot){
        isDecidingToStartNewPrintingJobOrNot = false;
        selectedButton = WIDGET_ID_OPEN_FILE;
        emit closeMessage();
    }
    else if (isShutingDownDevice){
        emit closeMessage();
        isShutingDownDevice = false;
    }
    else if (isEnteringDigitalInput){
        inputValue = 0;
        hasDotEntered = false;
        digitsOfFractions = -1;
        isEnteringDigitalInput = false;
        switch(whichParameterToSet){
        case PARAMETER_INK_KEY_QUANTITY:
            inkKeyQuantity = 0;
            ui->pushButton_KeyNumbers->setDown(false);
            ui->text_ValueOfInput->setText("");
            whichParameterToSet = 0;
            selectedButton = WIDGET_ID_INK_KEY_QUANTITY;
            break;
        case PARAMETER_FOUNTAIN_WIDTH:
            inkFountainWidth = 0;
            ui->pushButton_fountainWidth->setDown(false);
            ui->text_ValueOfInput->setText("");
            whichParameterToSet = 0;
            selectedButton = WIDGET_ID_FOUNTAIN_WIDTH;
            break;
        case PARAMETER_FOUNTAIN_HEIGHT:
            printingPlateHeight = 0;
            ui->pushButton_plateHeight->setDown(false);
            ui->text_ValueOfInput->setText("");
            whichParameterToSet = 0;
            selectedButton = WIDGET_ID_FOUNTAIN_HEIGHT;
            break;
        case PARAMETER_MAX_INK_VALUE:
            maxInkValue = 0;
            ui->pushButton_maxInkValue->setDown(false);
            ui->text_ValueOfInput->setText("");
            whichParameterToSet = 0;
            selectedButton = WIDGET_ID_MAX_INK_VALUE;
            break;
        case PARAMETER_INK_FRACTION:
            inkFraction = 0;
            ui->pushButton_inkFraction->setDown(false);
            ui->text_ValueOfInput->setText("");
            whichParameterToSet = 0;
            selectedButton = WIDGET_ID_INK_FRACTION;
            break;
        case PARAMETER_TOTAL_COLORS:
            ui->pushButton_totalColors->setDown(false);
            ui->text_totalColors->setText("");
            whichParameterToSet = 0;
            selectedButton = WIDGET_ID_TOTAL_COLORS;
            break;
        case PARAMETER_IP_ADDRESS:
            ui->widget_ip->setVisible(false);
            selectedButton = WIDGET_ID_MAKE_CONNECTION;
        }
    }
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
}
void MainWindow::physicalSelectButtonPressed()
{
    previouslySelectedButton = selectedButton;
    if (isWaitingForUserResponse){
        emit closeMessage();
        isWaitingForUserResponse = false;
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        return;
    }
    else if (isRevisingAllParameters){
        isRevisingAllParameters = false;

        collectMemoryGarbage();

        if (machineModel == 0){
            totalColors = 0;
            inkKeyQuantity = 0;
            inkFountainWidth = 0;
            printingPlateHeight = 0;
            upper_inkFountainWidthInPixel = 0;
            lower_inkFountainWidthInPixel = 0;
            for (int i = 0; i < 8; i ++)
                basicInkValue[i] = 0;

            maxInkValue = 0;
            inkFraction = 0;
            inputValue = 0;
            paintEventId = 0;
            hasDotEntered = false;
            digitsOfFractions = -1;
            ui->radioButton_oneSide->setEnabled(true);
            ui->radioButton_twoSides->setEnabled(true);
            ui->pushButton_totalColors->setEnabled(true);
            ui->pushButton_KeyNumbers->setEnabled(true);
            ui->pushButton_fountainWidth->setEnabled(true);
            ui->pushButton_plateHeight->setEnabled(true);
            ui->pushButton_maxInkValue->setEnabled(true);
            ui->pushButton_inkFraction->setEnabled(true);
            ui->pushButton_enterParameters->setEnabled(true);

            ui->radioButton_oneSide->setChecked(false);
            ui->radioButton_twoSides->setChecked(false);
            ui->text_numOfInkKeys->setText("");
            ui->text_fountainWidth->setText("");
            ui->text_plateHeight->setText("");
            ui->text_maxInkValue->setText("");
            ui->text_inkFraction->setText("");
            ui->text_totalColors->setText("");
            cancelMachineModelSelection();
            changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        }
        else
            selectMachineModel();
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        return;
    }
    else if (isStatusWidgetVisible){
        eliminateStatusWidget();
        isStatusWidgetVisible = false;
    }
    else if (isDecidingToStartNewPrintingJobOrNot){
        isDecidingToStartNewPrintingJobOrNot = false;
        emit closeMessage();
        collectMemoryGarbage();
        numOfPagesOpened = 0;
        openFile();
    }
    else if (isShutingDownDevice){
        isShutingDownDevice = false;
        system("halt");
    }
    else if (isSelectingFile){
        isSelectingFile = false;
        ui->pushButton_selectFile->setEnabled(true);
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        ui->widget_fileList->setVisible(false);
        isStatusWidgetVisible = true;
        ui->progressBar->setValue(0);
        ui->widget_status->setVisible(true);

        selectFile();
        selectedButton = WIDGET_ID_OPEN_FILE;
        if (isFileListInitialized){
            delete fileList;
            fileList = NULL;
            isFileListInitialized = false;
        }
    }
    else if (isDeletingFile){
        if (!ui->pushButton_selectFileToDelete->isEnabled()){
            changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
            return;
        }
        selectFileToDelete();
        if (isFileListInitialized){
            delete fileList;
            fileList = NULL;
            isFileListInitialized = false;
        }
    }
    else if (isEstablishingDeletion){
        emit closeMessage();
        if (toRemoveAllFiles == false){
            if (isFileFromUSB){
                const char *f = fileName.toAscii().data();
                remove(f);
            }
            else{
                int indexOfEntryToBeDelete = fileList->currentRow() - 1 - numOfContentsFromUSB;
                QByteArray response;
                response = "r";
                for (int i = 0; i < 4; i ++)
                    response.append((indexOfEntryToBeDelete >> (8 * i)) & (0xff));
                socket->write(response);
            }
        }
        else{
            char str[100];
            char dest[100];
            strcpy(dest,"/udisk/*");
            sprintf(str, "rm -fR %s", dest);
            system(str);

            QByteArray response;
            response = "r";
            for (int i = 0; i < 4; i ++)
                response.append('9');
            socket->write(response);
        }
        isEstablishingDeletion = false;
        selectedButton = WIDGET_ID_DELETE_FILE;
    }
    else{
        switch(selectedButton)
        {
        case WIDGET_ID_OPEN_FILE:
            openFile();                  //actionOpen was triggered
            break;
        case WIDGET_ID_MAKE_CONNECTION:
            makeConnection();            //actionSync was triggered
            break;
        case WIDGET_ID_SAVE_FILE:
            saveInkValue();
            break;
        case WIDGET_ID_DELETE_FILE:
            deleteFile();
            break;
        case WIDGET_ID_ZOOM_IN:
            zoomInInkValue();                  //actionClose was triggered
            break;
        case WIDGET_ID_REVISE_PARAMETER:
            reviseParameters();
            break;
        case WIDGET_ID_SHUT_DOWN:
            shutDownLinux();
            break;
        case WIDGET_ID_SHOW_HIDE_TABWIDGET:
            show_hideTabWidget();
            break;
        case WIDGET_ID_ONE_SIDE:
            if (ui->radioButton_oneSide->isEnabled()){
                setToOneSide();
                ui->radioButton_oneSide->setChecked(true);
            }
            break;
        case WIDGET_ID_TWO_SIDES:
            if (ui->radioButton_twoSides->isEnabled()){
                setToTwoSides();
                ui->radioButton_twoSides->setChecked(true);
            }
            break;
        case WIDGET_ID_INK_KEY_QUANTITY:
            if (ui->pushButton_KeyNumbers->isEnabled()){
                setParameter_inkKeyValues(); //pushButton_keyNumbers was clicked
            }
            break;
        case WIDGET_ID_FOUNTAIN_WIDTH:
            if (ui->pushButton_fountainWidth->isEnabled()){
                setParameter_fountainWidth();
            }
            break;
        case WIDGET_ID_FOUNTAIN_HEIGHT:
            if (ui->pushButton_plateHeight->isEnabled()){
                setParameter_plateHeight();
            }
            break;
        case WIDGET_ID_MAX_INK_VALUE:
            if (ui->pushButton_maxInkValue->isEnabled()){
                setParameter_maxInkValue();
            }
            break;
        case WIDGET_ID_INK_FRACTION:
            if (ui->pushButton_inkFraction->isEnabled()){
                setParameter_inkFraction();
            }
            break;
        case WIDGET_ID_TOTAL_COLORS:
            if (ui->pushButton_totalColors->isEnabled()){
                setParameter_totalColors();
            }
            break;
        case WIDGET_ID_ENTER_PARAMETERS:
            if (ui->pushButton_enterParameters->isEnabled())
                enterParameters();
            break;
        case WIDGET_ID_INPUT_ONE:
            inputOne();
            break;
        case WIDGET_ID_INPUT_TWO:
            inputTwo();
            break;
        case WIDGET_ID_INPUT_THREE:
            inputThree();
            break;
        case WIDGET_ID_INPUT_FOUR:
            inputFour();
            break;
        case WIDGET_ID_INPUT_FIVE:
            inputFive();
            break;
        case WIDGET_ID_INPUT_SIX:
            inputSix();
            break;
        case WIDGET_ID_INPUT_SEVEN:
            inputSeven();
            break;
        case WIDGET_ID_INPUT_EIGHT:
            inputEight();
            break;
        case WIDGET_ID_INPUT_NINE:
            inputNine();
            break;
        case WIDGET_ID_INPUT_ZERO:
            inputZero();
            break;
        case WIDGET_ID_INPUT_DOT:
            inputDot();
            break;
        case WIDGET_ID_DELETE:
            inputDelete();
            break;
        case WIDGET_ID_ENTER:
            inputEnter();
            break;
        case WIDGET_ID_UPPER_SIDE:
            showUpperSide();
            break;
        case WIDGET_ID_LOWER_SIDE:
            showDownSide();
            break;
        case WIDGET_ID_CYAN:
            showCyanComponent();
            break;
        case WIDGET_ID_MAGENTA:
            showMagentaComponent();
            break;
        case WIDGET_ID_YELLOW:
            showYellowComponent();
            break;
        case WIDGET_ID_BLACK:
            showBlackComponent();
            break;
        case WIDGET_ID_COLOR1:
            showColor1Component();
            break;
        case WIDGET_ID_COLOR2:
            showColor2Component();
            break;
        case WIDGET_ID_DIRECTION1:
            direction1();
            break;
        case WIDGET_ID_DIRECTION2:
            direction2();
            break;
        case WIDGET_ID_DIRECTION3:
            direction3();
            break;
        case WIDGET_ID_DIRECTION4:
            direction4();
            break;
        case WIDGET_ID_DIRECTION5:
            direction5();
            break;
        case WIDGET_ID_DIRECTION6:
            direction6();
            break;
        case WIDGET_ID_DIRECTION7:
            direction7();
            break;
        case WIDGET_ID_DIRECTION8:
            direction8();
            break;
        case WIDGET_ID_LAST_INK_ZONE:
            showLastInkZone();
            break;
        case WIDGET_ID_NEXT_INK_ZONE:
            showNextInkZone();
            break;
        case WIDGET_ID_INCREASE_CYAN:
            increaseCyan();
            break;
        case WIDGET_ID_DECREASE_CYAN:
            decreaseCyan();
            break;
        case WIDGET_ID_INCREASE_MAGENTA:
            increaseMagenta();
            break;
        case WIDGET_ID_DECREASE_MAGENTA:
            decreaseMagenta();
            break;
        case WIDGET_ID_INCREASE_YELLOW:
            increaseYellow();
            break;
        case WIDGET_ID_DECREASE_YELLOW:
            decreaseYellow();
            break;
        case WIDGET_ID_INCREASE_BLACK:
            increaseBlack();
            break;
        case WIDGET_ID_DECREASE_BLACK:
            decreaseBlack();
            break;
        case WIDGET_ID_INCREASE_COLOR1:
            increaseColor1();
            break;
        case WIDGET_ID_DECREASE_COLOR1:
            decreaseColor1();
            break;
        case WIDGET_ID_INCREASE_COLOR2:
            increaseColor2();
            break;
        case WIDGET_ID_DECREASE_COLOR2:
            decreaseColor2();
            break;
        case WIDGET_ID_ADJUST_ROLLER_SPEED:
            setToRollerSpeedAdjustment();
            break;
        case WIDGET_ID_ADJUST_BASIC_INK:
            setToBasicAdjustment();
            break;
        case WIDGET_ID_ADJUST_SINGLE_INK:
            setToSingleAdjustment();
            break;
        case WIDGET_ID_ROUGH_ADJUST:
            setRoughAdjustment();
            break;
        case WIDGET_ID_SUBTLE_ADJUST:
            setSubtleAdjustment();
            break;
        case WIDGET_ID_INK1:
            setToInk1();
            break;
        case WIDGET_ID_INK2:
            setToInk2();
            break;
        case WIDGET_ID_INK3:
            setToInk3();
            break;
        case WIDGET_ID_INK4:
            setToInk4();
            break;
        case WIDGET_ID_PAPER1:
            setToPaper1();
            break;
        case WIDGET_ID_PAPER2:
            setToPaper2();
            break;
        case WIDGET_ID_PAPER3:
            setToPaper3();
            break;
        case WIDGET_ID_PAPER4:
            setToPaper4();
            break;
        }
    }
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
}
void MainWindow::encoder_turnedLeft()
{
    previouslySelectedButton = selectedButton;
    if (isSelectingFile && (selectedButton >= (NUMBER_OF_TOTAL_WIDGET + 1))){
        if (selectedButton > (NUMBER_OF_TOTAL_WIDGET + 1))
            selectedButton --;
        fileList->setCurrentRow(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1);
        fileName = fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1)->text();
        if ((selectedButton - NUMBER_OF_TOTAL_WIDGET) <= numOfContentsFromUSB){
            fileName.prepend(UDISK_LOCATION);
            isFileFromUSB = true;
            isFileFromREMOTE = false;
        }
        else{
            fileName.prepend(REMOTE_LOCATION);
            isFileFromUSB = false;
            isFileFromREMOTE = true;
        }
        ui->pushButton_selectFile->setEnabled(true);
    }
    else if (isDeletingFile && (selectedButton >= (NUMBER_OF_TOTAL_WIDGET + 1))){
        if (selectedButton > (NUMBER_OF_TOTAL_WIDGET + 1))
            selectedButton --;
        fileList->setCurrentRow(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1);
        fileName = fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1)->text();
        if (fileList->item(0)->isSelected())
            toRemoveAllFiles = true;
        else if ((selectedButton - NUMBER_OF_TOTAL_WIDGET) <= numOfContentsFromUSB){
            fileName.prepend(UDISK_LOCATION);
            isFileFromUSB = true;
            isFileFromREMOTE = false;
        }
        else{
            fileName.prepend(REMOTE_LOCATION);
            isFileFromUSB = false;
            isFileFromREMOTE = true;
        }
        ui->pushButton_selectFileToDelete->setEnabled(true);
    }
    else if (isRevisingAllParameters && (selectedButton >= (NUMBER_OF_TOTAL_WIDGET + 1))){
        if (selectedButton > (NUMBER_OF_TOTAL_WIDGET + 1))
            selectedButton --;
        fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1)->setSelected(true);
        fileList->scrollToItem(fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1));
        machineModel = selectedButton - NUMBER_OF_TOTAL_WIDGET - 1;
        FILE *fileOfMachineModelNumber = fopen("/opt/PDA/bin/machineModel", "wb");
        fputc(machineModel, fileOfMachineModelNumber);
        fclose(fileOfMachineModelNumber);
        ui->pushButton_selectMachineModel->setEnabled(true);
    }
    if (isTabWidgetVisible){
        switch(tabIndex){
        case 0:
            if ((selectedButton > 1) && (selectedButton <= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_PARAMETER_SETTING_PANEL)))
                selectedButton --;
            else if (isEnteringDigitalInput && (selectedButton > (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_PARAMETER_SETTING_PANEL + 1))
                && (selectedButton <= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB)))
                selectedButton --;
            break;
        case 1:
            if (((selectedButton > (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + 1)) &&
                 (selectedButton <= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + NUMBER_OF_WIDGETS_ON_2NDTAB))) ||
                ((selectedButton <= NUMBER_OF_WIDGETS_ON_TOOLBAR) && (selectedButton > 1)))
                selectedButton --;
            else if (selectedButton == (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + 1))
                selectedButton = NUMBER_OF_WIDGETS_ON_TOOLBAR;
            break;
        case 2:
            if (((selectedButton > (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + NUMBER_OF_WIDGETS_ON_2NDTAB + 1)) &&
                 (selectedButton <= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                     + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB))) ||
                ((selectedButton <= NUMBER_OF_WIDGETS_ON_TOOLBAR) && (selectedButton > 1)))
                selectedButton --;
            else if (selectedButton == (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + NUMBER_OF_WIDGETS_ON_2NDTAB + 1))
                selectedButton = NUMBER_OF_WIDGETS_ON_TOOLBAR;
            break;
        case 3:
            if (((selectedButton > (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                    + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB + 1)) &&
                 (selectedButton <= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                     + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB + NUMBER_OF_WIDGETS_ON_4THTAB))) ||
                ((selectedButton <= NUMBER_OF_WIDGETS_ON_TOOLBAR) && (selectedButton > 1)))
                selectedButton --;
            else if (selectedButton == (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                        + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB + 1))
                selectedButton = NUMBER_OF_WIDGETS_ON_TOOLBAR;
            break;
        }
    }
    else{
        if ((selectedButton > WIDGET_ID_OPEN_FILE) && (selectedButton <= NUMBER_OF_WIDGETS_ON_TOOLBAR))
            selectedButton --;
    }
    if (selectedButton == 0)
        selectedButton = WIDGET_ID_OPEN_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
}
void MainWindow::encoder_turnedRight()
{
    previouslySelectedButton = selectedButton;
    if (isSelectingFile &&
             (selectedButton > NUMBER_OF_TOTAL_WIDGET) &&
             (selectedButton < (NUMBER_OF_TOTAL_WIDGET + numOfAvailableContents))){
        selectedButton ++;

        fileList->setCurrentRow(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1);
        fileName = fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1)->text();
        if ((selectedButton - NUMBER_OF_TOTAL_WIDGET) <= numOfContentsFromUSB){
            fileName.prepend(UDISK_LOCATION);
            isFileFromUSB = true;
            isFileFromREMOTE = false;
        }
        else{
            fileName.prepend(REMOTE_LOCATION);
            isFileFromUSB = false;
            isFileFromREMOTE = true;
        }
        ui->pushButton_selectFile->setEnabled(true);

    }
    else if (isDeletingFile &&
             (selectedButton > NUMBER_OF_TOTAL_WIDGET) &&
             (selectedButton < (NUMBER_OF_TOTAL_WIDGET + numOfAvailableContents))){
        selectedButton ++;
        fileList->setCurrentRow(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1);
        fileName = fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1)->text();
        if (fileList->item(0)->isSelected())
            toRemoveAllFiles = true;
        else if ((selectedButton - NUMBER_OF_TOTAL_WIDGET) <= numOfContentsFromUSB){
            fileName.prepend(UDISK_LOCATION);
            isFileFromUSB = true;
            isFileFromREMOTE = false;
        }
        else{
            fileName.prepend(REMOTE_LOCATION);
            isFileFromUSB = false;
            isFileFromREMOTE = true;
        }
        ui->pushButton_selectFileToDelete->setEnabled(true);
    }
    else if (isRevisingAllParameters &&
             (selectedButton > NUMBER_OF_TOTAL_WIDGET) &&
             (selectedButton < (NUMBER_OF_TOTAL_WIDGET + NUMBER_OF_MACHINE_MODELS))){
        selectedButton ++;
        fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1)->setSelected(true);
        fileList->scrollToItem(fileList->item(selectedButton - NUMBER_OF_TOTAL_WIDGET - 1));
        machineModel = selectedButton - NUMBER_OF_TOTAL_WIDGET - 1;
        FILE *fileOfMachineModelNumber = fopen("/opt/PDA/bin/machineModel", "wb");
        fputc(machineModel, fileOfMachineModelNumber);
        fclose(fileOfMachineModelNumber);
        ui->pushButton_selectMachineModel->setEnabled(true);
    }
    if (isTabWidgetVisible){
        switch(tabIndex){
        case 0:
            if (selectedButton < (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_PARAMETER_SETTING_PANEL))
                selectedButton ++;
            else if (isEnteringDigitalInput && (selectedButton < (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB)))
                selectedButton ++;
            break;
        case 1:
            if (selectedButton < NUMBER_OF_WIDGETS_ON_TOOLBAR ||
                ((selectedButton < (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + NUMBER_OF_WIDGETS_ON_2NDTAB)) &&
                 (selectedButton >= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB))))
                selectedButton ++;
            else if (selectedButton == NUMBER_OF_WIDGETS_ON_TOOLBAR)
                selectedButton = (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB + 1);
            break;
        case 2:
            if (((selectedButton < (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                    + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB)) &&
                 (selectedButton >= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                     + NUMBER_OF_WIDGETS_ON_2NDTAB))) || (selectedButton < NUMBER_OF_WIDGETS_ON_TOOLBAR))
                selectedButton ++;
            else if (selectedButton == NUMBER_OF_WIDGETS_ON_TOOLBAR)
                selectedButton = (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                  + NUMBER_OF_WIDGETS_ON_2NDTAB + 1);
            break;
        case 3:
            if (((selectedButton < (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                    + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB + NUMBER_OF_WIDGETS_ON_4THTAB)) &&
                 (selectedButton >= (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                     + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB))) ||
                (selectedButton < NUMBER_OF_WIDGETS_ON_TOOLBAR))
                selectedButton ++;
            else if (selectedButton == NUMBER_OF_WIDGETS_ON_TOOLBAR)
                selectedButton = (NUMBER_OF_WIDGETS_ON_TOOLBAR + NUMBER_OF_WIDGETS_ON_1STTAB
                                  + NUMBER_OF_WIDGETS_ON_2NDTAB + NUMBER_OF_WIDGETS_ON_3RDTAB + 1);
        }
    }
    else{
        if ((selectedButton >= WIDGET_ID_OPEN_FILE) && (selectedButton < NUMBER_OF_WIDGETS_ON_TOOLBAR))
            selectedButton ++;
    }
    if (selectedButton == 0)
        selectedButton = WIDGET_ID_OPEN_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
}
void MainWindow::selectMachineModel()
{
    if (isFileListInitialized){
        delete fileList;
        fileList = NULL;
        isFileListInitialized = false;
    }
    ui->widget_machineModel->setVisible(false);
    ui->radioButton_oneSide->setEnabled(true);
    ui->radioButton_twoSides->setEnabled(true);

    QString numStr;

    switch(machineModel){
    case 1:                 //Heidelberg 102V
        totalColors = 4;
        numberOfSides = 1;
        inkKeyQuantity = 32;
        inkFountainWidth = 102;
        printingPlateHeight = 72;
        maxInkValue = 16;
        inkFraction = 11;
        inkKeySteps = 176;
        break;
        /*
    case 1:                 //Heidelberg CD102-4
        totalColors = 4;
        numberOfSides = 1;
        ui->radioButton_twoSides->setChecked(false);
        ui->radioButton_oneSide->setChecked(true);

        inkKeyQuantity = 32;
        numStr.setNum((int)inkKeyQuantity);
        ui->text_numOfInkKeys->setText(numStr);

        inkFountainWidth = 102;
        numStr.setNum(inkFountainWidth);
        numStr.append(" cm");
        ui->text_fountainWidth->setText(numStr);

        printingPlateHeight = 72;
        numStr.setNum(printingPlateHeight);
        numStr.append(" cm");
        ui->text_plateHeight->setText(numStr);

        maxInkValue = 25;
        ui->text_maxInkValue->setText(numStr.setNum(maxInkValue));

        inkFraction = 20;
        ui->text_inkFraction->setText(numStr.setNum(inkFraction));

        inkKeySteps = 500;
        ui->horizontalSlider_cyanInkValue->setMaximum(inkKeySteps);
        ui->horizontalSlider_magentaInkValue->setMaximum(inkKeySteps);
        ui->horizontalSlider_yellowInkValue->setMaximum(inkKeySteps);
        ui->horizontalSlider_blackInkValue->setMaximum(inkKeySteps);
        break;
        */
    case 2:                 //Lithrone LS440
        totalColors = 4;
        numberOfSides = 1;
        inkKeyQuantity = 30;
        inkFountainWidth = 102;
        printingPlateHeight = 71;
        maxInkValue = 100;
        inkFraction = 2;
        inkKeySteps = 200;
        break;
    case 3:     //heidelberg PM74
        totalColors = 4;
        numberOfSides = 1;
        inkKeyQuantity = 23;
        inkFountainWidth = 74;
        printingPlateHeight = 51;
        maxInkValue = 16;
        inkFraction = 16;
        inkKeySteps = 256;
        break;
    case 4:
        totalColors = 6;
        numberOfSides = 1;
        inkKeyQuantity = 34;
        inkFountainWidth = 103;
        printingPlateHeight = 72;
        maxInkValue = 100;
        inkFraction = 2;
        inkKeySteps = 200;
        break;
    }
    ui->radioButton_twoSides->setChecked(false);
    ui->radioButton_oneSide->setChecked(true);
    ui->text_totalColors->setText(numStr.setNum(totalColors));
    numStr.setNum((int)inkKeyQuantity);
    ui->text_numOfInkKeys->setText(numStr);
    numStr.setNum(inkFountainWidth);
    numStr.append(" cm");
    ui->text_fountainWidth->setText(numStr);
    numStr.setNum(printingPlateHeight);
    numStr.append(" cm");
    ui->text_plateHeight->setText(numStr);
    ui->text_maxInkValue->setText(numStr.setNum(maxInkValue));
    ui->text_inkFraction->setText(numStr.setNum(inkFraction));
    ui->horizontalSlider_cyanInkValue->setMaximum(inkKeySteps);
    ui->horizontalSlider_magentaInkValue->setMaximum(inkKeySteps);
    ui->horizontalSlider_yellowInkValue->setMaximum(inkKeySteps);
    ui->horizontalSlider_blackInkValue->setMaximum(inkKeySteps);

    enterParameters();
    selectedButton = WIDGET_ID_REVISE_PARAMETER;
}
void MainWindow::cancelMachineModelSelection()
{
    if (isFileListInitialized){
        delete fileList;
        fileList = NULL;
        isFileListInitialized = false;
    }
    ui->widget_machineModel->setVisible(false);
    selectedButton = WIDGET_ID_REVISE_PARAMETER;
}
void MainWindow::enterParameters()
{
    if (isOtherInstructionInProcess())
        return;
    if (totalColors == 0 ||
        numberOfSides == 0 ||
        inkKeyQuantity == 0 ||
        inkFountainWidth == 0 ||
        printingPlateHeight == 0 ||
        maxInkValue == 0 ||
        inkFraction == 0){
        isWaitingForUserResponse = true;
        //please enter all parameters
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\350\276\223\345\205\245\346\211\200\346\234\211\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    if (isMemoryForColorOffsetValid){
        inkCurve.clear();
        changedPoints.clear();
        isMemoryForColorOffsetValid = false;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ENTER_PARAMETERS;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    int i;
    inkKeySteps = inkFraction * maxInkValue;
    ui->horizontalSlider_cyanInkValue->setMaximum(inkKeySteps);
    ui->horizontalSlider_magentaInkValue->setMaximum(inkKeySteps);
    ui->horizontalSlider_yellowInkValue->setMaximum(inkKeySteps);
    ui->horizontalSlider_blackInkValue->setMaximum(inkKeySteps);
    if (totalColors == 4){
        ui->color1->setEnabled(false);
        ui->color2->setEnabled(false);
        ui->pushButton_increaseColor1->setEnabled(false);
        ui->pushButton_increaseColor2->setEnabled(false);
        ui->pushButton_decreaseColor1->setEnabled(false);
        ui->pushButton_decreaseColor2->setEnabled(false);
        ui->horizontalSlider_color1InkValue->setEnabled(false);
        ui->horizontalSlider_color2InkValue->setEnabled(false);
    }
    else if (totalColors == 5){
        if (numberOfSides == 2){
            currentColorShowing = CLEAR;
            isWaitingForUserResponse = true;
            messageBox->setText("正反两面机型只支持最多每面4种颜色");
            messageBox->exec();
            return;
        }
        ui->color1->setEnabled(true);
        ui->color2->setEnabled(false);
        ui->pushButton_increaseColor1->setEnabled(true);
        ui->pushButton_increaseColor2->setEnabled(false);
        ui->pushButton_decreaseColor1->setEnabled(true);
        ui->pushButton_decreaseColor2->setEnabled(false);
        ui->horizontalSlider_color1InkValue->setEnabled(true);
        ui->horizontalSlider_color2InkValue->setEnabled(false);

        ui->horizontalSlider_color1InkValue->setMaximum(inkKeySteps);
    }
    else if (totalColors == 6){
        if (numberOfSides == 2){
            currentColorShowing = CLEAR;
            isWaitingForUserResponse = true;
            messageBox->setText("正反两面机型只支持最多每面4种颜色");
            messageBox->exec();
            return;
        }
        ui->color1->setEnabled(true);
        ui->color2->setEnabled(true);
        ui->pushButton_increaseColor1->setEnabled(true);
        ui->pushButton_increaseColor2->setEnabled(true);
        ui->pushButton_decreaseColor1->setEnabled(true);
        ui->pushButton_decreaseColor2->setEnabled(true);
        ui->horizontalSlider_color1InkValue->setEnabled(true);
        ui->horizontalSlider_color2InkValue->setEnabled(true);

        ui->horizontalSlider_color1InkValue->setMaximum(inkKeySteps);
        ui->horizontalSlider_color2InkValue->setMaximum(inkKeySteps);
    }
    for (int i = 0; i < 8; i ++){
        basicInkValue[i] = 0;
        inkRollerSpeed[i] = 30;     //all the ink roller speed are set to 30 by default
        inkRatio[i] = 1.0;
    }
    QList<short> qlist1;
    for (i = 0; i <= inkKeySteps; i ++)
        qlist1.append(i);
    for (i = 0; i < totalColors * numberOfSides; i ++)
        inkCurve.append(qlist1);

    QList<short> qlist3;
    qlist3.append(0);
    qlist3.append(inkKeySteps);
    for (i = 0; i < totalColors * numberOfSides; i ++)
        changedPoints.append(qlist3);

    isMemoryForColorOffsetValid = true;

    ui->radioButton_oneSide->setEnabled(false);
    ui->radioButton_twoSides->setEnabled(false);
    ui->pushButton_KeyNumbers->setEnabled(false);
    ui->pushButton_fountainWidth->setEnabled(false);
    ui->pushButton_plateHeight->setEnabled(false);
    ui->pushButton_maxInkValue->setEnabled(false);
    ui->pushButton_inkFraction->setEnabled(false);
    ui->pushButton_totalColors->setEnabled(false);
    ui->pushButton_enterParameters->setEnabled(false);

    //默认设置为高光涂料纸
    setToPaper1();

    if (isIncreasedInkQuantityValid)
        increasedInkQuantity.clear();

    QList<short> qlist5;
    for (i = 0; i < inkKeyQuantity; i ++)
        qlist5.append(0);

    for(i = 0; i < totalColors * numberOfSides; i ++)
        increasedInkQuantity.append(qlist5);

    isIncreasedInkQuantityValid = true;

    calculateInkRatio();

    writeInkInfoToFile();
}
void MainWindow::showStatusWidget()
{
    isStatusWidgetVisible = true;
    ui->widget_status->setVisible(true);
}
void MainWindow::eliminateStatusWidget()
{
    ui->widget_status->setVisible(false);
    isStatusWidgetVisible = false;
}
void MainWindow::statusHandler(int id)
{
    switch(id){
    case 0:
        ui->pushButton_sure->setEnabled(false);
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\350\216\267\345\217\226\346\226\207\344\273\266\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
                                 //正在获取文件信息
        ui->progressBar->setMaximum(0);
        break;
    case 1:
        ui->pushButton_sure->setEnabled(false);
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\346\211\223\345\274\200.PPF\346\226\207\344\273\266\357\274\214\350\257\267\347\250\215\345\220\216...", 0, QApplication::UnicodeUTF8));
        break;
    case 2:
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\350\256\241\347\256\227\346\262\271\345\242\250\346\225\260\346\215\256\357\274\214\350\257\267\347\250\215\345\220\216...", 0, QApplication::UnicodeUTF8));
        break;
    case 3:
        ui->pushButton_sure->setEnabled(true);
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\257\273\345\217\226\345\256\214\346\257\225", 0, QApplication::UnicodeUTF8));
        break;
    case 4:
        ui->pushButton_sure->setEnabled(false);
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\346\211\223\345\274\200.TIFF\346\226\207\344\273\266\357\274\214\350\257\267\347\250\215\345\220\216...", 0, QApplication::UnicodeUTF8));
        break;
    case 5:
        //ui->label_processStatus->setText(tr("正在计算油墨数据，请稍后..."));
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\350\256\241\347\256\227\346\262\271\345\242\250\346\225\260\346\215\256\357\274\214\350\257\267\347\250\215\345\220\216...", 0, QApplication::UnicodeUTF8));
        break;
    }
}
void MainWindow::setProgressBar(qint64 r)
{
    ui->progressBar->setRange(0, r);
}
void MainWindow::updateProgressBar(qint64 r)
{
    ui->progressBar->setValue(r);
}
void MainWindow::selectFile()
{
    selectedButton = WIDGET_ID_OPEN_FILE;
    isSelectingFile = false;
    isManipulatingImageFile = true;

    if (isFileFromREMOTE){
        fileName.remove(REMOTE_LOCATION);
        int indexOfEntryToBeTransmitted = fileList->currentRow() - numOfContentsFromUSB;
        isCommunicating = true;

        QByteArray response;
        response = "t";
        for (int i = 0; i < 4; i ++)
            response.append((indexOfEntryToBeTransmitted >> (8 * i)) & (0xff));
        socket->write(response);
    }
    else{
        manipulateImageFile();
    }
}
void MainWindow::deleteContentInRemoteFolder()
{
    char str[100];
    sprintf(str, "rm -fR /mnt/i/*");
    system(str);
}
void MainWindow::cleanUpAfterFileManipulationFailed(QString s)
{
    if (isFileListInitialized){
        delete fileList;
        fileList = NULL;
        isFileListInitialized = false;
    }
    entryNamesInRemoteImageFolder.clear();
    eliminateStatusWidget();
    currentColorShowing = CLEAR;
    isWaitingForUserResponse = true;
    messageBox->setText(s);
    messageBox->exec();
    fileName.clear();
    isManipulatingImageFile = false;
    isCommunicating = false;
    deleteContentInRemoteFolder();
}

void MainWindow::manipulateImageFile()
{
    if ((!fileName.contains(".tif", Qt::CaseInsensitive)) && (!fileName.contains(".ppf", Qt::CaseInsensitive))){  //it is a folder
        QDir d(fileName);

        QStringList nameFilters;
        nameFilters << "*.tif" << "*.ppf";
        QStringList filesInFolder = d.entryList(nameFilters, QDir::Files);
        if (filesInFolder.length() == 0){
            cleanUpAfterFileManipulationFailed("在该文件夹中没有找到油墨文件");
            return;
        }
        fileName.append("/").append(filesInFolder.at(0));
    }

    QString text;
    if (fileName.endsWith(".ppf", Qt::CaseInsensitive)){
        fileName = fileName.trimmed();
        QByteArray array = fileName.toAscii();
        const char *ppfFileName = array.data();
        if (numOfPagesOpened == 0){
            if (isFileFromUSB)
                upper_fileName = fileName.remove(UDISK_LOCATION);
            else if (isFileFromREMOTE)
                upper_fileName = fileName.remove(REMOTE_LOCATION);
            ph1 = new PPFHandler(ppfFileName, totalColors);
            connect(ph1, SIGNAL(progressRange(qint64)), this, SLOT(setProgressBar(qint64)));
            connect(ph1, SIGNAL(percentage(qint64)), this, SLOT(updateProgressBar(qint64)));
            connect(this, SIGNAL(status(int)), this, SLOT(statusHandler(int)));
            emit status(0);
            int retValueOfGetImageInfo = ph1->getColorOrder();
            if (retValueOfGetImageInfo < 0){
                if (retValueOfGetImageInfo == -1){
                    cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\345\255\230\346\224\276\351\241\272\345\272\217\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                    return;
                }
                else if (retValueOfGetImageInfo == -2){
                    cleanUpAfterFileManipulationFailed("该印刷机型不支持数量过多的色彩");
                    return;
                }
                else if (retValueOfGetImageInfo == -3){
                    cleanUpAfterFileManipulationFailed("该文件夹中的色彩文件数量不对");
                    return;
                }
            }

            if (ph1->getImagePlanarConfiguration() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\345\255\230\346\224\276\351\241\272\345\272\217\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph1->getImageDataSize() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\345\244\247\345\260\217\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph1->getTransferMatrix() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\226\271\345\220\221\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph1->getResolution() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\345\210\206\350\276\250\347\216\207\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }

            if (ph1->getEncodingAndCompression() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\345\210\206\350\276\250\347\216\207\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }

            //if the input ink fountain width is 0,
            //or if it is larger than the maximum display width,
            //set it to image width automatically
            if (inkFountainWidth == 0 || inkFountainWidth >= 200){
                inkFountainWidth = 2.54 * ph1->image_width / ph1->xResolution;
                text.setNum(inkFountainWidth);
                text.append(" cm");
                ui->text_fountainWidth->setText(text);
            }
            //if the input plate height is 0,
            //or if it is larger than the maximum display height,
            //set it to image height automatically
            if (printingPlateHeight == 0 || printingPlateHeight >= 200){
                printingPlateHeight = 2.54 * ph1->image_height / ph1->yResolution;
                text.setNum(printingPlateHeight);
                text.append(" cm");
                ui->text_plateHeight->setText(text);
            }
            upper_inkFountainWidthInPixel = (int)(ph1->xResolution * inkFountainWidth / 2.54);

            emit status(1);
            numberOfColorsInPPF1 = ph1->getImageData((int)inkFountainWidth, (int)printingPlateHeight);
            if (numberOfColorsInPPF1 == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            emit status(2);

            if (ph1->calculateInkCoverage(inkKeyQuantity, inkKeySteps) == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\220\204\345\242\250\345\214\272\346\225\260\346\215\256\345\207\272\351\224\231\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }

            emit status(3);
            isUpperFileOpened = true;
            upperFileFormat = PPF_FORMAT;
            for (int i = 0; i < numberOfColorsInPPF1; i ++)
                inkValues[i] = ph1->inkValues[i];
        }
        else if (numOfPagesOpened == 1){
            if (isFileFromUSB)
                lower_fileName = fileName.remove(UDISK_LOCATION);
            else if (isFileFromREMOTE)
                lower_fileName = fileName.remove(REMOTE_LOCATION);
            ph2 = new PPFHandler(ppfFileName, totalColors);
            connect(ph2, SIGNAL(progressRange(qint64)), this, SLOT(setProgressBar(qint64)));
            connect(ph2, SIGNAL(percentage(qint64)), this, SLOT(updateProgressBar(qint64)));
            connect(this, SIGNAL(status(int)), this, SLOT(statusHandler(int)));
            emit status(0);
            int retValueOfGetImageInfo = ph2->getColorOrder();
            if (retValueOfGetImageInfo < 0){
                if (retValueOfGetImageInfo == -1){
                    cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\345\255\230\346\224\276\351\241\272\345\272\217\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                    return;
                }
                else if (retValueOfGetImageInfo == -2){
                    cleanUpAfterFileManipulationFailed("该印刷机型不支持数量过多的色彩");
                    return;
                }
                else if (retValueOfGetImageInfo == -3){
                    cleanUpAfterFileManipulationFailed("该文件夹中的色彩文件数量不对");
                    return;
                }
            }
            if (ph2->getImagePlanarConfiguration() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\345\255\230\346\224\276\351\241\272\345\272\217\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph2->getImageDataSize() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\345\244\247\345\260\217\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph2->getTransferMatrix() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\226\271\345\220\221\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph2->getResolution() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\345\210\206\350\276\250\347\216\207\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (ph2->getEncodingAndCompression() == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\345\210\206\350\276\250\347\216\207\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            if (inkFountainWidth == 0 || inkFountainWidth >= 200){
                inkFountainWidth = 2.54 * ph2->image_width / ph2->xResolution;
                text.setNum(inkFountainWidth);
                text.append(" cm");
                ui->text_fountainWidth->setText(text);
            }
            if (printingPlateHeight == 0 || printingPlateHeight >= 200){
                printingPlateHeight = 2.54 * ph2->image_height / ph2->yResolution;
                text.setNum(printingPlateHeight);
                text.append(" cm");
                ui->text_plateHeight->setText(text);
            }
            lower_inkFountainWidthInPixel = (int)(ph2->xResolution * inkFountainWidth / 2.54);

            emit status(1);
            numberOfColorsInPPF2 = ph2->getImageData((int)inkFountainWidth, (int)printingPlateHeight);
            if (numberOfColorsInPPF2 == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\227\240\346\263\225\350\216\267\345\217\226\345\233\276\345\203\217\346\225\260\346\215\256\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            emit status(2);
            if (ph2->calculateInkCoverage(inkKeyQuantity, inkKeySteps) == -1){
                cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\350\256\241\347\256\227\345\220\204\345\242\250\345\214\272\346\225\260\346\215\256\345\207\272\351\224\231\357\274\214\350\257\273\345\217\226\345\274\202\345\270\270\347\273\210\346\255\242", 0, QApplication::UnicodeUTF8));
                return;
            }
            emit status(3);
            isLowerFileOpened = true;
            lowerFileFormat = PPF_FORMAT;
            for (int i = numberOfColorsInPPF1; i < (numberOfColorsInPPF1 + numberOfColorsInPPF2); i ++)
                inkValues[i] = ph2->inkValues[i - numberOfColorsInPPF1];
        }
    }
    else if (fileName.endsWith(".tif", Qt::CaseInsensitive)){
        if (fileName.compare("/udisk/007.tif") == 0){       //程序下载更新
            char str[100];
            char source[100];
            char dest[100];
            strcpy(source, "/udisk/007.tif");
            strcpy(dest,"/opt/PDA/bin/");
            sprintf(str, "mv %s %s", source, dest);
            if (system(str) == 0)
                qDebug() << "new file copied";
            sprintf(str, "rm /opt/PDA/bin/untitled");
            if (system(str) == 0)
                qDebug() << "old file removed";
            sprintf(str, "mv /opt/PDA/bin/007.tif /opt/PDA/bin/untitled");
            if (system(str) == 0)
                qDebug() << "new file renamed";
            sprintf(str, "chmod 777 /opt/PDA/bin/untitled");
            system(str);
            sprintf(str, "rm /opt/PDA/bin/ink*");
            if (system(str) == 0)
                qDebug() << "curve files removed";
            sprintf(str, "rm /opt/PDA/bin/machineModel");
            if (system(str) == 0)
                qDebug() << "machine model file removed";
            sprintf(str, "reboot");
            system(str);
        }
        if (numOfPagesOpened == 0){
            if (isFileFromUSB){
                upper_fileName = fileName;
                upper_fileName = upper_fileName.remove(UDISK_LOCATION);
            }
            else if (isFileFromREMOTE){
                upper_fileName = fileName;
                upper_fileName = upper_fileName.remove(REMOTE_LOCATION);
            }
            th1 = new TIFFHandler(fileName, totalColors);
            connect(th1, SIGNAL(progressRange(qint64)), this, SLOT(setProgressBar(qint64)));
            connect(th1, SIGNAL(percentage(qint64)), this, SLOT(updateProgressBar(qint64)));
            connect(this, SIGNAL(status(int)), this, SLOT(statusHandler(int)));
            emit status(0);

            int retValueOfGetImageInfo = th1->getImageInfo();
            if (retValueOfGetImageInfo < 0){
                if (retValueOfGetImageInfo == -1){
                    cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\276\223\345\205\245\346\234\211\350\257\257\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245", 0, QApplication::UnicodeUTF8));
                }
                else if (retValueOfGetImageInfo == -2){
                    cleanUpAfterFileManipulationFailed("该印刷机型不支持数量过多的色彩");
                }
                else if (retValueOfGetImageInfo == -3){
                    cleanUpAfterFileManipulationFailed("该文件夹中的色彩文件数量不对");
                }
                return;
            }
            if (th1->resolutionUnit == INCH){
                if (inkFountainWidth == 0 || inkFountainWidth >= 200){
                    //墨斗宽度输入有误，将墨斗宽度自动设为图像宽度
                    inkFountainWidth = 2.54 * th1->image_width / th1->x_resolution;
                    text.setNum(inkFountainWidth);
                    text.append(" cm");
                    ui->text_fountainWidth->setText(text);
                }
                if (printingPlateHeight == 0 || printingPlateHeight >= 200){
                    //印版长度输入有误，将印版长度自动设为图像长度
                    printingPlateHeight = 2.54 * th1->image_length / th1->y_resolution;
                    text.setNum(printingPlateHeight);
                    text.append(" cm");
                    ui->text_plateHeight->setText(text);
                }
                upper_inkFountainWidthInPixel = (int)(th1->x_resolution * inkFountainWidth / 2.54);
            }
            else if (th1->resolutionUnit == CENTIMETER){
                if (inkFountainWidth == 0 || inkFountainWidth >= 200){
                    //墨斗宽度输入有误，将墨斗宽度自动设为图像宽度
                    inkFountainWidth = th1->image_width / th1->x_resolution;
                    text.setNum(inkFountainWidth);
                    text.append(" cm");
                    ui->text_fountainWidth->setText(text);
                }
                if (printingPlateHeight == 0 || printingPlateHeight >= 200){
                    //印版长度输入有误，将印版长度自动设为图像长度
                    printingPlateHeight = th1->image_length / th1->y_resolution;
                    text.setNum(printingPlateHeight);
                    text.append(" cm");
                    ui->text_plateHeight->setText(text);
                }
                upper_inkFountainWidthInPixel = (int)(th1->x_resolution * inkFountainWidth);
            }

            emit status(4);
            numberOfColorsInTIF1 = th1->getImageData(inkFountainWidth, printingPlateHeight);
            emit status(5);
            th1->calculateInkCoverage(inkKeyQuantity, inkKeySteps);

            emit status(3);
            isUpperFileOpened = true;
            upperFileFormat = TIFF_FORMAT;

            for (int i = 0; i < numberOfColorsInTIF1; i ++)
                inkValues[i] = th1->inkValues[i];
        }
        else if (numOfPagesOpened == 1){
            if (isFileFromUSB){
                lower_fileName = fileName[0];
                lower_fileName = lower_fileName.remove(UDISK_LOCATION);
            }
            else if (isFileFromREMOTE){
                lower_fileName = fileName[0];
                lower_fileName = lower_fileName.remove(REMOTE_LOCATION);
            }
            th2 = new TIFFHandler(fileName, totalColors);
            connect(th2, SIGNAL(progressRange(qint64)), this, SLOT(setProgressBar(qint64)));
            connect(th2, SIGNAL(percentage(qint64)), this, SLOT(updateProgressBar(qint64)));
            connect(this, SIGNAL(status(int)), this, SLOT(statusHandler(int)));
            emit status(0);

            int retValueOfGetImageInfo = th2->getImageInfo();
            if (retValueOfGetImageInfo < 0){
                if (retValueOfGetImageInfo == -1){
                    cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\276\223\345\205\245\346\234\211\350\257\257\357\274\214\350\257\267\351\207\215\346\226\260\350\276\223\345\205\245", 0, QApplication::UnicodeUTF8));
                }
                else if (retValueOfGetImageInfo == -2){
                    cleanUpAfterFileManipulationFailed("该印刷机型不支持数量过多的色彩");
                }
                else if (retValueOfGetImageInfo == -3){
                    cleanUpAfterFileManipulationFailed("该文件夹中的色彩文件数量不对");
                }
                return;
            }

            if (th2->resolutionUnit == INCH){
                if (inkFountainWidth == 0 || inkFountainWidth >= 200){
                    //墨斗宽度输入有误，将墨斗宽度自动设为图像宽度
                    inkFountainWidth = 2.54 * th2->image_width / th2->x_resolution;
                    text.setNum(inkFountainWidth);
                    text.append(" cm");
                    ui->text_fountainWidth->setText(text);
                }
                if (printingPlateHeight == 0 || printingPlateHeight >= 200){
                    //印版长度输入有误，将印版长度自动设为图像长度
                    printingPlateHeight = 2.54 * th2->image_length / th2->y_resolution;
                    text.setNum(printingPlateHeight);
                    text.append(" cm");
                    ui->text_plateHeight->setText(text);
                }
                lower_inkFountainWidthInPixel = (int)(th2->x_resolution * inkFountainWidth / 2.54);
            }
            else if (th2->resolutionUnit == CENTIMETER){
                if (inkFountainWidth == 0 || inkFountainWidth >= 200){
                    //墨斗宽度输入有误，将墨斗宽度自动设为图像宽度
                    inkFountainWidth = th2->image_width / th2->x_resolution;
                    text.setNum(inkFountainWidth);
                    text.append(" cm");
                    ui->text_fountainWidth->setText(text);
                }
                if (printingPlateHeight == 0 || printingPlateHeight >= 200){
                    //印版长度输入有误，将印版长度自动设为图像长度
                    printingPlateHeight = th2->image_length / th2->y_resolution;
                    text.setNum(printingPlateHeight);
                    text.append(" cm");
                    ui->text_plateHeight->setText(text);
                }
                lower_inkFountainWidthInPixel = (int)(th2->x_resolution * inkFountainWidth);
            }

            emit status(4);
            numberOfColorsInTIF2 = th2->getImageData(inkFountainWidth, printingPlateHeight);
            emit status(5);
            th2->calculateInkCoverage(inkKeyQuantity, inkKeySteps);

            emit status(3);
            isLowerFileOpened = true;
            lowerFileFormat = TIFF_FORMAT;
            for (int i = numberOfColorsInTIF1; i < (numberOfColorsInTIF1 + numberOfColorsInTIF2); i ++)
                inkValues[i] = th2->inkValues[i - numberOfColorsInTIF1];
        }
    }

    fileName.clear();
    numOfPagesOpened ++;
    switch(numOfPagesOpened)
    {
    case 1:
        isUpperFileOpened = true;
        break;
    case 2:
        isLowerFileOpened = true;
        break;
    case 3:
        numOfPagesOpened = 0;
    }
    isManipulatingImageFile = false;
    eliminateStatusWidget();

    if (numOfPagesOpened == 1)
        showUpperSide();
    else if (numOfPagesOpened == 2)
        showDownSide();
    ui->tabWidget->setCurrentIndex(1);;
    if (isTabWidgetVisible)
        show_hideTabWidget();

    selectedButton = WIDGET_ID_OPEN_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    deleteContentInRemoteFolder();
}
void MainWindow::selectFileToDelete()
{
    ui->widget_deleteFileList->setVisible(false);
    isDeletingFile = false;
    QMessageBox *m = new QMessageBox(this);
    connect(this, SIGNAL(closeMessage()), m, SLOT(accept()));
    m->setWindowFlags(flags);
    m->setFont(font);
    m->setIcon(QMessageBox::Question);
    if (toRemoveAllFiles == false){
        QString fName = fileName;
        fName.remove(UDISK_LOCATION);
        fName.remove(REMOTE_LOCATION);
        fName.prepend(QApplication::translate("MainWindow", "\346\230\257\345\220\246\345\210\240\351\231\244\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        fName.append("?");
        m->setText(fName);
    }
    else{
        m->setText(QApplication::translate("MainWindow", "\346\230\257\345\220\246\345\210\240\351\231\244\346\211\200\346\234\211\346\226\207\344\273\266\357\274\237", 0, QApplication::UnicodeUTF8));
    }

    m->addButton(QMessageBox::Yes);
    m->addButton(QMessageBox::No);


    isEstablishingDeletion = true;

    connect(m->button(QMessageBox::Yes), SIGNAL(clicked()), this, SLOT(physicalSelectButtonPressed()));
    connect(m->button(QMessageBox::No), SIGNAL(clicked()), this, SLOT(physicalCancelButtonPressed()));
    m->exec();
}
void MainWindow::cancelSelect()
{
    ui->widget_fileList->setVisible(false);
    ui->widget_deleteFileList->setVisible(false);
}
int MainWindow::getAdjustedInkValue(int numOfPage, int color, int inkZone)
{
    int result = (basicInkValue[numOfPage * totalColors + color - 1] +
                  increasedInkQuantity[numOfPage * totalColors + color - 1][inkZone] +
                  inkCurve[numOfPage * totalColors + color - 1][inkValues[numOfPage * totalColors + color - 1][inkZone]]);
    result *= inkRatio[color - 1];
    if (result > inkKeySteps)
        result = inkKeySteps;
    else if (result < 0)
        result = 0;

    return result;
}
void MainWindow::setSelectedFileIndex(QListWidgetItem* i)
{
    previouslySelectedButton = selectedButton;
    fileName = i->text().toAscii();
    selectedButton = NUMBER_OF_TOTAL_WIDGET + 1 + fileList->currentRow();
    if (!isRevisingAllParameters){
        int selectedRow = fileList->currentRow();
        if (isDeletingFile)
            selectedRow = fileList->currentRow() - 1;
        else
            selectedRow = fileList->currentRow();
        if (selectedRow <= (numOfContentsFromUSB - 1)){
            isFileFromUSB = true;
            isFileFromREMOTE = false;
            fileName.prepend(UDISK_LOCATION);
        }
        else{
            isFileFromREMOTE = true;
            isFileFromUSB = false;
            fileName.prepend(REMOTE_LOCATION);
        }
    }
    if (isSelectingFile){
        ui->pushButton_selectFile->setEnabled(true);
        return;
    }
    else if (isDeletingFile){
        if (fileList->currentRow() == 0)
            toRemoveAllFiles = true;
        ui->pushButton_selectFileToDelete->setEnabled(true);
    }
    else if (isRevisingAllParameters){
        machineModel = fileList->currentRow();
        FILE *fileOfMachineModelNumber = fopen("/opt/PDA/bin/machineModel", "wb");
        fputc(machineModel, fileOfMachineModelNumber);
        fclose(fileOfMachineModelNumber);
        ui->pushButton_selectMachineModel->setEnabled(true);
    }
}
void MainWindow::showFilesAndFoldersFor(int instruction)
{
    QString t;
    fileList = new QListWidget();
    isFileListInitialized = true;
    if (instruction == OPENING){
        numOfAvailableContents = 0;
        ui->scrollArea->setWidget(fileList);
    }
    else if (instruction == DELETION){
        numOfAvailableContents = 1;
        t = QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\211\200\346\234\211\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8);
        QListWidgetItem *item = new QListWidgetItem(t, fileList);
        fileList->addItem(item);
        ui->scrollArea_deleteFile->setWidget(fileList);
    }
    QDir entryUSB(UDISK_LOCATION);
    QStringList fileNameFiltersForUSB, folderNameFiltersForUSB;
    fileNameFiltersForUSB << "*.tif" << "*.ppf" << "*.ink";
    folderNameFiltersForUSB << "*";
    QStringList filesInUSB = entryUSB.entryList(fileNameFiltersForUSB, QDir::Files);
    QStringList foldersInUSB = entryUSB.entryList(folderNameFiltersForUSB, QDir::Dirs);
    foldersInUSB.removeAt(foldersInUSB.indexOf("."));
    foldersInUSB.removeAt(foldersInUSB.indexOf(".."));
    for (int i = 0; i < foldersInUSB.length(); i ++){
        t = foldersInUSB.at(i);
        QListWidgetItem *item = new QListWidgetItem(t, fileList);
        fileList->addItem(item);
    }
    for (int i = 0; i < filesInUSB.length(); i ++){
        t = filesInUSB.at(i);
        QListWidgetItem *item = new QListWidgetItem(t, fileList);
        fileList->addItem(item);
    }

    numOfAvailableContents += filesInUSB.length();
    numOfAvailableContents += foldersInUSB.length();
    numOfContentsFromUSB = filesInUSB.length() + foldersInUSB.length();

    for (int i = 0; i < entryNamesInRemoteImageFolder.length(); i ++){
        t = entryNamesInRemoteImageFolder.at(i);
        QListWidgetItem *item = new QListWidgetItem(t, fileList);
        fileList->addItem(item);
    }

    numOfAvailableContents += entryNamesInRemoteImageFolder.length();
    numOfContentsFromREMOTE = entryNamesInRemoteImageFolder.length();

    int minimumNumOfContents = 0;
    if (instruction == DELETION)
        minimumNumOfContents = 1;
    if (numOfAvailableContents == minimumNumOfContents){
        isWaitingForUserResponse = true;
        //no file to open
        if (instruction == OPENING)
            messageBox->setText(QApplication::translate("MainWindow", "\346\262\241\346\234\211\346\226\207\344\273\266\345\217\257\344\273\245\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        //no file to delete
        else if (instruction == DELETION)
            messageBox->setText(QApplication::translate("MainWindow", "\346\262\241\346\234\211\346\226\207\344\273\266\345\217\257\344\273\245\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else if (numOfAvailableContents != minimumNumOfContents){
        if (instruction == OPENING){
            isSelectingFile = true;
            ui->pushButton_selectFile->setEnabled(false);
        }
        else if (instruction == DELETION){
            isDeletingFile = true;
            ui->pushButton_selectFileToDelete->setEnabled(false);
        }
        selectedButton = NUMBER_OF_TOTAL_WIDGET + 1;
                                 //there are totally 47 buttons/widgets,
                                 //so from 48, the consecutive numbers are assigned to
                                 //the existing ppf/tiff files in usb drive/SD card
        if (numOfContentsFromUSB > 0){
            isFileFromUSB = true;
            isFileFromREMOTE = false;
        }
        else{
            isFileFromUSB = false;
            isFileFromREMOTE = true;
        }
    }

    if (instruction == OPENING)
        ui->widget_fileList->setVisible(true);
    else if (instruction == DELETION)
        ui->widget_deleteFileList->setVisible(true);
    connect(fileList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(setSelectedFileIndex(QListWidgetItem*)));
}
void MainWindow::openFile()
{
    if (isOtherInstructionInProcess())
        return;
    if (currentColorShowing != CLEAR){
        paintEventId = CLEAR;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
    currentColorShowing = CLEAR;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_OPEN_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    if (numberOfSides == 0 ||
        totalColors == 0 ||
        inkKeyQuantity == 0 ||
        inkFountainWidth == 0 ||
        printingPlateHeight == 0 ||
        maxInkValue == 0 ||
        inkFraction == 0){
        isWaitingForUserResponse = true;
        //please enter all parameters
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\350\276\223\345\205\245\346\211\200\346\234\211\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    fileName.clear();

    if ((numOfPagesOpened == 2 && numberOfSides == 2) ||
        (numOfPagesOpened == 1 && numberOfSides == 1)){
        isDecidingToStartNewPrintingJobOrNot = true;

        QMessageBox *m = new QMessageBox(this);
        m->setWindowFlags(flags);
        connect(this, SIGNAL(closeMessage()), m, SLOT(accept()));
        m->setFont(font);
        m->setIcon(QMessageBox::Question);
        m->setText(QApplication::translate("MainWindow", "\345\215\263\345\260\206\346\226\260\345\273\272\345\215\260\345\210\267\344\273\273\345\212\241\357\274\214\346\230\257\345\220\246\347\273\247\347\273\255\357\274\237", 0, QApplication::UnicodeUTF8));
        m->addButton(QMessageBox::Yes);
        m->addButton(QMessageBox::No);
        connect(m->button(QMessageBox::Yes), SIGNAL(clicked()), this, SLOT(physicalSelectButtonPressed()));
        connect(m->button(QMessageBox::No), SIGNAL(clicked()), this, SLOT(physicalCancelButtonPressed()));
        m->exec();

        return;
    }
    if (isSocketConnected){
        entryNamesInRemoteImageFolder.clear();
        QByteArray response;
        response = "f";
        for (int i = 0; i < 4; i ++)
            response.append('0');
        socket->write(response); // send command to ask server to transmit all the entry names in image folder
    }
    else{
        showFilesAndFoldersFor(OPENING);
    }
}
void MainWindow::deleteFile()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DELETE_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    paintEventId = CLEAR;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    currentColorShowing = CLEAR;
    toRemoveAllFiles = false;

    if (isSocketConnected){
        entryNamesInRemoteImageFolder.clear();
        QByteArray response;
        response = "d";
        for (int i = 0; i < 4; i ++)
            response.append('0');
        socket->write(response); // send command to ask server to transmit all the entry names in image folder
    }
    else{
        showFilesAndFoldersFor(DELETION);
    }
}
void MainWindow::saveInkValue()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_SAVE_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentColorShowing != CLEAR){
        paintEventId = CLEAR;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
    currentColorShowing = CLEAR;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_SAVE_FILE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    DIR *entry = opendir(UDISK_LOCATION);
    if (entry == NULL){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //cannot find usb drive, please make sure that you have plugged the usb drive
        messageBox->setText(QApplication::translate("MainWindow", "\346\227\240\346\263\225\346\211\276\345\210\260USB\350\256\276\345\244\207\357\274\214\350\257\267\347\241\256\350\256\244\345\267\262\347\273\217\346\217\222\345\205\245U\347\233\230", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    if (!isUpperFileOpened && !isLowerFileOpened){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请将印版文件打开后再保存
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\260\206\345\215\260\347\211\210\346\226\207\344\273\266\346\211\223\345\274\200\345\220\216\345\206\215\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else{
        ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\345\255\230\345\202\250\347\233\270\345\205\263\346\225\260\346\215\256...", 0, QApplication::UnicodeUTF8));
        ui->pushButton_sure->setEnabled(false);
        ui->progressBar->setRange(0, 0);
        showStatusWidget();
        fileSaver *saver = new fileSaver(numOfPagesOpened, upper_fileName, lower_fileName,
                                         machineModel, inkFraction, inkKeyQuantity);
        int colors = 0;
        if (isUpperFileOpened && isLowerFileOpened)
            colors = 8;
        else
            colors = 4;
        for (int j = 0; j < colors; j ++)
            for (int i = 0; i < inkKeyQuantity; i ++)
                saver->inkValues[j][i] = inkValues[j][i];

        saver->saveGeneralFile();
        /*
        if (isUpperFileOpened){
            if (upperFileFormat == PPF_FORMAT)
                saver->saveAsPPF(PPF_FORMAT, ph1, upper_fileName);
            else
                saver->saveAsPPF(TIFF_FORMAT, th1, upper_fileName);
        }
        if (isLowerFileOpened){
            if (upperFileFormat == PPF_FORMAT)
                saver->saveAsPPF(PPF_FORMAT, ph2, upper_fileName);
            else
                saver->saveAsPPF(TIFF_FORMAT, th2, upper_fileName);
        }
        */
        eliminateStatusWidget();
    }
    closedir(entry);
    /*
    QString usbPath = UDISK_LOCATION;
    usbPath.chop(1);
    usbPath.trimmed();

    if ((r = umount(usbPath.toAscii().data())) < 0){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //无法卸载usb设备，文件尚未保存
        messageBox->setText(QApplication::translate("MainWindow", "\346\227\240\346\263\225\345\215\270\350\275\275usb\350\256\276\345\244\207\357\274\214\346\226\207\344\273\266\345\260\232\346\234\252\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    */
    isWaitingForUserResponse = true;
    currentColorShowing = CLEAR;
    //文件已经以文本格式存储在移动存储设备中
    messageBox->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\267\262\347\273\217\344\273\245\346\226\207\346\234\254\346\240\274\345\274\217\345\255\230\345\202\250\345\234\250\347\247\273\345\212\250\345\255\230\345\202\250\350\256\276\345\244\207\344\270\255", 0, QApplication::UnicodeUTF8));
    messageBox->exec();
}
void MainWindow::makeConnection()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_MAKE_CONNECTION;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (isSocketConnected){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText("与远程共享文件夹的连接已经建立，不需要再次连接");
        messageBox->exec();
        return;
    }
    if (!isTabWidgetVisible){
        show_hideTabWidget();
    }
    if (ui->tabWidget->currentIndex() != 0)
        ui->tabWidget->setCurrentIndex(0);
    isEnteringDigitalInput = true;
    selectedButton = WIDGET_ID_MAKE_CONNECTION;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    ui->pushButton_one->setStyleSheet("QPushButton{background-color:rgb(255, 255, 255)}");
    if (currentColorShowing != CLEAR){
        paintEventId = CLEAR;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
    currentColorShowing = CLEAR;
    serverAddress = "";

    QByteArray line;

    QFile fileOfIpAddress("/opt/PDA/bin/ipAddress");
    if (fileOfIpAddress.open(QIODevice::ReadOnly)){
        line = fileOfIpAddress.readLine();
        serverAddress.append(line);
    }
    fileOfIpAddress.close();

    ui->lineEdit_ipAddress->setText(serverAddress);
    whichParameterToSet = PARAMETER_IP_ADDRESS;
    ui->widget_ip->setVisible(true);
}
void MainWindow::connectServer()
{
    ui->widget_ip->setVisible(false);
    const int timeout = 5 * 1000;

    QHostAddress address;
    quint16 port = PORT;

    QFile fileOfIpAddress("/opt/PDA/bin/ipAddress");
    if (fileOfIpAddress.open(QIODevice::WriteOnly)){
        fileOfIpAddress.write(serverAddress.toAscii());
    }
    fileOfIpAddress.close();

    address.setAddress(serverAddress);
    socket->connectToHost(address, port);

    if (!socket->waitForConnected(timeout)){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //等待连接超时
        messageBox->setText(QApplication::translate("MainWindow", "\347\255\211\345\276\205\350\277\236\346\216\245\350\266\205\346\227\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    connect(socket, SIGNAL(disconnected()), this, SLOT(changeConnectionStatus()));
    isSocketConnected = true;

    ui->label_connection->setText("<img src=':/icons/network-connected.png'>");
    ui->label_connection->setGeometry(710, 10, 30, 30);
    ui->label_processStatus->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\345\267\262\347\273\217\345\273\272\347\253\213\357\274\214\347\255\211\345\276\205\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
            //tr("连接已经建立，等待接收数据"));
    ui->pushButton_sure->setEnabled(false);
    ui->progressBar->setValue(0);
    //ui->widget_status->setVisible(true);

    connect(socket, SIGNAL(readyRead()), this, SLOT(receiveFile()));
    /*share folder
    ui->widget_ip->setVisible(false);

    FILE *fileOfIpAddress = fopen("/opt/PDA/bin/ipAddress", "w+");
    for (int addressLength = 0; addressLength < serverAddress.size(); addressLength ++)
        fputc(serverAddress.at(addressLength).toAscii(), fileOfIpAddress);
    fclose(fileOfIpAddress);

    QString mountSharedFolderCommand = "mount -t nfs -o intr,nolock,rsize=1024,wsize=1024 ";
    mountSharedFolderCommand.append(serverAddress);
    mountSharedFolderCommand.append(":/images /mnt/i");
    int ret = system(mountSharedFolderCommand.trimmed().toAscii());
    if (ret != 0){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText("远程共享文件夹访问失败，请确认共享文件夹已经设置共享并且IP地址输入正确");
        messageBox->exec();
        return;
    }

    isShareFolderMounted = true;
    ui->label_connection->setText("<img src=':/icons/network-connected.png'>");
    ui->label_connection->setGeometry(710, 10, 30, 30);
    */
}
void MainWindow::processData(QByteArray &array)
{
    QDataStream in(&array, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_0);

    QString fileInfo;
    quint16 key;

    QByteArray data;
    in >> key >> data;

    switch(key){
    //all entry names in server image folder are sent to client,
    //listing all files/folders in remote image folder and local USB drive
    case 0x000A:
        showFilesAndFoldersFor(OPENING);
        break;
    case 0x000B:
        showFilesAndFoldersFor(DELETION);
        break;
    case 0x0000:		// getting all entry names in image folder in server
        entryNamesInRemoteImageFolder << fileInfo.fromUtf8(data.data(), data.size());
        break;
    case 0x0001:                // getting number of files to be tranmit
        numOfFilesReceived = 0;
        fileInfo = fileInfo.fromUtf8(data.data(), data.size());
        numOfFilesToBeTransmit = fileInfo.toInt();
        if (numOfFilesToBeTransmit == 1)
            isTransmittingFolder = false;
        else
            isTransmittingFolder = true;
        if (((numOfFilesToBeTransmit <= 6) && (numOfFilesToBeTransmit >= 4)) || (numOfFilesToBeTransmit == 1)){
            ui->label_processStatus->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\345\267\262\347\273\217\345\273\272\347\253\213\357\274\214\347\255\211\345\276\205\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
                    //tr("连接已经建立，等待接收数据"));
            ui->pushButton_sure->setEnabled(false);
            ui->progressBar->setValue(0);
            ui->widget_status->setVisible(true);

            ui->progressBar->setRange(0, (receivedFileSize - 1) * numOfFilesToBeTransmit);
            ui->progressBar->setValue(ui->progressBar->minimum());
            QByteArray response;
            response = "n";
            for (int i = 0; i < 4; i ++)
                response.append('0');
            socket->write(response);
        }
        else{
            QByteArray response;
            response = "e";
            for (int i = 0; i < 4; i ++)
                response.append('0');
            socket->write(response);
            cleanUpAfterFileManipulationFailed("颜色数量不正确");
        }
        break;
    case 0x0002:        //getting name of the file to be tranmit
        files[numOfFilesReceived].setFileName(fileName.fromUtf8(data.data(), data.size()).prepend(REMOTE_LOCATION));
        files[numOfFilesReceived].fileName().prepend(REMOTE_LOCATION);
        fileName = files[numOfFilesReceived].fileName();
        files[numOfFilesReceived].open(QIODevice::ReadWrite);
        break;
    case 0x0003:        //getting file size
        numOfCharactersReceived = 0;
        fileInfo = fileInfo.fromUtf8(data.data(), data.size());
        fileSizes[numOfFilesReceived] = fileInfo.toInt();

        setProgressBar(fileSizes[numOfFilesReceived]);
        updateProgressBar(numOfCharactersReceived);
        if (fileSizes[numOfFilesReceived] > MAXIMUM_FILE_SIZE){
            QByteArray response;
            response = "e";
            for (int i = 0; i < 4; i ++)
                response.append('0');
            socket->write(response);
            cleanUpAfterFileManipulationFailed("文件过大");
        }
        else{
            QByteArray response;
            response = "g";
            for (int i = 0; i < 4; i ++)
                response.append('0');
            socket->write(response);
        }
        break;
    case 0x0004:	// file data
        numOfCharactersReceived += data.size();
        ui->progressBar->setValue(numOfCharactersReceived);
        files[numOfFilesReceived].write(data.data(), data.size());
        files[numOfFilesReceived].flush();
        updateProgressBar(numOfCharactersReceived);
        break;
    case 0x0005:		// file EOF
        {
        files[numOfFilesReceived].close();
        numOfFilesReceived ++;
        if (numOfFilesReceived == numOfFilesToBeTransmit){
            ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\344\274\240\350\276\223\345\256\214\346\257\225", 0, QApplication::UnicodeUTF8));
                    //tr("文件传输完毕"));
            isCommunicating = false;
            if (isTransmittingFolder){
                char str[100];
                sprintf(str, "mkdir /mnt/i/1");
                system(str);
                sprintf(str, "mv /mnt/i/* /mnt/i/1");
                system(str);
                this->fileName = "/mnt/i/1";
            }
            manipulateImageFile();
        }
        if (files[0].fileName().compare("/mnt/i/007.tif") == 0){
            char str[100];
            char source[100];
            char dest[100];
            strcpy(source, "/mnt/i/007.tif");
            strcpy(dest,"/opt/PDA/bin/");
            sprintf(str, "mv %s %s", source, dest);
            if (system(str) == 0)
                qDebug() << "new file copied";
            sprintf(str, "rm /opt/PDA/bin/untitled");
            if (system(str) == 0)
                qDebug() << "old file removed";
            sprintf(str, "mv /opt/PDA/bin/007.tif /opt/*/bin/untitled");
            if (system(str) == 0)
                qDebug() << "new file renamed";
            sprintf(str, "chmod 777 /opt/PDA/bin/untitled");
            system(str);
            sprintf(str, "rm /opt/PDA/bin/ink*");
            if (system(str) == 0)
                qDebug() << "curve files removed";
            sprintf(str, "rm /opt/PDA/bin/machineModel");
            if (system(str) == 0)
                qDebug() << "machine model file removed";
            sprintf(str, "reboot");
            system(str);
        }
        while (!(socket->bytesAvailable() == 0)){};
        QByteArray response;
        response = "n";
        for (int i = 0; i < 4; i ++)
            response.append('0');
        socket->write(response);
        }
        break;
    case 0x0006:
        files[numOfFilesReceived].close();
        cleanUpAfterFileManipulationFailed(QApplication::translate("MainWindow", " \346\226\207\344\273\266\345\217\221\351\200\201\345\267\262\347\273\217\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    default: ;
    }
}
void MainWindow::receiveFile()
{
    ui->label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\344\274\240\350\276\223\346\225\260\346\215\256\357\274\214\350\257\267\347\250\215\345\220\216...", 0, QApplication::UnicodeUTF8));
            //tr("正在传输数据，请稍后..."));
    while(socket->bytesAvailable() >= sizeof(quint64))
    {
        if(blockSize == 0){
            if(socket->bytesAvailable() < sizeof(qint64))
                return;
            socket->read((char*)&blockSize, sizeof(qint64));  // read blockSize
        }

        if(socket->bytesAvailable() < blockSize)				//not enough data
            return;
        QByteArray data = socket->read(blockSize);
        processData(data);
        blockSize = 0;
    }
}
void MainWindow::changeConnectionStatus()
{
    isSocketConnected = false;
    ui->label_connection->setText("<img src=':/icons/network-disconnected.png'>");
    if ((!isCommunicating) && isManipulatingImageFile)
        return;
    if (ui->widget_status->isVisible()){
        ui->pushButton_sure->setEnabled(false);
        ui->progressBar->setValue(0);
        ui->widget_status->setVisible(false);
    }
    if (isSelectingFile || isDeletingFile){
        cancelSelect();
        isSelectingFile = false;
        isDeletingFile = false;
    }
    if (isEstablishingDeletion)
        isEstablishingDeletion = false;
    isCommunicating = false;
    cleanUpAfterFileManipulationFailed("与服务器的连接已经断开");
}
void MainWindow::showCyanComponent()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_CYAN;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if ((currentPage == 0) && (!isUpperFileOpened) && (!isLowerFileOpened)){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请先打开正面色彩文件
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else if (currentPage == 0 && isUpperFileOpened)
        currentPage = 1;

    paintEventId = CYAN;
    currentColorShowing = CYAN;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::showMagentaComponent()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_MAGENTA;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if ((currentPage == 0) && (!isUpperFileOpened) && (!isLowerFileOpened)){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请先打开正面色彩文件
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else if (currentPage == 0 && isUpperFileOpened)
        currentPage = 1;

    paintEventId = MAGENTA;
    currentColorShowing = MAGENTA;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::showYellowComponent()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_YELLOW;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if ((currentPage == 0) && (!isUpperFileOpened) && (!isLowerFileOpened)){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请先打开正面色彩文件
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else if (currentPage == 0 && isUpperFileOpened)
        currentPage = 1;

    paintEventId = YELLOW;
    currentColorShowing = YELLOW;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::showBlackComponent()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_BLACK;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if ((currentPage == 0) && (!isUpperFileOpened) && (!isLowerFileOpened)){
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请先打开正面色彩文件
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else if (currentPage == 0 && isUpperFileOpened)
        currentPage = 1;

    paintEventId = BLACK;
    currentColorShowing = BLACK;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::showColor1Component()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_COLOR1;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (totalColors <= 4){
        //该机型没有1号专色
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\245\346\234\272\345\236\213\346\262\241\346\234\2111\345\217\267\344\270\223\350\211\262", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else{
        if ((currentPage == 0) && (!isUpperFileOpened) && (!isLowerFileOpened)){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //请先打开正面色彩文件
            messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            return;
        }
        if (((currentPage == 0 && isUpperFileOpened) || (currentPage == 1)) &&
                 ((numberOfColorsInPPF1 < 5 && upperFileFormat == PPF_FORMAT) ||
                  (numberOfColorsInTIF1 < 5 && upperFileFormat == TIFF_FORMAT))){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //1号专色不可用
            messageBox->setText(QApplication::translate("MainWindow", "1\345\217\267\344\270\223\350\211\262\344\270\215\345\217\257\347\224\250", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            return;
        }
        else if (currentPage == 2 &&
                 ((numberOfColorsInPPF2 < 5 && lowerFileFormat == PPF_FORMAT) ||
                  (numberOfColorsInTIF2 < 5 && lowerFileFormat == TIFF_FORMAT))){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //1号专色不可用
            messageBox->setText(QApplication::translate("MainWindow", "1\345\217\267\344\270\223\350\211\262\344\270\215\345\217\257\347\224\250", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            return;
        }

        if (currentPage == 0 && isUpperFileOpened)
            currentPage = 1;

        paintEventId = COLOR1;
        currentColorShowing = COLOR1;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
}
void MainWindow::showColor2Component()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_COLOR2;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (totalColors <= 5){
        //该机型没有2号专色
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\245\346\234\272\345\236\213\346\262\241\346\234\2112\345\217\267\344\270\223\350\211\262", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    else{
        if ((currentPage == 0) && (!isUpperFileOpened) && (!isLowerFileOpened)){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //请先打开正面色彩文件
            messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            return;
        }
        if (((currentPage == 0 && isUpperFileOpened) || (currentPage == 1)) &&
                 ((numberOfColorsInPPF1 < 6 && upperFileFormat == PPF_FORMAT) ||
                  (numberOfColorsInTIF1 < 6 && upperFileFormat == TIFF_FORMAT))){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //2号专色不可用
            messageBox->setText(QApplication::translate("MainWindow", "2\345\217\267\344\270\223\350\211\262\344\270\215\345\217\257\347\224\250", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            return;
        }
        else if (currentPage == 2 &&
                 ((numberOfColorsInPPF2 < 6 && lowerFileFormat == PPF_FORMAT) ||
                  (numberOfColorsInTIF2 < 6 && lowerFileFormat == TIFF_FORMAT))){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //2号专色不可用
            messageBox->setText(QApplication::translate("MainWindow", "2\345\217\267\344\270\223\350\211\262\344\270\215\345\217\257\347\224\250", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            return;
        }
        if (currentPage == 0 && isUpperFileOpened)
            currentPage = 1;

        paintEventId = COLOR2;
        currentColorShowing = COLOR2;
        update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
    }
}
void MainWindow::showUpperSide()
{
    if (isOtherInstructionInProcess()){
        ui->radioButton_upperSide->setChecked(false);
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_UPPER_SIDE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    ui->radioButton_upperSide->setChecked(true);
    ui->radioButton_lowerSide->setChecked(false);
    if (!isUpperFileOpened){
        ui->radioButton_upperSide->setChecked(false);
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请先打开正面色彩文件
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\346\255\243\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    currentPage = 1;
    paintEventId = UPPER;
    currentColorShowing = UPPER;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::showDownSide()
{
    if (isOtherInstructionInProcess()){
        ui->radioButton_lowerSide->setChecked(false);
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_LOWER_SIDE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    ui->radioButton_upperSide->setChecked(false);
    ui->radioButton_lowerSide->setChecked(true);
    if (!isLowerFileOpened){
        ui->radioButton_lowerSide->setChecked(false);
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        //请先打开反面色彩文件
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\267\345\205\210\346\211\223\345\274\200\345\217\215\351\235\242\350\211\262\345\275\251\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    currentPage = 2;
    paintEventId = LOWER;
    currentColorShowing = LOWER;
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::changeDirection(int angle, bool isFlipped, int dir)
{
    if (currentPage == 1){
        rotateAngle_upper = angle;
        horizontallyFlipped_upper = isFlipped;
        if (upperFileFormat == PPF_FORMAT){
            for (int i = 0; i < numberOfColorsInPPF1; i ++)
                inkValues[i] = ph1->inkValues[(dir - 1) * MAXIMUM_NUMBER_OF_COLORS + i];
        }
        else if (upperFileFormat == TIFF_FORMAT){
            for (int i = 0; i < numberOfColorsInTIF1; i ++)
                inkValues[i] = th1->inkValues[(dir - 1) * MAXIMUM_NUMBER_OF_COLORS + i];
        }

        paintEventId = UPPER;
        currentColorShowing = UPPER;
    }
    else if (currentPage == 2){
        rotateAngle_lower = angle;
        horizontallyFlipped_lower = isFlipped;
        if (lowerFileFormat == PPF_FORMAT){
            for (int i = 0; i < numberOfColorsInPPF2; i ++)
                inkValues[i + MAXIMUM_NUMBER_OF_COLORS] = ph2->inkValues[(dir - 1) * MAXIMUM_NUMBER_OF_COLORS + i];
        }
        else if (lowerFileFormat == TIFF_FORMAT){
            for (int i = 0; i < numberOfColorsInTIF2; i ++)
                inkValues[i + MAXIMUM_NUMBER_OF_COLORS] = th2->inkValues[(dir - 1) * MAXIMUM_NUMBER_OF_COLORS + i];
        }

        paintEventId = LOWER;
        currentColorShowing = LOWER;
    }
    for (int i = 0; i < totalColors * numberOfSides; i ++)
        for (int j = 0; j < inkKeyQuantity; j ++)
            increasedInkQuantity[i][j] = 0;
    curveCollection.clear();
    update(0, TOOLBAR_HEIGHT, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT);
}
void MainWindow::direction1()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION1;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(0, false, 1);
}
void MainWindow::direction2()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION2;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(90, false, 2);
}
void MainWindow::direction3()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION3;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(180, false, 3);
}
void MainWindow::direction4()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION4;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(270, false, 4);
}
void MainWindow::direction5()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION5;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(0, true, 5);
}
void MainWindow::direction6()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION6;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(90, true, 6);
}
void MainWindow::direction7()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION7;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(180, true, 7);
}
void MainWindow::direction8()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DIRECTION8;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    changeDirection(270, true, 8);
}
void MainWindow::showLastInkZone()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_LAST_INK_ZONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    QString v;
    if (currentColorShowing >= 1 && currentColorShowing <= 8){
        if (currentInkZone > 0){
            currentInkZone --;
            ui->lineEdit_currentInkZone->setText(v.setNum(currentInkZone + 1));
            showCurrentInkZone();
        }
    }
}
void MainWindow::showNextInkZone()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_NEXT_INK_ZONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    QString v;
    if (currentColorShowing >= 1 && currentColorShowing <= 8){
        if (currentInkZone < (inkKeyQuantity - 1)){
            currentInkZone ++;
            ui->lineEdit_currentInkZone->setText(v.setNum(currentInkZone + 1));
            showCurrentInkZone();
        }
    }
}
void MainWindow::showCurrentInkZone()
{
    if (isOtherInstructionInProcess())
        return;
    QString v;
    QString cyanValue, magentaValue, yellowValue, blackValue, color1Value, color2Value;
    int cyanInt = 0;
    int magentaInt = 0;
    int yellowInt = 0;
    int blackInt = 0;
    int color1Int = 0;
    int color2Int = 0;
    if (currentColorShowing >= 1 && currentColorShowing <= 8){
        if (currentPage == 1 || currentPage == 2){
            if (isSingleAdjustment){
                cyanInt = getAdjustedInkValue(currentPage - 1, CYAN, currentInkZone);
                cyanValue.setNum(cyanInt / inkFraction);
                cyanValue.append(".").append(v.setNum(cyanInt % inkFraction));

                magentaInt = getAdjustedInkValue(currentPage - 1, MAGENTA, currentInkZone);
                magentaValue.setNum(magentaInt / inkFraction);
                magentaValue.append(".").append(v.setNum(magentaInt % inkFraction));

                yellowInt = getAdjustedInkValue(currentPage - 1, YELLOW, currentInkZone);
                yellowValue.setNum(yellowInt / inkFraction);
                yellowValue.append(".").append(v.setNum(yellowInt % inkFraction));

                blackInt = getAdjustedInkValue(currentPage - 1, BLACK, currentInkZone);
                blackValue.setNum(blackInt / inkFraction);
                blackValue.append(".").append(v.setNum(blackInt % inkFraction));
                if (totalColors >= 5 &&
                    (currentPage == 1 && (((upperFileFormat == PPF_FORMAT) && (numberOfColorsInPPF1 >= 5)) ||
                                          ((upperFileFormat == TIFF_FORMAT) && (numberOfColorsInTIF1 >= 5)))) ||
                    (currentPage == 2 && (((lowerFileFormat == PPF_FORMAT) && (numberOfColorsInPPF2 >= 5)) ||
                                          ((lowerFileFormat == TIFF_FORMAT) && (numberOfColorsInTIF2 >= 5))))){
                    color1Int = getAdjustedInkValue(currentPage - 1, COLOR1, currentInkZone);
                    color1Value.setNum(color1Int / inkFraction);
                    color1Value.append(".").append(v.setNum(color1Int % inkFraction));
                }
                if (totalColors >= 6 &&
                    (currentPage == 1 && (((upperFileFormat == PPF_FORMAT) && numberOfColorsInPPF1 >= 6) ||
                                          ((upperFileFormat == TIFF_FORMAT) && numberOfColorsInTIF1 >= 6))) ||
                    (currentPage == 2 && (((lowerFileFormat == PPF_FORMAT) && numberOfColorsInPPF2 >= 6) ||
                                          ((lowerFileFormat == TIFF_FORMAT) && numberOfColorsInTIF2 >= 6)))){
                    color2Int = getAdjustedInkValue(currentPage - 1, COLOR2, currentInkZone);
                    color2Value.setNum(color2Int / inkFraction);
                    color2Value.append(".").append(v.setNum(color2Int % inkFraction));
                }
            }
            else if (isBasicAdjustment){
                cyanInt = basicInkValue[(currentPage - 1) * totalColors + CYAN - 1];
                cyanValue.setNum(abs(cyanInt) / inkFraction);
                cyanValue.append(".").append(v.setNum(abs(cyanInt) % inkFraction));
                if (cyanInt < 0)
                    cyanValue.prepend("-");

                magentaInt = basicInkValue[(currentPage - 1) * totalColors + MAGENTA - 1];
                magentaValue.setNum(abs(magentaInt) / inkFraction);
                magentaValue.append(".").append(v.setNum(abs(magentaInt) % inkFraction));
                if (magentaInt < 0)
                    magentaValue.prepend("-");

                yellowInt = basicInkValue[(currentPage - 1) * totalColors + YELLOW - 1];
                yellowValue.setNum(abs(yellowInt) / inkFraction);
                yellowValue.append(".").append(v.setNum(abs(yellowInt) % inkFraction));
                if (yellowInt < 0)
                    yellowValue.prepend("-");

                blackInt = basicInkValue[(currentPage - 1) * totalColors + BLACK - 1];
                blackValue.setNum(abs(blackInt) / inkFraction);
                blackValue.append(".").append(v.setNum(abs(blackInt) % inkFraction));
                if (blackInt < 0)
                    blackValue.prepend("-");

                if (totalColors >= 5 &&
                    (currentPage == 1 && ((upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 >= 5) ||
                                          (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 >= 5))) ||
                    (currentPage == 2 && ((lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 >= 5) ||
                                          (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 >= 5)))){
                    color1Int = basicInkValue[(currentPage - 1) * totalColors + COLOR1 - 1];
                    color1Value.setNum(abs(color1Int) / inkFraction);
                    color1Value.append(".").append(v.setNum(abs(color1Int) % inkFraction));
                    if (color1Int < 0)
                        color1Value.prepend("-");
                }
                if (totalColors >= 6 &&
                    (currentPage == 1 && ((upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 >= 6) ||
                                          (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 >= 6))) ||
                    (currentPage == 2 && ((lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 >= 6) ||
                                          (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 >= 6)))){
                    color2Int = basicInkValue[(currentPage - 1) * totalColors + COLOR2 - 1];
                    color2Value.setNum(abs(color2Int) / inkFraction);
                    color2Value.append(".").append(v.setNum(abs(color2Int) % inkFraction));
                    if (color2Int < 0)
                        color2Value.prepend("-");
                }
            }
            else if (isRollerSpeedAdjustment){
                cyanInt = inkRollerSpeed[(currentPage - 1) * totalColors + CYAN - 1];                
                cyanValue.setNum(cyanInt);
                magentaInt = inkRollerSpeed[(currentPage - 1) * totalColors + MAGENTA - 1];
                magentaValue.setNum(magentaInt);
                yellowInt = inkRollerSpeed[(currentPage - 1) * totalColors + YELLOW - 1];
                yellowValue.setNum(yellowInt);
                blackInt = inkRollerSpeed[(currentPage - 1) * totalColors + BLACK - 1];
                blackValue.setNum(blackInt);
                if (totalColors >= 5 &&
                    (currentPage == 1 && ((upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 >= 5) ||
                                          (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 >= 5))) ||
                    (currentPage == 2 && ((lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 >= 5) ||
                                          (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 >= 5)))){
                    color1Int = inkRollerSpeed[(currentPage - 1) * totalColors + COLOR1 - 1];
                    color1Value.setNum(color1Int);
                }
                if (totalColors >= 6 &&
                    (currentPage == 1 && ((upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 >= 6) ||
                                          (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 >= 6))) ||
                    (currentPage == 2 && ((lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 >= 6) ||
                                          (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 >= 6)))){
                    color2Int = inkRollerSpeed[(currentPage - 1) * totalColors + COLOR2 - 1];
                    color2Value.setNum(color2Int);
                }
            }
            if (isSingleAdjustment || isBasicAdjustment || isRollerSpeedAdjustment){
                ui->horizontalSlider_cyanInkValue->setValue(cyanInt);
                ui->label_cyanInkValue->setText(cyanValue);

                ui->horizontalSlider_magentaInkValue->setValue(magentaInt);
                ui->label_magentaInkValue->setText(magentaValue);

                ui->horizontalSlider_yellowInkValue->setValue(yellowInt);
                ui->label_yellowInkValue->setText(yellowValue);

                ui->horizontalSlider_blackInkValue->setValue(blackInt);
                ui->label_blackInkValue->setText(blackValue);

                if (totalColors >= 5 &&
                    (currentPage == 1 && ((upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 >= 5) ||
                                          (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 >= 5))) ||
                    (currentPage == 2 && ((lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 >= 5) ||
                                          (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 >= 5)))){
                    ui->horizontalSlider_color1InkValue->setValue(color1Int);
                    ui->label_color1InkValue->setText(color1Value);
                }
                if (totalColors >= 6 &&
                    (currentPage == 1 && ((upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 >= 6) ||
                                          (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 >= 6))) ||
                    (currentPage == 2 && ((lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 >= 6) ||
                                          (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 >= 6)))){
                    ui->horizontalSlider_color2InkValue->setValue(color2Int);
                    ui->label_color2InkValue->setText(color2Value);
                }
            }
        }
    }
}
void MainWindow::quickSort(short *n, int left, int right)
{
    int dp;
    if (left<right) {
        dp=partition(n,left,right);
        quickSort(n,left,dp-1);
        quickSort(n,dp+1,right);
    }
}
int MainWindow::partition(short *n, int left, int right)
{
    int lo,hi,pivot,t;

    pivot=n[left];
    lo=left-1;
    hi=right+1;

    while(lo+1!=hi) {
        if(n[lo+1]<=pivot)
            lo++;
        else if(n[hi-1]>pivot)
            hi--;
        else {
            t=n[lo+1];
            n[++lo]=n[hi-1];
            n[--hi]=t;
        }
    }
    n[left]=n[lo];
    n[lo]=pivot;
    return lo;
}
void MainWindow::smoothCurve(struct curveUpdateInfo c)
{
    int pointIndex, x1, x2, x3, y1, y2, y3;
    pointIndex = x1 = x2 = x3 = y1 = y2 = y3 = 0;
    float k1, k2, temp;
    k1 = k2 = temp = 0;
    signed int deltaX1, deltaX2, deltaY1, deltaY2;
    deltaX1 = deltaX2 = deltaY1 = deltaY2 = 0;

    int currentColor = c.color;
    int increasedQuantity = c.increasedQuantity;

    inkCurve[currentColor][c.indexOfPoint] += increasedQuantity;
    if (inkCurve[currentColor][c.indexOfPoint] > inkKeySteps)
        inkCurve[currentColor][c.indexOfPoint] = inkKeySteps;
    else if (inkCurve[currentColor][c.indexOfPoint] < 0)
        inkCurve[currentColor][c.indexOfPoint] = 0;

    int size = changedPoints[currentColor].size();
    int i;

    short *unsorted = new short[size];
    for (i = 0; i < size; i ++)
        unsorted[i] = changedPoints[currentColor][i];

    quickSort(unsorted, 0, size - 1);

    for (i = 0; i < size; i ++)
        changedPoints[currentColor][i] = unsorted[i];
    delete []unsorted;
    unsorted = NULL;

    for (i = 0; i < size; i ++){
        if (changedPoints[currentColor][i] == c.indexOfPoint)
            pointIndex = i;
    }

    if (pointIndex != 0 && (pointIndex != inkKeySteps)){
        x1 = changedPoints[currentColor][pointIndex - 1];
        x2 = changedPoints[currentColor][pointIndex];
        x3 = changedPoints[currentColor][pointIndex + 1];
        y1 = inkCurve[currentColor][changedPoints[currentColor][pointIndex - 1]];
        y2 = inkCurve[currentColor][changedPoints[currentColor][pointIndex]];
        y3 = inkCurve[currentColor][changedPoints[currentColor][pointIndex + 1]];
        deltaX1 = x2 - x1;
        deltaX2 = x3 - x2;
        deltaY1 = y2 - y1;
        deltaY2 = y3 - y2;
        k1 = (float)deltaY1 / (float)deltaX1;
        k2 = (float)deltaY2 / (float)deltaX2;
        for (i = x1; i < x2; i ++){
            temp = (float)y1 + k1 * (float)(i - x1);
            if (temp - (int)temp >= 0.5)
                inkCurve[currentColor][i] = (int)temp + 1;
            else
                inkCurve[currentColor][i] = (int)temp;
        }
        for (i = x2; i < x3; i ++){
            temp = (float)y2 + k2 * (float)(i - x2);
            if (temp - (int)temp >= 0.5)
                inkCurve[currentColor][i] = (int)temp + 1;
            else
                inkCurve[currentColor][i] = (int)temp;
        }
    }
    else if (pointIndex == 0){
        x2 = changedPoints[currentColor][pointIndex];
        x3 = changedPoints[currentColor][pointIndex + 1];
        y2 = inkCurve[currentColor][changedPoints[currentColor][pointIndex]];
        y3 = inkCurve[currentColor][changedPoints[currentColor][pointIndex + 1]];
        deltaX2 = x3 - x2;
        deltaY2 = y3 - y2;
        k2 = (float)deltaY2 / (float)deltaX2;
        for (i = x2; i < x3; i ++){
            temp = (float)y2 + k2 * (float)(i - x2);
            if (temp - (int)temp >= 0.5)
                inkCurve[currentColor][i] = (int)temp + 1;
            else
                inkCurve[currentColor][i] = (int)temp;
        }
    }
    else{
        x1 = changedPoints[currentColor][pointIndex - 1];
        x2 = changedPoints[currentColor][pointIndex];
        y1 = inkCurve[currentColor][changedPoints[currentColor][pointIndex - 1]];
        y2 = inkCurve[currentColor][changedPoints[currentColor][pointIndex]];
        deltaX1 = x2 - x1;
        deltaY1 = y2 - y1;
        k1 = (float)deltaY1 / (float)deltaX1;
        for (i = x1; i < x2; i ++){
            temp = (float)y1 + k1 * (float)(i - x1);
            if (temp - (int)temp >= 0.5)
                inkCurve[currentColor][i] = (int)temp + 1;
            else
                inkCurve[currentColor][i] = (int)temp;
        }
    }
}
void MainWindow::changeInkValue(int color, bool isIncreasing)
{
    if (currentPage == 0)
        return;

    QString v, v1;

    int currentColor = (currentPage - 1) * totalColors + color - 1;
    int size = changedPoints[currentColor].size();

    if (currentColorShowing != CLEAR){
        for (int i = 0; i < (size - 1); i ++){
            if (inkValues[currentColor][currentInkZone] > changedPoints[currentColor][i] &&
                inkValues[currentColor][currentInkZone] < changedPoints[currentColor][i + 1]){
                changedPoints[currentColor].insert(i + 1, (short)inkValues[currentColor][currentInkZone]);
                break;
            }
        }
        size = curveCollection.size();
        int i;
        for (i = 0; i < size; i ++){
            if (curveCollection[i].color == currentColor){
                if (adjustmentQuantity == SUBTLE_ADJUSTMENT){
                    if (isIncreasing)
                        curveCollection[i].increasedQuantity ++;
                    else
                        curveCollection[i].increasedQuantity --;
                }
                else if (adjustmentQuantity == ROUGH_ADJUSTMENT){
                    if (isIncreasing)
                        curveCollection[i].increasedQuantity += inkFraction;
                    else
                        curveCollection[i].increasedQuantity -= inkFraction;
                }
                break;
            }
        }
        if (i == size){             //have not found the updated curve
            struct curveUpdateInfo c;
            c.color = currentColor;
            if (adjustmentQuantity == SUBTLE_ADJUSTMENT){
                if (isIncreasing)
                    c.increasedQuantity = 1;
                else
                    c.increasedQuantity = -1;
            }
            else if (adjustmentQuantity == ROUGH_ADJUSTMENT){
                if (isIncreasing)
                    c.increasedQuantity = inkFraction;
                else
                    c.increasedQuantity = -inkFraction;
            }
            c.indexOfPoint = inkValues[currentColor][currentInkZone];
            curveCollection.append(c);
        }

        if (adjustmentQuantity == SUBTLE_ADJUSTMENT){
            if (isIncreasing)
                increasedInkQuantity[currentColor][currentInkZone] ++;
            else
                increasedInkQuantity[currentColor][currentInkZone] --;
        }
        else if (adjustmentQuantity == ROUGH_ADJUSTMENT){
            if (isIncreasing)
                increasedInkQuantity[currentColor][currentInkZone] += inkFraction;
            else
                increasedInkQuantity[currentColor][currentInkZone] -= inkFraction;
        }
        int x = 0;
        switch(color){
        case CYAN:
            x = getAdjustedInkValue(currentPage - 1, CYAN, currentInkZone);
            ui->horizontalSlider_cyanInkValue->setValue(x);
            v.setNum(x / inkFraction);
            v.append(".");
            v.append(v1.setNum(x % inkFraction));
            ui->label_cyanInkValue->setText(v);
            break;
        case MAGENTA:
            x = getAdjustedInkValue(currentPage - 1, MAGENTA, currentInkZone);
            ui->horizontalSlider_magentaInkValue->setValue(x);
            v.setNum(x / inkFraction);
            v.append(".");
            v.append(v1.setNum(x % inkFraction));
            ui->label_magentaInkValue->setText(v);
            break;
        case YELLOW:
            x = getAdjustedInkValue(currentPage - 1, YELLOW, currentInkZone);
            ui->horizontalSlider_yellowInkValue->setValue(x);
            v.setNum(x / inkFraction);
            v.append(".");
            v.append(v1.setNum(x % inkFraction));
            ui->label_yellowInkValue->setText(v);
            break;
        case BLACK:
            x = getAdjustedInkValue(currentPage - 1, BLACK, currentInkZone);
            ui->horizontalSlider_blackInkValue->setValue(x);
            v.setNum(x / inkFraction);
            v.append(".");
            v.append(v1.setNum(x % inkFraction));
            ui->label_blackInkValue->setText(v);
            break;
        case COLOR1:
            x = getAdjustedInkValue(currentPage - 1, COLOR1, currentInkZone);
            ui->horizontalSlider_color1InkValue->setValue(x);
            v.setNum(x / inkFraction);
            v.append(".");
            v.append(v1.setNum(x % inkFraction));
            ui->label_color1InkValue->setText(v);
            break;
        case COLOR2:
            x = getAdjustedInkValue(currentPage - 1, COLOR2, currentInkZone);
            ui->horizontalSlider_color2InkValue->setValue(x);
            v.setNum(x / inkFraction);
            v.append(".");
            v.append(v1.setNum(x % inkFraction));
            ui->label_color2InkValue->setText(v);
            break;
        }
        paintEventId = currentColorShowing;
        update(fountainStartXLocation - inkZoneWidth * (inkKeyQuantity - currentInkZone),
               fountainStartYLocation, inkZoneWidth, VALUE_DISPLAY_HEIGHT);
    }
}
void MainWindow::changeRollerSpeed(int color, bool isIncreasing){
    if (currentPage == 0)
        return;
    QString v;
    int currentColor = (currentPage - 1) * totalColors + color - 1;
    if (isIncreasing){
        if (inkRollerSpeed[currentColor] < 100)
            inkRollerSpeed[currentColor] ++;
    }
    else{
        if (inkRollerSpeed[currentColor] > 10)
            inkRollerSpeed[currentColor] --;
    }
    switch(color){
    case CYAN:
        ui->horizontalSlider_cyanInkValue->setValue(inkRollerSpeed[currentColor]);
        ui->label_cyanInkValue->setText(v.setNum(inkRollerSpeed[currentColor]));
        break;
    case MAGENTA:
        ui->horizontalSlider_magentaInkValue->setValue(inkRollerSpeed[currentColor]);
        ui->label_magentaInkValue->setText(v.setNum(inkRollerSpeed[currentColor]));
        break;
    case YELLOW:
        ui->horizontalSlider_yellowInkValue->setValue(inkRollerSpeed[currentColor]);
        ui->label_yellowInkValue->setText(v.setNum(inkRollerSpeed[currentColor]));
        break;
    case BLACK:
        ui->horizontalSlider_blackInkValue->setValue(inkRollerSpeed[currentColor]);
        ui->label_blackInkValue->setText(v.setNum(inkRollerSpeed[currentColor]));
        break;
    case COLOR1:
        ui->horizontalSlider_color1InkValue->setValue(inkRollerSpeed[currentColor]);
        ui->label_color1InkValue->setText(v.setNum(inkRollerSpeed[currentColor]));
        break;
    case COLOR2:
        ui->horizontalSlider_color2InkValue->setValue(inkRollerSpeed[currentColor]);
        ui->label_color2InkValue->setText(v.setNum(inkRollerSpeed[currentColor]));
        break;
    }
    inkRatio[currentColor] = printingPlateHeight * 10.0 * ink_thickness[currentColor] / (INK_KEY_GAP * inkRollerSpeed[currentColor]);
    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::increaseCyan()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INCREASE_CYAN;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(CYAN, true);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(CYAN, true);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(CYAN, true);
}
void MainWindow::decreaseCyan()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DECREASE_CYAN;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(CYAN, false);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(CYAN, false);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(CYAN, false);
}
void MainWindow::increaseMagenta()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INCREASE_MAGENTA;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(MAGENTA, true);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(MAGENTA, true);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(MAGENTA, true);
}
void MainWindow::decreaseMagenta()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DECREASE_MAGENTA;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(MAGENTA, false);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(MAGENTA, false);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(MAGENTA, false);
}
void MainWindow::increaseYellow()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INCREASE_YELLOW;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(YELLOW, true);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(YELLOW, true);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(YELLOW, true);
}
void MainWindow::decreaseYellow()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DECREASE_YELLOW;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(YELLOW, false);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(YELLOW, false);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(YELLOW, false);
}
void MainWindow::increaseBlack()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INCREASE_BLACK;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(BLACK, true);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(BLACK, true);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(BLACK, true);
}
void MainWindow::decreaseBlack()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DECREASE_BLACK;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (isSingleAdjustment)
        changeInkValue(BLACK, false);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(BLACK, false);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(BLACK, false);
}
void MainWindow::increaseColor1()
{
    if (isOtherInstructionInProcess())
        return;
    if (totalColors <= 4){
        //该机型没有1号专色
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\245\346\234\272\345\236\213\346\262\241\346\234\2111\345\217\267\344\270\223\350\211\262", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INCREASE_COLOR1;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (currentPage == 1){
        if (upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 <= 4)
            return;
        if (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 <= 4)
            return;
    }
    if (currentPage == 2){
        if (lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 <= 4)
            return;
        if (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 <= 4)
            return;
    }

    if (isSingleAdjustment)
        changeInkValue(COLOR1, true);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(COLOR1, true);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(COLOR1, true);
}
void MainWindow::decreaseColor1()
{
    if (isOtherInstructionInProcess())
        return;
    if (totalColors <= 4){
        //该机型没有1号专色
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\245\346\234\272\345\236\213\346\262\241\346\234\2111\345\217\267\344\270\223\350\211\262", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DECREASE_COLOR1;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (currentPage == 1){
        if (upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 <= 4)
            return;
        if (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 <= 4)
            return;
    }
    if (currentPage == 2){
        if (lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 <= 4)
            return;
        if (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 <= 4)
            return;
    }
    if (isSingleAdjustment)
        changeInkValue(COLOR1, false);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(COLOR1, false);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(COLOR1, false);
}
void MainWindow::increaseColor2()
{
    if (isOtherInstructionInProcess())
        return;
    if (totalColors <= 5){
        //该机型没有2号专色
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\245\346\234\272\345\236\213\346\262\241\346\234\2112\345\217\267\344\270\223\350\211\262", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INCREASE_COLOR2;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (currentPage == 1){
        if (upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 <= 5)
            return;
        if (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 <= 5)
            return;
    }
    if (currentPage == 2){
        if (lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 <= 5)
            return;
        if (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 <= 5)
            return;
    }
    if (isSingleAdjustment)
        changeInkValue(COLOR2, true);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(COLOR2, true);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(COLOR2, true);
}
void MainWindow::decreaseColor2()
{
    if (isOtherInstructionInProcess())
        return;
    if (totalColors <= 5){
        //该机型没有2号专色
        isWaitingForUserResponse = true;
        currentColorShowing = CLEAR;
        messageBox->setText(QApplication::translate("MainWindow", "\350\257\245\346\234\272\345\236\213\346\262\241\346\234\2112\345\217\267\344\270\223\350\211\262", 0, QApplication::UnicodeUTF8));
        messageBox->exec();
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DECREASE_COLOR2;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage == 0)
        return;
    if (currentPage == 1){
        if (upperFileFormat == PPF_FORMAT && numberOfColorsInPPF1 <= 5)
            return;
        if (upperFileFormat == TIFF_FORMAT && numberOfColorsInTIF1 <= 5)
            return;
    }
    if (currentPage == 2){
        if (lowerFileFormat == PPF_FORMAT && numberOfColorsInPPF2 <= 5)
            return;
        if (lowerFileFormat == TIFF_FORMAT && numberOfColorsInTIF2 <= 5)
            return;
    }
    if (isSingleAdjustment)
        changeInkValue(COLOR2, false);
    else if (isBasicAdjustment)
        changeBasicInkQuantity(COLOR2, false);
    else if (isRollerSpeedAdjustment)
        changeRollerSpeed(COLOR2, false);
}
void MainWindow::zoomInInkValue()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ZOOM_IN;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (currentPage != 0){
        ui->tabWidget->setVisible(false);

        ui->tabWidget->setVisible(false);
        isTabWidgetVisible = false;
        ui->pushButton_showTabWidget->setGeometry(768, 55, 26, 26);
        ui->pushButton_showTabWidget->setText("<");
        maximum_display_width = 800;

        paintEventId = ZOOMIN;
        update();
    }
}
void MainWindow::changeBasicInkQuantity(int color, bool isIncreasing)
{
    int currentColor = (currentPage - 1) * totalColors + color - 1;
    if (adjustmentQuantity == SUBTLE_ADJUSTMENT){
        if (basicInkValue[currentColor] < inkKeySteps && isIncreasing)
            basicInkValue[currentColor] ++;
        else if (!isIncreasing)
            basicInkValue[currentColor] --;
    }
    else if (adjustmentQuantity == ROUGH_ADJUSTMENT){
        if (basicInkValue[currentColor] < inkKeySteps && isIncreasing)
            basicInkValue[currentColor] += inkFraction;
        else if (!isIncreasing)
            basicInkValue[currentColor] -= inkFraction;
    }
    QString numStr1, numStr2;
    numStr1.setNum(basicInkValue[currentColor] / inkFraction);
    numStr2.setNum(basicInkValue[currentColor] % inkFraction);
    numStr1.append(".").append(numStr2);
    switch(color){
    case CYAN:
        ui->horizontalSlider_cyanInkValue->setValue(basicInkValue[currentColor]);
        ui->label_cyanInkValue->setText(numStr1);
        break;
    case MAGENTA:
        ui->horizontalSlider_magentaInkValue->setValue(basicInkValue[currentColor]);
        ui->label_magentaInkValue->setText(numStr1);
        break;
    case YELLOW:
        ui->horizontalSlider_yellowInkValue->setValue(basicInkValue[currentColor]);
        ui->label_yellowInkValue->setText(numStr1);
        break;
    case BLACK:
        ui->horizontalSlider_blackInkValue->setValue(basicInkValue[currentColor]);
        ui->label_blackInkValue->setText(numStr1);
        break;
    case COLOR1:
        ui->horizontalSlider_color1InkValue->setValue(basicInkValue[currentColor]);
        ui->label_color1InkValue->setText(numStr1);
        break;
    case COLOR2:
        ui->horizontalSlider_color2InkValue->setValue(basicInkValue[currentColor]);
        ui->label_color2InkValue->setText(numStr1);
        break;
    }

    showCurrentInkZone();
    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToRollerSpeedAdjustment()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ADJUST_ROLLER_SPEED;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    isBasicAdjustment = false;
    isSingleAdjustment = false;
    isRollerSpeedAdjustment = true;
    ui->pushButton_adjustRollerSpeed->setEnabled(false);
    ui->pushButton_adjustBasicInk->setEnabled(true);
    ui->pushButton_adjustSingleInk->setEnabled(true);
    showCurrentInkZone();
}
void MainWindow::setToBasicAdjustment()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ADJUST_BASIC_INK;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    isBasicAdjustment = true;
    isSingleAdjustment = false;
    isRollerSpeedAdjustment = false;
    ui->pushButton_adjustRollerSpeed->setEnabled(true);
    ui->pushButton_adjustBasicInk->setEnabled(false);
    ui->pushButton_adjustSingleInk->setEnabled(true);
    showCurrentInkZone();
}
void MainWindow::setToSingleAdjustment()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ADJUST_SINGLE_INK;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    isBasicAdjustment = false;
    isSingleAdjustment = true;
    isRollerSpeedAdjustment = false;
    ui->pushButton_adjustRollerSpeed->setEnabled(true);
    ui->pushButton_adjustBasicInk->setEnabled(true);
    ui->pushButton_adjustSingleInk->setEnabled(false);
    showCurrentInkZone();
}
void MainWindow::setRoughAdjustment()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ROUGH_ADJUST;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    adjustmentQuantity = ROUGH_ADJUSTMENT;
    ui->pushButton_roughAdjust->setEnabled(false);
    ui->pushButton_subtleAdjust->setEnabled(true);
}
void MainWindow::setSubtleAdjustment()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_SUBTLE_ADJUST;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    adjustmentQuantity = SUBTLE_ADJUSTMENT;
    ui->pushButton_roughAdjust->setEnabled(true);
    ui->pushButton_subtleAdjust->setEnabled(false);
}
void MainWindow::switchGroupBox()
{
    if (isEnteringDigitalInput){
        ui->text_ValueOfInput->setText("");
        isEnteringDigitalInput = false;
        digitsOfFractions = -1;
        hasDotEntered = false;
        inputValue = 0;
        if (whichParameterToSet == PARAMETER_IP_ADDRESS)
            ui->widget_ip->setVisible(false);
        else{
            switch(selectedButtonBeforeDigitalInput){
            case WIDGET_ID_INK_KEY_QUANTITY:
                ui->pushButton_KeyNumbers->setDown(false);
                break;
            case WIDGET_ID_FOUNTAIN_WIDTH:
                ui->pushButton_fountainWidth->setDown(false);
                break;
            case WIDGET_ID_FOUNTAIN_HEIGHT:
                ui->pushButton_plateHeight->setDown(false);
                break;
            case WIDGET_ID_MAX_INK_VALUE:
                ui->pushButton_maxInkValue->setDown(false);
                break;
            case WIDGET_ID_INK_FRACTION:
                ui->pushButton_inkFraction->setDown(false);
                break;
            case WIDGET_ID_TOTAL_COLORS:
                ui->pushButton_totalColors->setDown(false);
            }
        }
        whichParameterToSet = 0;
    }
    else if (isSelectingFile || isRevisingAllParameters){
        cancelSelect();
        cancelMachineModelSelection();
        isSelectingFile = false;
        isRevisingAllParameters = false;
        if (isFileListInitialized){
            delete fileList;
            fileList = NULL;
            isFileListInitialized = false;
        }
        fileName.clear();
    }
    else if (isDeletingFile){
        cancelSelect();
        isDeletingFile = false;
        if (isFileListInitialized){
            delete fileList;
            fileList = NULL;
            isFileListInitialized = false;
        }
    }
    switch(ui->tabWidget->currentIndex()){
    case 0:
        tabIndex = 0;
        previouslySelectedButton = selectedButton;
        selectedButton = WIDGET_ID_OPEN_FILE;
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        break;
    case 1:
        tabIndex = 1;
        previouslySelectedButton = selectedButton;
        selectedButton = WIDGET_ID_UPPER_SIDE;
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        break;
    case 2:
        tabIndex = 2;
        previouslySelectedButton = selectedButton;
        selectedButton = WIDGET_ID_LAST_INK_ZONE;
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
        if (adjustmentQuantity == ROUGH_ADJUSTMENT){
            ui->pushButton_roughAdjust->setEnabled(false);
            ui->pushButton_subtleAdjust->setEnabled(true);
        }
        else if (adjustmentQuantity == SUBTLE_ADJUSTMENT){
            ui->pushButton_roughAdjust->setEnabled(true);
            ui->pushButton_subtleAdjust->setEnabled(false);
        }
        showCurrentInkZone();
        break;
    case 3:
        tabIndex = 3;
        previouslySelectedButton = selectedButton;
        selectedButton = WIDGET_ID_INK1;
        changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    }
}
void MainWindow::setToOneSide()
{
    if (isOtherInstructionInProcess()){
        ui->radioButton_oneSide->setChecked(false);
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ONE_SIDE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    numberOfSides = 1;
}
void MainWindow::setToTwoSides()
{
    if (isOtherInstructionInProcess()){
        ui->radioButton_twoSides->setChecked(false);
        return;
    }
    if (totalColors > 4){
        currentColorShowing = CLEAR;
        isWaitingForUserResponse = true;
        messageBox->setText("正反两面机型只支持最多每面4种颜色");
        messageBox->exec();
        return;
    }
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_TWO_SIDES;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    numberOfSides = 2;
}
void MainWindow::setParameter_inkKeyValues()
{
    if (isOtherInstructionInProcess())
        return;
    ui->text_numOfInkKeys->setText("");
    isEnteringDigitalInput = true;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INK_KEY_QUANTITY;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);


    selectedButton = WIDGET_ID_INK_KEY_QUANTITY;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    whichParameterToSet = PARAMETER_INK_KEY_QUANTITY;
    inkKeyQuantity = 0;
    ui->pushButton_KeyNumbers->setDown(true);
}
void MainWindow::setParameter_fountainWidth()
{
    if (isOtherInstructionInProcess())
        return;
    ui->text_fountainWidth->setText("");
    isEnteringDigitalInput = true;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_FOUNTAIN_WIDTH;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    selectedButton = WIDGET_ID_FOUNTAIN_WIDTH;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    whichParameterToSet = PARAMETER_FOUNTAIN_WIDTH;
    ui->pushButton_fountainWidth->setDown(true);
}
void MainWindow::setParameter_plateHeight()
{
    if (isOtherInstructionInProcess())
        return;
    ui->text_plateHeight->setText("");
    isEnteringDigitalInput = true;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_FOUNTAIN_HEIGHT;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    selectedButton = WIDGET_ID_FOUNTAIN_HEIGHT;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    whichParameterToSet = PARAMETER_FOUNTAIN_HEIGHT;
    ui->pushButton_plateHeight->setDown(true);
}
void MainWindow::setParameter_maxInkValue()
{
    if (isOtherInstructionInProcess())
        return;
    ui->text_maxInkValue->setText("");
    isEnteringDigitalInput = true;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_MAX_INK_VALUE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    selectedButton = WIDGET_ID_MAX_INK_VALUE;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    whichParameterToSet = PARAMETER_MAX_INK_VALUE;
    ui->pushButton_maxInkValue->setDown(true);
}
void MainWindow::setParameter_inkFraction()
{
    if (isOtherInstructionInProcess())
        return;
    ui->text_inkFraction->setText("");
    isEnteringDigitalInput = true;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INK_FRACTION;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    selectedButton = WIDGET_ID_INK_FRACTION;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    whichParameterToSet = PARAMETER_INK_FRACTION;
    ui->pushButton_inkFraction->setDown(true);
}
void MainWindow::setParameter_totalColors()
{
    if (isOtherInstructionInProcess())
        return;
    ui->text_totalColors->setText("");
    isEnteringDigitalInput = true;

    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_TOTAL_COLORS;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    selectedButton = WIDGET_ID_TOTAL_COLORS;
    selectedButtonBeforeDigitalInput = selectedButton;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    whichParameterToSet = PARAMETER_TOTAL_COLORS;
    ui->pushButton_totalColors->setDown(true);
}
void MainWindow::inputDot()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_DOT;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    if (whichParameterToSet >= PARAMETER_INK_KEY_QUANTITY && whichParameterToSet <= PARAMETER_TOTAL_COLORS){
        switch(whichParameterToSet){
        case PARAMETER_INK_KEY_QUANTITY:
            ui->pushButton_KeyNumbers->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_WIDTH:
            ui->pushButton_fountainWidth->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_HEIGHT:
            ui->pushButton_plateHeight->setDown(true);
            break;
        case PARAMETER_MAX_INK_VALUE:
            ui->pushButton_maxInkValue->setDown(true);
            break;
        case PARAMETER_INK_FRACTION:
            ui->pushButton_inkFraction->setDown(true);
            break;
        case PARAMETER_TOTAL_COLORS:
            ui->pushButton_totalColors->setDown(true);
        }
        digitsOfFractions ++;
        hasDotEntered = true;
        QString numStr;
        numStr.setNum(inputValue);
        numStr.append(".");
        ui->text_ValueOfInput->setText(numStr);
    }
    else if (whichParameterToSet == PARAMETER_IP_ADDRESS){
        serverAddress.append(".");
        ui->lineEdit_ipAddress->setText(serverAddress);
    }
}
void MainWindow::inputDelete()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_DELETE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    if (whichParameterToSet >= PARAMETER_INK_KEY_QUANTITY && whichParameterToSet <= PARAMETER_TOTAL_COLORS){
        switch(whichParameterToSet){
        case PARAMETER_INK_KEY_QUANTITY:
            ui->pushButton_KeyNumbers->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_WIDTH:
            ui->pushButton_fountainWidth->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_HEIGHT:
            ui->pushButton_plateHeight->setDown(true);
            break;
        case PARAMETER_MAX_INK_VALUE:
            ui->pushButton_maxInkValue->setDown(true);
            break;
        case PARAMETER_INK_FRACTION:
            ui->pushButton_inkFraction->setDown(true);
            break;
        case PARAMETER_TOTAL_COLORS:
            ui->pushButton_totalColors->setDown(true);
        }
        QString numStr;
        if (hasDotEntered){
            int temp = (int)(inputValue * powerOfTen(digitsOfFractions - 1));
            inputValue = (float)temp / powerOfTen(digitsOfFractions - 1);
            digitsOfFractions --;
            numStr.setNum(inputValue);
            if (digitsOfFractions == 0){
                numStr.append(".");
            }
            else if (digitsOfFractions == -1){
                hasDotEntered = false;
            }
        }
        else{
            inputValue = (int)inputValue / 10;
            numStr.setNum(inputValue);
        }
        if (hasDotEntered &&
            (inputValue == (int)inputValue) &&
            digitsOfFractions == 1){
            numStr.append(".");
            numStr.append("0");
        }
        ui->text_ValueOfInput->setText(numStr);
    }
    else if (whichParameterToSet == PARAMETER_IP_ADDRESS){
        serverAddress.chop(1);
        ui->lineEdit_ipAddress->setText(serverAddress);
    }
}
void MainWindow::inputEnter()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_ENTER;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    if (whichParameterToSet == PARAMETER_INK_KEY_QUANTITY){
        if (inputValue > 50 || inputValue <= 0){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //参数值无效，请输入正确的墨键数量
            messageBox->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\345\200\274\346\227\240\346\225\210\357\274\214\350\257\267\350\276\223\345\205\245\346\255\243\347\241\256\347\232\204\345\242\250\351\224\256\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            digitsOfFractions = -1;
            hasDotEntered = false;
            return;
        }
        QString numStr;
        numStr.setNum((int)inputValue);
        ui->text_numOfInkKeys->setText(numStr);
        ui->text_ValueOfInput->setText("");
        ui->pushButton_KeyNumbers->setDown(false);
        whichParameterToSet = 0;
        inkKeyQuantity = (int)inputValue;
        inputValue = 0;
        digitsOfFractions = -1;
        hasDotEntered = false;
    }
    else if (whichParameterToSet == PARAMETER_FOUNTAIN_WIDTH){
        if (inputValue > 200 || inputValue <= 0){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //参数值无效，请输入正确的墨斗宽度
            messageBox->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\345\200\274\346\227\240\346\225\210\357\274\214\350\257\267\350\276\223\345\205\245\346\255\243\347\241\256\347\232\204\345\242\250\346\226\227\345\256\275\345\272\246", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            digitsOfFractions = -1;
            hasDotEntered = false;
            return;
        }
        inkFountainWidth = inputValue;
        inputValue = 0;
        digitsOfFractions = -1;
        hasDotEntered = false;
        QString numStr;
        numStr.setNum(inkFountainWidth);
        numStr.append(" cm");
        ui->text_fountainWidth->setText(numStr);

        ui->text_ValueOfInput->setText("");
        ui->pushButton_fountainWidth->setDown(false);
        whichParameterToSet = 0;
    }
    else if (whichParameterToSet == PARAMETER_FOUNTAIN_HEIGHT){
        if (inputValue > 200 || inputValue <= 0){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //参数值无效，请输入正确的墨斗长度
            messageBox->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\345\200\274\346\227\240\346\225\210\357\274\214\350\257\267\350\276\223\345\205\245\346\255\243\347\241\256\347\232\204\345\242\250\346\226\227\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            digitsOfFractions = -1;
            hasDotEntered = false;
            return;
        }
        printingPlateHeight = inputValue;
        inputValue = 0;
        digitsOfFractions = -1;
        hasDotEntered = false;
        QString numStr;
        numStr.setNum(printingPlateHeight);
        numStr.append(" cm");
        ui->text_plateHeight->setText(numStr);

        ui->text_ValueOfInput->setText("");
        ui->pushButton_plateHeight->setDown(false);
        whichParameterToSet = 0;
    }
    else if (whichParameterToSet == PARAMETER_MAX_INK_VALUE){
        if (inputValue > 200 || inputValue <= 0){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //参数值无效，请输入正确的墨键最大开度
            messageBox->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\345\200\274\346\227\240\346\225\210\357\274\214\350\257\267\350\276\223\345\205\245\346\255\243\347\241\256\347\232\204\345\242\250\351\224\256\346\234\200\345\244\247\345\274\200\345\272\246", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            digitsOfFractions = -1;
            hasDotEntered = false;
            return;
        }
        maxInkValue = (int)inputValue;
        inputValue = 0;
        digitsOfFractions = -1;
        hasDotEntered = false;
        QString numStr;
        numStr.setNum(maxInkValue);
        ui->text_maxInkValue->setText(numStr);

        ui->text_ValueOfInput->setText("");
        ui->pushButton_maxInkValue->setDown(false);
        whichParameterToSet = 0;
    }
    else if (whichParameterToSet == PARAMETER_INK_FRACTION){
        if (inputValue > 100 || inputValue <= 0){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            //参数值无效，请输入正确的墨键开度小数部分最大值
            messageBox->setText(QApplication::translate("MainWindow", "\345\217\202\346\225\260\345\200\274\346\227\240\346\225\210\357\274\214\350\257\267\350\276\223\345\205\245\346\255\243\347\241\256\347\232\204\345\242\250\351\224\256\345\274\200\345\272\246\345\260\217\346\225\260\351\203\250\345\210\206\346\234\200\345\244\247\345\200\274", 0, QApplication::UnicodeUTF8));
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            inkFraction = 0;
            return;
        }
        inkFraction = (int)inputValue;
        QString numStr;
        numStr.setNum(inkFraction);
        ui->text_inkFraction->setText(numStr);
        ui->text_ValueOfInput->setText("");
        ui->pushButton_inkFraction->setDown(false);
        whichParameterToSet = 0;
        inputValue = 0;
        digitsOfFractions = -1;
        hasDotEntered = false;
    }
    else if (whichParameterToSet == PARAMETER_TOTAL_COLORS){
        if (inputValue > 6 || inputValue < 4){
            isWaitingForUserResponse = true;
            currentColorShowing = CLEAR;
            messageBox->setText("只支持4-6种颜色");
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            inkFraction = 0;
            return;
        }
        if (inputValue > 4 && numberOfSides == 2){
            currentColorShowing = CLEAR;
            isWaitingForUserResponse = true;
            messageBox->setText("正反两面机型只支持最多每面4种颜色");
            messageBox->exec();
            ui->text_ValueOfInput->setText("");
            inputValue = 0;
            inkFraction = 0;
            return;
        }
        totalColors = (int)inputValue;
        QString numStr;
        numStr.setNum(totalColors);
        ui->text_totalColors->setText(numStr);
        ui->text_ValueOfInput->setText("");
        ui->pushButton_totalColors->setDown(false);
        whichParameterToSet = 0;
        inputValue = 0;
        digitsOfFractions = -1;
        hasDotEntered = false;
    }
    else if (whichParameterToSet == PARAMETER_IP_ADDRESS){
        connectServer();
    }
    isEnteringDigitalInput = false;
    previouslySelectedButton = selectedButton;
    selectedButton = selectedButtonBeforeDigitalInput;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
}
void MainWindow::addDigit(int n)
{
    QString numStr;

    if (whichParameterToSet >= PARAMETER_INK_KEY_QUANTITY && whichParameterToSet <= PARAMETER_TOTAL_COLORS){
        switch(whichParameterToSet){
        case PARAMETER_INK_KEY_QUANTITY:
            ui->pushButton_KeyNumbers->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_WIDTH:
            ui->pushButton_fountainWidth->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_HEIGHT:
            ui->pushButton_plateHeight->setDown(true);
            break;
        case PARAMETER_MAX_INK_VALUE:
            ui->pushButton_maxInkValue->setDown(true);
            break;
        case PARAMETER_INK_FRACTION:
            ui->pushButton_inkFraction->setDown(true);
            break;
        case PARAMETER_TOTAL_COLORS:
            ui->pushButton_totalColors->setDown(true);
        }
        if (hasDotEntered){
            digitsOfFractions ++;
            inputValue += n * dividedByTen(digitsOfFractions);
        }
        else{
            inputValue *= 10;
            inputValue += n;
        }
        numStr.setNum(inputValue);
        ui->text_ValueOfInput->setText(numStr);
    }
    else if (whichParameterToSet == PARAMETER_IP_ADDRESS){
        serverAddress.append(numStr.setNum(n));
        ui->lineEdit_ipAddress->setText(serverAddress);
    }
}
void MainWindow::inputZero()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ZERO;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    if (whichParameterToSet >= PARAMETER_INK_KEY_QUANTITY && whichParameterToSet <= PARAMETER_TOTAL_COLORS){
        switch(whichParameterToSet){
        case PARAMETER_INK_KEY_QUANTITY:
            ui->pushButton_KeyNumbers->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_WIDTH:
            ui->pushButton_fountainWidth->setDown(true);
            break;
        case PARAMETER_FOUNTAIN_HEIGHT:
            ui->pushButton_plateHeight->setDown(true);
            break;
        case PARAMETER_MAX_INK_VALUE:
            ui->pushButton_maxInkValue->setDown(true);
            break;
        case PARAMETER_INK_FRACTION:
            ui->pushButton_inkFraction->setDown(true);
            break;
        case PARAMETER_TOTAL_COLORS:
            ui->pushButton_totalColors->setDown(true);
        }
        QString numStr;
        if (hasDotEntered){
            digitsOfFractions ++;
            numStr.setNum(inputValue);
            if (digitsOfFractions == 1)
                numStr.append(".");
            numStr.append("0");
        }
        else{
            inputValue *= 10;
            numStr.setNum(inputValue);
        }
        ui->text_ValueOfInput->setText(numStr);
    }
    else if (whichParameterToSet == PARAMETER_IP_ADDRESS){
        serverAddress.append("0");
        ui->lineEdit_ipAddress->setText(serverAddress);
    }
}
void MainWindow::inputNine()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_NINE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(9);
}
void MainWindow::inputEight()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_EIGHT;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(8);
}
void MainWindow::inputSeven()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_SEVEN;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(7);
}
void MainWindow::inputSix()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_SIX;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(6);
}
void MainWindow::inputFive()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_FIVE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(5);
}
void MainWindow::inputFour()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_FOUR;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(4);
}
void MainWindow::inputThree()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_THREE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(3);
}
void MainWindow::inputTwo()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_TWO;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(2);
}
void MainWindow::inputOne()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INPUT_ONE;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    addDigit(1);
}
void MainWindow::setToInk1()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INK1;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    inkType = 1;
    ui->radioButton_Ink1->setChecked(true);

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToInk2()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INK2;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    inkType = 2;
    ui->radioButton_Ink2->setChecked(true);

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToInk3()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INK3;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    inkType = 3;
    ui->radioButton_Ink3->setChecked(true);

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToInk4()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_INK4;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    inkType = 4;
    ui->radioButton_Ink4->setChecked(true);

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::calculateInkRatio()
{
    for (int i = 0; i < 8; i ++){
        if (ink_thickness[i] >= 0.004){      //to prevent the inkRatio to be too large
            if ((inkRollerSpeed[i] * 2) <= 100){
                inkRollerSpeed[i] *= 2;
            }
        }
        else if (ink_thickness[i] >= 0.003){
            float tempInkRollerSpeed = (float)inkRollerSpeed[i] * 1.5;
            if (tempInkRollerSpeed <= 100)
                inkRollerSpeed[i] = (int)tempInkRollerSpeed;
        }
        else if (ink_thickness[i] <= 0.002){
            if (inkRollerSpeed[i] >= 60){
                inkRollerSpeed[i] = 30;         //change back to default value
            }
            else if (inkRollerSpeed[i] >=45){
                float tempInkRollerSpeed = (float)inkRollerSpeed[i] / 1.5;
                inkRollerSpeed[i] = (int)tempInkRollerSpeed;
            }
        }
        inkRatio[i] = printingPlateHeight * 10.0 * ink_thickness[i] / (INK_KEY_GAP * (float)inkRollerSpeed[i]);
    }
}
void MainWindow::setToPaper1()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_PAPER1;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    paperType = 1;

    //高光涂料纸
    if (numberOfSides == 1){
        ink_thickness[0] = 0.001;       //cyan
        ink_thickness[1] = 0.001;       //magenta
        ink_thickness[2] = 0.001;       //yellow
        ink_thickness[3] = 0.001;       //black
        ink_thickness[4] = 0.001;       //special color1
        ink_thickness[5] = 0.001;       //special color2
    }
    else{
        ink_thickness[0] = 0.001;       //upper cyan
        ink_thickness[1] = 0.001;       //upper magenta
        ink_thickness[2] = 0.001;       //upper yellow
        ink_thickness[3] = 0.001;       //upper black

        ink_thickness[4] = 0.001;       //lower cyan
        ink_thickness[5] = 0.001;       //lower magenta
        ink_thickness[6] = 0.001;       //lower yellow
        ink_thickness[7] = 0.001;       //lower black
    }
    ui->verticalSlider_cyanInkThickness->setValue(10);
    ui->label_cyanInkThickness->setText("33");
    ui->verticalSlider_magentaInkThickness->setValue(10);
    ui->label_magentaInkThickness->setText("40");
    ui->verticalSlider_yellowInkThickness->setValue(10);
    ui->label_yellowInkThickness->setText("40");
    ui->verticalSlider_blackInkThickness->setValue(10);
    ui->label_blackInkThickness->setText("25");

    ui->radioButton_paper1->setChecked(true);
    ui->radioButton_paper2->setChecked(false);
    ui->radioButton_paper3->setChecked(false);
    ui->radioButton_paper4->setChecked(false);

    calculateInkRatio();

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToPaper2()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_PAPER2;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    paperType = 2;

    //哑光涂料纸
    if (numberOfSides == 1){
        ink_thickness[0] = 0.0014;      //cyan
        ink_thickness[1] = 0.0013;      //magenta
        ink_thickness[2] = 0.0012;      //yellow
        ink_thickness[3] = 0.002;       //black
        ink_thickness[4] = 0.002;       //special color1
        ink_thickness[5] = 0.002;       //special color2
    }
    else{
        ink_thickness[0] = 0.0014;      //upper cyan
        ink_thickness[1] = 0.0013;      //upper magenta
        ink_thickness[2] = 0.0012;      //upper yellow
        ink_thickness[3] = 0.002;       //upper black

        ink_thickness[4] = 0.0014;      //lower cyan
        ink_thickness[5] = 0.0013;      //lower magenta
        ink_thickness[6] = 0.0012;      //lower yellow
        ink_thickness[7] = 0.002;       //lower black
    }
    ui->verticalSlider_cyanInkThickness->setValue(14);
    ui->label_cyanInkThickness->setText("46");
    ui->verticalSlider_magentaInkThickness->setValue(13);
    ui->label_magentaInkThickness->setText("52");
    ui->verticalSlider_yellowInkThickness->setValue(12);
    ui->label_yellowInkThickness->setText("48");
    ui->verticalSlider_blackInkThickness->setValue(20);
    ui->label_blackInkThickness->setText("50");

    ui->radioButton_paper1->setChecked(false);
    ui->radioButton_paper2->setChecked(true);
    ui->radioButton_paper3->setChecked(false);
    ui->radioButton_paper4->setChecked(false);

    calculateInkRatio();

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToPaper3()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_PAPER3;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    paperType = 3;

    //非涂料纸
    if (numberOfSides == 1){
        ink_thickness[0] = 0.0023;       //cyan
        ink_thickness[1] = 0.0018;       //magenta
        ink_thickness[2] = 0.0017;       //yellow
        ink_thickness[3] = 0.0032;       //black
        ink_thickness[4] = 0.0032;       //special color1
        ink_thickness[5] = 0.0032;       //special color2
    }
    else {
        ink_thickness[0] = 0.0023;       //upper cyan
        ink_thickness[1] = 0.0018;       //upper magenta
        ink_thickness[2] = 0.0017;       //upper yellow
        ink_thickness[3] = 0.0032;       //upper black

        ink_thickness[4] = 0.0023;       //lower cyan
        ink_thickness[5] = 0.0018;       //lower magenta
        ink_thickness[6] = 0.0017;       //lower yellow
        ink_thickness[7] = 0.0032;       //lower black
    }
    ui->verticalSlider_cyanInkThickness->setValue(23);
    ui->label_cyanInkThickness->setText("76");
    ui->verticalSlider_magentaInkThickness->setValue(18);
    ui->label_magentaInkThickness->setText("72");
    ui->verticalSlider_yellowInkThickness->setValue(17);
    ui->label_yellowInkThickness->setText("68");
    ui->verticalSlider_blackInkThickness->setValue(32);
    ui->label_blackInkThickness->setText("80");

    ui->radioButton_paper1->setChecked(false);
    ui->radioButton_paper2->setChecked(false);
    ui->radioButton_paper3->setChecked(true);
    ui->radioButton_paper4->setChecked(false);

    calculateInkRatio();

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::setToPaper4()
{
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_PAPER4;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    paperType = 4;

    //新闻纸
    if (numberOfSides == 1){
        ink_thickness[0] = 0.003;       //cyan
        ink_thickness[1] = 0.0025;      //magenta
        ink_thickness[2] = 0.0025;      //yellow
        ink_thickness[3] = 0.004;       //black
        ink_thickness[4] = 0.004;       //special color1
        ink_thickness[5] = 0.004;       //special color2
    }
    else {
        ink_thickness[0] = 0.003;       //upper cyan
        ink_thickness[1] = 0.0025;      //upper magenta
        ink_thickness[2] = 0.0025;      //upper yellow
        ink_thickness[3] = 0.004;       //upper black

        ink_thickness[4] = 0.003;       //lower cyan
        ink_thickness[5] = 0.0025;      //lower magenta
        ink_thickness[6] = 0.0025;      //lower yellow
        ink_thickness[7] = 0.004;       //lower black
    }
    ui->verticalSlider_cyanInkThickness->setValue(30);
    ui->label_cyanInkThickness->setText("100");
    ui->verticalSlider_magentaInkThickness->setValue(25);
    ui->label_magentaInkThickness->setText("100");
    ui->verticalSlider_yellowInkThickness->setValue(25);
    ui->label_yellowInkThickness->setText("100");
    ui->verticalSlider_blackInkThickness->setValue(40);
    ui->label_blackInkThickness->setText("100");

    ui->radioButton_paper1->setChecked(false);
    ui->radioButton_paper2->setChecked(false);
    ui->radioButton_paper3->setChecked(false);
    ui->radioButton_paper4->setChecked(true);

    calculateInkRatio();

    paintEventId = currentColorShowing;
    update(0, VALUE_START_Y_LOCATION, maximum_display_width, VALUE_DISPLAY_HEIGHT);
}
void MainWindow::reviseParameters()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_REVISE_PARAMETER;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);
    if (!isTabWidgetVisible){
        ui->tabWidget->setVisible(true);
        isTabWidgetVisible = true;
        ui->pushButton_showTabWidget->setGeometry(556, 55, 26, 26);
        ui->pushButton_showTabWidget->setText(">");
        maximum_display_width = 590;
    }
    isRevisingAllParameters = true;

    currentColorShowing = CLEAR;
    update();

    fileList = new QListWidget();
    isFileListInitialized = true;
    ui->scrollArea_machineModel->setWidget(fileList);

    QListWidgetItem *item = new QListWidgetItem(QApplication::translate("MainWindow", "\350\207\252\350\241\214\350\256\276\345\256\232\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8), fileList);
    fileList->addItem(item);
    item = new QListWidgetItem("Heidelberg 102V", fileList);
    fileList->addItem(item);
    item = new QListWidgetItem("Lithrone LS440", fileList);
    fileList->addItem(item);
    item = new QListWidgetItem("Heidelberg PM74", fileList);
    fileList->addItem(item);
    item = new QListWidgetItem("Lithrone 40", fileList);
    fileList->addItem(item);

    selectedButton = NUMBER_OF_TOTAL_WIDGET + 1;

    ui->pushButton_selectMachineModel->setEnabled(false);
    ui->widget_machineModel->setVisible(true);
    connect(fileList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(setSelectedFileIndex(QListWidgetItem*)));
}
void MainWindow::writeInkInfoToFile()
{
    if (isMemoryForColorOffsetValid){
        FILE *configFile = NULL;
        switch(machineModel)
        {
        case 0:
            configFile = fopen("/opt/PDA/bin/ink0.configure", "wb");
            break;
        case 1:
            configFile = fopen("/opt/PDA/bin/ink1.configure", "wb");
            break;
        case 2:
            configFile = fopen("/opt/PDA/bin/ink2.configure", "wb");
            break;
        case 3:
            configFile = fopen("/opt/PDA/bin/ink3.configure", "wb");
            break;
        case 4:
            configFile = fopen("/opt/PDA/bin/ink4.configure", "wb");
            break;
        }

        if (configFile == NULL){
            switch(machineModel)
            {
            case 0:
                configFile = fopen("/opt/PDA/bin/ink0.configure", "w+");
                break;
            case 1:
                configFile = fopen("/opt/PDA/bin/ink1.configure", "w+");
                break;
            case 2:
                configFile = fopen("/opt/PDA/bin/ink2.configure", "w+");
                break;
            case 3:
                configFile = fopen("/opt/PDA/bin/ink3.configure", "w+");
                break;
            case 4:
                configFile = fopen("/opt/PDA/bin/ink4.configure", "w+");
                break;
            }
        }
        int j, k, l, size;

        fputc((char)totalColors, configFile);
        fputc((char)inkType, configFile);
        fputc((char)paperType, configFile);
        fputc((char)numberOfSides, configFile);
        fputc((char)inkKeyQuantity, configFile);
        int w = (int)(inkFountainWidth * 10);
        char w1 = (char)(w & 0xff);
        char w2 = w >> 8;
        fputc(w2, configFile);
        fputc(w1, configFile);
        w = (int)(printingPlateHeight * 10);
        w1 = (char)(w & 0xff);
        w2 = w >> 8;
        fputc(w2, configFile);
        fputc(w1, configFile);
        fputc(maxInkValue, configFile);
        fputc(inkFraction, configFile);
        for (int i = 0; i < 8; i ++)
            fputc(inkRollerSpeed[i], configFile);
        for (int i = 0; i < 8; i ++){
            if (basicInkValue[i] < 0)
                fputc(2, configFile);
            else
                fputc(1, configFile);
            fputc((char)abs(basicInkValue[i]), configFile);
            fputc((char)(abs(basicInkValue[i]) >> 8), configFile);
        }

        int colorQuantity = 0;
        if (numberOfSides == 2)
            colorQuantity = 8;
        else if (numberOfSides == 1)
            colorQuantity = totalColors;

        for (k = 0; k < colorQuantity; k ++){
            for (j = 0; j <= inkKeySteps; j ++){
                fputc(inkCurve[k][j], configFile);
                fputc(inkCurve[k][j] >> 8, configFile);
            }
            size = changedPoints[k].size();
            fputc(size, configFile);
            for (l = 0; l < size; l ++){
                fputc(changedPoints[k][l], configFile);
                fputc(changedPoints[k][l] >> 8, configFile);
            }
        }
        fclose(configFile);
    }
}
void MainWindow::collectMemoryGarbage()
{
    int size = curveCollection.size();
    for (int i = 0; i < size; i ++){
        if (curveCollection[i].increasedQuantity != 0)
            smoothCurve(curveCollection[i]);
    }
    if (isUpperFileOpened && (upperFileFormat == PPF_FORMAT)){
        delete ph1;
        ph1 = NULL;
        numberOfColorsInPPF1 = 0;
    }
    if (isLowerFileOpened && (lowerFileFormat == PPF_FORMAT)){
        delete ph2;
        ph2 = NULL;
        numberOfColorsInPPF2 = 0;
    }
    if (isUpperFileOpened && (upperFileFormat == TIFF_FORMAT)){
        delete th1;
        th1 = NULL;
        numberOfColorsInTIF1 = 0;
    }
    if (isLowerFileOpened && (lowerFileFormat == TIFF_FORMAT)){
        delete th2;
        th2 = NULL;
        numberOfColorsInTIF2 = 0;
    }
    if (isMemoryForColorOffsetValid){
        FILE *configFile = NULL;
        switch(machineModel)
        {
        case 0:
            configFile = fopen("/opt/PDA/bin/ink0.configure", "wb");
            break;
        case 1:
            configFile = fopen("/opt/PDA/bin/ink1.configure", "wb");
            break;
        case 2:
            configFile = fopen("/opt/PDA/bin/ink2.configure", "wb");
            break;
        case 3:
            configFile = fopen("/opt/PDA/bin/ink3.configure", "wb");
            break;
        case 4:
            configFile = fopen("/opt/PDA/bin/ink4.configure", "wb");
            break;
        }
        if (configFile == NULL){
            switch(machineModel)
            {
            case 0:
                configFile = fopen("/opt/PDA/bin/ink0.configure", "w+");
                break;
            case 1:
                configFile = fopen("/opt/PDA/bin/ink1.configure", "w+");
                break;
            case 2:
                configFile = fopen("/opt/PDA/bin/ink2.configure", "w+");
                break;
            case 3:
                configFile = fopen("/opt/PDA/bin/ink3.configure", "w+");
                break;
            case 4:
                configFile = fopen("/opt/PDA/bin/ink4.configure", "w+");
            }
        }
        int j, k, l, size;

        fputc((char)totalColors, configFile);
        fputc((char)inkType, configFile);
        fputc((char)paperType, configFile);
        fputc((char)numberOfSides, configFile);
        fputc((char)inkKeyQuantity, configFile);
        int w = (int)(inkFountainWidth * 10);
        char w1 = (char)(w & 0xff);
        char w2 = w >> 8;
        fputc(w2, configFile);
        fputc(w1, configFile);
        w = (int)(printingPlateHeight * 10);
        w1 = (char)(w & 0xff);
        w2 = w >> 8;
        fputc(w2, configFile);
        fputc(w1, configFile);
        fputc(maxInkValue, configFile);
        fputc(inkFraction, configFile);
        for (int i = 0; i < 8; i ++)
            fputc(inkRollerSpeed[i], configFile);
        for (int i = 0; i < 8; i ++){
            if (basicInkValue[i] < 0)
                fputc(2, configFile);
            else
                fputc(1, configFile);
            fputc((char)abs(basicInkValue[i]), configFile);
            fputc((char)(abs(basicInkValue[i]) >> 8), configFile);
        }
        int colorQuantity = 0;
        if (numberOfSides == 1)
            colorQuantity = totalColors;
        else if (numberOfSides == 2)
            colorQuantity = 8;

        for (k = 0; k < colorQuantity; k ++){
            for (j = 0; j <= inkKeySteps; j ++){
                fputc(inkCurve[k][j], configFile);
                fputc(inkCurve[k][j] >> 8, configFile);
            }
            size = changedPoints[k].size();
            fputc(size, configFile);
            for (l = 0; l < size; l ++){
                fputc(changedPoints[k][l], configFile);
                fputc(changedPoints[k][l] >> 8, configFile);
            }
        }
        fclose(configFile);
    }
    ui->lineEdit_currentInkZone->setText("1");
    ui->horizontalSlider_cyanInkValue->setValue(0);
    ui->horizontalSlider_magentaInkValue->setValue(0);
    ui->horizontalSlider_yellowInkValue->setValue(0);
    ui->horizontalSlider_blackInkValue->setValue(0);
    ui->horizontalSlider_color1InkValue->setValue(0);
    ui->horizontalSlider_color2InkValue->setValue(0);
    ui->label_cyanInkValue->setText("0.0");
    ui->label_magentaInkValue->setText("0.0");
    ui->label_yellowInkValue->setText("0.0");
    ui->label_blackInkValue->setText("0.0");
    ui->label_color1InkValue->setText("0.0");
    ui->label_color2InkValue->setText("0.0");
    ui->radioButton_upperSide->setChecked(false);
    ui->radioButton_lowerSide->setChecked(false);
    currentInkZone = 0;
    numOfCharactersReceived = 0;
    blockSize = 0;
    isUpperFileOpened = false;
    isLowerFileOpened = false;
    curveCollection.clear();
    hasDotEntered = false;
    inputValue = 0;
    numOfPagesOpened = 0;
    currentPage = 0;
    currentColorShowing = 0;
    digitsOfFractions = -1;
    whichParameterToSet = 0;
    paintEventId = 0;

    numOfAvailableContents = 0;
    numOfContentsFromUSB = 0;
    numOfContentsFromREMOTE = 0;

    isFileFromUSB = false;
    isFileFromREMOTE = false;

    previousXCoord = 0;
    previousYCoord = 0;
    currentXCoord = 0;
    currentYCoord = 0;
    upperLeftImageXCoord = 0;
    upperLeftImageYCoord = 0;

    rotateAngle_upper = 0;
    horizontallyFlipped_upper = false;
    rotateAngle_lower = 0;
    horizontallyFlipped_lower = false;

    fileName.clear();

    if (isIncreasedInkQuantityValid){
        increasedInkQuantity.clear();
        isIncreasedInkQuantityValid = false;
    }
    QList<short> qlist5;
    for (int i = 0; i < inkKeyQuantity; i ++)
        qlist5.append(0);
    for(int i = 0; i < totalColors * numberOfSides; i ++)
        increasedInkQuantity.append(qlist5);

    isIncreasedInkQuantityValid = true;

    //clear all that has painted
    paintEventId =CLEAR;
    update();
}
int MainWindow::powerOfTen(int n){
    int i = 0;
    int result = 1;
    for (; i < n; i ++)
        result = result * 10;
    return result;
}
double MainWindow::dividedByTen(int n){
    double result = 1;
    int i;
    for (i = 0; i < n; i ++)
        result /= 10;
    return result;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QString temp;
    QFont textFont = painter.font();
    textFont.setPointSize(10);
    textFont.setBold(true);
    painter.setFont(textFont);

    if (paintEventId == CLEAR){
        paintEventId = -1;        
        painter.fillRect(0, 0, maximum_display_width, FULLSCREEN_HEIGHT - TOOLBAR_HEIGHT, QColor::fromRgb(255, 255, 255));
        return;
    }
    else if ((paintEventId == CYAN) ||
             (paintEventId == MAGENTA) ||
             (paintEventId == YELLOW) ||
             (paintEventId == BLACK) ||
             (paintEventId == COLOR1) ||
             (paintEventId == COLOR2) ||
             (paintEventId == UPPER) ||
             (paintEventId == LOWER)){
        int rotateAngle = 0;
        bool horizontallyFlipped = false;
        bool isMixedColor = false;
        QColor componentColor;
        QImage *thumbnail = NULL;
        QPen *pen = new QPen();
        int imageDirection = 0;
        float tempResult = 0.0;
        int thumbnailLocation = 0;
        int originalImageWidth = 0;
        int originalImageHeight = 0;
        int inkFountainWidthInPixel = 0;

        int colorsExists = 0;

        if (currentPage == 1){
            rotateAngle = rotateAngle_upper;
            horizontallyFlipped = horizontallyFlipped_upper;
            if (upperFileFormat == PPF_FORMAT){
                inkFountainWidthInPixel = upper_inkFountainWidthInPixel / ph1->shrinkRatio;
                imageDirection = ph1->direction;
                shrinkedRatio = 1;

                if (rotateAngle == 0 || rotateAngle == 180){
                    if (ph1->thumbnailHeight > ph1->thumbnailWidth && ph1->thumbnailHeight > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)ph1->thumbnailHeight;
                    else if (ph1->thumbnailWidth > ph1->thumbnailHeight && ph1->thumbnailWidth > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)ph1->thumbnailWidth;
                    thumbnailLocation = ph1->thumbnailLocation * shrinkedRatio;
                }
                else{
                    if (ph1->thumbnailHeight > ph1->thumbnailWidth && ph1->thumbnailHeight > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)ph1->thumbnailHeight;
                    else if (ph1->thumbnailWidth > ph1->thumbnailHeight && ph1->thumbnailWidth > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)ph1->thumbnailWidth;
                    thumbnailLocation = ph1->thumbnailLocationAfterRotation * shrinkedRatio;
                }
                tempResult = (float)ph1->thumbnailWidth * shrinkedRatio;
                shrinkedImageWidth = (int)tempResult;
                tempResult = (float)ph1->thumbnailHeight * shrinkedRatio;
                shrinkedImageHeight = (int)tempResult;
                originalImageWidth = ph1->thumbnailWidth;
                originalImageHeight = ph1->thumbnailHeight;

                colorsExists = numberOfColorsInPPF1;

                switch(paintEventId){
                case CYAN:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->cyanComponent_horizontal;
                    else
                        thumbnail = ph1->cyanComponent_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(255, 0, 0, 0);
                    break;
                case MAGENTA:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->magentaComponent_horizontal;
                    else
                        thumbnail = ph1->magentaComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 255, 0, 0);
                    break;
                case YELLOW:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->yellowComponent_horizontal;
                    else
                        thumbnail = ph1->yellowComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 255, 0);
                    break;
                case BLACK:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->blackComponent_horizontal;
                    else
                        thumbnail = ph1->blackComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR1:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->specialColor1Component_horizontal;
                    else
                        thumbnail = ph1->specialColor1Component_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR2:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->specialColor2Component_horizontal;
                    else
                        thumbnail = ph1->specialColor2Component_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case UPPER:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = ph1->thumbnailImage_horizontal;
                    else
                        thumbnail = ph1->thumbnailImage_vertical;
                    isMixedColor = true;
                }
                paintEventId = -1;
            }
            else if (upperFileFormat == TIFF_FORMAT){
                inkFountainWidthInPixel = upper_inkFountainWidthInPixel / th1->shrinkRatio;
                shrinkedRatio = 1;

                if (rotateAngle == 0 || rotateAngle == 180){
                    if (th1->thumbnailHeight > th1->thumbnailWidth && th1->thumbnailHeight > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)th1->thumbnailHeight;
                    else if (th1->thumbnailWidth > th1->thumbnailHeight && th1->thumbnailWidth > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)th1->thumbnailWidth;
                    thumbnailLocation = th1->thumbnailLocation * shrinkedRatio;
                }
                else{
                    if (th1->thumbnailHeight > th1->thumbnailWidth && th1->thumbnailHeight > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)th1->thumbnailHeight;
                    else if (th1->thumbnailWidth > th1->thumbnailHeight && th1->thumbnailWidth > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)th1->thumbnailWidth;
                    thumbnailLocation = th1->thumbnailLocationAfterRotation * shrinkedRatio;
                }

                tempResult = shrinkedRatio * (float)th1->thumbnailWidth;
                shrinkedImageWidth = (int)tempResult;
                tempResult = shrinkedRatio * (float)th1->thumbnailHeight;
                shrinkedImageHeight = (int)tempResult;
                originalImageWidth = th1->thumbnailWidth;
                originalImageHeight = th1->thumbnailHeight;

                colorsExists = numberOfColorsInTIF1;

                switch(paintEventId){
                case CYAN:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->cyanComponent_horizontal;
                    else
                        thumbnail = th1->cyanComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(255, 0, 0, 0);
                    break;
                case MAGENTA:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->magentaComponent_horizontal;
                    else
                        thumbnail = th1->magentaComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 255, 0, 0);
                    break;
                case YELLOW:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->yellowComponent_horizontal;
                    else
                        thumbnail = th1->yellowComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 255, 0);
                    break;
                case BLACK:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->blackComponent_horizontal;
                    else
                        thumbnail = th1->blackComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR1:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->specialColor1Component_horizontal;
                    else
                        thumbnail = th1->specialColor1Component_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR2:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->specialColor2Component_horizontal;
                    else
                        thumbnail = th1->specialColor2Component_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case UPPER:
                    if (rotateAngle_upper == 0 ||
                        rotateAngle_upper == 180)
                        thumbnail = th1->thumbnailImage_horizontal;
                    else
                        thumbnail = th1->thumbnailImage_vertical;

                    isMixedColor = true;
                }
                paintEventId = -1;
            }
        }
        else if (currentPage == 2){
            rotateAngle = rotateAngle_lower;
            horizontallyFlipped = horizontallyFlipped_lower;
            if (lowerFileFormat == PPF_FORMAT){
                inkFountainWidthInPixel = lower_inkFountainWidthInPixel / ph2->shrinkRatio;
                imageDirection = ph2->direction;
                shrinkedRatio = 1;
                if (rotateAngle == 0 || rotateAngle == 180){
                    if (ph2->thumbnailHeight > ph2->thumbnailWidth && ph2->thumbnailHeight > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)ph2->thumbnailHeight;
                    else if (ph2->thumbnailWidth > ph2->thumbnailHeight && ph2->thumbnailWidth > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)ph2->thumbnailWidth;
                    thumbnailLocation = ph2->thumbnailLocation * shrinkedRatio;
                }
                else{
                    if (ph2->thumbnailHeight > ph2->thumbnailWidth && ph2->thumbnailHeight > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)ph2->thumbnailHeight;
                    else if (ph2->thumbnailWidth > ph2->thumbnailHeight && ph2->thumbnailWidth > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)ph2->thumbnailWidth;
                    thumbnailLocation = ph2->thumbnailLocationAfterRotation * shrinkedRatio;
                }

                tempResult = (float)ph2->thumbnailWidth * shrinkedRatio;
                shrinkedImageWidth = (int)tempResult;
                tempResult = (float)ph2->thumbnailHeight * shrinkedRatio;
                shrinkedImageHeight = (int)tempResult;
                originalImageWidth = ph2->thumbnailWidth;
                originalImageHeight = ph2->thumbnailHeight;

                colorsExists = numberOfColorsInPPF2;

                switch(paintEventId){
                case CYAN:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->cyanComponent_horizontal;
                    else
                        thumbnail = ph2->cyanComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(255, 0, 0, 0);
                    break;
                case MAGENTA:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->magentaComponent_horizontal;
                    else
                        thumbnail = ph2->magentaComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 255, 0, 0);
                    break;
                case YELLOW:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->yellowComponent_horizontal;
                    else
                        thumbnail = ph2->yellowComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 255, 0);
                    break;
                case BLACK:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->blackComponent_horizontal;
                    else
                        thumbnail = ph2->blackComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR1:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->specialColor1Component_horizontal;
                    else
                        thumbnail = ph2->specialColor1Component_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR2:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->specialColor2Component_horizontal;
                    else
                        thumbnail = ph2->specialColor2Component_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case LOWER:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = ph2->thumbnailImage_horizontal;
                    else
                        thumbnail = ph2->thumbnailImage_vertical;

                    isMixedColor = true;
                }
                paintEventId = -1;
            }
            else if (lowerFileFormat == TIFF_FORMAT){
                inkFountainWidthInPixel = lower_inkFountainWidthInPixel / th2->shrinkRatio;
                shrinkedRatio = 1;

                if (rotateAngle == 0 || rotateAngle == 180){
                    if (th2->thumbnailHeight > th2->thumbnailWidth && th2->thumbnailHeight > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)th2->thumbnailHeight;
                    else if (th2->thumbnailWidth > th2->thumbnailHeight && th2->thumbnailWidth > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)th2->thumbnailWidth;
                    thumbnailLocation = th2->thumbnailLocation * shrinkedRatio;
                }
                else{
                    if (th2->thumbnailHeight > th2->thumbnailWidth && th2->thumbnailHeight > maximum_display_width)
                        shrinkedRatio = (float)maximum_display_width / (float)th2->thumbnailHeight;
                    else if (th2->thumbnailWidth > th2->thumbnailHeight && th2->thumbnailWidth > MAXIMUM_DISPLAY_HEIGHT)
                        shrinkedRatio = (float)MAXIMUM_DISPLAY_HEIGHT / (float)th2->thumbnailWidth;
                    thumbnailLocation = th2->thumbnailLocationAfterRotation * shrinkedRatio;
                }

                tempResult = shrinkedRatio * (float)th2->thumbnailWidth;
                shrinkedImageWidth = (int)tempResult;
                tempResult = shrinkedRatio * (float)th2->thumbnailHeight;
                shrinkedImageHeight = (int)tempResult;
                originalImageWidth = th2->thumbnailWidth;
                originalImageHeight = th2->thumbnailHeight;

                colorsExists = numberOfColorsInTIF2;

                switch(paintEventId){
                case CYAN:
                    if (rotateAngle_lower == 0 ||
                        rotateAngle_lower == 180)
                        thumbnail = th2->cyanComponent_horizontal;
                    else
                        thumbnail = th2->cyanComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(255, 0, 0, 0);
                    break;
                case MAGENTA:
                    if (rotateAngle_lower == 0 ||
                        rotateAngle_lower == 180)
                        thumbnail = th2->magentaComponent_horizontal;
                    else
                        thumbnail = th2->magentaComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 255, 0, 0);
                    break;
                case YELLOW:
                    if (rotateAngle_lower == 0 ||
                        rotateAngle_lower == 180)
                        thumbnail = th2->yellowComponent_horizontal;
                    else
                        thumbnail = th2->yellowComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 255, 0);
                    break;
                case BLACK:
                    if (rotateAngle_lower == 0 ||
                        rotateAngle_lower == 180)
                        thumbnail = th2->blackComponent_horizontal;
                    else
                        thumbnail = th2->blackComponent_vertical;

                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR1:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = th2->specialColor1Component_horizontal;
                    else
                        thumbnail = th2->specialColor1Component_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case COLOR2:
                    if (rotateAngle_lower == 0 || rotateAngle_lower == 180)
                        thumbnail = th2->specialColor2Component_horizontal;
                    else
                        thumbnail = th2->specialColor2Component_vertical;
                    isMixedColor = false;
                    componentColor = QColor::fromCmyk(0, 0, 0, 255);
                    break;
                case LOWER:
                    if (rotateAngle_lower == 0 ||
                        rotateAngle_lower == 180)
                        thumbnail = th2->thumbnailImage_horizontal;
                    else
                        thumbnail = th2->thumbnailImage_vertical;

                    isMixedColor = true;
                }
                paintEventId = -1;
            }
        }

        fountainStartXLocation = 0;
        fountainStartYLocation = 495;
        upperLeftImageXCoord = (maximum_display_width - shrinkedImageWidth) / 2;
        upperLeftImageYCoord = (MAXIMUM_DISPLAY_HEIGHT - shrinkedImageHeight) / 2 + 47;

        if (imageDirection != 0){
            painter.save();
            switch(imageDirection){
            case BOTTOM2TOP_RIGHT2LEFT:{
                    painter.translate(0, upperLeftImageYCoord + shrinkedImageHeight);
                    painter.rotate(-90);

                    painter.translate(shrinkedImageHeight / 2,
                                      upperLeftImageXCoord + shrinkedImageWidth / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(shrinkedImageHeight / 2),
                                      -(upperLeftImageXCoord + shrinkedImageWidth / 2));
                    if (!horizontallyFlipped)
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, true));
                    else
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, false));
                    break;
                }
            case TOP2BOTTOM_RIGHT2LEFT:{
                    painter.translate(upperLeftImageXCoord + shrinkedImageWidth, upperLeftImageYCoord + shrinkedImageHeight);
                    painter.rotate(-90);
                    painter.translate(shrinkedImageHeight / 2,
                                      shrinkedImageWidth / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(shrinkedImageHeight / 2),
                                      -(shrinkedImageWidth / 2));
                    if (horizontallyFlipped)
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, true));
                    else
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, false));
                    break;
                }
            case BOTTOM2TOP_LEFT2RIGHT:{
                    painter.translate(0, upperLeftImageYCoord + shrinkedImageHeight);
                    painter.rotate(90);
                    painter.translate(shrinkedImageHeight / 2,
                                      upperLeftImageXCoord + shrinkedImageWidth / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(shrinkedImageHeight / 2),
                                      -(upperLeftImageXCoord + shrinkedImageWidth / 2));
                    if (horizontallyFlipped)
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, true));
                    else
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, false));
                    break;
                }
            case TOP2BOTTOM_LEFT2RIGHT:{
                    painter.translate(0, upperLeftImageYCoord + shrinkedImageHeight);
                    painter.rotate(90);
                    painter.translate(shrinkedImageHeight / 2,
                                      upperLeftImageXCoord + shrinkedImageWidth / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(shrinkedImageHeight / 2),
                                      -(upperLeftImageXCoord + shrinkedImageWidth / 2));
                    if (horizontallyFlipped)
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, false));
                    else
                        painter.drawImage(0, upperLeftImageXCoord, thumbnail->mirrored(false, true));
                    break;
                }
            case LEFT2RIGHT_TOP2BOTTOM:{
                    painter.translate(upperLeftImageXCoord + shrinkedImageWidth / 2,
                                      upperLeftImageYCoord + shrinkedImageHeight / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(upperLeftImageXCoord + shrinkedImageWidth / 2),
                                      -(upperLeftImageYCoord + shrinkedImageHeight / 2));
                    if (horizontallyFlipped)
                        painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(true, false));
                    else
                        painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(false, false));
                    break;
                }
            case LEFT2RIGHT_BOTTOM2TOP:{
                    painter.translate(upperLeftImageXCoord + shrinkedImageWidth / 2,
                                      upperLeftImageYCoord + shrinkedImageHeight / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(upperLeftImageXCoord + shrinkedImageWidth / 2),
                                      -(upperLeftImageYCoord + shrinkedImageHeight / 2));
                    if (horizontallyFlipped)
                        painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(true, true));
                    else
                        painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(false, true));
                    break;
                }
            case RIGHT2LEFT_TOP2BOTTOM:{
                    painter.translate(upperLeftImageXCoord + shrinkedImageWidth / 2,
                                      upperLeftImageYCoord + shrinkedImageHeight / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(upperLeftImageXCoord + shrinkedImageWidth / 2),
                                      -(upperLeftImageYCoord + shrinkedImageHeight / 2));
                    if (horizontallyFlipped)
                        painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(false, false));
                    else
                        painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(true, false));
                    break;
                }
            case RIGHT2LEFT_BOTTOM2TOP:{
                    painter.translate(upperLeftImageXCoord + shrinkedImageWidth / 2,
                                      upperLeftImageYCoord + shrinkedImageHeight / 2);
                    painter.rotate(rotateAngle);
                    painter.translate(-(upperLeftImageXCoord + shrinkedImageWidth / 2),
                                      -(upperLeftImageYCoord + shrinkedImageHeight / 2));
                    if (horizontallyFlipped)
                        *thumbnail = thumbnail->mirrored(false, false);
                    else
                        *thumbnail = thumbnail->mirrored(true, false);
                    painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(false, true));
                }
            }
            painter.restore();
        }
        else{
            painter.save();

            painter.translate(upperLeftImageXCoord + shrinkedImageWidth / 2,
                              upperLeftImageYCoord + shrinkedImageHeight / 2);
            painter.rotate(rotateAngle);
            painter.translate(-(upperLeftImageXCoord + shrinkedImageWidth / 2),
                              -(upperLeftImageYCoord + shrinkedImageHeight / 2));
            if (horizontallyFlipped)
                painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, thumbnail->mirrored(true, false));
            else
                painter.drawImage(upperLeftImageXCoord, upperLeftImageYCoord, *thumbnail);
            painter.restore();
        }
        if (!isMixedColor){
            float float_inkZoneWidth = (float)maximum_display_width /
                                       (float)inkKeyQuantity;
            if (float_inkZoneWidth - (int)float_inkZoneWidth >= 0.5)
                inkZoneWidth = (int)float_inkZoneWidth + 1;
            else
                inkZoneWidth = (int)float_inkZoneWidth;
            fountainStartXLocation = (maximum_display_width - inkZoneWidth * inkKeyQuantity) / 2;
            painter.fillRect(fountainStartXLocation, fountainStartYLocation, inkZoneWidth * inkKeyQuantity, 36, QColor::fromRgb(200, 200, 200));
            if (rotateAngle / 90 % 2 != 0){
                upperLeftImageXCoord = (maximum_display_width - shrinkedImageHeight) / 2;
                upperLeftImageYCoord = (MAXIMUM_DISPLAY_HEIGHT - shrinkedImageWidth) / 2 + 47;
            }
            QPoint center(upperLeftImageXCoord + currentXCoord, upperLeftImageYCoord + currentYCoord);
            painter.drawEllipse(center, 5, 5);
            painter.drawLine(QPoint(center.x() - 10, center.y()), QPoint(center.x() + 10, center.y()));
            painter.drawLine(QPoint(center.x(), center.y() - 10), QPoint(center.x(), center.y() + 10));
            painter.setPen(QColor::fromRgb(0, 0, 0));
            int adjustedInkValue;
            if (isTabWidgetVisible)
                textFont.setPointSize(7);
            else
                textFont.setPointSize(8);
            painter.setFont(textFont);

            QString string_rollerSpeed;
            QRect rectForRollerSpeed(fountainStartXLocation, fountainStartYLocation -30, 150, 15);
            temp.append("墨斗辊转速:");
            string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors + currentColorShowing - 1]);
            temp.append(string_rollerSpeed);
            painter.drawText(rectForRollerSpeed, Qt::AlignCenter, temp);

            for (int i = 0; i < inkKeyQuantity; i ++){
                adjustedInkValue = getAdjustedInkValue(currentPage - 1, currentColorShowing, i);
                QRect rectForZoneNum(fountainStartXLocation, fountainStartYLocation - 15, inkZoneWidth, 15);
                painter.drawText(rectForZoneNum, Qt::AlignCenter, temp.setNum(i + 1));
                painter.drawLine(fountainStartXLocation, fountainStartYLocation, fountainStartXLocation + inkZoneWidth, fountainStartYLocation);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation, fountainStartXLocation, fountainStartYLocation + 36);
                pen->setStyle(Qt::DotLine);
                painter.setPen(*pen);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation + 36,
                                 fountainStartXLocation, fountainStartYLocation + 66);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation + 66,
                                 fountainStartXLocation + inkZoneWidth, fountainStartYLocation + 66);
                pen->setStyle(Qt::SolidLine);
                painter.setPen(*pen);
                QRect rect(fountainStartXLocation, fountainStartYLocation + 36 - adjustedInkValue / (inkKeySteps / 30),
                           inkZoneWidth, adjustedInkValue / (inkKeySteps / 30));
                painter.fillRect(rect, componentColor);
                painter.drawRect(rect);

                QRect rectForFraction(fountainStartXLocation, fountainStartYLocation + 52, inkZoneWidth, 15);
                temp.setNum(adjustedInkValue % inkFraction);
                painter.drawText(rectForFraction, Qt::AlignCenter, temp);
                QRect rectForText(fountainStartXLocation, fountainStartYLocation + 38, inkZoneWidth, 15);
                temp.setNum(adjustedInkValue / inkFraction);
                painter.drawText(rectForText, Qt::AlignCenter, temp);
                fountainStartXLocation += inkZoneWidth;
            }
            painter.drawLine(fountainStartXLocation, fountainStartYLocation, fountainStartXLocation, fountainStartYLocation + 64);
        }
        else{
            float float_inkZoneWidth = (float)maximum_display_width / (float)inkKeyQuantity;
            if (float_inkZoneWidth - (int)float_inkZoneWidth >= 0.5)
                inkZoneWidth = (int)float_inkZoneWidth + 1;
            else
                inkZoneWidth = (int)float_inkZoneWidth;
            fountainStartXLocation = (maximum_display_width - inkZoneWidth * inkKeyQuantity) / 2;
            int colorTextAreaHeight = 63 + (colorsExists - 4) * 15;
            painter.fillRect(fountainStartXLocation, fountainStartYLocation, inkZoneWidth * inkKeyQuantity, colorTextAreaHeight, QColor::fromRgb(200, 200, 200));
            if (rotateAngle / 90 % 2 != 0){
                upperLeftImageXCoord = (maximum_display_width - shrinkedImageHeight) / 2;
                upperLeftImageYCoord = (MAXIMUM_DISPLAY_HEIGHT - shrinkedImageWidth) / 2 + 47;
            }
            QPoint center(upperLeftImageXCoord + currentXCoord, upperLeftImageYCoord + currentYCoord);
            painter.drawEllipse(center, 5, 5);
            painter.drawLine(QPoint(center.x() - 10, center.y()), QPoint(center.x() + 10, center.y()));
            painter.drawLine(QPoint(center.x(), center.y() - 10), QPoint(center.x(), center.y() + 10));
            if (isTabWidgetVisible)
                textFont.setPointSize(7);
            else
                textFont.setPointSize(8);
            painter.setFont(textFont);

            QString string_rollerSpeed;
            QRect rectForRollerSpeed(fountainStartXLocation, fountainStartYLocation -30, 600, 15);

            temp.clear();
            temp.append("转速:");

            temp.append("青- ");
            string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors]);
            temp.append(string_rollerSpeed);

            temp.append("   红- ");
            string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors + 1]);
            temp.append(string_rollerSpeed);

            temp.append("   黄- ");
            string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors + 2]);
            temp.append(string_rollerSpeed);

            temp.append("   黑- ");
            string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors + 3]);
            temp.append(string_rollerSpeed);

            if (colorsExists >= 5){
                temp.append("   专色1- ");
                string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors + 4]);
                temp.append(string_rollerSpeed);
            }
            if (colorsExists >= 6){
                temp.append("   专色2- ");
                string_rollerSpeed.setNum(inkRollerSpeed[(currentPage - 1) * totalColors + 5]);
                temp.append(string_rollerSpeed);
            }
            painter.drawText(rectForRollerSpeed, Qt::AlignCenter, temp);

            for (int i = 0; i < inkKeyQuantity; i ++){
                painter.setPen(QColor::fromRgb(0, 0, 0));
                QRect rectForText(fountainStartXLocation, fountainStartYLocation - 15, inkZoneWidth, 15);
                temp.setNum(i + 1);
                painter.drawText(rectForText, Qt::AlignCenter, temp);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation, fountainStartXLocation, fountainStartYLocation + colorTextAreaHeight);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation, fountainStartXLocation + inkZoneWidth, fountainStartYLocation);

                painter.drawLine(fountainStartXLocation, fountainStartYLocation + colorTextAreaHeight, fountainStartXLocation + inkZoneWidth, fountainStartYLocation + colorTextAreaHeight);

                painter.setPen(QColor::fromRgb(0, 128, 128));
                QRect rectForCyan(fountainStartXLocation, fountainStartYLocation + 2, inkZoneWidth, 15);
                temp.setNum(getAdjustedInkValue(currentPage - 1, CYAN, i) / inkFraction);

                painter.drawText(rectForCyan, Qt::AlignCenter, temp);

                painter.setPen(QColor::fromRgb(128, 0, 0));
                QRect rectForMagenta(fountainStartXLocation, fountainStartYLocation + 17, inkZoneWidth, 15);
                temp.setNum(getAdjustedInkValue(currentPage - 1, MAGENTA, i) / inkFraction);

                painter.drawText(rectForMagenta, Qt::AlignCenter, temp);

                painter.setPen(QColor::fromRgb(128, 128, 0));
                QRect rectForYellow(fountainStartXLocation, fountainStartYLocation + 32, inkZoneWidth, 15);
                temp.setNum(getAdjustedInkValue(currentPage - 1, YELLOW, i) / inkFraction);

                painter.drawText(rectForYellow, Qt::AlignCenter, temp);

                painter.setPen(QColor::fromCmyk(0, 0, 0, 255));
                QRect rectForBlack(fountainStartXLocation, fountainStartYLocation + 47, inkZoneWidth, 15);
                temp.setNum(getAdjustedInkValue(currentPage - 1, BLACK, i) / inkFraction);

                painter.drawText(rectForBlack, Qt::AlignCenter, temp);

                if (colorsExists >= 5){
                    painter.setPen(QColor::fromCmyk(150, 150, 150, 150));
                    QRect rectForSpecialColor1(fountainStartXLocation, fountainStartYLocation + 62, inkZoneWidth, 15);
                    temp.setNum(getAdjustedInkValue(currentPage - 1, COLOR1, i) / inkFraction);

                    painter.drawText(rectForSpecialColor1, Qt::AlignCenter, temp);
                }
                if (colorsExists >= 6){
                    painter.setPen(QColor::fromCmyk(150, 150, 150, 150));
                    QRect rectForSpecialColor2(fountainStartXLocation, fountainStartYLocation + 77, inkZoneWidth, 15);
                    temp.setNum(getAdjustedInkValue(currentPage - 1, COLOR2, i) / inkFraction);

                    painter.drawText(rectForSpecialColor2, Qt::AlignCenter, temp);
                }
                fountainStartXLocation += inkZoneWidth;
            }
            painter.drawLine(fountainStartXLocation, fountainStartYLocation, fountainStartXLocation, fountainStartYLocation + colorTextAreaHeight);
        }

        tempResult = inkFountainWidthInPixel * shrinkedRatio;
        if (tempResult - (int)tempResult >= 0.5)
            inkFountainWidthInPixel = (int)tempResult + 1;
        else
            inkFountainWidthInPixel = (int)tempResult;
        float inkZoneWidth = tempResult / (float)inkKeyQuantity;
        int firstInkZoneStartXLocation = 0;
        pen->setColor(Qt::darkGray);
        pen->setStyle(Qt::DotLine);
        painter.setPen(*pen);
        firstInkZoneStartXLocation = (maximum_display_width - inkFountainWidthInPixel) / 2;

        textFont.setPointSize(6);
        painter.setFont(textFont);
        for (int i = 0; i <= inkKeyQuantity; i ++){
            painter.drawLine(firstInkZoneStartXLocation + i * inkZoneWidth, 47,
                             firstInkZoneStartXLocation + i * inkZoneWidth, 47 + MAXIMUM_DISPLAY_HEIGHT);
            if (i != inkKeyQuantity){
                QRect inkNum(firstInkZoneStartXLocation + i * inkZoneWidth, 47,
                             inkZoneWidth, 10);
                temp.setNum(i + 1);

                painter.drawText(inkNum, Qt::AlignCenter, temp);
            }
        }
    }
    else if (paintEventId == ZOOMIN){
        paintEventId = -1;
        QColor componentColor[6];
        componentColor[0] = QColor::fromCmyk(255, 0, 0, 0);
        componentColor[1] = QColor::fromCmyk(0, 255, 0, 0);
        componentColor[2] = QColor::fromCmyk(0, 0, 255, 0);
        componentColor[3] = QColor::fromCmyk(0, 0, 0, 255);
        if (currentPage == 1){
            if (numberOfColorsInPPF1 == 5)
                componentColor[4] = QColor::fromRgb(233, 233, 233);
            if (numberOfColorsInPPF1 == 6){
                componentColor[4] = QColor::fromRgb(233, 233, 233);
                componentColor[5] = QColor::fromRgb(233, 233, 233);
            }
        }
        if (currentPage == 2){
            if (numberOfColorsInPPF2 == 5)
                componentColor[4] = QColor::fromRgb(233, 233, 233);
            if (numberOfColorsInPPF2 == 6){
                componentColor[4] = QColor::fromRgb(233, 233, 233);
                componentColor[5] = QColor::fromRgb(233, 233, 233);
            }
        }
        float float_inkZoneWidth = (float)(FULLSCREEN_WIDTH) /
                                   (float)inkKeyQuantity;
        if (float_inkZoneWidth - (int)float_inkZoneWidth >= 0.5)
            inkZoneWidth = (int)float_inkZoneWidth + 1;
        else
            inkZoneWidth = (int)float_inkZoneWidth;
        fountainStartXLocation = (FULLSCREEN_WIDTH - inkZoneWidth * inkKeyQuantity) / 2;

        painter.setPen(QColor::fromRgb(0, 0, 0));
        int adjustedInkValue;
        fountainStartYLocation = 100;
        textFont.setPointSize(6);
        painter.setFont(textFont);
        for (int i = 0; i < inkKeyQuantity; i ++){
            QRect rectForZoneNum(fountainStartXLocation, fountainStartYLocation - 18, inkZoneWidth, 12);
            painter.drawText(rectForZoneNum, Qt::AlignCenter, temp.setNum(i + 1));
            fountainStartXLocation += inkZoneWidth;
        }
        textFont.setPointSize(8);
        painter.setFont(textFont);
        QPen *pen = new QPen();

        int numberOfColorsInZOOMIN = 4;
        if (currentPage == 1 && upperFileFormat == PPF_FORMAT)
            numberOfColorsInZOOMIN = numberOfColorsInPPF1;
        if (currentPage == 2 && lowerFileFormat == PPF_FORMAT)
            numberOfColorsInZOOMIN = numberOfColorsInPPF2;


        for (int color = 1; color <= numberOfColorsInZOOMIN; color ++){
            textFont.setPointSize(6);
            painter.setFont(textFont);
            fountainStartXLocation = (FULLSCREEN_WIDTH - inkZoneWidth * inkKeyQuantity) / 2;
            QRect rectForColorName(5, fountainStartYLocation - 7, 100, 10);
            switch(color){
            case CYAN:
                temp = "CYAN:";
                break;
            case MAGENTA:
                temp = "MAGENTA:";
                break;
            case YELLOW:
                temp = "YELLOW:";
                break;
            case BLACK:
                temp = "BLACK:";
                break;
            case COLOR1:
                temp = "COLOR1:";
                break;
            case COLOR2:
                temp = "COLOR2:";
                break;
            }
            painter.drawText(rectForColorName, Qt::AlignLeft, temp);
            fountainStartYLocation += 9;

            textFont.setPointSize(8);
            painter.setFont(textFont);
            for (int i = 0; i < inkKeyQuantity; i ++){
                adjustedInkValue = getAdjustedInkValue(currentPage - 1, color, i);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation - 3, fountainStartXLocation + inkZoneWidth, fountainStartYLocation - 3);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation - 3, fountainStartXLocation, fountainStartYLocation + 20);
                pen->setStyle(Qt::DotLine);
                painter.setPen(*pen);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation + 20,
                                 fountainStartXLocation, fountainStartYLocation + 60);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation + 40,
                                 fountainStartXLocation + inkZoneWidth, fountainStartYLocation + 40);
                painter.drawLine(fountainStartXLocation, fountainStartYLocation + 60,
                                 fountainStartXLocation + inkZoneWidth, fountainStartYLocation + 60);
                pen->setStyle(Qt::SolidLine);
                painter.setPen(*pen);
                QRect rect(fountainStartXLocation, fountainStartYLocation + 20 - adjustedInkValue / (inkKeySteps / 20),
                           inkZoneWidth, adjustedInkValue / (inkKeySteps / 20));
                painter.fillRect(rect, componentColor[color - 1]);
                painter.drawRect(rect);

                QRect rectForText(fountainStartXLocation, fountainStartYLocation + 22, inkZoneWidth, 20);
                temp.setNum(adjustedInkValue / inkFraction);
                painter.drawText(rectForText, Qt::AlignCenter, temp);

                QRect rectForFraction(fountainStartXLocation, fountainStartYLocation + 42, inkZoneWidth, 20);
                temp.setNum(adjustedInkValue % inkFraction);
                painter.drawText(rectForFraction, Qt::AlignCenter, temp);

                fountainStartXLocation += inkZoneWidth;
            }
            painter.drawLine(fountainStartXLocation, fountainStartYLocation - 3, fountainStartXLocation, fountainStartYLocation + 20);
            fountainStartYLocation += 75;
        }
    }
}
void MainWindow::shutDownLinux()
{
    if (isOtherInstructionInProcess())
        return;
    previouslySelectedButton = selectedButton;
    selectedButton = WIDGET_ID_SHUT_DOWN;
    changeWidgetVisualEffect(previouslySelectedButton, selectedButton);

    isShutingDownDevice = true;

    QMessageBox *m = new QMessageBox(this);
    m->setWindowFlags(flags);
    connect(this, SIGNAL(closeMessage()), m, SLOT(accept()));
    m->setFont(font);
    m->setIcon(QMessageBox::Question);
    m->setText("是否确认关闭系统？");
    m->addButton(QMessageBox::Yes);
    m->addButton(QMessageBox::No);
    connect(m->button(QMessageBox::Yes), SIGNAL(clicked()), this, SLOT(physicalSelectButtonPressed()));
    connect(m->button(QMessageBox::No), SIGNAL(clicked()), this, SLOT(physicalCancelButtonPressed()));
    m->exec();

    return;
}
MainWindow::~MainWindow()
{
    collectMemoryGarbage();
    fileName.clear();
    if (isMemoryForColorOffsetValid){
        inkCurve.clear();
        changedPoints.clear();

        isMemoryForColorOffsetValid = false;
    }
    if (isSocketConnected){
        isSocketConnected = false;
        socket->disconnectFromHost();
        socket->deleteLater();
    }
    delete ui;
}
