#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  // Open a file for reading
  ifstream file("input.txt");

  // Loop using while (!File.eof())
  cout << "Loop using while (!File.eof())" << endl;
  string line;
  while (!file.eof())
  {
    getline(file, line);
    cout << line << endl;
  }

  // Reset the file pointer to the beginning of the file
  file.clear();
  file.seekg(0, ios::beg);

  // Loop using while (File >> line)
  cout << "Loop using while getline(file, line)" << endl;
  while (getline(file, line))
  {
    cout << line << endl;
  }

  // Close the file
  file.close();

  return 0;
}