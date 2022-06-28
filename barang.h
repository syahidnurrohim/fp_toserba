#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21
static char *getDtTm(char *buff)
{
    time_t t = time(0);
    strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
    return buff;
}

struct Barang
{
    int ID_barang, stock;
    long tPemasukan;
    double harga;
    string nama, tExpired;
} barang, tBarang;

char flatfile[30] = "barang.dat";

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
            int pos = -1 * sizeof(barang);
            f.seekp(pos, ios ::cur);                  // cari posisi text di file
            f.write((char *)&barang, sizeof(barang)); // menulisnya ke barang.txt
            break;                                    // stop
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

                    int pos = -1 * sizeof(barang);
                    f.seekp(pos, ios ::cur);                  // cari posisi text sekarang di file
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