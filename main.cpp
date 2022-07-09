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
#include "Menu.h"

int main()
{
  Menu::utama();
  return 0;
}
