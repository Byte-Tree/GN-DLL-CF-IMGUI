#include "NetVerification.h"
SOCKET  ȫ_��֤ͨѶ::ͨѶ���; INT32 ȫ_��֤ͨѶ::ʣ��ʱ��;

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
 * ��ȡstr���Ԫ��
 * @param stream ����ȡ�ַ���
 * @param str ��ȡ��λ�ַ���
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
 * ��ȡstrǰ��Ԫ��
 * @param stream ����ȡ�ַ���
 * @param str ��ȡ��λ�ַ���
 * @return
 */
static auto cutPre(string stream, const string& str) {
    int nPos = (int)stream.find(str);
    if (nPos != -1) {
        stream = stream.substr(0, nPos);
    }
    return stream;
}

BOOL ȫ_��֤ͨѶ::TCP_�Ͽ�()
{
    if (closesocket(ͨѶ���) != -1) { return TRUE; }//�ر��׽�������
    return FALSE;
}

BOOL ȫ_��֤ͨѶ::TCP_����(const char* ip, INT32 �˿�)
{

    sockaddr_in ServerAddress;
    WSADATA  v1;

    if (ͨѶ��� > 0)
    {
        closesocket(ͨѶ���); //�ر��׽�������
        return FALSE;
    }
    //WSAStartup(MAKEWORD(2, 2), &v1);
    if (WSAStartup(257, &v1) == -1) { return FALSE; }
    ͨѶ��� = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//�����׽���
    if (ͨѶ��� == -1) { return FALSE; }

    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(�˿�);
    ServerAddress.sin_addr.S_un.S_addr = inet_addr(ip);
    //inet_pton(AF_INET, ip, (void*)&ServerAddress.sin_addr.S_un.S_addr);

    if (connect(ͨѶ���, (sockaddr*)&ServerAddress, sizeof(sockaddr_in)) == -1)
    {
        closesocket(ͨѶ���);
        ͨѶ��� = 0;
        return FALSE;
    }

    return TRUE;
}

BOOL ȫ_��֤ͨѶ::TCP_����(const char* ����)
{
    return (send(ͨѶ���, ����, (int)strlen(����), 0) > 0);
}

BOOL ȫ_��֤ͨѶ::TCP_����(char* ��������)
{
    INT32 ͨѶ����;



    ͨѶ���� = recv(ͨѶ���, ��������, 1024, NULL);
    if (ͨѶ���� == SOCKET_ERROR || ͨѶ���� == NULL || ͨѶ���� == 1024)
    {
        Sleep(1000);
        ͨѶ���� = recv(ͨѶ���, ��������, 1024, NULL);
        if (ͨѶ���� == SOCKET_ERROR || ͨѶ���� == NULL || ͨѶ���� == 1024)
        {
            //��ӡ�ı�("Ψһ������ - ͨѶ����:%d", ͨѶ����);
            return FALSE;
        }
    }
    return TRUE;


}

string ȫ_��֤ͨѶ::ת��ʱ��(INT32 ����)
{
    string �����ı�;
    string �����ı�;

    �����ı� = std::to_string(���� / 86400);
    �����ı� = �����ı� + "��";

    �����ı� = std::to_string((���� % 86400) / 3600);
    �����ı� = �����ı� + �����ı� + "Сʱ";

    �����ı� = std::to_string((���� % 86400 % 3600) / 60);
    �����ı� = �����ı� + �����ı� + "��";

    �����ı� = std::to_string(���� % 86400 % 3600 % 60);
    �����ı� = �����ı� + �����ı� + "��";
    //��.append(��ʱ�ı�);
    return �����ı�;
}

BOOL ȫ_��֤ͨѶ::��֤_��ʼ��(const char* ip, INT32 �˿�)
{
    if (TCP_����(ip, �˿�) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL ȫ_��֤ͨѶ::��֤_����¼(string ����)
{
  //  VMProtectBeginMutation("��֤_����¼");

    char* �������� = new char[1024]; char AES��ʱ[200];
    string ��ʱ�ı�, ��ʱת��;
    int �Խ���ID, ��¼ʱ��, ����ʱ��;
    string ʣ���ַ�, �ı����; LPCSTR д������; LPCSTR ��������;
    SYSTEMTIME time;
    //===========================================================
    �Խ���ID = GetCurrentProcessId();
    �Խ���ID = (�Խ���ID + 188) / 2;
    //===========================================================
    ��¼ʱ�� = ȫ_��֤ͨѶ::��������("time");//�ȶ�ȡ��¼��ʱ��
    GetLocalTime(&time);
    ����ʱ�� = (time.wDay + 88) * 2;
    ��ʱת�� = std::to_string(����ʱ��);
    д������ = ��ʱת��.c_str();
    �������� = "time";
    ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�

    if (��¼ʱ�� == 0)
    {
        ��¼ʱ�� = (time.wDay - 1 + 88) * 2;//��һ��ʹ��
    }
    //===========================================================��¼ʱ�� = 857857 �����۵�
    string �ָ��� = "|";
    ��ʱ�ı� = ("Cverification|") + ���� + �ָ��� + std::to_string(��¼ʱ��) + �ָ��� + std::to_string(�Խ���ID);
    strcpy(AES��ʱ, ��ʱ�ı�.c_str());


    if (TCP_����(AES��ʱ) == FALSE)
    {
        ��ʱת�� = std::to_string(10);
        д������ = ��ʱת��.c_str();
        �������� = ("bool");
        ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
        return NULL;
    }
    else
    {
        Sleep(500);
    }
    if (TCP_����(��������) == FALSE)
    {
        ��ʱת�� = std::to_string(10);
        д������ = ��ʱת��.c_str();
        �������� = ("bool");
        ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
        return NULL;
    }
    TCP_�Ͽ�();
    if (strlen(��������) == 0)
    {
        ��ʱת�� = std::to_string(10);
        д������ = ��ʱת��.c_str();
        �������� = ("bool");
        ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
        return NULL;
    }
    else
    {
        if (strlen(��������) == 0)//�Ƿ���ת
        {
            ��ʱת�� = std::to_string(10);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;
        }
        ʣ���ַ� = ��������;

        int �ı�λ�� = (int)ʣ���ַ�.find("|");
        �ı���� = ʣ���ַ�.substr(0, �ı�λ��);
        ʣ���ַ� = cutNext(ʣ���ַ�, "|");

        if (�ı���� == ("1002"))
        {
            ��ʱת�� = std::to_string(2);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;
        }
        if (�ı���� == ("1003"))
        {
            ��ʱת�� = std::to_string(3);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;
        }
        if (�ı���� == ("1004"))
        {
            ��ʱת�� = std::to_string(4);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;
        }
        if (�ı���� == ("1005"))
        {
            ��ʱת�� = std::to_string(5);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;
        }
        if (�ı���� == ("1006"))
        {

            ��ʱת�� = std::to_string(6);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;
        }
        if (�ı���� == ("1007"))
        {
            ��ʱת�� = std::to_string(7);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;

        }
        if (�ı���� == ("1008"))
        {
            ��ʱת�� = std::to_string(8);
            д������ = ��ʱת��.c_str();
            �������� = ("bool");
            ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
            return NULL;

        }
        if (�ı���� == ("1001"))
        {

            �ı�λ�� = (int)ʣ���ַ�.find(�ָ���);
            �ı���� = ʣ���ַ�.substr(0, �ı�λ��);
            ʣ���ַ� = cutNext(ʣ���ַ�, �ָ���);
            �Խ���ID = �Խ���ID + 998 * 2;
            if (�ı���� != std::to_string(�Խ���ID))//��������::������֤ʧ��
            {
                TerminateProcess((HANDLE)-1, 0);
                return NULL;
            }

            �ı�λ�� = (int)ʣ���ַ�.find(�ָ���);
            if (�ı�λ�� != 0)
            {
                �ı���� = ʣ���ַ�.substr(0, �ı�λ��);
                ʣ��ʱ�� = atoi(�ı����.c_str());

                ��ʱת�� = std::to_string(1);
                д������ = ��ʱת��.c_str();
                �������� = ("bool");
                ȫ_��֤ͨѶ::д������(��������, д������);//�ټ�¼�˴�
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

BOOL ȫ_��֤ͨѶ::д������(LPCSTR lpKeyName, LPCSTR lpString)
{
    return WritePrivateProfileStringA("Configure", lpKeyName, lpString, "c:\\User.ini");
}

INT32 ȫ_��֤ͨѶ::��������(LPCSTR lpKeyName)
{
    char* szBuffer = new char[MAX_PATH];
    GetPrivateProfileStringA("Configure", lpKeyName, "", szBuffer, MAX_PATH, "c:\\User.ini");
    int result;
    result = GetPrivateProfileIntA("Configure", lpKeyName, 0, "c:\\User.ini");
    return result;
}

string ȫ_��֤ͨѶ::�ı�����(LPCSTR lpKeyName)
{
    char* szBuffer = new char[MAX_PATH];
    GetPrivateProfileStringA("Configure", lpKeyName, "Key", szBuffer, MAX_PATH, "c:\\User.ini");
    return szBuffer;
}

