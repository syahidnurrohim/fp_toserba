struct Admin
{
    string nama, alamat, username, password;
    long no_id;
} uAdmin;

char adm[30] = "admin.txt";

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