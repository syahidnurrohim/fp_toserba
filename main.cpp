#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <cstring>

using namespace std;
struct toko
{
  int ID_barang, stock;
  long no_id, tPemasukan;
  double harga;
  char nama[255], tExpired[255], alamat[255], username[255], password[255];
} barang, tBarang, uAdmin, uPegawai;

#include "Barang.h"
#include "Admin.h"
#include "Pegawai.h"
#include "Autentifikasi.h"

int main()
{
  int pil, pil2, pil3, pil4, status1, status2, status3, status4, i;
  status1 = 0;
  while (status1 == 0)
  {
    cout << "\n\t\tSelamat Datang di Aplikasi SIDIA ( Sistem Database Input Barang )\n"
         << "1. Registrasi\n"
         << "2. Login\n"
         << "3. Exit\n"
         << "Masukkan pilihan :  ";
    cin >> pil;
    switch (pil)
    {
    case 1: // registrasi
      Autentifikasi::registrasi();
      break;
    case 2: // login
      status2 = 0;
      while (status2 == 0)
      {
        cout << "\n\t\tLogin SIDIA\n"
             << "1. Admin\n"
             << "2. Pegawai\n"
             << "3. Kembali\n";
        cout << "Masukkan pilihan: ";
        cin >> pil2;
        // status2 = 1;
        switch (Autentifikasi::login(pil2))
        {
        case 1: // menu admin
          status3 = 0;
          while (status3 == 0)
          {
            cout << "\n\t\tAplikasi SIDIA";
            cout << "\nMenu ADMIN\n"
                 << "1. Kelola barang\n"
                 << "2. Kelola Admin\n"
                 << "3. Kelola Pegawai\n"
                 << "4. Logout\n";
            cout << "Masukkan pilihan : ";
            cin >> pil3;
            switch (pil3)
            {
            case 1: // Kelola barang
              status4 = 0;
              while (status4 == 0)
              {
                cout << "\n\t\tAplikasi SIDIA"
                     << "\nMenu KELOLA BARANG"
                     << "\n1. Daftar Barang\n"
                     << "2. Tambah Barang\n"
                     << "3. Edit Barang\n"
                     << "4. Cari Barang\n"
                     << "5. Sorting Barang\n"
                     << "6. Hapus Data Barang\n"
                     << "7. Kembali\n"
                     << "Masukkan pilihan: ";
                cin >> pil4;
                switch (pil4)
                {
                case 1:
                  Barang::show();
                  break;
                case 2:
                  cout << "Silahkan masukkan data barang.\n";
                  Barang::create();
                  break;
                case 3:
                  cout << "Masukkan ID barang diperbarui: ";
                  cin >> i;
                  Barang::update(i);
                  break;
                case 4:
                  cout << "Masukkan ID barang dicari: ";
                  cin >> i;
                  Barang::search(i);
                  break;
                case 5:

                  break;
                case 6:
                  cout << "Masukkan ID barang dihapus: ";
                  cin >> i;
                  Barang::destroy(i);
                  break;
                case 7:
                  cout << "Kembali...\n";
                  status4 = 1;
                  break;
                default:
                  cout << "Input Anda salah.\n";
                  break;
                }
              }
              break;
            case 2: // Kelola admin
              status4 = 0;
              while (status4 == 0)
              {
                cout << "\nKELOLA ADMIN\n1.Daftar Admin\n2.Tambah Admin\n3.Hapus Admin\n4.Kembali\n";
                cout << "Masukkan pilihan: ";
                cin >> pil4;
                switch (pil4)
                {
                case 1:
                  Admin::show();
                  break;
                case 2:
                  cout << "Silahkan masukkan data Admin.\n";
                  Admin::create();
                  break;
                case 3:
                  cout << "Masukkan No. Identitas Admin dihapus: ";
                  cin >> i;
                  Admin::destroy(i);
                  break;
                case 4:
                  cout << "Kembali...\n";
                  status4 = 1;
                  break;
                default:
                  cout << "Input Anda salah.\n";
                  break;
                }
              }
              break;
            case 3:
              status4 = 0; // Kelola pegawai
              while (status4 == 0)
              {
                cout << "\nKELOLA PEGAWAI\n1.Daftar Pegawai\n2.Tambah Pegawai\n3.Perbarui Data Pegawai\n4.Hapus Data Pegawai\n5.Kembali\n";
                cout << "\nMasukkan pilihan: ";
                cin >> pil4;
                switch (pil4)
                {
                case 1:
                  Pegawai::show();
                  break;
                case 2:
                  cout << "Silahkan masukkan data Pegawai.\n";
                  Pegawai::create();
                  break;
                case 3:
                  cout << "Masukkan No. Identitas Pegawai diperbarui: ";
                  cin >> i;
                  Pegawai::update(i);
                  break;
                case 4:
                  cout << "Masukkan No. Identitas Pegawai dihapus: ";
                  cin >> i;
                  Pegawai::destroy(i);
                  break;
                case 5:
                  cout << "Kembali...\n";
                  status4 = 1;
                  break;
                default:
                  cout << "Input Anda salah.\n";
                  break;
                }
              }
              break;
            case 4:
              cout << "Logging out\n";
              status3 = 1;
              break;
            default:
              cout << "\nInput Anda salah.";
              break;
            }
          }
          break;
        case 2: // menu pegawai
          status3 = 0;
          while (status3 == 0)
          {
            cout << "\t\tTOKO SERBA ADA\n";
            cout << "PEGAWAI\n1.Daftar Barang\n2.Menjual\n3.Logout\n";
            cout << "Masukkan pilihan: ";
            cin >> pil3;
            switch (pil)
            {
            case 1:
              Barang::show();
              break;
            case 2:
              cout << "Masukkan ID barang dijual: ";
              cin >> i;
              Barang::sale(i);
              break;
            case 3:
              cout << "Logging out\n";
              status3 = 1;
              break;
            default:
              cout << "Input Anda salah.\n";
              break;
            }
          }
          break;
        case 3:
          cout << "Keluar...\n";
          status2 = 1;
          break;
        default:
          cout << "\nInput Anda salah.\n";
          break;
        }
        break;
      }
      break;
    case 3:
      cout << "Keluar...\n";
      status1 = 1;
      break;
    default:
      cout << "\nInput Anda salah.\n";
      break;
    }
  }
  getch();
  return 0;
}
