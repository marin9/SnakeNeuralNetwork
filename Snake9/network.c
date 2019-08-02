#include <math.h>
#include "network.h"

#define E	2.7182818


static NetworkParams *net_param;



static void float_copy(float *dest, float *src, int n){
	int i;
	for(i=0;i<n;++i){
		dest[i]=src[i];
	}
}

static float network_activation_func(float x, int f){
	switch(f){
	case SIGMOID:
		return 1/(1+pow(E, -x));
	case TANH:
		return -1+2/(1+pow(E, -2*x));
	case LINEAR:
		return x*0.3;
	case ADALINE:
		return x;
	default:
		return x;
	}
}


int network_init(NetworkParams *param){
	if(!param){
		return -1;
	}else{
		net_param=param;
		return 0;
	}
}

int network_output(float *input, float *output){
	int i, j;

	if(!input || !output){
		return -1;
	}

	//layer1
	for(i=0;i<LAYER1_OUT;++i){
		float sum=0;
		for(j=0;j<LAYER1_IN;++j){
			sum += input[j]*net_param->wL1[i][j];
		}
		output[i]=network_activation_func(sum, SIGMOID);
	}

	float_copy(input, output, LAYER1_OUT);

	//layer2
	for(i=0;i<LAYER2_OUT;++i){
		float sum=0;
		for(j=0;j<LAYER2_IN;++j){
			sum += input[j]*net_param->wL1[i][j];
		}
		output[i]=network_activation_func(sum, LINEAR);
	}
	return 0;
}
