#include "network.h"


static NetworkParams *net_param;


int network_init(NetworkParams *param){
	if(!param){
		return -1;
	}else{
		net_param=param;
		return 0;
	}
}

int network_output(float *input, float *output){
	int i, j, sum;

	if(!input || !output){
		return -1;
	}

	for(i=0;i<NET_OUTPUTS;++i){
		sum=0;
		for(j=0;j<NET_INPUTS;++j){
			sum += input[j]*net_param->w[i][j];
		}
		output[i]=sum;
	}
	return 0;
}
