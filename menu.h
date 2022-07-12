namespace Menu
{
  void utama();
  void login();
  void admin();
  void pegawai();
  void adminKelolaBarang();
  void adminKelolaAdmin();
  void adminKelolaPegawai();

  void utama()
  {
    int pilihan;
    cout << "\n\t\tSelamat Datang di Aplikasi SIDIA ( Sistem Database Input Barang )\n"
         << "1. Registrasi\n"
         << "2. Login\n"
         << "3. Exit\n"
         << "Masukkan pilihan :  ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
      Autentifikasi::registrasi();
      break;
    case 2:
      Menu::login();
      break;
    case 3:
      cout << "Keluar...\n";
      exit(1);
    default:
      cout << "\nInput Anda salah.\n";
      break;
    }
    Menu::utama();
  }

  void login()
  {
    int pilihan;
    cout << "\n\t\tLogin SIDIA\n"
         << "1. Admin\n"
         << "2. Pegawai\n"
         << "3. Kembali\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    switch (Autentifikasi::login(pilihan))
    {
    case 1:
      Menu::admin();
      break;
    case 2:
      Menu::pegawai();
      break;
    case 3:
      cout << "Keluar...\n";
      Menu::utama();
      break;
    default:
      cout << "\nInput Anda salah.\n";
      break;
    }
    Menu::login();
  }

  void admin()
  {
    int pilihan;
    cout << "\n\t\tAplikasi SIDIA";
    cout << "\nMenu ADMIN\n"
         << "1. Kelola barang\n"
         << "2. Kelola Admin\n"
         << "3. Kelola Pegawai\n"
         << "4. Logout\n";
    cout << "Masukkan pilihan : ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
      Menu::adminKelolaBarang();
      break;
    case 2:
      Menu::adminKelolaAdmin();
      break;
    case 3:
      Menu::adminKelolaPegawai();
      break;
    case 4:
      cout << "Logging out\n";
      Menu::login();
      break;
    default:
      cout << "\nInput Anda salah.";
      break;
    }
    Menu::admin();
  }

  void pegawai()
  {
    int pilihan, idBarang;
    cout << "\n\t\tAplikasi SIDIA";
    cout << "\nMenu PEGAWAI\n"
         << "1.Daftar Barang\n"
         << "2.Menjual\n"
         << "3.Logout\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
      Barang::show();
      break;
    case 2:
      cout << "Masukkan ID barang dijual: ";
      cin >> idBarang;
      Barang::sale(idBarang);
      break;
    case 3:
      cout << "Logging out\n";
      Menu::login();
      break;
    default:
      cout << "Input Anda salah.\n";
      break;
    }
    Menu::pegawai();
  }

  void adminKelolaBarang()
  {
    int pilihan, idBarang;
    cout << "\n\t\tAplikasi SIDIA"
         << "\nMenu KELOLA BARANG"
         << "\n1. Daftar Barang\n"
         << "2. Tambah Barang\n"
         << "3. Edit Barang\n"
         << "4. Cari Barang\n"
         << "5. Sorting Barang\n"
         << "6. Hapus Data Barang\n"
         << "7. Kembali\n"
         << "Masukkan pilihan : ";
    cin >> pilihan;
    switch (pilihan)
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
      cin >> idBarang;
      Barang::update(idBarang);
      break;
    case 4:
      cout << "Masukkan ID barang dicari: ";
      cin >> idBarang;
      Barang::search(idBarang);
      break;
    case 5:
      int order, col;
      cout << "Sorting barang berdasarkan: " << endl;
      cout << "1. ID Barang" << endl;
      cout << "2. Nama" << endl;
      cout << "3. Harga" << endl;
      cout << "4. Stock" << endl;
      cout << "4. Kadaluwarsa" << endl;
      cout << "Masukkan pilihan : ";
      cin >> col;
      Barang::sort(col, 1);
      break;
    case 6:
      cout << "Masukkan ID barang dihapus: ";
      cin >> idBarang;
      Barang::destroy(idBarang);
      break;
    case 7:
      cout << "Kembali...\n";
      Menu::admin();
      break;
    default:
      cout << "Input Anda salah.\n";
      break;
    }
    Menu::adminKelolaBarang();
  }

  void adminKelolaAdmin()
  {
    int pilihan, idAdmin;
    cout << "\n\t\tAplikasi SIDIA"
         << "\nMenu KELOLA ADMIN\n"
         << "1.Daftar Admin\n"
         << "2.Tambah Admin\n"
         << "3.Hapus Admin\n"
         << "4.Kembali\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    switch (pilihan)
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
      cin >> idAdmin;
      Admin::destroy(idAdmin);
      break;
    case 4:
      cout << "Kembali...\n";
      Menu::admin();
      break;
    default:
      cout << "Input Anda salah.\n";
      break;
    }
    Menu::adminKelolaAdmin();
  }

  void adminKelolaPegawai()
  {
    int pilihan, idPegawai;
    cout << "\n\t\tAplikasi SIDIA"
         << "\nMenu KELOLA PEGAWAI\n"
         << "1.Daftar Pegawai\n"
         << "2.Tambah Pegawai\n"
         << "3.Perbarui Data Pegawai\n"
         << "4.Hapus Data Pegawai\n"
         << "5.Kembali\n";
    cout << "\nMasukkan pilihan: ";
    cin >> pilihan;
    switch (pilihan)
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
      cin >> idPegawai;
      Pegawai::update(idPegawai);
      break;
    case 4:
      cout << "Masukkan No. Identitas Pegawai dihapus: ";
      cin >> idPegawai;
      Pegawai::destroy(idPegawai);
      break;
    case 5:
      cout << "Kembali...\n";
      Menu::admin();
      break;
    default:
      cout << "Input Anda salah.\n";
      break;
    }
    Menu::adminKelolaPegawai();
  }
}
