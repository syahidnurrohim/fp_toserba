#include <iostream>
#include <fstream>

using namespace std;

struct User 
{
  string username;
  string password;
  string nama;
};

void login();
void registrasi();
void menu();
void show_user();
bool find_by_username(string username);
int insert_user(User *u);
string readline(fstream &file);
string create_tag(string tag, string content);
User read_user_file(fstream &file);

int main()
{
  menu();
  return 0;
}

void menu()
{
  int pilihan;
  cout << "1. Login" << endl;
  cout << "2. Register" << endl;
  cout << "3. Exit" << endl;
  cout << "4. User" << endl;
  cout << "Pilih Menu : "; cin >> pilihan;
  switch (pilihan) {
    case 1:
      login();
      break;
    case 2:
      registrasi();
      break;
    case 3:
      exit(0);
    case 4:
      show_user();
      break;
    default:
      cout << "Pilihan tidak tersedia" << endl;
  }
  menu();
}

void registrasi()
{
  User *u = new User();
  cout << "Masukkan Nama: "; cin >> u->nama;
  cout << "Masukkan Username : "; cin >> u->username;
  cout << "Masukkan Password : "; cin >> u->password;

  int insert = insert_user(u);
  if (insert == 1) {
    cout << "User berhasil disimpan" << endl;
  } else if (insert == 2) {
    cout << "User gagal disimpan" << endl;
  }
}

void login()
{
  string username, password;
  cout << "Masukkan Username : "; cin >> username;
  cout << "Masukkan Password : "; cin >> password;

  bool ditemukan = find_by_username(username);

  if (ditemukan) {
    cout << "Login berhasil" << endl;
  } else {
    cout << "Username / password salah!!" << endl;
  }
}

bool find_by_username(string username)
{
  fstream file;
  file.open("user.txt", ios::in);
  if (file.good()) {
  }
  file.close();
  return true;
}

User read_user_file(fstream &file)
{
    string str = readline(file); 
    bool start;
    bool end;
    while (str != "") {
      start = str == "<User>";
      end = str == "</User>";
      if (start && !end) {

      }
      if (start && end) {

      }
      str = readline(file);
    }
}

/*
 * Data akan disimpan dengan format
 * startdata
 * nama
 * username
 * password
 * enddata
 */
int insert_user(User *u)
{
  fstream file;
  file.open("user.txt", ios::app | ios::binary);

  // Ketika file dapat dibuka
  if (file.good()) {
    file << "<User>" << endl;
    file << create_tag("Nama", u->nama) << endl;
    file << create_tag("Username", u->username) << endl;
    file << create_tag("Password", u->password) << endl;
    file << "</User>" << endl;
  }
  file.close();
  return 1;
}

void show_user()
{
  fstream file;
  file.open("user.txt", ios::in);

  if (file.good()) {
    User *u = new User();
    file.read((char *)u, sizeof(User));
    cout << u->username << endl;
    cout << "u->username" << endl;
  }
}

string create_tag(string tag, string content)
{
  return "<" + tag + ">" + content + "</" + tag + ">";
}

string readline(fstream &file)
{
  char c;
  string str = "";

  if (file.eof()) {
    return ""; 
  }

  while (file.get(c) && c != '\n') {
    str += c;
  }

  return str;
}
