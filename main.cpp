#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <string>

using namespace std;

struct toko
{
	int ID_barang, stock;
	long no_id, tPemasukan;
	double harga;
	string nama, tExpired, alamat, username, password;
} barang, tBarang, uAdmin, uPegawai;

#include "Barang.h"
#include "Admin.h"
#include "Pegawai.h"
#include "Autentifikasi.h"

int registrasi()
{
	Admin::create();
	return 0;
}

int login(int privil)
{
	int flag;
	char ch1, ch2;

	string temp1;
	string temp2;

	if (privil == 1)
	{
		cout << "Username: ";
		cin >> temp1;

		cout << "Password: ";
		ch2 = _getch();
		while (ch2 != 13)
		{
			temp2.push_back(ch2);
			cout << "*";
			ch2 = _getch();
		}
		ifstream fadm2;
		fadm2.open(Admin::dbAdmin, ios::binary);
		while (fadm2.read((char *)&uAdmin, sizeof(uAdmin)))
		{
			if (temp1 == uAdmin.username && temp2 == uAdmin.password)
			{
				cout << "\nAnda berhasil login.\n";
				flag = 1;
				return 1;
				break; // keluar dari loop
			}
		}
		if (flag != 1)
		{
			cout << "\nMaaf username atau password yang Anda masukkan salah.\n";
		}
	}
	else if (privil == 2)
	{
		cout << "Username: ";
		cin >> temp1;

		cout << "Password: ";
		ch2 = _getch();
		while (ch2 != 13)
		{
			temp2.push_back(ch2);
			cout << "*";
			ch2 = _getch();
		}

		ifstream fpg2;
		fpg2.open(Pegawai::dbPegawai, ios ::binary);
		while (fpg2.read((char *)&uPegawai, sizeof(uPegawai)))
		{
			if (temp1 == uPegawai.username && temp2 == uPegawai.password)
			{
				cout << "\nAnda berhasil login.\n";
				return 2;
				flag = 1;
				break; // keluar dari loop
			}
		}
		if (flag != 1)
		{
			cout << "\nMaaf username atau password yang Anda masukkan salah.\n";
		}
	}
	else if (privil == 3)
	{
		return 3;
	}
	else
	{
		return 5;
	}

	return -1;
}

int main()
{
	int pil, pil2, pil3, status1, status2, status3, i;
	status1 = 0;
	while (status1 == 0)
	{ // menu awal
		cout << "\nLogin Sebagai\n1.Admin\n2.Pegawai\n3.Register\n4.Batal\n";
		cout << "Masukkan pilihan: ";
		cin >> pil;
		status2 = 1;
		switch (login(pil))
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
							cout << "Masukkan ID barang dihapus: ";
							cin >> i;
							Barang::destroy(i);
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
					Barang::show();
					break;
				case 2:
					Barang::sale(13);
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
			registrasi();
			break;
		case 4:
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