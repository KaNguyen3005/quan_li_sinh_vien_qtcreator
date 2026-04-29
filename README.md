

https://github.com/user-attachments/assets/b3d98009-7d06-408d-8005-485e8c037b48


# Đồ án: Phần mềm Quản lý Sinh viên

## Giới thiệu
Đây là đồ án môn **Cấu trúc dữ liệu & Giải thuật (CTDL&GT)**, xây dựng ứng dụng quản lý sinh viên bằng **C++/Qt**.
Mục tiêu của đồ án là kết hợp giao diện desktop với nhiều cấu trúc dữ liệu và thuật toán kinh điển để xử lý dữ liệu sinh viên.

## Các tính năng nổi bật (gắn với CTDL&GT)
- **Quản lý hồ sơ sinh viên (CRUD):** thêm, sửa, xoá, tìm theo mã sinh viên.
- **Lưu trữ dữ liệu trên nhiều cấu trúc:**
  - Mảng động (`mang`)
  - Danh sách liên kết đơn (`dslk_don`)
  - Danh sách liên kết kép (`dslk_kep`)
  - Danh sách liên kết vòng (`dslk_vong`)
- **Sắp xếp dữ liệu theo nhiều tiêu chí** (mã SV, họ tên, lớp, điểm) với các thuật toán:
  - Bubble Sort
  - Selection Sort
  - Insertion Sort
  - Merge Sort
  - Quick Sort
  - Heap Sort
- **Tìm kiếm sinh viên:**
  - Tìm kiếm vét cạn (linear search)
  - Tìm kiếm nhị phân (binary search) trên dữ liệu phù hợp
- **Thống kê học tập:**
  - Liệt kê sinh viên điểm cao / điểm thấp
  - Tính điểm trung bình theo lớp
- **Nhập/xuất dữ liệu CSV** phục vụ lưu trữ và tái sử dụng dữ liệu.

## Cách mở và chạy bản đã build
Dự án đã có sẵn file thực thi. Người dùng chỉ cần:

1. Mở thư mục:
   `build/Desktop_Qt_6_8_2_MinGW_64_bit-Release/release/`
2. Chạy file:
   `quan_li_sinh_vien.exe`

## Lưu ý triển khai
- Giữ nguyên toàn bộ các file `.dll` và thư mục con đi kèm trong thư mục `release`.
- Khi sao chép sang máy khác, nên sao chép **cả thư mục `release`** rồi mới chạy `quan_li_sinh_vien.exe` để tránh lỗi thiếu thư viện runtime.
