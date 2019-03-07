# lottery_calculation
to calculate a probability of lottery


the first time to create a project from GitHub 


you can ignore this file , because i just to try , good luck  !!!!!!!!!!!!!!

const int ROW = 15;
	const int COL = 7;
	
	// 11 15 16 20 24 31    04
	int test[15][7] = {
		{ 1, 8,21,23,24,26, 7},
		{11,15,19,23,24,31, 1},
		{ 5, 9,10,18,26,30,16},
		{ 7,10,12,15,21,25, 8},
		{ 3, 6,13,19,21,22,11},
		{4,11,15,25,30,32,1    },
		{3,8,10,21,28,29,5    },
		{4,8,10,14,27,30,13    },
		{6,8,9,10,20,33,5    },
		{2,6,13,18,20,21,15    },
		
		{3,18,19,24,26,33,9		},
		{1,3,13,16,20,26,9		},
		{2,5,13,20,21,31,13		},
		{7,13,14,19,22,32,5		},
		{4,6,11,14,17,26,14		}
		
	};
	int Probability[33] = {0};
	
	//计算每个数字在一组数值的概率。
	for(int i = 0; i < ROW; i++){
		
		for(int j = 0; j < COL; j++){
			//printf(" num: %d  \n", test[i][j]);
			int num = test[i][j];
			for(int k = 0; k < ROW; k++){
				if(i != k)
					continue;
				for(int a = 0; a < COL; a++){
					if(k == i && j == a){
					}else{
						int compare = test[k][a];
						for(int b = 0; b < ROW; b++){
							int result = 0;
							for(int c = 0; c < COL; c++){
								if(b != k){
									if(num == test[b][c] || compare == test[b][c]){
										result += 1;
									}
								}
							}
							if(result >= 2){
								Probability[num] += 1;
							}
						}
					}
					
				}
			}
			
		}
		
	}
	
	for(int i = 1; i < 33; i++){
		printf("Probability[%d]:%d  \n", i, Probability[i]);
	}
