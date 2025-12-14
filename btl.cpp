#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include <limits>


using namespace std;

// ==================== ENUMS ====================
enum class VaiTro { BanDoc, ThuThu, QuanTriVien }; 

string vaiTroToString(VaiTro v) {
    switch (v) {
        case VaiTro::QuanTriVien: return "Quản trị viên";
        case VaiTro::ThuThu: return "Thủ thư";
        case VaiTro::BanDoc: return "Bạn đọc";
        default: return "Không xác định";
    }
}

enum class TinhTrangMuon { DangMuon, DaTra, QuaHan };

string tinhTrangMuonToString(TinhTrangMuon t) {
    switch (t) {
        case TinhTrangMuon::DangMuon: return "Đang mượn"; //0
        case TinhTrangMuon::DaTra: return "Đã trả"; //1
        case TinhTrangMuon::QuaHan: return "Quá hạn"; //2
        default: return "Không xác định";
    }
}

// ==================== CLASS SACH ====================
class Sach {
public:
    int maSach;
    string ISBN;
    string tenSach;
    string tacGia;
    string nhaXuatBan;
    int namXuatBan;
    string keSach;
    int soLuong; 

    Sach() : maSach(0), namXuatBan(0), soLuong(0) {}
    Sach(int ma, string isbn, string ten, string tacgia, string nxb, int nam, string ke, int sl)
        : maSach(ma), ISBN(isbn), tenSach(ten), tacGia(tacgia), nhaXuatBan(nxb), namXuatBan(nam),
            keSach(ke), soLuong(sl) {}

    void inThongTin() const {
        cout << maSach << ", " 
             << ISBN << ", " 
             << tenSach << ", " 
             << tacGia << ", " 
             << nhaXuatBan << ", " 
             << namXuatBan << ", " 
             << keSach << ", " 
             << soLuong << '\n';
    }
};

// ==================== CLASS NGUOI DUNG ====================
class NguoiDung {
public:
    int maNguoiDung;
    string tenDangNhap;
    string matKhau;
    string hoTen;
    string email;
    VaiTro vaiTro;

    NguoiDung() : maNguoiDung(0), vaiTro(VaiTro::BanDoc) {}
    NguoiDung(int ma, string ten, string mk, string hoten, string mail, VaiTro vt)
        : maNguoiDung(ma), tenDangNhap(ten), matKhau(mk), hoTen(hoten), email(mail), vaiTro(vt) {}

    void inThongTin() const {
        cout << "[" << maNguoiDung << "] " << hoTen << " (" << tenDangNhap << ") - Vai trò: " << vaiTroToString(vaiTro) << endl;
    }
};

// ==================== CLASS PHIEU MUON ====================
class PhieuMuon {
public:
    int maPhieu;
    int maSach;
    int maNguoiDung;
    time_t ngayMuon;
    time_t hanTra;
    time_t ngayTra;
    TinhTrangMuon tinhTrang;

    PhieuMuon() : maPhieu(0), maSach(0), maNguoiDung(0), ngayMuon(0), hanTra(0), ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}
    PhieuMuon(int maPhieu, int maSach, int maNguoiDung, time_t muon, time_t han)
        : maPhieu(maPhieu), maSach(maSach), maNguoiDung(maNguoiDung), ngayMuon(muon), hanTra(han),
          ngayTra(0), tinhTrang(TinhTrangMuon::DangMuon) {}

    void inThongTin() const { 
        cout << "Mã phiếu: " << maPhieu
             << ", Mã sách: " << maSach
             << ", Mã người dùng: " << maNguoiDung
             << ", Ngày mượn: " << ctime(&ngayMuon)
             << "Hạn trả: " << ctime(&hanTra)
             << "Tình trạng: " << tinhTrangMuonToString(tinhTrang)
             << endl;
        if (tinhTrang == TinhTrangMuon::DaTra) {
            cout << "Ngày trả: " << ctime(&ngayTra) << endl;
        } else {
             cout << endl; 
        }
    }
};

string chuThuong(const string& s) {
    string thuong = s;
    transform(thuong.begin(), thuong.end(), thuong.begin(), ::tolower);
    return thuong;
}
// ==================== CLASS THU VIEN ====================
class ThuVien {
private:
    vector<Sach> danhSachSach;
    int maSachCuoi = 0;

public:
    void themSach(const Sach& sach) {
        Sach moi = sach;
        moi.maSach = ++maSachCuoi;
        for (auto& s : danhSachSach) {
            if (s.ISBN == moi.ISBN) {
                cout << "Đã tồn tại sách với ISBN \"" << moi.ISBN << "\" trong thư viện. Vui lòng kiểm tra lại.\n";
                return;
            }
        }
        danhSachSach.push_back(moi);
        cout << "Đã thêm sách với mã " << moi.maSach << endl;

    }

    bool suaSach(int ma, const Sach& capNhat) {
        for (auto& s : danhSachSach) {
            if (s.maSach != ma && s.ISBN == capNhat.ISBN) {
                cout << "Sách với ISBN \"" << capNhat.ISBN << "\" đã tồn tại trong thư viện. Vui lòng kiểm tra lại.\n";
                return false;
            }
        }
        for (auto& s : danhSachSach) {
            if (s.maSach == ma) {
                s.ISBN = capNhat.ISBN;
                s.tenSach = capNhat.tenSach;
                s.tacGia = capNhat.tacGia;
                s.nhaXuatBan = capNhat.nhaXuatBan;
                s.namXuatBan = capNhat.namXuatBan;
                s.keSach = capNhat.keSach;
                s.soLuong = capNhat.soLuong; 
                cout << "Đã cập nhật sách mã " << ma << "." << endl;
                return true;
            }
        }
        cout << "Không tìm thấy sách mã " << ma << "." << endl;
        return false;
    }

    bool xoaSach(int ma) {
        auto it = remove_if(danhSachSach.begin(), danhSachSach.end(),
                            [ma](const Sach& s) { return s.maSach == ma; });
        if (it != danhSachSach.end()) {
            danhSachSach.erase(it, danhSachSach.end());
            cout << "Đã xoá sách mã " << ma << "." << endl;
            return true;
        }
        cout << "Không tìm thấy sách mã " << ma << "." << endl;
        return false;
    }

    vector<Sach> timKiemSach(const string& tuKhoa) {
        vector<Sach> ketQua;
        string tuKhoaThuong = chuThuong(tuKhoa);
        for (const auto& s : danhSachSach) {
            string tongHop = s.ISBN + " " + s.tenSach + " " + s.tacGia + " " + s.nhaXuatBan;
            string tongHopThuong = chuThuong(tongHop);

            if (tongHopThuong.find(tuKhoaThuong) != string::npos) {
                ketQua.push_back(s);
            }
        }
        return ketQua;
    }

    void inDanhSachSach() {
        cout << "----- Danh sách sách (" << danhSachSach.size() << " cuốn) -----" << endl;
        if (danhSachSach.empty()) {
            cout << "Không có sách nào trong thư viện." << endl;
            return;
        }
        cout << "ID, ISBN, Tên Sách, Tác giả, NXB, Năm, Kệ sách, Số Lượng\n";
        for (const auto& s : danhSachSach) {
            s.inThongTin();
        }
    }

    void luuVaoTep(const string& tenTep) {
        ofstream fout(tenTep);
        if (!fout) {
            cout << "Lỗi khi mở tệp để lưu sách." << endl;
            return;
        }
        for (const auto& s : danhSachSach) {
            fout << s.maSach << "|" << s.ISBN << "|" << s.tenSach << "|" << s.tacGia << "|" << s.nhaXuatBan << "|"
                 << s.namXuatBan << "|" << s.keSach << "|" << s.soLuong << "\n";
        }
        fout.close();
        cout << "Đã lưu sách vào tệp " << tenTep << endl;
    }

    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Không có tệp để tải sách." << endl;
            return;
        }
        danhSachSach.clear();
        string dong;
        while (getline(fin, dong)) {
            Sach s;
            size_t pos = 0, truoc = 0;
            vector<string> truong;
            while ((pos = dong.find('|', truoc)) != string::npos) {
                truong.push_back(dong.substr(truoc, pos - truoc));
                truoc = pos + 1;
            }
            truong.push_back(dong.substr(truoc)); 

             if (truong.size() != 8) {
                cout << "Lỗi định dạng tệp sách: " << dong << " (out of range)\n";
                continue; 
            }

            if (truong.size() == 8) {
                s.maSach = stoi(truong[0]);
                s.ISBN = truong[1];
                s.tenSach = truong[2];
                s.tacGia = truong[3];
                s.nhaXuatBan = truong[4];
                s.namXuatBan = stoi(truong[5]);
                s.keSach = truong[6];
                s.soLuong = stoi(truong[7]);

                danhSachSach.push_back(s);
                if (s.maSach > maSachCuoi) {
                    maSachCuoi = s.maSach; 
                }
            }
        } 
        fin.close();
        cout << "Đã tải sách từ tệp " << tenTep << endl;
    }

    Sach* laySachTheoMa(int ma) {
        for (auto& s : danhSachSach) {
            if (s.maSach == ma) {
                return &s;
            }
        }
        return nullptr;
    }
};

// ==================== QUAN LI NGUOI DUNG ====================
class QuanLyNguoiDung {
private:
    vector<NguoiDung> danhSachNguoiDung;
    int idCuoi = 0;

public:
    void themNguoiDung(const NguoiDung& nguoiDung) {
        NguoiDung nguoiMoi = nguoiDung;
        nguoiMoi.maNguoiDung = ++idCuoi;
        for (auto& u : danhSachNguoiDung) {
            if (chuThuong(u.tenDangNhap) == chuThuong(nguoiMoi.tenDangNhap) || chuThuong(u.email) == chuThuong(nguoiMoi.email)) {
                cout << "Tên đăng nhập hoặc email đã tồn tại.\n";
                return;
            }
        }
        danhSachNguoiDung.push_back(nguoiMoi);
        cout << "Đã thêm người dùng với ID " << nguoiMoi.maNguoiDung << endl;
    }

    bool suaNguoiDung(int id, const NguoiDung& nguoiCapNhat) {
        for (auto& u : danhSachNguoiDung) {
            if (u.maNguoiDung != id && (chuThuong(u.tenDangNhap) == chuThuong(nguoiCapNhat.tenDangNhap) || chuThuong(u.email) == chuThuong(nguoiCapNhat.email))) {
                cout << "Tên đăng nhập hoặc email đã tồn tại.\n";
                return false;
            }
            
            if (u.maNguoiDung == id) {
                u.tenDangNhap = nguoiCapNhat.tenDangNhap;
                u.matKhau = nguoiCapNhat.matKhau;
                u.hoTen = nguoiCapNhat.hoTen;
                u.email = nguoiCapNhat.email;
                u.vaiTro = nguoiCapNhat.vaiTro;
            cout << "Đã cập nhật người dùng có ID " << id << "." << endl;
            return true;
            }
        }
        cout << "Không tìm thấy người dùng có ID " << id << "." << endl;
        return false;
    }

    bool xoaNguoiDung(int id) {
        auto it = remove_if(danhSachNguoiDung.begin(), danhSachNguoiDung.end(),
                            [id](const NguoiDung& u) { return u.maNguoiDung == id; });
        if (it != danhSachNguoiDung.end()) {
            danhSachNguoiDung.erase(it, danhSachNguoiDung.end());
            cout << "Đã xoá người dùng có ID " << id << "." << endl;
            return true;
        }
        cout << "Không tìm thấy người dùng có ID " << id << "." << endl;
        return false;
    }

    vector<NguoiDung> timKiemNguoiDung(const string& tuKhoa) {
        vector<NguoiDung> ketQua;
        string tuKhoaThuong = tuKhoa;
        transform(tuKhoaThuong.begin(), tuKhoaThuong.end(), tuKhoaThuong.begin(), ::tolower);

        for (const auto& u : danhSachNguoiDung) {
            string ketHop = u.tenDangNhap + " " + u.hoTen + " " + u.email;
            string ketHopThuong = ketHop;
            transform(ketHopThuong.begin(), ketHopThuong.end(), ketHopThuong.begin(), ::tolower);

            if (ketHopThuong.find(tuKhoaThuong) != string::npos) {
                ketQua.push_back(u);
            }
        }
        return ketQua;
    }

    void inTatCaNguoiDung() {
        cout << "----- Danh sách người dùng (" << danhSachNguoiDung.size() << " người) -----" << endl;
        if (danhSachNguoiDung.empty()) {
            cout << "Không có người dùng nào trong hệ thống." << endl;
            return;
        }
        for (const auto& u : danhSachNguoiDung) {
            u.inThongTin();
        }
    }

    void luuVaoTep(const string& tenTep) {
        ofstream fout(tenTep);
        if (!fout) {
            cout << "Lỗi khi mở tệp để lưu người dùng." << endl;
            return;
        }
        for (const auto& u : danhSachNguoiDung) {
            fout << u.maNguoiDung << "|" << u.tenDangNhap << "|" << u.matKhau << "|" << u.hoTen << "|"
                 << u.email << "|" << (int)u.vaiTro << "\n";
        }
        fout.close();
        cout << "Đã lưu người dùng vào tệp " << tenTep << endl;
    }

    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Không có tệp nào để tải người dùng." << endl;
            return;
        }
        danhSachNguoiDung.clear();
        string dong;
        while (getline(fin, dong)) {
            NguoiDung u;
            size_t viTri = 0, truoc = 0;
            vector<string> truong;
            while ((viTri = dong.find('|', truoc)) != string::npos) {
                truong.push_back(dong.substr(truoc, viTri - truoc));
                truoc = viTri + 1;
            }
            truong.push_back(dong.substr(truoc));

            if (truong.size() != 6) {
                cout << "Lỗi định dạng tệp người dùng: " << dong << " (out of range)\n";
                continue; 
            }

            if (truong.size() == 6) {
                u.maNguoiDung = stoi(truong[0]);
                u.tenDangNhap = truong[1];
                u.matKhau = truong[2];
                u.hoTen = truong[3];
                u.email = truong[4];
                u.vaiTro = static_cast<VaiTro>(stoi(truong[5]));

                danhSachNguoiDung.push_back(u);
                if (u.maNguoiDung > idCuoi) {
                    idCuoi = u.maNguoiDung; 
                }
            }
        }
        fin.close();
        cout << "Đã tải người dùng từ tệp " << tenTep << endl;
    }

    NguoiDung* layNguoiDungTheoMa(int ma) {
        for (auto& u : danhSachNguoiDung) {
            if (u.maNguoiDung == ma) {
                return &u;
            }
        }
        return nullptr;
    }

    NguoiDung* dangNhap(const string& tenDangNhap, const string& matKhau) {
        for (auto& u : danhSachNguoiDung) {
            if ((chuThuong(u.tenDangNhap) == chuThuong(tenDangNhap) || chuThuong(u.email) == chuThuong(tenDangNhap)) && u.matKhau == matKhau) {
                return &u;
            }
        }
        return nullptr;
    }
};

// ==================== QUAN LY MUON TRA ====================
class QuanLyMuon {
private:
    vector<PhieuMuon> danhSachPhieuMuon;
    int maPhieuCuoi = 0;
    ThuVien& thuVien; 
    QuanLyNguoiDung& quanLyNguoiDung; 

public:
    QuanLyMuon(ThuVien& tv, QuanLyNguoiDung& qlnd) : thuVien(tv), quanLyNguoiDung(qlnd) {}

    void muonSach(int maNguoiDung, int maSach) {
        Sach* sach = thuVien.laySachTheoMa(maSach);
        NguoiDung* nguoiDung = quanLyNguoiDung.layNguoiDungTheoMa(maNguoiDung);

        if (!sach) {
            cout << "Không tìm thấy sách với mã " << maSach << endl;
            return;
        }
        if (!nguoiDung) {
            cout << "Không tìm thấy người dùng với mã " << maNguoiDung << endl;
            return;
        }
        if (!sach->soLuong) {
            cout << "Sách \"" << sach->tenSach << "\" hiện đang hết." << endl;
            return;
        }
        for (auto& pm : danhSachPhieuMuon) {
            if (pm.maNguoiDung == maNguoiDung && (pm.maSach == maSach && pm.tinhTrang == TinhTrangMuon::DangMuon || pm.tinhTrang == TinhTrangMuon::QuaHan)) {
                cout << "Bạn đã mượn sách \"" << sach->tenSach << "\". Bạn chỉ được phép mượn 1 cuốn sách cùng một lúc.\n"; 
                cout << "Phiếu mượn hiện tại: #" << pm.maPhieu << endl;      
                return;
            }
        }

        time_t ngayMuon = time(0);
        time_t hanTra = ngayMuon + (14 * 24 * 60 * 60); // 14 ngày

        PhieuMuon phieuMoi(++maPhieuCuoi, maSach, maNguoiDung, ngayMuon, hanTra);
        danhSachPhieuMuon.push_back(phieuMoi);

        sach->soLuong--; 

        cout << "Đã tạo phiếu mượn #" << phieuMoi.maPhieu << " cho sách \"" << sach->tenSach
             << "\" cho \"" << nguoiDung->hoTen << "\"." << endl;
    }
    void traSach(int maPhieu, const NguoiDung* nguoiDungHienTai) {
        PhieuMuon* phieu = nullptr;
        for (auto& pm : danhSachPhieuMuon) {
            if (pm.maPhieu == maPhieu && (pm.tinhTrang == TinhTrangMuon::DangMuon || pm.tinhTrang == TinhTrangMuon::QuaHan)) {
                phieu = &pm;
                break;
            }
        }
        if (!phieu) {
            cout << "Không tìm thấy phiếu mượn với mã " << maPhieu << "." << endl;
            return;
        }
        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc && phieu->maNguoiDung != nguoiDungHienTai->maNguoiDung) {
            cout << "Bạn không mượn sách này." << endl;
            return;
        }
        Sach* sach = thuVien.laySachTheoMa(phieu->maSach);
        if (sach) {
            sach->soLuong++;
        }
        phieu->ngayTra = time(0);
        phieu->tinhTrang = TinhTrangMuon::DaTra;
        cout << "Đã cập nhật phiếu mượn #" << maPhieu << " là 'Đã trả'." << endl;
    }

    vector<PhieuMuon> layLichSuMuonTheoNguoiDung(int maNguoiDung) {
        vector<PhieuMuon> lichSu;
        for (auto& pm : danhSachPhieuMuon) {
            if (pm.maNguoiDung == maNguoiDung) {
                if (pm.tinhTrang == TinhTrangMuon::DangMuon && pm.hanTra < time(0)) {
                    pm.tinhTrang = TinhTrangMuon::QuaHan; 
                }
                lichSu.push_back(pm);
            }
        }
        return lichSu;
    }

    vector<PhieuMuon> layLichSuMuonTheoSach(int maSach) {
        vector<PhieuMuon> lichSu;
        for (auto& pm : danhSachPhieuMuon) {
            if (pm.maSach == maSach) {
                if (pm.tinhTrang == TinhTrangMuon::DangMuon && pm.hanTra < time(0)) { 
                    pm.tinhTrang = TinhTrangMuon::QuaHan; 
                }
                lichSu.push_back(pm);
            }
        }
        return lichSu;
    }

    void inTatCaPhieuMuon() {
        cout << "----- Danh sách phiếu mượn (" << danhSachPhieuMuon.size() << " phiếu) -----" << endl;
        if (danhSachPhieuMuon.empty()) {
            cout << "Không có phiếu mượn nào trong hệ thống." << endl;
            return;
        }
        for (auto& pm : danhSachPhieuMuon) {
            if (pm.tinhTrang == TinhTrangMuon::DangMuon && pm.hanTra < time(0)) {
                pm.tinhTrang = TinhTrangMuon::QuaHan; 
            }
            pm.inThongTin();
        }
    }

    void luuVaoTep(const string& tenTep) {
        ofstream fout(tenTep);
        if (!fout) {
            cout << "Lỗi khi mở tệp để lưu phiếu mượn." << endl;
            return;
        }
        for (const auto& pm : danhSachPhieuMuon) {
            fout << pm.maPhieu << "|" << pm.maSach << "|" << pm.maNguoiDung << "|"
                 << pm.ngayMuon << "|" << pm.hanTra << "|" << pm.ngayTra << "|"
                 << (int)pm.tinhTrang << "\n";
        }
        fout.close();
        cout << "Đã lưu phiếu mượn vào tệp " << tenTep << endl;
    }

    void taiTuTep(const string& tenTep) {
        ifstream fin(tenTep);
        if (!fin) {
            cout << "Không có tệp nào để tải phiếu mượn." << endl;
            return;
        }
        danhSachPhieuMuon.clear();
        string dong;
        while (getline(fin, dong)) {
            PhieuMuon pm;
            size_t viTri = 0, truoc = 0;
            vector<string> truong;
            while ((viTri = dong.find('|', truoc)) != string::npos) {
                truong.push_back(dong.substr(truoc, viTri - truoc));
                truoc = viTri + 1;
            }
            truong.push_back(dong.substr(truoc));

            if (truong.size() == 7) {
                pm.maPhieu = stoi(truong[0]);
                pm.maSach = stoi(truong[1]);
                pm.maNguoiDung = stoi(truong[2]);
                pm.ngayMuon = stoll(truong[3]); 
                pm.hanTra = stoll(truong[4]);
                pm.ngayTra = stoll(truong[5]);
                pm.tinhTrang = static_cast<TinhTrangMuon>(stoi(truong[6]));

                danhSachPhieuMuon.push_back(pm);
                if (pm.maPhieu > maPhieuCuoi) maPhieuCuoi = pm.maPhieu;
            }
        }
        fin.close();
        cout << "Đã tải phiếu mượn từ tệp " << tenTep << endl;
    }
};

void hienThiMenuChinh(const NguoiDung* nguoiDungHienTai) {
    cout << "\n======= Hệ Thống Quản Lý Thư Viện =======\n";
    if (nguoiDungHienTai) {
        cout << "Chào mừng, " << nguoiDungHienTai->hoTen << " (" << vaiTroToString(nguoiDungHienTai->vaiTro) << ")\n";
    }
    cout << "1. Quản lý sách\n";
    cout << "2. Quản lý người dùng\n";
    cout << "3. Quản lý mượn/trả sách\n";
    cout << "0. Đăng xuất và thoát\n";
    cout << "Chọn một tuỳ chọn: ";
}

void hienThiMenuSach() {
    cout << "\n--- Quản Lý Sách ---\n";
    cout << "1. Thêm sách\n";
    cout << "2. Chỉnh sửa sách\n";
    cout << "3. Xoá sách\n";
    cout << "4. Tìm kiếm sách\n";
    cout << "5. Hiển thị tất cả sách\n";
    cout << "0. Quay lại\n";
    cout << "Chọn một tuỳ chọn: ";
}

void hienThiMenuNguoiDung() {
    cout << "\n--- Quản Lý Người Dùng ---\n";
    cout << "1. Thêm người dùng\n";
    cout << "2. Chỉnh sửa người dùng\n";
    cout << "3. Xoá người dùng\n";
    cout << "4. Tìm kiếm người dùng\n";
    cout << "5. Hiển thị tất cả người dùng\n";
    cout << "0. Quay lại\n";
    cout << "Chọn một tuỳ chọn: ";
}

void hienThiMenuMuonTra() {

    cout << "\n--- Quản Lý Mượn/Trả Sách ---\n";
    cout << "1. Mượn sách\n";
    cout << "2. Trả sách\n";
    cout << "3. Xem lịch sử mượn theo người dùng\n";
    cout << "4. Xem lịch sử mượn theo sách\n";
    cout << "5. Hiển thị tất cả lịch sử mượn\n";
    cout << "0. Quay lại\n";
    cout << "Chọn một tuỳ chọn: ";
}

int getValidIntegerInput() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Lỗi!, Vui lòng nhập số!: ";
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void chayGiaoDienDong(ThuVien& thuVien, QuanLyNguoiDung& quanLyNguoiDung, QuanLyMuon& quanLyMuon, NguoiDung* nguoiDungHienTai) {
    int luaChon = -1;
    while (luaChon != 0) {
        hienThiMenuChinh(nguoiDungHienTai);
        luaChon = getValidIntegerInput();

        switch(luaChon) {
            case 1: { // Quan ly sach
                // Chỉ cho phép Thủ thư và Quản trị viên quản lý sách
                int chon;
                do {
                    hienThiMenuSach();
                    chon = getValidIntegerInput();

                    if (chon == 1) { // Them sach
                        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc) {
                            cout << "Bạn không có quyền truy cập chức năng này." << endl;
                            continue;
                        }
                        Sach sachMoi;
                        cout << "Nhập ISBN: "; getline(cin >> ws, sachMoi.ISBN);
                        cout << "Nhập tên sách: "; getline(cin >> ws, sachMoi.tenSach);
                        cout << "Nhập tác giả: "; getline(cin >> ws, sachMoi.tacGia);
                        cout << "Nhập nhà xuất bản: "; getline(cin >> ws, sachMoi.nhaXuatBan);
                        cout << "Nhập năm xuất bản: "; sachMoi.namXuatBan = getValidIntegerInput(); 
                        cout << "Nhập kệ sách: "; getline(cin >> ws, sachMoi.keSach);
                        cout << "Nhập số lượng sách: "; sachMoi.soLuong = getValidIntegerInput(); 
                        while (sachMoi.soLuong < 0) {
                            cout << "Số lượng sách phải lớn hơn 0!\nNhập số lượng sách: ";
                            sachMoi.soLuong = getValidIntegerInput();
                        }
                        thuVien.themSach(sachMoi);
                    } else if (chon == 2) { // Chinh sua sach
                        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc) {
                            cout << "Bạn không có quyền truy cập chức năng này." << endl;
                            continue;
                        }
                        int id;
                        cout << "Nhập ID sách cần chỉnh sửa: "; id = getValidIntegerInput(); 
                        Sach* currentSach = thuVien.laySachTheoMa(id);

                        if (!currentSach) {
                            cout << "Sách không tồn tại." << endl;
                            continue;
                        }

                        Sach sachCapNhat;
                        cout << "Nhập ISBN mới (0 để bỏ qua): "; getline(cin >> ws, sachCapNhat.ISBN);
                        cout << "Nhập tên sách mới (0 để bỏ qua): "; getline(cin >> ws, sachCapNhat.tenSach);
                        cout << "Nhập tác giả mới (0 để bỏ qua): "; getline(cin >> ws, sachCapNhat.tacGia);
                        cout << "Nhập nhà xuất bản mới (0 để bỏ qua): "; getline(cin >> ws, sachCapNhat.nhaXuatBan);
                        cout << "Nhập năm xuất bản mới (0 để bỏ qua): "; sachCapNhat.namXuatBan = getValidIntegerInput();
                        cout << "Nhập kệ sách mới (0 để bỏ qua): "; getline(cin >> ws, sachCapNhat.keSach);
                        cout << "Nhập số lượng sách (0 để bỏ qua): "; sachCapNhat.soLuong = getValidIntegerInput();
                        while (sachCapNhat.soLuong < 0) {
                            cout << "Số lượng sách phải lớn hơn hoặc bằng 0!\nNhập số lượng sách: ";
                            sachCapNhat.soLuong = getValidIntegerInput();
                        }
                        if (sachCapNhat.ISBN == "0") sachCapNhat.ISBN = currentSach->ISBN;
                        if (sachCapNhat.tenSach == "0") sachCapNhat.tenSach = currentSach->tenSach;
                        if (sachCapNhat.tacGia == "0") sachCapNhat.tacGia = currentSach->tacGia;
                        if (sachCapNhat.nhaXuatBan == "0") sachCapNhat.nhaXuatBan = currentSach->nhaXuatBan;
                        if (sachCapNhat.namXuatBan == 0) sachCapNhat.namXuatBan = currentSach->namXuatBan;
                        if (sachCapNhat.keSach == "0") sachCapNhat.keSach = currentSach->keSach;
                        if (sachCapNhat.soLuong == 0) sachCapNhat.soLuong = currentSach->soLuong; // Keep old quantity if not provided

                        thuVien.suaSach(id, sachCapNhat);

                    } else if (chon == 3) { // Xoa sach
                        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc) {
                            cout << "Bạn không có quyền truy cập chức năng này." << endl;
                            continue;
                        }
                        int id;
                        cout << "Nhập ID sách cần xoá: "; id = getValidIntegerInput(); 
                        thuVien.xoaSach(id);
                    } else if (chon == 4) { // Tim kiem sach
                        string tuKhoa;
                        cout << "Nhập từ khoá để tìm kiếm: "; getline(cin , tuKhoa);
                        auto ketQua = thuVien.timKiemSach(tuKhoa);
                        if (ketQua.empty()) {
                            cout << "Không tìm thấy sách nào với từ khoá \"" << tuKhoa << "\"." << endl;
                        } else {
                            cout << "----- Kết quả tìm kiếm sách  với từ khóa \"" << tuKhoa << "\"-----" << endl;
                            for (const auto& sach : ketQua) sach.inThongTin();
                        }
                    } else if (chon == 5) { // Hien thi tat ca sach
                        thuVien.inDanhSachSach();
                    }
                } while (chon != 0);
                thuVien.luuVaoTep("sach.txt"); // Save after changes
                break;
            }

            case 2: { // Quan ly nguoi dung
                // Chỉ cho phép Quản trị viên quản lý người dùng
                if (nguoiDungHienTai->vaiTro != VaiTro::QuanTriVien) {
                    cout << "Bạn không có quyền truy cập chức năng này." << endl;
                    continue;
                }
                int chon;
                do {
                    hienThiMenuNguoiDung();
                    chon = getValidIntegerInput();
                    if (chon == 1) { // Them nguoi dung
                        NguoiDung nguoiDungMoi; int vaiTroInt; 
                        cout << "Nhập tên đăng nhập: "; getline(cin >> ws, nguoiDungMoi.tenDangNhap);
                        cout << "Nhập mật khẩu: "; getline(cin >> ws, nguoiDungMoi.matKhau);
                        cout << "Nhập họ tên đầy đủ: "; getline(cin >> ws, nguoiDungMoi.hoTen);
                        cout << "Nhập email: "; getline(cin >> ws, nguoiDungMoi.email);
                        do { 
                            cout << "Nhập vai trò (0 = Bạn đọc, 1 = Thủ thư, 2 = Quản trị viên): "; vaiTroInt = getValidIntegerInput(); 
                        } while (vaiTroInt < 0 || vaiTroInt > 2); 
                        nguoiDungMoi.vaiTro = static_cast<VaiTro>(vaiTroInt);
                        quanLyNguoiDung.themNguoiDung(nguoiDungMoi);
                    } else if (chon == 2) { // Chinh sua nguoi dung
                        int id;
                        cout << "Nhập ID người dùng cần chỉnh sửa: "; id = getValidIntegerInput(); 
                        NguoiDung nguoiDungCapNhat;
                        NguoiDung* currentUser = quanLyNguoiDung.layNguoiDungTheoMa(id);
                        if (!currentUser) {
                            cout << "Người dùng không tồn tại." << endl;
                            continue;
                        }

                        cout << "Nhập tên đăng nhập mới (0 để bỏ qua): "; getline(cin >> ws, nguoiDungCapNhat.tenDangNhap);    
                        cout << "Nhập mật khẩu mới (0 để bỏ qua): "; getline(cin >> ws, nguoiDungCapNhat.matKhau);
                        cout << "Nhập họ tên đầy đủ mới (0 để bỏ qua): "; getline(cin >> ws, nguoiDungCapNhat.hoTen);
                        cout << "Nhập email mới (0 để bỏ qua): "; getline(cin >> ws, nguoiDungCapNhat.email);
                        int vaiTroInt;
                        do {
                            cout << "Nhập vai trò mới (0 = Bạn đọc, 1 = Thủ thư, 2 = Quản trị viên): "; vaiTroInt = getValidIntegerInput();
                        } while (vaiTroInt < 0 || vaiTroInt > 2); 
                        nguoiDungCapNhat.vaiTro = static_cast<VaiTro>(vaiTroInt);
                        
                        if (nguoiDungCapNhat.tenDangNhap == "0") nguoiDungCapNhat.tenDangNhap = currentUser->tenDangNhap;
                        if (nguoiDungCapNhat.matKhau == "0") nguoiDungCapNhat.matKhau = currentUser->matKhau;
                        if (nguoiDungCapNhat.hoTen == "0") nguoiDungCapNhat.hoTen = currentUser->hoTen;
                        if (nguoiDungCapNhat.email == "0") nguoiDungCapNhat.email = currentUser->email;
                        quanLyNguoiDung.suaNguoiDung(id, nguoiDungCapNhat);

                    } else if (chon == 3) { // Xoa nguoi dung
                        int id;
                        cout << "Nhập ID người dùng cần xoá: "; id = getValidIntegerInput(); 
                        quanLyNguoiDung.xoaNguoiDung(id);

                    } else if (chon == 4) { // Tim kiem nguoi dung
                        string tuKhoa;
                        cout << "Nhập từ khoá để tìm kiếm: "; getline(cin, tuKhoa);
                        auto ketQua = quanLyNguoiDung.timKiemNguoiDung(tuKhoa);
                        if (ketQua.empty()) {
                            cout << "Không tìm thấy người dùng nào với từ khoá \"" << tuKhoa << "\"." << endl;
                        } else {
                            cout << "----- Kết quả tìm kiếm người dùng với từ khóa \"" << tuKhoa << "\"-----"<< endl;
                            for (const auto& nguoiDung : ketQua) nguoiDung.inThongTin();
                        }
                    } else if (chon == 5) { // Hien thi tat ca nguoi dung
                        quanLyNguoiDung.inTatCaNguoiDung();
                    }
                } while (chon != 0);
                quanLyNguoiDung.luuVaoTep("nguoidung.txt"); // Save after changes
                break;
            }

            case 3: { // Quan ly muon/tra
                int chon;
                do {
                    hienThiMenuMuonTra();
                    chon = getValidIntegerInput();
                    if (chon == 1) { // Muon sach
                        int idNguoiDung, idSach, soLuongMuon;
                        idNguoiDung = nguoiDungHienTai->maNguoiDung; // ID người dùng hiện tại

                        if (nguoiDungHienTai->vaiTro != VaiTro::BanDoc) {
                            cout << "Nhập ID người dùng cần mượn sách: "; idNguoiDung = getValidIntegerInput(); 
                        }
                        cout << "Nhập ID sách: "; idSach = getValidIntegerInput(); 
                        cout << "Hạn trả sách là 14 ngày kể từ ngày mượn." << endl;
                        quanLyMuon.muonSach(idNguoiDung, idSach);
                    } else if (chon == 2) { // Tra sach
                        int idMuon;
                        cout << "Nhập ID phiếu mượn để trả: "; idMuon = getValidIntegerInput(); 
                        quanLyMuon.traSach(idMuon, nguoiDungHienTai);
                    } else if (chon == 3) { // Xem lich su muon theo nguoi dung
                        int idNguoiDung;
                        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc) {
                            auto lichSu = quanLyMuon.layLichSuMuonTheoNguoiDung(nguoiDungHienTai->maNguoiDung);
                            if (lichSu.empty()) {
                                cout << "Bạn chưa có lịch sử mượn sách." << endl;
                            } else {
                                cout << "Lịch sử mượn sách của bạn (ID: " << nguoiDungHienTai->maNguoiDung << ")\n";
                                for (const auto& banGhi : lichSu) banGhi.inThongTin();
                            }
                            continue;
                        }
                        cout << "Nhập ID người dùng để xem lịch sử: "; 
                        idNguoiDung = getValidIntegerInput(); 
                        auto lichSu = quanLyMuon.layLichSuMuonTheoNguoiDung(idNguoiDung);
                        if (lichSu.empty()) {
                            cout << "Người dùng ID " << idNguoiDung << " chưa có lịch sử mượn sách." << endl;
                        } else {
                            cout << "----- Lịch sử mượn sách của người dùng ID \"" << idNguoiDung << "\" -----" << endl;
                            for (const auto& banGhi : lichSu) banGhi.inThongTin();
                        }
                    } else if (chon == 4) { // Xem lich su muon theo sach
                        int idSach;
                        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc) {
                            cout << "Bạn không có quyền truy cập chức năng này." << endl;
                            continue;
                        }
                        cout << "Nhập ID sách để xem lịch sử: "; idSach = getValidIntegerInput();
                        auto lichSu = quanLyMuon.layLichSuMuonTheoSach(idSach);
                        if (lichSu.empty()) {
                            cout << "Sách này chưa có lịch sử mượn." << endl;
                        } else {
                            cout << "----- Lịch sử mượn sách ID \"" << idSach << "\" -----" << endl;
                            for (const auto& banGhi : lichSu) banGhi.inThongTin();
                        }
                    } else if (chon == 5) { // Hien thi tat ca lich su muon
                        // Chỉ Thủ thư và Quản trị viên mới có thể xem tất cả phiếu mượn
                        if (nguoiDungHienTai->vaiTro == VaiTro::BanDoc) {
                            cout << "Bạn không có quyền truy cập chức năng này." << endl;
                            continue;
                        }
                        quanLyMuon.inTatCaPhieuMuon();
                    }
                } while (chon != 0);
                quanLyMuon.luuVaoTep("phieumuon.txt"); 
                break;
            }

            case 0:
                cout << "Đang đăng xuất và thoát... " << endl;
                break;

            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng thử lại." << endl;
        }
    }
}

int main() {

    ThuVien thuVien;
    QuanLyNguoiDung quanLyNguoiDung;
    QuanLyMuon quanLyMuon(thuVien, quanLyNguoiDung); 

    thuVien.taiTuTep("sach.txt");
    quanLyNguoiDung.taiTuTep("nguoidung.txt");
    quanLyMuon.taiTuTep("phieumuon.txt");


    if (quanLyNguoiDung.layNguoiDungTheoMa(1) == nullptr) {
        NguoiDung admin(0, "admin", "admin", "Quản trị viên", "admin@thuvien.com", VaiTro::QuanTriVien);
        quanLyNguoiDung.themNguoiDung(admin);
        quanLyNguoiDung.luuVaoTep("nguoidung.txt");
    }

    NguoiDung* nguoiDungHienTai = nullptr;
    string tenDangNhap, matKhau;

    while (nguoiDungHienTai == nullptr) {
        cout << "\n======= Đăng Nhập Hệ Thống =======\n";
        cout << "Tên đăng nhập: ";
        getline(cin, tenDangNhap);
        cout << "Mật khẩu: ";
        getline(cin, matKhau);

        nguoiDungHienTai = quanLyNguoiDung.dangNhap(tenDangNhap, matKhau);

        if (nguoiDungHienTai == nullptr) {
            cout << "Tên đăng nhập hoặc mật khẩu không đúng. Vui lòng thử lại." << endl;
        } else {
            cout << "Đăng nhập thành công! Chào mừng " << nguoiDungHienTai->hoTen << " (" << vaiTroToString(nguoiDungHienTai->vaiTro) << ")." << endl;
        }
    }

    // Chạy giao diện chính chỉ khi người dùng đã đăng nhập thành công
    chayGiaoDienDong(thuVien, quanLyNguoiDung, quanLyMuon, nguoiDungHienTai);

    thuVien.luuVaoTep("sach.txt");
    quanLyNguoiDung.luuVaoTep("nguoidung.txt");
    quanLyMuon.luuVaoTep("phieumuon.txt");

    return 0;
}
