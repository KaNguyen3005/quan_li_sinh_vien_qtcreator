#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "read_write.cpp"
#include "dslk_don.h"
#include "helper.h"
#include <QElapsedTimer>
#include "addui.h"
#include "updateui.h"
#include <QAbstractItemView>
#include <QTableWidgetItem>
#include <QTimer>
#include <QRandomGenerator>
#include <cmath>
#include <QGraphicsDropShadowEffect>
//"E:\learnLongLife\c++\quan_li_sinh_vien\icons\PTIT.png"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    selectedIndex = 0;
    sortIndex = 0;
    path = "";
    ui->setupUi(this);
    isImport = false;
    // Set độ rộng các cột (theo chỉ số cột)
    ui->tableWidget->setColumnWidth(0, 120); // MSSV
    ui->tableWidget->setColumnWidth(1, 150); // Họ
    ui->tableWidget->setColumnWidth(2, 100); // Tên
    ui->tableWidget->setColumnWidth(3, 100); // Lớp
    ui->tableWidget->setColumnWidth(4, 80);  // Điểm
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setWindowIcon(QIcon(":\\images\\icons\\app.png"));
    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested,
            this, &MainWindow::showTableContextMenu);
    QPalette p = ui->lcdSoLuongSinhVien->palette();
    p.setColor(QPalette::WindowText, QColor("#00FF66"));  // Xanh lá sáng hơn
    ui->lcdSoLuongSinhVien->setAutoFillBackground(true);

    ui->lcdSoLuongSinhVien->setPalette(p);
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pix(":\\images\\icons\\PTIT.png");
    scene->addPixmap(pix);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->graphicsView->scale(3.0, 3.0);  // Phóng to 2 lần
    ui->statusBtn->setEnabled(false);
    ui->statusBtn->setText("✖ Not import");
    ui->statusBtn->setStyleSheet("QPushButton { color: white; background-color: red; border-radius: 8px; padding: 6px; font: bold 14px; }");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->greeting->setAlignment(Qt::AlignCenter);
    ui->greeting->setStyleSheet(R"(
    QLabel {
        font-size: 24px;
        font-weight: bold;
        color: white;
        background-color: qlineargradient(
            spread:pad, x1:0, y1:0, x2:1, y2:0,
            stop:0 #3f87a6, stop:1 #ebf8e1
        );
        border: 3px solid #4CAF50;
        border-radius: 15px;
        padding: 10px;
    }
)");

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(4, 4);
    shadow->setColor(QColor(0, 0, 0, 160));  // bóng đen, độ mờ nhẹ

    ui->greeting->setGraphicsEffect(shadow);
    QRegularExpression regex("[\\p{L}0-9\\-._ ]+");
    QValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineEdit->setValidator(validator);
}
MainWindow::~MainWindow()
{
    delete ui;
}

bool showYesNoMessageBox(QWidget* parent, const QString& title, const QString& message) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(parent, title, message,
                                  QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}


void MainWindow::on_importBtn_clicked()
{
    // Mở hộp thoại chọn tệp
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    "Chọn tệp",
                                                    "",
                                                    "CSV Files (*.csv);;All Files (*.*)");

    // Kiểm tra nếu người dùng đã chọn tệp
    if (!filePath.isEmpty()) {
        // Hiển thị đường dẫn tệp
        QMessageBox::information(this, "Tệp đã chọn", "Đường dẫn tệp: " + filePath);
    }
    path = filePath;
    ui->labelFilePath->setText(filePath);
    qDebug() << path;
}





void MainWindow::on_exitBtn_clicked()
{
    this->close();

}


void MainWindow::initDs() {
    if(!ds_don.isEmpty()){
    }
}

bool MainWindow::initData() {
    QStringList errors;
    switch(selectedIndex){
    case 0:
        break;
    case 1:{
        errors = loadDuLieu(path, ds_mang, mssvSet);
        if(!errors.isEmpty()) ds_mang.clear();
        break;
    }
    case 2:{

        errors = loadDuLieu(path, ds_don, mssvSet);
        if(!errors.isEmpty()) ds_don.clear();

        break;
    }
    case 3:
        errors = loadDuLieu(path, ds_kep, mssvSet);
        if(!errors.isEmpty()) ds_kep.clear();

        break;
    case 4:
        errors = loadDuLieu(path, ds_vong, mssvSet);
        if(!errors.isEmpty()) ds_vong.clear();
        break;
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không hợp lệ");
        break;
    }


    if (!errors.isEmpty()) {
        mssvSet.clear();
        QString errorText = "Đã xảy ra lỗi trong quá trình import:\n\n" + errors.join("\n");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Lỗi Import Dữ Liệu");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Import thất bại do dữ liệu không hợp lệ.");
        msgBox.setDetailedText(errorText);  // Mở rộng để xem chi tiết
        msgBox.exec();
        return false;
    } else {
        QMessageBox::information(this, "Thành công", "Import dữ liệu thành công!");
        return true;
    }
}

template <typename ListType>
void loadToTable(ListType& ds, QTableWidget* tableWidget, bool isVong = false) {
    tableWidget->clear();                      // Xóa nội dung cũ
    tableWidget->setRowCount(0);               // Đặt lại số hàng
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm" << "Tên đảo ngược");
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    int row = 0;
    // Duyệt danh sách (phụ thuộc cách bạn tổ chức)
    auto temp = ds.getFirst();
    if(temp == nullptr) return;

    if(isVong && ds.isEmpty()){
        return;
    }
    if(temp != nullptr){
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(temp->sv.getMssv()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(temp->sv.getHo()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(temp->sv.getTen()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(temp->sv.getLop()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(temp->sv.getDiem())));
        tableWidget->setItem(row, 5,new QTableWidgetItem(""));
        ++row;
    }
    for (typename ListType::node* node = ds.getFirst()->next; node != nullptr && (!isVong || node != ds.getFirst()); node = node->next) {
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(node->sv.getMssv()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(node->sv.getHo()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(node->sv.getTen()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(node->sv.getLop()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(node->sv.getDiem())));
        tableWidget->setItem(row, 5,new QTableWidgetItem(""));
        ++row;
    }

}

QSet<QString> getLops(QTableWidget* table) {
    QSet<QString> set;
    for(int i = 0; i < table->rowCount(); i++){
        set.insert(table->item(i, 3)->text());
    }
    return set;
}


void loadToTableArray(mang& ds, QTableWidget* tableWidget) {
    tableWidget->clear();                      // Xóa nội dung cũ
    tableWidget->setRowCount(0);               // Đặt lại số hàng

    tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm" << "");
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    int row = 0;

    // Duyệt danh sách (phụ thuộc cách bạn tổ chức)
    for (int i = 0; i < ds.size(); i++) {
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(ds.arr[i].mssv));
        tableWidget->setItem(row, 1, new QTableWidgetItem(ds.arr[i].ho));
        tableWidget->setItem(row, 2, new QTableWidgetItem(ds.arr[i].ten));
        tableWidget->setItem(row, 3, new QTableWidgetItem(ds.arr[i].lop));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(ds.arr[i].diem)));
        tableWidget->setItem(row, 5,new QTableWidgetItem(""));

        ++row;
    }
}

void MainWindow::on_downloadBtn_clicked()
{
    selectedIndex = ui->methodBox->currentIndex();
    if(path == "" || selectedIndex == 0){
        QMessageBox::critical(this, "Lỗi", "Bạn chưa chọn file hoặc chọn cách lưu trữ");
        return;
    }
    initDs();
    ui->comboBoxLopTb->clear();
    bool checkData = initData();
    if(checkData && selectedIndex != 1){
        switch(selectedIndex){
        case 2: {
            loadToTable(ds_don, ui->tableWidget);
            isImport = true;

            break;
        }
        case 3: {

            loadToTable(ds_kep, ui->tableWidget);
            isImport = true;

            break;
        }
        case 4: {
            loadToTable(ds_vong, ui->tableWidget, true);
            isImport = true;
            break;
        }
        default:
            break;
        }

    }
    else if(selectedIndex == 1){
        loadToTableArray(ds_mang, ui->tableWidget);
        isImport = true;

    }

    else return;
    QSet<QString> set = getLops(ui->tableWidget);
    QStringList sortedList = QStringList(set.begin(), set.end());
    sortedList.sort(Qt::CaseInsensitive);  // không phân biệt hoa thường (nếu cần)

    for (const QString &x : sortedList) {
        ui->comboBoxLopTb->addItem(x);
    }
    ui->lcdSoLuongSinhVien->display(ui->tableWidget->rowCount());
    ui->clearBtn->setEnabled(true);
    ui->downloadBtn->setEnabled(false);
    ui->methodBox->setEnabled(false);
    ui->statusBtn->setText("✔ Imported");
    ui->statusBtn->setStyleSheet("QPushButton { color: white; background-color: green; border-radius: 8px; padding: 6px; font: bold 14px; }");

}





void MainWindow::handleBubbleSort(){
    switch (selectedIndex){
        case 0:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
        case 1:{
            QElapsedTimer timer;
            Helper<dslk_don::node, dslk_don> helper;
            int standardIndex = ui->comboBoxStandarSort->currentIndex();
            timer.start();  // Bắt đầu đếm thời gian
            ds_mang.bubble_sort(standardIndex + 1);
            qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
            QString result;
            searchMode = standardIndex;
            result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
            ui->timeSortView->setText(result);
            loadToTableArray(ds_mang, ui->tableWidget);
            break;
        }
        case 2: {
            QElapsedTimer timer;
            Helper<dslk_don::node, dslk_don> helper;
            int standardIndex = ui->comboBoxStandarSort->currentIndex();
            auto cmp = helper.getCmp(standardIndex);
            timer.start();  // Bắt đầu đếm thời gian
            helper.buble_sort(ds_don.getFirst(), false, cmp);
            qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
            QString result;

            result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
            ui->timeSortView->setText(result);
            loadToTable(ds_don, ui->tableWidget);
            break;
        }
        case 3:
        {
            QElapsedTimer timer;
            Helper<dslk_kep::node, dslk_kep> helper;
            int standardIndex = ui->comboBoxStandarSort->currentIndex();
            auto cmp = helper.getCmp(standardIndex);
            timer.start();  // Bắt đầu đếm thời gian
            ds_kep.bubble_sort(cmp);
            qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
            QString result;
            searchMode = standardIndex;
            result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
            ui->timeSortView->setText(result);
            loadToTable(ds_kep, ui->tableWidget);
            break;
        }
        case 4:{
            QElapsedTimer timer;
            Helper<dslk_vong::node, dslk_vong> helper;
            int standard = ui->comboBoxStandarSort->currentIndex();
            auto cmp = helper.getCmp(standard);
            timer.start();  // Bắt đầu đếm thời gian
            helper.buble_sort(ds_vong.getFirst(),true, cmp);
            qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
            QString result;

            result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
            ui->timeSortView->setText(result);
            loadToTable(ds_vong, ui->tableWidget, true);
            break;
        }
        default:
            QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
    }
}

void MainWindow::handleInsertionSort(){
    switch (selectedIndex){
    case 0:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 1:
    {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        timer.start();  // Bắt đầu đếm thời gian
        ds_mang.insertion_sort(standardIndex + 1);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        searchMode = standardIndex;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }    case 2: {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);
        timer.start();  // Bắt đầu đếm thời gian
        helper.insertion_sort(ds_don.getFirst(), false, cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_don, ui->tableWidget);
        break;
    }
    case 3:
    {
        QElapsedTimer timer;
        Helper<dslk_kep::node, dslk_kep> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);        
        timer.start();  // Bắt đầu đếm thời gian
        ds_kep.insertion_sort(cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        searchMode = standardIndex;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_kep, ui->tableWidget, true);
        break;
    }
    case 4:
    {
        QElapsedTimer timer;
        Helper<dslk_vong::node, dslk_vong> helper;
        int standard = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standard);
        timer.start();  // Bắt đầu đếm thời gian
        helper.insertion_sort(ds_vong.getFirst(),true, cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    }
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
    }
}


void MainWindow::handleSelectionSort(){
    switch (selectedIndex){
    case 0:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 1:
    {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        timer.start();  // Bắt đầu đếm thời gian
        ds_mang.selection_sort(standardIndex + 1);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        searchMode = standardIndex;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }
    case 2: {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);
        timer.start();  // Bắt đầu đếm thời gian
        helper.selection_sort(ds_don.getFirst(), false, cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_don, ui->tableWidget);
        break;
    }
    case 3:{

        QElapsedTimer timer;
        Helper<dslk_kep::node, dslk_kep> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);
        timer.start();  // Bắt đầu đếm thời gian
        ds_kep.selection_sort(cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        searchMode = standardIndex;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_kep, ui->tableWidget);

        break;
    }
    case 4:
    {
        QElapsedTimer timer;
        Helper<dslk_vong::node, dslk_vong> helper;
        int standard = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standard);
        timer.start();  // Bắt đầu đếm thời gian
        helper.selection_sort(ds_vong.getFirst(),true, cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    }
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
    }
}


void MainWindow::handleMergeSort(){
    switch (selectedIndex){
    case 0:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 1:
    {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        timer.start();  // Bắt đầu đếm thời gian
        ds_mang.merge_sort(standardIndex + 1, 0, ds_mang.size() - 1);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        searchMode = standardIndex;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }
    case 2: {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);
        timer.start();  // Bắt đầu đếm thời gian
        helper.mergeSort(&ds_don.getFirst(), cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_don, ui->tableWidget);
        break;
    }
    case 3:
    {
        QElapsedTimer timer;
        Helper<dslk_kep::node, dslk_kep> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);
        timer.start();  // Bắt đầu đếm thời gian
        helper.mergeSort(&ds_kep.getFirst(), cmp);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        searchMode = standardIndex;
        ui->timeSortView->setText(result);
        loadToTable(ds_kep, ui->tableWidget);
        break;
    }
    case 4:
    {
        QElapsedTimer timer;
        Helper<dslk_vong::node, dslk_vong> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        auto cmp = helper.getCmp(standardIndex);
        // 1. Ngắt vòng

        timer.start();  // Bắt đầu đếm thời gian
        helper.mergeSortVong_last(ds_vong.last, cmp);

        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;

        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    }
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
    }
}

void MainWindow::handleQuickSort(){
    switch (selectedIndex){
    case 0:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 1:
    {
        QElapsedTimer timer;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        timer.start();  // Bắt đầu đếm thời gian
        ds_mang.quick_sort(standardIndex + 1, 0, ds_mang.size() - 1);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        searchMode = standardIndex;
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }
    case 2:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 3:
    {
        QElapsedTimer timer;
        Helper<dslk_don::node, dslk_don> helper;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        timer.start();  // Bắt đầu đếm thời gian
        switch (standardIndex) {
        case 0:
            ds_kep.quick_sort(0, ds_kep.length - 1, ds_kep.cmp_bang_mssv);
            break;
        case 1:

            ds_kep.quick_sort(0, ds_kep.length - 1, ds_kep.cmp_bang_ten);

            break;
        case 2:
            ds_kep.quick_sort(0, ds_kep.length - 1, ds_kep.cmp_bang_diem);
            break;
        default:
            break;
        }
        searchMode = standardIndex;
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_kep, ui->tableWidget);
        break;
    }
    case 4:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
    }
}

void MainWindow::handleHeapSort() {
    switch (selectedIndex){
    case 0:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 1:
    {
        QElapsedTimer timer;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();
        timer.start();  // Bắt đầu đếm thời gian
        ds_mang.heap_sort(standardIndex + 1,ds_mang.size());
        searchMode = standardIndex;
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }
    case 2:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    case 3:
    {
        QElapsedTimer timer;
        int standardIndex = ui->comboBoxStandarSort->currentIndex();

        timer.start();  // Bắt đầu đếm thời gian
        switch(standardIndex) {
            case 0:
                ds_kep.heap_sort(ds_kep.cmp_bang_mssv);
                break;
            case 1:
                ds_kep.heap_sort(ds_kep.cmp_bang_ten);
                break;
            case 2:
                ds_kep.heap_sort(ds_kep.cmp_bang_diem);
                break;
        }
        searchMode = standardIndex;
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSortView->setText(result);
        loadToTable(ds_kep, ui->tableWidget);
        break;
    }
    case 4:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    }
}

void MainWindow::on_sortBtn_clicked()
{
    if(!isImport){
        QMessageBox::critical(this, "Lỗi", "Vui lòng import trước khi sắp xếp");
        return;
    }
    switch(sortIndex) {
    case 0:
        QMessageBox::critical(this, "Lỗi", "Vui lòng chọn phương thức sort");
        break;
    case 1:
        handleBubbleSort();
        break;
    case 2:
        handleInsertionSort();
        break;
    case 3:
        handleSelectionSort();
        break;
    case 4:
        handleQuickSort();
        break;
    case 5:
        handleMergeSort();
        break;
    case 6:
        handleHeapSort();
        break;
    default:
        QMessageBox::critical(this,"Lỗi", "Phương thức lưu trữ không phù hợp");
        break;
    }
}


int MainWindow::getSoLuong(QString &lop){
    int rows = ui->tableWidget->rowCount();
    int cnt = 0;
    for(int i = 0; i < rows; i++){
        QTableWidgetItem* item = ui->tableWidget->item(i, 3);
        QString temp = item->text();
        if(temp == lop){
            cnt++;
        }
    }
    return cnt;
}

void MainWindow::on_caculateBtn_clicked()
{
    if(!isImport || !selectedIndex) {
        QMessageBox::critical(this,"Lỗi", "Hãy import dữ liệu trước khi tính điểm trung bình");
        return;
    }
    QString selectedLop = ui->comboBoxLopTb->currentText();

    switch (selectedIndex){
    case 1:{
        qreal result = ds_mang.tinh_tb(selectedLop);
        ui->lableAverageView->setText(QString::number(result));
        break;
    }
    case 2: {
        Helper<dslk_don::node, dslk_don> helper;
        qreal result = helper.tinh_tb(ds_don.getFirst(), selectedLop);
        ui->lableAverageView->setText(QString::number(result));
        break;
    }
    case 3:
    {
        Helper<dslk_kep::node, dslk_kep> helper;
        qreal result = helper.tinh_tb(ds_kep.getFirst(), selectedLop);
        ui->lableAverageView->setText(QString::number(result));
        break;
    }
    case 4:{
        qreal result = ds_vong.tinh_tb(selectedLop);
        ui->lableAverageView->setText(QString::number(result));
        break;
    }
    default:
        break;
    }
    int soLuong = getSoLuong(selectedLop);
    ui->SoLuongView->setText(QString::number(soLuong));
}




void MainWindow::on_comboBoxSort_currentIndexChanged(int index)
{
    sortIndex = index;
}


void MainWindow::on_listMinBtn_clicked()
{
    qDebug() << isImport;
    if(!isImport){
        QMessageBox::critical(this, "Lỗi", "Vui lòng chọn import trước khi chọn chức năng này");
        return;
    }
    switch (selectedIndex){
    case 1:
    {
        mang list = ds_mang.danh_sach_diem_thap();
        loadToTableArray(list, ui->tableWidget);
        ui->huyMinBtn->setEnabled(true);
        break;
    }
    case 2: {
        Helper<dslk_don::node, dslk_don> helper;
        dslk_don list = helper.liet_ke_sv_diem_thap(ds_don.getFirst());
        loadToTable(list, ui->tableWidget);
        ui->huyMinBtn->setEnabled(true);
        break;
    }
    case 3:{

        Helper<dslk_kep::node, dslk_kep> helper;
        dslk_kep list = helper.liet_ke_sv_diem_thap(ds_kep.getFirst());
        loadToTable(list, ui->tableWidget);
        ui->huyMinBtn->setEnabled(true);
        break;
    }
    case 4:{
        dslk_vong list = ds_vong.liet_ke_diem_thap();
        loadToTable(list, ui->tableWidget, true);
        ui->huyMinBtn->setEnabled(true);
        break;
    }
    default:
        break;
    }
    ui->huyMaxBtn->setEnabled(false);
    ui->huySearchBtn->setEnabled(false);
    ui->searchBtn->setEnabled(false);
    ui->comboBoxSearch->setEnabled(false);
    ui->sortBtn->setEnabled(false);

}


void MainWindow::on_listMaxBtn_clicked()
{
    if(!isImport){
        QMessageBox::critical(this, "Lỗi", "Vui lòng chọn import trước khi chọn chức năng này");
        return;
    }

    switch (selectedIndex){
    case 1:    {
        mang list = ds_mang.danh_sach_diem_cao();
        loadToTableArray(list, ui->tableWidget);
        ui->huyMaxBtn->setEnabled(true);
        break;
    }
    case 2: {
        Helper<dslk_don::node, dslk_don> helper;
        dslk_don list = helper.liet_ke_sv_diem_cao(ds_don.getFirst());
        loadToTable(list, ui->tableWidget);
        ui->huyMaxBtn->setEnabled(true);
        break;
    }
    case 3:
    {
        Helper<dslk_kep::node, dslk_kep> helper;
        dslk_kep list = helper.liet_ke_sv_diem_cao(ds_kep.getFirst());
        loadToTable(list, ui->tableWidget);
        ui->huyMaxBtn->setEnabled(true);
        break;
    }
    case 4:{
        dslk_vong list = ds_vong.liet_ke_diem_cao();
        loadToTable(list, ui->tableWidget, true);
        ui->huyMaxBtn->setEnabled(true);
        break;
    }
    default:
        break;
    }
    ui->huyMinBtn->setEnabled(false);
    ui->huySearchBtn->setEnabled(false);
    ui->searchBtn->setEnabled(false);
    ui->comboBoxSearch->setEnabled(false);
    ui->sortBtn->setEnabled(false);
}


void MainWindow::on_huyMaxBtn_clicked()
{
    switch (selectedIndex){
    case 1:    {
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }
    case 2: {
        loadToTable(ds_don, ui->tableWidget);
        break;
    }
    case 3:
        loadToTable(ds_kep, ui->tableWidget);

        break;
    case 4:
        loadToTable(ds_vong, ui->tableWidget, true);

        break;
    default:
        break;
    }
    ui->huyMaxBtn->setEnabled(false);
    ui->searchBtn->setEnabled(true);
    ui->comboBoxSearch->setEnabled(true);
    ui->sortBtn->setEnabled(true);

}


void MainWindow::on_huyMinBtn_clicked()
{
    switch (selectedIndex){
    case 1:    {
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    }
    case 2: {
        loadToTable(ds_don, ui->tableWidget);
        break;
    }
    case 3:
        loadToTable(ds_kep, ui->tableWidget);

        break;
    case 4:
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    default:
        break;
    }
    ui->huyMinBtn->setEnabled(false);
    ui->searchBtn->setEnabled(true);
    ui->comboBoxSearch->setEnabled(true);
    ui->sortBtn->setEnabled(true);


}

void resertTable(int i, int j, QTableWidget* table =nullptr) {
    QTableWidgetItem* item = table->item(i, j);
    if (item) {
        item->setBackground(QBrush());  // Hoặc QColor("#ffeecc")
        item->setForeground(QBrush());   // Màu chữ
    }
}

void to_mau(int i, int j, QTableWidget* table = nullptr){
    QTableWidgetItem* item = table->item(i, j);
    if (item) {
        item->setBackground(Qt::red);  // Hoặc QColor("#ffeecc")
        item->setForeground(Qt::black);   // Màu chữ
    }
}

QString ten_dao_nguoc(QString temp){
    QString result = "";
    int n = temp.length();
    for(int i = n - 1; i >= 0; i--){
        result += temp[i];
    }
    return result;
}

void dao_nguoc(int i, int j, QString &temp,QTableWidget* table = nullptr){
    if (!table) return;

    if (table->rowCount() <= i)
        table->setRowCount(i + 1);
    if (table->columnCount() <= j)
        table->setColumnCount(j + 1);

    QString reversed = ten_dao_nguoc(temp);

    QTableWidgetItem* item = table->item(i, j);
    if (!item) {
        item = new QTableWidgetItem(reversed);
        table->setItem(i, j, item);
    } else {
        item->setText(reversed);
    }
}

template<typename ListType>
void MainWindow::handleTimKiem(ListType &list) {
    int index = ui->comboBoxSearch->currentIndex();
    bool checkDaoNguoc = ui->radioButtonTenDaoNguoYes->isChecked();
    Helper<typename ListType::node, ListType> helper;
    QString input = ui->lineEdit->text();
    QElapsedTimer timer;
    QList<int> indexes = {};
    switch(index){
    case 0:{
        QString input = ui->lineEdit->text();
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_ma(list.getFirst(),input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos /1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 1:{
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = QList(helper.tim_kiem_theo_ten(list.getFirst(),input));
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 2: {
        QString text = ui->lineEdit->text();
        bool ok;
        text.toFloat(&ok);
        if(!ok) break;
        double input = text.toDouble();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_diem(list.getFirst(),input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 3:{
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_ho(list.getFirst(),input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 4:
    {
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_lop(list.getFirst(),input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    default:
        break;
    }
    if(indexes.size() == 0) {
        QMessageBox::information(this,"Thông tin", "Không tìm thấy");
        return;
    }
    if(checkDaoNguoc){
        ui->tableWidget->setColumnCount(6); // Ví dụ: 6 cột
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm" << "Tên đảo ngược");
    }
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            resertTable(i, j, ui->tableWidget);
        }
    }
    if(index == 1){
        index = 2;
    }
    else if(index == 2){
        index = 4;
    }
    else if(index == 3){
        index = 1;
    }
    else if(index == 4){
        index = 3;
    }
    for(auto x : indexes){
        int columnCount = ui->tableWidget->columnCount();
        if(checkDaoNguoc){
            QTableWidgetItem* item_ho = ui->tableWidget->item(x, 1);
            QTableWidgetItem* item_ten = ui->tableWidget->item(x, 2);
            QString temp = item_ho->text() + " " + item_ten->text();
            dao_nguoc(x, 5, temp, ui->tableWidget);
        }

        to_mau(x, index, ui->tableWidget);

    }
    loadKetQuaTimKiem(indexes, ui->tableWidget);
    QString quantity = QString::number(indexes.length());
    ui->quantitySearchView_2->setText(quantity);

}

void MainWindow::handleTimKiemArr(mang &ds) {
    int index = ui->comboBoxSearch->currentIndex();
    QString input = ui->lineEdit->text();
    QElapsedTimer timer;
    QList<int> indexes;
    bool checkDaoNguoc = ui->radioButtonTenDaoNguoYes->isChecked();
    bool isNhiPhan = false;
    switch(index){
    case 0:{
        timer.start();  // Bắt đầu đếm thời gian
        if(searchMode == 0){
            indexes = ds.tim_kiem_nhi_phan_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
            isNhiPhan = true;
        }
        else indexes = ds.tim_vet_can_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }

    case 1:{
        timer.start();  // Bắt đầu đếm thời gian
        if(searchMode == 1){

            indexes = ds.tim_kiem_nhi_phan_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
            isNhiPhan = true;

        }
        else {

            indexes = ds.tim_vet_can_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        }
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }
    case 2: {
        timer.start();  // Bắt đầu đếm thời gian
        if(searchMode == 2){
            isNhiPhan = true;

            indexes = ds.tim_kiem_nhi_phan_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        }
        else {
            indexes = ds.tim_vet_can_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        }
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }
    case 3:{
        timer.start();  // Bắt đầu đếm thời gian
        if(searchMode == 3){
            isNhiPhan = true;

            indexes = ds.tim_kiem_nhi_phan_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        }
        else{

            indexes = ds.tim_vet_can_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        }
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }
    case 4:
    {
        timer.start();  // Bắt đầu đếm thời gian
        if(searchMode == 4){
            isNhiPhan = true;

            indexes = ds.tim_kiem_nhi_phan_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        }
        else indexes = ds.tim_vet_can_ds_sv(ui->comboBoxSearch->currentIndex() + 1, input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }
    default:
        break;
    }
    if(indexes.size() == 0) {
        QMessageBox::information(this,"Thông tin", "Không tìm thấy");
        return;
    }
    if(checkDaoNguoc){
        ui->tableWidget->setColumnCount(6); // Ví dụ: 6 cột
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm" << "Tên đảo ngược");
    }
    else{
        ui->tableWidget->setColumnCount(5); // Ví dụ: 6 cột
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm");
    }
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            resertTable(i, j, ui->tableWidget);
        }
    }
    if(index == 1){
        index = 2;
    }
    else if(index == 2){
        index = 4;
    }
    else if(index == 3){
        index = 1;
    }
    else if(index == 4){
        index = 3;
    }
    for(auto x : indexes){
        int columnCount = ui->tableWidget->columnCount();
        if(checkDaoNguoc){
            QTableWidgetItem* item_ho = ui->tableWidget->item(x, 1);
            QTableWidgetItem* item_ten = ui->tableWidget->item(x, 2);
            QString temp = item_ho->text() + " " + item_ten->text();
            dao_nguoc(x, 5, temp, ui->tableWidget);
        }

        to_mau(x, index, ui->tableWidget);
    }
    loadKetQuaTimKiem(indexes, ui->tableWidget);
    QString quantity = QString::number(indexes.length());
    ui->quantitySearchView_2->setText(quantity);
}

void MainWindow::handleTimKiemVong() {
    int index = ui->comboBoxSearch->currentIndex();
    Helper<dslk_vong::node, dslk_vong> helper;
    QString input = ui->lineEdit->text();
    QElapsedTimer timer;
    QList<int> indexes;
    bool checkDaoNguoc = ui->radioButtonTenDaoNguoYes->isChecked();

    switch(index){
    case 0:{
        QString input = ui->lineEdit->text();
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_ma(ds_vong.getFirst(),input, true);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }

    case 1:{
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_ten(ds_vong.getFirst(),input, true);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 2: {
        QString text = ui->lineEdit->text();
        bool ok;
        text.toFloat(&ok);
        if(!ok) break;
        double input = text.toDouble();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_diem(ds_vong.getFirst(),input, true);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 3:{
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_ho(ds_vong.getFirst(),input, true);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 4:
    {
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        timer.start();  // Bắt đầu đếm thời gian
        indexes = helper.tim_kiem_theo_lop(ds_vong.getFirst(),input, true);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    default:
        break;
    }
    if(indexes.size() == 0) {
        QMessageBox::information(this,"Thông tin", "Không tìm thấy");
        return;
    }
    if(checkDaoNguoc){
        ui->tableWidget->setColumnCount(6); // Ví dụ: 6 cột
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm" << "Tên đảo ngược");
    }
    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            resertTable(i, j, ui->tableWidget);
        }
    }
    if(index == 1){
        index = 2;
    }
    else if(index == 2){
        index = 4;
    }
    else if(index == 3){
        index = 1;
    }
    else if(index == 4){
        index = 3;
    }
    for(auto x : indexes){
        int columnCount = ui->tableWidget->columnCount();
        if(checkDaoNguoc){
            QTableWidgetItem* item_ho = ui->tableWidget->item(x, 1);
            QTableWidgetItem* item_ten = ui->tableWidget->item(x, 2);
            QString temp = item_ho->text() + " " + item_ten->text();
            dao_nguoc(x, 5, temp, ui->tableWidget);
        }

        to_mau(x, index, ui->tableWidget);
    }
    loadKetQuaTimKiem(indexes, ui->tableWidget);
    QString quantity = QString::number(indexes.length());
    ui->quantitySearchView_2->setText(quantity);
}

void MainWindow::loadKetQuaTimKiem(QList<int> indexes, QTableWidget* table){
    int rows = table->rowCount();
    for(int i = rows - 1; i >= 0; i--){
        if(!indexes.contains(i)){
            table->removeRow(i);
        }
    }
}

void MainWindow::handleTimKiemKep() {
    int index = ui->comboBoxSearch->currentIndex();
    QString input = ui->lineEdit->text();
    QElapsedTimer timer;
    QList<int> indexes;
    bool checkDaoNguoc = ui->radioButtonTenDaoNguoYes->isChecked();
    bool isNhiPhan = false;
    switch(index){
    case 0:{
        QString input = ui->lineEdit->text();
        SinhVien sv = SinhVien();
        sv.mssv = input;
        dslk_kep::node* des = ds_kep.create_new_node(sv);
        timer.start();  // Bắt đầu đếm thời gian

        if(searchMode == 0){
            indexes = ds_kep.binary_search(&dslk_kep::search_theo_ma, des);
            isNhiPhan = true;
        }
        else {
            Helper<dslk_kep::node, dslk_kep> helper;
            indexes = helper.tim_kiem_theo_ma(ds_kep.getFirst(), input);
        }
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }

    case 1:{
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        SinhVien sv = SinhVien();
        sv.ten = input;
        dslk_kep::node* des = ds_kep.create_new_node(sv);
        timer.start();  // Bắt đầu đếm thời gian

        if(searchMode == 1){
            indexes = ds_kep.binary_search(&dslk_kep::search_theo_ten, des);
            isNhiPhan = true;

        }
        else {
            Helper<dslk_kep::node, dslk_kep> helper;
            indexes = helper.tim_kiem_theo_ten(ds_kep.getFirst(), input);
        }
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }
    case 2: {
        QString text = ui->lineEdit->text();
        bool ok;
        text.toFloat(&ok);
        if(!ok) break;
        double input = text.toDouble();
        timer.start();  // Bắt đầu đếm thời gian
        SinhVien sv = SinhVien();
        sv.diem = input;
        dslk_kep::node* des = ds_kep.create_new_node(sv);
        QElapsedTimer timer;
        timer.start();
        if(searchMode == 2){
            indexes = ds_kep.binary_search(&dslk_kep::search_theo_diem, des);
            isNhiPhan = true;

        }
        else {
            Helper<dslk_kep::node, dslk_kep> helper;
            indexes = helper.tim_kiem_theo_diem(ds_kep.getFirst(), input);
        }
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result + (isNhiPhan ? " bằng tìm kiếm nhị phân" : " bằng tìm kiếm vét cạn"));
        break;
    }
    case 3:{
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        SinhVien sv = SinhVien();
        sv.ho = input;
        timer.start();  // Bắt đầu đếm thời gian

        Helper<dslk_kep::node, dslk_kep> helper;
        indexes = helper.tim_kiem_theo_ho(ds_kep.getFirst(), input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    case 4:
    {
        QString input = ui->lineEdit->text();
        QElapsedTimer timer;
        SinhVien sv = SinhVien();
        sv.lop = input;
        timer.start();  // Bắt đầu đếm thời gian

        Helper<dslk_kep::node, dslk_kep> helper;
        indexes = helper.tim_kiem_theo_lop(ds_kep.getFirst(), input);
        qint64 nanos = timer.nsecsElapsed();  // Thời gian đã trôi qua (ms)
        QString result;
        result = QString::number(nanos / 1'000'000.0, 'f', 3) + " ms";
        ui->timeSearchView->setText(result);
        break;
    }
    default:
        break;
    }
    if(indexes.size() == 0) {
        QMessageBox::information(this,"Thông tin", "Không tìm thấy");
        return;
    }
    if(checkDaoNguoc){
        ui->tableWidget->setColumnCount(6); // Ví dụ: 6 cột
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Mã số sinh viên" << "Họ" << "Tên" << "Lớp" << "Điểm" << "Tên đảo ngược");
    }

    int rows = ui->tableWidget->rowCount();
    int columns = ui->tableWidget->columnCount();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            resertTable(i, j, ui->tableWidget);
        }
    }
    if(index == 1){
        index = 2;
    }
    else if(index == 2){
        index = 4;
    }
    else if(index == 3){
        index = 1;
    }
    else if(index == 4){
        index = 3;
    }
    for(auto x : indexes){
        int columnCount = ui->tableWidget->columnCount();
        if(checkDaoNguoc){
            QTableWidgetItem* item_ho = ui->tableWidget->item(x, 1);
            QTableWidgetItem* item_ten = ui->tableWidget->item(x, 2);
            QString temp = item_ho->text() + " " + item_ten->text();
            dao_nguoc(x, 5, temp, ui->tableWidget);
        }

        to_mau(x, index, ui->tableWidget);
    }
    loadKetQuaTimKiem(indexes, ui->tableWidget);
    QString quantity = QString::number(indexes.length());
    ui->quantitySearchView_2->setText(quantity);
}


void MainWindow::on_searchBtn_clicked()
{
    if(!isImport){
        QMessageBox::critical(this, "Lỗi", "Vui lòng import trước khi tìm kiếm");
        return;
    }
    if(ui->lineEdit->text() == ""){
        QMessageBox::critical(this, "Lỗi", "Vui lòng nhập thông tin tìm kiếm");
        return;

    }
    switch(selectedIndex){
        case 0:
        break;
        case 1:{
            handleTimKiemArr(ds_mang);
            break;
        }
        case 2: {
            handleTimKiem(ds_don);
            ui->timeSearchView->setText(ui->timeSearchView->text() + " bằng tìm kiếm vét cạn");

            break;
        }
        case 3: {
            handleTimKiemKep();
            break;
        }
        case 4:{
            handleTimKiemVong();
            ui->timeSearchView->setText(ui->timeSearchView->text() + " bằng tìm kiếm vét cạn" );
            break;
        }
        default:
            break;
    }
    ui->huySearchBtn->setEnabled(true);
    ui->searchBtn->setEnabled(false);
    ui->comboBoxSearch->setEnabled(false);
}

void MainWindow::resert() {
    ui->huyMaxBtn->setEnabled(false);
    ui->huyMinBtn->setEnabled(false);
    ui->huySearchBtn->setEnabled(false);

}

void MainWindow::on_huySearchBtn_clicked()
{
    switch(selectedIndex){
    case 0:
        break;
    case 1:
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    case 2:
        loadToTable(ds_don, ui->tableWidget);

        break;
    case 3:
        loadToTable(ds_kep, ui->tableWidget);
        break;
    case 4:
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    default:
        break;
    }
    ui->quantitySearchView_2->setText(0);
    ui->huySearchBtn->setEnabled(false);
    ui->searchBtn->setEnabled(true);
    ui->comboBoxSearch->setEnabled(true);
}


void MainWindow::on_addBtn_clicked()
{
    if(!isImport){
        QMessageBox::critical(this, "Lỗi", "Vui lòng import trước khi thêm sinh viên");
        return;
    }
    addUi* dialog_add = new addUi(mssvSet,this);
    dialog_add->show();
}

void MainWindow::updateTable(){
    switch(selectedIndex){
    case 0:
        break;
    case 1:
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    case 2:
        loadToTable(ds_don, ui->tableWidget);
        break;
    case 3:
        loadToTable(ds_kep, ui->tableWidget);
        break;
    case 4:
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    default:
        break;
    }
    searchMode = -1;
    ui->comboBoxLopTb->clear();
    ui->lcdSoLuongSinhVien->display(ui->tableWidget->rowCount());
    QSet<QString> set = getLops(ui->tableWidget);
    QStringList sortedList = QStringList(set.begin(), set.end());
    sortedList.sort(Qt::CaseInsensitive);  // không phân biệt hoa thường (nếu cần)

    for (const QString &x : sortedList) {
        ui->comboBoxLopTb->addItem(x);
    }
}

void MainWindow::handleXoaSv(QString &mssv){
    switch(selectedIndex){
    case 0:
        break;
    case 1:
        ds_mang.xoa_sv(mssv);
        break;
    case 2:
        ds_don.xoa_sv(mssv);
        break;
    case 3:
        ds_kep.xoa_sv(mssv);
        break;
    case 4:
        ds_vong.xoa_sv(mssv);
        break;
    default:
        break;
    }
    mssvSet.remove(mssv);
}


void MainWindow::showTableContextMenu(const QPoint &pos)
{
    QTableWidgetItem* item = ui->tableWidget->itemAt(pos);

    QMenu menu(this);
    QAction* editAction = nullptr;
    QAction* deleteAction = nullptr;


    // Nếu người dùng chuột phải vào 1 dòng đã có dữ liệu thì mới cho sửa/xoá
    if (item) {
        editAction = menu.addAction("✏️ Sửa");
        deleteAction = menu.addAction("🗑️ Xoá");
    }

    QAction* selectedAction = menu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));

    if (selectedAction == editAction) {
        int row = item->row();
        QString mssv = ui->tableWidget->item(row, 0)->text();
        QString ho = ui->tableWidget->item(row, 1)->text();
        QString ten = ui->tableWidget->item(row, 2)->text();
        QString lop = ui->tableWidget->item(row, 3)->text();
        QString temp = ui->tableWidget->item(row, 4)->text();
        qreal diem = temp.toDouble();
        SinhVien sv = SinhVien(mssv, ho, ten, lop, diem);

        updateui* updateUi = new updateui(sv, mssvSet,this);
        updateUi->show();
    } else if (selectedAction == deleteAction) {
        bool reply = showYesNoMessageBox(this,"Xác nhận", "Bạn có chắc chắn xóa");
        if(reply){
            int row = item->row();
            QString mssv = ui->tableWidget->item(row, 0)->text();
            handleXoaSv(mssv);
            ui->tableWidget->removeRow(row);
            ui->lcdSoLuongSinhVien->display(ui->tableWidget->rowCount());
            ui->comboBoxLopTb->clear();
            QSet<QString> set = getLops(ui->tableWidget);
            QStringList sortedList = QStringList(set.begin(), set.end());
            sortedList.sort(Qt::CaseInsensitive);  // không phân biệt hoa thường (nếu cần)

            for (const QString &x : sortedList) {
                ui->comboBoxLopTb->addItem(x);
            }
        }
    }
}

void MainWindow::on_saveBtn_clicked()
{
    if(!isImport){
        QMessageBox::critical(this, "Lỗi", "Vui lòng import trước khi lưu");
        return;
    }
    if(ui->huyMaxBtn->isEnabled()) on_huyMinBtn_clicked();
    if(ui->huyMaxBtn->isEnabled()) on_huyMaxBtn_clicked();
    saveTableToCSV(ui->tableWidget);
}


void MainWindow::on_clearBtn_clicked()
{
    bool reply = showYesNoMessageBox(this,"Xác nhận", "Nếu chưa lưu dữ liệu, các thay đổi của bạn có thể mất. Bạn chắc chắn clear ?");
    if(!reply) return;
    switch (selectedIndex){
    case 1:
        ds_mang.clear();
        loadToTableArray(ds_mang, ui->tableWidget);
        break;
    case 2:
        ds_don.clear();
        loadToTable(ds_don, ui->tableWidget, false);
        break;
    case 3:
        ds_kep.clear();
        loadToTable(ds_kep, ui->tableWidget, false);
        break;
    case 4:
        ds_vong.clear();
        loadToTable(ds_vong, ui->tableWidget, true);
        break;
    }
    ui->clearBtn->setEnabled(false);
    mssvSet.clear();
    searchMode = -1;
    this->isImport = false;
    this->selectedIndex = 0;
    ui->lableAverageView->setText("");
    ui->comboBoxLopTb->clear();
    ui->SoLuongView->setText("");
    ui->methodBox->setCurrentIndex(0);
    ui->methodBox->setEnabled(true);
    ui->downloadBtn->setEnabled(true);
    ui->timeSearchView->setText("");
    ui->timeSortView->setText("");
    ui->lcdSoLuongSinhVien->display(0);
    ui->statusBtn->setText("✖ Not import");
    ui->statusBtn->setStyleSheet("QPushButton { color: white; background-color: red; border-radius: 8px; padding: 6px; font: bold 14px; }");
}

