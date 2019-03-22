


#include<stdio.h>
#include<signal.h>
#include<string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <clocale>
#include <cwchar>
#include<limits.h>
#include<unistd.h>
#include <ctype.h>

int count1 = 0;
int count2 = 0;
int countAll = 0;
int Probability_red[17] = {0};


void combine(int n,int m,int a[],int b[],const int M)
{

	for(int j=n;j>=m;j--)
	{
		b[m-1]=j-1;
		if(m>1)
			combine(j-1,m-1,a,b,M);//用到了递归思想
		else
		{
			int aa = 0;
			for(int i= 0; i < M; i++){
				//printf("%d ",a[b[i] + 1]);
				aa += a[b[i] + 1];
			}
			
	#if 0		
			for(int i = 1; i < 16; i++)
			{
				int tt = Probability_red[i] + aa;
				double bb = (double)tt/countAll;
				if(bb >= 0.06 && bb <= 0.09)
				{
					for(int tmp= 0; tmp < M; tmp++){
						printf("%d ",b[tmp] + 1);
						//printf("%d ",a[b[tmp] + 1]);
					}
					printf("%d ", i);
					printf("  bb:%f  \n", bb);
					//printf("\n");
				}	
			}	
			
	#else
			double bb = (double)aa/countAll;
			if(bb >= 0.07 && bb <= 0.09)
			{
				for(int tmp= 0; tmp < M; tmp++){
					//printf("%d ",b[tmp] + 1);
					//printf("%d ",a[b[tmp] + 1]);
				}
				//printf("  bb:%f  \n", bb);
				//printf("\n");
			}	
	#endif 
			//printf("bb:%f  \n", bb);
				
		}
	}
}






//#define VERSION1
	//5(10): 4+0 , 3 + 1
	//6(5):  2+1, 1+1, 0+1
int main(int argc, char *argv[])
{
#ifdef VERSION1	
	const int ROW = 100;
	const int COL = 6;
	

	
	// 03 13 14 16 25 27    12
	int test[100][7] = {
		{3,9,10,13,17,21,7		},
		{2,11,12,17,27,32,6		},
		{8,10,11,19,21,24,15		},
		{16,20,22,23,24,32,9		},
		{19,21,22,25,31,32,1		},
		
		{2,5,6,7,14,23,1		},
		{1,2,8,15,21,32,14		},
		{1,2,6,9,11,22,10		},
		{4,14,20,26,27,29,15		},
		{12,21,22,26,27,31,14		}, //10
		
		{3,10,11,12,19,21,3		},
		{3,5,7,11,16,17,14		},
		{16,18,19,20,21,22,9		},
		{22,3,9,20,24,28,14		},
		{6,12,15,18,21,25,1		},
		
		{13,15,22,27,32,33,7		},
		{2,4,9,11,20,21,1		},
		{7,11,14,20,22,24,6		},
		{3,6,9,16,22,31,13		},
		{7,8,15,16,26,29,7		}, //20
		
		{2,8,10,18,28,31,4		},
		{1,2,15,16,22,30,9		},
		{13,14,16,19,22,31,8		},
		{1,8,15,16,26,29,6		},
		{2,6,10,12,16,32,7		},
		
		{8,13,18,22,25,31,10		},
		{4,5,12,16,22,30,10		},
		{1,14,16,18,24,33,14		},
		{2,10,14,15,18,23,11		},
		{1,2,5,12,21,32,11		}, //30
		
		{7,9,16,19,24,31,6		},
		{1,2,6,19,21,26,8		},
		{1,9,16,21,27,31,15		},
		{6,19,20,24,27,31,8		},
		{2,5,9,18,30,32,3		},
			
		{2,8,25,26,27,29,2		},
		{9,11,24,29,31,32,3		},
		{4,11,14,15,21,30,16		},
		{3,4,7,13,15,20,7		},
		{8,11,13,18,24,31,1		}, //40
		
		{12,13,22,25,29,33,16		},
		{6,11,12,17,26,33,15		},
		{4,8,24,28,32,33,11		},
		{6,13,14,18,29,30,3		},
		{6,8,13,19,29,32,6		},
		
		{1,6,8,19,29,30,13		},
		{6,11,17,19,31,33,15		},
		{1,7,9,28,31,33,16		},
		{5,7,14,15,17,19,15		},
		{9,10,15,21,24,30,15		},  //50
		
		{1,5,6,19,24,29,16			},
		{5,20,21,25,26,32,4			},
		{10,12,13,19,21,28,14			},
		{9,10,12,18,19,29,7			},
		{3,14,16,20,23,29,3			},  
		
		{1,6,9,18,20,30,4			},
		{3,7,28,29,31,33,3			},
		{2,5,11,18,23,28,5			},
		{4,12,14,23,25,26,7			},
		{11,16,18,20,27,29,10			},  //60
		
		{2,5,9,11,13,30,12			},
		{4,12,15,20,22,29,1			},
		{10,12,13,17,24,30,5			},
		{1,7,11,13,28,30,2			},
		{7,12,22,23,25,32,1			},  
		
		{1,8,10,16,25,31,9			},
		{6,14,18,25,28,31,10			},
		{3,4,6,15,18,21,3			},
		{1,13,19,22,31,32,8			},
		{1,4,11,16,24,31,16			},  //70
		
		{2,5,9,22,24,29,6			},
		{7,10,11,14,19,28,14			},
		{7,10,14,15,21,25,1			},
		{1,2,12,14,20,29,10			},
		{1,7,10,13,18,20,9			},  
		
		{1,8,18,27,28,31,10			},
		{1,4,6,7,28,33,8			},
		{5,8,10,12,13,25,4			},
		{3,14,15,16,17,23,6			},
		{3,6,12,21,30,31,16			},  //80
		
		{7,9,17,20,22,24,13			},
		{1,12,14,18,26,32,14			},
		{7,11,17,18,20,22,9			},
		{4,5,11,16,25,28,5			},
		{1,3,4,24,29,30,11			},  
		
		{2,5,8,9,29,30,9			},
		{2,17,21,23,25,32,6			},
		{6,7,8,12,22,27,3			},
		{4,5,20,22,24,31,5			},
		{5,7,8,19,30,33,7			},  //90
		
		{6,8,11,12,17,28,9			},
		{6,11,24,25,30,33,14			},
		{3,7,8,15,21,27,1			},
		{7,8,15,18,22,32,7			},
		{6,11,13,17,26,27,9			},  
		
		{2,13,14,17,22,24,8			},
		{6,15,23,26,31,33,5			},
		{6,11,18,23,27,29,9			},
		{6,8,9,12,23,30,8			},
		{3,13,17,21,27,33,5			}  //100
		

		
	};
	
	
#else
	
	const int ROW = 80;
	const int COL = 6;
	
	//5(10): 4+0 , 3 + 1
	//6(5):  2+1, 1+1, 0+1
	
	// 11 15 16 20 24 31    04
	int test[80][7] = {
		{ 1, 8,21,23,24,26, 7},
		{11,15,19,23,24,31, 1},
		{ 5, 9,10,18,26,30,16},
		{ 7,10,12,15,21,25, 8},
		{ 3, 6,13,19,21,22,11},
		
		{4,11,15,25,30,32,1    },
		{3,8,10,21,28,29,5    },
		{4,8,10,14,27,30,13    },
		{6,8,9,10,20,33,5    },
		{2,6,13,18,20,21,15    }, //10
		
		{3,18,19,24,26,33,9		},
		{1,3,13,16,20,26,9		},
		{2,5,13,20,21,31,13		},
		{7,13,14,19,22,32,5		},
		{4,6,11,14,17,26,14		},
		
		{4,5,16,19,28,33,11		},
		{2,4,7,20,26,29,10		},
		{5,15,16,21,27,32,13		},
		{5,8,10,11,12,19,10		},
		{1,4,10,20,27,30,7		},  //20
		
		{5,7,15,22,25,32,12		},
		{6,15,17,19,20,29,14		},
		{1,12,14,21,28,29,2		},
		{1,5,13,15,19,25,4		},
		{11,18,19,23,26,28,3		},
		
		{1,2,4,6,21,23,8		},
		{5,11,12,16,21,24,12		},
		{1,3,6,12,13,27,1		},
		{5,6,15,20,21,26,15		},
		{5,12,14,15,29,30,15		},  //30
		
		{1,2,12,14,19,20,16		},
		{7,8,9,19,22,32,5		},
		{1,5,7,8,9,15,6		},
		{3,8,13,23,25,33,13		},
		{10,15,26,29,30,32,11		},
		
		{2,11,13,19,23,28,8		},
		{14,17,20,26,30,32,15		},
		{5,14,15,20,23,30,9		},
		{5,10,16,18,27,29,13		},
		{6,11,27,29,32,33,4		},	//40
		
		{1,8,9,25,28,30,15		},
		{16,19,21,22,25,29,10		},
		{3,10,17,24,27,29,15		},
		{6,7,9,12,24,25,13		},
		{5,12,15,16,21,24		},
		
		{2,4,15,17,22,32,8		},
		{4,9,13,16,23,25,5		},
		{2,7,8,10,12,13,5		},
		{1,14,15,23,26,29,7		},
		{9,10,15,19,28,31,8		}, //50
		
		{2,5,13,17,20,27,2		},
		{3,13,16,20,24,25,10		},
		{4,8,9,13,21,30,1		},
		{2,3,12,14,20,24,8		},
		{1,11,28,29,30,33,4		},
		
		{5,18,19,21,32,33,11		},
		{1,2,3,21,23,33,10		},
		{5,15,18,19,24,26,13		},
		{8,15,20,24,26,32,16		},
		{3,6,11,16,20,24,5		},  //60
		
		{6,11,14,17,23,31,1		},
		{2,4,12,15,27,29,7		},
		{18,22,25,29,30,31,3		},
		{2,3,9,12,15,33,13		},
		{2,14,15,19,23,26,15		},
		
		{2,4,11,12,16,17,4		},
		{8,9,11,14,22,25,4		},
		{1,5,10,13,14,23,8		},
		{9,11,14,25,29,30,6		},
		{8,15,16,17,29,31,15		}, //70
		
		{3,5,9,12,15,24,9		},
		{2,3,5,26,28,29,5		},
		{2,7,10,22,28,29,1		},
		{8,9,17,19,21,33,13		},
		{2,4,6,12,14,31,10		},
		
		{3,12,24,25,28,30,16		},
		{3,6,12,17,21,25,1		},
		{5,8,9,11,21,31,3		},
		{3,8,12,17,24,27,6		},
		{5,8,17,18,28,29,8		} //80
		
	};
	
	
	
#endif
	
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
	//int Probability_red[17] = {0};
	
	for(int i = 0; i < ROW; i++){
		int red = test[i][6];
		//一次也算
		Probability_red[red] += 1;
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
	
	
	
	
	
	for(int i = 1; i < 33; i++){
		switch(i){
		#ifdef VERSION1
		// 03 13 14 16 25 27    12
			case 3:
			case 13:
			case 14:
			case 16:
			case 25:
			case 27:
				printf("Probability[%d]:%d  <<< \n", i, Probability[i]);
				break;
			default:
				printf("Probability[%d]:%d  \n", i, Probability[i]);
				break;
		#else
			// 11 15 16 20 24 31    04
			case 11:
			case 15:
			case 16:
			case 20:
			case 24:
			case 31:
				printf("Probability[%d]:%d  <<< \n", i, Probability[i]);
				break;
			default:
				printf("Probability[%d]:%d  \n", i, Probability[i]);
				break;
		#endif
		}
		
	}
	printf("---------------------------------------\n");
	// 11 15 16 20 24 31    04
	// 03 13 14 16 25 27    12
	for(int i = 1; i < 17; i++){
		switch(i){
		#ifdef VERSION1
			case 12:
				printf("Probability_1[%d]:%d  <<< \n", i, Probability_red[i]);
				break;
			default:
				printf("Probability_1[%d]:%d  \n", i, Probability_red[i]);
				break;
		#else
			case 4:
				printf("Probability_1[%d]:%d  <<< \n", i, Probability_red[i]);
				break;
			default:
				printf("Probability_1[%d]:%d  \n", i, Probability_red[i]);
				break;
		#endif
		}
		
	}
	
	count1 = 0;
	count2 = 0;
	for(int i = 1; i < 33; i++){
		count1 += Probability[i];	
	}
	for(int i = 1; i < 17; i++){
		count2 += Probability_red[i];	
	}
	printf("count1:%d  \n", count1);
	printf("count2:%d  \n", count2);
	countAll = count1 + count2;
	
	
	int m = 6;  //多少个数字的组合
	int b[m];
	const int M = m;

	//第一个参数：范围
	combine(32, m, Probability, b, M);
	

	
	
	printf("count_6:%f  \n", (double)1253 / (count1 + count2));
	
	
	
	
	
	return 0;
}
