#pragma once

#define ADALINE		0
#define SIGMOID		1
#define TANH		2
#define LINEAR		3



typedef struct{
	int score;
	int act_func_L1;
	int act_func_L2;
	float wL1[6][6];
	float wL2[3][6];
} NetworkParams;


int network_init(NetworkParams *param);
int network_output(float *input, float *output);
