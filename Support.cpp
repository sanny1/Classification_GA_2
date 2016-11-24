//
// Created by Sanyog Chhetri on 05/11/16.
//

#include "Support.h"

unsigned long Checker(const vector<string >& in_out_genes,
                      const vector<string >& in_outgen_genes,
                      const vector<unsigned char >& out_gen_genes,
                      const vector<unsigned char >& out_out_genes)
{
	unsigned long fitness = 0;
	for(int i = 0; i < (in_out_genes.size()-1); i++)
	{
		for(int j = 0; j < in_outgen_genes.size(); j++)
		{
			if(in_out_genes.at(i).compare(in_outgen_genes.at(j)) == 0)
			{
				if(out_gen_genes.at(j) == out_out_genes.at(i))
				{
					fitness++;
				}
				break;
			}
		}
	}
	return fitness;
}

data::data() : out_tmp(0, 0), num_tmps(0, 0)
{
}

void data::Read_data(int a)
{
	char name[200];
	unsigned char value;
	string char_value;
	int check = 0;
	sprintf(name, "/Users/sanyogchhetri/ClionProjects/Backpropagation/Data%d.txt", a);
	ifstream read_data(name);
	if (!read_data)
	{
		cout << "non_existent file " << endl;
	}
	while (!read_data.eof())
	{
		if (check == 0)
		{
			read_data >> char_value;
			tmp.push_back(char_value);
		}
		else if (check)
		{
			read_data >> value;
			out_tmp.push_back(value);
		}
		check = ~check;
	}
}

void data::separator(int a)
{
	int val = 0;
	for (int i = 0; i < tmp.size(); i++)
	{
//		stringstream stream(tmp.at(i));
		for (char &z:tmp.at(i))
		{
			val = z - '0';
			num_tmps.push_back(val);
		}
	}
}

vector<float> data::num_tmps_get()
{
	return num_tmps;
}

vector<string> data::tmp_get()
{
	return tmp;
}

vector<unsigned char> data::out_tmp_get()
{
	return out_tmp;
}