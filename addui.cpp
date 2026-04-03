#include "addui.h"
#include "ui_addui.h"
#include <QMessageBox>
#include <qmenu.h>
#include "read_write.h"
#include "validate.h"
addUi::addUi(QSet<QString> &mssvSet, MainWindow *parent)
    : ui(new Ui::addUi), mssvSet(mssvSet)
{
    mainWin = parent;
    ui->setupUi(this);
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->doubleSpinBoxDiem->setMinimum(0);
    ui->doubleSpinBoxDiem->setMaximum(10);
    this->setWindowIcon(QIcon(":\\images\\icons\\icons\\add.png"));

    connect(ui->tableWidget, &QTableWidget::customContextMenuRequested,
            this, &addUi::showTableContextMenu);
}

addUi::~addUi()
{
    delete ui;
}

void addUi::insertToTable(SinhVien &sv) {
    QTableWidget* table = ui->tableWidget;
    table->insertRow(0);
    table->setItem(0, 0, new QTableWidgetItem(sv.mssv));
    table->setItem(0, 1, new QTableWidgetItem(sv.ho));
    table->setItem(0, 2, new QTableWidgetItem(sv.ten));
    table->setItem(0, 3, new QTableWidgetItem(sv.lop));
    table->setItem(0, 4, new QTableWidgetItem(QString::number(sv.diem)));
}




bool addUi::validateThemSv(SinhVien &sv,QSet<QString> &mssvSet){
    QString mssv = sv.mssv;
    QString ho = sv.ho;
    QString ten = sv.ten;
    QString lop = sv.lop;
    QStringList errors;
    validate vld;
    if (!vld.isValidString(mssv)) {
        errors << QString("Mã sinh viên chứa ký tự trắng hoặc không hợp lệ!");
    }

    if((!vld.isValidWithSpace(ho))){
        errors << QString("Họ chứa ký tự không hợp lệ hoặc dài quá 255 ký tự!");

    }
    if(!vld.isValidWithSpace(ten)){
        errors << QString("Tên chứa ký tự không hợp lệ hoặc dài quá 255 ký tự!");

    }

    if ((!vld.isValidString(lop))) {
        errors << QString("Lớp chứa ký tự trắng hoặc không hợp lệ!");
    }



    if (!check_data_null(sv)) {
        errors << QString("Thiếu thông tin bắt buộc!");
    }

    if (mssvSet.contains(mssv.toUpper())) {
        errors << QString("Trùng mã sinh viên");
    }
    if (!errors.isEmpty()) {
        QString errorText = "Đã xảy ra lỗi trong quá trình import:\n\n" + errors.join("\n");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Lỗi Import Dữ Liệu");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Import thất bại do dữ liệu không hợp lệ.");
        msgBox.setDetailedText(errorText);  // Mở rộng để xem chi tiết
        msgBox.exec();
        return false;
    } else {
        QMessageBox::information(this, "Thành công", "Thêm sinh viên thành công!");        
        sv.ho= vld.deleteMiddleSpace(ho);
        sv.ten = vld.deleteMiddleSpace(ten);
        sv.ho = vld.capitalizeWords(ho);
        sv.ten = vld.capitalizeWords(ten);
        sv.lop = sv.lop.toUpper();
        sv.mssv = sv.mssv.toUpper();
        return true;
    }
}

void addUi::on_pushButtonAdd_clicked()
{
    QString mssv = ui->lineEditMssv->text().trimmed();
    QString ho = ui->lineEditHo->text().trimmed();
    QString ten = ui->lineEditTen->text().trimmed();
    QString lop = ui->lineEditLop->text().trimmed();
    qreal diem = ui->doubleSpinBoxDiem->value();
    SinhVien sv = SinhVien(mssv, ho, ten, lop, diem);
    bool validateCheck = validateThemSv(sv, mssvSet);
    if(!validateCheck) return;
    mssvSet.insert(sv.mssv);
    list.append(sv);
    insertToTable(sv);
    ui->lineEditMssv->setText("");
    ui->lineEditHo->setText("");
    ui->lineEditTen->setText("");
    ui->lineEditLop->setText("");
    ui->doubleSpinBoxDiem->setValue(0);

}


void addUi::on_pushButtonCancel_clicked()
{
    this->close();
}


void addUi::on_pushButtonSave_clicked()
{
    int ret = QMessageBox::question(
        this,
        "Xác nhận",
        "Bạn có chắc chắn muốn thêm sinh viên không?",
        QMessageBox::Yes | QMessageBox::No
        );
    if(ret == QMessageBox::No) return;

    switch(mainWin->selectedIndex){
    case 0:

        break;
    case 1:{

        for(int i = 0; i < list.size(); i++){
            mainWin->ds_mang.them_sv(list[i]);
            mainWin->mssvSet.insert(list[i].mssv);
        }
        break;
    }
    case 2:
        for(int i = 0; i < list.size(); i++){
            mainWin->ds_don.them_sv(list[i]);
            mainWin->mssvSet.insert(list[i].mssv);

        }
        break;
    case 3:
        for(int i = 0; i < list.size(); i++){
            mainWin->ds_kep.them_sv(list[i]);
            mainWin->mssvSet.insert(list[i].mssv);

        }
        break;
    case 4:
        for(int i = 0; i < list.size(); i++){
            mainWin->ds_vong.them_sv(list[i]);
            mainWin->mssvSet.insert(list[i].mssv);

        }
        break;
    default:
        break;
    }
    qDebug() << "save" << mainWin->mssvSet.size();
    mainWin->updateTable();
    this->close();

}

void addUi::handleXoaSv(QString &mssv){
    for(int i = 0; i < list.size(); i++){
        if(list[i].mssv == mssv){
            list.removeAt(i);
            mssvSet.remove(mssv);
            return;
        }
    }
}

void addUi::showTableContextMenu(const QPoint &pos)
{
    qDebug() << 1;
    QTableWidgetItem* item = ui->tableWidget->itemAt(pos);

    QMenu menu(this);
    QAction* deleteAction;


    // Nếu người dùng chuột phải vào 1 dòng đã có dữ liệu thì mới cho sửa/xoá
    if (item) {
        deleteAction = menu.addAction("🗑️ Xoá");
    }

    QAction* selectedAction = menu.exec(ui->tableWidget->viewport()->mapToGlobal(pos));

    if (selectedAction == deleteAction) {
        int row = item->row();
        QString mssv = ui->tableWidget->item(row, 0)->text();
        handleXoaSv(mssv);
        ui->tableWidget->removeRow(row);
    }
}

