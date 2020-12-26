/********************************************************************************
** Form generated from reading UI file 'rviz_jaka.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RVIZ_JAKA_UI_H
#define RVIZ_JAKA_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qwt_text_label.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *stopBt;
    QPushButton *powerOnBt;
    QPushButton *recoveryBt;
    QPushButton *enableBt;
    QTabWidget *tabWidget;
    QWidget *jointTab;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *label_5;
    QPushButton *j2SubBt;
    QLabel *label_2;
    QwtTextLabel *j4;
    QPushButton *j5AddBt;
    QPushButton *j5SubBt;
    QwtTextLabel *j1;
    QPushButton *j2AddBt;
    QPushButton *j1SubBt;
    QwtTextLabel *j2;
    QPushButton *j1AddBt;
    QPushButton *j4SubBt;
    QLabel *label_7;
    QPushButton *j4AddBt;
    QLabel *label_4;
    QPushButton *j3AddBt;
    QPushButton *j3SubBt;
    QLabel *label_6;
    QwtTextLabel *j5;
    QwtTextLabel *j3;
    QwtTextLabel *j6;
    QLabel *label_3;
    QPushButton *j6SubBt;
    QPushButton *j6AddBt;
    QDoubleSpinBox *moveOnceSp;
    QRadioButton *moveOnceBt;
    QRadioButton *moveContinuouslyBt;
    QSpacerItem *verticalSpacer;
    QWidget *ioTab;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QCheckBox *doBox3;
    QCheckBox *doBox2;
    QCheckBox *doBox1;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *doBox5;
    QCheckBox *doBox6;
    QCheckBox *doBox4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nameLabel;
    QSpacerItem *horizontalSpacer;
    QCheckBox *isRealCk;
    QLineEdit *prefixLineEdit;
    QPushButton *applyBt;
    QHBoxLayout *horizontalLayout;
    QLineEdit *ipLineEdit;
    QPushButton *loginBt;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_8;
    QDoubleSpinBox *maxDegSp;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(379, 608);
        gridLayout_2 = new QGridLayout(Form);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(2, 12, 2, 12);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, -1, -1, -1);
        stopBt = new QPushButton(Form);
        stopBt->setObjectName(QStringLiteral("stopBt"));
        stopBt->setEnabled(true);
        stopBt->setStyleSheet(QStringLiteral("color:white; background-color: red; "));

        gridLayout->addWidget(stopBt, 14, 0, 1, 1);

        powerOnBt = new QPushButton(Form);
        powerOnBt->setObjectName(QStringLiteral("powerOnBt"));
        powerOnBt->setEnabled(false);

        gridLayout->addWidget(powerOnBt, 10, 0, 1, 1, Qt::AlignVCenter);

        recoveryBt = new QPushButton(Form);
        recoveryBt->setObjectName(QStringLiteral("recoveryBt"));
        recoveryBt->setEnabled(true);

        gridLayout->addWidget(recoveryBt, 14, 1, 1, 1);

        enableBt = new QPushButton(Form);
        enableBt->setObjectName(QStringLiteral("enableBt"));
        enableBt->setEnabled(false);

        gridLayout->addWidget(enableBt, 10, 1, 1, 1);

        tabWidget = new QTabWidget(Form);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        jointTab = new QWidget();
        jointTab->setObjectName(QStringLiteral("jointTab"));
        gridLayout_6 = new QGridLayout(jointTab);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(6, 6, 6, 6);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_5 = new QLabel(jointTab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 4, 0, 1, 1);

        j2SubBt = new QPushButton(jointTab);
        j2SubBt->setObjectName(QStringLiteral("j2SubBt"));

        gridLayout_5->addWidget(j2SubBt, 2, 2, 1, 1);

        label_2 = new QLabel(jointTab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        j4 = new QwtTextLabel(jointTab);
        j4->setObjectName(QStringLiteral("j4"));

        gridLayout_5->addWidget(j4, 4, 1, 1, 1);

        j5AddBt = new QPushButton(jointTab);
        j5AddBt->setObjectName(QStringLiteral("j5AddBt"));

        gridLayout_5->addWidget(j5AddBt, 5, 3, 1, 1);

        j5SubBt = new QPushButton(jointTab);
        j5SubBt->setObjectName(QStringLiteral("j5SubBt"));

        gridLayout_5->addWidget(j5SubBt, 5, 2, 1, 1);

        j1 = new QwtTextLabel(jointTab);
        j1->setObjectName(QStringLiteral("j1"));

        gridLayout_5->addWidget(j1, 1, 1, 1, 1);

        j2AddBt = new QPushButton(jointTab);
        j2AddBt->setObjectName(QStringLiteral("j2AddBt"));

        gridLayout_5->addWidget(j2AddBt, 2, 3, 1, 1);

        j1SubBt = new QPushButton(jointTab);
        j1SubBt->setObjectName(QStringLiteral("j1SubBt"));

        gridLayout_5->addWidget(j1SubBt, 1, 2, 1, 1);

        j2 = new QwtTextLabel(jointTab);
        j2->setObjectName(QStringLiteral("j2"));

        gridLayout_5->addWidget(j2, 2, 1, 1, 1);

        j1AddBt = new QPushButton(jointTab);
        j1AddBt->setObjectName(QStringLiteral("j1AddBt"));

        gridLayout_5->addWidget(j1AddBt, 1, 3, 1, 1);

        j4SubBt = new QPushButton(jointTab);
        j4SubBt->setObjectName(QStringLiteral("j4SubBt"));

        gridLayout_5->addWidget(j4SubBt, 4, 2, 1, 1);

        label_7 = new QLabel(jointTab);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 5, 0, 1, 1);

        j4AddBt = new QPushButton(jointTab);
        j4AddBt->setObjectName(QStringLiteral("j4AddBt"));

        gridLayout_5->addWidget(j4AddBt, 4, 3, 1, 1);

        label_4 = new QLabel(jointTab);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 2, 0, 1, 1);

        j3AddBt = new QPushButton(jointTab);
        j3AddBt->setObjectName(QStringLiteral("j3AddBt"));

        gridLayout_5->addWidget(j3AddBt, 3, 3, 1, 1);

        j3SubBt = new QPushButton(jointTab);
        j3SubBt->setObjectName(QStringLiteral("j3SubBt"));

        gridLayout_5->addWidget(j3SubBt, 3, 2, 1, 1);

        label_6 = new QLabel(jointTab);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 3, 0, 1, 1);

        j5 = new QwtTextLabel(jointTab);
        j5->setObjectName(QStringLiteral("j5"));

        gridLayout_5->addWidget(j5, 5, 1, 1, 1);

        j3 = new QwtTextLabel(jointTab);
        j3->setObjectName(QStringLiteral("j3"));

        gridLayout_5->addWidget(j3, 3, 1, 1, 1);

        j6 = new QwtTextLabel(jointTab);
        j6->setObjectName(QStringLiteral("j6"));

        gridLayout_5->addWidget(j6, 6, 1, 1, 1);

        label_3 = new QLabel(jointTab);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_5->addWidget(label_3, 6, 0, 1, 1);

        j6SubBt = new QPushButton(jointTab);
        j6SubBt->setObjectName(QStringLiteral("j6SubBt"));

        gridLayout_5->addWidget(j6SubBt, 6, 2, 1, 1);

        j6AddBt = new QPushButton(jointTab);
        j6AddBt->setObjectName(QStringLiteral("j6AddBt"));

        gridLayout_5->addWidget(j6AddBt, 6, 3, 1, 1);

        moveOnceSp = new QDoubleSpinBox(jointTab);
        moveOnceSp->setObjectName(QStringLiteral("moveOnceSp"));
        moveOnceSp->setDecimals(1);
        moveOnceSp->setMinimum(1);
        moveOnceSp->setMaximum(60);
        moveOnceSp->setSingleStep(3);

        gridLayout_5->addWidget(moveOnceSp, 0, 1, 1, 1);

        moveOnceBt = new QRadioButton(jointTab);
        moveOnceBt->setObjectName(QStringLiteral("moveOnceBt"));
        moveOnceBt->setChecked(true);

        gridLayout_5->addWidget(moveOnceBt, 0, 0, 1, 1);

        moveContinuouslyBt = new QRadioButton(jointTab);
        moveContinuouslyBt->setObjectName(QStringLiteral("moveContinuouslyBt"));
        moveContinuouslyBt->setLayoutDirection(Qt::LeftToRight);

        gridLayout_5->addWidget(moveContinuouslyBt, 0, 2, 1, 2, Qt::AlignHCenter|Qt::AlignVCenter);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget->addTab(jointTab, QString());
        ioTab = new QWidget();
        ioTab->setObjectName(QStringLiteral("ioTab"));
        gridLayout_8 = new QGridLayout(ioTab);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        doBox3 = new QCheckBox(ioTab);
        doBox3->setObjectName(QStringLiteral("doBox3"));

        gridLayout_7->addWidget(doBox3, 0, 2, 1, 1);

        doBox2 = new QCheckBox(ioTab);
        doBox2->setObjectName(QStringLiteral("doBox2"));

        gridLayout_7->addWidget(doBox2, 0, 1, 1, 1);

        doBox1 = new QCheckBox(ioTab);
        doBox1->setObjectName(QStringLiteral("doBox1"));

        gridLayout_7->addWidget(doBox1, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_2, 2, 0, 1, 3);

        doBox5 = new QCheckBox(ioTab);
        doBox5->setObjectName(QStringLiteral("doBox5"));

        gridLayout_7->addWidget(doBox5, 1, 1, 1, 1);

        doBox6 = new QCheckBox(ioTab);
        doBox6->setObjectName(QStringLiteral("doBox6"));

        gridLayout_7->addWidget(doBox6, 1, 2, 1, 1);

        doBox4 = new QCheckBox(ioTab);
        doBox4->setObjectName(QStringLiteral("doBox4"));

        gridLayout_7->addWidget(doBox4, 1, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);

        tabWidget->addTab(ioTab, QString());

        gridLayout->addWidget(tabWidget, 13, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        nameLabel = new QLabel(Form);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setFrameShape(QFrame::StyledPanel);
        nameLabel->setFrameShadow(QFrame::Plain);

        horizontalLayout_2->addWidget(nameLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        isRealCk = new QCheckBox(Form);
        isRealCk->setObjectName(QStringLiteral("isRealCk"));

        horizontalLayout_2->addWidget(isRealCk);

        prefixLineEdit = new QLineEdit(Form);
        prefixLineEdit->setObjectName(QStringLiteral("prefixLineEdit"));
        prefixLineEdit->setMinimumSize(QSize(0, 36));
        prefixLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(prefixLineEdit);

        applyBt = new QPushButton(Form);
        applyBt->setObjectName(QStringLiteral("applyBt"));

        horizontalLayout_2->addWidget(applyBt);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ipLineEdit = new QLineEdit(Form);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        ipLineEdit->setMinimumSize(QSize(0, 36));

        horizontalLayout->addWidget(ipLineEdit);

        loginBt = new QPushButton(Form);
        loginBt->setObjectName(QStringLiteral("loginBt"));

        horizontalLayout->addWidget(loginBt);


        gridLayout->addLayout(horizontalLayout, 8, 0, 1, 2);

        label = new QLabel(Form);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 11, 0, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(Form);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setValue(5);

        gridLayout->addWidget(doubleSpinBox_2, 12, 1, 1, 1);

        label_8 = new QLabel(Form);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 12, 0, 1, 1);

        maxDegSp = new QDoubleSpinBox(Form);
        maxDegSp->setObjectName(QStringLiteral("maxDegSp"));
        maxDegSp->setDecimals(1);
        maxDegSp->setMaximum(180);
        maxDegSp->setValue(5);

        gridLayout->addWidget(maxDegSp, 11, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);


        retranslateUi(Form);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", Q_NULLPTR));
        stopBt->setText(QApplication::translate("Form", "\346\200\245\345\201\234", Q_NULLPTR));
        powerOnBt->setText(QApplication::translate("Form", "\344\270\212\347\224\265", Q_NULLPTR));
        recoveryBt->setText(QApplication::translate("Form", "\347\242\260\346\222\236\344\277\235\346\212\244\345\244\215\344\275\215", Q_NULLPTR));
        enableBt->setText(QApplication::translate("Form", "\344\275\277\350\203\275", Q_NULLPTR));
        label_5->setText(QApplication::translate("Form", "joint_4", Q_NULLPTR));
        j2SubBt->setText(QApplication::translate("Form", "-", Q_NULLPTR));
        label_2->setText(QApplication::translate("Form", "joint_1", Q_NULLPTR));
        j5AddBt->setText(QApplication::translate("Form", "+", Q_NULLPTR));
        j5SubBt->setText(QApplication::translate("Form", "-", Q_NULLPTR));
        j2AddBt->setText(QApplication::translate("Form", "+", Q_NULLPTR));
        j1SubBt->setText(QApplication::translate("Form", "-", Q_NULLPTR));
        j1AddBt->setText(QApplication::translate("Form", "+", Q_NULLPTR));
        j4SubBt->setText(QApplication::translate("Form", "-", Q_NULLPTR));
        label_7->setText(QApplication::translate("Form", "joint_5", Q_NULLPTR));
        j4AddBt->setText(QApplication::translate("Form", "+", Q_NULLPTR));
        label_4->setText(QApplication::translate("Form", "joint_2", Q_NULLPTR));
        j3AddBt->setText(QApplication::translate("Form", "+", Q_NULLPTR));
        j3SubBt->setText(QApplication::translate("Form", "-", Q_NULLPTR));
        label_6->setText(QApplication::translate("Form", "joint_3", Q_NULLPTR));
        label_3->setText(QApplication::translate("Form", "joint_6", Q_NULLPTR));
        j6SubBt->setText(QApplication::translate("Form", "-", Q_NULLPTR));
        j6AddBt->setText(QApplication::translate("Form", "+", Q_NULLPTR));
        moveOnceBt->setText(QApplication::translate("Form", "\347\202\271\345\212\250", Q_NULLPTR));
        moveContinuouslyBt->setText(QApplication::translate("Form", "\350\277\236\347\273\255", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(jointTab), QApplication::translate("Form", "\345\205\263\350\212\202\347\251\272\351\227\264", Q_NULLPTR));
        doBox3->setText(QApplication::translate("Form", "DO3", Q_NULLPTR));
        doBox2->setText(QApplication::translate("Form", "DO2", Q_NULLPTR));
        doBox1->setText(QApplication::translate("Form", "DO1", Q_NULLPTR));
        doBox5->setText(QApplication::translate("Form", "DO5", Q_NULLPTR));
        doBox6->setText(QApplication::translate("Form", "DO6", Q_NULLPTR));
        doBox4->setText(QApplication::translate("Form", "DO4", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(ioTab), QApplication::translate("Form", "IO", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("Form", "JAKA", Q_NULLPTR));
        isRealCk->setText(QApplication::translate("Form", "\347\234\237\346\234\272", Q_NULLPTR));
        prefixLineEdit->setPlaceholderText(QApplication::translate("Form", "prefix, e.g., ns0, ns1.", Q_NULLPTR));
        applyBt->setText(QApplication::translate("Form", "\345\272\224\347\224\250", Q_NULLPTR));
        ipLineEdit->setText(QString());
        ipLineEdit->setPlaceholderText(QApplication::translate("Form", "\350\276\223\345\205\245ip\345\234\260\345\235\200", Q_NULLPTR));
        loginBt->setText(QApplication::translate("Form", "\347\231\273\345\275\225", Q_NULLPTR));
        label->setText(QApplication::translate("Form", "\346\234\200\345\244\247\350\247\222\351\200\237\345\272\246(deg/s)", Q_NULLPTR));
        label_8->setText(QApplication::translate("Form", "\346\234\200\345\244\247\347\272\277\351\200\237\345\272\246(mm/s)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RVIZ_JAKA_UI_H
