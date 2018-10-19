
/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct implementation for the characters
typedef struct{
	int charG, charT, charE, charD, charH, charB;
	char charI[500], charW[500];
} People;

// struct implementation for array map
typedef struct{
	int mapG, mapT, mapE, mapD;
} Track;
	
int main(int argc, char* argv[]){
	printf("\n\n\n\n");
	// Coding for correct amount of command line arguments	
	if (argc == 4){
		
        //printf("1: %s\n", argv[0]);
        //printf("Map file input: %s\n", argv[1]);
        //printf("Dwarves file input: %s\n", argv[2]);
        //printf("Routing algorithm input: %s\n", argv[3]);
        //
       
		int tempCharNumber = 0;
		FILE *fp;
		char filename[100],dTempN[100],ch;
		int linecount = 0;
		// get dwarf numbers
		// Copy -homes.txt into filename
		strcpy(filename, argv[2]);  
		// Open file in read-only mode
		fp = fopen(filename,"r");

		// If file opened successfully
		if (fp){
			while ((ch=getc(fp)) != EOF)  //Repeat until End Of File character is reached.
				if (ch == '\n') { ++linecount; }// Increment line count if new line character
		}
		// Error handling incase
		else{
			printf("Failed to open something\n");
			exit(-1);
		}
		// dwarf number = line count - bilbo(1)
		tempCharNumber = linecount - 1;

		//Initialize both arrays
		//Set characters into 1D array
		//1D array for characters
		People lotrTemp[tempCharNumber];
		for(int temp = 0; temp < tempCharNumber; temp = temp +1){
			//set beginning point of character
			lotrTemp[temp].charB = -1;
			//set other character factors
			lotrTemp[temp].charH = 0;
			lotrTemp[temp].charD = 0;
			lotrTemp[temp].charT = 0;
			lotrTemp[temp].charG = 0;
			lotrTemp[temp].charE = 0;
			//printf("%d\n", temp);
			//printf("%d\n", lotrTemp[temp].charB);
			//printf("%d\n", lotrTemp[temp].charH);
			//printf("%d\n", lotrTemp[temp].charD);
			//printf("%d\n", lotrTemp[temp].charT);
			//printf("%d\n", lotrTemp[temp].charG);
			//printf("%d\n", lotrTemp[temp].charE);
		}
		//Set 2D map array
		//2D array map initialization
		Track tempArray[26][26];
		for(int MT1 = 0; MT1 < 26; MT1 = MT1 + 1){
			for(int MT2 = 0; MT2 < 26; MT2 = MT2 + 1){
				// set initial map topology file
                tempArray[MT1][MT2].mapG = -1;
				tempArray[MT1][MT2].mapT = -1;
                tempArray[MT1][MT2].mapE = -1;
                tempArray[MT1][MT2].mapD = -1;
                //printf("%d\n", MT1);
                //printf("%d\n", MT2);
                //printf("%d\n", tempArray[MT1][MT2].mapG);
                //printf("%d\n", tempArray[MT1][MT2].mapT);
                //printf("%d\n", tempArray[MT1][MT2].mapE);
                //printf("%d\n", tempArray[MT1][MT2].mapD);
			}
		}
		//Read the first file -map.txt
		FILE *openMapFile = fopen(argv[1], "r");
		char firstArray,secondArray;
		int tempD, tempT,tempG,tempTr,T1,T2;
		//Data from map
		while (fscanf(openMapFile, "%c %c %d %d %d %d\n", &firstArray, &secondArray, &tempD, &tempT, &tempG, &tempTr) != EOF){
			T1 = firstArray - 65;
			T2 = secondArray - 65;
			tempArray[T1][T2].mapD = tempD;
			tempArray[T1][T2].mapT = tempT;
			tempArray[T1][T2].mapG = tempG;
			tempArray[T1][T2].mapE = tempTr;
			tempArray[T2][T1].mapD = tempD;
			tempArray[T2][T1].mapT = tempT;
			tempArray[T2][T1].mapG = tempG;
			tempArray[T2][T1].mapE = tempTr;
			//printf("%d\n", tempArray[T1][T2].mapD);
			//printf("%d\n", tempArray[T1][T2].mapT);
			//printf("%d\n", tempArray[T1][T2].mapG);
			//printf("%d\n", tempArray[T1][T2].mapE);
			//printf("%d\n", tempArray[T2][T1].mapD);
			//printf("%d\n", tempArray[T2][T1].mapT);
			//printf("%d\n", tempArray[T2][T1].mapG);
			//printf("%d\n", tempArray[T2][T1].mapE);
		}
		fclose(openMapFile);

		//Read the second file -homes.txt
		FILE *openNumberFile = fopen(argv[2], "r");
		char nameTemp;
		char initialTemp;
		//Data for character home
		int secondFileTemp = 0;
		const char *initial = "Bilbo";
		while (fscanf(openNumberFile, "%s %c\n", dTempN, &nameTemp) != EOF){
			char openC;
			// Find bilbo's home
            if (strcmp(initial, dTempN) == 0){
				//printf("%s\n", dTempN);
				//printf("%c\n", nameTemp);
            	initialTemp = nameTemp;
            }
            // Find other character's home
			else if (strcmp(initial, dTempN) != 0){
				sprintf(lotrTemp[secondFileTemp].charI, dTempN);
				lotrTemp[secondFileTemp].charB = nameTemp - 65;
				openC = lotrTemp[secondFileTemp].charB + 65;
				sprintf(lotrTemp[secondFileTemp].charW, "%c ",openC);
				secondFileTemp = secondFileTemp + 1;
				//printf("%s\n", dTempN);
				//printf("%c\n", openC);
			}
		}
		fclose(openNumberFile);
		//printf("Bilbo home test: %c\n", initialTemp);

		//Series of if and else if statement for routing algorithms
		//Reference program for Dijkstra’s Algorithm in C
		//https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
		
		//SHP ALGORITHM
		if (0 == (strcmp(argv[3], "SHP"))){
			for(int temp = 0; temp < tempCharNumber; temp = temp + 1){
				int tempH[26],tempPred[26],tempVisited[26],count,mindistance,tempNode;
				char SHP[500],cStore;
				int tempSave = 0;
				int data = initialTemp - 65;
				// Initialize temp hops, predecessor and visited
				for (int temp = 0; temp < 26; temp = temp + 1){
					tempH[temp] = 9999;
					tempPred[temp] = -1;
					tempVisited[temp] = -1;
					//printf("%d\n", tempH[temp]);
					//printf("%d\n", tempPred[temp]);
					//printf("%d\n", tempVisited[temp]);
				}
				// Starting node for temp hops and visited
				tempH[lotrTemp[temp].charB] = 0;
				tempVisited[lotrTemp[temp].charB] = 0;
				count = 0;

				while (count < 26){
					mindistance = 9999;
					tempNode = -1;
					// find node at minimum distance
					for (int tempMin = 0; tempMin < 26; tempMin = tempMin + 1){
						if ((tempVisited[tempMin] < 1) && (tempH[tempMin] < mindistance)){
							mindistance = tempH[tempMin];
							tempNode = tempMin;
							//printf("%d\n", tempNode);
						}
					}
					// if dwarf arrives at destination
					if (tempNode == (initialTemp - 65))
						break;
					//check if a better path exists
					tempVisited[tempNode] = 1;
					for(int new = 0; new < 26; new = new + 1){
						// record new paths in tempNode
                        if ((tempVisited[new] < 0) && (tempArray[tempNode][new].mapD > -1)){
                            tempH[new] = tempH[tempNode] + 1;
                            tempVisited[new] = 0;
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
                        // switch to better path in tempNode
                        else if ((tempH[tempNode] + 1 < tempH[new]) && (tempVisited[new] < 1) && (tempArray[tempNode][new].mapD > -1)){
                            tempH[new] = tempH[tempNode] + 1;
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
					}
					//printf("%d\n", tempNode);
					count++;
				}
				
				// Store data into 1D array for characters
				while (tempPred[data] != -1){
					lotrTemp[temp].charH = lotrTemp[temp].charH + 1;
					lotrTemp[temp].charD = lotrTemp[temp].charD + tempArray[(tempPred[data])][data].mapD;
					lotrTemp[temp].charT = lotrTemp[temp].charT + tempArray[(tempPred[data])][data].mapT;
					lotrTemp[temp].charG = lotrTemp[temp].charG + tempArray[(tempPred[data])][data].mapG;
					lotrTemp[temp].charE = lotrTemp[temp].charE + tempArray[(tempPred[data])][data].mapE;
					cStore = data + 65;
					SHP[tempSave] = cStore;
					data = tempPred[data];
					//printf("%d\n", lotrTemp[temp].charH);
					//printf("%d\n", lotrTemp[temp].charD);
					//printf("%d\n", lotrTemp[temp].charT);
					//printf("%d\n", lotrTemp[temp].charG);
					//printf("%d\n", lotrTemp[temp].charE)
					tempSave = tempSave + 1;
				}
				while(tempSave > 0){
					sprintf(lotrTemp[temp].charW, "%s%c ", lotrTemp[temp].charW, SHP[--tempSave]);
					//printf("%d\n", lotrTemp[temp].charW);
				}
			}
		} // END SHP ALGORITHM
		
		//SDP ALGORITHM
		else if (0 == strcmp(argv[3], "SDP")){
			for(int temp = 0; temp < tempCharNumber; temp = temp + 1){
				int tempD[26],tempPred[26],tempVisited[26], count, mindistance, tempNode;
				char SHP[500],cStore;
				int tempSave = 0;
				int data = initialTemp - 65;

				// Initialize temp distance, predecessor and visited
				for (int temp = 0; temp < 26; temp = temp + 1){
					tempD[temp] = 9999;
					tempPred[temp] = -1;
					tempVisited[temp] = -1;
					//printf("%d\n", tempD[temp]);
					//printf("%d\n", tempPred[temp]);
					//printf("%d\n", tempVisited[temp]);
				}
				// Starting node for temp distance and visited
				tempD[lotrTemp[temp].charB] = 0;
				tempVisited[lotrTemp[temp].charB] = 0;
				count = 0;

				while (count < 26){
					mindistance = 9999;
					tempNode = -1;
					// find node at minimum distance
					for (int tempMin = 0; tempMin < 26; tempMin = tempMin + 1){
						if (tempVisited[tempMin] < 1 && tempD[tempMin] < mindistance){
							mindistance = tempD[tempMin];
							tempNode = tempMin;
							//printf("%d\n", tempNode);
						}
					}
					// if dwarf arrives at destination
					if (tempNode == (initialTemp - 65))
						break;
					//check if a better path exists
					tempVisited[tempNode] = 1;
					for(int new = 0; new < 26; new = new + 1){
						// record new distance in tempNode
                        if ((tempVisited[new] < 0) && (tempArray[tempNode][new].mapD > -1)){
                            tempD[new] = tempArray[tempNode][new].mapD + tempD[tempNode];
                            tempVisited[new] = 0;
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
                        // switch to better distance in tempNode
                        else if ((tempArray[tempNode][new].mapD + tempD[tempNode] < tempD[new]) && (tempVisited[new] < 1) && (tempArray[tempNode][new].mapD > -1)){
                            tempD[new] = tempArray[tempNode][new].mapD + tempD[tempNode];
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
					}
					//printf("%d\n", tempNode);
					count++;
				}
				// Store data into 1D array for characters
				while (tempPred[data] != -1){
					lotrTemp[temp].charH = lotrTemp[temp].charH + 1;
					lotrTemp[temp].charD = lotrTemp[temp].charD + tempArray[(tempPred[data])][data].mapD;
					lotrTemp[temp].charT = lotrTemp[temp].charT + tempArray[(tempPred[data])][data].mapT;
					lotrTemp[temp].charG = lotrTemp[temp].charG + tempArray[(tempPred[data])][data].mapG;
					lotrTemp[temp].charE = lotrTemp[temp].charE + tempArray[(tempPred[data])][data].mapE;
					cStore = data + 65;
					SHP[tempSave] = cStore;
					data = tempPred[data];
					//printf("%d\n", lotrTemp[temp].charH);
					//printf("%d\n", lotrTemp[temp].charD);
					//printf("%d\n", lotrTemp[temp].charT);
					//printf("%d\n", lotrTemp[temp].charG);
					//printf("%d\n", lotrTemp[temp].charE);
					tempSave = tempSave + 1;
				}
				while(tempSave > 0){
					sprintf(lotrTemp[temp].charW, "%s%c ", lotrTemp[temp].charW, SHP[--tempSave]);
					//printf("%d\n", lotrTemp[temp].charW);
				}
			}
		}// END SDP ALGORITHM
		
		//STP ALGORITHM
		else if (0 == strcmp(argv[3], "STP")){
			for(int temp = 0; temp < tempCharNumber; temp = temp + 1){
				int tempT[26],tempPred[26],tempVisited[26],count,mindistance,tempNode;
				char SHP[500],cStore;
				int tempSave = 0;
				int data = initialTemp - 65;
				// Initialize temp time, predecessor and visited
				for (int temp = 0; temp < 26; temp = temp + 1){
					tempT[temp] = 9999;
					tempPred[temp] = -1;
					tempVisited[temp] = -1;
					//printf("%d\n", tempT[temp]);
					//printf("%d\n", tempPred[temp]);
					//printf("%d\n", tempVisited[temp]);
				}
				// Starting node for temp hops and visited
				tempT[lotrTemp[temp].charB] = 0;
				tempVisited[lotrTemp[temp].charB] = 0;
				count = 0;

				while (count < 26){
					mindistance = 9999;
					tempNode = -1;
					// find node at minimum distance
					for (int tempMin = 0; tempMin < 26; tempMin = tempMin + 1){
						if ((tempVisited[tempMin] < 1) && (tempT[tempMin] < mindistance)){
							mindistance = tempT[tempMin];
							tempNode = tempMin;
							//printf("%d\n", tempNode);
						}
					}
					// if dwarf arrives at destination
					if (tempNode == (initialTemp - 65))
						break;
					//check if a better path exists
					tempVisited[tempNode] = 1;
					for(int new = 0; new < 26; new = new + 1){
						// record new times in tempNode
                        if ((tempVisited[new] < 0) && (tempArray[tempNode][new].mapD > -1)){
                            tempT[new] = tempArray[tempNode][new].mapT + tempT[tempNode];
                            tempVisited[new] = 0;
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
                        // switch to better time in tempNode
                        else if ((tempArray[tempNode][new].mapT + tempT[tempNode] < tempT[new]) && (tempVisited[new] < 1) && (tempArray[tempNode][new].mapD > -1)){
                            tempT[new] = tempArray[tempNode][new].mapT + tempT[tempNode];
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
					}
					//printf("%d\n", tempNode);
					count++;
				}
				
				// Store data into 1D array for characters
				while (tempPred[data] != -1){
					lotrTemp[temp].charH = lotrTemp[temp].charH + 1;
					lotrTemp[temp].charD = lotrTemp[temp].charD + tempArray[(tempPred[data])][data].mapD;
					lotrTemp[temp].charT = lotrTemp[temp].charT + tempArray[(tempPred[data])][data].mapT;
					lotrTemp[temp].charG = lotrTemp[temp].charG + tempArray[(tempPred[data])][data].mapG;
					lotrTemp[temp].charE = lotrTemp[temp].charE + tempArray[(tempPred[data])][data].mapE;
					cStore = data + 65;
					SHP[tempSave] = cStore;
					data = tempPred[data];
					//printf("%d\n", lotrTemp[temp].charH);
					//printf("%d\n", lotrTemp[temp].charD);
					//printf("%d\n", lotrTemp[temp].charT);
					//printf("%d\n", lotrTemp[temp].charG);
					//printf("%d\n", lotrTemp[temp].charE)
					tempSave = tempSave + 1;
				}
				while(tempSave > 0){
					sprintf(lotrTemp[temp].charW, "%s%c ", lotrTemp[temp].charW, SHP[--tempSave]);
					//printf("%d\n", lotrTemp[temp].charW);
				}
			}
		}// END STP ALGORITHM
		
		//FTP ALGORITHM
		else if (0 == strcmp(argv[3], "FTP")){
			printf("Try other file\n");
		}// END FTP ALGORITHM
		
		else{
			printf("Routing algorithm input is wrong");
			printf("\n\n\n\n");
			exit(-1);
		}

		// Begin display printing part similar to example output
        // Begin printing individual dwarf stats
		printf("Routing algorithm input: %s\n", argv[3]);
		printf("Destination is always Bilbo's home at node: %c", initialTemp);
		printf("\n\n////////////////////////////////////////////////////////////////\n\n");
		printf("DWARF - HOME - HOPS - - DIST  - TIME - GOLD - TROLLS - PATH\n");
		char fileTEST[100];
		strcpy(fileTEST, "test-");
		strcat(fileTEST, argv[3]);
		strcat(fileTEST, ".txt");
		FILE *printToFile;
		printToFile = fopen(fileTEST,"w");
		if(printToFile == NULL)
			exit(-1);
		fprintf(printToFile, "Routing algorithm input: %s\n", argv[3]);
		fprintf(printToFile, "Destination is always Bilbo's home at node: %c", initialTemp);
		fprintf(printToFile, "\n\n////////////////////////////////////////////////////////////////\n\n");
		fprintf(printToFile, "DWARF - HOME - HOPS - - DIST  - TIME - GOLD - TROLLS - PATH\n");
		//Display character data
		for (int printTemp; printTemp < tempCharNumber; printTemp = printTemp + 1){
			printf("%s",lotrTemp[printTemp].charI);
            printf("\t%c",lotrTemp[printTemp].charB + 65);
            printf("\t%d",lotrTemp[printTemp].charH);
            printf("\t%d",lotrTemp[printTemp].charD);
            printf("\t%d",lotrTemp[printTemp].charT);
            printf("\t%d",lotrTemp[printTemp].charG);
            printf("\t%d",lotrTemp[printTemp].charE);
            printf("\t%s\n",lotrTemp[printTemp].charW);
            // print to file 
            
            fprintf(printToFile, "%-3s",lotrTemp[printTemp].charI);
            fprintf(printToFile, "\t%3c",lotrTemp[printTemp].charB + 65);
            fprintf(printToFile, "\t%5d",lotrTemp[printTemp].charH);
            fprintf(printToFile, "\t%8d",lotrTemp[printTemp].charD);
            fprintf(printToFile, "\t%4d",lotrTemp[printTemp].charT);
            fprintf(printToFile, "\t%3d",lotrTemp[printTemp].charG);
            fprintf(printToFile, "\t%6d",lotrTemp[printTemp].charE);
            fprintf(printToFile, "\t%17s\n",lotrTemp[printTemp].charW);
		}
		
		//Average part
		// Add total parts from dwarfs and divide by number of dwarfs for average parts
		
		//Hops number
		float hopNumber = 0;
		for (int hopTemp = 0; hopTemp < tempCharNumber; hopTemp = hopTemp + 1){
			hopNumber = hopNumber + lotrTemp[hopTemp].charH;
			//printf("\t\t%0.2f", hopNumber);
		}
		hopNumber = hopNumber/tempCharNumber;
		//printf("\t\t%0.2f", hopNumber);

		//Distance number
		float distanceNumber = 0;
		for(int distanceTemp = 0; distanceTemp < tempCharNumber; distanceTemp = distanceTemp + 1){
			distanceNumber = distanceNumber + lotrTemp[distanceTemp].charD;
			//printf("\t%0.1f", distanceNumber);
		}
		distanceNumber = distanceNumber/tempCharNumber;	
		//printf("\t%0.1f", distanceNumber);

		//Time number
		float timeNumber = 0;
		for(int timeTemp = 0; timeTemp < tempCharNumber; timeTemp = timeTemp + 1){
			timeNumber = timeNumber + lotrTemp[timeTemp].charT;
			//printf("\t%0.1f", timeNumber);
		}
		timeNumber = timeNumber/tempCharNumber;
		//printf("\t%0.1f", timeNumber);
		
		//Gold number
		float goldNumber = 0;
		for (int goldTemp = 0; goldTemp < tempCharNumber; goldTemp = goldTemp + 1){
			goldNumber = goldNumber + lotrTemp[goldTemp].charG;
			//printf("\t%0.1f", goldNumber);
		}
		goldNumber = goldNumber/tempCharNumber; 
		//printf("\t%0.1f", goldNumber);
		
        //troll number
		float trollNumber = 0;
		for (int trollTemp = 0; trollTemp < tempCharNumber; trollTemp = trollTemp + 1){
			trollNumber = trollNumber + lotrTemp[trollTemp].charE;
			//printf("\t%0.1f\n\n", trollNumber);
		}
		trollNumber = trollNumber/tempCharNumber; 
		//printf("\t%0.1f\n\n", trollNumber);
     
		// Print all averages similar to example output
        printf("\nAVERAGE");
        printf("\t\t%0.2f", hopNumber);
        printf("\t%0.1f", distanceNumber);
        printf("\t%0.1f", timeNumber);
        printf("\t%0.1f", goldNumber);
        printf("\t%0.1f\n\n", trollNumber);
		printf("////////////////////////////////////////////////////////////////\n\n");
		printf("\n\n\n\n");
		//print to file
		fprintf(printToFile,"\nAVERAGE\t");
        fprintf(printToFile,"\t\t%0.2f", hopNumber);
        fprintf(printToFile,"\t%0.1f", distanceNumber);
        fprintf(printToFile,"\t%0.1f", timeNumber);
        fprintf(printToFile,"\t%0.1f", goldNumber);
        fprintf(printToFile,"\t%0.1f\n\n", trollNumber);
		fprintf(printToFile,"////////////////////////////////////////////////////////////////\n\n");
		fprintf(printToFile,"\n\n\n\n");
		fclose(printToFile);
		return 0;
    }
    // Coding for incorrect amount of command line arguments
    else{
		printf("Missing some command line arguments\n");
		printf("input map, then home, then routing algorithm");
		printf("\n\n\n\n");
		exit(-1);
	}
	//printf("\n\n\n\n");
}
