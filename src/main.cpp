
#define _GLIBCXX_USE_NANOSLEEP

#include "main.hpp"
#include <algorithm>

/*
    What I know:
        Cipher 1:
            is a shift cipher. Offset 13, so basically ROT-13!

        Cipher 2:
            is not a regular shift cipher.
            is a Vigenere cipher. Key length of 9!

        Cipher 3:
            is not a regular shift cipher.
            does not appear to be a Vigenere cipher, checked keylengths [1-50]

            could be columnar transposition
            could be monoalphabetic substitution

        Cipher 4:
            is not a regular shift cipher.
            does not appear to be a Vigenere cipher, checked keylengths [1-50]

            could be columnar transposition
            could be monoalphabetic substitution

Ceasar cipher - no cipher
shift cipher - Cipher 1, no other cipher
monoalphabetic substitution cipher
one-time-pad - basically uncrackable without finding secret key
columnar transposition - of those, could be rail cipher or regular
vignere cipher - Cipher 2, no other cipher

*/

int main(int argc, char** argv)
{
    auto cipher1lower = toLowerCase(cipher1);
    auto cipher2lower = toLowerCase(cipher2);
    auto cipher3lower = toLowerCase(cipher3);
    auto cipher4lower = toLowerCase(cipher4);
//"wecrlteerdsoeefeaocaivden"
    std::cout << crackRailCipher("wireeedseeeacaecvdltnrofo") << std::endl;
/*
    std::cout << "Cipher 1, attempted crack of shift cipher:" << std::endl;
    std::cout << cipher1lower << std::endl;
    std::cout << crackShiftCipher(cipher1lower) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;*/
/*
    std::cout << "Cipher 2, attempted crack of Vigenere cipher:" << std::endl;
    std::cout << crackVigenereCipher(cipher2lower) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;*/
/*
    std::cout << "Cipher 4, attempted crack of vigenere cipher:" << std::endl;
    std::cout << crackVigenereCipher(cipher4lower) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;*/
}



std::string crackShiftCipher(const std::string& ciphertext)
{
    float bestDeviation = 4096;
    std::string currentGuess;

    for (std::size_t shift = 0; shift <= 26; shift++)
    {
        std::string copy(ciphertext);
        for (std::size_t j = 0; j < ciphertext.size(); j++)
            copy[j] = (ciphertext[j] - 97 + shift) % 26 + 97;

        float dev = getDeviationFromEnglish(copy);
        if (dev < bestDeviation)
        {
            bestDeviation = dev;
            currentGuess = copy;
        }
    }

    return currentGuess;
}



std::string crackVigenereCipher(const std::string& ciphertext)
{
    float bestDeviation = 4096;
    std::string currentGuess;

    for (std::size_t keyLength = 1; keyLength <= 25; keyLength++)
    {
        std::string whole(ciphertext); //will be overridden

        for (std::size_t offset = 0; offset < keyLength; offset++)
        {
            std::string subStr;
            for (std::size_t j = offset; j < ciphertext.size(); j += keyLength)
                subStr += ciphertext[j];

            auto cracked = crackShiftCipher(subStr);
            for (std::size_t j = 0; j < subStr.size(); j++)
                whole[j * keyLength + offset] = cracked[j];
        }

        float dev = getDeviationFromEnglish(whole);
        if (dev < bestDeviation)
        {
            bestDeviation = dev;
            currentGuess = whole;

            std::cout << std::endl;
            std::cout << "Better guess! Keylength of " << keyLength << std::endl;
            std::cout << "Deviation from English: " << dev << std::endl;
            std::cout << currentGuess << std::endl;
        }
    }

    return currentGuess;
}

//wearediscoveredfleeatonce
//wecrlteerdsoeefeadcaivden


std::string crackRailCipher(const std::string& ciphertext)
{
    int maxKeyLength = 40;
    if (maxKeyLength >= ciphertext.size())
        maxKeyLength = ciphertext.size();

    //for (int keyLength = 2; keyLength < maxKeyLength; keyLength++)
    int keyLength = 4;
    {
        std::string plaintext(ciphertext);

        int cipherIndex = 0;
        for (int offset = 0; offset < keyLength; offset++)
        {
            int diff = (keyLength - 1) * 2 - offset * 2;

            if (offset == keyLength - 1)
                diff = (keyLength - 1) * 2;
            std::cout << diff << std::endl;
            for (int j = offset; j < ciphertext.size(); j += diff)
            {
                plaintext[j] = ciphertext[cipherIndex];
                cipherIndex++;
            }
        }

        std::cout << cipherIndex << ", " << ciphertext.size() << std::endl;

        std::cout << keyLength << ": " << plaintext << std::endl;
    }

    return "";
}



std::string toLowerCase(const std::string& str)
{
    std::string copy(str);
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return copy;
}



float getDeviationFromEnglish(const std::string& str)
{
    FrequencyMap map;

    for (std::size_t j = 0; j < str.size(); j++)
        map[str[j]] = map[str[j]] + 1;

    auto ENGLISH = getEnglishFrequencyMap();
    float deviation = 0;
    for (auto& x: map)
    {
        float diff = x.second / str.size() - ENGLISH[x.first] / 100;
        deviation += diff * diff;
    }

    return deviation;
}



FrequencyMap getEnglishFrequencyMap()
{
    static FrequencyMap english;

    if (!english.empty())
        return english;

    english['a'] = 8.167f;
    english['b'] = 1.492f;
    english['c'] = 2.783f;
    english['d'] = 4.253f;
    english['e'] = 12.702f;
    english['f'] = 2.228f;
    english['g'] = 2.015f;
    english['h'] = 6.094f;
    english['i'] = 6.966f;
    english['j'] = 0.153f;
    english['k'] = 0.772f;
    english['l'] = 4.025f;
    english['m'] = 2.406f;
    english['n'] = 6.749f;
    english['o'] = 7.507f;
    english['p'] = 1.929f;
    english['q'] = 0.095f;
    english['r'] = 5.987f;
    english['s'] = 6.327f;
    english['t'] = 9.056f;
    english['u'] = 2.758f;
    english['v'] = 0.978f;
    english['w'] = 2.360f;
    english['x'] = 0.150f;
    english['y'] = 1.974f;
    english['z'] = 0.075f;

    return english;
}
