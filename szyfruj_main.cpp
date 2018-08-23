#include <conio.h>
#include<iostream>
#include<string>
#include "Lista.h"
#include <fstream>
using namespace std;


 
string GetCommands(string,int);
void SetParameters(lista*);
string Szyfruj(string, string, string);

 //cod szyfruje, dec rozszyfrowywuje, nie da siê zaszyfrowac cod i rozszyfrowac przez cod.
int main(int argc, char *argv[])
{
	string commands[4];
	if(5 == argc) 
	{
	for(int i=1; 5>i; i++) commands[i-1] = argv[i];
	cout<<"corectly amount of arguments"<<endl;
	}
	else if(2 == argc )
	{
		commands[0] = argv[1] ;
		if("help" == commands[0] || "doc" == commands[0])
		{
		cout<<argv[1]<<endl;
		cout<<"\tHelpin info for szyfruj.exe\nCommands cod and cod2 are cripting, next to commands dec and dec2 are decripting.\n Note, commands are nummered. That why cod is working with dec and don't with dec2. Also u can't cripting by dec and encripting by cod. \nExemple cript formula: szyfruj cod input.txt output.txt 1qaz2wsx3edc4rfv\n decript: szyfruj dec input2.txt output2.txt 1qaz2wsx3edc4rfv\n\tREMEMBER\nKEY can't includes recurring bajts !!!!"<<endl;
		}
		else
		{
			cout<<"try 'szyfruj help' or 'szyfruj doc' "<<endl;
		}
		_getch();
		return 0;
	}
	else
	{
			cout<<"there is a problem wtih amount of arguments, program will terminated, try again"<<endl;
			_getch();
			return 0;
	}

	//Test comand valid
	lista *cript_commands_list=new lista;
	SetParameters(cript_commands_list);
	if(cript_commands_list->IsThereElement(commands[0])) cout<<"command of cript is good"<<endl;
	else
	{
		cout<<"command of cript is not valid, program will be terminated, try again"<<endl;
		_getch();
		return 0;
	}

	//Test 128bit code
	string s_help = commands[3].c_str();
	int amount = s_help.length();
	if(16==amount) cout<<"Lenght of code is valid";
	else
	{
		cout<<"code is not valid, program will be terminated, try again"<<endl;
		_getch();
		return 0;
	}
	lista *characters = new lista;
	s_help = "";
	for(int i=0; 16>i; i++) 
	{
			s_help += commands[3][i];
			characters->puch(s_help);
			s_help = "";
	}
	int size = characters->Getsize();
	for(int j=0; size>j; j++) 
	{
		s_help += characters->GetString(1);
		characters->remove(j+1);
		if(!characters->IsThereElement(s_help)) s_help = "";
		else
		{
		cout<<"code can't have 2 the same bajts, program will be terminated, try again"<<endl;
		_getch();
		return 0;
		}
		
	}
	cout<<"code is correct"<<endl;

	//stream files
	fstream input;
	fstream output;
	input.open( commands[1], ios::out | ios::in );
	

	if(input.good() && input.is_open()) cout<<commands[1]<<" input file is egsist and is openable"<<endl;
	else
	{
		cout<<"input file error"<<endl;
		_getch();
		return 0;
	} 
	output.open( commands[2], ios::out);
	if(output.good() && output.is_open()) cout<<commands[2]<<" output file is egsist and is openable"<<endl;
	else
	{
		cout<<"output file error"<<endl;
		_getch();
		return 0;
	} 

	string code;
	string s_convert_amount = "";
	int i_convert_amount=0;
	char space = ' ';
	lista *codes = new lista;
	int i_ID=1;
	while(!input.eof())
	{
		getline( input, code);
		s_help = code.c_str();
		amount = s_help.length();
		
			int h=0;
			for(int k=0; ((amount/16)+1)>k; k++) 
			{
				s_convert_amount = code.substr(h,16);
				i_convert_amount = s_convert_amount.length();
				while(i_convert_amount < 16 && i_convert_amount > 0)
				{
					code = code + space;
					s_convert_amount = code.substr(h,16);
					i_convert_amount = s_convert_amount.length();
				}
				if(i_convert_amount > 0) codes->puch(code.substr(h,16));
				h+=16;
			}
			s_help = "";
		
			//szyfrowanie ca³ej lini
			output.flush();
			int i_size = codes->Getsize()+1-i_ID;
			for(int x=0; (i_size)>x; x++)
			{
				output<<Szyfruj(codes->GetString(i_ID), commands[3], commands[0]);
				i_ID++;
			}
			output<<'\n';
	}
	cout<<"Input text:"<<endl;
	codes->show();
	cout<<"closing files ("<<commands[1]<<" "<<commands[2]<<")"<<endl;
	input.close();
	output.close();
	cout<<"FINISH"<<endl;
	system("pause");
return 0;
}

string GetCommands(string _main, int n)
{
	string *s_tab= new string[n+1];
	for(int i=0; i<(n+1); i++) s_tab[i]="";
	char c_help;
	int j=0;
	
	for(int i=0; n+1>i; i++)
	{
		c_help = _main[j];
		while(' ' != c_help && '\0' != c_help)
		{
			s_tab[i] += c_help;
			j++;
			c_help = _main[j];
		}
		j++;
	}
		
	return s_tab[n];
};

void SetParameters(lista *_b)
{
	_b->puch("cod");
	_b->puch("cod2");
	_b->puch("dec");
	_b->puch("dec2");
}

//blok is 128bits, klucz is 128bits, metoda is method to kript
string Szyfruj(string blok, string klucz, string metoda)
{
	int i_h = 0;
	if("cod" == metoda) i_h = 1;
	else if("cod2" == metoda) i_h = 2;
	else if("dec" == metoda) i_h = 3;
	else if("dec2" == metoda) i_h = 4;
	else i_h = 0;
	char c_return_[16];
	string s_return_="";

	switch(i_h)
	{
	case 1:// encrypted xor by key and special constant byte 'a'
		
		for(int i=0; i<16; i++)
		{
			c_return_[i] = 'a' ^ klucz[i];
			c_return_[i] = c_return_[i] ^ blok[i];
		}
		for(int j=0; j<16; j++)
		{
			s_return_ += c_return_[j]+1;
		}
		break;
	case 2:// encrypted xor by key and special constant byte 'b'

		for(int i=0; i<16; i++)
		{
			c_return_[i] = 'b' ^ klucz[i];
			c_return_[i] = c_return_[i] ^ blok[i];
		}
		for(int j=0; j<16; j++)
		{
			s_return_ += c_return_[j]+1;
		}
		break;
	case 3:// decrypted xor by key and special constant byte 'a'

		for(int i=0; i<16; i++)
		{
			blok[i] = blok[i]-1;
			c_return_[i] = blok[i] ^ 'a';
			c_return_[i] = c_return_[i] ^ klucz[i];
		}
		for(int j=0; j<16; j++)
		{
			s_return_ += c_return_[j];
		}
		break;
		
	case 4:// decrypted xor by key and special constant byte 'b'

		for(int i=0; i<16; i++)
		{
			blok[i] = blok[i]-1;
			c_return_[i] = blok[i] ^ 'b';
			c_return_[i] = c_return_[i] ^ klucz[i];
		}
		for(int j=0; j<16; j++)
		{
			s_return_ += c_return_[j];
		}
		break;
	default:
		cout<<"U need to implement this command in switch before u use that"<<endl;
	break;
	}

	return s_return_;
}

