
#define _GLIBCXX_USE_NANOSLEEP

#include "main.hpp"
#include <algorithm>

/*
    What I know:
        Cipher 1:
            is a shift cipher. Shift key is 13, so basically ROT-13!

        Cipher 2:
            is not a regular shift cipher.
            is a Vigenere cipher. Key length of 9, key worcester

        Cipher 3:
            is not a regular shift cipher.
            does not appear to be a Vigenere cipher, checked keylengths [1-50]
            does not appear to be a Fence Rail cipher, checked leylengths [1-25]
            has very flat frequencies, suggesting something unusual
                monoalphabetic sub or column transpose couldn't do this
                One-time pad? Vigenere? Vigenere autokey? Hill?
                Variance from English: 0.0282431
                One-time pad is impossible, V autokey nor Hill were listed.
                I'm pretty sure that this is an uncrackable one-time pad.

        Cipher 4:
            is not a regular shift cipher.
            does not appear to be a Vigenere cipher, checked keylengths [1-50]
            does not appear to be a Fence Rail cipher, checked leylengths [1-25]
            has varying frequency distributions, suggesting substitutions
                Monoalphabetic? Columnar transpose? Affine cipher (p28)?
                Variance from English: 0.0521973
                Columnar transposition leaves normal statistical distribution
                Thus, this is a regular monoalphabetic cipher.
                I wish this cipher were longer, would make cracking easier.

Hints and notes:
Ceasar cipher - no cipher, rough distribution graph
shift cipher - Cipher 1, no other cipher, rough distribution graph
monoalphabetic substitution cipher, rough distribution graph
one-time-pad - basically uncrackable without finding secret key, flat distrib
columnar transposition - rail or regular, rough distribution graph
vignere cipher - Cipher 2, no other cipher, flat distribution

*/

int main(int argc, char** argv)
{
    auto cipher1lower = toLowerCase(cipher1);
    auto cipher2lower = toLowerCase(cipher2);
    auto cipher3lower = toLowerCase(cipher3);
    auto cipher4lower = toLowerCase(cipher4);

    std::cout << "Cipher 1, attempted crack of shift cipher:" << std::endl;
    std::cout << cipher1lower << std::endl;
    std::cout << crackShiftCipher(cipher1lower) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    /*
        letmebeginbysayingthankstoallyouwhovetraveledfromfarandwidetobravethecoldtodayweallmadethisjourneyforareasonitshumblingbutinmyheartiknowyoudidntcomeherejustformeyoucameherebecauseyoubelieveinwhatthiscountrycanbeinthefaceofwaryoubelievetherecanbepeaceinthefaceofdespairyoubelievetherecanbehopeinthefaceofapoliticsthatsshutyououtthatstoldyoutosettlethatsdividedusfortoolongyoubelievewecanbeonepeoplereachingforwhatspossiblebuildingthatmoreperfectunionthatsthejourneywereontodaybutletmetellyouhowicametobehereasmostofyouknowiamnotanativeofthisgreatstateimovedtoillinoisovertwodecadesagoiwasayoungmanthenjustayearoutofcollegeiknewnooneinchicagowaswithoutmoneyorfamilyconnectionsbutagroupofchurcheshadofferedmeajobasacommunityorganizerforayearandiacceptedthejobsightunseenmotivatedthenbyasinglesimplepowerfulideathatimightplayasmallpartinbuildingabetteramericamyworktookmetosomeofchicagospoorestneighborhoodsijoinedwithpastorsandlaypeopletodealwithcommunitiesthathadbeenravagedbyplantclosingsisawthattheproblemspeoplefacedwerents
    */

    std::cout << "Cipher 2, attempted crack of Vigenere cipher:" << std::endl;
    std::cout << cipher2lower << std::endl;
    std::cout << crackVigenereCipher(cipher2lower) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    /*
        callmeishmaelsomeyearsagonevermindhowlongpreciselyhavinglittleornomoneyinmypurseandnothingparticulartointerestmeonshoreithoughtiwouldsailaboutalittleandseethewaterypartoftheworlditisawayihaveofdrivingoffthespleenandregulatingthecirculationwheneverifindmyselfgrowinggrimaboutthemouthwheneveritisadampdrizzlynovemberinmysoulwheneverifindmyselfinvoluntarilypausingbeforecoffinwarehousesandbringinguptherearofeveryfuneralimeetandespeciallywhenevermyhyposgetsuchanupperhandofmethatitrequiresastrongmoralprincipletopreventmefromdeliberatelysteppingintothestreetandmethodicallyknockingpeopleshatsofftheniaccountithightimetogettoseaassoonasicanthisismysubstituteforpistolandballwithaphilosophicalflourishcatothrowshimselfuponhisswordiquietlytaketotheshipthereisnothingsurprisin
    */

    /*
    std::cout << "Cipher 4, attempted crack of vigenere cipher:" << std::endl;
    std::cout << crackVigenereCipher(cipher4lower) << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    //std::cout << crackRailCipher("wireeedseeeacaecvdltnrofo") << std::endl;

    //std::cout << getDeviationFromEnglish(cipher3lower) << std::endl;
    //std::cout << getDeviationFromEnglish(cipher4lower) << std::endl;

    std::cout << crackVigenereCipher(cipher3lower) << std::endl;
    */
}



/*
    Cracks the ciphertext via brute-force.
    It tries all 26 combinations, and returns the shift that is
    most statistically similar to English's letter frequencies.
*/
std::string crackShiftCipher(const std::string& ciphertext)
{
    float bestDeviation = 4096;
    std::string currentGuess;
    int best = -1;

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
            best = shift;
        }
    }

    return currentGuess;
}



/*
    Cracks the Vigenere cipher by looking at every keyLength-th letter,
    and then cracking that shift cipher. Since the key repeats, there is
    statistical information that is repeated in the ciphertext. This method
    cracks each character of the key in turn, and then returns the most
    statistically-likely plaintext. Note that this doesn't always lead to the
    best plaintext, but by printing off the intermediate better guesses,
    the actual plaintext can be revealed.
*/
std::string crackVigenereCipher(const std::string& ciphertext)
{
    float bestDeviation = 4096;
    std::string currentGuess;

    for (std::size_t keyLength = 1; keyLength <= 20; keyLength++)
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



/*
    Cracks the rail cipher by just brute-forcing the key.
    There's no statistics involved in this cipher, so its just a matter
    of rearranging the ciphertext to reveal the plaintext.
*/
std::string crackRailCipher(const std::string& ciphertext)
{
    int maxKeyLength = 40;
    if (maxKeyLength >= ciphertext.size())
        maxKeyLength = ciphertext.size();

    for (int keyLength = 2; keyLength < maxKeyLength; keyLength++)
    {
        std::string plaintext(ciphertext);

        int cipherIndex = 0;
        for (int offset = 0; offset < keyLength; offset++)
        {
            int diff = (keyLength - 1) * 2 - offset * 2;

            if (offset == keyLength - 1)
                diff = (keyLength - 1) * 2;

            for (int j = offset; j < ciphertext.size(); j += diff)
            {
                plaintext[j] = ciphertext[cipherIndex];
                cipherIndex++;
            }
        }

        std::cout << keyLength << ": " << plaintext << std::endl;
    }

    return "";
}



/*
    Converts the given text to lowercase and returns the result.
*/
std::string toLowerCase(const std::string& str)
{
    std::string copy(str);
    std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
    return copy;
}



/*
    Returns the statistical deviation of str from English's letter
    frequency distributions.
*/
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



/*
    Returns the letter frequencies for English. Courtesy Wikipedia.
*/
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
