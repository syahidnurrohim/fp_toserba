namespace Admin
{
  char dbAdmin[30] = "admin.dat";

  // input data ke variabel admin
  void input()
  {
    cout << "Nama : ";
    cin.ignore();
    // getline(cin, uAdmin.nama);
    cin.getline(uAdmin.nama, 255);
    cout << "No. Identitas : ";
    cin >> uAdmin.no_id;
    cout << "Alamat : ";
    cin.ignore();
    // getline(cin, uAdmin.alamat);
    cin.getline(uAdmin.alamat, 255);
    cout << "Username : ";
    cin >> uAdmin.username;
    cout << "Password : ";
    cin >> uAdmin.password;
    cout << "\n";
  }

  // menambah data admin
  void create()
  {
    ofstream create;
    input();
    // proses simpan objek ke file
    create.open(dbAdmin, ios ::binary | ios ::app);
    create.write((char *)&uAdmin, sizeof(uAdmin));
    create.close();
  }

  // output data dari variabel admin
  void output()
  {
    cout << "|" << setw(25) << uAdmin.nama
      << "|" << setw(20) << uAdmin.no_id
      << "|" << setw(25) << uAdmin.alamat
      << "|" << endl;
  }

  // menampikan data admin
  void show()
  {
    ifstream show;
    show.open(dbAdmin, ios ::binary);
    cout << "\n\t\t\tDaftar Admin\n";
    cout << "+-------------------------+--------------------+-------------------------+\n";
    cout << "|           Nama          "
      << "|    No. Identitas   "
      << "|          Alamat         |" << endl;
    cout << "+-------------------------+--------------------+-------------------------+\n";
    while (show.read((char *)&uAdmin, sizeof(uAdmin)))
    {
      output();
    }
    cout << "+--------------------+--------------------+------------------------------+\n";
    show.close();
  }

  // menghapus data admin
  void destroy(int no_id_dihapus)
  {
    ifstream destroy;
    destroy.open(dbAdmin, ios ::binary);

    ofstream updateDestroy;
    updateDestroy.open("tempadm.txt", ios ::out | ios ::binary);

    bool ktemu = false;
    while (destroy.read((char *)&uAdmin, sizeof(uAdmin)))
    {
      if (uAdmin.no_id != no_id_dihapus)
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
      cout << "+-------------------------+--------------------+-------------------------+\n";
      cout << "|           Nama          "
        << "|    No. Identitas   "
        << "|          Alamat         |" << endl;
      cout << "+-------------------------+--------------------+-------------------------+\n";
      output();
      cout << "+--------------------+--------------------+------------------------------+\n";
      cout << "Data admin telah dihapus.\n";
    }
    else
    {
      cout << "Data admin dengan No. Identitas " << no_id_dihapus << " tidak ditemukan.\n";
    }

    destroy.close();
    updateDestroy.close();

    remove(dbAdmin);
    rename("tempadm.txt", dbAdmin);
  }
}
