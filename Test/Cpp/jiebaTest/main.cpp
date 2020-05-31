#include <iostream>
#include <fstream>
#include <string>
#include "cppjieba/include/cppjieba/Jieba.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    //读取a.txt
    ifstream in;
    in.open("a.txt");
    string s[1000];
    int i = 1;
    while (!in.eof())
    {
        in >> s[i];
        i++;
    }

    const char *const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
    const char *const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
    const char *const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
    const char *const IDF_PATH = "cppjieba/dict/idf.utf8";
    const char *const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";
    //创建jieba类
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);

    //输出到b.txt
    ofstream out;
    out.open("b.txt");
    for (int j = 1; j < i; j++)
    {
        vector<string> words; //获取分词的vecotr

        jieba.Cut(s[j], words, true); //执行分词

        out << limonp::Join(words.begin(), words.end(), "/") << endl;
    }

    return 0;
}
