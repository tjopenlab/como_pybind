/*
g++ testBreakSignature.cpp
*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <assert.h>

int getOneType(const char *str, char *buf);
void breakSignature(const char *str) {
    char c = *str;
    char buf[256];

    while (c != '\0') {
        int len = getOneType(str, buf);
        if (len == 0)
            break;
        //printf("len:%d, %s\n", len, buf);
        std::string str_ = std::string(buf);
        std::cout << str_ << std::endl;
        str += len;
        c = *str;
    }
}

int getOneType(const char *str, char *buf) {
    char c = *str;
    if (c != '\0') {
        switch (c) {
            case 'B':   // Byte        B
            case 'S':   // Short       S
            case 'I':   // Integer     I
            case 'J':   // Long        J
            case 'F':   // Float       F
            case 'D':   // Double      D
            case 'C':   // Char        C
            case 'Z':   // Boolean     Z
            case 'T':   // String      T
            case 'H':   // HANDLE      H
            case 'E':   // ECode       E
            case 'K':   // CoclassID   |     K
            case 'M':   // ComponentID |     M
            case 'U': { // InterfaceID |     U
                buf[0] = c;
                buf[1] = '\0';
                str++;
                break;
            }
            case '[': { // Array       [
                buf[0] = c;
                str++;
                int len = getOneType(str, buf + 1);
                if (len == 0)
                    buf[1] = '\0';
                break;
            }
            case 'R':   // Triple      R
            case 'P':   // Pointer     *
            case '&': { // Reference   &
                buf[0] = c;
                str++;
                buf[1] = *str;
                buf[2] = '\0';
                str++;
                break;
            }
            case 'L': { // Interface   | Lxx/xx;
                        // Enum    Lxx/xx;
                int i = 0;
                str++;
                c = *str;
                while ((c != ';') && (c != '\0') && (i < 256)) {
                    buf[i++] = c;
                    str++;
                    c = *str;
                }
                if (c == ';')
                    str++;
                break;
            }
            default:
                //assert(false);
                buf[0] = '\0';
                return 0;
        }
        c = *str;
    }
    else
        return 0;

    return strlen(buf);
}

int main()
{
    breakSignature("[[[JBSTLabc/def/kk;");
}
