// 实现一个反汇编器
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

// 枚举类型的二进制指令集
enum BinIns
{
    binHalt,
    binIn,
    binOut,
    binAdd,
    binSub,
    binMul,
    binDiv,
    binDup,
    binLd,
    binSt,
    binLdc,
    binJlt,
    binJle,
    binJgt,
    binJge,
    binJeq,
    binJne,
    binJmp,
    binInvalid
};
// 枚举类型说明：
// enum后面定义的是枚举类型名
// 花括号内部是该枚举类型可以取的值

// 二进制指令结构体
// 指令码+操作数
struct Instruction
{
    BinIns op; // 指令码只占一个字节
    int arg;   // 操作数，占四个字节
};

// 初始化汇编指令集
void InitAssembleInstructions(vector<string> &assIns)
{
    assIns.clear();

    assIns.push_back("HALT");
    assIns.push_back("IN");
    assIns.push_back("OUT");
    assIns.push_back("ADD");
    assIns.push_back("SUB");
    assIns.push_back("MUL");
    assIns.push_back("DIV");

    assIns.push_back("DUP");

    assIns.push_back("LD");
    assIns.push_back("ST");
    assIns.push_back("LDC");
    assIns.push_back("JLT");
    assIns.push_back("JLE");
    assIns.push_back("JGT");
    assIns.push_back("JGE");
    assIns.push_back("JEQ");
    assIns.push_back("JNE");
    assIns.push_back("JMP");
}

// 初始化
// 指令-参数个数 映射
void InitInstrctionArgNumber(map<BinIns, int> &insArgNum)
{
    insArgNum.clear();

    insArgNum[binHalt] = 0;
    insArgNum[binIn] = 0;
    insArgNum[binOut] = 0;
    insArgNum[binAdd] = 0;
    insArgNum[binSub] = 0;
    insArgNum[binMul] = 0;
    insArgNum[binDiv] = 0;

    insArgNum[binDup] = 0;

    insArgNum[binLd] = 0;
    insArgNum[binSt] = 0;

    insArgNum[binLdc] = 1;
    insArgNum[binJlt] = 1;
    insArgNum[binJle] = 1;
    insArgNum[binJgt] = 1;
    insArgNum[binJge] = 1;
    insArgNum[binJeq] = 1;
    insArgNum[binJne] = 1;
    insArgNum[binJmp] = 1;

    insArgNum[binInvalid] = 0;
}

// 建立二进制指令到汇编指令的映射
// 初始化
void InitBinaryToAssemble(const vector<string> &assIns /*汇编指令*/, map<BinIns, string> &binToIns /*映射*/)
{
    binToIns.clear();
    for (int i = 0; i != assIns.size(); ++i)
    {
        // assIns和BinIns的指令次序一致
        binToIns[static_cast<BinIns>(i)] = assIns[i];
        //static_cast <type-id>(expression)把expression转换为type-id类型
    }
}

// 读入二进制指令
void ReadBinary(vector<string> &bin)
{
    bin.clear();
    string line;
    cout << "please input the binary code(end with empthy line):" << endl;
    while (getline(cin, line, '\n'))
    {
        if(line.length()==0) break;
        bin.push_back(line);
    }
}

// 显示二进制指令
void Display(const vector<string> &bar)
{
    for (int i = 0; i != bar.size(); ++i)
    {
        cout << bar[i] << endl;
    }
}

// 将读入的二进制指令转换为Instruction形式
void BinaryToAssemble(const vector<string> &bin /*二进制指令*/,
                      vector<string> &ass /*汇编指令*/,
                      const map<BinIns, string> &binToIns /*映射关系*/,
                      map<BinIns, int> &insArgNum /*指令-参数个数 映射*/)
{
    ass.clear();
    string binLine;
    for (int i = 0; i <= bin.size(); ++i)
    {
        binLine += bin[i] + '\t';
    }

    // cout << binLine << endl;

    istringstream sin(binLine);
    string strOp, strArg;
    string op;
    string arg;
    string assIns;
    BinIns opBin;
    while (sin >> strOp)
    {
        opBin = static_cast<BinIns>(atoi(strOp.c_str()));
        auto cit = binToIns.find(opBin);
        if (cit == binToIns.end())
        {
            // 非法二进制指令
            // 忽略处理
            ;
            break;
        }
        op = cit->second;
        int argNum = insArgNum[cit->first];
        if (argNum > 0)
        {
            sin >> strArg;
            arg = strArg;
        }
        else
        {
            arg = "";
        }
        assIns = op + '\t' + arg;
        ass.push_back(assIns);
    }
}

int main()
{
    // 汇编指令集
    vector<string> assIns;
    InitAssembleInstructions(assIns); //初始化汇编指令

    // 二进制指令-参数个数
    map<BinIns, int> insArgNum;
    InitInstrctionArgNumber(insArgNum); //初始化二进制指令的参数个数

    // 二进制到汇编指令的映射
    map<BinIns, string> binToAss;
    InitBinaryToAssemble(assIns, binToAss); //bin->halt-halt

    vector<string> bin; // 保存读入的二进制指令
    ReadBinary(bin);

    vector<string> ass; // 保存转换后的汇编指令
    BinaryToAssemble(bin, ass, binToAss, insArgNum);

    cout << "the decompile ass is: " << endl;
    Display(ass);

    cout << endl;

    return 0;
}