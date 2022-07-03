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

/* ** Waktu ** */
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21
static char *getDtTm(char *buff)
{
  time_t t = time(0);
  strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
  return buff;
}

/* ** Fungsi dan Prosedur barang * **/

void keluaranBarang()
{
  cout << "|" << setw(5) << barang.ID_barang
    << "|" << setw(20) << barang.nama
    << "|" << setw(12) << barang.harga
    << "|" << setw(10) << barang.stock
    << "|" << setw(14) << barang.tExpired << "|" << endl;
}

void buatBarang()
{
  int i;
  cout << "ID          : ";
  cin >> barang.ID_barang;
  cout << "Nama        : ";
  cin.ignore();
  getline(cin, barang.nama);
  cout << "Harga       : ";
  cin >> barang.harga;
  cout << "Stock       : ";
  cin >> barang.stock;
  cout << "Kedaluwarsa : ";
  cin >> barang.tExpired;
  cout << "\n";
}

char flatfile[30] = "barang.dat";

void simpanDataBarang()
{
  ofstream f;
  buatBarang();
  // proses simpan objek ke file
  f.open(flatfile, ios ::binary | ios ::app);
  f.write((char *)&barang, sizeof(barang));
  f.close();
}

void bacaDataBarang()
{
  ifstream f;
  f.open(flatfile, ios ::binary);
  cout << "+-----+--------------------+------------+----------+--------------+\n";
  cout << "|   ID"
    << "|                Nama"
    << "|       Harga"
    << "|     Stock"
    << "|   Kedaluwarsa|" << endl;
  cout << "+-----+--------------------+------------+----------+--------------+\n";
  while (f.read((char *)&barang, sizeof(barang)))
  {
    keluaranBarang();
  }
  cout << "+-----+--------------------+------------+----------+--------------+\n";
  f.close();
}

void perbaruiDataBarang(int ID_barang_diperbarui)
{
  fstream f; // baca/tulis file langsung
  f.open(flatfile, ios ::in | ios ::out);
  bool ktemu;
  ktemu = false;
  while (f.read((char *)&barang, sizeof(barang)))
  {
    if (barang.ID_barang == ID_barang_diperbarui)
    {
      ktemu = true;
      // menampilkan detil sebelum diperbarui
      cout << "+-----+--------------------+------------+----------+--------------+\n";
      cout << "|   ID"
        << "|                Nama"
        << "|       Harga"
        << "|     Stock"
        << "|   Kedaluwarsa|" << endl;
      cout << "+-----+--------------------+------------+----------+--------------+\n";
      keluaranBarang();
      cout << "+-----+--------------------+------------+----------+--------------+\n";

      // memasukkan data baru
      cout << "Silahkan masukkan data barang baru." << endl;
      buatBarang();
      cout << "Data barang telah diperbarui\n";
      int pos = -1 * (int)sizeof(barang);
      f.seekp(pos, ios ::cur);				  // cari posisi text di file
      f.write((char *)&barang, sizeof(barang)); // menulisnya ke barang.txt
      break;									  // stop
    }
  }
  if (!ktemu)
  {
    cout << "\nID barang " << ID_barang_diperbarui << " tidak ditemukan.\n";
  }
  f.close();
}

void cariBarang(int ID_barang_cari)
{
  bool ktemu = false;

  ifstream f;
  f.open(flatfile, ios ::binary);
  while (f.read((char *)&barang, sizeof(barang)))
  {
    // keadaan jika barang ditemukan
    if (barang.ID_barang == ID_barang_cari)
    {
      tBarang = barang;
      ktemu = true;
      break; // stop looping
    }
  }
  if (ktemu)
  { // eksekusi ketika barang ditemukan
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    cout << "|   ID"
      << "|                Nama"
      << "|       Harga"
      << "|     Stock"
      << "|   Kedaluwarsa|" << endl;
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    keluaranBarang();
    cout << "+-----+--------------------+------------+----------+--------------+\n";
  }
  else
  {
    cout << "\nID barang " << ID_barang_cari << " tidak ditemukan.\n";
  }
  f.close();
}

void hapusDataBarang(int ID_barang_dihapus)
{
  ifstream f2;
  f2.open(flatfile, ios ::binary);

  ofstream f3;
  f3.open("temp.txt", ios ::out | ios ::binary);

  bool ktemu = false;
  while (f2.read((char *)&barang, sizeof(barang)))
  {
    if (barang.ID_barang != ID_barang_dihapus)
    {
      f3.write((char *)&barang, sizeof(barang));
    }
    else
    {
      ktemu = true;
    }
  }

  if (ktemu)
  {
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    cout << "|   ID"
      << "|                Nama"
      << "|       Harga"
      << "|     Stock"
      << "|   Kedaluwarsa|" << endl;
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    keluaranBarang();
    cout << "+-----+--------------------+------------+----------+--------------+\n";
  }
  else
  {
    cout << "Data barang dengan ID " << ID_barang_dihapus << " tidak ditemukan.\n";
  }

  f2.close();
  f3.close();

  remove(flatfile);
  rename("temp.txt", flatfile);
}

/* Definisi Admin dan Pegawai */
/* ** Admin ** */

void keluaranAdmin()
{
  cout << "|" << setw(25) << uAdmin.nama
    << "|" << setw(20) << uAdmin.no_id
    << "|" << setw(25) << uAdmin.alamat
    << "|" << endl;
}

void buatAdmin()
{
  cout << "Nama : ";
  cin.ignore();
  getline(cin, uAdmin.nama);
  cout << "No. Identitas : ";
  cin >> uAdmin.no_id;
  cout << "Alamat : ";
  cin.ignore();
  getline(cin, uAdmin.alamat);
  cout << "username : ";
  cin >> uAdmin.username;
  cout << "Password : ";
  cin >> uAdmin.password;
  cout << "\n";
}

char adm[30] = "admin.dat";

void simpanDataAdmin()
{
  ofstream fadm;
  buatAdmin();
  // proses simpan objek ke file
  fadm.open(adm, ios ::binary | ios ::app);
  fadm.write((char *)&uAdmin, sizeof(uAdmin));
  fadm.close();
}

void bacaDataAdmin()
{
  ifstream fadm;
  fadm.open(adm, ios ::binary);
  cout << "\n\t\t\tDaftar Admin\n";
  cout << "+-------------------------+--------------------+-------------------------+\n";
  cout << "|           Nama          "
    << "|    No. Identitas   "
    << "|          Alamat         |" << endl;
  cout << "+-------------------------+--------------------+-------------------------+\n";
  while (fadm.read((char *)&uAdmin, sizeof(uAdmin)))
  {
    keluaranAdmin();
  }
  cout << "+--------------------+--------------------+------------------------------+\n";
  fadm.close();
}

void hapusDataAdmin(int no_id_dihapus)
{
  ifstream fadm2;
  fadm2.open(adm, ios ::binary);

  ofstream fadm3;
  fadm3.open("tempadm.txt", ios ::out | ios ::binary);

  bool ktemu = false;
  while (fadm2.read((char *)&uAdmin, sizeof(uAdmin)))
  {
    if (uAdmin.no_id != no_id_dihapus)
    {
      fadm3.write((char *)&uAdmin, sizeof(uAdmin));
    }
    else
    {
      ktemu = true;
    }
  }

  if (ktemu)
  {
    cout << "+-------------------------+--------------------+-------------------------+\n";
    cout << "|           Nama          "
      << "|    No. Identitas   "
      << "|          Alamat         |" << endl;
    cout << "+-------------------------+--------------------+-------------------------+\n";
    keluaranAdmin();
    cout << "+--------------------+--------------------+------------------------------+\n";
    cout << "Data admin telah dihapus.\n";
  }
  else
  {
    cout << "Data admin dengan No. Identitas " << no_id_dihapus << " tidak ditemukan.\n";
  }

  fadm2.close();
  fadm3.close();

  remove(adm);
  rename("tempadm.txt", adm);
}

/* ** Pegawai ** */

void keluaranPegawai()
{
  cout << "|" << setw(20) << uPegawai.nama
    << "|" << setw(20) << uPegawai.no_id
    << "|" << setw(20) << uPegawai.alamat
    << "|" << setw(20) << uPegawai.username
    << "|" << setw(20) << uPegawai.password << "|" << endl;
}

void buatPegawai()
{
  cout << "Nama : ";
  cin.ignore();
  getline(cin, uPegawai.nama);
  cout << "No. Identitas : ";
  cin >> uPegawai.no_id;
  cout << "Alamat : ";
  cin.ignore();
  getline(cin, uPegawai.alamat);
  cout << "username : ";
  cin >> uPegawai.username;
  cout << "Password : ";
  cin >> uPegawai.password;
}

char pg[30] = "pegawai.txt";

void simpanPegawai()
{
  ofstream fpg;
  buatPegawai();
  // proses simpan objek ke file
  fpg.open(pg, ios ::binary | ios ::app);
  fpg.write((char *)&uPegawai, sizeof(uPegawai));
  fpg.close();
}

void bacaPegawai()
{ // akses untuk admin
  ifstream fpg;
  fpg.open(pg, ios ::binary);
  cout << "\n\t\t\tDaftar Pegawai\n";
  cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
  cout << "|        Nama        "
    << "|    No. Identitas   "
    << "|       Alamat       |"
    << "      username      |"
    << "      Password      |" << endl;
  cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
  while (fpg.read((char *)&uPegawai, sizeof(uPegawai)))
  {
    keluaranPegawai();
  }
  cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
  fpg.close();
}

void perbaruiDataPegawai(long no_id_diperbarui)
{
  fstream f; // baca/tulis file langsung
  f.open(pg, ios ::in | ios ::out);
  bool ktemu;
  ktemu = false;
  while (f.read((char *)&uPegawai, sizeof(uPegawai)))
  {
    if (uPegawai.no_id == no_id_diperbarui)
    {
      ktemu = true;
      // menampilkan detil sebelum diperbarui
      cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
      cout << "|        Nama        "
        << "|    No. Identitas   "
        << "|       Alamat       |"
        << "      username      |"
        << "      Password      |" << endl;
      cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
      keluaranPegawai();
      cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";

      // memasukkan data baru
      cout << "Silahkan masukkan data pegawai baru." << endl;
      buatBarang();
      cout << "Data pegawai telah diperbarui\n";
      int pos = -1 * (int)sizeof(uPegawai);
      f.seekp(pos, ios ::cur);					  // cari posisi text di file
      f.write((char *)&uPegawai, sizeof(uPegawai)); // menulisnya ke barang.txt
      break;										  // stop
    }
  }
  if (!ktemu)
  {
    cout << "\nNo. Identitas " << no_id_diperbarui << " tidak ditemukan.\n";
  }
  f.close();
}

void hapusDataPegawai(int no_id_dihapus)
{
  ifstream fpg2;
  fpg2.open(pg, ios ::binary);

  ofstream fpg3;
  fpg3.open("temp_pg.txt", ios ::out | ios ::binary);

  bool ktemu = false;
  while (fpg2.read((char *)&uAdmin, sizeof(uAdmin)))
  {
    if (uPegawai.no_id != no_id_dihapus)
    {
      fpg3.write((char *)&uAdmin, sizeof(uAdmin));
    }
    else
    {
      ktemu = true;
    }
  }

  if (ktemu)
  {
    cout << "+-----+--------------------+----------+----------+-------------+\n";
    cout << "| Nama"
      << "|     No. Identitas"
      << "|     Alamat|" << endl;
    cout << "+-----+--------------------+----------+----------+-------------+\n";
    keluaranPegawai();
    cout << "+-----+--------------------+----------+----------+-------------+\n";
    cout << "Data pegawai telah dihapus.\n";
  }
  else
  {
    cout << "Data pegawai dengan No. Identitas " << no_id_dihapus << " tidak ditemukan.\n";
  }

  fpg2.close();
  fpg3.close();

  remove(pg);
  rename("temp_pg.txt", pg);
}

/* ** Transaksi ** */

void Jual(int ID_barang_dijual)
{
  fstream f; // baca/tulis file langsung
  f.open(flatfile, ios ::in | ios ::out);
  // ganti ke address folder masing"
  ofstream struk("D:\\TUGAS\\DASPROG\\MINGGU UAS\\TUBES_toserba\\struk.txt", ios::trunc); // overwrite
  ofstream trx("D:\\TUGAS\\DASPROG\\MINGGU UAS\\TUBES_toserba\\transaksi.txt", ios::app); // continously
  unsigned int jumlah, pil, hTotal = 0, harga_jenis;

  char buff[DTTMSZ]; // buffer waktu
  struk << "-------------------------------------------------\n";
  struk << getDtTm(buff) << endl;
  trx << "-------------------------------------------------\n";
  trx << getDtTm(buff) << endl;
  bool tambah;

  tambah = true;
  while (tambah)
  {
    fstream f; // baca/tulis file langsung
    f.open(flatfile, ios ::in | ios ::out);
    while (f.read((char *)&barang, sizeof(barang)))
    {
      if (barang.ID_barang == ID_barang_dijual)
      {
        // menampilkan detil sebelum diperbarui
        cout << "+-----+--------------------+------------+----------+--------------+\n";
        cout << "|   ID"
          << "|                Nama"
          << "|       Harga"
          << "|     Stock"
          << "|   Kedaluwarsa|" << endl;
        cout << "+-----+--------------------+------------+----------+--------------+\n";
        keluaranBarang();
        cout << "+-----+--------------------+------------+----------+--------------+\n";

        // memasukkan data baru
        cout << "Masukkan jumlah barang: ";
        cin >> jumlah;
        if (barang.stock >= jumlah)
        {
          // assign data barang lama ke temporary
          unsigned int temp, temp2;
          double temp3;
          string temp4, temp5;
          temp = barang.ID_barang;
          temp4 = barang.nama;
          temp3 = barang.harga;
          temp2 = barang.stock - jumlah;
          temp5 = barang.tExpired;

          hapusDataBarang(ID_barang_dijual); // data barang lama dihapus

          // assign data untuk struk dan menulis kembali ke barang.dat
          barang.ID_barang = temp;
          barang.nama = temp4;
          barang.harga = temp3;
          barang.stock = temp2;
          barang.tExpired = temp5;
          harga_jenis = barang.harga * jumlah;

          int pos = -1 * (int)sizeof(barang);
          f.seekp(pos, ios ::cur);				  // cari posisi text sekarang di file
          f.write((char *)&barang, sizeof(barang)); // menulisnya ke barang.dat
          struk << "-------------------------------------------------\n";
          struk << barang.nama << setw(5) << jumlah << setw(10) << barang.harga << setw(10) << harga_jenis << endl;
          trx << "-------------------------------------------------\n";
          trx << barang.nama << setw(5) << jumlah << setw(10) << barang.harga << setw(10) << harga_jenis << endl;
          hTotal += harga_jenis;
        }
        else
        {
          cout << "Stok tidak tersedia atau mencukupi.\n";
        }
        cout << "Transaksi(1/0) : ";
        cin >> pil;
        if (pil == 1)
        {
          cout << "\nMencetak struk...\n";
          tambah = false;
        }
        else if (pil == 0)
        {
          tambah = true;
        }
        else
        {
          cout << "Input Anda salah.";
          tambah = false;
        }
      }
    }
  }
  struk << "-------------------------------------------------\n";
  struk << setw(28) << "HARGA TOTAL = " << hTotal << "\n\n";
  trx << "-------------------------------------------------\n";
  trx << setw(28) << "HARGA TOTAL = " << hTotal << "\n\n";
  struk.close();
  trx.close();
  f.close();
}

/* registrasi & login */

int Registrasi()
{
  simpanDataAdmin();
  return 0;
}

int Login(int privil)
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
    fadm2.open(adm, ios::binary);
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
    fpg2.open(pg, ios ::binary);
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
        Registrasi();
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
