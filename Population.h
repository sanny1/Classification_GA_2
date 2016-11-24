//
// Created by Sanyog Chhetri on 12/11/16.
//

#ifndef CLASSIFICATION_GA_2_POPULATION_H
#define CLASSIFICATION_GA_2_POPULATION_H

#include "Individual.h"

using namespace Ann;

class Population
{
private:
	vector<Individual > parents;
	vector<Individual > children;
	Individual temp;
	vector<int > select;
	vector<string > ideal_input;
	vector<unsigned char > ideal_output;
private:
	int pop_size;
	int no_ins;
	int no_rule;
	int best_fitness;
	int sum_fitness;
private:
	float mean_fitness;
public:
	Population(int ps, int rules, int g_z);
	virtual ~Population(){};
public:
	void Initialise();
	void Evaluates(unsigned long(*fitness_func)(const vector<string >& in_out_genes, const vector<string >& in_outgen_genes,
	                                            const vector<unsigned char >& out_gen_genes, const vector<unsigned char >& out_out_genes), int l);
	void Selection();
	void Tournament_Selection(int k);
	void Poppairing(int j);
	void Organise();
	void PopMutate(int r_t);
	void Deterministic_crowding();
	void reinsert(int div);
public:
	void Set_ideal_output(vector<unsigned char > out_val);
	void Set_ideal_ins(vector<string > str);
	void print_a_individual();
public:
	int Best_fitness();
	float Mean_fitness();
};


#endif //CLASSIFICATION_GA_2_POPULATION_H
