
#define _GLIBCXX_USE_NANOSLEEP

#include "main.hpp"
#include <algorithm>


int main(int argc, char** argv)
{

    auto cipher1lower = toLowerCase(cipher1);
    std::cout << crackShiftCipher(cipher1lower) << std::endl;
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

    float deviation = 0;
    auto ENGLISH = getEnglishFrequencyMap();
    for (auto& x: map)
    {
        float diff = x.second / str.size() - ENGLISH[x.first];
        deviation += diff;
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
