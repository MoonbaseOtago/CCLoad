#include <kdialog.h>
#include <klocale.h>

/********************************************************************************
** Form generated from reading UI file 'prefs_base.ui'
**
** Created: Sun Nov 25 16:49:52 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFS_BASE_H
#define UI_PREFS_BASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include "kcolorbutton.h"

QT_BEGIN_NAMESPACE

class Ui_prefs_base
{
public:
    QGridLayout *gridLayout;
    QLabel *textLabel2_2;
    KColorButton *kcfg_col_background;
    QLabel *textLabel1;
    QLabel *textLabel2;
    KColorButton *kcfg_col_foreground;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QSpinBox *kcfg_val_time;
    QSpacerItem *spacerItem2;

    void setupUi(QWidget *prefs_base)
    {
        if (prefs_base->objectName().isEmpty())
            prefs_base->setObjectName(QString::fromUtf8("prefs_base"));
        prefs_base->resize(282, 156);
        gridLayout = new QGridLayout(prefs_base);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textLabel2_2 = new QLabel(prefs_base);
        textLabel2_2->setObjectName(QString::fromUtf8("textLabel2_2"));
        textLabel2_2->setWordWrap(false);

        gridLayout->addWidget(textLabel2_2, 0, 0, 1, 1);

        kcfg_col_background = new KColorButton(prefs_base);
        kcfg_col_background->setObjectName(QString::fromUtf8("kcfg_col_background"));

        gridLayout->addWidget(kcfg_col_background, 0, 1, 1, 1);

        textLabel1 = new QLabel(prefs_base);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setWordWrap(false);

        gridLayout->addWidget(textLabel1, 2, 0, 1, 1);

        textLabel2 = new QLabel(prefs_base);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout->addWidget(textLabel2, 1, 0, 1, 1);

        kcfg_col_foreground = new KColorButton(prefs_base);
        kcfg_col_foreground->setObjectName(QString::fromUtf8("kcfg_col_foreground"));

        gridLayout->addWidget(kcfg_col_foreground, 1, 1, 1, 1);

        spacerItem = new QSpacerItem(41, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem, 0, 2, 1, 1);

        spacerItem1 = new QSpacerItem(41, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem1, 1, 2, 1, 1);

        kcfg_val_time = new QSpinBox(prefs_base);
        kcfg_val_time->setObjectName(QString::fromUtf8("kcfg_val_time"));
        kcfg_val_time->setMinimum(1);
        kcfg_val_time->setValue(2);

        gridLayout->addWidget(kcfg_val_time, 2, 1, 1, 1);

        spacerItem2 = new QSpacerItem(41, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem2, 2, 2, 1, 1);


        retranslateUi(prefs_base);

        QMetaObject::connectSlotsByName(prefs_base);
    } // setupUi

    void retranslateUi(QWidget *prefs_base)
    {
        textLabel2_2->setText(tr2i18n("Background color:", 0));
#ifndef UI_QT_NO_TOOLTIP
        kcfg_col_background->setToolTip(tr2i18n("Choose a new background color", 0));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        kcfg_col_background->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Change the <span style=\" font-weight:600;\">background</span> color by clicking here and choose the new <span style=\" color:#ff0000;\">color</span> in the <span style=\" font-style:italic;\">color dialog</span>.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        kcfg_col_background->setText(QString());
        textLabel1->setText(tr2i18n("Project age:", 0));
        textLabel2->setText(tr2i18n("Foreground color:", 0));
#ifndef UI_QT_NO_TOOLTIP
        kcfg_col_foreground->setToolTip(tr2i18n("Choose a new foreground color", 0));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        kcfg_col_foreground->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Change the <span style=\" font-weight:600;\">foreground</span> color by clicking here and choose the new <span style=\" color:#ff0000;\">color</span> in the <span style=\" font-style:italic;\">color dialog</span>.</p></body></html>", 0));
#endif // QT_NO_WHATSTHIS
        kcfg_col_foreground->setText(QString());
#ifndef UI_QT_NO_TOOLTIP
        kcfg_val_time->setToolTip(tr2i18n("Set the project age (in days)", 0));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        kcfg_val_time->setWhatsThis(tr2i18n("Change the project age (in days) by choosing a new number of days.", 0));
#endif // QT_NO_WHATSTHIS
        Q_UNUSED(prefs_base);
    } // retranslateUi

};

namespace Ui {
    class prefs_base: public Ui_prefs_base {};
} // namespace Ui

QT_END_NAMESPACE

#endif // PREFS_BASE_H

