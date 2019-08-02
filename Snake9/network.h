#pragma once

#define ADALINE		0
#define SIGMOID		1
#define TANH		2
#define LINEAR		3


#define LAYER1_IN	6
#define LAYER1_OUT	6
#define LAYER2_IN	6
#define LAYER2_OUT	3


typedef struct{
	int score;
	int act_func_L1;
	int act_func_L2;
	float wL1[LAYER1_OUT][LAYER1_IN];
	float wL2[LAYER2_OUT][LAYER2_IN];
} NetworkParams;


int network_init(NetworkParams *param);
int network_output(float *input, float *output);
