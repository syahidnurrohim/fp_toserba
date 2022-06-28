#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <string>

using namespace std;

#include "admin.h"
#include "barang.h"
#include "pegawai.h"
#include "login.h"

int main()
{
	int pil, pil2, pil3, status1, status2, status3, i;
	status1 = 0;
	while (status1 == 0)
	{ // menu awal
		cout << "\nLogin Sebagai\n1.Admin\n2.Pegawai\n3.Batal\n";
		cout << "Masukkan pilihan: ";
		cin >> pil;
		status2 = 1;
		switch (Login(pil))
		{
		case 1:
			cout << "\n\t\tTOKO SERBA ADA";
			status2 = 0;
			while (status2 == 0)
			{ // menu admin
				cout << "\nADMIN\n1.Kelola Barang\n2.Kelola Admin\n3.Kelola Pegawai\n4.Logout\n";
				cout << "Masukkan pilihan: ";
				cin >> pil2;
				switch (pil2)
				{
				case 1:
					cout << "\nKELOLA BARANG\n1.Daftar Barang\n2.Tambah\n3.Perbarui\n4.Cari\n5.Hapus\n6.Kembali\n";
					status3 = 0;
					while (status3 == 0)
					{ // Kelola barang
						cout << "Masukkan pilihan: ";
						cin >> pil3;
						switch (pil3)
						{
						case 1:
							bacaDataBarang();
							break;
						case 2:
							cout << "Silahkan masukkan data barang.\n";
							simpanDataBarang();
							break;
						case 3:
							cout << "Masukkan ID barang diperbarui: ";
							cin >> i;
							perbaruiDataBarang(i);
							break;
						case 4:
							cout << "Masukkan ID barang dicari: ";
							cin >> i;
							cariBarang(i);
							break;
						case 5:
							cout << "Masukkan ID barang dihapus: ";
							cin >> i;
							hapusDataBarang(i);
							break;
						case 6:
							status3 = 1;
							break;
						default:
							cout << "Input Anda salah.\n";
							break;
						}
					}
					break;
				case 2:
					cout << "\nKELOLA ADMIN\n1.Daftar Admin\n2.Tambah Admin\n3.Hapus Admin\n4.Kembali\n";
					status3 = 0; // Kelola admin
					while (status3 == 0)
					{
						cout << "Masukkan pilihan: ";
						cin >> pil;
						switch (pil)
						{
						case 1:
							bacaDataAdmin();
							break;
						case 2:
							cout << "Silahkan masukkan data Admin.\n";
							simpanDataAdmin();
							break;
						case 3:
							cout << "Masukkan No. Identitas Admin dihapus: ";
							cin >> i;
							hapusDataAdmin(i);
						case 4:
							status3 = 1;
							break;
						default:
							cout << "Input Anda salah.\n";
							break;
						}
					}
					break;
				case 3:
					cout << "\nKELOLA PEGAWAI\n1.Daftar Pegawai\n2.Tambah Pegawai\n3.Perbarui Data Pegawai\n4.Hapus Data Pegawai\n5.Kembali\n";
					status3 = 0; // Kelola pegawai
					while (status3 == 0)
					{
						cout << "\nMasukkan pilihan: ";
						cin >> pil;
						switch (pil)
						{
						case 1:
							bacaPegawai();
							break;
						case 2:
							cout << "Silahkan masukkan data Pegawai.\n";
							simpanPegawai();
							break;
						case 3:
							cout << "Masukkan No. Identitas Pegawai diperbarui: ";
							cin >> i;
							perbaruiDataPegawai(i);
							break;
						case 4:
							cout << "Masukkan No. Identitas Pegawai dihapus: ";
							cin >> i;
							hapusDataPegawai(i);
							break;
						case 5:
							status3 = 1;
							break;
						default:
							cout << "Input Anda salah.\n";
							break;
						}
					}
					break;
				case 4:
					cout << "Logging out\n";
					status2 = 1;
					break;
				default:
					cout << "\nInput Anda salah.";
					break;
				}
			}
			break;
		case 2:
			cout << "\t\tTOKO SERBA ADA\n";
			cout << "PEGAWAI\n1.Daftar Barang\n2.Menjual\n3.Logout\n";
			status2 = 0;
			while (status2 == 0)
			{
				cout << "Masukkan pilihan: ";
				cin >> pil;
				switch (pil)
				{
				case 1:
					bacaDataBarang();
					break;
				case 2:
					Jual(13);
					break;
				case 3:
					cout << "Logging out\n";
					status2 = 1;
					break;
				default:
					cout << "Input Anda salah.\n";
					break;
				}
			}
			break;
		case 3:
			status1 = 1;
			cout << "Keluar...\n";
			break;
		default:
			cout << "\nInput Anda salah.\n";
			break;
		}
	}
	getch();
	return 0;
}