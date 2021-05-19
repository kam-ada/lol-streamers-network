#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void matchpair (string x, string y)
{
  ifstream fin(x);

  if (fin.fail()){
    cout << "read file x: " << x;
    exit (1);
  }

  string header;
  getline (fin, header);
  string line;
  vector <int> id1;
  int idx = 0;

  while (getline (fin, line)){
    istringstream ss (line);
    string no;
    getline (ss, no, ',');
    getline (ss, no, ',');
    int n = stoi(no);
    id1.push_back(n);
  }

  fin.close();

  fin.open(y);

  if (fin.fail()){
    cout << "read file y: " << y;
    exit (1);
  }

  getline (fin, header);
  vector <int> id2;

  while (getline (fin, line)){
    if (line[line.length()-1] == '0'){
      istringstream ss (line);
      string no;
      getline (ss, no, ',');
      getline (ss, no, ',');
      int n = stoi(no);
      id2.push_back(n);
    }
  }

  fin.close();

  sort(id1.begin(), id1.end());
  sort(id2.begin(), id2.end());

  int duplicates = 0;
  int id1_index = 0;
  int id2_index = 0;
  int count = 0;

  while (true){
    if (id1[id1_index] == id2[id2_index]){
      duplicates ++;
      id1_index ++;
      id2_index ++;
    }
    else if (id1[id1_index] < id2[id2_index]){
      id1_index ++;
    }
    else if (id1[id1_index] > id2[id2_index]){
      id2_index ++;
    }
    if (id1_index >= id1.size() - 1 || id2_index >= id2.size() - 1){
      break;
    }
  }

  cout << "Number of followers for " << x << " : " << id1.size() << endl;
  cout << "Number of followers for " << y << " : " << id2.size() << endl;

  ofstream fout ("shared.csv", ios::app);

  if (fout.fail()){
    cout << "write file";
    exit (1);
  }

  fout << x.erase(x.length()-4, 4) << "," << y.erase(y.length()-4, 4) << "," << duplicates << endl;

  fout.close();
}

int main()
{

  string streamer[] = {"anniebot.csv", "ballslol.csv", "bjergsen.csv", "broxah.csv", "cyanide.csv", "dekar173.csv",
                       "doublelift.csv", "dyrus.csv", "goodguygarry.csv", "Hai.csv", "hyrqbot.csv", "kaypea.csv",
                       "kev1n.csv", "Lemonnation.csv", "lolgeranimo.csv", "meteos.csv", "nyph.csv", "ocelote.csv",
                       "reginald.csv", "rekkles.csv", "sOAZ.csv", "solorenekononly.csv", "svenskeren.csv", "swordart.csv",
                       "TheOddOne.csv", "Westrice.csv", "Wildturtle.csv", "Wingsofdeath.csv", "Xpecial.csv", "xPeke.csv",
                       "Yellowstar.csv", "zwag.csv"};

  for (int i = 0; i < 32; ++ i){
    for (int j = i + 1; j < 32; ++ j)
      matchpair (streamer[i], streamer[j]);
  }

}
