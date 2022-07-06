#include <iostream>
#include <fstream>

using namespace std;

struct User
{
  char username[255], password;
};

int main()
{
  User user;
  cout << "Username : ";
  cin >> user.username;
  cout << "Password : ";
  cin >> user.password;

  ofstream in;
  in.open("toserba.dat", ios::app | ios::binary);
  in.write((char *)&user, sizeof(user));
  in.close();
  cout << sizeof(user) << endl;

  ifstream out;
  out.open("toserba.dat", ios::binary);
  out.read((char *)&user, sizeof(user));
  cout << user.username << " - " << user.password << endl;
  cout << "-------" << endl;
  out.close();
}