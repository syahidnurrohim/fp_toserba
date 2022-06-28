struct Pegawai
{
    string nama, alamat, username, password;
    long no_id;
} uPegawai;

char pg[30] = "pegawai.txt";

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
            int pos = -1 * sizeof(uPegawai);
            f.seekp(pos, ios ::cur);                      // cari posisi text di file
            f.write((char *)&uPegawai, sizeof(uPegawai)); // menulisnya ke barang.txt
            break;                                        // stop
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