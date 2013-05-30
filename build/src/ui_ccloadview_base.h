#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'ccloadview_base.ui'
**
** Created: Tue Mar 5 16:17:19 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCLOADVIEW_BASE_H
#define UI_CCLOADVIEW_BASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kled.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_8;
    QPushButton *flashCC;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_3;
    QLineEdit *pxSelBits;
    QLabel *pxSellabel;
    QLabel *fileName_8;
    QLineEdit *pxSel;
    QLabel *xxx;
    QLineEdit *pxDir;
    QLineEdit *pxBits;
    QLineEdit *px;
    QLabel *fileName_7;
    QLabel *fileName_4;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_13;
    QPushButton *DD;
    QPushButton *DC;
    QPushButton *RST;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QTextBrowser *console;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_12;
    QPushButton *Connect;
    QLineEdit *port;
    QCheckBox *autoConnect;
    QGroupBox *Interface;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *Production;
    QRadioButton *Debug;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_3;
    QPushButton *step;
    QPushButton *run;
    QPushButton *halt;
    QLabel *label_18;
    QLineEdit *setPC;
    QLabel *label_19;
    QLineEdit *readLocation;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_10;
    QPushButton *selectFile;
    QLabel *fileName;
    QPushButton *readFile;
    QCheckBox *verifyAfterWrite;
    QCheckBox *erasePage;
    QPushButton *writeFile;
    QGridLayout *gridLayout_9;
    QLabel *fileName_2;
    QLineEdit *startAddress;
    QLabel *fileName_3;
    QLineEdit *endAddress;
    QPushButton *verifyFile;
    QProgressBar *progress;
    QPushButton *loadFile;
    QPushButton *eraseChip;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QLabel *Message_4;
    QComboBox *chipModel;
    QLabel *Message_5;
    QLabel *chipSeries;
    QLabel *Message_8;
    QLabel *chipID;
    QLabel *Message_6;
    QLabel *revision;
    QLabel *Message_7;
    QLabel *chipSize;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_4;
    KLed *chipEraseDone;
    QLabel *fileName_5;
    KLed *pconIdle;
    QLabel *fileName_6;
    KLed *cpuHalted;
    QLabel *fileName_9;
    KLed *powerMode0;
    QLabel *fileName_10;
    KLed *haltStatus;
    QLabel *fileName_11;
    KLed *debugLocked;
    QLabel *fileName_12;
    KLed *oscillatorStable;
    QLabel *fileName_13;
    KLed *stackOverflow;
    QLabel *fileName_14;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_5;
    QLabel *fileName_17;
    QLabel *fileName_15;
    KLed *dmaPause;
    QLabel *fileName_18;
    KLed *timersOff;
    KLed *timerSuspend;
    KLed *selFlashInfo;
    QLabel *fileName_16;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_2;
    QLabel *REG_A;
    QLabel *label_15;
    QLabel *REG_DPL0;
    QLabel *label_7;
    QLabel *label_16;
    QLabel *REG_DPL1;
    QLabel *label_2;
    QLabel *label;
    QLabel *REG_B;
    QLabel *label_13;
    QLabel *REG_SP;
    QLabel *label_4;
    QLabel *REG_R0;
    QLabel *label_8;
    QLabel *REG_R4;
    QLabel *label_5;
    QLabel *REG_R1;
    QLabel *label_9;
    QLabel *REG_R5;
    QLabel *label_6;
    QLabel *REG_R2;
    QLabel *REG_R6;
    QLabel *REG_R3;
    QLabel *label_11;
    QLabel *REG_R7;
    QLabel *REG_DPH1;
    QLabel *label_10;
    QLabel *label_3;
    QLabel *label_12;
    QLabel *label_14;
    QLabel *label_17;
    QLabel *REG_PSW;
    QLabel *REG_PC;
    QLabel *REG_DPH0;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *getStatus;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QLabel *Message_2;
    QLabel *statusLine;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(877, 917);
        verticalLayout_5 = new QVBoxLayout(Form);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_3 = new QGroupBox(Form);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_8 = new QGridLayout(groupBox_3);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        flashCC = new QPushButton(groupBox_3);
        flashCC->setObjectName(QString::fromUtf8("flashCC"));

        gridLayout_8->addWidget(flashCC, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer, 0, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pxSelBits = new QLineEdit(groupBox_3);
        pxSelBits->setObjectName(QString::fromUtf8("pxSelBits"));

        gridLayout_3->addWidget(pxSelBits, 0, 1, 1, 1);

        pxSellabel = new QLabel(groupBox_3);
        pxSellabel->setObjectName(QString::fromUtf8("pxSellabel"));

        gridLayout_3->addWidget(pxSellabel, 1, 0, 1, 1);

        fileName_8 = new QLabel(groupBox_3);
        fileName_8->setObjectName(QString::fromUtf8("fileName_8"));

        gridLayout_3->addWidget(fileName_8, 3, 0, 1, 1);

        pxSel = new QLineEdit(groupBox_3);
        pxSel->setObjectName(QString::fromUtf8("pxSel"));

        gridLayout_3->addWidget(pxSel, 1, 1, 1, 1);

        xxx = new QLabel(groupBox_3);
        xxx->setObjectName(QString::fromUtf8("xxx"));

        gridLayout_3->addWidget(xxx, 2, 0, 1, 1);

        pxDir = new QLineEdit(groupBox_3);
        pxDir->setObjectName(QString::fromUtf8("pxDir"));

        gridLayout_3->addWidget(pxDir, 4, 1, 1, 1);

        pxBits = new QLineEdit(groupBox_3);
        pxBits->setObjectName(QString::fromUtf8("pxBits"));

        gridLayout_3->addWidget(pxBits, 2, 1, 1, 1);

        px = new QLineEdit(groupBox_3);
        px->setObjectName(QString::fromUtf8("px"));

        gridLayout_3->addWidget(px, 3, 1, 1, 1);

        fileName_7 = new QLabel(groupBox_3);
        fileName_7->setObjectName(QString::fromUtf8("fileName_7"));

        gridLayout_3->addWidget(fileName_7, 4, 0, 1, 1);

        fileName_4 = new QLabel(groupBox_3);
        fileName_4->setObjectName(QString::fromUtf8("fileName_4"));

        gridLayout_3->addWidget(fileName_4, 0, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_3, 1, 0, 1, 2);


        horizontalLayout->addWidget(groupBox_3);

        groupBox_7 = new QGroupBox(Form);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_13 = new QGridLayout(groupBox_7);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        DD = new QPushButton(groupBox_7);
        DD->setObjectName(QString::fromUtf8("DD"));

        gridLayout_13->addWidget(DD, 0, 0, 1, 1);

        DC = new QPushButton(groupBox_7);
        DC->setObjectName(QString::fromUtf8("DC"));

        gridLayout_13->addWidget(DC, 1, 0, 1, 1);

        RST = new QPushButton(groupBox_7);
        RST->setObjectName(QString::fromUtf8("RST"));

        gridLayout_13->addWidget(RST, 2, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        console = new QTextBrowser(Form);
        console->setObjectName(QString::fromUtf8("console"));

        verticalLayout_4->addWidget(console);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_6 = new QGroupBox(Form);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout_12 = new QGridLayout(groupBox_6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        Connect = new QPushButton(groupBox_6);
        Connect->setObjectName(QString::fromUtf8("Connect"));

        gridLayout_12->addWidget(Connect, 0, 0, 1, 1);

        port = new QLineEdit(groupBox_6);
        port->setObjectName(QString::fromUtf8("port"));

        gridLayout_12->addWidget(port, 0, 1, 1, 1);

        autoConnect = new QCheckBox(groupBox_6);
        autoConnect->setObjectName(QString::fromUtf8("autoConnect"));
        autoConnect->setChecked(true);

        gridLayout_12->addWidget(autoConnect, 1, 0, 1, 2);


        horizontalLayout_2->addWidget(groupBox_6);

        Interface = new QGroupBox(Form);
        Interface->setObjectName(QString::fromUtf8("Interface"));
        verticalLayout_2 = new QVBoxLayout(Interface);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        Production = new QRadioButton(Interface);
        Production->setObjectName(QString::fromUtf8("Production"));
        Production->setChecked(true);

        verticalLayout_2->addWidget(Production);

        Debug = new QRadioButton(Interface);
        Debug->setObjectName(QString::fromUtf8("Debug"));

        verticalLayout_2->addWidget(Debug);


        horizontalLayout_2->addWidget(Interface);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_9 = new QGroupBox(Form);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        verticalLayout_3 = new QVBoxLayout(groupBox_9);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        step = new QPushButton(groupBox_9);
        step->setObjectName(QString::fromUtf8("step"));
        step->setEnabled(false);

        verticalLayout_3->addWidget(step);

        run = new QPushButton(groupBox_9);
        run->setObjectName(QString::fromUtf8("run"));
        run->setEnabled(false);

        verticalLayout_3->addWidget(run);

        halt = new QPushButton(groupBox_9);
        halt->setObjectName(QString::fromUtf8("halt"));
        halt->setEnabled(false);

        verticalLayout_3->addWidget(halt);

        label_18 = new QLabel(groupBox_9);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        verticalLayout_3->addWidget(label_18);

        setPC = new QLineEdit(groupBox_9);
        setPC->setObjectName(QString::fromUtf8("setPC"));
        setPC->setEnabled(false);

        verticalLayout_3->addWidget(setPC);

        label_19 = new QLabel(groupBox_9);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        verticalLayout_3->addWidget(label_19);

        readLocation = new QLineEdit(groupBox_9);
        readLocation->setObjectName(QString::fromUtf8("readLocation"));
        readLocation->setEnabled(false);

        verticalLayout_3->addWidget(readLocation);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));

        verticalLayout_3->addLayout(verticalLayout_6);


        horizontalLayout_3->addWidget(groupBox_9);

        groupBox_4 = new QGroupBox(Form);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_10 = new QGridLayout(groupBox_4);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        selectFile = new QPushButton(groupBox_4);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));
        selectFile->setEnabled(false);

        gridLayout_10->addWidget(selectFile, 0, 0, 1, 2);

        fileName = new QLabel(groupBox_4);
        fileName->setObjectName(QString::fromUtf8("fileName"));

        gridLayout_10->addWidget(fileName, 0, 2, 1, 1);

        readFile = new QPushButton(groupBox_4);
        readFile->setObjectName(QString::fromUtf8("readFile"));
        readFile->setEnabled(false);

        gridLayout_10->addWidget(readFile, 2, 0, 1, 1);

        verifyAfterWrite = new QCheckBox(groupBox_4);
        verifyAfterWrite->setObjectName(QString::fromUtf8("verifyAfterWrite"));
        verifyAfterWrite->setChecked(true);

        gridLayout_10->addWidget(verifyAfterWrite, 2, 1, 1, 2);

        erasePage = new QCheckBox(groupBox_4);
        erasePage->setObjectName(QString::fromUtf8("erasePage"));
        erasePage->setChecked(false);

        gridLayout_10->addWidget(erasePage, 2, 3, 1, 1);

        writeFile = new QPushButton(groupBox_4);
        writeFile->setObjectName(QString::fromUtf8("writeFile"));
        writeFile->setEnabled(false);

        gridLayout_10->addWidget(writeFile, 3, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        fileName_2 = new QLabel(groupBox_4);
        fileName_2->setObjectName(QString::fromUtf8("fileName_2"));

        gridLayout_9->addWidget(fileName_2, 0, 0, 1, 1);

        startAddress = new QLineEdit(groupBox_4);
        startAddress->setObjectName(QString::fromUtf8("startAddress"));

        gridLayout_9->addWidget(startAddress, 0, 1, 1, 1);

        fileName_3 = new QLabel(groupBox_4);
        fileName_3->setObjectName(QString::fromUtf8("fileName_3"));

        gridLayout_9->addWidget(fileName_3, 1, 0, 1, 1);

        endAddress = new QLineEdit(groupBox_4);
        endAddress->setObjectName(QString::fromUtf8("endAddress"));

        gridLayout_9->addWidget(endAddress, 1, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 3, 2, 2, 2);

        verifyFile = new QPushButton(groupBox_4);
        verifyFile->setObjectName(QString::fromUtf8("verifyFile"));
        verifyFile->setEnabled(false);

        gridLayout_10->addWidget(verifyFile, 4, 0, 1, 1);

        progress = new QProgressBar(groupBox_4);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setValue(0);

        gridLayout_10->addWidget(progress, 5, 2, 1, 2);

        loadFile = new QPushButton(groupBox_4);
        loadFile->setObjectName(QString::fromUtf8("loadFile"));
        loadFile->setEnabled(false);

        gridLayout_10->addWidget(loadFile, 1, 0, 1, 2);

        eraseChip = new QPushButton(groupBox_4);
        eraseChip->setObjectName(QString::fromUtf8("eraseChip"));
        eraseChip->setEnabled(false);

        gridLayout_10->addWidget(eraseChip, 5, 0, 1, 1);


        horizontalLayout_3->addWidget(groupBox_4);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_10->addLayout(verticalLayout_4);

        horizontalSpacer_5 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox_5 = new QGroupBox(Form);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Message_4 = new QLabel(groupBox_5);
        Message_4->setObjectName(QString::fromUtf8("Message_4"));

        gridLayout->addWidget(Message_4, 0, 0, 1, 1);

        chipModel = new QComboBox(groupBox_5);
        chipModel->setObjectName(QString::fromUtf8("chipModel"));

        gridLayout->addWidget(chipModel, 0, 1, 1, 1);

        Message_5 = new QLabel(groupBox_5);
        Message_5->setObjectName(QString::fromUtf8("Message_5"));

        gridLayout->addWidget(Message_5, 1, 0, 1, 1);

        chipSeries = new QLabel(groupBox_5);
        chipSeries->setObjectName(QString::fromUtf8("chipSeries"));

        gridLayout->addWidget(chipSeries, 1, 1, 1, 1);

        Message_8 = new QLabel(groupBox_5);
        Message_8->setObjectName(QString::fromUtf8("Message_8"));

        gridLayout->addWidget(Message_8, 2, 0, 1, 1);

        chipID = new QLabel(groupBox_5);
        chipID->setObjectName(QString::fromUtf8("chipID"));

        gridLayout->addWidget(chipID, 2, 1, 1, 1);

        Message_6 = new QLabel(groupBox_5);
        Message_6->setObjectName(QString::fromUtf8("Message_6"));

        gridLayout->addWidget(Message_6, 3, 0, 1, 1);

        revision = new QLabel(groupBox_5);
        revision->setObjectName(QString::fromUtf8("revision"));

        gridLayout->addWidget(revision, 3, 1, 1, 1);

        Message_7 = new QLabel(groupBox_5);
        Message_7->setObjectName(QString::fromUtf8("Message_7"));

        gridLayout->addWidget(Message_7, 4, 0, 1, 1);

        chipSize = new QLabel(groupBox_5);
        chipSize->setObjectName(QString::fromUtf8("chipSize"));

        gridLayout->addWidget(chipSize, 4, 1, 1, 1);


        horizontalLayout_5->addWidget(groupBox_5);

        horizontalSpacer_7 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        chipEraseDone = new KLed(groupBox);
        chipEraseDone->setObjectName(QString::fromUtf8("chipEraseDone"));

        gridLayout_4->addWidget(chipEraseDone, 0, 0, 1, 1);

        fileName_5 = new QLabel(groupBox);
        fileName_5->setObjectName(QString::fromUtf8("fileName_5"));

        gridLayout_4->addWidget(fileName_5, 0, 1, 1, 1);

        pconIdle = new KLed(groupBox);
        pconIdle->setObjectName(QString::fromUtf8("pconIdle"));

        gridLayout_4->addWidget(pconIdle, 1, 0, 1, 1);

        fileName_6 = new QLabel(groupBox);
        fileName_6->setObjectName(QString::fromUtf8("fileName_6"));

        gridLayout_4->addWidget(fileName_6, 1, 1, 1, 1);

        cpuHalted = new KLed(groupBox);
        cpuHalted->setObjectName(QString::fromUtf8("cpuHalted"));

        gridLayout_4->addWidget(cpuHalted, 2, 0, 1, 1);

        fileName_9 = new QLabel(groupBox);
        fileName_9->setObjectName(QString::fromUtf8("fileName_9"));

        gridLayout_4->addWidget(fileName_9, 2, 1, 1, 1);

        powerMode0 = new KLed(groupBox);
        powerMode0->setObjectName(QString::fromUtf8("powerMode0"));

        gridLayout_4->addWidget(powerMode0, 3, 0, 1, 1);

        fileName_10 = new QLabel(groupBox);
        fileName_10->setObjectName(QString::fromUtf8("fileName_10"));

        gridLayout_4->addWidget(fileName_10, 3, 1, 1, 1);

        haltStatus = new KLed(groupBox);
        haltStatus->setObjectName(QString::fromUtf8("haltStatus"));

        gridLayout_4->addWidget(haltStatus, 4, 0, 1, 1);

        fileName_11 = new QLabel(groupBox);
        fileName_11->setObjectName(QString::fromUtf8("fileName_11"));

        gridLayout_4->addWidget(fileName_11, 4, 1, 1, 1);

        debugLocked = new KLed(groupBox);
        debugLocked->setObjectName(QString::fromUtf8("debugLocked"));

        gridLayout_4->addWidget(debugLocked, 5, 0, 1, 1);

        fileName_12 = new QLabel(groupBox);
        fileName_12->setObjectName(QString::fromUtf8("fileName_12"));

        gridLayout_4->addWidget(fileName_12, 5, 1, 1, 1);

        oscillatorStable = new KLed(groupBox);
        oscillatorStable->setObjectName(QString::fromUtf8("oscillatorStable"));

        gridLayout_4->addWidget(oscillatorStable, 6, 0, 1, 1);

        fileName_13 = new QLabel(groupBox);
        fileName_13->setObjectName(QString::fromUtf8("fileName_13"));

        gridLayout_4->addWidget(fileName_13, 6, 1, 1, 1);

        stackOverflow = new KLed(groupBox);
        stackOverflow->setObjectName(QString::fromUtf8("stackOverflow"));

        gridLayout_4->addWidget(stackOverflow, 7, 0, 1, 1);

        fileName_14 = new QLabel(groupBox);
        fileName_14->setObjectName(QString::fromUtf8("fileName_14"));

        gridLayout_4->addWidget(fileName_14, 7, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(groupBox);

        horizontalSpacer_8 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        groupBox_2 = new QGroupBox(Form);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_7 = new QGridLayout(groupBox_2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        fileName_17 = new QLabel(groupBox_2);
        fileName_17->setObjectName(QString::fromUtf8("fileName_17"));

        gridLayout_5->addWidget(fileName_17, 2, 1, 1, 1);

        fileName_15 = new QLabel(groupBox_2);
        fileName_15->setObjectName(QString::fromUtf8("fileName_15"));

        gridLayout_5->addWidget(fileName_15, 0, 1, 1, 1);

        dmaPause = new KLed(groupBox_2);
        dmaPause->setObjectName(QString::fromUtf8("dmaPause"));

        gridLayout_5->addWidget(dmaPause, 1, 0, 1, 1);

        fileName_18 = new QLabel(groupBox_2);
        fileName_18->setObjectName(QString::fromUtf8("fileName_18"));

        gridLayout_5->addWidget(fileName_18, 3, 1, 1, 1);

        timersOff = new KLed(groupBox_2);
        timersOff->setObjectName(QString::fromUtf8("timersOff"));

        gridLayout_5->addWidget(timersOff, 0, 0, 1, 1);

        timerSuspend = new KLed(groupBox_2);
        timerSuspend->setObjectName(QString::fromUtf8("timerSuspend"));

        gridLayout_5->addWidget(timerSuspend, 2, 0, 1, 1);

        selFlashInfo = new KLed(groupBox_2);
        selFlashInfo->setObjectName(QString::fromUtf8("selFlashInfo"));

        gridLayout_5->addWidget(selFlashInfo, 3, 0, 1, 1);

        fileName_16 = new QLabel(groupBox_2);
        fileName_16->setObjectName(QString::fromUtf8("fileName_16"));

        gridLayout_5->addWidget(fileName_16, 1, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_5, 0, 0, 1, 1);


        horizontalLayout_7->addWidget(groupBox_2);

        horizontalSpacer_9 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox_8 = new QGroupBox(Form);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setMinimumSize(QSize(131, 0));
        gridLayout_2 = new QGridLayout(groupBox_8);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        REG_A = new QLabel(groupBox_8);
        REG_A->setObjectName(QString::fromUtf8("REG_A"));
        REG_A->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_A, 1, 2, 1, 3);

        label_15 = new QLabel(groupBox_8);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 3, 5, 1, 1);

        REG_DPL0 = new QLabel(groupBox_8);
        REG_DPL0->setObjectName(QString::fromUtf8("REG_DPL0"));
        REG_DPL0->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_DPL0, 3, 6, 1, 1);

        label_7 = new QLabel(groupBox_8);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 8, 0, 1, 1);

        label_16 = new QLabel(groupBox_8);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 4, 5, 1, 1);

        REG_DPL1 = new QLabel(groupBox_8);
        REG_DPL1->setObjectName(QString::fromUtf8("REG_DPL1"));
        REG_DPL1->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_DPL1, 4, 6, 1, 1);

        label_2 = new QLabel(groupBox_8);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(groupBox_8);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        REG_B = new QLabel(groupBox_8);
        REG_B->setObjectName(QString::fromUtf8("REG_B"));

        gridLayout_2->addWidget(REG_B, 1, 6, 1, 1);

        label_13 = new QLabel(groupBox_8);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 2, 5, 1, 1);

        REG_SP = new QLabel(groupBox_8);
        REG_SP->setObjectName(QString::fromUtf8("REG_SP"));
        REG_SP->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_SP, 2, 6, 1, 1);

        label_4 = new QLabel(groupBox_8);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        REG_R0 = new QLabel(groupBox_8);
        REG_R0->setObjectName(QString::fromUtf8("REG_R0"));
        REG_R0->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R0, 5, 2, 1, 2);

        label_8 = new QLabel(groupBox_8);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 5, 5, 1, 1);

        REG_R4 = new QLabel(groupBox_8);
        REG_R4->setObjectName(QString::fromUtf8("REG_R4"));
        REG_R4->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R4, 5, 6, 1, 1);

        label_5 = new QLabel(groupBox_8);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 6, 0, 1, 1);

        REG_R1 = new QLabel(groupBox_8);
        REG_R1->setObjectName(QString::fromUtf8("REG_R1"));
        REG_R1->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R1, 6, 1, 1, 2);

        label_9 = new QLabel(groupBox_8);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 6, 5, 1, 1);

        REG_R5 = new QLabel(groupBox_8);
        REG_R5->setObjectName(QString::fromUtf8("REG_R5"));
        REG_R5->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R5, 6, 6, 1, 1);

        label_6 = new QLabel(groupBox_8);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 7, 0, 1, 1);

        REG_R2 = new QLabel(groupBox_8);
        REG_R2->setObjectName(QString::fromUtf8("REG_R2"));
        REG_R2->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R2, 7, 1, 1, 2);

        REG_R6 = new QLabel(groupBox_8);
        REG_R6->setObjectName(QString::fromUtf8("REG_R6"));
        REG_R6->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R6, 7, 6, 1, 1);

        REG_R3 = new QLabel(groupBox_8);
        REG_R3->setObjectName(QString::fromUtf8("REG_R3"));
        REG_R3->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R3, 8, 1, 1, 2);

        label_11 = new QLabel(groupBox_8);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 8, 5, 1, 1);

        REG_R7 = new QLabel(groupBox_8);
        REG_R7->setObjectName(QString::fromUtf8("REG_R7"));
        REG_R7->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_R7, 8, 6, 1, 1);

        REG_DPH1 = new QLabel(groupBox_8);
        REG_DPH1->setObjectName(QString::fromUtf8("REG_DPH1"));
        REG_DPH1->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_DPH1, 4, 2, 1, 2);

        label_10 = new QLabel(groupBox_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 7, 5, 1, 1);

        label_3 = new QLabel(groupBox_8);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 5, 1, 1);

        label_12 = new QLabel(groupBox_8);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 1);

        label_14 = new QLabel(groupBox_8);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 3, 0, 1, 1);

        label_17 = new QLabel(groupBox_8);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 4, 0, 1, 1);

        REG_PSW = new QLabel(groupBox_8);
        REG_PSW->setObjectName(QString::fromUtf8("REG_PSW"));
        REG_PSW->setMinimumSize(QSize(50, 0));

        gridLayout_2->addWidget(REG_PSW, 2, 2, 1, 3);

        REG_PC = new QLabel(groupBox_8);
        REG_PC->setObjectName(QString::fromUtf8("REG_PC"));

        gridLayout_2->addWidget(REG_PC, 0, 1, 1, 6);

        REG_DPH0 = new QLabel(groupBox_8);
        REG_DPH0->setObjectName(QString::fromUtf8("REG_DPH0"));
        REG_DPH0->setMinimumSize(QSize(50, 0));
        REG_DPH0->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(REG_DPH0, 3, 2, 1, 3);


        horizontalLayout_8->addWidget(groupBox_8);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        getStatus = new QPushButton(Form);
        getStatus->setObjectName(QString::fromUtf8("getStatus"));

        horizontalLayout_4->addWidget(getStatus);

        horizontalSpacer_6 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_10->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        Message_2 = new QLabel(Form);
        Message_2->setObjectName(QString::fromUtf8("Message_2"));

        horizontalLayout_9->addWidget(Message_2);

        statusLine = new QLabel(Form);
        statusLine->setObjectName(QString::fromUtf8("statusLine"));
        statusLine->setMinimumSize(QSize(100, 0));

        horizontalLayout_9->addWidget(statusLine);


        verticalLayout_5->addLayout(horizontalLayout_9);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(tr2i18n("Form", 0));
        groupBox_3->setTitle(tr2i18n("Check CC Led", 0));
        flashCC->setText(tr2i18n("Flash CC", 0));
        pxSelBits->setText(tr2i18n("0x06", 0));
        pxSellabel->setText(tr2i18n("PxSEL", 0));
        fileName_8->setText(tr2i18n("Px", 0));
        pxSel->setText(tr2i18n("0xf5", 0));
        xxx->setText(tr2i18n("PxBits", 0));
        pxDir->setText(tr2i18n("0xff", 0));
        pxBits->setText(tr2i18n("0x18", 0));
        px->setText(tr2i18n("0xa0", 0));
        fileName_7->setText(tr2i18n("PxDir", 0));
        fileName_4->setText(tr2i18n("PxSELBits", 0));
        groupBox_7->setTitle(tr2i18n("Raw Pins", 0));
        DD->setText(tr2i18n("DD", 0));
        DC->setText(tr2i18n("DC", 0));
        RST->setText(tr2i18n("RST", 0));
        groupBox_6->setTitle(tr2i18n("Serial", 0));
        Connect->setText(tr2i18n("Connect", 0));
        port->setText(tr2i18n("/dev/ttyACM0", 0));
        autoConnect->setText(tr2i18n("Auto Connect", 0));
        Interface->setTitle(tr2i18n("Interface", 0));
        Production->setText(tr2i18n("Production", 0));
        Debug->setText(tr2i18n("Debug", 0));
        groupBox_9->setTitle(tr2i18n("Debug", 0));
        step->setText(tr2i18n("Step", 0));
        run->setText(tr2i18n("Run", 0));
        halt->setText(tr2i18n("Halt", 0));
        label_18->setText(tr2i18n("PC:", 0));
        setPC->setText(tr2i18n("0x0000", 0));
        label_19->setText(tr2i18n("Read Mem:", 0));
        readLocation->setText(tr2i18n("0x0000", 0));
        groupBox_4->setTitle(tr2i18n("Read/Write", 0));
        selectFile->setText(tr2i18n("Select File", 0));
        fileName->setText(tr2i18n("unknown", 0));
        readFile->setText(tr2i18n("Read", 0));
        verifyAfterWrite->setText(tr2i18n("Verify After Write", 0));
        erasePage->setText(tr2i18n("Erase Page", 0));
        writeFile->setText(tr2i18n("Write", 0));
        fileName_2->setText(tr2i18n("Start:", 0));
        fileName_3->setText(tr2i18n("End:", 0));
        verifyFile->setText(tr2i18n("Verify", 0));
        loadFile->setText(tr2i18n("Load File", 0));
        eraseChip->setText(tr2i18n("Erase Chip", 0));
        groupBox_5->setTitle(tr2i18n("Chip", 0));
        Message_4->setText(tr2i18n("Model", 0));
        Message_5->setText(tr2i18n("Chip:", 0));
        chipSeries->setText(tr2i18n("unknown", 0));
        Message_8->setText(tr2i18n("ID:", 0));
        chipID->setText(tr2i18n("unknown", 0));
        Message_6->setText(tr2i18n("Revision:", 0));
        revision->setText(tr2i18n("unknown", 0));
        Message_7->setText(tr2i18n("Size:", 0));
        chipSize->setText(tr2i18n("unknown", 0));
        groupBox->setTitle(tr2i18n("CC Status Byte", 0));
        fileName_5->setText(tr2i18n("Chip Erase Done (0x80)", 0));
        fileName_6->setText(tr2i18n("PCON Idle (0x40)", 0));
        fileName_9->setText(tr2i18n("CPU Halted  (0x20)", 0));
        fileName_10->setText(tr2i18n("Power Mode 0 (0x10)", 0));
        fileName_11->setText(tr2i18n("Halt Status  (0x08)", 0));
        fileName_12->setText(tr2i18n("Debug Locked  (0x04)", 0));
        fileName_13->setText(tr2i18n("Oscillator Stable (0x02)", 0));
        fileName_14->setText(tr2i18n("Stack Overflow  (0x01)", 0));
        groupBox_2->setTitle(tr2i18n("CC Config Byte", 0));
        fileName_17->setText(tr2i18n("Timer Suspend", 0));
        fileName_15->setText(tr2i18n("Timers Off", 0));
        fileName_18->setText(tr2i18n("Sel Flash Info", 0));
        fileName_16->setText(tr2i18n("DMA Pause", 0));
        groupBox_8->setTitle(tr2i18n("Registers", 0));
        REG_A->setText(QString());
        label_15->setText(tr2i18n("DPL0:", 0));
        REG_DPL0->setText(QString());
        label_7->setText(tr2i18n("R3:", 0));
        label_16->setText(tr2i18n("DPL1:", 0));
        REG_DPL1->setText(QString());
        label_2->setText(tr2i18n("A:", 0));
        label->setText(tr2i18n("PC:", 0));
        REG_B->setText(QString());
        label_13->setText(tr2i18n("SP:", 0));
        REG_SP->setText(QString());
        label_4->setText(tr2i18n("R0:", 0));
        REG_R0->setText(QString());
        label_8->setText(tr2i18n("R4:", 0));
        REG_R4->setText(QString());
        label_5->setText(tr2i18n("R1:", 0));
        REG_R1->setText(QString());
        label_9->setText(tr2i18n("R5:", 0));
        REG_R5->setText(QString());
        label_6->setText(tr2i18n("R2:", 0));
        REG_R2->setText(QString());
        REG_R6->setText(QString());
        REG_R3->setText(QString());
        label_11->setText(tr2i18n("R7:", 0));
        REG_R7->setText(QString());
        REG_DPH1->setText(QString());
        label_10->setText(tr2i18n("R6:", 0));
        label_3->setText(tr2i18n("B:", 0));
        label_12->setText(tr2i18n("PSW:", 0));
        label_14->setText(tr2i18n("DHP0:", 0));
        label_17->setText(tr2i18n("DPH1:", 0));
        REG_PSW->setText(QString());
        REG_PC->setText(QString());
        REG_DPH0->setText(QString());
        getStatus->setText(tr2i18n("Get Status", 0));
        Message_2->setText(tr2i18n("Status:", 0));
        statusLine->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CCLOADVIEW_BASE_H

