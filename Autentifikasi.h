namespace Autentifikasi
{
    int registrasi()
    {
        Admin::create();
        return 0;
    }

    int login(int privil)
    {
        int flag = 0;
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
}