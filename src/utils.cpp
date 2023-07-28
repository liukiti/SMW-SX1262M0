#include "utils.hpp"

// https://scanftree.com/programs/c/c-code-to-convert-decimal-to-hexadecimal/
void convertLongInt2HexArray(long int decimalNumber, char *hexaNumber)
{
    long int remainder, quotient;
    int i = 1, j, temp;

    if (decimalNumber < 0 || hexaNumber == NULL)
        return;

    quotient = decimalNumber;
    while (quotient != 0)
    {
        temp = quotient % 16;
        // To convert integer into character
        if (temp < 10)
            temp = temp + 48;
        else
            temp = temp + 55;
        hexaNumber[i++] = temp;
        quotient = quotient / 16;
    }
}

// https://stackoverflow.com/a/35452093
uint8_t *convertHexString2HexArray(char *string, size_t stringLen, uint8_t *arrayLenOrIndex)
{
    *arrayLenOrIndex = 0;

    if (string == NULL)
        return NULL;

    if ((stringLen % 2) != 0) // must be even
        return NULL;

    size_t dlength = stringLen / 2;

    uint8_t *data = (uint8_t *)malloc(dlength);
    memset(data, 0, dlength);

    size_t index = 0;
    while (index < stringLen)
    {
        char c = string[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else
        {
            *arrayLenOrIndex = index;
            free(data);
            return NULL;
        }

        data[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }
    *arrayLenOrIndex = dlength;
    return data;
}

// https://stackoverflow.com/a/36505819
uint8_t dallas_crc8(const uint8_t *pdata, const uint32_t size)
{

    uint8_t crcr = 0;
    for (uint32_t i = 0; i < size; ++i)
    {
        uint8_t inbyte = pdata[i];
        for (uint8_t j = 0; j < 8; ++j)
        {
            uint8_t mix = (crcr ^ inbyte) & 0x01;
            crcr >>= 1;
            if (mix)
                crcr ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crcr;
}

// https://quescol.com/interview-preparation/remove-character-from-string-c
void removeChar(char *str, char charToRemmove)
{
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == charToRemmove)
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
}