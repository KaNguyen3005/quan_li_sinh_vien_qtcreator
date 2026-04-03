#include "dslk_vong.h"


dslk_vong::dslk_vong(){
    last = nullptr;
}

bool dslk_vong::isEmpty(){
    if (last == nullptr) return true;
    return false;
}

dslk_vong::node* dslk_vong::tim_vet_can(QString &msv){
    if (last == nullptr) return nullptr;
    node* p = last->next;
    while (p != last){
        if (p->sv.mssv == msv) return p;
        p = p->next;
    }
    if (p->sv.mssv == msv) return p;
    return nullptr;
}

dslk_vong::node* dslk_vong::create_new_node(SinhVien &sv){
    dslk_vong::node* tmp = new dslk_vong::node();
    tmp->sv.diem = sv.diem;
    tmp->sv.ho = sv.ho;
    tmp->sv.lop = sv.lop;
    tmp->sv.mssv = sv.mssv;
    tmp->sv.ten = sv.ten;
    tmp->next = nullptr;
    return tmp;
}

dslk_vong::node* dslk_vong::them_sv(SinhVien &sv){
    if (tim_vet_can(sv.mssv) != nullptr){
        return {};
    }
    dslk_vong::node* p = create_new_node(sv);
    if (isEmpty()){
        last = p;
        last->next = last;
        return {};
    }
    p->next = last->next;
    last->next = p;
    last = p;
    return last;
}

dslk_vong::node* dslk_vong::sua_sv(QString &mssv, SinhVien &sv){
    dslk_vong::node* p = last->next;
    if (tim_vet_can(mssv) == nullptr){
        return {};
    }

    p = last->next;
    while (p->sv.mssv != mssv){
        p = p->next;
    }
    p->sv.ho = sv.ho;
    p->sv.ten = sv.ten;
    p->sv.lop = sv.lop;
    p->sv.diem = sv.diem;
    return p;
}

bool dslk_vong::xoa_sv(QString &msv){
    if (tim_vet_can(msv) == nullptr){
        return false;
    }

    dslk_vong::node* p = last;
    while (p->next->sv.mssv != msv){
        p = p->next;
        if (p->next == last) break;
    }
    if (last->sv.mssv == msv){
        p->next = last->next;
        delete(last);
        last = p;
        return true;
    }
    dslk_vong::node* tmp = p->next;
    p->next = tmp->next;
    delete(tmp);
    return true;
}

dslk_vong dslk_vong::liet_ke_diem_thap(){
    dslk_vong::node* p = last->next;
    dslk_vong ve;
    float MIN = 100;
    while (p != last){
        MIN = qMin(MIN, p->sv.diem);
        p = p->next;
    }
    MIN = qMin(MIN, p->sv.diem);
    p = last->next;
    while (p != last){
        if (p->sv.diem == MIN) ve.them_sv(p->sv);
        p = p->next;
    }
    if (p->sv.diem == MIN) ve.them_sv(p->sv);
    return ve;
}

dslk_vong dslk_vong::liet_ke_diem_cao(){
    dslk_vong::node* p = last->next;
    dslk_vong ve;
    float MAX = -1;
    while (p != last){
        MAX = qMax(MAX, p->sv.diem);
        p = p->next;
    }
    MAX = qMax(MAX, p->sv.diem);
    p = last->next;
    while (p != last){
        if (p->sv.diem == MAX) ve.them_sv(p->sv);
        p = p->next;
    }
    if (p->sv.diem == MAX) ve.them_sv(p->sv);
    return ve;
}

qreal dslk_vong::tinh_tb(QString& lop){
    float avg = 0;
    int cnt = 1;
    dslk_vong::node* p = last->next;
    while (p != last){
        if(p->sv.lop == lop){
        avg += p->sv.diem;
        cnt++;
        }

        p = p->next;
    }
    if(p->sv.lop == lop) avg += p->sv.diem;
    return avg/cnt;
}
dslk_vong::node* nullNode = new dslk_vong::node();

dslk_vong::node*& dslk_vong::getFirst(){
    if(last == nullptr) return nullNode;
    return last->next;
}


void dslk_vong::clear() {
    if (last == nullptr) return; // Danh sách rỗng

    node* temp = last->next; // Bắt đầu từ node đầu
    node* p;

    while (temp != last) {
        p = temp;
        temp = temp->next;
        qDebug() << p->sv.getMssv();
        delete p;
    }

    // Cuối cùng xóa node cuối (last)
    qDebug() << last->sv.getMssv();
    delete last;
    last = nullptr;
    first = nullptr;
}
