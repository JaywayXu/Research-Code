#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cppjieba/include/cppjieba/Jieba.hpp"
using namespace std;

const char *const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
const char *const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
const char *const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
const char *const IDF_PATH = "cppjieba/dict/idf.utf8";
const char *const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";

const int readFilesNum = 3; // 读取文件的个数
//const string readFiles[] = {"C3-Art0002.txt", "C3-Art0003.txt", "C3-Art0005.txt"}; // 读取的文件
const string readFiles[] = {"a1.txt", "a2.txt", "a3.txt"}; // 读取的文件
const string writeFile = "b.txt";                          // 写入的文件
const int topk = 5;                                        // 越高关键词越多

class InvertedIndexPoint
{ // 倒排索引节点类
public:
    string keyword;         // 关键词
    vector<string> fileVec; // 对应文件vector
    InvertedIndexPoint() {} // 默认构造函数
    InvertedIndexPoint(string keyword, string filename)
    { // 根据传进的keyword和最初的filename创建
        this->keyword = keyword;
        fileVec.push_back(filename);
    }
    void appendFile(string file)
    { // 添加索引的文件
        // // 如果存在
        // for (int i = 0; i < fileVec.size(); i++)
        // {
        //     if (file.compare(fileVec[i]) == 0)
        //     { // 找到了相同文件
        //         return;
        //     }
        // }
        fileVec.push_back(file);
    }
};

class InvertedIndexList
{ // 倒排索引类
public:
    vector<InvertedIndexPoint> list;                     //节点vector
    int getIndex(string keyword);                        // 查找索引是否存在，存在则返回对应下标
    void addKeyFile(string keyword, string filename);    // 添加关键词和对应文件
    void getFilesVec(string keyword, vector<string> &v); // 查找关键词所在的文件
    void printToFile(string filename);                   // 打印输出
};

int InvertedIndexList::getIndex(string keyword)
{ // 查找索引是否存在，存在则返回对应下标，不存在返回-1
    for (int i = 0; i < list.size(); i++)
    {
        if (!keyword.compare(list[i].keyword)) // 相等
        {
            return i;
        }
    }
    return -1;
}

void InvertedIndexList::addKeyFile(string keyword, string filename)
{ // 添加关键词和对应文件
    int index = getIndex(keyword);
    if (index != -1)
    { // 如果当前存在keyword，则添加文件
        list[index].appendFile(filename);
    }
    else
    { // 如果不存在keyword，则创建索引
        InvertedIndexPoint p(keyword, filename);
        list.push_back(p);
    }
}

void InvertedIndexList::getFilesVec(string keyword, vector<string> &v)
{ // 查找关键词所在的文件
    int index = getIndex(keyword);
    if (index != -1)
    {
        // // 拷贝vector
        // for (int i = 0; i < list[index].fileVec.size(); i++)
        // {
        //     v.push_back(list[index].fileVec[i]);
        // }
        v = list[index].fileVec;
    }
}

void InvertedIndexList::printToFile(string filename)
{ // 输出到文件
    ofstream out;
    out.open(filename);

    for (int i = 0; i < list.size(); i++)
    {
        out << list[i].keyword << ":";
        for (int j = 0; j < list[i].fileVec.size(); j++)
        {
            out << " " << list[i].fileVec[j];
        }
        out << endl;
    }

    out.close();
}

void extractFileKeywords(cppjieba::Jieba &jieba, vector<cppjieba::KeywordExtractor::Word> &keywords, string filename)
{ // 对文件进行关键词分析，返回关键词数组
    // 读取文件
    ifstream in;
    in.open(filename);
    string readString, s;
    while (!in.eof())
    {
        in >> s;
        readString += s;
    }
    in.close();

    jieba.extractor.Extract(readString, keywords, topk); // 执行关键词提取
}

int main(int argc, char const *argv[])
{
    // 创建jieba类
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);

    // 创建倒排索引对象
    InvertedIndexList iil;

    // 对每个文件进行关键词分析
    for (int i = 0; i < readFilesNum; i++)
    {
        vector<cppjieba::KeywordExtractor::Word> fileKeywords;  // 获取关键次的vector
        extractFileKeywords(jieba, fileKeywords, readFiles[i]); // 对文件分析关键词

        for (int j = 0; j < fileKeywords.size(); j++)
        {
            iil.addKeyFile(fileKeywords[j].word, readFiles[i]); // 添加关键词和文件名

            // 测试读取文件某字节
            ifstream iff;
            iff.open(readFiles[i]);
            iff.clear();
            iff.seekg(fileKeywords[j].offsets[0], ios::cur);
            string a;
            iff >> a;
            iff.close();
            ofstream off;
            off.open("x.txt", ios::app);
            off << readFiles[i] << ":" << fileKeywords[j].word << ":";
            off << a << endl;
            off.close();

            // // 测试getFilesVec
            // vector<string> v;
            // iil.getFilesVec(fileKeywords[j].word, v);
            // ofstream testo;
            // testo.open("x.txt", ios::app);
            // testo << fileKeywords[j].word << ":";
            // for (int x = 0; x < v.size(); x++)
            // {
            //     if (v.size() > 0)
            //     {
            //         testo << " " << v[x];
            //     }
            // }
            // testo << endl;
            // testo.close();
        }

        // // 每个文件的关键词输出测试
        // ofstream out;
        // out.open("x.txt", ios::app);
        // for (int j = 0; j < fileKeywords.size(); j++)
        // {
        //     out << fileKeywords[j].word << " ";
        // }
        // out << endl;
        // out.close();
    }

    iil.printToFile(writeFile); // 输出当前倒排索引

    return 0;
}
