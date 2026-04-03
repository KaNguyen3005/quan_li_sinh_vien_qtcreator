#include "sinhvien.h"
#include <QLocale>
#include <QTextStream>
#include "bits/stdc++.h"
using namespace std;
SinhVien::SinhVien(){
    mssv = "";
    ten = "";
    ho = "";
    lop = "";
    diem = 0;
}
SinhVien::SinhVien(const QString &mssv, const QString &ho, const QString &ten, const QString &lop , const qreal diem) : mssv(mssv), ho(ho), ten(ten), lop(lop), diem(diem){}

void SinhVien::in_thong_tin() {
    qDebug() << "MSSV:" << mssv;
    qDebug() << "Họ"  << ho;
    qDebug() << "Tên:" << ten;
    qDebug() << "Lớp"  << lop;
    qDebug() << "Điểm:" << diem;
}

QString SinhVien::ten_dao_nguoc(){
    QString temp = ho + " " + ten;
    QString result = "";
    int n = temp.length();
    for(int i = n - 1; i >= 0; i--){
        result += temp[i];
    }
    return result;
}
