#include<fstream>
#include<string>
#include<map>
#include<sstream>
#include<utility>
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;
using std::stringstream;
bool GetMap(stringstream &ss, map<string,float>&transfer_key_value);
bool AddUp(stringstream &ss,  map<string,float>&transfer_key_value, float &total);
int main()
{
	ifstream istream("input.txt");
	if(!istream.is_open())
		return 0;
	std::ofstream of("output.txt",std::ios_base::trunc);
	of.setf(std::ios::fixed, std::ios::floatfield);  
	of.precision(2);//设置精度 
	map<string, float> transfer_key_value;//设置一个key key为名称 value 为和m的比例 map
	string lineStr;
	of<<"anqiu1987@sina.com\n";
	while(std::getline(istream,lineStr))
	{
		if(lineStr.size() == 0)//排除空行
			continue;
		stringstream ss(lineStr);
		if(string::npos != lineStr.find('='))//this is the transfer rule
		{
			if(!GetMap(ss, transfer_key_value))
			{
				istream.close();
				of.close();
				return -1;
			}
			
		}else//the counter
		{
			float total = 0;
			if(!AddUp(ss, transfer_key_value,total))
			{
				istream.close();
				of.close();
				return -1;
			}
			of<<"\n"<<total<<" m";
		}
	}

	istream.close();
	istream.close();
		
}
bool GetMap(stringstream &ss, map<string,float>&transfer_key_value)
{
			float i;//
			string name;
			string equal;
			float j;
			string meter;
			ss>>i>>name>>equal>>j>>meter;
			if(ss.bad())
			{
				return false;
			}
			transfer_key_value.insert(std::make_pair<string,float>(name,j)); 
			if(0 == strcmp(name.c_str(), "mile"))
			{
				transfer_key_value.insert(std::make_pair<string,float>((string)"miles",j));
			}else if(0 == strcmp(name.c_str(), "inch"))
			{
				transfer_key_value.insert(std::make_pair<string,float>((string)"inches",j));
			}else if(0 == strcmp(name.c_str(), "fath"))
			{
				transfer_key_value.insert(std::make_pair<string,float>((string)"faths",j));
			}else if(0 == strcmp(name.c_str(), "yard"))
			{
				transfer_key_value.insert(std::make_pair<string,float>((string)"yards",j));
			}else if(0 == strcmp(name.c_str(), "foot"))
			{
				transfer_key_value.insert(std::make_pair<string,float>((string)"feet",j));
			}
			return true;
}
bool AddUp(stringstream &ss,  map<string,float>&transfer_key_value, float &total)
{
			float i;
			string name;
			char operate;
			ss>>i >>name;
			if(ss.bad())
			{return false;}
			total += i * transfer_key_value[(string)name];
			while(ss>>operate)
			{
				ss>>i>>name;
				if(ss.bad())
				{return false;}
				switch(operate){
				case '+':
					total += i * transfer_key_value[(string)name];
					break;
				case '-':
					total -= i * transfer_key_value[(string)name];
					break;
				default://应该不会到这里
					break;
				}
			}
			return true;
}