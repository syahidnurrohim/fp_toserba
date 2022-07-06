namespace Pegawai
{
    char dbPegawai[30] = "pegawai.dat";

    void input()
    {
        cout << "Nama : ";
        // cin.ignore();
        // getline(cin, uPegawai.nama);
        cin >> uPegawai.nama;
        cout << "No. Identitas : ";
        cin >> uPegawai.no_id;
        cout << "Alamat : ";
        // cin.ignore();
        // getline(cin, uPegawai.alamat);
        cin >> uPegawai.alamat;
        cout << "username : ";
        cin >> uPegawai.username;
        cout << "Password : ";
        cin >> uPegawai.password;
    }

    void create()
    {
        ofstream create;
        input();
        // proses simpan objek ke file
        create.open(dbPegawai, ios ::binary | ios ::app);
        create.write((char *)&uPegawai, sizeof(uPegawai));
        create.close();
    }

    void output()
    {
        cout << "|" << setw(20) << uPegawai.nama
             << "|" << setw(20) << uPegawai.no_id
             << "|" << setw(20) << uPegawai.alamat
             << "|" << setw(20) << uPegawai.username
             << "|" << setw(20) << uPegawai.password << "|" << endl;
    }

    void show()
    { // akses untuk admin
        ifstream show;
        show.open(dbPegawai, ios ::binary);
        cout << "\n\t\t\tDaftar Pegawai\n";
        cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
        cout << "|        Nama        "
             << "|    No. Identitas   "
             << "|       Alamat       |"
             << "      username      |"
             << "      Password      |" << endl;
        cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
        while (show.read((char *)&uPegawai, sizeof(uPegawai)))
        {
            output();
        }
        cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
        show.close();
    }

    void update(long no_id_diperbarui)
    {
        fstream update; // baca/tulis file langsung
        update.open(dbPegawai, ios ::in | ios ::out);
        bool ktemu;
        ktemu = false;
        while (update.read((char *)&uPegawai, sizeof(uPegawai)))
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
                output();
                cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+\n";

                // memasukkan data baru
                cout << "Silahkan masukkan data pegawai baru." << endl;
                create();
                cout << "Data pegawai telah diperbarui\n";
                int pos = -1 * (int)sizeof(uPegawai);
                update.seekp(pos, ios ::cur);                      // cari posisi text di file
                update.write((char *)&uPegawai, sizeof(uPegawai)); // menulisnya ke barang.txt
                break;                                             // stop
            }
        }
        if (!ktemu)
        {
            cout << "\nNo. Identitas " << no_id_diperbarui << " tidak ditemukan.\n";
        }
        update.close();
    }

    void destroy(int no_id_dihapus)
    {
        ifstream destroy;
        destroy.open(dbPegawai, ios ::binary);

        ofstream updateDestroy;
        updateDestroy.open("temp_pg.txt", ios ::out | ios ::binary);

        bool ktemu = false;
        while (destroy.read((char *)&uAdmin, sizeof(uAdmin)))
        {
            if (uPegawai.no_id != no_id_dihapus)
            {
                updateDestroy.write((char *)&uAdmin, sizeof(uAdmin));
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
            output();
            cout << "+-----+--------------------+----------+----------+-------------+\n";
            cout << "Data pegawai telah dihapus.\n";
        }
        else
        {
            cout << "Data pegawai dengan No. Identitas " << no_id_dihapus << " tidak ditemukan.\n";
        }

        destroy.close();
        updateDestroy.close();

        remove(dbPegawai);
        rename("temp_pg.txt", dbPegawai);
    }
}