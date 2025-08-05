#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <map>
#include <filesystem>
#include "platform.hpp"

using namespace std;

map<string,map<string,string>>i18n={
	{"en",{
		{"lang_name","English"},
		{"title","maimaiDX DXSCORE Calculate"},
		{"result","DX Score: %d/%d, CRIT/PERFECT/GREAT[%d-%d-%d]"},
		{"menu_1","1. Calculate"},
		{"menu_2","2. Language"},
		{"menu_exit","0. Exit"},
		{"dx_score","DX Score [%d/%d]\n"},
		{"dx_cent_star","Achivement (DX Score) [%.2f%%/%d]\n"},
		{"autosave_on","Auto Save: On"},
		{"autosave_off","Auto Save: Off"},
		{"presstips","Press c, r, s, p to calculate, refresh, save or switch auto save. You can press 0 to back."},
		{"in_crit","Enter your Crit Perfect count: "},
		{"in_perfect","Enter your Perfect count: "},
		{"in_great","Enter your Great count: "},
		{"invaild_in","At least one input value is invaild. Please check it."},
		{"in_songname","Enter the song name: "},
		{"saved_songname","Song Name "},
		{"saved_dxscore","DX Score "},
		{"saved_dxcent","Achivement "},
		{"saved_done","Save done."}
	}},
	{"zh",{
		{"lang_name","中文"},
		{"title","maimaiDX DX分数 计算器"},
		{"result","DX分数: %d/%d, CRIT/PERFECT/GREAT[%d-%d-%d]"},
		{"menu_1","1. 计算 DX分数"},
		{"menu_2","2. 切换语言"},
		{"menu_exit","0. 退出"},
		{"dx_score","DX分数 [%d/%d]\n"},
		{"dx_cent_star","DX分数达成率 [%.2f%%/%d]\n"},
		{"autosave_on","自动保存: 开启"},
		{"autosave_off","自动保存: 关闭"},
		{"presstips","按下 c 开始计算，按下 r 清空数据，按下 s 保存本次计算，按下 p 切换自动保存状态，或按下 0 返回主菜单"},
		{"in_crit","Crit Perfect判定数"},
		{"in_perfect","Perfect判定数"},
		{"in_great","Great判定数"},
		{"invaild_in","输入的判定数中至少有一个不符合规则"},
		{"in_songname","输入乐曲名: "},
		{"saved_songname","乐曲名 "},
		{"saved_dxscore","DX 分数 "},
		{"saved_dxcent","DX分数达成率 "},
		{"saved_done","保存完成"}
		}}
};

float cent=0.00;
int calcdxscore=0,totaldxscore=0,calcdxstar=0;
int crit=0,perfect=0,great=0;
char op;
int isAutoSave=1;
string songname="Untitle";
string lang="en";

void showLanguageMenu() {
    clearScreen();
    printf("Languages/语言:\n");
    for (const auto& lang_pair : i18n) {
        const string& code = lang_pair.first;
        const string& name = lang_pair.second.at("lang_name");
        printf("[%s] %s\n", code.c_str(), name.c_str());
    }
    printf("\nEnter the language code and press Return./输入语言代码后按下回车\n");
}

void mainMenu() {
	clearScreen();
	printf("%s\n\n",i18n[lang]["title"].c_str());
	printf(i18n[lang]["result"].c_str(),calcdxscore,totaldxscore,crit,perfect,great);
	printf("\n\n%s\n",i18n[lang]["menu_1"].c_str());
	printf("%s\n",i18n[lang]["menu_2"].c_str());
	printf("%s\n",i18n[lang]["menu_exit"].c_str());
}

void calcMenu() {
	clearScreen();
	printf("%s\n",i18n[lang]["title"].c_str());
	printf(i18n[lang]["dx_score"].c_str(),calcdxscore,totaldxscore);
	printf(i18n[lang]["dx_cent_star"].c_str(),cent,calcdxstar);
	printf("CRIT[%d] PERFECT[%d] GREAT[%d]\n",crit,perfect,great);
	if (isAutoSave==1) printf("%s\n\n",i18n[lang]["autosave_on"].c_str());
	else printf("%s\n\n",i18n[lang]["autosave_off"].c_str());
	printf("%s\n\n",i18n[lang]["presstips"].c_str());
}

int main(){	

	ofstream outfile("record.txt",ios::app);

	showLanguageMenu();
	cin>>lang;
	if (i18n.find(lang)==i18n.end()) {
		printf("Invaild lang code. Changed to English.\n");
		printf("无效的语言代码，已被切换为英文\n");
		lang="en";
		pauseSystem();
	}
	
	while (true) {
		mainMenu();
		op=getch();
		
		if (op=='0') break;
		else if (op=='2') {
			showLanguageMenu();
			cin>>lang;
			if (i18n.find(lang)==i18n.end()) {
				printf("Invaild lang code. Keep current language.\n");
				printf("无效的语言代码，将保持当前的语言\n");
				pauseSystem();
			}
			continue;
		}
		else if (op=='1') {
			while (true) {
				calcMenu();
				op=getch();
				
				if (op=='0') break;
				switch (op) {
					case 'p' :
						if (isAutoSave==1) isAutoSave=0;
						else if (isAutoSave==0) isAutoSave=1;
						break;
					case 'r' :
						calcdxscore=calcdxstar=totaldxscore=crit=perfect=great=cent=0;
						break;
					case 's' :
						printf("%s",i18n[lang]["in_songname"].c_str());
						outfile<<i18n[lang]["saved_songname"].c_str()<<songname<<endl;
						outfile<<i18n[lang]["saved_dxscore"].c_str()<<"["<<calcdxscore<<"/"<<totaldxscore<<"]"<<endl;
						outfile<<i18n[lang]["saved_dxcent"].c_str()<<"["<<cent<<"%/"<<calcdxstar<<"]"<<endl;
						outfile<<"CRIT"<<"["<<crit<<"]"<<" "<<"PERFECT"<<"["<<perfect<<"]"<<" "<<"GREAT"<<"["<<great<<"]"<<endl;
						outfile<<endl;
						printf("%s",i18n[lang]["saved_done"].c_str());
						pauseSystem();
						break;
					case 'c' :
						printf("%s",i18n[lang]["in_crit"].c_str());
						scanf("%d",&crit);
						printf("%s",i18n[lang]["in_perfect"].c_str());
						scanf("%d",&perfect);
						printf("%s",i18n[lang]["in_great"].c_str());
						scanf("%d",&great);
						if (crit<0||perfect<0||great<0) {
							printf("%s",i18n[lang]["invaild_in"].c_str());
							pauseSystem();
							crit=perfect=great=0;
							continue;
						}
						
						totaldxscore=(crit+perfect+great)*3;
						calcdxscore=crit*3+perfect*2+great*1;
						cent=static_cast<float>(calcdxscore)/totaldxscore*100;
						if (cent>=97.00f) calcdxstar=5;
						else if (cent>=95.00f) calcdxstar=4;
						else if (cent>=93.00f) calcdxstar=3;
						else if (cent>=90.00f) calcdxstar=2;
						else if (cent>=85.00f) calcdxstar=1;
						else calcdxstar=0;
						if (isAutoSave==1) {
							printf("%s",i18n[lang]["in_songname"].c_str());
							cin.ignore();
							getline(cin,songname);
							outfile<<i18n[lang]["saved_songname"].c_str()<<songname<<endl;
							outfile<<i18n[lang]["saved_dxscore"].c_str()<<"["<<calcdxscore<<"/"<<totaldxscore<<"]"<<endl;
							outfile<<i18n[lang]["saved_dxcent"].c_str()<<"["<<cent<<"%/"<<calcdxstar<<"]"<<endl;
							outfile<<"CRIT"<<"["<<crit<<"]"<<" "<<"PERFECT"<<"["<<perfect<<"]"<<" "<<"GREAT"<<"["<<great<<"]"<<endl;
							outfile<<endl;
							break;
						}
						default:continue;
				}
			}
		}
	}
}
