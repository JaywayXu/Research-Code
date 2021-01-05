// 实现一个简单的汇编器
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

enum BinIns;

// 二进制指令结构体
// 指令码+操作数
struct Instruction
{
    BinIns op;  // 指令码只占一个字节
    int    arg; // 操作数，占四个字节
};

// 枚举类型的二进制指令集
enum BinIns
{
    binHalt, binIn, binOut, binAdd, binSub, binMul, binDiv,
    binDup,
    binLd, binSt, binLdc, binJlt, binJle, binJgt, binJge, binJeq, binJne, binJmp,
    binInvalid
};

// 初始化汇编指令集
void InitAssembleInstructions(vector<string>& assIns)
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
// 指令-参数个数
void InitInstrctionArgNumber(map<BinIns, int>& insArgNum)
{
    insArgNum.clear();

    insArgNum[binHalt] = 0;
    insArgNum[binIn]   = 0;
    insArgNum[binOut]  = 0;
    insArgNum[binAdd]  = 0;
    insArgNum[binSub]  = 0;
    insArgNum[binMul]  = 0;
    insArgNum[binDiv]  = 0;

    insArgNum[binDup]  = 0;

    insArgNum[binLd]   = 0;
    insArgNum[binSt]   = 0;

    insArgNum[binLdc]  = 1;
    insArgNum[binJlt]  = 1;
    insArgNum[binJle]  = 1;
    insArgNum[binJgt]  = 1;
    insArgNum[binJge]  = 1;
    insArgNum[binJeq]  = 1;
    insArgNum[binJne]  = 1;
    insArgNum[binJmp]  = 1;

    insArgNum[binInvalid] = 1;
}

// 建立汇编指令到二进制指令的映射
// 初始化
void InitAssembleToBinary(const vector<string>& assIns, map<string, BinIns>& assToBin)
{
    assToBin.clear();
    for (auto i = 0; i != assIns.size(); ++i)
    {
        // assIns和BinIns的指令次序一致
        assToBin[assIns[i]] = static_cast<BinIns>(i);
    }
}

// 读入汇编指令
void ReadAssemble(vector<string>& ass)
{
    ass.clear();
    string line;
    while (getline(cin, line))
    {
        ass.push_back(line);
    }
}

// 显示
void Display(const vector<string>& bar)
{
    for (auto i = 0; i != bar.size(); ++i)
    {
        cout << bar[i] << endl;
    }
}

string StringToUpper(const string& str)
{
    string ret;
    for (auto i = 0; i != str.size(); ++i)
    {
        ret += toupper(str[i]);
    }
    return ret;
}

void AssembleToBinary(const vector<string>& ass,
                      vector<Instruction>& bin,
                      const map<string, BinIns>& assToBin,
                      map<BinIns, int>& insArgNum)
{
    string assline;
    // 将ass汇总
    for (auto i = 0; i != ass.size(); ++i)
    {
        assline += StringToUpper(ass[i]) + '\t';
    }

    cout << assline << endl;

    istringstream sin(assline);
    string strOp, strArg;
    Instruction ins;
    BinIns op;
    int    arg;
    while (sin >> strOp)
    {
        auto cit = assToBin.find(strOp);
        if (cit == assToBin.end())
        {
            // 没有找到对应的指令码
            // 忽略处理
            ;
            break;
        }
        op = cit->second;
        // insArgNum为非const型
        // assToBin const型保障了insArgNum[]不会存在更新的情况
        int argNum = insArgNum[op];
        if (argNum > 0)
        {
            sin >> strArg;
            arg = atoi(strArg.c_str());
        }
        else
        {
            arg = 0;
        }
        ins.op = op;
        ins.arg = arg;
        bin.push_back(ins);
    }
}

string IntToString(int n, int sizeofbytes)
{
    string ret;
    ret.resize(sizeofbytes * 8, '0');
    for (int i = ret.size() - 1; i >= 0 && n != 0; --i, n /= 2)
    {
        ret[i] = n % 2 + '0';
    }
    return ret;
}

void OutputBinary(const vector<Instruction>& bin,
                  const map<BinIns, int>& insArgNum)
{
    for (auto i = 0; i != bin.size(); ++i)
    {
        cout << bin[i].op;
        cout << '\t' << IntToString(bin[i].op, 1);
        auto cit = insArgNum.find(bin[i].op);
        if (cit == insArgNum.end())
        {
            // 如果没有找到
            // 不做处理
            ;
            break;
        }
        if (cit->second > 0)
        {
            cout << '\t' << bin[i].arg;
            cout << '\t' << IntToString(bin[i].arg, 4);
        }
        cout << endl;
    }
}

int main()
{
    // 汇编指令集
    vector<string> assIns;
    InitAssembleInstructions(assIns);

    // 二进制指令-操作数个数
    map<BinIns, int> insArgNum;
    InitInstrctionArgNumber(insArgNum);

    // 汇编指令到二进制的映射
    map<string, BinIns> assToBin;
    InitAssembleToBinary(assIns, assToBin);

    vector<string> ass; // 保持读入的汇编指令
    ReadAssemble(ass);

    cout << endl;
    Display(ass);
    cout << endl;

    vector<Instruction> bin; // 保存二进制指令
    AssembleToBinary(ass, bin, assToBin, insArgNum);

    OutputBinary(bin, insArgNum);

    cout << endl;

    return 0;
}