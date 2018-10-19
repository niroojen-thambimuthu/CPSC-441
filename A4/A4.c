/*
 * 
 * CPSC 441- A4
 * 
 * Niroojen Thambimuthu 10153928
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>


// loop function, will recursively add binary levels depending on starting point
// Will call loop function again if next level is required during collisions
void loop(int testingLevel, int index, float *coll, float *succ, float *prob, int zero, int *first, int *second, int *third, int *fourth, int *fifth, int *sixth, int *seventh, int *eight, int *nine, int *ten, int simul){
    float suctemp = *succ;
    float protemp = *prob;
    float colltemp = *coll;
    float Col = 0;
    float Suc = 0;
    float Probes = 0;
    
    if (testingLevel == 0){
        // compute level 1
        for (int one = index*2; one < (index*2)+2; one++){
            if (first[one] == 1){
                suctemp++;
                protemp++;
            }
            else if (first[one] > 1){
                colltemp++;
                protemp++;
                loop((testingLevel+1),one,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
    }
    else if(testingLevel == 1){
        // compute level 2
        for(int two = index*2; two < (index*2)+2; two++){
            if (second[two] == 1){
                suctemp++;
                protemp++;
            }
            else if (second[two] > 1){
				colltemp++;
                protemp++;
                loop((testingLevel+1),two,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
    }
    else if (testingLevel == 2){
        // compute level 3
        for(int three = index*2; three < (index*2)+2; three++){
            if (third[three] == 1){
                suctemp++;
                protemp++;
                
            }
            else if (third[three] > 1){
                colltemp++;
                protemp++;
                loop((testingLevel+1),three,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
    }
    else if (testingLevel == 3){
		// compute level 4
		for(int four = index*2; four < (index*2)+2; four++){
            if (fourth[four] == 1){
                suctemp++;
                protemp++;
            }
            else if (fourth[four] > 1){
                colltemp++;
                protemp++;;
                loop((testingLevel+1),four,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
	}
	else if (testingLevel == 4){
		// compute level 5
		for(int five = index*2; five < (index*2)+2; five++){
            if (fifth[five] == 1){
                suctemp++;
                protemp++;
            }
            else if (fifth[five] > 1){
                colltemp++;
                protemp++;
                loop((testingLevel+1),five,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
	}
	else if (testingLevel == 5){
		// compute level 6
		for(int six = index*2; six < (index*2)+2; six++){
            if (sixth[six] == 1){
                suctemp++;
                protemp++;
            }
            else if (sixth[six] > 1){
                colltemp++;
                protemp++;
                loop((testingLevel+1),six,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
	}
	else if (testingLevel == 6){
		// compute level 7
		for(int seven = index*2; seven < (index*2)+2; seven++){
            if (seventh[seven] == 1){
                suctemp++;
                protemp++;
            }
            else if (seventh[seven] > 1){
                colltemp++;
                protemp++;
                loop((testingLevel+1),seven,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
	}
	else if (testingLevel == 7){
		// compute level 8
		for(int eigt = index*2; eigt < (index*2)+2; eigt++){
            if (eight[eigt] == 1){
                suctemp++;
                protemp++;
            }
            else if (eight[eigt] > 1){colltemp++;
                protemp++;
                loop((testingLevel+1),eigt,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
	}
	else if (testingLevel == 8){
		// compute level 9
		for(int ninth = index*2; ninth < (index*2)+2; ninth++){
            if (nine[ninth] == 1){
                suctemp++;
                protemp++;
            }
            else if (nine[ninth] > 1){
                colltemp++;
                protemp++;
                loop((testingLevel+1),ninth,&Col, &Suc, &Probes,zero, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
	}
	else if (testingLevel == 9){
		// compute level 10
		for(int tenth = index*2; tenth < (index*2)+2; tenth++){
            if (ten[tenth] == 1){
                suctemp++;
                protemp++;
            }
            else if (ten[tenth] > 1){
                colltemp++;
                protemp++;
            }
        }
	}
    else{
        printf("Error in calling function");
    }
    
    *coll = colltemp+Col;
    *succ = suctemp+Suc;
    *prob = protemp+Probes;
}





int main(void)
{
    FILE *printToFile = fopen("simulation.txt","w");
    if(printToFile == NULL)
			exit(-1);
			
			
    fprintf(printToFile, "\n\ni\tk\t\tidle\t\tsuccess\t\tcollision\n");
    fprintf(printToFile, "---------------------------------------------\n");

    // test level i       // i = 0, 2, 4, 6, 8, and 10.
    int testingLevel = 0;
    for(int testingLevel = 0; testingLevel < 11; testingLevel=testingLevel+2){
    
    // kStations           k = 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, and 1024.
    //int kStations = 1024;
    for(int kStations = 1; kStations<1025; kStations=kStations*2){
    
    int length = 1024;
    int simulation = 100;
    
    int ten[length][simulation];
    for (int i = 0; i < simulation; i++){
        for (int j = 0; j < length; j++ ) {
            ten[j][i] = 0;
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    //int ten[1024];
    int nine[512];
    int eight[256];
    int seventh[128];
    int sixth[64];
    int fifth[32];
    int fourth[16];
    int third[8];
    int second[4];
    int first[2];
    int zeroB; 
    
    // randomly asigns 1 into level 3 based on kStations
    // third[random] = 1
    // if random number has been chosen before, retry
    int n=kStations;
    bool arr[1024]={0};
    int seed = 1234;
    srand(seed);
    int count = 0;
    for(int loop = 0; loop<simulation; loop++){
        //time_t t;
        srand(seed);
        bool arr[1024]={0};
        for(int i=0;i<n;++i){
            int r=rand()%length;
            if(!arr[r]){
                //printf("%d\n",r);
                ten[r][loop]=1;/////////////////////////////////////////////
                count++;
            }
            else{
                i--;
                //printf("repeat");
            }
            arr[r]=1;
        }
        
        //printf("\n");
        for(int i = 0; i < length; i++){
            arr[i] = 0;
            //printf("%d", arr[i]);
            //printf("\n");
        }
        seed = seed + 1024;
         
    }
    //printf("\n\nHow many stations transmitting: %d\n",count);
    //////////////////////////////////////////////////////////////////////
    
    float averageIdle = 0;
    float averageSuccess=0;
    float averageCollision = 0;
    
    
   
    

    fprintf(printToFile, "%d",testingLevel);
    fprintf(printToFile, "\t%d", kStations);    
	for (int simul = 0; simul < simulation; simul++){
		
		
    // * add binary levels *//
    //level 9
    for(int nineFor = 0; nineFor < 512; nineFor++)
        nine[nineFor] = ten[(nineFor*2)][simul] + ten[(nineFor*2)+1][simul];
    //level 8
    for(int eightFor = 0; eightFor < 256; eightFor++)
        eight[eightFor] = nine[(eightFor*2)] + nine[(eightFor*2)+1];
    //level 7
    for(int sevenFor = 0; sevenFor < 128; sevenFor++)
        seventh[sevenFor] = eight[(sevenFor*2)] + eight[(sevenFor*2)+1];
    //level 6
    for(int sixFor = 0; sixFor < 64; sixFor++)
        sixth[sixFor] = seventh[(sixFor*2)] + seventh[(sixFor*2)+1];
    //level 5
    for(int fiveFor = 0; fiveFor < 32; fiveFor++)
        fifth[fiveFor] = sixth[(fiveFor*2)] + sixth[(fiveFor*2)+1];
    //level 4
    for(int fourFor = 0; fourFor < 16; fourFor++)
        fourth[fourFor] = fifth[(fourFor*2)] + fifth[(fourFor*2)+1];
    // level 3
    for(int thirdFor = 0; thirdFor < 8; thirdFor++)
        third[thirdFor] = fourth[(thirdFor*2)] + fourth[(thirdFor*2)+1];
    // level 2
    for (int secFor = 0; secFor < 4; secFor++)
        second[secFor] = third[(secFor*2)] + third[(secFor*2)+1];
    // level 1
    for (int firstFor = 0; firstFor < 2; firstFor++)
        first[firstFor] = second[(firstFor*2)] + second[(firstFor*2)+1];
    // level 0
    zeroB = first[0]+first[1];
    
    
    
    // * initialization for percent calculations *//
    float collision = 0;
    float success = 0;
    float idle = 0;
    float probes = 0;
    float loopCol = 0;
    float loopSuc = 0;
    float loopProbes = 0;


	// * starting level selection coding *//
    //printf("\n\ttest level %d\n",testingLevel);
    
    // test level 0
    if (testingLevel == 0){
        if (zeroB == 0){
            //printf("\n\tidle\n");
            idle++;
            probes++;
        }
        else if (zeroB == 1){
            success++;
            probes++;
        }
        else if (zeroB > 1){
            collision++;
            probes++;
            ///////// level 1
            loop(testingLevel,0,&loopCol, &loopSuc, &loopProbes,zeroB, first, second,third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
        }
    }// end test 0
    // test level 2
    else if(testingLevel == 2){
        for(int two = 0; two < 4; two++){
            if (second[two] == 0){
                idle++;
                probes++;
            }
            else if (second[two] == 1){
                success++;
                probes++;
            }
            else if (second[two] > 1){
                collision++;
                probes++;
                ///////// level 2
                loop(testingLevel,two,&loopCol, &loopSuc, &loopProbes,zeroB, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
            }
        }
    }// end test 2
    // test level 4
    else if (testingLevel == 4){	
		for(int four = 0; four < 16; four++){
			if (fourth[four] == 0){
                idle++;
                probes++;
            }
            else if (fourth[four] == 1){
                success++;
                probes++;
            }
            else if (fourth[four] > 1){
                collision++;
                probes++;
                ///////// level 5
                loop(testingLevel,four,&loopCol, &loopSuc, &loopProbes,zeroB, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
			}
		}
	}// end test 4
	// test level 6
	else if (testingLevel == 6){
		for(int six = 0; six < 64; six++){
			if (sixth[six] == 0){
                idle++;
                probes++;
            }
            else if (sixth[six] == 1){
                success++;
                probes++;
            }
            else if (sixth[six] > 1){
                collision++;
                probes++;
                ///////// level 7
                loop(testingLevel,six,&loopCol, &loopSuc, &loopProbes,zeroB, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
			}
		}
	}// end test 6
	// test level 8
	else if (testingLevel == 8){
		for(int eig = 0; eig < 256; eig++){
			if (eight[eig] == 0){
                idle++;
                probes++;
            }
            else if (eight[eig] == 1){
                success++;
                probes++;
            }
            else if (eight[eig] > 1){
                collision++;
                probes++;
                ///////// level 9
                 loop(testingLevel,eig,&loopCol, &loopSuc, &loopProbes,zeroB, first, second, third,fourth,fifth,sixth,seventh,eight,nine,ten,simul);
			}
		}	
	}// end test 8
	// test level 10
	else if (testingLevel == 10){
        for(int tent = 0; tent < 1024; tent++){
            if (ten[tent][simul] == 0){
                idle++;
                probes++;
            }
            else if (ten[tent][simul] == 1){
                success++;
                probes++;
            }
            else if (ten[tent][simul] > 1){
                collision++;
                probes++;
                
            }
        }		
	} // end test 10
    else{
        printf("error test level i");
    }
    
    //printf("test received prob %0.3f\t\n", loopProbes);
    float totalS = success+loopSuc;
    float totalC = collision+loopCol;
    float totalP = probes+loopProbes;
    
    //printf("\nlvl 0 test: %d\t\n", zeroB);
    //printf("\n\n\n\n\nidle counter: %0.3f\t\n", idle);
    //printf("\nsuccess counter: %0.3f\t\n", totalS);
    //printf("\ncollision counter: %0.3f\t\n", totalC);
    //printf("\nprobes counter: %0.3f\t\n", totalP);
    
    
    float totalIdle = (idle/totalP)*100;
    //printf("\n\n\tidle percentage: %0.3f\t\n", totalIdle);
    
    float totalSuccess = (totalS/totalP)*100;
    //printf("\n\n\tSuccess percentage: %0.3f\t\n", totalSuccess);
    
    float totalCollision = (totalC/totalP)*100;
    //printf("\n\n\tCollision percentage: %0.3f\t\n", totalCollision);

	averageIdle = averageIdle + totalIdle;
    averageSuccess=averageSuccess+totalSuccess;
    averageCollision = averageCollision+totalCollision;
    //printf("\n\n\tidle percentage: %0.3f\t\n", averageIdle);
	//printf("\n\n\tSuccess percentage: %0.3f\t\n", averageSuccess);
	//printf("\n\n\tCollision percentage: %0.3f\t\n", averageCollision);
}
	fprintf(printToFile, "\t\t%0.3f", averageIdle/100);
	fprintf(printToFile, "\t\t%0.3f", averageSuccess/100);
	fprintf(printToFile, "\t\t%0.3f\n", averageCollision/100);
}
}
	fclose(printToFile);
	printf("\n\n");
    return 0;
}
