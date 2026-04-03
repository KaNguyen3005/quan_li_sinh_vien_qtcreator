#include <cstdlib>
#include <QString>
#include <sinhvien.h>
#include <QChar>
#include <QIODevice>
#include <QFile>
#include "read_write.h"
#include "DanhSach.h"
#include "dslk_don.h"
#include <QTableWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <validate.h>
// #include "dslk_vong.h"
// #include "dslk_kep.h"
using namespace std;



SinhVien process_substring(const QString& s) {
    SinhVien x;

    QStringList parts = s.split(';');

    QString msv = parts.value(0).trimmed();
    QString ho = parts.value(1).trimmed();
    QString ten = parts.value(2).trimmed();
    QString lop = parts.value(3).trimmed();
    QString diemStr = parts.value(4).trimmed();

    diemStr.replace(",", ".");  // đổi dấu phẩy thành chấm (nếu có)
    validate vld;
    x.setMssv(msv.toUpper());
    x.setHo(vld.capitalizeWords(vld.deleteMiddleSpace(ho)));
    x.setTen(vld.capitalizeWords(vld.deleteMiddleSpace(ten)));
    x.setLop(lop.toUpper());
    bool ok;
    qreal diem = diemStr.toDouble(&ok);
    diem = ok ? diem : -1.0;
    x.setDiem(diem);
    return x;
}

bool check_msv(QString msv){
    for (QChar c : msv){
        if (c == ' ' || c == ';' || c == ',') return false;
    }
    return true;
}

bool check_lop(QString lop){
    for (QChar c : lop){
        if (c == ' ' || c == ';' || c == ',') return false;
    }
    return true;
}

bool check_data_null(SinhVien x){
    if (x.getDiem() < 0 || x.getHo().length() == 0 || x.getLop().length() == 0 || x.getMssv().length() == 0 || x.getTen().length() == 0)
        return false;
    return true;
}

bool check_diem(int diem){
    return diem >= 0 && diem <= 10;
}

template<typename ListType>
QStringList loadDuLieu(const QString& filePath, ListType& danhSach, QSet<QString> &mssvSet) {
    QStringList errors;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors << "Không thể mở file: " + file.errorString();
        return errors;
    }

    QTextStream in(&file);
    int lineNumber = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineNumber++;

        if (lineNumber == 1) continue; // Bỏ dòng tiêu đề
        if (line.isEmpty()) continue;

        SinhVien sv = process_substring(line);
        bool hasError = false;
        QStringList parts = line.split(';');
        if(parts.size() != 5){
            errors << QString("Dòng %1: Lỗi số lượng phần tử không hợp lệ!").arg(lineNumber);
            hasError = true;
            continue;
        }
        if (!check_msv(sv.getMssv())) {
            errors << QString("Dòng %1: Mã sinh viên chứa ký tự trắng hoặc không hợp lệ!").arg(lineNumber);
            hasError = true;
        }

        if (!check_lop(sv.getLop())) {
            errors << QString("Dòng %1: Lớp chứa ký tự trắng hoặc không hợp lệ!").arg(lineNumber);
            hasError = true;
        }

        if (!check_data_null(sv)) {
            errors << QString("Dòng %1: Thiếu thông tin bắt buộc!").arg(lineNumber);
            hasError = true;
        }

        if(!check_diem(sv.diem)) {
            qDebug() << "Điểm" << sv.diem;
            errors << QString("Dòng %1: Điểm không hợp lệ!").arg(lineNumber);
            hasError = true;
        }
        if (mssvSet.contains(sv.getMssv())) {
            errors << QString("Dòng %1: Trùng mã sinh viên: %2").arg(lineNumber).arg(sv.getMssv());
            hasError = true;
        }

        if (!hasError) {
            mssvSet.insert(sv.getMssv());
            danhSach.them_sv(sv);
            qDebug() << "đã thêm ";
        }

    }

    return errors;
}


void saveTableToCSV(QTableWidget *table)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Lưu file CSV", "", "CSV files (*.csv)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file để ghi!");
        return;
    }

    QTextStream out(&file);

    // Ghi dòng tiêu đề (header)
    for (int col = 0; col < 5; ++col) {
        out << table->horizontalHeaderItem(col)->text();
        if (col < table->columnCount() - 1)
            out << ";";
    }
    out << "\n";

    // Ghi từng dòng dữ liệu
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < 5; ++col) {
            QTableWidgetItem *item = table->item(row, col);
            out << (item ? item->text() : "");
            if (col < table->columnCount() - 1)
                out << ";";
        }
        out << "\n";
    }

    file.close();
    QMessageBox::information(nullptr, "Hoàn tất", "Dữ liệu đã được lưu vào file CSV.");
}
