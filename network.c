#include <math.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

#define E	2.7182818284


void neuron_init(Neuron *n, float *w, int c, int type){
	n->type=type;
	n->count=c;

	int i;
	for(i=0;i<c;++i){
		n->w[i]=w[i];
	}
}

float neuron_output(Neuron *n, float *input){
	int i;
	float sum=0;

	for(i=0;i<n->count;++i){
		sum += input[i]*n->w[i];
	}

	switch(n->type){
	case SIGMOID:
		return 1/(1+pow(E, -sum));
	case TANH:
		return -1+2/(1+pow(E, -2*sum));
	case LINEAR:
		return sum*3;
	default:
		return sum;
	}
}

void network_init(Network *n, float *w1, float *w2, float *w3){
	int i;
	for(i=0;i<6;++i){
		neuron_init(&(n->stage1[i]), w1, 6, SIGMOID);
		neuron_init(&(n->stage2[i]), w2, 6, TANH);
		neuron_init(&(n->stage3[i]), w3, 6, SIGMOID);
	}
}

void network_output(Network *n, float *input, float *output){
	int i;
	float in[6];
	float out[6];

	memcpy(in, input, 6*sizeof(float));
	for(i=0;i<6;++i){
		out[i]=neuron_output(&(n->stage1[i]), in);
	}

	memcpy(in, out, 6*sizeof(float));
	for(i=0;i<6;++i){
		out[i]=neuron_output(&(n->stage2[i]), in);
	}

	memcpy(in, out, 6*sizeof(float));
	for(i=0;i<3;++i){
		out[i]=neuron_output(&(n->stage3[i]), in);
	}

	for(i=0;i<3;++i){
		output[i]=out[i];
	}
}
