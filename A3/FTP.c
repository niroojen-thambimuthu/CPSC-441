
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
		char filename[100];
		char ch;
		int linecount = 0;
		char dTempN[100];
		// get dwarf numbers
		// Copy -homes.txt into filename
		strcpy(filename, argv[2]);  
		// Open file in read-only mode
		fp = fopen(filename,"r");

		// If file opened successfully, then write the string to file
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
		People lortTemp[tempCharNumber];
		int tempNumber;
		for(tempNumber = 0; tempNumber < tempCharNumber; tempNumber = tempNumber +1){
			//set beginning point of character
			lortTemp[tempNumber].charB = -1;
			//set other character factors
			lortTemp[tempNumber].charH = 0;
			lortTemp[tempNumber].charD = 0;
			lortTemp[tempNumber].charT = 0;
			lortTemp[tempNumber].charG = 0;
			lortTemp[tempNumber].charE = 0;
			//printf("%d\n", tempNumber);
			//printf("%d\n", lortTemp[tempNumber].charB);
			//printf("%d\n", lortTemp[tempNumber].charH);
			//printf("%d\n", lortTemp[tempNumber].charD);
			//printf("%d\n", lortTemp[tempNumber].charT);
			//printf("%d\n", lortTemp[tempNumber].charG);
			//printf("%d\n", lortTemp[tempNumber].charE);
		}
		//Set 2D map array
		//2D array map initialization
		Track tempArray[26][26];
		for(int maptemp1 = 0; maptemp1 < 26; maptemp1 = maptemp1 + 1){
			for(int maptemp2 = 0; maptemp2 < 26; maptemp2 = maptemp2 + 1){
				// set initial map topology file
                tempArray[maptemp1][maptemp2].mapG = -1;
				tempArray[maptemp1][maptemp2].mapT = -1;
                tempArray[maptemp1][maptemp2].mapE = -1;
                tempArray[maptemp1][maptemp2].mapD = -1;
                //printf("%d\n", maptemp1);
                //printf("%d\n", maptemp2);
                //printf("%d\n", tempArray[maptemp1][maptemp2].mapG);
                //printf("%d\n", tempArray[maptemp1][maptemp2].mapT);
                //printf("%d\n", tempArray[maptemp1][maptemp2].mapE);
                //printf("%d\n", tempArray[maptemp1][maptemp2].mapD);
			}
		}
		//Read the first file -map.txt
		FILE *openMapFile = fopen(argv[1], "r");
		char firstArray,secondArray;
		int tempD, tempT,tempG,tempTr;
		//Data from map
		while (fscanf(openMapFile, "%c %c %d %d %d %d\n", &firstArray, &secondArray, &tempD, &tempT, &tempG, &tempTr) != EOF){
			tempArray[firstArray - 65][secondArray - 65].mapD = tempD;
			tempArray[firstArray - 65][secondArray - 65].mapT = tempT;
			tempArray[firstArray - 65][secondArray - 65].mapG = tempG;
			tempArray[firstArray - 65][secondArray - 65].mapE = tempTr;
			tempArray[secondArray - 65][firstArray - 65].mapD = tempD;
			tempArray[secondArray - 65][firstArray - 65].mapT = tempT;
			tempArray[secondArray - 65][firstArray - 65].mapG = tempG;
			tempArray[secondArray - 65][firstArray - 65].mapE = tempTr;
			//printf("%d\n", tempArray[firstArray - 65][secondArray - 65].mapD);
			//printf("%d\n", tempArray[firstArray - 65][secondArray - 65].mapT);
			//printf("%d\n", tempArray[firstArray - 65][secondArray - 65].mapG);
			//printf("%d\n", tempArray[firstArray - 65][secondArray - 65].mapE);
			//printf("%d\n", tempArray[secondArray - 65][firstArray - 65].mapD);
			//printf("%d\n", tempArray[secondArray - 65][firstArray - 65].mapT);
			//printf("%d\n", tempArray[secondArray - 65][firstArray - 65].mapG);
			//printf("%d\n", tempArray[secondArray - 65][firstArray - 65].mapE);
		}
		fclose(openMapFile);

		//Read the second file -homes.txt
		FILE *openNumberFile = fopen(argv[2], "r");
		char nameTemp;
		char initialTemp;
		//Data for character home
		tempNumber = 0;
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
				sprintf(lortTemp[tempNumber].charI, dTempN);
				lortTemp[tempNumber].charB = nameTemp - 65;
				openC = lortTemp[tempNumber].charB + 65;
				sprintf(lortTemp[tempNumber].charW, "%c ",openC);
				tempNumber = tempNumber + 1;
				//printf("%s\n", dTempN);
				//printf("%c\n", openC);
			}
		}
		fclose(openNumberFile);
		//printf("%c\n", initialTemp);

		// Series of if and else if statement for routing algorithms
		//SHP ALGORITHM
		if (0 == (strcmp(argv[3], "FTP"))){
			for(int temp = 0; temp < tempCharNumber; temp = temp + 1){
				int tempTr[26],tempPred[26],tempVisited[26],count,mindistance,tempNode;
				char SHP[500],cStore;
				int tempSave = 0;
				int data = initialTemp - 65;
				// Initialize temp troll, predecessor and visited
				for (int temp = 0; temp < 26; temp = temp + 1){
					tempTr[temp] = 9999;
					tempPred[temp] = -1;
					tempVisited[temp] = -1;
					//printf("%d\n", tempTr[temp]);
					//printf("%d\n", tempPred[temp]);
					//printf("%d\n", tempVisited[temp]);
				}
				// Starting node for temp hops and visited
				tempTr[lortTemp[temp].charB] = 0;
				tempVisited[lortTemp[temp].charB] = 0;
				count = 0;

				while (count < 26){
					mindistance = 9999;
					tempNode = -1;
					// find node at minimum distance
					for (int tempMin = 0; tempMin < 26; tempMin = tempMin + 1){
						if ((tempVisited[tempMin] < 1) && (tempTr[tempMin] < mindistance)){
							mindistance = tempTr[tempMin];
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
						// record new trolls in tempNode
                        if ((tempVisited[new] < 0) && (tempArray[tempNode][new].mapD > -1)){
                        	tempTr[new] = tempArray[tempNode][new].mapE + tempTr[tempNode];
                            tempVisited[new] = 0;
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
                        // switch to less troll path in tempNode
                        else if ((tempArray[tempNode][new].mapE + tempTr[tempNode] < tempTr[new]) && (tempVisited[new] < 1) && (tempArray[tempNode][new].mapD > -1)){
                            tempTr[new] = tempArray[tempNode][new].mapE + tempTr[tempNode];
                            tempPred[new] = tempNode;
                            //printf("%d\n", tempNode);
                        }
					}
					//printf("%d\n", tempNode);
					count++;
				}
				
				// Store data into 1D array for characters
				while (tempPred[data] != -1){
					lortTemp[temp].charH = lortTemp[temp].charH + 1;
					lortTemp[temp].charD = lortTemp[temp].charD + tempArray[(tempPred[data])][data].mapD;
					lortTemp[temp].charT = lortTemp[temp].charT + tempArray[(tempPred[data])][data].mapT;
					lortTemp[temp].charG = lortTemp[temp].charG + tempArray[(tempPred[data])][data].mapG;
					lortTemp[temp].charE = lortTemp[temp].charE + tempArray[(tempPred[data])][data].mapE;
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
					sprintf(lortTemp[temp].charW, "%s%c ", lortTemp[temp].charW, SHP[--tempSave]);
					//printf("%d\n", lotrTemp[temp].charW);
				}
			}
		} // END SHP ALGORITHM
		else{
			printf("FTP only file or routing algorithm input is wrong");
			printf("\n\n\n\n");
			exit(-1);
		}

		// Begin printing part
        
		//Hops number
		float hopNumber = 0;
		int hopTemp = 0;
		for (hopTemp; hopTemp < tempCharNumber; hopTemp = hopTemp + 1)
			hopNumber = hopNumber + lortTemp[hopTemp].charH;
		hopNumber = hopNumber/tempCharNumber;

		//Distance number
		float distanceNumber = 0;
		int distanceTemp = 0;
		for(distanceTemp; distanceTemp < tempCharNumber; distanceTemp = distanceTemp + 1)
			distanceNumber = distanceNumber + lortTemp[distanceTemp].charD;
		distanceNumber = distanceNumber/tempCharNumber;

		//Time number
		float timeNumber = 0;
		int timeTemp = 0;
		for(timeTemp; timeTemp < tempCharNumber; timeTemp = timeTemp + 1)
			timeNumber = timeNumber + lortTemp[timeTemp].charT;
		timeNumber = timeNumber/tempCharNumber;

		//Gold number
		float goldNumber = 0;
		int goldTemp = 0;
		for (goldTemp; goldTemp < tempCharNumber; goldTemp = goldTemp + 1)
			goldNumber = goldNumber + lortTemp[goldTemp].charG;
		goldNumber = goldNumber/tempCharNumber;

        //troll number
		float trollNumber = 0;
		int trollTemp = 0;
		for (trollTemp; trollTemp < tempCharNumber; trollTemp = trollTemp + 1)
			trollNumber = trollNumber + lortTemp[trollTemp].charE;
		trollNumber = trollNumber/tempCharNumber;

     
		// Begin diplay
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
		tempNumber = 0;
		char cStats;
		for (tempNumber; tempNumber < tempCharNumber; tempNumber = tempNumber + 1){
			cStats = lortTemp[tempNumber].charB + 65;
			char cStats = lortTemp[tempNumber].charB + 65;
			printf("%s",lortTemp[tempNumber].charI);
            printf("\t%c",cStats);
            printf("\t%d",lortTemp[tempNumber].charH);
            printf("\t%d",lortTemp[tempNumber].charD);
            printf("\t%d",lortTemp[tempNumber].charT);
            printf("\t%d",lortTemp[tempNumber].charG);
            printf("\t%d",lortTemp[tempNumber].charE);
            printf("\t%s\n", lortTemp[tempNumber].charW);
            // print to file			
            fprintf(printToFile,"%-3s",lortTemp[tempNumber].charI);
            fprintf(printToFile,"\t%3c",cStats);
            fprintf(printToFile,"\t%5d",lortTemp[tempNumber].charH);
            fprintf(printToFile,"\t%8d",lortTemp[tempNumber].charD);
            fprintf(printToFile,"\t%4d",lortTemp[tempNumber].charT);
            fprintf(printToFile,"\t%3d",lortTemp[tempNumber].charG);
            fprintf(printToFile,"\t%6d",lortTemp[tempNumber].charE);
            fprintf(printToFile,"\t%17s\n", lortTemp[tempNumber].charW);
		}
		// Print average
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
