#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//file names should be saved as "streamername.csv"

int compare_2_streamers(string streamer1, string streamer2)
{

  //read from 1st file, store follower id in vector id1
  ifstream fin;
  fin.open(streamer1);

  if (fin.fail()){
    cout << "Failed to open 1";
    exit (1);
  }

  string line;
  vector <int> id1;
  getline(fin, line);
  while (getline(fin, line)){
    if (line[line.length()-1] == '0'){
      stringstream ss (line);
      string no;
      getline(ss, no, ',');
      getline(ss, no, ',');
      int n = stoi(no);
      id1.push_back(n);
    }
  }

  fin.close();

  //read from 2nd file, store follower id in vector id2
  fin.open(streamer2);

  if (fin.fail()){
    cout << "Failed to open 2";
    exit (1);
  }

  vector <int> id2;
  getline(fin, line);
  while (getline(fin, line)){
    if (line[line.length()-1] == '0'){
      stringstream ss (line);
      string no;
      getline(ss, no, ',');
      getline(ss, no, ',');
      int n = stoi(no);
      id2.push_back(n);
    }
  }
  fin.close();


  //sort ids in both vectors in ascending order
  sort(id1.begin(), id1.end());
  sort(id2.begin(), id2.end());

  //count duplicates
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

  cout << "Number of followers for " << streamer1 << " : " << id1.size() << endl;
  cout << "Number of followers for " << streamer2 << " : " << id2.size() << endl;
  cout << "Number of shared followers = " << duplicates << endl;

  return 0;
}

int main()
{
  //insert names of all streamers to be compared
  cout << "Insert list of steamers (enter \"???\" after last): " << endl;
  vector <string> streamers;
  string name;
  cin >> name;
  while (name != "???"){
    name = name + ".csv";
    streamers.push_back(name);
    cin >> name;
  }

  for (int i = 0; i < streamers.size(); ++ i){
    for (int j = i + 1; j < streamers.size(); ++ j){
      compare_2_streamers(streamers[i], streamers[j]);
      cout << endl;
    }
  }

  cout << "Process finished" << endl;

  return 0;
}
