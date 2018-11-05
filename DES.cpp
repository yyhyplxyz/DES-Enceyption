//
// Created by 杨元昊 on 2018/11/4.
//

#include "memory.h"
#include "DES.h"
#include "Settings.h"
//-----------------------------------------------------------------------------------
//以下是各个函数的定义
//-----------------------------------------------------------------------------------
bool Using_DES(char *Out, char *In, long textlen, int keylen,const char *Key, bool Type)
{
    if( !( Out && In && Key && (tex
        return false;
    SETKEY(Key, keylen);
    for(long i=0,j=textlen>>3; i<j; ++i,Out+=8,In+=8)
        DES(Out, In, &SubKey[0], Type); // 1 次 DES

    return true;
}
void ByteToBit(bool *Out, const char *In, int bits)
{
    for(int i=0; i<bits; ++i)
        Out[i] = (In[i>>3]>>(i&7)) & 1;
}
void BitToByte(char *Out, const bool *In, int bits)
{
    memset(Out, 0, bits>>3);
    for(int i=0; i<bits; ++i)
        Out[i>>3] |= In[i]<<(i&7);
}
void CYCLELEFT(bool *In, int len, int loop)
{
    memcpy(T, In, loop);
    memcpy(In, In+loop, len-loop);
    memcpy(In+len-loop, T, loop);
}
void Set_SubKey(SUBKEY_P pskey, const char Key[8])
{
    static bool K[64], *KL=&K[0], *KR=&K[28];
    ByteToBit(K, Key, 64);
    TRANSFORM(K, K, PC1_TABLE, 56);
    for(int i=0; i<16; ++i)
    {
        CYCLELEFT(KL, 28, LOOP_TABLE[i]);
        CYCLELEFT(KR, 28, LOOP_TABLE[i]);
        TRANSFORM((*pskey)[i], K, PC2_TABLE, 48);
    }
}
void SETKEY(const char* Key, int len)
{
    memset(deskey, 0, 24);
    memcpy(deskey, Key, len>24?24:len);
    Set_SubKey(&SubKey[0], &deskey[0]);
}
void S_BOXF(bool Out[32], const bool In[48])
{
    for(char i=0,j,k; i<8; ++i,In+=6,Out+=4)
    {
        j = (In[0]<<1) + In[5];
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4];
        ByteToBit(Out, &S_BOX[i][j][k], 4);
    }
}
void F_FUNCTION(bool In[32], const bool Ki[48])
{
    static bool MR[48];
    TRANSFORM(MR, In, E_TABLE, 48);
    XOR(MR, Ki, 48);
    S_BOXF(In, MR);
    TRANSFORM(In, In, P_TABLE, 32);
}
void TRANSFORM(bool *Out, bool *In, const char *Table, int len)
{
    for(int i=0; i<len; ++i)
        T[i] = In[ Table[i]-1 ];
    memcpy(Out, T, len);
}
void XOR(bool *InA, const bool *InB, int len)
{
    for(int i=0; i<len; ++i)
        InA[i] ^= InB[i];
}
void DES(char Out[8], char In[8], const SUBKEY_P pskey, bool Type)
{
    static bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];
    ByteToBit(M, In, 64);
    TRANSFORM(M, M, IP_TABLE, 64);
    if( Type == ENCRYPTION )
    {
        for(int i=0; i<16; ++i)
        {
            memcpy(tmp, Ri, 32);
            F_FUNCTION(Ri, (*pskey)[i]);
            XOR(Ri, Li, 32);
            memcpy(Li, tmp, 32);
        }
    }
    else
    {
        for(int i=15; i>=0; --i)
        {
            memcpy(tmp, Li, 32);
            F_FUNCTION(Li, (*pskey)[i]);
            XOR(Li, Ri, 32);
            memcpy(Ri, tmp, 32);
        }
    }
    TRANSFORM(M, M, IPF_TABLE, 64);
    BitToByte(Out, M, 64);
}