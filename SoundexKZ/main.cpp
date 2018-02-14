/********************Soundex algorithm for Kazakh***************************************************
*      @Author: Raushan Yergozhiyeva                                                               *
*      @About: in the program below Soundex algorithm for Kazakh language was implemented.         *
*      @Specifics: Only cirillic alphabet can be used for input.                                   *
*      Step-by-step @Soundex algorithm for kazakh:                                                  *
* @1. If the first letter is 'Д' and it is followed by letter 'Ж', cross out the first letter;     *
* @2. Convert the remaining letters in the following way:                                          *
*     0: 'а', 'ә', 'е', 'и', 'й', 'о', 'ө', 'у', 'ұ', 'ү', 'ы', 'і', 'ю', 'я', 'ъ', 'ь', 'э', 'ё'; *
*     1: 'б', 'в', 'п', 'ф';                                                                       *
*     2: 'с', 'з', 'ц', 'ш', 'щ', 'ж', 'ч';                                                        *
*     3: 'д', 'т';                                                                                 *
*     4: 'г', 'ғ', 'к', 'қ', 'х', 'һ';                                                             *
*     5: 'м', 'н', 'ң';                                                                            *
*     6: 'р';                                                                                      *
*     7: 'л';                                                                                      *
* @3. Cross out any repeating adjacent digits except the first;                                    *
* @4. Cross out the first digit;                                                                   *
* @5. Cross out any 0's;                                                                           *
* @6. Take the first 3 out of remaining digits. If fewer than 3 digits remain, append 0's.         *
***************************************************************************************************/
#include <iostream>
#include <set>
#include <string>
// Абдильдин Әбділдин - ді қос
using namespace std;

string SoundexKZ(string s);
string ChangeTheLetter(string s);
string crossOutRepeatingDigits(string s);
string crossOutZeroes(string s);

int main()
{
    setlocale(LC_ALL,"Kazakh");
    // every character in kazakh is 2 bits, not 1 bit like english letters
    string s;
    cout << "Input the name in kazakh cirillics(first letter in upper case, others in lower case):" << endl;;

    cin >> s;

    // 1st step
    int pos_d = s.find("Д");
    int pos_j = s.find("ж");
    if (pos_d==0 && pos_j==2) s.erase (0,2);

    // 2-6th steps
    string ans = SoundexKZ(s);

    // output the result(first letter of the name + code)
    string first_letter = s;
    first_letter.erase (2,s.length()-2);
    if (first_letter=="ж") first_letter="Ж";
    cout << first_letter + ans << endl;

    return 0;
}
string SoundexKZ(string s){
    string res = "";

    // 2nd step
    string alphabet[42] = {"а", "ә", "б", "в", "г", "ғ", "д", "е", "ё", "ж", "з", "и", "й", "к", "қ", "л", "м", "н", "ң","о", "ө", "п", "р", "с", "т", "у", "ұ", "ү", "ф", "х", "ч", "ш", "щ", "ц", "һ", "ъ", "ы", "і", "ь", "э", "ю", "я"};

    set< pair<int, string> > list;

    for (int i = 0; i<42; i++){
    int pos = -1;
    while(s.find(alphabet[i], pos+1)!= -1)
    {
        pos = s.find(alphabet[i], pos+1);
        list.insert(make_pair(pos/2 + 1, alphabet[i]));
    }
    }

    /*set< pair<int, string> >::iterator it;
    for (it = list.begin(); it!=list.end(); it++){
        cout << it->first << " " << it->second << endl;
    }*/
    set< pair<int, string> >::iterator it;
    for (it = list.begin(); it!=list.end(); it++){
        res+=ChangeTheLetter(it->second);
    }

    // 3rd  step
    res = crossOutRepeatingDigits(res);

    // 4th step

    string alphabetUp[42] = {"А", "Ә", "Б", "В", "Г", "Ғ", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Қ", "Л", "М", "Н", "Ң","О", "Ө", "П", "Р", "С", "Т", "У", "Ұ", "Ү", "Ф", "Х", "Ч", "Ш", "Щ", "Ц", "Һ", "Ъ", "Ы", "І", "Ь", "Э", "Ю", "Я"};

    bool erase = true;
    for (int i=0; i<42; i++){
        if (s.find(alphabetUp[i])==0) erase = false;
    }

    // the program doesnt recognize upper letters in kazakh alphabet, so cross out the first digit if ONLY its a lower case letter
    if (erase) res.erase (0,1);

    // 5th step
    res = crossOutZeroes(res);

    // 6th step
    if (res.length()>4) res.erase(5,res.length()-5);
    else {
        while(res.length()<5) res+="0";
    }
    return res;
}
string ChangeTheLetter(string s){
    string res = "";
    if (s=="а" || s=="ә" || s=="е" || s=="ё" || s=="и" || s=="й"|| s=="о" || s=="ө" || s=="у" || s=="ұ" || s=="ү" || s=="ы" || s=="і" || s=="ъ" || s=="ь" || s=="э" || s=="ю" || s=="я") res = "0";
    if (s=="с" || s=="ц" || s=="з" || s=="ш" || s=="щ" || s=="ч" || s=="ж") res = "2";
    if (s=="к" || s=="қ" || s=="ғ" || s=="г" || s=="х" || s=="һ") res = "4";
    if (s=="б" || s=="в" || s=="п" || s=="ф") res = "1";
    if (s=="м" || s=="н" || s=="ң") res = "5";
    if (s=="д" || s=="т") res = "3";
    if (s=="р") res = "6";
    if (s=="л") res = "7";
    return res;
}
string crossOutRepeatingDigits(string s){
    string res = "";
    char x;
    int i=0;
    while (i<s.length()){
        x = s[i];
        res+=x;
        while(i<s.length() && s[i]==x){
            i++;
        }
    }
    return res;
}
string crossOutZeroes(string s){
    string res = "";
    for (int i=0; i<s.length(); i++){
        if (s[i]!='0') res+=s[i];
    }
    return res;
}
