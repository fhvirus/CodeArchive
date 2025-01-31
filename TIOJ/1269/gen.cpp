#include <fstream>
#include <string>
using namespace std;

string code_path[5] = {"sub_1.txt", "sub_2.txt", "sub_3.txt", "sub_4.txt", "sub_5.txt"};
string output_path = "output.cpp";

int main() {
  fstream fin, fout;
  string t, out;
  size_t len, pos;

  fout.open(output_path.c_str(), ios::out);
  fout << "#include \"lib1269.h\"\n\n";

  for (int i = 0; i < 5; i++) {
    out = "";
    len = 0;
    fin.open(code_path[i].c_str(), ios::in);
    while (getline(fin, t)) {
      len += t.size() + 1;

      pos = 0;
      while ((pos = t.find('\\', pos)) != string::npos) t.insert(pos, 1, '\\'), pos += 2;
      pos = 0;
      while ((pos = t.find('\'', pos)) != string::npos) t.insert(pos, 1, '\\'), pos += 2;
      pos = 0;
      while ((pos = t.find('\"', pos)) != string::npos) t.insert(pos, 1, '\\'), pos += 2;

      out += t + "\\n";
    }
    fout << "char sol" << i + 1 << '[' << len + 2 << "] = \"" << out << "\";\n";
    fin.close();
  }
  fout << "\nchar* GetCode(int subtask)\n{\n    switch (subtask) {\n        case 1: return sol1;\n"
          "        case 2: return sol2;\n        case 3: return sol3;\n        case 4: return sol4;\n"
          "        case 5: return sol5;\n    }\n    return 0;\n}\n";
  fout.close();
}
