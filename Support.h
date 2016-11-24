//
// Created by Sanyog Chhetri on 05/11/16.
//

#ifndef CLASSIFICATION_GA_2_SUPPORT_H
#define CLASSIFICATION_GA_2_SUPPORT_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

unsigned long Checker(const vector<string >& in_out_genes, const vector<string >& in_outgen_genes,
                      const vector<unsigned char >& out_gen_genes, const vector<unsigned char >& out_out_genes);

class data
{
	vector<string> tmp;
	vector<unsigned char> out_tmp;
	vector<float> num_tmps;
public:
	data();
	virtual ~data(){};
	void Read_data(int a);
	void separator(int a);//separates string and text to int
	vector<string> tmp_get();
	vector<unsigned char> out_tmp_get();
	vector<float> num_tmps_get();
};


#endif //CLASSIFICATION_GA_2_SUPPORT_H
