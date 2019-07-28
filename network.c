#include <math.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

#define E	2.718


void neuron_init(Neuron *n, float *w, int c, int type){
	n->type=type;
	n->count=c;

	int i;
	for(i=0;i<6;++i){
		n->w[i]=w[i];
	}
}

float neuron_output(Neuron *n, float *input){
	int i;
	float sum=0;

	for(i=0;i<6;++i){
		sum += input[i]*n->w[i];
	}

	switch(n->type){
	case SIGMOID:
		return 1/(1+pow(E, -sum));
	case TANH:
		return -1+2/(1+pow(E, -2*sum));
	case LINEAR:
		return sum*0.3;
	default:
		return sum;
	}
}

#include <stdio.h>
void network_init(Network *n, float *w1, float *w2, float *w3){
	int i;
	for(i=0;i<6;++i){
		neuron_init(&(n->stage1[i]), w1, 6, LINEAR);
		neuron_init(&(n->stage2[i]), w2, 6, SIGMOID);
		neuron_init(&(n->stage3[i]), w3, 6, LINEAR);

		int j;
		for(j=0;j<6;++j){
			w1[j] *= 1.2;
			w2[j] *= 1.3;
			w3[j] *= 1.5;
		}
	}
}

void network_output(Network *n, float *input, float *output){
	int i;
	float in[6];
	float out[6];

	memcpy(in, input, 6*sizeof(float));
	for(i=0;i<6;++i){
		out[i]=neuron_output(&(n->stage1[i]), in);
/*
		printf("### w: %f %f %f %f %f %f\n", n->stage1[i].w[0], n->stage1[i].w[1], n->stage1[i].w[2], 
			n->stage1[i].w[3], n->stage1[i].w[4], n->stage1[i].w[5]);
		printf("### in: %f %f %f %f %f %f out: %f\n\n", in[0], in[1], in[2], in[3], in[4], in[5], out[i]);
*/
	}
	printf("in: %f %f %f %f %f %f\nout: %f %f %f %f %f %f\n\n", in[0], in[1], in[2], in[3], in[4], in[5], 
		out[0], out[1], out[2], out[3], out[4], out[5]);


	memcpy(in, out, 6*sizeof(float));
	for(i=0;i<6;++i){
		out[i]=neuron_output(&(n->stage2[i]), in);
	}

	memcpy(in, out, 6*sizeof(float));
	for(i=0;i<3;++i){
		output[i]=neuron_output(&(n->stage3[i]), in);
	}
}
