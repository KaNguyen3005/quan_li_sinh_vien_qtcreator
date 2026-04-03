#include "mainwindow.h"
#include <QApplication>
#include <QList>
#include <QDebug>
#include "bits/stdc++.h"
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QSplashScreen>
using namespace std;

QList<SinhVien> danhSach = {};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Tạo ảnh splash với nền trắng và chữ tuỳ chỉnh
    QPixmap pix(800, 300);
    pix.fill(Qt::white);

    QPainter painter(&pix);
    painter.setPen(Qt::darkGreen);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(pix.rect(), Qt::AlignCenter,
                     "✨ Sản phẩm báo cáo môn học CTDL&GT của nhóm 16 ✨\n\n"
                     "👨‍💻 Thành viên: Ka, Thanh, Phương, Quỳnh\n\n"
                     "❤️ Cảm ơn vì đã lựa chọn phần mềm này.");
    painter.end();

    QSplashScreen splash(pix);
    splash.show();

    // Đợi 2 giây trước khi hiện main window
    QTimer::singleShot(2000, &splash, &QSplashScreen::close);

    MainWindow w;
    QTimer::singleShot(2000, &w, [&]() { w.show(); });


    return a.exec();
}
