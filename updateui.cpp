#include "updateui.h"
#include "ui_updateui.h"
#include "read_write.h"
#include <QMessageBox>
#include "validate.h"
updateui::updateui(SinhVien &sv, QSet<QString> &mssvSet, MainWindow *parent)
    : mainWin(parent)
    , ui(new Ui::updateui), sv(sv), mssvSet(mssvSet)
{
    ui->setupUi(this);

    ui->lineEditMssv->setText(sv.mssv);
    ui->lineEditHo->setText(sv.ho);
    ui->lineEditTen->setText(sv.ten);
    ui->lineEditLop->setText(sv.lop);
    ui->doubleSpinBoxDiem->setValue(sv.diem);
    ui->doubleSpinBoxDiem->setMinimum(0);
    ui->doubleSpinBoxDiem->setMaximum(10);
    this->setWindowIcon(QIcon(":\\images\\icons\\update.png"));

}

updateui::~updateui()
{
    delete ui;
}

void updateui::on_pushButtonCancel_clicked()
{
    this->close();
}



void updateui::on_pushButtonSave_clicked()
{
    QString mssv = ui->lineEditMssv->text().trimmed();
    QString ho = ui->lineEditHo->text().trimmed();
    QString ten = ui->lineEditTen->text().trimmed();
    QString lop = ui->lineEditLop->text().trimmed();
    qreal diem = ui->doubleSpinBoxDiem->value();
    SinhVien newSv = SinhVien(mssv, ho, ten, lop, diem);
    qDebug() << "Lớp" << lop;
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

    if (!vld.isValidString(lop)) {
        errors << QString("Lớp chứa ký tự trắng hoặc không hợp lệ!");
    }

    if (!check_data_null(newSv)) {
        errors << QString("Thiếu thông tin bắt buộc!");
    }
    if (!errors.isEmpty()) {
        QString errorText = "Đã xảy ra lỗi trong quá trình sửa:\n\n" + errors.join("\n");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Lỗi sửa dữ liệu");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Sửa thất bại do dữ liệu không hợp lệ.");
        msgBox.setDetailedText(errorText);  // Mở rộng để xem chi tiết
        msgBox.exec();
        return;
    } else {
        QMessageBox::information(this, "Thành công", "Sửa sinh viên thành công!");

    }
    qDebug() << "Lớp 2 : " << lop;
    newSv.ten = vld.capitalizeWords(vld.deleteMiddleSpace(ten));
    newSv.ho = vld.capitalizeWords(vld.deleteMiddleSpace(ho));
    newSv.lop = lop.toUpper();
    newSv.mssv = mssv.toUpper();
    newSv.in_thong_tin();
    switch(mainWin->selectedIndex){
    case 0:
        break;
    case 1:
        mainWin->ds_mang.sua_sv(mssv, newSv);
        break;
    case 2:
        mainWin->ds_don.sua_sv(mssv, newSv);
        break;
    case 3:
        mainWin->ds_kep.sua_sv(mssv, newSv);
        break;
    case 4:
        mainWin->ds_vong.sua_sv(mssv, newSv);
        break;
    default:
        break;
    }
    if(mssv != newSv.mssv){
        mssvSet.remove(mssv);
        mssvSet.insert(newSv.mssv);
    }
    mainWin->updateTable();
    this->close();
}

