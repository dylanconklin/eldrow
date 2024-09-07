#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){
  std::vector <std::string> wordlist;
  std::vector <std::vector <std::string> > wordlistlist;
  std::string word;
  std::fstream input;
  std::fstream output;
  std::string outputFileName;
  input.open("./dictionary/words", std::fstream::in);
  while(getline(input, word)){
    while(wordlistlist.size() <= word.size())
      wordlistlist.push_back(wordlist);
    if(word.find("'") == std::string::npos){
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      wordlistlist[word.length()].push_back(word);
    }
  }
  input.close();
  for(int i = 0; i < wordlistlist.size(); i++){
    outputFileName = "./dictionary";
    outputFileName += std::to_string(i);
    outputFileName += ".txt";
    output.open(outputFileName, std::fstream::out | std::fstream::app);
    for(int j = 0; j < wordlistlist[i].size(); j++){
      output << wordlistlist[i][j] << std::endl;
    }
    output.close();
  }
}
