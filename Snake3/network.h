#pragma once

#define NET_INPUTS	6
#define NET_OUTPUTS	3


typedef struct{
	float w[NET_INPUTS][NET_INPUTS];
	int score;
} NetworkParams;


int network_init(NetworkParams *param);
int network_output(float *input, float *output);
