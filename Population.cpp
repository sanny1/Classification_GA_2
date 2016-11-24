//
// Created by Sanyog Chhetri on 12/11/16.
//

#include "Population.h"

Population::Population(int ps, int rules, int g_z) : temp(rules, g_z), parents(ps, Individual(rules, g_z)),
                                                     children(ps, Individual(rules, g_z)), select(ps, 0)
{
	pop_size = ps;
	no_ins = g_z;
	no_rule = rules;
}

void Population::Initialise()
{
	for (int i = pop_size; i--;)
	{
		parents.at(i).initialising_genome();
	}
}

void Population::Set_ideal_ins(vector<string> str)
{
	ideal_input = str;
}

void Population::Set_ideal_output(vector<unsigned char> out_val)
{
	ideal_output = out_val;
}

void Population::Evaluates(
		unsigned long (*fitness_func)(const vector<string> &, const vector<string> &,
		                              const vector<unsigned char> &, const vector<unsigned char> &), int l)
{
	unsigned long fit_val;
	if (l == 1)
	{
		for (int i = 0; i < pop_size; i++)
		{
			parents.at(i).extracting_inputs();
			parents.at(i).ext_input_to_string();
			fit_val = fitness_func(ideal_input, parents.at(i).get_string_inp(), parents.at(i).get_extracted_output(),
			                       ideal_output);
			parents.at(i).Set_fitness(fit_val);
		}
	}
	else if (l == 2)
	{
		for (int i = 0; i < pop_size; i++)
		{
			children.at(i).extracting_inputs();
			children.at(i).ext_input_to_string();
			fit_val = fitness_func(ideal_input, children.at(i).get_string_inp(), children.at(i).get_extracted_output(),
			                       ideal_output);
			children.at(i).Set_fitness(fit_val);
		}
	}
}

void Population::Selection()
{
	for(int i = 0; i < pop_size; i++)
	{
		select.at(i) = i;
	}
}

void Population::Tournament_Selection(int k)
{
	int rand_num = 0;
	for (int i = 0; i < pop_size; i++)
	{
		best_fitness = 0;
		for (int j = 0; j < k; j++)
		{
			rand_num = rand() % pop_size;
			if (best_fitness < parents.at(rand_num).get_fitness())
			{
				select.at(i) = rand_num;
				best_fitness = parents.at(rand_num).get_fitness();
			}
		}
	}
}

void Population::Poppairing(int j)// have to put it for output
{
	int rand_num = 0;
	int rand_per = 0;
	int rand_out = 0;
	for (unsigned long i = 0; i < select.size(); i += 2)
	{
		rand_per = rand() % 100;
		if (j > rand_per)
		{
			rand_num = rand() % (no_ins * no_rule);
			rand_out = rand() % no_rule;
			for (int j = 0; j < 2; j++)
			{
				vector<unsigned char> father = parents.at(select.at(i + j)).get_inputs();//vector
				vector<unsigned char> father_out = parents.at(select.at(i + j)).get_outputs();//vector output
				vector<unsigned char> mother = parents.at(select.at(i + (!j))).get_inputs();//vector
				vector<unsigned char> mother_out = parents.at(select.at(i + (!j))).get_outputs();//vector ouput
				vector<unsigned char> tmp(father.begin(), father.end() - ((no_ins * no_rule) - rand_num));
				vector<unsigned char> tmp_out(father_out.begin(), father_out.end() - ((no_rule) - rand_out));
				vector<unsigned char> tmp2(mother.begin() + rand_num, mother.end());
				vector<unsigned char> tmp2_out(mother_out.begin() + rand_out, mother_out.end());
				tmp.insert(tmp.end(), tmp2.begin(), tmp2.end());
				tmp_out.insert(tmp_out.end(), tmp2_out.begin(), tmp2_out.end());
				children.at(i + j).Set_inputs(tmp);
				children.at(i + j).Set_outputs(tmp_out);
			}
		}
		else
		{
			children.at(i) = parents.at(select.at(i));
			children.at(i + 1) = parents.at(select.at(i + 1));
		}
	}
}

void Population::Organise()
{
	int temp_fit_val1, temp_fit_val2;
	for (int i = (pop_size); i--;)
	{
		for (int j = (pop_size - 1); j--;)
		{
			temp_fit_val1 = parents.at(j).get_fitness();
			temp_fit_val2 = parents.at(j + 1).get_fitness();
			if (temp_fit_val1 > temp_fit_val2)
			{
				temp = parents.at(j);
				parents.at(j) = parents.at(j + 1);
				parents.at(j + 1) = temp;
			}
		}
	}
	for (int i = (pop_size); i--;)
	{
		for (int j = (pop_size - 1); j--;)
		{
			temp_fit_val1 = children.at(j).get_fitness();
			temp_fit_val2 = children.at(j + 1).get_fitness();
			if (temp_fit_val1 > temp_fit_val2)
			{
				temp = children.at(j);
				children.at(j) = children.at(j + 1);
				children.at(j + 1) = temp;
			}
		}
	}
//	cout << parents.at((pop_size-1)).get_fitness() << endl;
//	parents.at((pop_size-1)).print_genome();
}

void Population::PopMutate(int r_t)//might need to mutate output as well
{
	for (int i = 0; i < pop_size; i++)
	{
		children.at(i).mutate(r_t);
	}
}

void Population::reinsert(int div)
{
	int count = 0;
	for (int i = (pop_size - 1); i > (pop_size / div); i--)
	{
		parents.at(count) = children.at(i);
		count++;
	}
}

void Population::print_a_individual()
{
	parents.at(0).print_genome();
}

void Population::Deterministic_crowding()
{
	for(int i = 0; i < select.size(); i+=2)
	{
		int fit_1 = parents.at(select.at(i)).get_fitness();
		int fit_2 = parents.at(select.at(i+1)).get_fitness();
		if(fit_1 < fit_2)
		{
			int c_fit_1 = children.at(i).get_fitness();
			int c_fit_2 = children.at(i+1).get_fitness();
			if(c_fit_1 < c_fit_2)
			{
				parents.at(select.at(i)) = children.at(i+1);
			}
			else
			{
				parents.at(select.at(i)) = children.at(i);
			}
		}
		else
		{
			int c_fit_1 = children.at(i).get_fitness();
			int c_fit_2 = children.at(i+1).get_fitness();
			if(c_fit_1 < c_fit_2)
			{
				parents.at(select.at(i+1)) = children.at(i+1);
			}
			else
			{
				parents.at(select.at(i+1)) = children.at(i);
			}
		}
	}
}

int Population::Best_fitness()
{
	return parents.at(pop_size - 1).get_fitness();
}

float Population::Mean_fitness()
{
	sum_fitness = 0;
	for (int i = pop_size; i--;)
	{
		sum_fitness += parents.at(i).get_fitness();
	}
	mean_fitness = sum_fitness / pop_size;
	return mean_fitness;
}