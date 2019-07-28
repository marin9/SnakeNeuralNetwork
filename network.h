#pragma once

#define NOFUNC		0
#define SIGMOID		1
#define TANH		2
#define LINEAR		3


typedef struct{
	int type;
	int count;
	float w[6];
} Neuron;

void neuron_init(Neuron *n, float *w, int c, int type);
float neuron_output(Neuron *n, float *input);



typedef struct{
	Neuron stage1[6];
	Neuron stage2[6];
	Neuron stage3[3];
} Network;

void network_init(Network *n, float *w1, float *w2, float *w3);
void network_output(Network *n, float *input, float *output);
