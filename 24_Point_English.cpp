#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
using namespace std;

void oppo(char &d, char c){
	if(c == '/'){
		if(d == '*')
			d = '/';
		if(d == '/')
			d = '*';
	}
	if(c == '-'){
		if(d == '+')
			d = '-';
		if(d == '-')
			d = '+';
	}
}

bool find(string s){
	for(int i = 0; i < s.size(); i++)
		if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			return 1;
	return 0;
}

string uncover(string s, char c){
	if(find(s) == 0)
		return s;
	int b = 1;
	for(int a = 0; b < (s.size() - 1); b++){
		if(a == 0 && (s[b] == '+' || s[b] == '-' || s[b] == '*' || s[b] == '/'))
			break;
		if(s[b] == '(')
			a++;
		else if(s[b] == ')')
			a--;
	}
	char d = s[b];
	string e = "(", f = ")";
	string F = (((b - 1) < 0 || (b - 1) >= s.size()) ? "" : s.substr(1, (b - 1)));
	string S = (((s.size() - b - 2) > 0 && (b + 1) < s.size()) ? s.substr((b + 1), (s.size() - b - 2)) : "");
	if(c == ' ')
		e = "", f = "";
	if(c == '*' || c == '/')
		if(d == '*' || d == '/')
			e = "", f = "", oppo(d, c);
	if(c == '+' || c == '-')
		e = "", f = "", oppo(d, c);
	if(F.empty() && S.empty())
		return "";
	else if(F.empty())
		return uncover(S, d);
	else if(S.empty())
		return uncover(F, d);
	else
		return (e + uncover(F, d) + "" + d + uncover(S, d) + f);
}

string main_solve(vector<float> w, vector<string> v, float temp){
	if(w.size() == 1){
		if(w[0] != 24)
			return "No Solution";
		else
			return uncover(v[0], ' ');
	}
	for(int i = 0; i < w.size(); i++)
		for(int j = (i + 1); j < w.size(); j++){
			vector<float> nw = w, cw;
			vector<string> nv = v, cv;
			string S;
			float a = nw[i], b = nw[j];
			string s = nv[i], t = nv[j];
			nw.erase(nw.begin() + j), nw.erase(nw.begin() + i);
			nv.erase(nv.begin() + j), nv.erase(nv.begin() + i);
			for(int k = 0; k < 2; k++){
				cw = nw, cv = nv, cw.push_back(a * b), cv.push_back("(" + s + "*" + t + ")");
				S = main_solve(cw, cv, temp + 1);
				if(S != "No Solution")
					return S;
				cw = nw, cv = nv, cw.push_back(a / b), cv.push_back("(" + s + "/" + t + ")");
				S = main_solve(cw, cv, temp + 1);
				if(S != "No Solution")
					return S;
				cw = nw, cv = nv, cw.push_back(a + b), cv.push_back("(" + s + "+" + t + ")");
				S = main_solve(cw, cv, temp + 1);
				if(S != "No Solution")
					return S;
				cw = nw, cv = nv, cw.push_back(a - b), cv.push_back("(" + s + "-" + t + ")");
				S = main_solve(cw, cv, temp + 1);
				if(S != "No Solution")
					return S;
				swap(a, b), swap(s, t);
			}
		}
	return "No Solution";
}

bool all_num(string s){
	for(int i = 0; i < s.size(); i++)
		if(s[i] < '0' || s[i] > '9')
			return 0;
	return 1;
}

float sti(string s){
	float res = 0;
	for(float i = 0; i < s.size(); i++)
		res *= 10, res += (s[i] - '0');
	return res;
}

string its(int n){
	string res = "";
	while(n)
		res = string(1, (n % 10 + '0')) + res, n /= 10;
	return res;
}

signed main(){
	cout << "Welcome to the 24 point game!\n\n";
	srand(time(NULL));
	while(1){
		cout << "Please type in : \n";
		cout << "\'1\'.Type in 4 numbers.\n";
		cout << "\'2\'.The system will randomly pick four numbers(a solution is ensured).\n";
		cout << "\'Any other keys\'.Clear screen.\n";
		char c = getch();
		if(c == '1'){
			bool good = 1;
			vector<float> w;
			vector<string> v(4);
			cout << "Please type in four numbers below 1e9(or it may possibly lead to RE).\n";
			cin >> v[0] >> v[1] >> v[2] >> v[3];
			for(int i = 0; i < 4; i++){
				if(v[i] == "J" || v[i] == "j")
					w.push_back(11);
				else if(v[i] == "Q" || v[i] == "q")
					w.push_back(12);
				else if(v[i] == "K" || v[i] == "k")
					w.push_back(13);
				else if(all_num(v[i]) == 1)
					w.push_back(sti(v[i]));
				else{
					cout << "Invalid input.\n";
					good = 0, Sleep(750);
					break;
				}
			}
			if(!good)
				continue;
			string s = main_solve(w, v, 0);
			if(s == "No Solution")
				cout << "There is No Solution.\n";
			else{
				cout << "There is at least one solution, press any key to check one of them.\n";
				char c2 = getch();
				cout << s << "\n\n";
			}
		}
		else if(c == '2'){
			vector<float> w(4);
			vector<string> v(4);
			while(1){
				for(int i = 0; i < 4; i++)
					w[i] = (rand() % 13 + 1), v[i] = its(w[i]);
				if(main_solve(w, v, 0) != "No Solution")
					break;
			}
			cout << "The four nunbers are : " << w[0] << ' ' << w[1] << ' ' << w[2] << ' ' << w[3] << ", press any key to check one of the solutions.\n";
			char c2 = getch();
			cout << main_solve(w, v, 0) << "\n\n";
		}
		else{
			cout << "Sure to clear screen?\n\'1\'.Yes.\n\'Any other keys\'.No.\n";
			char c = getch();
			if(c == '1'){
				system("CLS");
				cout << "Welcome to the 24 point game!\n";
			}
			cout << endl;
		}
	}
	return 0;
}
