# lottery_calculation
to calculate a probability of lottery


the first time to create a project from GitHub 


you can ignore this file , because i just to try , good luck  !!!!!!!!!!!!!!

const int ROW = 35;
	const int COL = 6;
	
	//5(10): 4+0 , 3 + 1
	//6(5):  2+1, 1+1, 0+1
	
	// 11 15 16 20 24 31    04
	int test[35][7] = {
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
		{4,6,11,14,17,26,14		},
		
		{4,5,16,19,28,33,11		},
		{2,4,7,20,26,29,10		},
		{5,15,16,21,27,32,13		},
		{5,8,10,11,12,19,10		},
		{1,4,10,20,27,30,7		},
		
		{5,7,15,22,25,32,12		},
		{6,15,17,19,20,29,14		},
		{1,12,14,21,28,29,2		},
		{1,5,13,15,19,25,4		},
		{11,18,19,23,26,28,3		},
		
		{1,2,4,6,21,23,8		},
		{5,11,12,16,21,24,12		},
		{1,3,6,12,13,27,1		},
		{5,6,15,20,21,26,15		},
		{5,12,14,15,29,30,15		},
		
		{1,2,12,14,19,20,16		},
		{7,8,9,19,22,32,5		},
		{1,5,7,8,9,15,6		},
		{3,8,13,23,25,33,13		},
		{10,15,26,29,30,32,11		}
		
	};
	int Probability[33] = {0};
	
	//计算每个数字概率，在一行中出现的两个以上数字，在其他行中出现越高，概率越大。
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			
			//当前行的第一个数字
			int num = test[i][j];
			for(int k = 0; k < ROW; k++){
				//同一行的第二个数字
				if(i != k)
					continue;
				for(int a = 0; a < COL; a++){
					
					if(a != j){
						//选择进行匹配的另一数字
						int compare = test[k][a];
						//一个数字在其他行出现的次数，如果出现了，再看看有没第三个相同数字。。
						for(int b = 0; b < ROW; b++){
							if(b <= i)
								continue;
							int result = 0;
							for(int c = 0; c < COL; c++){
								if(num == test[b][c] || compare == test[b][c]){
									result += 1;
								}
							}
							if(result >= 2){
								Probability[num] += 1;
								//第三个数字
								for(int d = 0; d < ROW; d++){
									for(int e = 0; e < COL; e++){
										//当前行的第三个数字
										if(d == k){
											if(num == test[d][e] || compare == test[d][e])
												continue;
											int compare3 = test[d][e];
											int result = 0;
											for(int g = 0; g < COL; g++){
												if(num == test[b][g] || compare == test[b][g] || compare3 == test[b][g]){
													result += 1;
												}
											}
											if(result >= 3){
												Probability[num] += 1;
												//第四个数字
												for(int a4 = 0; a4 < ROW; a4++){
													for(int b4 = 0; b4 < COL; b4++){
														//当前行的第四个数字
														if(a4 == k){
															if(num == test[a4][b4] || compare == test[a4][b4] || compare3 == test[a4][b4])
																continue;
															int compare4 = test[a4][b4];
															int result = 0;
															for(int c4 = 0; c4 < COL; c4++){
																if(num == test[b][c4] || compare == test[b][c4] || compare3 == test[b][c4] || compare4 == test[b][c4]){
																	result += 1;
																}
															}
															if(result >= 4){
																Probability[num] += 1;
																//第五个数字
																for(int a5 = 0; a5 < ROW; a5++){
																	for(int b5 = 0; b5 < COL; b5++){
																		//当前行的第五个数字
																		if(a5 == k){
																			if(num == test[a5][b5] || compare == test[a5][b5] || compare3 == test[a5][b5] || compare4 == test[a5][a5])
																				continue;
																			int compare5 = test[a5][b5];
																			int result = 0;
																			for(int c5 = 0; c5 < COL; c5++){
																				if(num == test[b][c5] || compare == test[b][c5] || compare3 == test[b][c5] || compare4 == test[b][c5] || compare5 == test[b][c5]){
																					result += 1;
																				}
																			}
																			if(result >= 5){
																				Probability[num] += 1;
																				//第六个数字
																				for(int a6 = 0; a6 < ROW; a6++){
																					for(int b6 = 0; b6 < COL; b6++){
																						//当前行的第五个数字
																						if(a6 == k){
																							if(num == test[a6][b6] || compare == test[a6][b6] || compare3 == test[a6][b6] || compare4 == test[a6][b6] || compare5 == test[a6][b6])
																								continue;
																							int compare6 = test[a6][b6];
																							int result = 0;
																							for(int c6 = 0; c6 < COL; c6++){
																								if(num == test[b][c6] || compare == test[b][c6] || compare3 == test[b][c6] || compare4 == test[b][c6] || compare5 == test[b][c6] || compare6 == test[b][c6]){
																									result += 1;
																								}
																							}
																							if(result >= 6){
																								Probability[num] += 1;
																							}
																						}
																					}
																				
																				}
																			}
																		}
																	}
																
																}
															}
														}
													}
												
												}
											}
										}
									}								
								}								
							}
						}
					}					
				}
			}
		}
	}
	
	//7:在每次出现此数字的一行中，相同匹配的1-6的数字越多，+1
	int Probability_red[17] = {0};
	
	for(int i = 0; i < ROW; i++){
		int red = test[i][6];
		for(int j = 0; j < 6; j++){
			//当前行的数字
			int compare = test[i][j];
			for(int c = 0; c < ROW; c++){
				//其他行, 比当前行靠后的行，防止跟前面的行重复了
				if(c > i){
					//只有跟RED一样的行才进行对比
					if(red == test[c][6]){
						//其他行的数字
						for(int d = 0; d < 6; d++){
							//匹配到
							if(compare == test[c][d]){
								Probability_red[compare] += 1;
								//继续匹配
								for(int e = 0; e < 6; e++){
									if(e != j){
										for(int f = 0; f < 6; f++){
											if(test[i][j] == test[c][f]){
												int countNum = test[i][j];
												Probability_red[countNum] += 1;
											}
										}
									}
								}
							}						
						}
					}				
				}
			}	
		}	
	}
	
	
	
	// 11 15 16 20 24 31    04
	for(int i = 1; i < 33; i++){
		switch(i){
			case 11:
			case 15:
			case 16:
			case 20:
			case 24:
			case 31:
			case 4:
				printf("Probability[%d]:%d  <<< \n", i, Probability[i]);
				break;
			default:
				printf("Probability[%d]:%d  \n", i, Probability[i]);
				break;
		}
		
	}
	printf("---------------------------------------\n");
	// 11 15 16 20 24 31    04
	for(int i = 1; i < 17; i++){
		switch(i){
			case 4:
				printf("Probability_red[%d]:%d  <<< \n", i, Probability_red[i]);
				break;
			default:
				printf("Probability_red[%d]:%d  \n", i, Probability_red[i]);
				break;
		}
		
	}
