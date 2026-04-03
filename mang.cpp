#include "mang.h"
#include "bits/stdc++.h"
mang::mang() {}

int mang::size(){
    return arr.size();
}

bool mang::isEmpty(){
    if (arr.size() == 0) return true;
    return false;
}

SinhVien mang::tim_vet_can(QString &mssv){
    SinhVien tmp;
    tmp.diem = -1; tmp.ho = ""; tmp.lop = ""; tmp.mssv = ""; tmp.ten = "";
    for (SinhVien x : arr){
        if (x.mssv == mssv){
            return x;
        }
    }
    return tmp;     //trả về sinh viên rỗng
}

SinhVien mang::them_sv(SinhVien &sv){
    if (tim_vet_can(sv.mssv).diem == -1){
        arr.push_back(sv);
        return sv;
    }
    return {};
}

SinhVien mang::sua_sv(QString &mssv, SinhVien &sv) {
    for(int i = 0; i < arr.size(); i++){
        if(arr[i].mssv == sv.mssv){
            arr[i] = sv;
            return arr[i];
        }
    }
    return {};
}

bool mang::xoa_sv(QString mssv){
    int idx = 0;
    for (int i = 0; i < arr.size(); i++){
        if (arr[i].mssv == mssv){
            idx = i;
            break;
        }
    }

    for (int i = idx; i < arr.size()-1; i++){
        arr[i] = arr[i+1];
    }
    arr.pop_back();
    return true;
}

mang mang::danh_sach_diem_cao(){
    qreal high = 0;
    for (SinhVien x : arr){
        high = qMax(high, x.diem);
    }
    mang ans;
    for (SinhVien x : arr){
        if (x.diem == high){
            ans.them_sv(x);
        }
    }
    return ans;
}

mang mang::danh_sach_diem_thap(){
    qreal low = 11;
    for (SinhVien x : arr){
        low = qMin(low, x.diem);
    }
    mang ans;
    for (SinhVien x : arr){
        if (x.diem == low){
            ans.them_sv(x);
        }
    }
    return ans;
}

qreal mang::tinh_tb(QString &lop){
    float sum = 0;
    int dem = 0;
    for (SinhVien x : arr){
        if(lop == x.lop){
            sum += x.diem;
            dem++;
        }
    }
    return sum/dem;
}

bool mang::cmp(int choose, SinhVien a, SinhVien b){
    if (choose == 1){
        return QString::localeAwareCompare(a.mssv.toLower(), b.mssv.toLower()) > 0;
    }
    else{
        if (choose == 2){
            return QString::localeAwareCompare(a.ten.toLower(), b.ten.toLower()) > 0;
        }
        else return a.diem > b.diem;
    }
}

void mang::bubble_sort(int choose){
    int flag;
    for (int i = 0; i < arr.size()-1; i++){
        flag = true;
        for (int j = 0; j < arr.size()-i-1; j++){
            if (cmp(choose, arr[j], arr[j+1])){
                std::swap(arr[j], arr[j+1]);
                flag = false;
            }
        }
        if(flag) return;
    }
}

void mang::selection_sort(int choose){
    for (int i = 0; i < arr.size()-1; i++){
        int idx_min = i;
        for (int j = i+1; j < arr.size(); j++){
            if (cmp(choose, arr[idx_min], arr[j])){
                idx_min = j;
            }
        }
        std::swap(arr[i], arr[idx_min]);
    }
}

void mang::insertion_sort(int choose){
    for (int i = 0; i < arr.size(); i++){
        SinhVien key = arr[i];
        int j = i-1;
        while (j >= 0 && cmp(choose, arr[j], key)){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int mang::partition(int choose, int low, int high){
    SinhVien pivot = arr[high];
    int i = low-1;
    for (int j = low; j <= high-1; j++){
        if (cmp(choose, pivot, arr[j])){
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[high]);
    return (i+1);
}

void mang::quick_sort(int choose, int low, int high){
    if (low < high){
        int pi = partition(choose, low, high);
        quick_sort(choose, low, pi-1);
        quick_sort(choose, pi+1, high);
    }
}

void mang::merge(int choose, int l, int m, int r){
    int n1 = m-l+1, n2 = r-m;
    SinhVien L[n1+1], R[n2+1];
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2){
        if (!cmp(choose, L[i], R[j])){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++; k++;
    }
}

void mang::merge_sort(int choose, int l, int r){
    if (l < r){
        int m = l+(r-l)/2;
        merge_sort(choose, l, m);
        merge_sort(choose, m+1, r);
        merge(choose, l, m, r);
    }
}

void mang::heap(int choose, int n, int i){
    int largest = i;
    int l = 2*i+1, r = 2*i+2;
    if (l < n && cmp(choose, arr[l], arr[largest])) largest = l;
    if (r < n && cmp(choose, arr[r], arr[largest])) largest = r;
    if (largest != i){
        std::swap(arr[i], arr[largest]);
        heap(choose, n, largest);
    }
}

void mang::heap_sort(int choose, int n){
    for (int i = n/2-1; i >= 0; i--){
        heap(choose, n, i);
    }
    for (int i = n-1; i > 0; i--){
        std::swap(arr[0], arr[i]);
        heap(choose, i, 0);
    }
}

QString mang::lower_case(QString s){
    return s.toLower();
}

QList<int> mang::tim_vet_can_ds_sv(int choose, QString tieu_chi){
    QList<int> ans;
    if(choose == 3){
        bool ok;
        tieu_chi.toFloat(&ok);
        if(!ok) return ans;
    }
    for (int i = 0; i < arr.size(); i++){
        if (choose == 1)    //Tìm theo mã sinh viên
            if (arr[i].mssv.startsWith(tieu_chi, Qt::CaseInsensitive)) ans.append(i);
        if (choose == 2){
            //Tìm theo tên

            if (arr[i].ten.startsWith(tieu_chi, Qt::CaseInsensitive)) ans.append(i);
        }
        if (choose == 3)    //Tìm theo điểm
            if (arr[i].diem == tieu_chi.toDouble()) ans.append(i);
        if (choose == 4)  {
            //Tìm theo họ
            if (arr[i].ho.startsWith(tieu_chi, Qt::CaseInsensitive)) ans.append(i);
        }
        if (choose == 5)    //Tìm theo lớp
            if (arr[i].lop.startsWith(tieu_chi, Qt::CaseInsensitive)) ans.append(i);
    }
    return ans;
}

int mang::search(int choose, SinhVien x, QString tieu_chi){
    if (choose == 1){
        if (x.mssv.startsWith(tieu_chi, Qt::CaseInsensitive)){
            return 0;
        }
        else{
            if (QString::localeAwareCompare(x.mssv.toLower(), tieu_chi.toLower()) > 0) return 1;
            else return -1;
        }
    }
    if (choose == 2){

        if (x.ten.startsWith(tieu_chi, Qt::CaseInsensitive)){

            return 0;
        }
        else{
            if (QString::localeAwareCompare(x.ten.toLower(), tieu_chi.toLower()) > 0) return 1;
            else return -1;
        }
    }
    if (choose == 3){
        if (qAbs(x.diem - tieu_chi.toDouble()) <= 1e-3){
            return 0;
        }
        else{
            if (x.diem > tieu_chi.toDouble()) {

                return 1;}
            else{

                return -1;
            }
        }
    }
    if (choose == 4){
        if (x.ho.startsWith(tieu_chi, Qt::CaseInsensitive)){
            return 0;
        }
        else{
            if (QString::localeAwareCompare(x.ho.toLower(), tieu_chi.toLower()) > 0) return 1;
            else return -1;
        }
    }

    if (choose == 5){
        if (x.lop.startsWith(tieu_chi, Qt::CaseInsensitive)){
            return 0;
        }
        else{
            if (QString::localeAwareCompare(x.lop.toLower(), tieu_chi.toLower()) > 0) return 1;
            else return -1;
        }
    }
}

QList<int> mang::tim_kiem_nhi_phan_ds_sv(int choose, QString tieu_chi){
    QList<int> ans;
    if(choose == 3){
        bool ok;
        tieu_chi.toFloat(&ok);
        if(!ok) return ans;
    }
    int l = 0, r = arr.size() - 1;
    int idx = 0;
    while (l <= r){
        int m = (l+r)/2;
        int res = search(choose, arr[m], tieu_chi);
        if (res == 0){
            ans.append(m);
            idx = m;
            break;
        }
        else{
            if (res == -1) l = m+1;
            if (res == 1) r = m-1;
        }
    }
    int i = idx+1;
    //Dò qua phải
    while (i < arr.size()) {
        bool match = false;
        if (choose == 1 && arr[i].mssv.startsWith(tieu_chi, Qt::CaseInsensitive)) match = true;
        if (choose == 2 && arr[i].ten.startsWith(tieu_chi, Qt::CaseInsensitive)) {
            match = true;
        }
        if (choose == 3 && arr[i].diem == tieu_chi.toDouble()) match = true;
        if (choose == 4 && arr[i].ho.startsWith(tieu_chi, Qt::CaseInsensitive)) match = true;
        if (choose == 5 && arr[i].lop.startsWith(tieu_chi, Qt::CaseInsensitive)) match = true;

        if (match) ans.append(i);
        else break;
        i++;
    }

    // Dò qua trái
    i = idx - 1;
    while (i >= 0) {
        bool match = false;
        if (choose == 1 && arr[i].mssv.startsWith(tieu_chi, Qt::CaseInsensitive)) match = true;
        if (choose == 2 && arr[i].ten.startsWith(tieu_chi, Qt::CaseInsensitive)){
            match = true;
        }
        if (choose == 3 && arr[i].diem == tieu_chi.toDouble()) match = true;
        if (choose == 4 && arr[i].ho.startsWith(tieu_chi, Qt::CaseInsensitive)) match = true;
        if (choose == 5 && arr[i].lop.startsWith(tieu_chi, Qt::CaseInsensitive)) match = true;

        if (match) ans.append(i);
        else break;
        i--;
    }
    return ans;
}

void mang::clear() {
    while(!arr.empty()){
        arr.pop_back();
    }
}
