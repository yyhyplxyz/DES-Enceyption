//
// Created by 杨元昊 on 2018/11/4.
//

#include "DES.h"
#include "stdio.h"
#include "string.h"
#include "memory.h"


int main()
{
    char text[]="The Test of DES !\n";

    char key[]="Tsinghua ",buf[255];

    memset(buf, 0, sizeof(buf));
    strcpy(buf, text);
    puts("\n 加密前文本:");
    puts(buf);
    printf("加密前文本长度：%d\n",sizeof(text));

    puts("\n 密钥:");
    puts(key);
    printf("密钥文本长度：%d\n",sizeof(key));
    Using_DES(buf, buf, sizeof(text), sizeof(key), key, ENCRYPTION);
    puts("\n 加密后:");
    puts(buf);

    Using_DES(buf, buf, sizeof(text),sizeof(key), key, DECRYPTION);
    puts("\n 解密后文本:");
    puts(buf);
    getchar();
    return 0;
}