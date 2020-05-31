#pragma warning(disable : 4996)
#include <iostream>
#include "cppjieba/include/cppjieba/Jieba.hpp"
using namespace std;

/*const char* const DICT_PATH = "./cppjieba-master/dict/jieba.dict.utf8";
const char* const HMM_PATH = "./cppjieba-master/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./cppjieba-master/dict/user.dict.utf8";
const char* const IDF_PATH = "./cppjieba-master/dict/idf.utf8";
const char* const STOP_WORD_PATH = "./cppjieba-master/dict/stop_words.utf8";*/

const char *const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
const char *const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
const char *const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
const char *const IDF_PATH = "cppjieba/dict/idf.utf8";
const char *const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";
int main(int argc, char **argv)
{
	cppjieba::Jieba jieba(DICT_PATH,
						  HMM_PATH,
						  USER_DICT_PATH,
						  IDF_PATH,
						  STOP_WORD_PATH);
	vector<string> words;
	string s;
	s = "他来到了网易杭研大厦";
	cout << s << endl;
	cout << "[demo] Cut With HMM" << endl;
	jieba.Cut(s, words, true);
	cout << limonp::Join(words.begin(), words.end(), "/") << endl;
	return EXIT_SUCCESS;
}