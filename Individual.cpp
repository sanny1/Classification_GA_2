//
// Created by Sanyog Chhetri on 04/11/16.
//

#include "Individual.h"

using namespace Ann;

Individual::Individual(const unsigned long& r,const unsigned long& gz):inputs((gz*r),0),outputs(r,0),extracted_inputs(0,0), number_ext_inps(r,0)
{
	rules = r;
	genome_size = gz;
}

void Individual::initialising_genome()
{
	unsigned long rule_genome = rules*genome_size;
	unsigned char rand_tmp = 0;
	for(int i = 0; i < rule_genome; i ++)
	{
		rand_tmp = (rand() % 3)+'0';
		inputs.at(i) = rand_tmp;
	}
	for(int i = 0; i < rules; i++)
	{
		rand_tmp = (rand()%2)+'0';
		outputs.at(i) = rand_tmp;
	}
}

void Individual::extracting_inputs()
{
	vector<int> vec_count(rules,0);
	vector<unsigned long> pos(0,0);
	extracted_inputs.clear();
	extracted_outputs.clear();
	for(int i = 0; i < rules; i++)
	{
		int count = 0;
		for(int j = 0; j < genome_size; j++)
		{
			if(inputs.at((i*genome_size)+j) == '2')
			{
				count++;
				pos.push_back(((i*genome_size)+j));
			}
		}
		vec_count.at(i) = count;
	}
	int pos_count = 0;
	for(int i = 0; i < rules; i++)
	{
		int x = 1;
		x = x << vec_count.at(i);
		vector<unsigned char> tmp((inputs.begin()+(genome_size*i)),
		                          (inputs.begin()+genome_size+(genome_size*i)));//spliting the vector in 5's
		number_ext_inps.at(i) = x;
		for(int j = 0; j < x; j++)
		{
			for(int k = 0; k < vec_count.at(i); k++)
			{
				tmp.at(pos.at(pos_count+k)-(i*genome_size)) = (((j >> k) & 1) + '0');
			}
			for(auto& z: tmp)
			{
				extracted_inputs.push_back(z);
			}
			extracted_outputs.push_back(outputs.at(i));
		}
		pos_count = pos_count + vec_count.at(i);
	}
}

void Individual::ext_input_to_string()
{
	int val = 0;
	val = extracted_inputs.size()/genome_size;
	ext_string_inps.clear();
	for(int i = 0; i < val; i ++)
	{
		string tmp((extracted_inputs.begin() + (i*genome_size)), (extracted_inputs.begin() + (i*genome_size) + genome_size));
		ext_string_inps.push_back(tmp);
	}
}

void Individual::Set_fitness(unsigned long val)
{
	fitness = val;
}

void Individual::Set_inputs(vector<unsigned char> val)
{
	inputs = val;
}

void Individual::Set_outputs(vector<unsigned char> val_outs)
{
	outputs = val_outs;
}

void Individual::mutate(int rate)
{
	for(int i = 0; i < (rules*genome_size);i++)
	{
		int rand_num = rand()%1000;
		if (rate > rand_num)
		{
			int rand_bit = 0;
			if (inputs.at(i) == '2')
			{
				rand_bit = (rand() % 2 + 1);
				inputs.at(i) -= rand_bit;
			}
			else if (inputs.at(i) == '0')
			{
				rand_bit = ((rand() % 2) + 1);
				inputs.at(i) += rand_bit;
			}
			else
			{
				rand_bit = (rand() % 2);
				if (rand_bit == 0)
				{
					rand_bit = -1;
				}
				inputs.at(i) += rand_bit;
			}
		}
	}
	for(int i = 0; i < rules; i ++)
	{
		int rand_num = rand()%1000;
		if(rate > rand_num)
		{
			if(outputs.at(i) == '0')
			{
				outputs.at(i) = '1';
			}
			else
			{
				outputs.at(i) = '0';
			}
		}
	}
}

void Individual::print_genome()
{
	int count = 0;
	auto it = outputs.begin();
	for(auto& z : inputs)
	{
		if(count == genome_size)
		{
			cout << " " << *it;
			it++;
			count = 0;
			cout << endl;
		}
		cout << z;
		count++;
	}
	cout << " " << *it;
}

vector<unsigned char > Individual::get_extracted_inputs()
{
	return extracted_inputs;
}

vector<unsigned char > Individual::get_inputs()
{
	return inputs;
}

vector<unsigned long > Individual::get_number_ext_inps()
{
	return number_ext_inps;
}

vector<unsigned char > Individual::get_extracted_output()
{
	return extracted_outputs;
}

vector<unsigned char > Individual::get_outputs()
{
	return outputs;
}

vector<string > Individual::get_string_inp()
{
	return ext_string_inps;
}

unsigned long Individual::get_fitness()
{
	return fitness;
}
