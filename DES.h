//
// Created by 杨元昊 on 2018/11/4.
//

#ifndef DES_DES_H
#define DES_DES_H
//////////////////////////////////////////////////////////////////////////
// ENCRYPTION:加密,DECRYPTION:解密
enum {ENCRYPTION,DECRYPTION};
//////////////////////////////////////////////////////////////////////////
bool Using_DES(char *Out,char *In,long textlen,int keylen,const char
*Key,bool Type = ENCRYPTION);
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
typedef bool (*SUBKEY_P)[16][48];
//-----------------------------------------------------------------------------------
static void DES(char Out[8], char In[8], const SUBKEY_P pskey, bool Type);//标准 DES 加/解密
static void SETKEY(const char* Key, int len);// 设置密钥
static void Set_SubKey(SUBKEY_P pskey, const char Key[8]);// 设置子密钥
static void F_FUNCTION(bool In[32], const bool Ki[48]);// f 函数完成扩展置换、S-盒代替和 P 盒置换
static void S_BOXF(bool Out[32], const bool In[48]);// S-盒代替函数
static void TRANSFORM(bool *Out, bool *In, const char *Table, int len);// 变换函数
static void XOR(bool *InA, const bool *InB, int len);//异或函数
static void CYCLELEFT(bool *In, int len, int loop);// 循环左移函数
static void ByteToBit(bool *Out, const char *In, int bits);// 字节组转换成位组函数
static void BitToByte(char *Out, const bool *In, int bits);// 位组转换成字节组函数
//-----------------------------------------------------------------------------------
static bool SubKey[1][16][48];// 子密钥
static char T[256], deskey[16];

#endif //DES_DES_H
