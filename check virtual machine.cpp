#include "cpuid.h"
#include <windows.h>
#include <bitset>
#include <string>
using namespace std;

//HEX Package

char* hex_package(char* p,int regid)
{
    int nums = 32 - 8;
    char* bin_Package_index = p;
    char bin_Package_buf[32] = { 0 };
    char* bin_Package_buf_p = bin_Package_buf;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            bin_Package_buf_p[j] = bin_Package_index[nums + j];
        }

        nums = nums - 8;
        bin_Package_buf_p = bin_Package_buf_p + 8;

    }

    /* print  ECX EDX register  value
    if (regid == 1)
    {
        cout << "---------ecx---------" << endl;
        for (int i = 0; i < 32; i++)
        {
            if (bin_Package_buf[i] == 0x01)
            {
                cout << cpu_ecx_buf[i] << endl;
            }
        }
    }

    if (regid == 0)
    {
        cout << "---------edx---------" << endl;
        for (int i = 0; i < 32; i++)
        {
            if (bin_Package_buf[i] == 0x01)
            {
                cout << cpu_edx_buf[i] << endl;
            }
        }
    }
    */

    {
        
        {
            if (bin_Package_buf[4] == 0x01)
            {
                MessageBoxW(NULL, L"oh yes", NULL, NULL);
            }
            else
            {
                MessageBoxW(NULL, L"oh no", NULL, NULL);
            }
        }
    }
    return bin_Package_buf;
}

//HEX to BIN
char* hex_to_bin(char* p,int regid)
{
    char* bin_buf = new char(32);
    char* bin_buf_end = bin_buf + 32 - 1;

    char* bin_buf_return = new char(32);

    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 8; i++)
        {
            if ((*(p + j) >> i) & 1)
            {
                *(bin_buf_end--) = 1;
            }
            else
            {
                *(bin_buf_end--) = 0;
            }

        }
    }

    hex_package(bin_buf, regid);
    return bin_buf;

}

static int Cpuid()
{
    unsigned int ecx_buf[1];
    unsigned int edx_buf[1];
    char* ecx_buf_char = new char(4);
    char* edx_buf_char = new char(4);
    char* ecx_bufchar_p = (char*)ecx_buf;
    char* edx_bufchar_p = (char*)edx_buf;

    __asm
    {
        pusha;
        xor eax, eax
            xor ebx, edx
            xor ecx, ecx
            xor edx, edx
            mov eax, 1
            cpuid
            mov ecx_buf, ecx
            mov edx_buf, edx
            popa
    }

    for (int i = 0; i < 4; i++)
    {
        ecx_buf_char[i] = ecx_bufchar_p[i];
        edx_buf_char[i] = edx_bufchar_p[i];
    }


     hex_to_bin(ecx_buf_char,1);
     /*if you print edx ecx all info,Please un comment
     hex_to_bin(edx_buf_char,0);
     */
}

int main()
{
    Cpuid();
}