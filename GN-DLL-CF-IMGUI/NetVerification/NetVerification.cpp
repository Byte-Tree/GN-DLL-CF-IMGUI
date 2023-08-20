#include "NetVerification.h"
SOCKET  全_验证通讯::通讯句柄; INT32 全_验证通讯::剩余时间;

void char_2_Hex(char* Char, char* Hex)
{
    int length = (int)strlen(Char);
    for (int i = 0; i < length; i++)
    {
        int tmp = int(Char[i]);
        if (Char[i] < 0)
            tmp = (-1) * Char[i] + 128;
        int high = tmp / 16;
        int low = tmp % 16;
        char HIHG;
        char LOW;

        if (high >= 10)
            HIHG = char(high - 10 + 65);
        else
            HIHG = char(high + 48);

        if (low >= 10)
            LOW = char(low - 10 + 65);
        else
            LOW = char(low + 48);

        Hex[2 * i] = HIHG;
        Hex[2 * i + 1] = LOW;
    }
}

//16 -> char 
void Hex_2_char(char* Hex, char* Char)
{
    int length = (int)strlen(Hex) / 2;
    for (int i = 0; i < length; i++)
    {
        int high;
        int low;
        if (int(Hex[2 * i]) >= 65)
            high = int(Hex[2 * i] - 65 + 10);
        else
            high = int(Hex[2 * i] - 48);

        if (int(Hex[2 * i + 1]) >= 65)
            low = int(Hex[2 * i + 1] - 65 + 10);
        else
            low = int(Hex[2 * i + 1] - 48);

        Char[i] = char(high * 16 + low);
    }
}

char* RC4(char* C, char* key)
{
    int S[256];
    int T[256];

    int  count = 0;
    count = (int)strlen(key);

    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
        int tmp = i % count;
        T[i] = key[tmp];
    }

    int j = 0;

    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + T[i]) % 256;
        int tmp;
        tmp = S[j];
        S[j] = S[i];
        S[i] = tmp;
    }

    int length = 0;
    length = (int)strlen(C);

    int i;
    i = 0, j = 0;

    for (int p = 0; p < length; p++)
    {

        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        int tmp;
        tmp = S[j];
        S[j] = S[i];
        S[i] = tmp;

        int k = S[(S[i] + S[j]) % 256];
        C[p] = C[p] ^ k;
    }

    return C;
}

/**
 * 截取str后的元素
 * @param stream 待截取字符串
 * @param str 截取定位字符串
 * @return
 */
static auto cutNext(string stream, const string& str) {
    int nPos = (int)stream.find(str);

    if (nPos != -1) {
        stream = stream.substr(nPos + str.size(), stream.size());
    }
    return stream;
}

/**
 * 截取str前的元素
 * @param stream 待截取字符串
 * @param str 截取定位字符串
 * @return
 */
static auto cutPre(string stream, const string& str) {
    int nPos = (int)stream.find(str);
    if (nPos != -1) {
        stream = stream.substr(0, nPos);
    }
    return stream;
}

BOOL 全_验证通讯::TCP_断开()
{
    if (closesocket(通讯句柄) != -1) { return TRUE; }//关闭套接字连接
    return FALSE;
}

BOOL 全_验证通讯::TCP_连接(const char* ip, INT32 端口)
{

    sockaddr_in ServerAddress;
    WSADATA  v1;

    if (通讯句柄 > 0)
    {
        closesocket(通讯句柄); //关闭套接字连接
        return FALSE;
    }
    //WSAStartup(MAKEWORD(2, 2), &v1);
    if (WSAStartup(257, &v1) == -1) { return FALSE; }
    通讯句柄 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建套接字
    if (通讯句柄 == -1) { return FALSE; }

    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(端口);
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(ip);
    //inet_pton(AF_INET, ip, (void*)&ServerAddress.sin_addr.S_un.S_addr);

    if (connect(通讯句柄, (sockaddr*)&ServerAddress, sizeof(sockaddr_in)) == -1)
    {
        closesocket(通讯句柄);
        通讯句柄 = 0;
        return FALSE;
    }

    return TRUE;
}

BOOL 全_验证通讯::TCP_发送(const char* 内容)
{
    return (send(通讯句柄, 内容, (int)strlen(内容), 0) > 0);
}

BOOL 全_验证通讯::TCP_接收(char* 接收数据)
{
    INT32 通讯返回;



    通讯返回 = recv(通讯句柄, 接收数据, 1024, NULL);
    if (通讯返回 == SOCKET_ERROR || 通讯返回 == NULL || 通讯返回 == 1024)
    {
        Sleep(1000);
        通讯返回 = recv(通讯句柄, 接收数据, 1024, NULL);
        if (通讯返回 == SOCKET_ERROR || 通讯返回 == NULL || 通讯返回 == 1024)
        {
            //打印文本("唯一机器码 - 通讯返回:%d", 通讯返回);
            return FALSE;
        }
    }
    return TRUE;


}

string 全_验证通讯::转换时间(INT32 秒数)
{
    string 返回文本;
    string 计算文本;

    计算文本 = std::to_string(秒数 / 86400);
    返回文本 = 计算文本 + "天";

    计算文本 = std::to_string((秒数 % 86400) / 3600);
    返回文本 = 返回文本 + 计算文本 + "小时";

    计算文本 = std::to_string((秒数 % 86400 % 3600) / 60);
    返回文本 = 返回文本 + 计算文本 + "分";

    计算文本 = std::to_string(秒数 % 86400 % 3600 % 60);
    返回文本 = 返回文本 + 计算文本 + "秒";
    //天.append(临时文本);
    return 返回文本;
}

BOOL 全_验证通讯::验证_初始化(const char* ip, INT32 端口)
{
    if (TCP_连接(ip, 端口) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL 全_验证通讯::验证_卡登录(string 卡号)
{
  //  VMProtectBeginMutation("验证_卡登录");

    char* 接收数据 = new char[1024]; char AES临时[200];
    string 临时文本, 临时转换;
    int 自进程ID, 记录时间, 计算时间;
    string 剩余字符, 文本左边; LPCSTR 写出数据; LPCSTR 配置名称;
    SYSTEMTIME time;
    //===========================================================
    自进程ID = GetCurrentProcessId();
    自进程ID = (自进程ID + 188) / 2;
    //===========================================================
    记录时间 = 全_验证通讯::整数配置("time");//先读取记录的时间
    GetLocalTime(&time);
    计算时间 = (time.wDay + 88) * 2;
    临时转换 = std::to_string(计算时间);
    写出数据 = 临时转换.c_str();
    配置名称 = "time";
    全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次

    if (记录时间 == 0)
    {
        记录时间 = (time.wDay - 1 + 88) * 2;//第一次使用
    }
    //===========================================================记录时间 = 857857 跳过扣点
    string 分隔符 = "|";
    临时文本 = ("Cverification|") + 卡号 + 分隔符 + std::to_string(记录时间) + 分隔符 + std::to_string(自进程ID);
    strcpy(AES临时, 临时文本.c_str());


    if (TCP_发送(AES临时) == FALSE)
    {
        临时转换 = std::to_string(10);
        写出数据 = 临时转换.c_str();
        配置名称 = ("bool");
        全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
        return NULL;
    }
    else
    {
        Sleep(500);
    }
    if (TCP_接收(接收数据) == FALSE)
    {
        临时转换 = std::to_string(10);
        写出数据 = 临时转换.c_str();
        配置名称 = ("bool");
        全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
        return NULL;
    }
    TCP_断开();
    if (strlen(接收数据) == 0)
    {
        临时转换 = std::to_string(10);
        写出数据 = 临时转换.c_str();
        配置名称 = ("bool");
        全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
        return NULL;
    }
    else
    {
        if (strlen(接收数据) == 0)//非法跳转
        {
            临时转换 = std::to_string(10);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;
        }
        剩余字符 = 接收数据;

        int 文本位置 = (int)剩余字符.find("|");
        文本左边 = 剩余字符.substr(0, 文本位置);
        剩余字符 = cutNext(剩余字符, "|");

        if (文本左边 == ("1002"))
        {
            临时转换 = std::to_string(2);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;
        }
        if (文本左边 == ("1003"))
        {
            临时转换 = std::to_string(3);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;
        }
        if (文本左边 == ("1004"))
        {
            临时转换 = std::to_string(4);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;
        }
        if (文本左边 == ("1005"))
        {
            临时转换 = std::to_string(5);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;
        }
        if (文本左边 == ("1006"))
        {

            临时转换 = std::to_string(6);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;
        }
        if (文本左边 == ("1007"))
        {
            临时转换 = std::to_string(7);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;

        }
        if (文本左边 == ("1008"))
        {
            临时转换 = std::to_string(8);
            写出数据 = 临时转换.c_str();
            配置名称 = ("bool");
            全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
            return NULL;

        }
        if (文本左边 == ("1001"))
        {

            文本位置 = (int)剩余字符.find(分隔符);
            文本左边 = 剩余字符.substr(0, 文本位置);
            剩余字符 = cutNext(剩余字符, 分隔符);
            自进程ID = 自进程ID + 998 * 2;
            if (文本左边 != std::to_string(自进程ID))//返回数据::进程验证失败
            {
                TerminateProcess((HANDLE)-1, 0);
                return NULL;
            }

            文本位置 = (int)剩余字符.find(分隔符);
            if (文本位置 != 0)
            {
                文本左边 = 剩余字符.substr(0, 文本位置);
                剩余时间 = atoi(文本左边.c_str());

                临时转换 = std::to_string(1);
                写出数据 = 临时转换.c_str();
                配置名称 = ("bool");
                全_验证通讯::写配置项(配置名称, 写出数据);//再记录此次
                return TRUE;
            }
            else
            {
                TerminateProcess((HANDLE)-1, 0);
                return NULL;
            }

        }
        else
        {
            TerminateProcess((HANDLE)-1, 0);
            return NULL;
        }
    }
   // VMProtectEnd();
    return NULL;
}

BOOL 全_验证通讯::写配置项(LPCSTR lpKeyName, LPCSTR lpString)
{
    return WritePrivateProfileStringA("Configure", lpKeyName, lpString, "c:\\User.ini");
}

INT32 全_验证通讯::整数配置(LPCSTR lpKeyName)
{
    char* szBuffer = new char[MAX_PATH];
    GetPrivateProfileStringA("Configure", lpKeyName, "", szBuffer, MAX_PATH, "c:\\User.ini");
    int result;
    result = GetPrivateProfileIntA("Configure", lpKeyName, 0, "c:\\User.ini");
    return result;
}

string 全_验证通讯::文本配置(LPCSTR lpKeyName)
{
    char* szBuffer = new char[MAX_PATH];
    GetPrivateProfileStringA("Configure", lpKeyName, "Key", szBuffer, MAX_PATH, "c:\\User.ini");
    return szBuffer;
}

