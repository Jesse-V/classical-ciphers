
#ifndef MAIN
#define MAIN

#include <iostream>
#include <unordered_map>

typedef std::unordered_map<char, float> FrequencyMap;

std::string crackShiftCipher(const std::string& ciphertext);
float getDeviationFromEnglish(const std::string& str);
FrequencyMap getEnglishFrequencyMap();
std::string toLowerCase(const std::string& str);

static const std::string& cipher1 = "YRGZRORTVAOLFNLVATGUNAXFGBNYYLBHJUBIRGENIRYRQSEBZSNENAQJVQRGBOENIRGURPBYQGBQNLJRNYYZNQRGUVFWBHEARLSBENERNFBAVGFUHZOYVATOHGVAZLURNEGVXABJLBHQVQAGPBZRURERWHFGSBEZRLBHPNZRURERORPNHFRLBHORYVRIRVAJUNGGUVFPBHAGELPNAORVAGURSNPRBSJNELBHORYVRIRGURERPNAORCRNPRVAGURSNPRBSQRFCNVELBHORYVRIRGURERPNAORUBCRVAGURSNPRBSNCBYVGVPFGUNGFFUHGLBHBHGGUNGFGBYQLBHGBFRGGYRGUNGFQVIVQRQHFSBEGBBYBATLBHORYVRIRJRPNAORBARCRBCYRERNPUVATSBEJUNGFCBFFVOYROHVYQVATGUNGZBERCRESRPGHAVBAGUNGFGURWBHEARLJRERBAGBQNLOHGYRGZRGRYYLBHUBJVPNZRGBORURERNFZBFGBSLBHXABJVNZABGNANGVIRBSGUVFTERNGFGNGRVZBIRQGBVYYVABVFBIREGJBQRPNQRFNTBVJNFNLBHATZNAGURAWHFGNLRNEBHGBSPBYYRTRVXARJABBARVAPUVPNTBJNFJVGUBHGZBARLBESNZVYLPBAARPGVBAFOHGNTEBHCBSPUHEPURFUNQBSSRERQZRNWBONFNPBZZHAVGLBETNAVMRESBENLRNENAQVNPPRCGRQGURWBOFVTUGHAFRRAZBGVINGRQGURAOLNFVATYRFVZCYRCBJRESHYVQRNGUNGVZVTUGCYNLNFZNYYCNEGVAOHVYQVATNORGGRENZREVPNZLJBEXGBBXZRGBFBZRBSPUVPNTBFCBBERFGARVTUOBEUBBQFVWBVARQJVGUCNFGBEFNAQYNLCRBCYRGBQRNYJVGUPBZZHAVGVRFGUNGUNQORRAENINTRQOLCYNAGPYBFVATFVFNJGUNGGURCEBOYRZFCRBCYRSNPRQJRERAGF";

static const std::string& cipher2 = "YOCNQWBWYIOVNWGFIPAOIUEYHRVRSIOMFWLFSZFPKHKITEGVNCZTZZJUCKXLEIFNBFOSFXCZJAPRYJLIRJREQXZBRXLOIVMUNPRNHFKRLXVVOHDGSFLLFNSZVLGNKYPWNQYDWWREZRDSMMECEHKNISGHJASKJIOTXVNMGCVLHJKDSNQVDWMKEGRYEQBLRRSFHHJBZZJUFHJLAIJLZVGRSGHIAULNELBRXPVVEMJVYCWHZQROAIEAJVTMXBRUIMJGPXZVFSWEIKJBQRXCLVXZXQFQHYYLWGIMAFZVMKTHRIDUTMRSPPJCMGQTXVZJAPUSMEAYABVXIJBJZJRDAWWEJZJJFNYFMEIEZPREMLMECPVHSJXGFBTZPASKIYKIJGWSGHSNWEIMFZYGPVVTISKSWAJVTCXNRVNOCKQWXXRJRVUTWVMRHZPYLWGIMAFDALQISJCSKUYUAEEQDGGVZTRUKTDGXZTXZPFVSYAKIJWGKTSFZQFNOCRVAGGZLZVVSHKIMABKOIXKSDZSCKFWKEKAZPUXWITZJUZPXGMLVOHIGILTRUISKJSVBGRHZPMRGVOZJUGGSHEIJDOKUSXYXYABZCGUHYEPWKJMYAXZISKQKWMXFOSRCWKHSEWGZEEFMLZOWJOCKNFJPWKWXWYSILWJVSDTRUXOCNAAMLRLVZNSKHTYEQRNJDHYIEGYEELHXYNCNULAFWVHTLRSFAMJOKFTHAJYZAHCAXSDIKKHYGWZBTKDSIGMKGSKDWEIWMKTIEGZP";

static const std::string& cipher3 = "FAZEADMCPYXQYYBLFYDISJZTBCHKOGNWKVVERPZPCYBHEGKDQCAXZNGYLMWXAXTXNVBCHKPCYHCQOBOSQCOFDRSVFWDABBHTWAKAKXOUZLMURHPAFXVKIFTUIIXLHGNKGZIHHPPTXNBYSMUVJATOBFKVEVWQKMZUAJIISAVPDZPNSNJZJJFRRHJIPYFNGJCHBIWPJFJOVFMXPPNCANTOYKAXZNVHSRPBJIYOTINOWFVQQVSHUJGBBISGNVZUBWEYWDULPHQJKHYMOYDSTDABPRXFCGPUBOILBNDDAGXPSRLTLBXNKGVEBTSAOGFBEQYKDJVUVZDENQJYRULYYWRKIQSISBOIIQCZYPGEATBIEESIRUYIBAVKLJPOGLECAFUGCTDGMQNPIZXVPEYDRZJDIZLNOVNWXMBFIDMSNKBLSKXMBLWWLDSWDYQLVLNVXWMAZPWYSNUALUMGRNOCQQXBTPYDTWMUTOUHEVUAXDNSKTWJQERTBUVYSDZGUPNQCBSDZTLDPHHCIIMECWPRIHYAYUOSZTUUBKFGMINSUDJHMZQUVTRKDOCGIQEEJIPXXDBIGROIOWYRRSQNVMQWOBQRXKFMFVWALWOZYVHRXPVBBJDXKVOVRRLYOAYKWSRNZQIJIPGBMQYPVHXMWLNYMCCTLLTTLHVQXPBAPHPWMVRYIFNNZVIIYQSKSQHLIWSUEBKSATWRQHDXCIAXPHPKJPNRHSKUDXWJPHQVZSBKWRIPKSBGPFDKBSEKELPNMCQBTZHQNKGOYCCGYUJILNEIFFVTFINEBTRBSYBZPIOIHLFJSCOFCPMIAPNLMRGQJWULELBVKXJUGMKCGFBLXQIRNQVWBAPAJIUHGWNBIUCTMJLVWEFASNOLSXARDVBJLTDYYIDJAKIZLKLXZYIRAYRVRJUFLZBFXORVZUGKWXDMVSTIRSWTCBULNVFNIMKFKYAWWZOQBPOQIFQNPITDSKIVREQNHQVLQYNXHWQPPJKWMYJPWPERHVOEYZNPAOMANCVDJPVDEZFEXFMWJEMTGILYFBOGUVDPCRVKOUPBEWDYMTYRGINEXBLHSCQIJQGOSZCAGYGINQHWUOLLGMLFARAKIYTQBNEDYNKAWCWQPCLJMBCFTKODWEMANXJQODLMZZCRELPHAHDCERGGEPNNHLHABYYBCQINWJXYJIELFZAKRZDLJKPPTDCJPHFEUJNZSDTIZAIOKBBWBOFZSCYJMEGBCQDUBYPBIWHCJBCPGQJGUTYZDRCCDQSIKSGVXTYFYOHLXQGZIRCJKSAICLFHKPPDZMDAVMTLJLEEIWFQSPPWLTAFOEVMNILSTLCYTUDTTQVBZMLCBOKOYIYGXCNONSOQPEAAZKSMFPUUPVRHPPRTWJNUPPRJNXKVBTJMCIBKTQZAFWMWZRFLNNOCZAQWDBWGEQACKIMXDUYAZTHNHFVXNFLYPGEWQDDWAPRJEXPAPMFJMRDJHXKRWWHRXSLFDPWWQXGKIAWUUIMWYEBTAMMCMULBJUFRRWRQXHUHFFOSDPCKBCBXYVQCCMOUOLYVPEGDVLWPMTZPAPTESGUIARCGUOUOLOFNDNCROETXAMCLVRADDXAYLWRPAQSRXKRYFHMOYNYBPYATOWPHDKZDLIQLGLKNOKFRRZLMBIJWRJDLYQLEJXDUCCQECKAIPGQWVBPHQTEZERLKEABHHPGUWRINAPKTTEAJKRRVYGEBCSDDBBSPXCKMXNCSYCFBCZSNJTXDTQCHZENUOYKHKXZWTYPPBOGYYIZPPIMLKGFYNNGNWHJBQKOCKJOLYYPAPKZPFYZSVCHOYSZOYWIDKIVNYYOFETELOFIRNYWXNNOWZBLHPPWMWPILZNCGAOBAMJVWAVFDLOLMJGDPARWSECJSVYHHGNRJWTOKOEZILUCZBQHWYVAVVGXJKHAQYNYOZFMGWYMLFXKDVQHZSHGPZGEPOMGFQERGAXGHTFLDMTWPXYUGEJNDKVVQVYFRLTZJHTANWSXLPATKINJNDPWWVCJJXAOEECOESXERNLMVZXKRLJPELBKBFUHFDYAIHAPAOBCOIWAYTICHFEWHNNTNXSEZBJFKGYLGPUMPRVDBLFMFODARWLHSFOCNPFCLMGXSSIQUNTSKWEIHZZMYNEQYEZWKKNFUAMOJZMCGPGWOBCEGFRJKQXYEGHAPPEPPBDFBZCVRVDUXKGNTRZUVLJKBRSPQGZFNADEUCEGFOQCFHNIJSXKNCZOPKKWDDRROXHLVSKNMSGVAAXAMTANVCPEFLQQUCRRNEVQRVJZMFPVDUXYYBDWXARARTJMDXIVNPFBDNPGPOVCHYHVXZMBYWNYKZQEOCMOSSWZDERWINZVNVMPHWJUVCUVDOJYCOTPBQOOBQGHFVCFSDNFFTORLCPHIOJZGPGGUIAGAMIFLBTSXZMYGBRNYSFTVQKWZDIKCZVABUNCPRCZZBMEWJLYMLTVOAARVBVNNLFTKBKFJLJLYTUNHCDKIXHUUTRZQVHIEAGVJEREHFDPRHPURYGYXSHJNZVYLBTJHYEBGJUYSJZGOXQPNOMVWQJLWNQNLSYLRCMGEAWQNBAZOAWJFTXPRIGQTPPJNRJGYUJFEYWHNNKUBDJYABZXJILRZJHPADUOVOWNTPCOJEZHLWYKIEOGAYQGMLCJCVVCMSSZXBIGBXGDYZRRJRXPEJYALXLNIZVBDZCTRRATJKTXEWHZJHOMHOPLOGCKQPIKQPMTEUKOTCBGEWVJHDWTIIMNNEQYLKTZWJIIMUJEICJQKICTUVHGAQPFXSPUJGMBUGMFYAQHZJDUKMGJQWRJRHHFLWPAFEPGAJKESEEDMSTZRTMVGWURDWLYVUCJUKLJXRPJKPCHTQQNKWHWQDLBMLXXJLCTXWYLIMQMCWGDORBNCIUKUTIQNUSPJUTGXKTFTWUAHELIHJVAAXXUDKHUPDOYLRHMLNYQCSBQPOAPOAOQMFMOCELRLZZIERUCHNIGLD";

#endif
