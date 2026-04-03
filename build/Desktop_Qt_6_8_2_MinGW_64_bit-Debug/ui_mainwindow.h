/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *importLaylout;
    QPushButton *importBtn;
    QLabel *labelFilePath;
    QHBoxLayout *methodLayout;
    QLabel *labelMethod;
    QComboBox *methodBox;
    QPushButton *clearBtn;
    QHBoxLayout *actionLayout;
    QPushButton *downloadBtn;
    QPushButton *exitBtn;
    QTableWidget *tableWidget;
    QPushButton *sortBtn;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *timeSortView;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *timeSearch;
    QLabel *timeSearchView;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QPushButton *searchBtn;
    QPushButton *huySearchBtn;
    QPushButton *caculateBtn;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lableAverage;
    QLabel *lableAverageView;
    QLabel *soLuongLable;
    QLabel *SoLuongView;
    QWidget *horizontalLayoutWidget_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelSort;
    QComboBox *comboBoxSort;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lableSearch;
    QComboBox *comboBoxSearch;
    QLabel *label;
    QRadioButton *radioButtonTenDaoNguoYes;
    QRadioButton *radioButtonTenDaoNguocNo;
    QLabel *lableStatusView;
    QWidget *horizontalLayoutWidget_10;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *listMinBtn;
    QPushButton *huyMinBtn;
    QWidget *horizontalLayoutWidget_11;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *listMaxBtn;
    QPushButton *huyMaxBtn;
    QWidget *horizontalLayoutWidget_12;
    QHBoxLayout *horizontalLayout_9;
    QLabel *labelSort_2;
    QComboBox *comboBoxStandarSort;
    QComboBox *comboBoxLopTb;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *addBtn;
    QPushButton *saveBtn;
    QLCDNumber *lcdSoLuongSinhVien;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1307, 657);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 10, 751, 501));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(0, 0, 0, 0);
        importLaylout = new QHBoxLayout();
        importLaylout->setObjectName("importLaylout");
        importBtn = new QPushButton(verticalLayoutWidget);
        importBtn->setObjectName("importBtn");

        importLaylout->addWidget(importBtn);

        labelFilePath = new QLabel(verticalLayoutWidget);
        labelFilePath->setObjectName("labelFilePath");

        importLaylout->addWidget(labelFilePath);


        mainLayout->addLayout(importLaylout);

        methodLayout = new QHBoxLayout();
        methodLayout->setObjectName("methodLayout");
        labelMethod = new QLabel(verticalLayoutWidget);
        labelMethod->setObjectName("labelMethod");

        methodLayout->addWidget(labelMethod);

        methodBox = new QComboBox(verticalLayoutWidget);
        methodBox->addItem(QString());
        methodBox->addItem(QString());
        methodBox->addItem(QString());
        methodBox->addItem(QString());
        methodBox->addItem(QString());
        methodBox->setObjectName("methodBox");

        methodLayout->addWidget(methodBox);

        clearBtn = new QPushButton(verticalLayoutWidget);
        clearBtn->setObjectName("clearBtn");
        clearBtn->setEnabled(false);

        methodLayout->addWidget(clearBtn);


        mainLayout->addLayout(methodLayout);

        actionLayout = new QHBoxLayout();
        actionLayout->setObjectName("actionLayout");
        downloadBtn = new QPushButton(verticalLayoutWidget);
        downloadBtn->setObjectName("downloadBtn");

        actionLayout->addWidget(downloadBtn);

        exitBtn = new QPushButton(verticalLayoutWidget);
        exitBtn->setObjectName("exitBtn");

        actionLayout->addWidget(exitBtn);


        mainLayout->addLayout(actionLayout);

        tableWidget = new QTableWidget(verticalLayoutWidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setMinimumSize(QSize(749, 0));

        mainLayout->addWidget(tableWidget);

        sortBtn = new QPushButton(centralwidget);
        sortBtn->setObjectName("sortBtn");
        sortBtn->setGeometry(QRect(780, 170, 83, 29));
        horizontalLayoutWidget_4 = new QWidget(centralwidget);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(780, 211, 196, 22));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_4);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        timeSortView = new QLabel(horizontalLayoutWidget_4);
        timeSortView->setObjectName("timeSortView");

        horizontalLayout->addWidget(timeSortView);

        horizontalLayoutWidget_5 = new QWidget(centralwidget);
        horizontalLayoutWidget_5->setObjectName("horizontalLayoutWidget_5");
        horizontalLayoutWidget_5->setGeometry(QRect(780, 330, 199, 22));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        timeSearch = new QLabel(horizontalLayoutWidget_5);
        timeSearch->setObjectName("timeSearch");

        horizontalLayout_2->addWidget(timeSearch);

        timeSearchView = new QLabel(horizontalLayoutWidget_5);
        timeSearchView->setObjectName("timeSearchView");

        horizontalLayout_2->addWidget(timeSearchView);

        horizontalLayoutWidget_7 = new QWidget(centralwidget);
        horizontalLayoutWidget_7->setObjectName("horizontalLayoutWidget_7");
        horizontalLayoutWidget_7->setGeometry(QRect(780, 280, 371, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(horizontalLayoutWidget_7);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_4->addWidget(lineEdit);

        searchBtn = new QPushButton(horizontalLayoutWidget_7);
        searchBtn->setObjectName("searchBtn");

        horizontalLayout_4->addWidget(searchBtn);

        huySearchBtn = new QPushButton(horizontalLayoutWidget_7);
        huySearchBtn->setObjectName("huySearchBtn");
        huySearchBtn->setEnabled(false);

        horizontalLayout_4->addWidget(huySearchBtn);

        caculateBtn = new QPushButton(centralwidget);
        caculateBtn->setObjectName("caculateBtn");
        caculateBtn->setGeometry(QRect(780, 390, 81, 29));
        horizontalLayoutWidget_6 = new QWidget(centralwidget);
        horizontalLayoutWidget_6->setObjectName("horizontalLayoutWidget_6");
        horizontalLayoutWidget_6->setGeometry(QRect(780, 360, 275, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lableAverage = new QLabel(horizontalLayoutWidget_6);
        lableAverage->setObjectName("lableAverage");

        horizontalLayout_3->addWidget(lableAverage);

        lableAverageView = new QLabel(horizontalLayoutWidget_6);
        lableAverageView->setObjectName("lableAverageView");

        horizontalLayout_3->addWidget(lableAverageView);

        soLuongLable = new QLabel(horizontalLayoutWidget_6);
        soLuongLable->setObjectName("soLuongLable");

        horizontalLayout_3->addWidget(soLuongLable);

        SoLuongView = new QLabel(horizontalLayoutWidget_6);
        SoLuongView->setObjectName("SoLuongView");

        horizontalLayout_3->addWidget(SoLuongView);

        horizontalLayoutWidget_8 = new QWidget(centralwidget);
        horizontalLayoutWidget_8->setObjectName("horizontalLayoutWidget_8");
        horizontalLayoutWidget_8->setGeometry(QRect(780, 130, 222, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_8);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        labelSort = new QLabel(horizontalLayoutWidget_8);
        labelSort->setObjectName("labelSort");

        horizontalLayout_5->addWidget(labelSort);

        comboBoxSort = new QComboBox(horizontalLayoutWidget_8);
        comboBoxSort->addItem(QString());
        comboBoxSort->addItem(QString());
        comboBoxSort->addItem(QString());
        comboBoxSort->addItem(QString());
        comboBoxSort->addItem(QString());
        comboBoxSort->addItem(QString());
        comboBoxSort->addItem(QString());
        comboBoxSort->setObjectName("comboBoxSort");

        horizontalLayout_5->addWidget(comboBoxSort);

        horizontalLayoutWidget_9 = new QWidget(centralwidget);
        horizontalLayoutWidget_9->setObjectName("horizontalLayoutWidget_9");
        horizontalLayoutWidget_9->setGeometry(QRect(780, 240, 482, 31));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_9);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lableSearch = new QLabel(horizontalLayoutWidget_9);
        lableSearch->setObjectName("lableSearch");

        horizontalLayout_6->addWidget(lableSearch);

        comboBoxSearch = new QComboBox(horizontalLayoutWidget_9);
        comboBoxSearch->addItem(QString());
        comboBoxSearch->addItem(QString());
        comboBoxSearch->addItem(QString());
        comboBoxSearch->addItem(QString());
        comboBoxSearch->addItem(QString());
        comboBoxSearch->setObjectName("comboBoxSearch");

        horizontalLayout_6->addWidget(comboBoxSearch);

        label = new QLabel(horizontalLayoutWidget_9);
        label->setObjectName("label");

        horizontalLayout_6->addWidget(label);

        radioButtonTenDaoNguoYes = new QRadioButton(horizontalLayoutWidget_9);
        radioButtonTenDaoNguoYes->setObjectName("radioButtonTenDaoNguoYes");

        horizontalLayout_6->addWidget(radioButtonTenDaoNguoYes);

        radioButtonTenDaoNguocNo = new QRadioButton(horizontalLayoutWidget_9);
        radioButtonTenDaoNguocNo->setObjectName("radioButtonTenDaoNguocNo");

        horizontalLayout_6->addWidget(radioButtonTenDaoNguocNo);

        lableStatusView = new QLabel(centralwidget);
        lableStatusView->setObjectName("lableStatusView");
        lableStatusView->setGeometry(QRect(110, 530, 63, 20));
        horizontalLayoutWidget_10 = new QWidget(centralwidget);
        horizontalLayoutWidget_10->setObjectName("horizontalLayoutWidget_10");
        horizontalLayoutWidget_10->setGeometry(QRect(780, 420, 333, 41));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_10);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        listMinBtn = new QPushButton(horizontalLayoutWidget_10);
        listMinBtn->setObjectName("listMinBtn");

        horizontalLayout_7->addWidget(listMinBtn);

        huyMinBtn = new QPushButton(horizontalLayoutWidget_10);
        huyMinBtn->setObjectName("huyMinBtn");
        huyMinBtn->setEnabled(false);

        horizontalLayout_7->addWidget(huyMinBtn);

        horizontalLayoutWidget_11 = new QWidget(centralwidget);
        horizontalLayoutWidget_11->setObjectName("horizontalLayoutWidget_11");
        horizontalLayoutWidget_11->setGeometry(QRect(780, 470, 327, 41));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_11);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        listMaxBtn = new QPushButton(horizontalLayoutWidget_11);
        listMaxBtn->setObjectName("listMaxBtn");

        horizontalLayout_8->addWidget(listMaxBtn);

        huyMaxBtn = new QPushButton(horizontalLayoutWidget_11);
        huyMaxBtn->setObjectName("huyMaxBtn");
        huyMaxBtn->setEnabled(false);

        horizontalLayout_8->addWidget(huyMaxBtn);

        horizontalLayoutWidget_12 = new QWidget(centralwidget);
        horizontalLayoutWidget_12->setObjectName("horizontalLayoutWidget_12");
        horizontalLayoutWidget_12->setGeometry(QRect(1010, 130, 228, 31));
        horizontalLayout_9 = new QHBoxLayout(horizontalLayoutWidget_12);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        labelSort_2 = new QLabel(horizontalLayoutWidget_12);
        labelSort_2->setObjectName("labelSort_2");

        horizontalLayout_9->addWidget(labelSort_2);

        comboBoxStandarSort = new QComboBox(horizontalLayoutWidget_12);
        comboBoxStandarSort->addItem(QString());
        comboBoxStandarSort->addItem(QString());
        comboBoxStandarSort->addItem(QString());
        comboBoxStandarSort->setObjectName("comboBoxStandarSort");

        horizontalLayout_9->addWidget(comboBoxStandarSort);

        comboBoxLopTb = new QComboBox(centralwidget);
        comboBoxLopTb->setObjectName("comboBoxLopTb");
        comboBoxLopTb->setGeometry(QRect(1110, 360, 111, 28));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(440, 530, 331, 31));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        addBtn = new QPushButton(layoutWidget);
        addBtn->setObjectName("addBtn");

        horizontalLayout_10->addWidget(addBtn);

        saveBtn = new QPushButton(layoutWidget);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout_10->addWidget(saveBtn);

        lcdSoLuongSinhVien = new QLCDNumber(centralwidget);
        lcdSoLuongSinhVien->setObjectName("lcdSoLuongSinhVien");
        lcdSoLuongSinhVien->setGeometry(QRect(780, 90, 64, 23));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(940, 40, 63, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1307, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 sinh vi\303\252n", nullptr));
        importBtn->setText(QCoreApplication::translate("MainWindow", "Nh\341\272\255p t\341\273\207p", nullptr));
        labelFilePath->setText(QCoreApplication::translate("MainWindow", "Ch\306\260a ch\341\273\215n file", nullptr));
        labelMethod->setText(QCoreApplication::translate("MainWindow", "Ph\306\260\306\241ng th\341\273\251c l\306\260u tr\341\273\257", nullptr));
        methodBox->setItemText(0, QCoreApplication::translate("MainWindow", "--- Select ---", nullptr));
        methodBox->setItemText(1, QCoreApplication::translate("MainWindow", "M\341\272\243ng", nullptr));
        methodBox->setItemText(2, QCoreApplication::translate("MainWindow", "Danh s\303\241ch li\303\252n k\341\272\277t \304\221\306\241n", nullptr));
        methodBox->setItemText(3, QCoreApplication::translate("MainWindow", "Danh s\303\241ch li\303\252n k\341\272\277t k\303\251p", nullptr));
        methodBox->setItemText(4, QCoreApplication::translate("MainWindow", "Danh s\303\241ch li\303\252n k\341\272\277t v\303\262ng", nullptr));

        clearBtn->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        downloadBtn->setText(QCoreApplication::translate("MainWindow", "T\341\272\243i t\341\273\207p", nullptr));
        exitBtn->setText(QCoreApplication::translate("MainWindow", "Tho\303\241t", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "M\303\243 s\341\273\221 sinh vi\303\252n", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "H\341\273\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "T\303\252n", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "L\341\273\233p", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\304\220i\341\273\203m", nullptr));
        sortBtn->setText(QCoreApplication::translate("MainWindow", "S\341\272\257p x\341\272\277p", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Th\341\273\235i gian s\341\272\257p x\341\272\277p :", nullptr));
        timeSortView->setText(QString());
        timeSearch->setText(QCoreApplication::translate("MainWindow", "Th\341\273\235i gian t\303\254m ki\341\272\277m:", nullptr));
        timeSearchView->setText(QString());
        searchBtn->setText(QCoreApplication::translate("MainWindow", "T\303\254m ki\341\272\277m", nullptr));
        huySearchBtn->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y", nullptr));
        caculateBtn->setText(QCoreApplication::translate("MainWindow", "T\303\255nh", nullptr));
        lableAverage->setText(QCoreApplication::translate("MainWindow", "\304\220i\341\273\203m trung b\303\254nh :", nullptr));
        lableAverageView->setText(QString());
        soLuongLable->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 l\306\260\341\273\243ng :", nullptr));
        SoLuongView->setText(QString());
        labelSort->setText(QCoreApplication::translate("MainWindow", "S\341\272\257p x\341\272\277p b\341\272\261ng", nullptr));
        comboBoxSort->setItemText(0, QCoreApplication::translate("MainWindow", "--- Select ---", nullptr));
        comboBoxSort->setItemText(1, QCoreApplication::translate("MainWindow", "Bubble sort", nullptr));
        comboBoxSort->setItemText(2, QCoreApplication::translate("MainWindow", "Insertion sort", nullptr));
        comboBoxSort->setItemText(3, QCoreApplication::translate("MainWindow", "Selection sort", nullptr));
        comboBoxSort->setItemText(4, QCoreApplication::translate("MainWindow", "Quick sort", nullptr));
        comboBoxSort->setItemText(5, QCoreApplication::translate("MainWindow", "Merge sort", nullptr));
        comboBoxSort->setItemText(6, QCoreApplication::translate("MainWindow", "Heap sort", nullptr));

        lableSearch->setText(QCoreApplication::translate("MainWindow", "T\303\254m ki\341\272\277m theo", nullptr));
        comboBoxSearch->setItemText(0, QCoreApplication::translate("MainWindow", "M\303\243 s\341\273\221 sinh vi\303\252n", nullptr));
        comboBoxSearch->setItemText(1, QCoreApplication::translate("MainWindow", "T\303\252n", nullptr));
        comboBoxSearch->setItemText(2, QCoreApplication::translate("MainWindow", "\304\220i\341\273\203m", nullptr));
        comboBoxSearch->setItemText(3, QCoreApplication::translate("MainWindow", "H\341\273\215", nullptr));
        comboBoxSearch->setItemText(4, QCoreApplication::translate("MainWindow", "L\341\273\233p", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "T\303\252n \304\221\341\272\243o ng\306\260\341\273\243c : ", nullptr));
        radioButtonTenDaoNguoYes->setText(QCoreApplication::translate("MainWindow", "c\303\263", nullptr));
        radioButtonTenDaoNguocNo->setText(QCoreApplication::translate("MainWindow", "kh\303\264ng", nullptr));
        lableStatusView->setText(QString());
        listMinBtn->setText(QCoreApplication::translate("MainWindow", "Li\341\273\207t k\303\252 c\303\241c sinh vi\303\252n \304\221i\341\273\203m th\341\272\245p nh\341\272\245t", nullptr));
        huyMinBtn->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y", nullptr));
        listMaxBtn->setText(QCoreApplication::translate("MainWindow", "Li\341\273\207t k\303\252 c\303\241c sinh vi\303\252n \304\221i\341\273\203m cao nh\341\272\245t", nullptr));
        huyMaxBtn->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y", nullptr));
        labelSort_2->setText(QCoreApplication::translate("MainWindow", "S\341\272\257p x\341\272\277p theo", nullptr));
        comboBoxStandarSort->setItemText(0, QCoreApplication::translate("MainWindow", "M\303\243 s\341\273\221 sinh vi\303\252n", nullptr));
        comboBoxStandarSort->setItemText(1, QCoreApplication::translate("MainWindow", "T\303\252n", nullptr));
        comboBoxStandarSort->setItemText(2, QCoreApplication::translate("MainWindow", "\304\220i\341\273\203m", nullptr));

        addBtn->setText(QCoreApplication::translate("MainWindow", "Th\303\252m sinh vi\303\252n", nullptr));
        saveBtn->setText(QCoreApplication::translate("MainWindow", "L\306\260u", nullptr));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
