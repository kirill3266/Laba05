    #include <iostream>
    #include<io.h>
    #include <fcntl.h>
    #include<vector>
    #include <wctype.h>
    using namespace std;

    void prisv(vector<wchar_t>& res, vector<wchar_t> vec, int& Fbeg, int& Fend, int& Sbeg, int& Send, int& count,int& Flag,int& Vlen) {
        if (Flag == 1) {
            if (Vlen!=0) res.push_back(L'(');
            for (int i = Fbeg; i != Fend; i++)
                res.push_back(vec[i]);
            res.push_back(L'→');
            for (int i = Sbeg; i != Send+1; i++)
                res.push_back(vec[i]);
            res.push_back(L'→');
            res.push_back(count + L'0');
            if (Vlen != 0) res.push_back(L')');
            else Flag = -2;
            Send = Fend-1;
            Vlen = Fend;
            Sbeg = Fbeg;
            Fbeg = -1;
            Fend = 0;
            count = 0;
        }
        else if (Flag > 1) {
            res.insert(res.begin(), L'(');
            int i;
            for (i = 1; Fend-i+1!=Fbeg; i++)
                res.insert(res.begin()+1, vec[Fend-i]);
            res.insert(res.begin()+i, L'→');
            res.push_back(L'→');
            res.push_back(count + L'0');
            res.push_back(L')');
            Send = Fend-1;
            Sbeg = Fbeg;
            Vlen = Fend;
            Fbeg = -1;
            Fend = 0;
            count = 0;
            wcout << endl;
        }
        else if (Flag == -1) {
            for (int i =1; i != Fend+1; i++)
                res.insert(res.begin(), vec[Fend- i]);
            res.insert(res.begin() + Fend, L'→');
            res.push_back(L'→');
            res.push_back(count + L'0');
            Flag = -2;
        }
    }

    void perevod(vector<wchar_t> vec) {

        vector<wchar_t> res;

        int Fbeg = -1;
        int Fend = 0;
        int Sbeg = 0;
        int Send = vec.size() - 2;
        int Flag = 0;
        int count = 0;
        int Vlen = Send;

        for (Vlen = Send; Flag != -2; Vlen--) {
            if (!iswdigit(vec[Vlen]) && Sbeg == 0) {
                Sbeg = Vlen + 1;
            }
            if (vec[Vlen] == L'↑' && Fend == 0) {
                count++;
                continue;
            }
            else if (Sbeg != 0 && Fend == 0 && count != 0) {
                Fend = Vlen + 1;
            }
            if (!iswdigit(vec[Vlen]) && Fbeg < 0 && Fend != 0) {
                Fbeg = Vlen + 1;
            }
            else if (Vlen == 0) {
                Fbeg = Vlen;
            }
            if (Vlen == 0 && Flag > 0) {
                Flag = -1;
                prisv(res, vec, Fbeg, Fend, Sbeg, Send, count, Flag, Vlen);
            }
            else if (Fbeg != -1) {
                Flag++;
                prisv(res, vec, Fbeg, Fend, Sbeg, Send, count, Flag, Vlen);
            }
        }
        wcout << L"Итог!" << endl;
        for (int i = 0; i < res.size(); i++)
            wcout << res[i];
        wcout << endl;
    }


    int main() {

        _setmode(_fileno(stdin), _O_U16TEXT);
        _setmode(_fileno(stdout), _O_U16TEXT);

        wchar_t ch = 0;
        wchar_t prev = 0;
        int dcounter = 0;
        vector<wchar_t> myVector;

         cout << L"Введите строку:" << endl;
        do
        {
            wcin.get(ch);
            if (iswdigit(ch)) dcounter++;
            if (!iswdigit(ch) && ch != L'↑' && ch != L'\n' || prev == 0 && ch == L'↑' || prev == L'↑' && ch == L'\n') {
                wcout << L"Некорректный ввод!" << endl;
                return 1;
            }
            myVector.push_back(ch);
            prev = ch;
        } while (ch != L'\n');

        if (dcounter == myVector.size()-1) {
            wcout << L"Некорректный ввод!" << endl;
            return 1;
        }

        perevod(myVector);

        return 0;
    }