#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <readline/readline.h>
#include <set>
#include <string>
#include <time.h>
#include <vector>

bool isValid(std::string &guess, unsigned int length, std::set <std::string> &wordSet){
  bool guess_in_wordlist = false;
  if(guess.length() != length){
    if(guess.length() < length)
      std::cout << "Too short";
    else
      std::cout << "Too long";
    std::cout << ", try a word that is " << length << " letters long" << std::endl;
    getchar();
    return false;
  }
  if(wordSet.find(guess) != wordSet.end())
    guess_in_wordlist = true;
  return guess_in_wordlist;
}

void print_result(std::string word, std::string guess){
  for(long unsigned int i = 0; i < word.length(); i++){
    if(word[i] == guess[i]) std::cout << "\033[3;42;30m";
    else if(word.find(guess[i]) != std::string::npos) std::cout << "\033[3;43;30m";
    else std::cout << "\033[3;40;37m";
    std::cout << guess[i] << "\033[0m";
  }
  std::cout << std::endl;
}

void print_history(std::string word, std::vector <std::string> attempted_words, int indent){
  for(long unsigned int i = 0; i < attempted_words.size(); i++){
    for(int j = 0; j < indent; j++)
      std::cout << " ";
    print_result(word, attempted_words[i]);
  }
}

void print_end_game_message(bool win, std::string word){
  if(win){
    std::cout << "You win" << std::endl;
    return;
  }
  std::cout << "You lose" << std::endl;
  std::cout << "The word was " << word << std::endl;
}

bool play(std::string word, std::set <std::string> &wordSet){
  std::string prompt = ">>> ";
  bool win = false;
  std::vector <std::string> attempted_words;
  for(int turn = 1; turn <= 6; turn++){
    system("clear");
    print_history(word, attempted_words, prompt.length());
    char * guess_from_readline = readline(prompt.c_str());
    std::string guess(guess_from_readline);
    free(guess_from_readline);
    if(!isValid(guess, word.length(), wordSet)){
      turn--;
      continue;
    }
    attempted_words.push_back(guess);
    if(word == guess){
      win = true;
      break;
    }
  }
  print_end_game_message(win, word);
  std::cout << "Press any key to play again, or q to quit" << std::endl;
  return (getchar() != 'q');
}

int main(int argc, char *argv[]){
  srand(time(0));
  std::string inputFileName;
  std::string word;
  std::set <std::string> wordSet;
  bool playagain = true;
  if(argc != 2){
    std::cout << "Usage: " << argv[0] << " {integer}" << std::endl << std::endl;
    std::cout << "EXAMPLE: " << argv[0] << " 5" << std::endl;
    exit(EXIT_FAILURE);
  }
  inputFileName = "./dictionary/" + std::to_string(std::stoi(argv[1])) + ".txt";
  std::fstream input;
  input.open(inputFileName, std::fstream::in);
  while(getline(input, word))
    wordSet.insert(word);
  input.close();
  do{
    std::set<std::string>::iterator it = wordSet.cbegin();
    std::advance(it, rand() % wordSet.size());
    playagain = play(*it, wordSet);
  }while(playagain);
  exit(EXIT_SUCCESS);
}
