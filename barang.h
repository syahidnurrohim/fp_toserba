namespace Barang
{
  /* ** Waktu ** */
#define DTTMFMT "%Y-%m-%d %H:%M:%S "
#define DTTMSZ 21

  static char *getDtTm(char *buff)
  {
    time_t t = time(0);
    strftime(buff, DTTMSZ, DTTMFMT, localtime(&t));
    return buff;
  }

  struct Node
  {
    toko data;
    Node *next;
  };

  Node *head;
  Node *sorted;

  void printNode(Node *head);
  void insertSort(Node *newnode, int col, int order);

  char dbBarang[30] = "barang.dat";

  void input()
  {
    cout << "ID          : ";
    cin >> barang.ID_barang;
    cout << "Nama        : ";
    cin >> barang.nama;
    // cin.ignore();
    // getline(cin, barang.nama);
    cout << "Harga       : ";
    cin >> barang.harga;
    cout << "Stock       : ";
    cin >> barang.stock;
    cout << "Kedaluwarsa : ";
    cin >> barang.tExpired;
    cout << "\n";
  }

  void create()
  {
    ofstream create;
    input();
    // proses simpan objek ke file
    create.open(dbBarang, ios ::binary | ios ::app);
    create.write((char *)&barang, sizeof(barang));
    create.close();
  }

  void output()
  {
    cout << "|" << setw(5) << barang.ID_barang
      << "|" << setw(20) << barang.nama
      << "|" << setw(12) << barang.harga
      << "|" << setw(10) << barang.stock
      << "|" << setw(14) << barang.tExpired << "|" << endl;
  }

  void show()
  {
    ifstream show;
    show.open(dbBarang, ios ::binary);
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    cout << "|   ID"
      << "|                Nama"
      << "|       Harga"
      << "|     Stock"
      << "|   Kedaluwarsa|" << endl;
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    while (show.read((char *)&barang, sizeof(barang)))
    {
      output();
    }
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    show.close();
  }

  void update(int ID_barang_diperbarui)
  {
    fstream update; // baca/tulis file langsung
    update.open(dbBarang, ios ::in | ios ::out);
    bool ktemu;
    ktemu = false;
    while (update.read((char *)&barang, sizeof(barang)))
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
        output();
        cout << "+-----+--------------------+------------+----------+--------------+\n";

        // memasukkan data baru
        cout << "Silahkan masukkan data barang baru." << endl;
        input();
        cout << "Data barang telah diperbarui\n";
        int pos = -1 * (int)sizeof(barang);
        update.seekp(pos, ios ::cur);                  // cari posisi text di file
        update.write((char *)&barang, sizeof(barang)); // menulisnya ke barang.txt
        break;                                         // stop
      }
    }
    if (!ktemu)
    {
      cout << "\nID barang " << ID_barang_diperbarui << " tidak ditemukan.\n";
    }
    update.close();
  }

  void destroy(int ID_barang_dihapus)
  {
    ifstream destroy;
    destroy.open(dbBarang, ios ::binary);

    ofstream updateDestroy;
    updateDestroy.open("temp.txt", ios ::out | ios ::binary);

    bool ktemu = false;
    while (destroy.read((char *)&barang, sizeof(barang)))
    {
      if (barang.ID_barang != ID_barang_dihapus)
      {
        updateDestroy.write((char *)&barang, sizeof(barang));
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
      output();
      cout << "+-----+--------------------+------------+----------+--------------+\n";
    }
    else
    {
      cout << "Data barang dengan ID " << ID_barang_dihapus << " tidak ditemukan.\n";
    }

    destroy.close();
    updateDestroy.close();

    remove(dbBarang);
    rename("temp.txt", dbBarang);
  }

  void search(int ID_barang_cari)
  {
    bool ktemu = false;

    ifstream search;
    search.open(dbBarang, ios ::binary);
    while (search.read((char *)&barang, sizeof(barang)))
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
      output();
      cout << "+-----+--------------------+------------+----------+--------------+\n";
    }
    else
    {
      cout << "\nID barang " << ID_barang_cari << " tidak ditemukan.\n";
    }
    search.close();
  }

  void sort(int col, int order)
  {
    ifstream show;
    show.open(dbBarang, ios ::binary);
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    cout << "|   ID"
      << "|                Nama"
      << "|       Harga"
      << "|     Stock"
      << "|   Kedaluwarsa|" << endl;
    cout << "+-----+--------------------+------------+----------+--------------+\n";

    head = new Node();
    Node *first = head;
    while (show.read((char *)&barang, sizeof(barang)))
    {
      first->data = barang;
      first->next = new Node();
      first = first->next;
      first->data.ID_barang = -1;
    }

    Barang::sorted = NULL;
    while (head != NULL) {
      Node *next = head->next;
      Barang::insertSort(head, col, order);
      head = next;
    }
    head = Barang::sorted;

    printNode(Barang::sorted);
    cout << "+-----+--------------------+------------+----------+--------------+\n";
    show.close();
  }

  void insertSort(Node *newnode, int col, int order)
  {
    bool rule1;

    if (Barang::sorted != NULL) {
      switch (col) {
        case 1:
          rule1 = Barang::sorted->data.ID_barang >= newnode->data.ID_barang;
          break;
        case 2:
          rule1 = Barang::sorted->data.nama >= newnode->data.nama;
          break;
        case 3:
          rule1 = Barang::sorted->data.harga >= newnode->data.harga;
          break;
        case 4:
          rule1 = Barang::sorted->data.stock >= newnode->data.stock;
          break;
        case 5:
          rule1 = Barang::sorted->data.tExpired >= newnode->data.tExpired;
          break;
      }
    }

    if (Barang::sorted == NULL || rule1) {
      newnode->next = Barang::sorted;
      sorted = newnode;
    } else {
      Node* current = Barang::sorted;
      bool rule2;
      switch (col) {
        case 1:
          rule2 = (current->next->data.ID_barang < newnode->data.ID_barang);
          break;
        case 2:
          rule2 = current->next->data.nama < newnode->data.nama;
          break;
        case 3:
          rule2 = current->next->data.harga < newnode->data.harga;
          break;
        case 4:
          rule2 = current->next->data.stock < newnode->data.stock;
          break;
        case 5:
          rule2 = current->next->data.tExpired < newnode->data.tExpired;
          break;
      }
      while (current->next != NULL
          && rule2) {
        current = current->next;
      }
      newnode->next = current->next;
      current->next = newnode;
    }
  }

  void sale(int ID_barang_dijual)
  {
    fstream sale; // baca/tulis file langsung
    sale.open(dbBarang, ios ::in | ios ::out);
    // ganti ke address folder masing"
    ofstream struk("struk.txt", ios::trunc); // overwrite
    ofstream trx("transaksi.txt", ios::app); // continously
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
      fstream sale; // baca/tulis file langsung
      sale.open(dbBarang, ios ::in | ios ::out);
      while (sale.read((char *)&barang, sizeof(barang)))
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
          output();
          cout << "+-----+--------------------+------------+----------+--------------+\n";

          // memasukkan data baru
          cout << "Masukkan jumlah barang: ";
          cin >> jumlah;
          if (barang.stock >= jumlah)
          {
            // assign data barang lama ke temporary
            unsigned int temp, temp2;
            double temp3;
            char temp4[255], temp5[255];
            temp = barang.ID_barang;
            // temp4 = barang.nama;
            strcpy(temp4, barang.nama);
            temp3 = barang.harga;
            temp2 = barang.stock - jumlah;
            // temp5 = barang.tExpired;
            strcpy(temp5, barang.tExpired);

            destroy(ID_barang_dijual); // data barang lama dihapus

            // assign data untuk struk dan menulis kembali ke barang.dat
            barang.ID_barang = temp;
            strcpy(temp4, barang.nama);
            // barang.nama = temp4;
            barang.harga = temp3;
            barang.stock = temp2;
            strcpy(temp5, barang.tExpired);
            // barang.tExpired = temp5;
            harga_jenis = barang.harga * jumlah;

            int pos = -1 * (int)sizeof(barang);
            sale.seekp(pos, ios ::cur);                  // cari posisi text sekarang di file
            sale.write((char *)&barang, sizeof(barang)); // menulisnya ke barang.dat
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
          cout << "Transaksi lagi?(1/0) : ";
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
    sale.close();
  }

  void printNode(Node *head)
  {
    while (head != NULL) {
      toko barang = head->data;
      if (barang.ID_barang == -1) {
        head = head->next;
        continue;
      }
      cout << "|" << setw(5) << barang.ID_barang
        << "|" << setw(20) << barang.nama
        << "|" << setw(12) << barang.harga
        << "|" << setw(10) << barang.stock
        << "|" << setw(14) << barang.tExpired << "|" << endl;
      head = head->next;
    }
  }
}
