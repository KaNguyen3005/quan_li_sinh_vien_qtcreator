#include "validate.h"

validate::validate() {}


bool validate::isValidWithSpace(QString &str) {
    if (str.length() > 255) return false;  // Giới hạn độ dài tối đa
    if (str.isEmpty()) return true; // Cho phép chuỗi rỗng

    // Cho phép: chữ cái Unicode, số, và dấu cách
    QRegularExpression regex("^[\\p{L}\\d ]+$");
    return regex.match(str).hasMatch();
}

bool validate::isValidString(QString &str) {
    // Regex này KHÔNG cho phép ký tự đặc biệt, chỉ cho:
    // - chữ cái (kể cả tiếng Việt)
    // - số từ 0-9
    // - viết liền không dấu cách
    if (str.length() > 255) return false;
    if (str.isEmpty()) return true; // Cho phép chuỗi rỗng


    // Cho phép: chữ cái Unicode, số, dấu gạch ngang
    // KHÔNG cho khoảng trắng hoặc ký tự đặc biệt khác
    QRegularExpression regex("^[\\p{L}\\d-]+$");
    return regex.match(str).hasMatch();
}


QString validate::deleteMiddleSpace(QString &str){
    str.replace(QRegularExpression("\\s+"), " ");
    return str;
};

QString validate::capitalizeWords(const QString& input) {
    QStringList words = input.split(' ', Qt::SkipEmptyParts);
    for (int i = 0; i < words.size(); ++i) {
        if (!words[i].isEmpty()) {
            words[i][0] = words[i][0].toUpper();
            for (int j = 1; j < words[i].size(); ++j) {
                words[i][j] = words[i][j].toLower();
            }
        }
    }
    return words.join(' ');
}

