/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Wed Jan 16 18:05:06 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *text_numOfInkKeys;
    QRadioButton *radioButton_oneSide;
    QRadioButton *radioButton_twoSides;
    QLineEdit *text_fountainWidth;
    QLineEdit *text_plateHeight;
    QPushButton *pushButton_fountainWidth;
    QPushButton *pushButton_plateHeight;
    QPushButton *pushButton_maxInkValue;
    QLineEdit *text_maxInkValue;
    QPushButton *pushButton_KeyNumbers;
    QFrame *line;
    QPushButton *pushButton_enter;
    QPushButton *pushButton_seven;
    QPushButton *pushButton_dot;
    QPushButton *pushButton_five;
    QPushButton *pushButton_nine;
    QPushButton *pushButton_four;
    QPushButton *pushButton_zero;
    QPushButton *pushButton_one;
    QPushButton *pushButton_two;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_six;
    QPushButton *pushButton_eight;
    QPushButton *pushButton_three;
    QTextBrowser *text_ValueOfInput;
    QFrame *line_6;
    QFrame *line_7;
    QPushButton *pushButton_inkFraction;
    QLineEdit *text_inkFraction;
    QPushButton *pushButton_enterParameters;
    QPushButton *pushButton_totalColors;
    QLineEdit *text_totalColors;
    QWidget *tab_3;
    QToolButton *cyan;
    QToolButton *magenta;
    QToolButton *yellow;
    QToolButton *black;
    QFrame *line_2;
    QToolButton *pushButton_direction1;
    QToolButton *pushButton_direction2;
    QToolButton *pushButton_direction3;
    QToolButton *pushButton_direction4;
    QToolButton *pushButton_direction5;
    QToolButton *pushButton_direction6;
    QToolButton *pushButton_direction7;
    QToolButton *pushButton_direction8;
    QRadioButton *radioButton_lowerSide;
    QRadioButton *radioButton_upperSide;
    QToolButton *color1;
    QToolButton *color2;
    QWidget *tab_2;
    QLabel *label;
    QLabel *label_cyanInkValue;
    QLabel *label_3;
    QLabel *label_magentaInkValue;
    QLabel *label_5;
    QLabel *label_yellowInkValue;
    QLabel *label_7;
    QLabel *label_blackInkValue;
    QPushButton *pushButton_decreaseCyan;
    QPushButton *pushButton_increaseCyan;
    QPushButton *pushButton_decreaseMagenta;
    QPushButton *pushButton_increaseMagenta;
    QPushButton *pushButton_decreaseYellow;
    QPushButton *pushButton_increaseYellow;
    QPushButton *pushButton_decreaseBlack;
    QPushButton *pushButton_increaseBlack;
    QLineEdit *lineEdit_currentInkZone;
    QPushButton *pushButton_nextInkZone;
    QPushButton *pushButton_lastInkZone;
    QPushButton *pushButton_roughAdjust;
    QPushButton *pushButton_subtleAdjust;
    QPushButton *pushButton_increaseColor1;
    QLabel *label_13;
    QPushButton *pushButton_decreaseColor1;
    QLabel *label_color1InkValue;
    QLabel *label_14;
    QLabel *label_color2InkValue;
    QPushButton *pushButton_increaseColor2;
    QPushButton *pushButton_decreaseColor2;
    QSlider *horizontalSlider_cyanInkValue;
    QSlider *horizontalSlider_magentaInkValue;
    QSlider *horizontalSlider_yellowInkValue;
    QSlider *horizontalSlider_blackInkValue;
    QSlider *horizontalSlider_color1InkValue;
    QSlider *horizontalSlider_color2InkValue;
    QPushButton *pushButton_adjustBasicInk;
    QPushButton *pushButton_adjustSingleInk;
    QPushButton *pushButton_adjustRollerSpeed;
    QWidget *tab_4;
    QSlider *verticalSlider_cyanInkThickness;
    QRadioButton *radioButton_paper4;
    QRadioButton *radioButton_paper3;
    QRadioButton *radioButton_paper2;
    QRadioButton *radioButton_paper1;
    QRadioButton *radioButton_Ink1;
    QRadioButton *radioButton_Ink2;
    QRadioButton *radioButton_Ink3;
    QRadioButton *radioButton_Ink4;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_12;
    QSlider *verticalSlider_magentaInkThickness;
    QSlider *verticalSlider_yellowInkThickness;
    QSlider *verticalSlider_blackInkThickness;
    QLabel *label_15;
    QLabel *label_cyanInkThickness;
    QLabel *label_magentaInkThickness;
    QLabel *label_yellowInkThickness;
    QLabel *label_blackInkThickness;
    QWidget *widget_status;
    QLabel *label_processStatus;
    QProgressBar *progressBar;
    QPushButton *pushButton_sure;
    QWidget *widget;
    QPushButton *actionOpen;
    QPushButton *actionSync;
    QPushButton *actionSave;
    QPushButton *actionDelete;
    QPushButton *actionZoomIn;
    QPushButton *actionSettings;
    QProgressBar *progressBar_battery;
    QLabel *label_4;
    QLabel *label_connection;
    QPushButton *actionShutDown;
    QWidget *widget_ip;
    QLabel *label_ip;
    QLineEdit *lineEdit_ipAddress;
    QPushButton *pushButton_enterIP;
    QPushButton *pushButton_cancelIP;
    QWidget *widget_deleteFileList;
    QScrollArea *scrollArea_deleteFile;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *label_10;
    QPushButton *pushButton_selectFileToDelete;
    QPushButton *pushButton_cancelDelete;
    QWidget *widget_machineModel;
    QScrollArea *scrollArea_machineModel;
    QWidget *scrollAreaWidgetContents_4;
    QLabel *label_11;
    QPushButton *pushButton_selectMachineModel;
    QPushButton *pushButton_cancelMachineSelection;
    QWidget *widget_fileList;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_9;
    QPushButton *pushButton_selectFile;
    QPushButton *pushButton_cancelSelect;
    QPushButton *pushButton_showTabWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("WenQuanYi Zen Hei"));
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(590, 46, 212, 561));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu"));
        font1.setPointSize(8);
        font1.setBold(true);
        font1.setWeight(75);
        tabWidget->setFont(font1);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setIconSize(QSize(24, 16));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setFont(font);
        text_numOfInkKeys = new QLineEdit(tab);
        text_numOfInkKeys->setObjectName(QString::fromUtf8("text_numOfInkKeys"));
        text_numOfInkKeys->setGeometry(QRect(90, 40, 103, 25));
        text_numOfInkKeys->setFont(font1);
        text_numOfInkKeys->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255);border:1px solid}"));
        radioButton_oneSide = new QRadioButton(tab);
        radioButton_oneSide->setObjectName(QString::fromUtf8("radioButton_oneSide"));
        radioButton_oneSide->setGeometry(QRect(90, 10, 51, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("WenQuanYi Zen Hei"));
        font2.setPointSize(8);
        font2.setBold(true);
        font2.setWeight(75);
        radioButton_oneSide->setFont(font2);
        radioButton_oneSide->setAutoExclusive(true);
        radioButton_twoSides = new QRadioButton(tab);
        radioButton_twoSides->setObjectName(QString::fromUtf8("radioButton_twoSides"));
        radioButton_twoSides->setGeometry(QRect(145, 10, 51, 21));
        radioButton_twoSides->setFont(font2);
        radioButton_twoSides->setAutoExclusive(true);
        text_fountainWidth = new QLineEdit(tab);
        text_fountainWidth->setObjectName(QString::fromUtf8("text_fountainWidth"));
        text_fountainWidth->setGeometry(QRect(90, 70, 103, 25));
        text_fountainWidth->setFont(font1);
        text_fountainWidth->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        text_plateHeight = new QLineEdit(tab);
        text_plateHeight->setObjectName(QString::fromUtf8("text_plateHeight"));
        text_plateHeight->setGeometry(QRect(90, 100, 103, 25));
        text_plateHeight->setFont(font1);
        text_plateHeight->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        pushButton_fountainWidth = new QPushButton(tab);
        pushButton_fountainWidth->setObjectName(QString::fromUtf8("pushButton_fountainWidth"));
        pushButton_fountainWidth->setGeometry(QRect(10, 70, 70, 25));
        pushButton_fountainWidth->setFont(font2);
        pushButton_fountainWidth->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/icons/width.png")), QIcon::Normal, QIcon::Off);
        pushButton_fountainWidth->setIcon(icon);
        pushButton_fountainWidth->setIconSize(QSize(40, 25));
        pushButton_plateHeight = new QPushButton(tab);
        pushButton_plateHeight->setObjectName(QString::fromUtf8("pushButton_plateHeight"));
        pushButton_plateHeight->setGeometry(QRect(10, 100, 70, 25));
        pushButton_plateHeight->setFont(font1);
        pushButton_plateHeight->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/icons/height.png")), QIcon::Normal, QIcon::Off);
        pushButton_plateHeight->setIcon(icon1);
        pushButton_plateHeight->setIconSize(QSize(40, 25));
        pushButton_maxInkValue = new QPushButton(tab);
        pushButton_maxInkValue->setObjectName(QString::fromUtf8("pushButton_maxInkValue"));
        pushButton_maxInkValue->setGeometry(QRect(10, 130, 70, 25));
        pushButton_maxInkValue->setFont(font2);
        pushButton_maxInkValue->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_maxInkValue->setIconSize(QSize(40, 25));
        text_maxInkValue = new QLineEdit(tab);
        text_maxInkValue->setObjectName(QString::fromUtf8("text_maxInkValue"));
        text_maxInkValue->setGeometry(QRect(90, 130, 103, 25));
        text_maxInkValue->setFont(font1);
        text_maxInkValue->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        pushButton_KeyNumbers = new QPushButton(tab);
        pushButton_KeyNumbers->setObjectName(QString::fromUtf8("pushButton_KeyNumbers"));
        pushButton_KeyNumbers->setGeometry(QRect(10, 40, 70, 25));
        pushButton_KeyNumbers->setFont(font1);
        pushButton_KeyNumbers->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/icons/inkNumber.png")), QIcon::Normal, QIcon::Off);
        pushButton_KeyNumbers->setIcon(icon2);
        pushButton_KeyNumbers->setIconSize(QSize(40, 25));
        line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 260, 211, 16));
        line->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(233, 233, 233);}\n"
""));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_enter = new QPushButton(tab);
        pushButton_enter->setObjectName(QString::fromUtf8("pushButton_enter"));
        pushButton_enter->setGeometry(QRect(110, 430, 80, 26));
        pushButton_enter->setFont(font1);
        pushButton_enter->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/icons/enter.png")), QIcon::Normal, QIcon::Off);
        pushButton_enter->setIcon(icon3);
        pushButton_enter->setIconSize(QSize(50, 24));
        pushButton_seven = new QPushButton(tab);
        pushButton_seven->setObjectName(QString::fromUtf8("pushButton_seven"));
        pushButton_seven->setGeometry(QRect(20, 355, 40, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Ubuntu"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        pushButton_seven->setFont(font3);
        pushButton_seven->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_dot = new QPushButton(tab);
        pushButton_dot->setObjectName(QString::fromUtf8("pushButton_dot"));
        pushButton_dot->setGeometry(QRect(150, 390, 40, 30));
        pushButton_dot->setFont(font3);
        pushButton_dot->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_five = new QPushButton(tab);
        pushButton_five->setObjectName(QString::fromUtf8("pushButton_five"));
        pushButton_five->setGeometry(QRect(85, 320, 40, 30));
        pushButton_five->setFont(font3);
        pushButton_five->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_nine = new QPushButton(tab);
        pushButton_nine->setObjectName(QString::fromUtf8("pushButton_nine"));
        pushButton_nine->setGeometry(QRect(150, 355, 40, 30));
        pushButton_nine->setFont(font3);
        pushButton_nine->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_four = new QPushButton(tab);
        pushButton_four->setObjectName(QString::fromUtf8("pushButton_four"));
        pushButton_four->setGeometry(QRect(20, 320, 40, 30));
        pushButton_four->setFont(font3);
        pushButton_four->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_zero = new QPushButton(tab);
        pushButton_zero->setObjectName(QString::fromUtf8("pushButton_zero"));
        pushButton_zero->setGeometry(QRect(20, 390, 40, 30));
        pushButton_zero->setFont(font3);
        pushButton_zero->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_one = new QPushButton(tab);
        pushButton_one->setObjectName(QString::fromUtf8("pushButton_one"));
        pushButton_one->setGeometry(QRect(20, 285, 40, 30));
        pushButton_one->setFont(font3);
        pushButton_one->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_two = new QPushButton(tab);
        pushButton_two->setObjectName(QString::fromUtf8("pushButton_two"));
        pushButton_two->setGeometry(QRect(85, 285, 40, 30));
        pushButton_two->setFont(font3);
        pushButton_two->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_delete = new QPushButton(tab);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        pushButton_delete->setGeometry(QRect(20, 430, 80, 26));
        pushButton_delete->setFont(font3);
        pushButton_delete->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_six = new QPushButton(tab);
        pushButton_six->setObjectName(QString::fromUtf8("pushButton_six"));
        pushButton_six->setGeometry(QRect(150, 320, 40, 30));
        pushButton_six->setFont(font3);
        pushButton_six->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_eight = new QPushButton(tab);
        pushButton_eight->setObjectName(QString::fromUtf8("pushButton_eight"));
        pushButton_eight->setGeometry(QRect(85, 355, 40, 30));
        pushButton_eight->setFont(font3);
        pushButton_eight->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_three = new QPushButton(tab);
        pushButton_three->setObjectName(QString::fromUtf8("pushButton_three"));
        pushButton_three->setGeometry(QRect(150, 285, 40, 30));
        pushButton_three->setFont(font3);
        pushButton_three->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        text_ValueOfInput = new QTextBrowser(tab);
        text_ValueOfInput->setObjectName(QString::fromUtf8("text_ValueOfInput"));
        text_ValueOfInput->setGeometry(QRect(65, 392, 80, 27));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Ubuntu"));
        font4.setPointSize(8);
        text_ValueOfInput->setFont(font4);
        text_ValueOfInput->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        line_6 = new QFrame(tab);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(10, 30, 184, 3));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(tab);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(85, 10, 3, 215));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        pushButton_inkFraction = new QPushButton(tab);
        pushButton_inkFraction->setObjectName(QString::fromUtf8("pushButton_inkFraction"));
        pushButton_inkFraction->setGeometry(QRect(10, 160, 70, 25));
        pushButton_inkFraction->setFont(font2);
        pushButton_inkFraction->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_inkFraction->setIconSize(QSize(40, 25));
        text_inkFraction = new QLineEdit(tab);
        text_inkFraction->setObjectName(QString::fromUtf8("text_inkFraction"));
        text_inkFraction->setGeometry(QRect(90, 160, 103, 25));
        text_inkFraction->setFont(font1);
        text_inkFraction->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        pushButton_enterParameters = new QPushButton(tab);
        pushButton_enterParameters->setObjectName(QString::fromUtf8("pushButton_enterParameters"));
        pushButton_enterParameters->setGeometry(QRect(88, 230, 105, 26));
        pushButton_enterParameters->setFont(font1);
        pushButton_enterParameters->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        pushButton_enterParameters->setIcon(icon3);
        pushButton_enterParameters->setIconSize(QSize(50, 24));
        pushButton_totalColors = new QPushButton(tab);
        pushButton_totalColors->setObjectName(QString::fromUtf8("pushButton_totalColors"));
        pushButton_totalColors->setGeometry(QRect(10, 190, 70, 25));
        pushButton_totalColors->setFont(font2);
        pushButton_totalColors->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/icons/numberOfColors.png")), QIcon::Normal, QIcon::Off);
        pushButton_totalColors->setIcon(icon4);
        pushButton_totalColors->setIconSize(QSize(40, 25));
        text_totalColors = new QLineEdit(tab);
        text_totalColors->setObjectName(QString::fromUtf8("text_totalColors"));
        text_totalColors->setGeometry(QRect(90, 190, 103, 25));
        text_totalColors->setFont(font1);
        text_totalColors->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/icons/settings.png")), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon5, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tab_3->setFont(font);
        cyan = new QToolButton(tab_3);
        cyan->setObjectName(QString::fromUtf8("cyan"));
        cyan->setGeometry(QRect(40, 70, 45, 45));
        cyan->setFont(font);
        cyan->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/icons/c.png")), QIcon::Normal, QIcon::Off);
        cyan->setIcon(icon6);
        cyan->setIconSize(QSize(40, 40));
        magenta = new QToolButton(tab_3);
        magenta->setObjectName(QString::fromUtf8("magenta"));
        magenta->setGeometry(QRect(120, 70, 45, 45));
        magenta->setFont(font);
        magenta->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        QIcon icon7;
        icon7.addPixmap(QPixmap(QString::fromUtf8(":/icons/m.png")), QIcon::Normal, QIcon::Off);
        magenta->setIcon(icon7);
        magenta->setIconSize(QSize(40, 40));
        yellow = new QToolButton(tab_3);
        yellow->setObjectName(QString::fromUtf8("yellow"));
        yellow->setGeometry(QRect(40, 120, 45, 45));
        yellow->setFont(font);
        yellow->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon8;
        icon8.addPixmap(QPixmap(QString::fromUtf8(":/icons/y.png")), QIcon::Normal, QIcon::Off);
        yellow->setIcon(icon8);
        yellow->setIconSize(QSize(40, 40));
        black = new QToolButton(tab_3);
        black->setObjectName(QString::fromUtf8("black"));
        black->setGeometry(QRect(120, 120, 45, 45));
        black->setFont(font);
        black->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon9;
        icon9.addPixmap(QPixmap(QString::fromUtf8(":/icons/k.png")), QIcon::Normal, QIcon::Off);
        black->setIcon(icon9);
        black->setIconSize(QSize(40, 40));
        line_2 = new QFrame(tab_3);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 260, 211, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton_direction1 = new QToolButton(tab_3);
        pushButton_direction1->setObjectName(QString::fromUtf8("pushButton_direction1"));
        pushButton_direction1->setGeometry(QRect(40, 290, 40, 40));
        pushButton_direction1->setFont(font);
        pushButton_direction1->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon10;
        icon10.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction1.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction1->setIcon(icon10);
        pushButton_direction1->setIconSize(QSize(75, 75));
        pushButton_direction2 = new QToolButton(tab_3);
        pushButton_direction2->setObjectName(QString::fromUtf8("pushButton_direction2"));
        pushButton_direction2->setGeometry(QRect(130, 290, 40, 40));
        pushButton_direction2->setFont(font);
        pushButton_direction2->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon11;
        icon11.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction2.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction2->setIcon(icon11);
        pushButton_direction2->setIconSize(QSize(75, 75));
        pushButton_direction3 = new QToolButton(tab_3);
        pushButton_direction3->setObjectName(QString::fromUtf8("pushButton_direction3"));
        pushButton_direction3->setGeometry(QRect(40, 340, 40, 40));
        pushButton_direction3->setFont(font);
        pushButton_direction3->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon12;
        icon12.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction3.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction3->setIcon(icon12);
        pushButton_direction3->setIconSize(QSize(75, 75));
        pushButton_direction4 = new QToolButton(tab_3);
        pushButton_direction4->setObjectName(QString::fromUtf8("pushButton_direction4"));
        pushButton_direction4->setGeometry(QRect(130, 340, 40, 40));
        pushButton_direction4->setFont(font);
        pushButton_direction4->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon13;
        icon13.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction4.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction4->setIcon(icon13);
        pushButton_direction4->setIconSize(QSize(75, 75));
        pushButton_direction5 = new QToolButton(tab_3);
        pushButton_direction5->setObjectName(QString::fromUtf8("pushButton_direction5"));
        pushButton_direction5->setGeometry(QRect(40, 390, 40, 40));
        pushButton_direction5->setFont(font);
        pushButton_direction5->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon14;
        icon14.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction5.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction5->setIcon(icon14);
        pushButton_direction5->setIconSize(QSize(75, 75));
        pushButton_direction6 = new QToolButton(tab_3);
        pushButton_direction6->setObjectName(QString::fromUtf8("pushButton_direction6"));
        pushButton_direction6->setGeometry(QRect(130, 390, 40, 40));
        pushButton_direction6->setFont(font);
        pushButton_direction6->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon15;
        icon15.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction6.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction6->setIcon(icon15);
        pushButton_direction6->setIconSize(QSize(75, 75));
        pushButton_direction7 = new QToolButton(tab_3);
        pushButton_direction7->setObjectName(QString::fromUtf8("pushButton_direction7"));
        pushButton_direction7->setGeometry(QRect(40, 440, 40, 40));
        pushButton_direction7->setFont(font);
        pushButton_direction7->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon16;
        icon16.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction7.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction7->setIcon(icon16);
        pushButton_direction7->setIconSize(QSize(75, 75));
        pushButton_direction8 = new QToolButton(tab_3);
        pushButton_direction8->setObjectName(QString::fromUtf8("pushButton_direction8"));
        pushButton_direction8->setGeometry(QRect(130, 440, 40, 40));
        pushButton_direction8->setFont(font);
        pushButton_direction8->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon17;
        icon17.addPixmap(QPixmap(QString::fromUtf8(":/icons/direction8.png")), QIcon::Normal, QIcon::Off);
        pushButton_direction8->setIcon(icon17);
        pushButton_direction8->setIconSize(QSize(75, 75));
        radioButton_lowerSide = new QRadioButton(tab_3);
        radioButton_lowerSide->setObjectName(QString::fromUtf8("radioButton_lowerSide"));
        radioButton_lowerSide->setGeometry(QRect(130, 40, 51, 23));
        QIcon icon18;
        icon18.addPixmap(QPixmap(QString::fromUtf8(":/icons/lower.png")), QIcon::Normal, QIcon::Off);
        radioButton_lowerSide->setIcon(icon18);
        radioButton_lowerSide->setAutoExclusive(false);
        radioButton_upperSide = new QRadioButton(tab_3);
        radioButton_upperSide->setObjectName(QString::fromUtf8("radioButton_upperSide"));
        radioButton_upperSide->setGeometry(QRect(30, 40, 51, 23));
        QIcon icon19;
        icon19.addPixmap(QPixmap(QString::fromUtf8(":/icons/upper.png")), QIcon::Normal, QIcon::Off);
        radioButton_upperSide->setIcon(icon19);
        radioButton_upperSide->setAutoExclusive(false);
        color1 = new QToolButton(tab_3);
        color1->setObjectName(QString::fromUtf8("color1"));
        color1->setGeometry(QRect(40, 170, 45, 45));
        color1->setFont(font);
        color1->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon20;
        icon20.addPixmap(QPixmap(QString::fromUtf8(":/icons/color1.png")), QIcon::Normal, QIcon::Off);
        color1->setIcon(icon20);
        color1->setIconSize(QSize(40, 40));
        color2 = new QToolButton(tab_3);
        color2->setObjectName(QString::fromUtf8("color2"));
        color2->setGeometry(QRect(120, 170, 45, 45));
        color2->setFont(font);
        color2->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon21;
        icon21.addPixmap(QPixmap(QString::fromUtf8(":/icons/color2.png")), QIcon::Normal, QIcon::Off);
        color2->setIcon(icon21);
        color2->setIconSize(QSize(40, 40));
        QIcon icon22;
        icon22.addPixmap(QPixmap(QString::fromUtf8(":/icons/colors.png")), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_3, icon22, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setFont(font);
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(15, 140, 16, 16));
        label->setFont(font2);
        label_cyanInkValue = new QLabel(tab_2);
        label_cyanInkValue->setObjectName(QString::fromUtf8("label_cyanInkValue"));
        label_cyanInkValue->setGeometry(QRect(1, 215, 35, 20));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Ubuntu"));
        font5.setPointSize(7);
        font5.setBold(false);
        font5.setWeight(50);
        label_cyanInkValue->setFont(font5);
        label_cyanInkValue->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(65, 140, 16, 16));
        label_3->setFont(font2);
        label_magentaInkValue = new QLabel(tab_2);
        label_magentaInkValue->setObjectName(QString::fromUtf8("label_magentaInkValue"));
        label_magentaInkValue->setGeometry(QRect(50, 215, 35, 20));
        label_magentaInkValue->setFont(font5);
        label_magentaInkValue->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(115, 140, 16, 16));
        label_5->setFont(font2);
        label_yellowInkValue = new QLabel(tab_2);
        label_yellowInkValue->setObjectName(QString::fromUtf8("label_yellowInkValue"));
        label_yellowInkValue->setGeometry(QRect(100, 215, 35, 20));
        label_yellowInkValue->setFont(font5);
        label_yellowInkValue->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(165, 140, 16, 16));
        label_7->setFont(font2);
        label_blackInkValue = new QLabel(tab_2);
        label_blackInkValue->setObjectName(QString::fromUtf8("label_blackInkValue"));
        label_blackInkValue->setGeometry(QRect(150, 215, 35, 20));
        label_blackInkValue->setFont(font5);
        label_blackInkValue->setAlignment(Qt::AlignCenter);
        pushButton_decreaseCyan = new QPushButton(tab_2);
        pushButton_decreaseCyan->setObjectName(QString::fromUtf8("pushButton_decreaseCyan"));
        pushButton_decreaseCyan->setGeometry(QRect(5, 185, 30, 30));
        QFont font6;
        font6.setPointSize(9);
        font6.setBold(true);
        font6.setWeight(75);
        pushButton_decreaseCyan->setFont(font6);
        pushButton_decreaseCyan->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_increaseCyan = new QPushButton(tab_2);
        pushButton_increaseCyan->setObjectName(QString::fromUtf8("pushButton_increaseCyan"));
        pushButton_increaseCyan->setGeometry(QRect(5, 70, 30, 30));
        pushButton_increaseCyan->setFont(font6);
        pushButton_increaseCyan->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_decreaseMagenta = new QPushButton(tab_2);
        pushButton_decreaseMagenta->setObjectName(QString::fromUtf8("pushButton_decreaseMagenta"));
        pushButton_decreaseMagenta->setGeometry(QRect(55, 185, 30, 30));
        pushButton_decreaseMagenta->setFont(font6);
        pushButton_decreaseMagenta->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_increaseMagenta = new QPushButton(tab_2);
        pushButton_increaseMagenta->setObjectName(QString::fromUtf8("pushButton_increaseMagenta"));
        pushButton_increaseMagenta->setGeometry(QRect(55, 70, 30, 30));
        pushButton_increaseMagenta->setFont(font6);
        pushButton_increaseMagenta->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_decreaseYellow = new QPushButton(tab_2);
        pushButton_decreaseYellow->setObjectName(QString::fromUtf8("pushButton_decreaseYellow"));
        pushButton_decreaseYellow->setGeometry(QRect(105, 185, 30, 30));
        pushButton_decreaseYellow->setFont(font6);
        pushButton_decreaseYellow->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_increaseYellow = new QPushButton(tab_2);
        pushButton_increaseYellow->setObjectName(QString::fromUtf8("pushButton_increaseYellow"));
        pushButton_increaseYellow->setGeometry(QRect(105, 70, 30, 30));
        pushButton_increaseYellow->setFont(font6);
        pushButton_increaseYellow->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_decreaseBlack = new QPushButton(tab_2);
        pushButton_decreaseBlack->setObjectName(QString::fromUtf8("pushButton_decreaseBlack"));
        pushButton_decreaseBlack->setGeometry(QRect(155, 185, 30, 30));
        pushButton_decreaseBlack->setFont(font6);
        pushButton_decreaseBlack->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_increaseBlack = new QPushButton(tab_2);
        pushButton_increaseBlack->setObjectName(QString::fromUtf8("pushButton_increaseBlack"));
        pushButton_increaseBlack->setGeometry(QRect(155, 70, 30, 30));
        pushButton_increaseBlack->setFont(font6);
        pushButton_increaseBlack->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        lineEdit_currentInkZone = new QLineEdit(tab_2);
        lineEdit_currentInkZone->setObjectName(QString::fromUtf8("lineEdit_currentInkZone"));
        lineEdit_currentInkZone->setGeometry(QRect(80, 32, 51, 23));
        QFont font7;
        font7.setPointSize(10);
        lineEdit_currentInkZone->setFont(font7);
        lineEdit_currentInkZone->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255, 255, 255); border:1px solid}"));
        lineEdit_currentInkZone->setAlignment(Qt::AlignCenter);
        pushButton_nextInkZone = new QPushButton(tab_2);
        pushButton_nextInkZone->setObjectName(QString::fromUtf8("pushButton_nextInkZone"));
        pushButton_nextInkZone->setGeometry(QRect(140, 30, 21, 26));
        pushButton_nextInkZone->setFont(font6);
        pushButton_nextInkZone->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_lastInkZone = new QPushButton(tab_2);
        pushButton_lastInkZone->setObjectName(QString::fromUtf8("pushButton_lastInkZone"));
        pushButton_lastInkZone->setGeometry(QRect(50, 30, 21, 26));
        pushButton_lastInkZone->setFont(font6);
        pushButton_lastInkZone->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_roughAdjust = new QPushButton(tab_2);
        pushButton_roughAdjust->setObjectName(QString::fromUtf8("pushButton_roughAdjust"));
        pushButton_roughAdjust->setGeometry(QRect(20, 450, 81, 21));
        pushButton_roughAdjust->setFont(font6);
        pushButton_roughAdjust->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon23;
        icon23.addPixmap(QPixmap(QString::fromUtf8(":/icons/rough.png")), QIcon::Normal, QIcon::Off);
        pushButton_roughAdjust->setIcon(icon23);
        pushButton_roughAdjust->setIconSize(QSize(20, 20));
        pushButton_subtleAdjust = new QPushButton(tab_2);
        pushButton_subtleAdjust->setObjectName(QString::fromUtf8("pushButton_subtleAdjust"));
        pushButton_subtleAdjust->setGeometry(QRect(110, 450, 81, 21));
        pushButton_subtleAdjust->setFont(font6);
        pushButton_subtleAdjust->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon24;
        icon24.addPixmap(QPixmap(QString::fromUtf8(":/icons/subtle.png")), QIcon::Normal, QIcon::Off);
        pushButton_subtleAdjust->setIcon(icon24);
        pushButton_subtleAdjust->setIconSize(QSize(20, 20));
        pushButton_increaseColor1 = new QPushButton(tab_2);
        pushButton_increaseColor1->setObjectName(QString::fromUtf8("pushButton_increaseColor1"));
        pushButton_increaseColor1->setGeometry(QRect(35, 240, 30, 30));
        pushButton_increaseColor1->setFont(font6);
        pushButton_increaseColor1->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        label_13 = new QLabel(tab_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(35, 300, 21, 20));
        label_13->setFont(font2);
        pushButton_decreaseColor1 = new QPushButton(tab_2);
        pushButton_decreaseColor1->setObjectName(QString::fromUtf8("pushButton_decreaseColor1"));
        pushButton_decreaseColor1->setGeometry(QRect(35, 355, 30, 30));
        pushButton_decreaseColor1->setFont(font6);
        pushButton_decreaseColor1->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        label_color1InkValue = new QLabel(tab_2);
        label_color1InkValue->setObjectName(QString::fromUtf8("label_color1InkValue"));
        label_color1InkValue->setGeometry(QRect(35, 385, 35, 20));
        label_color1InkValue->setFont(font5);
        label_color1InkValue->setAlignment(Qt::AlignCenter);
        label_14 = new QLabel(tab_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(123, 300, 21, 20));
        label_14->setFont(font2);
        label_color2InkValue = new QLabel(tab_2);
        label_color2InkValue->setObjectName(QString::fromUtf8("label_color2InkValue"));
        label_color2InkValue->setGeometry(QRect(120, 385, 31, 20));
        label_color2InkValue->setFont(font5);
        label_color2InkValue->setAlignment(Qt::AlignCenter);
        pushButton_increaseColor2 = new QPushButton(tab_2);
        pushButton_increaseColor2->setObjectName(QString::fromUtf8("pushButton_increaseColor2"));
        pushButton_increaseColor2->setGeometry(QRect(120, 240, 30, 30));
        pushButton_increaseColor2->setFont(font6);
        pushButton_increaseColor2->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        pushButton_decreaseColor2 = new QPushButton(tab_2);
        pushButton_decreaseColor2->setObjectName(QString::fromUtf8("pushButton_decreaseColor2"));
        pushButton_decreaseColor2->setGeometry(QRect(120, 355, 30, 30));
        pushButton_decreaseColor2->setFont(font6);
        pushButton_decreaseColor2->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        horizontalSlider_cyanInkValue = new QSlider(tab_2);
        horizontalSlider_cyanInkValue->setObjectName(QString::fromUtf8("horizontalSlider_cyanInkValue"));
        horizontalSlider_cyanInkValue->setGeometry(QRect(35, 70, 21, 141));
        horizontalSlider_cyanInkValue->setFont(font);
        horizontalSlider_cyanInkValue->setOrientation(Qt::Vertical);
        horizontalSlider_magentaInkValue = new QSlider(tab_2);
        horizontalSlider_magentaInkValue->setObjectName(QString::fromUtf8("horizontalSlider_magentaInkValue"));
        horizontalSlider_magentaInkValue->setGeometry(QRect(85, 70, 21, 141));
        horizontalSlider_magentaInkValue->setFont(font);
        horizontalSlider_magentaInkValue->setOrientation(Qt::Vertical);
        horizontalSlider_yellowInkValue = new QSlider(tab_2);
        horizontalSlider_yellowInkValue->setObjectName(QString::fromUtf8("horizontalSlider_yellowInkValue"));
        horizontalSlider_yellowInkValue->setGeometry(QRect(135, 70, 21, 141));
        horizontalSlider_yellowInkValue->setFont(font);
        horizontalSlider_yellowInkValue->setOrientation(Qt::Vertical);
        horizontalSlider_blackInkValue = new QSlider(tab_2);
        horizontalSlider_blackInkValue->setObjectName(QString::fromUtf8("horizontalSlider_blackInkValue"));
        horizontalSlider_blackInkValue->setGeometry(QRect(185, 70, 21, 141));
        horizontalSlider_blackInkValue->setFont(font);
        horizontalSlider_blackInkValue->setOrientation(Qt::Vertical);
        horizontalSlider_color1InkValue = new QSlider(tab_2);
        horizontalSlider_color1InkValue->setObjectName(QString::fromUtf8("horizontalSlider_color1InkValue"));
        horizontalSlider_color1InkValue->setGeometry(QRect(68, 240, 21, 141));
        horizontalSlider_color1InkValue->setFont(font);
        horizontalSlider_color1InkValue->setOrientation(Qt::Vertical);
        horizontalSlider_color2InkValue = new QSlider(tab_2);
        horizontalSlider_color2InkValue->setObjectName(QString::fromUtf8("horizontalSlider_color2InkValue"));
        horizontalSlider_color2InkValue->setGeometry(QRect(153, 240, 21, 141));
        horizontalSlider_color2InkValue->setFont(font);
        horizontalSlider_color2InkValue->setOrientation(Qt::Vertical);
        pushButton_adjustBasicInk = new QPushButton(tab_2);
        pushButton_adjustBasicInk->setObjectName(QString::fromUtf8("pushButton_adjustBasicInk"));
        pushButton_adjustBasicInk->setGeometry(QRect(80, 410, 51, 21));
        pushButton_adjustBasicInk->setFont(font6);
        pushButton_adjustBasicInk->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon25;
        icon25.addPixmap(QPixmap(QString::fromUtf8(":/icons/basicInk.png")), QIcon::Normal, QIcon::Off);
        pushButton_adjustBasicInk->setIcon(icon25);
        pushButton_adjustBasicInk->setIconSize(QSize(20, 20));
        pushButton_adjustSingleInk = new QPushButton(tab_2);
        pushButton_adjustSingleInk->setObjectName(QString::fromUtf8("pushButton_adjustSingleInk"));
        pushButton_adjustSingleInk->setGeometry(QRect(140, 410, 51, 21));
        pushButton_adjustSingleInk->setFont(font6);
        pushButton_adjustSingleInk->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon26;
        icon26.addPixmap(QPixmap(QString::fromUtf8(":/icons/individualInk.png")), QIcon::Normal, QIcon::Off);
        pushButton_adjustSingleInk->setIcon(icon26);
        pushButton_adjustSingleInk->setIconSize(QSize(20, 20));
        pushButton_adjustRollerSpeed = new QPushButton(tab_2);
        pushButton_adjustRollerSpeed->setObjectName(QString::fromUtf8("pushButton_adjustRollerSpeed"));
        pushButton_adjustRollerSpeed->setGeometry(QRect(20, 410, 51, 21));
        pushButton_adjustRollerSpeed->setFont(font6);
        pushButton_adjustRollerSpeed->setStyleSheet(QString::fromUtf8("QWidget {background-color:rgb(200, 200, 200);}"));
        QIcon icon27;
        icon27.addPixmap(QPixmap(QString::fromUtf8(":/icons/rollerSpeed.png")), QIcon::Normal, QIcon::Off);
        pushButton_adjustRollerSpeed->setIcon(icon27);
        pushButton_adjustRollerSpeed->setIconSize(QSize(20, 20));
        QIcon icon28;
        icon28.addPixmap(QPixmap(QString::fromUtf8(":/icons/details.png")), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_2, icon28, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalSlider_cyanInkThickness = new QSlider(tab_4);
        verticalSlider_cyanInkThickness->setObjectName(QString::fromUtf8("verticalSlider_cyanInkThickness"));
        verticalSlider_cyanInkThickness->setGeometry(QRect(20, 280, 20, 181));
        verticalSlider_cyanInkThickness->setMinimum(0);
        verticalSlider_cyanInkThickness->setMaximum(30);
        verticalSlider_cyanInkThickness->setValue(0);
        verticalSlider_cyanInkThickness->setOrientation(Qt::Vertical);
        radioButton_paper4 = new QRadioButton(tab_4);
        radioButton_paper4->setObjectName(QString::fromUtf8("radioButton_paper4"));
        radioButton_paper4->setGeometry(QRect(120, 190, 61, 41));
        QFont font8;
        font8.setPointSize(7);
        radioButton_paper4->setFont(font8);
        radioButton_paper3 = new QRadioButton(tab_4);
        radioButton_paper3->setObjectName(QString::fromUtf8("radioButton_paper3"));
        radioButton_paper3->setGeometry(QRect(120, 130, 61, 41));
        radioButton_paper3->setFont(font8);
        radioButton_paper2 = new QRadioButton(tab_4);
        radioButton_paper2->setObjectName(QString::fromUtf8("radioButton_paper2"));
        radioButton_paper2->setGeometry(QRect(120, 70, 61, 41));
        radioButton_paper2->setFont(font8);
        radioButton_paper1 = new QRadioButton(tab_4);
        radioButton_paper1->setObjectName(QString::fromUtf8("radioButton_paper1"));
        radioButton_paper1->setGeometry(QRect(120, 10, 61, 41));
        radioButton_paper1->setFont(font8);
        radioButton_Ink1 = new QRadioButton(tab_4);
        radioButton_Ink1->setObjectName(QString::fromUtf8("radioButton_Ink1"));
        radioButton_Ink1->setGeometry(QRect(30, 10, 61, 41));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Ubuntu"));
        font9.setPointSize(7);
        radioButton_Ink1->setFont(font9);
        radioButton_Ink1->setAutoExclusive(true);
        radioButton_Ink2 = new QRadioButton(tab_4);
        radioButton_Ink2->setObjectName(QString::fromUtf8("radioButton_Ink2"));
        radioButton_Ink2->setGeometry(QRect(30, 70, 61, 41));
        radioButton_Ink2->setFont(font8);
        radioButton_Ink2->setAutoExclusive(true);
        radioButton_Ink3 = new QRadioButton(tab_4);
        radioButton_Ink3->setObjectName(QString::fromUtf8("radioButton_Ink3"));
        radioButton_Ink3->setGeometry(QRect(30, 130, 61, 41));
        radioButton_Ink3->setFont(font8);
        radioButton_Ink3->setAutoExclusive(true);
        radioButton_Ink4 = new QRadioButton(tab_4);
        radioButton_Ink4->setObjectName(QString::fromUtf8("radioButton_Ink4"));
        radioButton_Ink4->setGeometry(QRect(30, 190, 61, 41));
        radioButton_Ink4->setFont(font8);
        radioButton_Ink4->setAutoExclusive(true);
        label_2 = new QLabel(tab_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 260, 16, 16));
        QFont font10;
        font10.setFamily(QString::fromUtf8("WenQuanYi Zen Hei"));
        font10.setPointSize(7);
        font10.setBold(true);
        font10.setWeight(75);
        label_2->setFont(font10);
        label_6 = new QLabel(tab_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(70, 260, 16, 16));
        label_6->setFont(font10);
        label_8 = new QLabel(tab_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(120, 260, 16, 16));
        label_8->setFont(font10);
        label_12 = new QLabel(tab_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(170, 260, 16, 16));
        label_12->setFont(font10);
        verticalSlider_magentaInkThickness = new QSlider(tab_4);
        verticalSlider_magentaInkThickness->setObjectName(QString::fromUtf8("verticalSlider_magentaInkThickness"));
        verticalSlider_magentaInkThickness->setGeometry(QRect(70, 280, 20, 181));
        verticalSlider_magentaInkThickness->setMinimum(0);
        verticalSlider_magentaInkThickness->setMaximum(25);
        verticalSlider_magentaInkThickness->setValue(0);
        verticalSlider_magentaInkThickness->setOrientation(Qt::Vertical);
        verticalSlider_yellowInkThickness = new QSlider(tab_4);
        verticalSlider_yellowInkThickness->setObjectName(QString::fromUtf8("verticalSlider_yellowInkThickness"));
        verticalSlider_yellowInkThickness->setGeometry(QRect(120, 280, 20, 181));
        verticalSlider_yellowInkThickness->setMinimum(0);
        verticalSlider_yellowInkThickness->setMaximum(25);
        verticalSlider_yellowInkThickness->setValue(0);
        verticalSlider_yellowInkThickness->setOrientation(Qt::Vertical);
        verticalSlider_blackInkThickness = new QSlider(tab_4);
        verticalSlider_blackInkThickness->setObjectName(QString::fromUtf8("verticalSlider_blackInkThickness"));
        verticalSlider_blackInkThickness->setGeometry(QRect(170, 280, 20, 181));
        verticalSlider_blackInkThickness->setMinimum(0);
        verticalSlider_blackInkThickness->setMaximum(40);
        verticalSlider_blackInkThickness->setValue(0);
        verticalSlider_blackInkThickness->setOrientation(Qt::Vertical);
        label_15 = new QLabel(tab_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(80, 500, 57, 15));
        label_15->setFont(font8);
        label_15->setAlignment(Qt::AlignCenter);
        label_cyanInkThickness = new QLabel(tab_4);
        label_cyanInkThickness->setObjectName(QString::fromUtf8("label_cyanInkThickness"));
        label_cyanInkThickness->setGeometry(QRect(10, 470, 31, 16));
        label_cyanInkThickness->setFont(font8);
        label_cyanInkThickness->setAlignment(Qt::AlignCenter);
        label_magentaInkThickness = new QLabel(tab_4);
        label_magentaInkThickness->setObjectName(QString::fromUtf8("label_magentaInkThickness"));
        label_magentaInkThickness->setGeometry(QRect(60, 470, 31, 16));
        label_magentaInkThickness->setFont(font8);
        label_magentaInkThickness->setAlignment(Qt::AlignCenter);
        label_yellowInkThickness = new QLabel(tab_4);
        label_yellowInkThickness->setObjectName(QString::fromUtf8("label_yellowInkThickness"));
        label_yellowInkThickness->setGeometry(QRect(110, 470, 31, 16));
        label_yellowInkThickness->setFont(font8);
        label_yellowInkThickness->setAlignment(Qt::AlignCenter);
        label_blackInkThickness = new QLabel(tab_4);
        label_blackInkThickness->setObjectName(QString::fromUtf8("label_blackInkThickness"));
        label_blackInkThickness->setGeometry(QRect(160, 470, 31, 16));
        label_blackInkThickness->setFont(font8);
        label_blackInkThickness->setAlignment(Qt::AlignCenter);
        QIcon icon29;
        icon29.addPixmap(QPixmap(QString::fromUtf8(":/icons/curve.png")), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab_4, icon29, QString());
        widget_status = new QWidget(centralWidget);
        widget_status->setObjectName(QString::fromUtf8("widget_status"));
        widget_status->setGeometry(QRect(250, 250, 301, 101));
        widget_status->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(200,200,200);border:2px outset rgb(180,180,180)}"));
        label_processStatus = new QLabel(widget_status);
        label_processStatus->setObjectName(QString::fromUtf8("label_processStatus"));
        label_processStatus->setGeometry(QRect(10, 10, 281, 20));
        QFont font11;
        font11.setPointSize(8);
        label_processStatus->setFont(font11);
        label_processStatus->setStyleSheet(QString::fromUtf8("QWidget{border:0px solid gray;}"));
        progressBar = new QProgressBar(widget_status);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 40, 281, 20));
        progressBar->setFont(font);
        progressBar->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255,255,255);border:1px solid}"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);
        pushButton_sure = new QPushButton(widget_status);
        pushButton_sure->setObjectName(QString::fromUtf8("pushButton_sure"));
        pushButton_sure->setGeometry(QRect(210, 70, 81, 20));
        pushButton_sure->setFont(font7);
        pushButton_sure->setStyleSheet(QString::fromUtf8("QWidget{border:1px outset rgb(180,180,180)}"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 800, 46));
        widget->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(114, 136, 172); border-style:outset;border-width:2px;border-color:rgb(114, 136, 172)}"));
        actionOpen = new QPushButton(widget);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setGeometry(QRect(11, 3, 40, 40));
        actionOpen->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon30;
        icon30.addPixmap(QPixmap(QString::fromUtf8(":/icons/Picture-TIFF-32x32.png")), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon30);
        actionOpen->setIconSize(QSize(32, 32));
        actionSync = new QPushButton(widget);
        actionSync->setObjectName(QString::fromUtf8("actionSync"));
        actionSync->setGeometry(QRect(56, 3, 40, 40));
        actionSync->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon31;
        icon31.addPixmap(QPixmap(QString::fromUtf8(":/icons/Connect-32x32.png")), QIcon::Normal, QIcon::Off);
        actionSync->setIcon(icon31);
        actionSync->setIconSize(QSize(32, 32));
        actionSave = new QPushButton(widget);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setGeometry(QRect(101, 3, 40, 40));
        actionSave->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon32;
        icon32.addPixmap(QPixmap(QString::fromUtf8(":/icons/save-32x32.png")), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon32);
        actionSave->setIconSize(QSize(32, 32));
        actionDelete = new QPushButton(widget);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionDelete->setGeometry(QRect(146, 3, 40, 40));
        actionDelete->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon33;
        icon33.addPixmap(QPixmap(QString::fromUtf8(":/icons/delete.png")), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon33);
        actionDelete->setIconSize(QSize(32, 32));
        actionZoomIn = new QPushButton(widget);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        actionZoomIn->setGeometry(QRect(191, 3, 40, 40));
        actionZoomIn->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon34;
        icon34.addPixmap(QPixmap(QString::fromUtf8(":/icons/zoom_in.png")), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon34);
        actionZoomIn->setIconSize(QSize(36, 36));
        actionSettings = new QPushButton(widget);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionSettings->setGeometry(QRect(236, 3, 40, 40));
        actionSettings->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon35;
        icon35.addPixmap(QPixmap(QString::fromUtf8(":/icons/Settings-icon.png")), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon35);
        actionSettings->setIconSize(QSize(32, 32));
        progressBar_battery = new QProgressBar(widget);
        progressBar_battery->setObjectName(QString::fromUtf8("progressBar_battery"));
        progressBar_battery->setGeometry(QRect(750, 12, 41, 22));
        progressBar_battery->setFont(font11);
        progressBar_battery->setStyleSheet(QString::fromUtf8("QProgressBar{background-color:rgb(255,255,255);border:1px inset rgb(200,200,200);} QProgressBar::chunk{background-color:qlineargradient(spread:reflect, x1:1, y1:0.506, x2:1, y2:0, stop:0 rgba(0, 191, 0, 255), stop:1 rgba(255, 255, 255, 255))}"));
        progressBar_battery->setValue(100);
        progressBar_battery->setAlignment(Qt::AlignCenter);
        progressBar_battery->setTextVisible(false);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(790, 19, 5, 10));
        label_4->setStyleSheet(QString::fromUtf8("QLabel{background:rgb(200,200,200);border:1px outset rgb(180,180,180)}"));
        label_connection = new QLabel(widget);
        label_connection->setObjectName(QString::fromUtf8("label_connection"));
        label_connection->setGeometry(QRect(710, 10, 30, 30));
        label_connection->setStyleSheet(QString::fromUtf8("QWidget{border:0px}"));
        label_connection->setPixmap(QPixmap(QString::fromUtf8(":/icons/network-disconnected.png")));
        label_connection->setScaledContents(true);
        actionShutDown = new QPushButton(widget);
        actionShutDown->setObjectName(QString::fromUtf8("actionShutDown"));
        actionShutDown->setGeometry(QRect(281, 3, 40, 40));
        actionShutDown->setStyleSheet(QString::fromUtf8("QWidget{border:0px}\n"
"QWidget:hover{border:1px solid}"));
        QIcon icon36;
        icon36.addPixmap(QPixmap(QString::fromUtf8(":/icons/Turn-Off-icon.png")), QIcon::Normal, QIcon::Off);
        actionShutDown->setIcon(icon36);
        actionShutDown->setIconSize(QSize(32, 32));
        widget_ip = new QWidget(centralWidget);
        widget_ip->setObjectName(QString::fromUtf8("widget_ip"));
        widget_ip->setGeometry(QRect(300, 200, 200, 121));
        widget_ip->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(200,200,200)}"));
        label_ip = new QLabel(widget_ip);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setGeometry(QRect(10, 10, 180, 20));
        label_ip->setFont(font11);
        label_ip->setStyleSheet(QString::fromUtf8("QWidget{border:0px solid gray;}"));
        lineEdit_ipAddress = new QLineEdit(widget_ip);
        lineEdit_ipAddress->setObjectName(QString::fromUtf8("lineEdit_ipAddress"));
        lineEdit_ipAddress->setGeometry(QRect(10, 40, 181, 25));
        lineEdit_ipAddress->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(255,255,255);border: 1px solid}"));
        pushButton_enterIP = new QPushButton(widget_ip);
        pushButton_enterIP->setObjectName(QString::fromUtf8("pushButton_enterIP"));
        pushButton_enterIP->setGeometry(QRect(10, 80, 80, 26));
        pushButton_enterIP->setFont(font4);
        pushButton_enterIP->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        pushButton_cancelIP = new QPushButton(widget_ip);
        pushButton_cancelIP->setObjectName(QString::fromUtf8("pushButton_cancelIP"));
        pushButton_cancelIP->setGeometry(QRect(110, 80, 80, 26));
        pushButton_cancelIP->setFont(font4);
        pushButton_cancelIP->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        widget_deleteFileList = new QWidget(centralWidget);
        widget_deleteFileList->setObjectName(QString::fromUtf8("widget_deleteFileList"));
        widget_deleteFileList->setGeometry(QRect(130, 110, 421, 431));
        widget_deleteFileList->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(200,200,200)}"));
        scrollArea_deleteFile = new QScrollArea(widget_deleteFileList);
        scrollArea_deleteFile->setObjectName(QString::fromUtf8("scrollArea_deleteFile"));
        scrollArea_deleteFile->setGeometry(QRect(10, 35, 401, 341));
        scrollArea_deleteFile->setFont(font11);
        scrollArea_deleteFile->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(244,244,244)}"));
        scrollArea_deleteFile->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 397, 337));
        scrollArea_deleteFile->setWidget(scrollAreaWidgetContents_3);
        label_10 = new QLabel(widget_deleteFileList);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 6, 181, 21));
        QFont font12;
        font12.setPointSize(8);
        font12.setBold(true);
        font12.setWeight(75);
        label_10->setFont(font12);
        label_10->setStyleSheet(QString::fromUtf8("QWidget{border:none}"));
        pushButton_selectFileToDelete = new QPushButton(widget_deleteFileList);
        pushButton_selectFileToDelete->setObjectName(QString::fromUtf8("pushButton_selectFileToDelete"));
        pushButton_selectFileToDelete->setGeometry(QRect(10, 390, 121, 27));
        pushButton_selectFileToDelete->setFont(font1);
        pushButton_selectFileToDelete->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        pushButton_cancelDelete = new QPushButton(widget_deleteFileList);
        pushButton_cancelDelete->setObjectName(QString::fromUtf8("pushButton_cancelDelete"));
        pushButton_cancelDelete->setGeometry(QRect(290, 390, 121, 27));
        pushButton_cancelDelete->setFont(font1);
        pushButton_cancelDelete->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        widget_machineModel = new QWidget(centralWidget);
        widget_machineModel->setObjectName(QString::fromUtf8("widget_machineModel"));
        widget_machineModel->setGeometry(QRect(280, 110, 241, 261));
        widget_machineModel->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(200,200,200)}"));
        scrollArea_machineModel = new QScrollArea(widget_machineModel);
        scrollArea_machineModel->setObjectName(QString::fromUtf8("scrollArea_machineModel"));
        scrollArea_machineModel->setGeometry(QRect(10, 35, 221, 171));
        scrollArea_machineModel->setFont(font11);
        scrollArea_machineModel->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(244,244,244)}"));
        scrollArea_machineModel->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 217, 167));
        scrollArea_machineModel->setWidget(scrollAreaWidgetContents_4);
        label_11 = new QLabel(widget_machineModel);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 6, 181, 21));
        label_11->setFont(font12);
        label_11->setStyleSheet(QString::fromUtf8("QWidget{border:none}"));
        pushButton_selectMachineModel = new QPushButton(widget_machineModel);
        pushButton_selectMachineModel->setObjectName(QString::fromUtf8("pushButton_selectMachineModel"));
        pushButton_selectMachineModel->setGeometry(QRect(10, 220, 91, 27));
        pushButton_selectMachineModel->setFont(font1);
        pushButton_selectMachineModel->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        pushButton_cancelMachineSelection = new QPushButton(widget_machineModel);
        pushButton_cancelMachineSelection->setObjectName(QString::fromUtf8("pushButton_cancelMachineSelection"));
        pushButton_cancelMachineSelection->setGeometry(QRect(140, 220, 91, 27));
        pushButton_cancelMachineSelection->setFont(font1);
        pushButton_cancelMachineSelection->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        widget_fileList = new QWidget(centralWidget);
        widget_fileList->setObjectName(QString::fromUtf8("widget_fileList"));
        widget_fileList->setGeometry(QRect(130, 110, 421, 431));
        widget_fileList->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(200,200,200)}"));
        scrollArea = new QScrollArea(widget_fileList);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 35, 401, 341));
        scrollArea->setFont(font11);
        scrollArea->setStyleSheet(QString::fromUtf8("QWidget{background:rgb(244,244,244)}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 397, 337));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_9 = new QLabel(widget_fileList);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 6, 181, 21));
        label_9->setFont(font12);
        label_9->setStyleSheet(QString::fromUtf8("QWidget{border:none}"));
        pushButton_selectFile = new QPushButton(widget_fileList);
        pushButton_selectFile->setObjectName(QString::fromUtf8("pushButton_selectFile"));
        pushButton_selectFile->setGeometry(QRect(10, 390, 121, 27));
        pushButton_selectFile->setFont(font1);
        pushButton_selectFile->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        pushButton_cancelSelect = new QPushButton(widget_fileList);
        pushButton_cancelSelect->setObjectName(QString::fromUtf8("pushButton_cancelSelect"));
        pushButton_cancelSelect->setGeometry(QRect(290, 390, 121, 27));
        pushButton_cancelSelect->setFont(font1);
        pushButton_cancelSelect->setStyleSheet(QString::fromUtf8("QWidget:pressed{border:1px inset rgb(180,180,180)}"));
        pushButton_showTabWidget = new QPushButton(centralWidget);
        pushButton_showTabWidget->setObjectName(QString::fromUtf8("pushButton_showTabWidget"));
        pushButton_showTabWidget->setGeometry(QRect(556, 55, 26, 26));
        pushButton_showTabWidget->setStyleSheet(QString::fromUtf8("QPushButton {background-color:rgb(200, 200, 200);}\n"
""));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_selectFile, SIGNAL(clicked()), MainWindow, SLOT(physicalSelectButtonPressed()));
        QObject::connect(pushButton_cancelSelect, SIGNAL(clicked()), MainWindow, SLOT(cancelSelect()));
        QObject::connect(pushButton_cancelSelect, SIGNAL(clicked()), MainWindow, SLOT(physicalCancelButtonPressed()));
        QObject::connect(actionSave, SIGNAL(clicked()), MainWindow, SLOT(saveInkValue()));
        QObject::connect(actionOpen, SIGNAL(clicked()), MainWindow, SLOT(openFile()));
        QObject::connect(actionSync, SIGNAL(clicked()), MainWindow, SLOT(makeConnection()));
        QObject::connect(actionDelete, SIGNAL(clicked()), MainWindow, SLOT(deleteFile()));
        QObject::connect(actionZoomIn, SIGNAL(clicked()), MainWindow, SLOT(zoomInInkValue()));
        QObject::connect(actionSettings, SIGNAL(clicked()), MainWindow, SLOT(reviseParameters()));
        QObject::connect(pushButton_sure, SIGNAL(clicked()), MainWindow, SLOT(eliminateStatusWidget()));
        QObject::connect(pushButton_selectFileToDelete, SIGNAL(clicked()), MainWindow, SLOT(physicalSelectButtonPressed()));
        QObject::connect(pushButton_cancelDelete, SIGNAL(clicked()), MainWindow, SLOT(physicalCancelButtonPressed()));
        QObject::connect(pushButton_selectMachineModel, SIGNAL(clicked()), MainWindow, SLOT(physicalSelectButtonPressed()));
        QObject::connect(pushButton_cancelMachineSelection, SIGNAL(clicked()), MainWindow, SLOT(physicalCancelButtonPressed()));
        QObject::connect(cyan, SIGNAL(clicked()), MainWindow, SLOT(showCyanComponent()));
        QObject::connect(magenta, SIGNAL(clicked()), MainWindow, SLOT(showMagentaComponent()));
        QObject::connect(yellow, SIGNAL(clicked()), MainWindow, SLOT(showYellowComponent()));
        QObject::connect(black, SIGNAL(clicked()), MainWindow, SLOT(showBlackComponent()));
        QObject::connect(tabWidget, SIGNAL(currentChanged(int)), MainWindow, SLOT(switchGroupBox()));
        QObject::connect(pushButton_dot, SIGNAL(clicked()), MainWindow, SLOT(inputDot()));
        QObject::connect(pushButton_eight, SIGNAL(clicked()), MainWindow, SLOT(inputEight()));
        QObject::connect(pushButton_enter, SIGNAL(clicked()), MainWindow, SLOT(inputEnter()));
        QObject::connect(pushButton_five, SIGNAL(clicked()), MainWindow, SLOT(inputFive()));
        QObject::connect(pushButton_four, SIGNAL(clicked()), MainWindow, SLOT(inputFour()));
        QObject::connect(pushButton_nine, SIGNAL(clicked()), MainWindow, SLOT(inputNine()));
        QObject::connect(pushButton_one, SIGNAL(clicked()), MainWindow, SLOT(inputOne()));
        QObject::connect(pushButton_decreaseMagenta, SIGNAL(clicked()), MainWindow, SLOT(decreaseMagenta()));
        QObject::connect(pushButton_seven, SIGNAL(clicked()), MainWindow, SLOT(inputSeven()));
        QObject::connect(pushButton_six, SIGNAL(clicked()), MainWindow, SLOT(inputSix()));
        QObject::connect(pushButton_three, SIGNAL(clicked()), MainWindow, SLOT(inputThree()));
        QObject::connect(pushButton_two, SIGNAL(clicked()), MainWindow, SLOT(inputTwo()));
        QObject::connect(pushButton_zero, SIGNAL(clicked()), MainWindow, SLOT(inputZero()));
        QObject::connect(pushButton_fountainWidth, SIGNAL(clicked()), MainWindow, SLOT(setParameter_fountainWidth()));
        QObject::connect(pushButton_plateHeight, SIGNAL(clicked()), MainWindow, SLOT(setParameter_plateHeight()));
        QObject::connect(pushButton_delete, SIGNAL(clicked()), MainWindow, SLOT(inputDelete()));
        QObject::connect(pushButton_maxInkValue, SIGNAL(clicked()), MainWindow, SLOT(setParameter_maxInkValue()));
        QObject::connect(pushButton_lastInkZone, SIGNAL(clicked()), MainWindow, SLOT(showLastInkZone()));
        QObject::connect(pushButton_nextInkZone, SIGNAL(clicked()), MainWindow, SLOT(showNextInkZone()));
        QObject::connect(pushButton_decreaseCyan, SIGNAL(clicked()), MainWindow, SLOT(decreaseCyan()));
        QObject::connect(pushButton_increaseCyan, SIGNAL(clicked()), MainWindow, SLOT(increaseCyan()));
        QObject::connect(pushButton_increaseMagenta, SIGNAL(clicked()), MainWindow, SLOT(increaseMagenta()));
        QObject::connect(pushButton_increaseYellow, SIGNAL(clicked()), MainWindow, SLOT(increaseYellow()));
        QObject::connect(pushButton_decreaseYellow, SIGNAL(clicked()), MainWindow, SLOT(decreaseYellow()));
        QObject::connect(pushButton_increaseBlack, SIGNAL(clicked()), MainWindow, SLOT(increaseBlack()));
        QObject::connect(pushButton_decreaseBlack, SIGNAL(clicked()), MainWindow, SLOT(decreaseBlack()));
        QObject::connect(pushButton_KeyNumbers, SIGNAL(clicked()), MainWindow, SLOT(setParameter_inkKeyValues()));
        QObject::connect(radioButton_upperSide, SIGNAL(clicked()), MainWindow, SLOT(showUpperSide()));
        QObject::connect(pushButton_inkFraction, SIGNAL(clicked()), MainWindow, SLOT(setParameter_inkFraction()));
        QObject::connect(radioButton_lowerSide, SIGNAL(clicked()), MainWindow, SLOT(showDownSide()));
        QObject::connect(pushButton_direction1, SIGNAL(clicked()), MainWindow, SLOT(direction1()));
        QObject::connect(pushButton_direction2, SIGNAL(clicked()), MainWindow, SLOT(direction2()));
        QObject::connect(pushButton_direction3, SIGNAL(clicked()), MainWindow, SLOT(direction3()));
        QObject::connect(pushButton_direction4, SIGNAL(clicked()), MainWindow, SLOT(direction4()));
        QObject::connect(pushButton_direction5, SIGNAL(clicked()), MainWindow, SLOT(direction5()));
        QObject::connect(pushButton_direction6, SIGNAL(clicked()), MainWindow, SLOT(direction6()));
        QObject::connect(pushButton_direction7, SIGNAL(clicked()), MainWindow, SLOT(direction7()));
        QObject::connect(pushButton_direction8, SIGNAL(clicked()), MainWindow, SLOT(direction8()));
        QObject::connect(radioButton_oneSide, SIGNAL(clicked()), MainWindow, SLOT(setToOneSide()));
        QObject::connect(radioButton_twoSides, SIGNAL(clicked()), MainWindow, SLOT(setToTwoSides()));
        QObject::connect(pushButton_enterParameters, SIGNAL(clicked()), MainWindow, SLOT(enterParameters()));
        QObject::connect(pushButton_roughAdjust, SIGNAL(clicked()), MainWindow, SLOT(setRoughAdjustment()));
        QObject::connect(pushButton_subtleAdjust, SIGNAL(clicked()), MainWindow, SLOT(setSubtleAdjustment()));
        QObject::connect(color1, SIGNAL(clicked()), MainWindow, SLOT(showColor1Component()));
        QObject::connect(color2, SIGNAL(clicked()), MainWindow, SLOT(showColor2Component()));
        QObject::connect(pushButton_adjustBasicInk, SIGNAL(clicked()), MainWindow, SLOT(setToBasicAdjustment()));
        QObject::connect(pushButton_adjustSingleInk, SIGNAL(clicked()), MainWindow, SLOT(setToSingleAdjustment()));
        QObject::connect(pushButton_increaseColor1, SIGNAL(clicked()), MainWindow, SLOT(increaseColor1()));
        QObject::connect(pushButton_increaseColor2, SIGNAL(clicked()), MainWindow, SLOT(increaseColor2()));
        QObject::connect(pushButton_decreaseColor1, SIGNAL(clicked()), MainWindow, SLOT(decreaseColor1()));
        QObject::connect(pushButton_decreaseColor2, SIGNAL(clicked()), MainWindow, SLOT(decreaseColor2()));
        QObject::connect(pushButton_adjustRollerSpeed, SIGNAL(clicked()), MainWindow, SLOT(setToRollerSpeedAdjustment()));
        QObject::connect(radioButton_paper4, SIGNAL(clicked()), MainWindow, SLOT(setToPaper4()));
        QObject::connect(radioButton_paper3, SIGNAL(clicked()), MainWindow, SLOT(setToPaper3()));
        QObject::connect(radioButton_paper2, SIGNAL(clicked()), MainWindow, SLOT(setToPaper2()));
        QObject::connect(radioButton_paper1, SIGNAL(clicked()), MainWindow, SLOT(setToPaper1()));
        QObject::connect(radioButton_Ink1, SIGNAL(clicked()), MainWindow, SLOT(setToInk1()));
        QObject::connect(radioButton_Ink2, SIGNAL(clicked()), MainWindow, SLOT(setToInk2()));
        QObject::connect(radioButton_Ink3, SIGNAL(clicked()), MainWindow, SLOT(setToInk3()));
        QObject::connect(radioButton_Ink4, SIGNAL(clicked()), MainWindow, SLOT(setToInk4()));
        QObject::connect(pushButton_showTabWidget, SIGNAL(clicked()), MainWindow, SLOT(show_hideTabWidget()));
        QObject::connect(pushButton_enterIP, SIGNAL(clicked()), MainWindow, SLOT(inputEnter()));
        QObject::connect(pushButton_cancelIP, SIGNAL(clicked()), MainWindow, SLOT(physicalCancelButtonPressed()));
        QObject::connect(pushButton_totalColors, SIGNAL(clicked()), MainWindow, SLOT(setParameter_totalColors()));
        QObject::connect(actionShutDown, SIGNAL(clicked()), MainWindow, SLOT(shutDownLinux()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\262\271\345\242\250\351\242\204\347\275\256\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButton_oneSide->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\215\225\351\235\242\345\215\260\345\210\267\346\234\272</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton_oneSide->setText(QApplication::translate("MainWindow", "\345\215\225\351\235\242", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButton_twoSides->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\346\255\243\345\217\215\344\270\244\351\235\242\345\215\260\345\210\267\346\234\272</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton_twoSides->setText(QApplication::translate("MainWindow", "\346\255\243\345\217\215", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_fountainWidth->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\242\250\347\233\222\345\256\275\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_fountainWidth->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_plateHeight->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\215\260\347\211\210\351\225\277\345\272\246</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_plateHeight->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_maxInkValue->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'WenQuanYi Zen Hei'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu';\">\345\242\250\345\214\272\346\234\200\345\244\247\345\200\274</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_maxInkValue->setText(QApplication::translate("MainWindow", "100%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_KeyNumbers->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\242\250\351\224\256\346\225\260\351\207\217</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_KeyNumbers->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_enter->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\350\276\223\345\205\245</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_enter->setText(QString());
        pushButton_seven->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
        pushButton_dot->setText(QApplication::translate("MainWindow", ".", 0, QApplication::UnicodeUTF8));
        pushButton_five->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        pushButton_nine->setText(QApplication::translate("MainWindow", "9", 0, QApplication::UnicodeUTF8));
        pushButton_four->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        pushButton_zero->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pushButton_one->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        pushButton_two->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_delete->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\210\240\351\231\244</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_delete->setText(QApplication::translate("MainWindow", "DEL", 0, QApplication::UnicodeUTF8));
        pushButton_six->setText(QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8));
        pushButton_eight->setText(QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8));
        pushButton_three->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_inkFraction->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'WenQuanYi Zen Hei'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<table style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu';\">\345\242\250\345\214\272\345\200\274\345\260\217\346\225\260\351\203\250\345\210\206</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_inkFraction->setText(QApplication::translate("MainWindow", ".?", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_enterParameters->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\350\276\223\345\205\245</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_enterParameters->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_totalColors->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\"-qt-table-type: root; margin-top:4px; margin-bottom:4px; margin-left:4px; margin-right:4px;\">\n"
"<tr>\n"
"<td style=\"border: none;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'WenQuanYi Zen Hei'; font-size:8pt;\">\350\211\262\345\275\251\346\225\260\351\207\217</span></p></td></tr></table></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_totalColors->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
#ifndef QT_NO_TOOLTIP
        cyan->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">C</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cyan->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        magenta->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">M</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        magenta->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        yellow->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Y</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        yellow->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        black->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        black->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction1->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\210\235\345\247\213\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction2->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">90\345\272\246\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction3->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">180\345\272\246\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction3->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction4->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">270\345\272\246\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction4->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction5->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\346\250\252\345\220\221\347\277\273\350\275\254</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction5->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction6->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\277\273\350\275\254/90\345\272\246\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction6->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction7->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\277\273\350\275\254/180\345\272\246\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction7->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_direction8->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\277\273\350\275\254/270\345\272\246\346\226\271\345\220\221</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_direction8->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButton_lowerSide->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\217\215\351\235\242</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton_lowerSide->setText(QString());
#ifndef QT_NO_TOOLTIP
        radioButton_upperSide->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\346\255\243\351\235\242</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton_upperSide->setText(QString());
#ifndef QT_NO_TOOLTIP
        color1->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        color1->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        color2->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        color2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QString());
        label->setText(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
        label_cyanInkValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "M", 0, QApplication::UnicodeUTF8));
        label_magentaInkValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        label_yellowInkValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "K", 0, QApplication::UnicodeUTF8));
        label_blackInkValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_decreaseCyan->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">C\345\200\274\344\270\213\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_decreaseCyan->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_increaseCyan->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">C\345\200\274\344\270\212\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_increaseCyan->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_decreaseMagenta->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">M\345\200\274\344\270\213\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_decreaseMagenta->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_increaseMagenta->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">M\345\200\274\344\270\212\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_increaseMagenta->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_decreaseYellow->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Y\345\200\274\344\270\213\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_decreaseYellow->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_increaseYellow->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Y\345\200\274\344\270\212\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_increaseYellow->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_decreaseBlack->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K\345\200\274\344\270\213\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_decreaseBlack->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_increaseBlack->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K\345\200\274\344\270\212\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_increaseBlack->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        lineEdit_currentInkZone->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_nextInkZone->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\344\270\213\344\270\252\345\242\250\345\214\272</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_nextInkZone->setText(QApplication::translate("MainWindow", "->", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_lastInkZone->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\344\270\212\344\270\252\345\242\250\345\214\272</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_lastInkZone->setText(QApplication::translate("MainWindow", "<-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_roughAdjust->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\262\227\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_roughAdjust->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_subtleAdjust->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\276\256\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_subtleAdjust->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_increaseColor1->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K\345\200\274\344\270\212\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_increaseColor1->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "S1", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_decreaseColor1->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K\345\200\274\344\270\213\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_decreaseColor1->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        label_color1InkValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "S2", 0, QApplication::UnicodeUTF8));
        label_color2InkValue->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_increaseColor2->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K\345\200\274\344\270\212\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_increaseColor2->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_decreaseColor2->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">K\345\200\274\344\270\213\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_decreaseColor2->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_adjustBasicInk->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\262\227\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_adjustBasicInk->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_adjustSingleInk->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\262\227\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_adjustSingleInk->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_adjustRollerSpeed->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\347\262\227\350\260\203</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_adjustRollerSpeed->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QString());
        radioButton_paper4->setText(QApplication::translate("MainWindow", "\346\226\260\351\227\273\347\272\270", 0, QApplication::UnicodeUTF8));
        radioButton_paper3->setText(QApplication::translate("MainWindow", "\351\235\236\346\266\202\n"
"\346\226\231\347\272\270", 0, QApplication::UnicodeUTF8));
        radioButton_paper2->setText(QApplication::translate("MainWindow", "\345\223\221\345\205\211\n"
"\346\266\202\346\226\231\347\272\270", 0, QApplication::UnicodeUTF8));
        radioButton_paper1->setText(QApplication::translate("MainWindow", "\351\253\230\345\205\211\n"
"\346\266\202\346\226\231\347\272\270", 0, QApplication::UnicodeUTF8));
        radioButton_Ink1->setText(QApplication::translate("MainWindow", "\346\262\271\345\242\2501", 0, QApplication::UnicodeUTF8));
        radioButton_Ink2->setText(QApplication::translate("MainWindow", "\346\262\271\345\242\2502", 0, QApplication::UnicodeUTF8));
        radioButton_Ink3->setText(QApplication::translate("MainWindow", "\346\262\271\345\242\2503", 0, QApplication::UnicodeUTF8));
        radioButton_Ink4->setText(QApplication::translate("MainWindow", "\346\262\271\345\242\2504", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "C", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "M", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "K", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "\345\242\250\345\261\202\345\216\232\345\272\246", 0, QApplication::UnicodeUTF8));
        label_cyanInkThickness->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_magentaInkThickness->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_yellowInkThickness->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_blackInkThickness->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QString());
        label_processStatus->setText(QApplication::translate("MainWindow", "\346\255\243\345\234\250\350\216\267\345\217\226\346\226\207\344\273\266\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        progressBar->setFormat(QApplication::translate("MainWindow", "%p%", 0, QApplication::UnicodeUTF8));
        pushButton_sure->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\346\211\223\345\274\200\346\226\207\344\273\266</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionSync->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\350\277\236\346\216\245\344\270\273\346\234\272</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSync->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\344\277\235\345\255\230</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\345\210\240\351\231\244\346\226\207\344\273\266</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDelete->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionZoomIn->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\346\270\205\351\233\266</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionZoomIn->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionSettings->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\350\256\276\347\275\256\345\217\202\346\225\260</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSettings->setText(QString());
        label_4->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_connection->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\350\277\236\346\216\245\347\212\266\346\200\201</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_connection->setText(QString());
#ifndef QT_NO_TOOLTIP
        actionShutDown->setToolTip(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\350\256\276\347\275\256\345\217\202\346\225\260</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShutDown->setText(QString());
        label_ip->setText(QApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200\357\274\232", 0, QApplication::UnicodeUTF8));
        pushButton_enterIP->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245", 0, QApplication::UnicodeUTF8));
        pushButton_cancelIP->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\351\234\200\350\246\201\345\210\240\351\231\244\347\232\204\346\226\207\344\273\266...", 0, QApplication::UnicodeUTF8));
        pushButton_selectFileToDelete->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_cancelDelete->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\345\215\260\345\210\267\346\234\272\346\234\272\345\236\213:", 0, QApplication::UnicodeUTF8));
        pushButton_selectMachineModel->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_cancelMachineSelection->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\346\226\207\344\273\266...", 0, QApplication::UnicodeUTF8));
        pushButton_selectFile->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_cancelSelect->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton_showTabWidget->setText(QApplication::translate("MainWindow", "<", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
