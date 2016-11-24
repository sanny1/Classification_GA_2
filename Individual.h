//
// Created by Sanyog Chhetri on 04/11/16.
//

#ifndef CLASSIFICATION_GA_2_INDIVIDUAL_H
#define CLASSIFICATION_GA_2_INDIVIDUAL_H

#include<iostream>
#include<vector>

using namespace std;

namespace Ann
{

	class Individual
	{
	private:
		vector<unsigned char > inputs;
		vector<unsigned char > outputs;
		vector<unsigned char > extracted_inputs;//outputs remember to make them same
		vector<unsigned long > number_ext_inps;
		vector<string > ext_string_inps;
		vector<unsigned char > extracted_outputs;
	private:
		unsigned long rules;
		unsigned long genome_size;
		unsigned long fitness;
	public:
		Individual(const unsigned long& r,const unsigned long& gz);
		virtual ~Individual(){};
	public:
		void extracting_inputs();
		void ext_input_to_string();
		void initialising_genome();
		void Set_fitness(unsigned long val);
		void Set_inputs(vector<unsigned char > val);
		void Set_outputs(vector<unsigned char > val_outs);
		void mutate(int rate);
	public:
		vector<unsigned char > get_inputs();
		vector<unsigned char > get_outputs();
		vector<unsigned char > get_extracted_inputs();
		vector<unsigned char > get_extracted_output();
	public:
		unsigned long get_fitness();
		vector<unsigned long > get_number_ext_inps();
		vector<string > get_string_inp();
	public:
		void print_genome();
	};
}

#endif //CLASSIFICATION_GA_2_INDIVIDUAL_H
