#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "getter_setter_auto.cpp"

#include <QList>
#include <QMainWindow>
#include "dslk_don.h"
#include "dslk_vong.h"
#include "mang.h"
#include <QTimer>
#include "dslk_kep.h"
#include <QTableWidget>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    PROPERTY(int ,selectedIndex, SelectedIndex);
    PROPERTY(int , sortIndex, SortIndex);
    PROPERTY(QString, path, Path);
    PROPERTY(bool, isImport, IsImport);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_importBtn_clicked();


    void on_exitBtn_clicked();

    void on_downloadBtn_clicked();

    void initDs();

    bool initData();

    void handleBubbleSort();

    void handleInsertionSort();

    void handleSelectionSort();

    void on_sortBtn_clicked();

    void on_caculateBtn_clicked();

    void on_comboBoxSort_currentIndexChanged(int index);

    void on_listMinBtn_clicked();

    void on_listMaxBtn_clicked();

    void on_huyMaxBtn_clicked();

    void on_huyMinBtn_clicked();


    void on_searchBtn_clicked();

    void on_huySearchBtn_clicked();
    void on_addBtn_clicked();

    void showTableContextMenu(const QPoint &pos);

    void on_saveBtn_clicked();

    void on_clearBtn_clicked();

private:
    template<typename ListType>
    void handleTimKiem(ListType &list);
    void handleMergeSort();
    void resert();
    void handleQuickSort();
    void handleTimKiemArr(mang &ds);
    void handleTimKiemVong();
    void handleXoaSv(QString &mssv);
    void handleTimKiemKep();
    void handleHeapSort();
    int getSoLuong(QString &lop);
public:
    void updateTable();
    void loadKetQuaTimKiem(QList<int> indexes, QTableWidget* table = nullptr);
private:
    int hue = 0;
public:

    Ui::MainWindow *ui;
    dslk_don ds_don;
    // dslk_kep ds_kep;
    dslk_vong ds_vong;
    dslk_kep ds_kep;
    mang ds_mang;
    QSet<QString> mssvSet;
    int searchMode = -1;


};
#endif // MAINWINDOW_H
