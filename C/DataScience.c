#include <stdio.h>
#include <stdlib.h>
#include "/nop/nop.h"
#include <math.h>


int ColCount(char * file) 
{
	int Cols = 0; 
	char Text;
	FILE * CsvRead = fopen(file,"r");
	if(CsvRead == NULL)
	{
		printf("Failed to openfile\n");
	}
	Text = getc(CsvRead);
	while(Text != '\n')
	{	
		if(Text == ',')
		{
			Cols++;
		} 
		Text = getc(CsvRead);
	}
	fclose(CsvRead);
	return Cols + 1; 
}

int RowCount(char * file)
{
	char Text;
	int Count = -1; 
	FILE * CsvRead = fopen(file,"r");
	if(CsvRead == NULL)
	{
		printf("Failed to openfile\n");
		return 1;
	}
	Text = getc(CsvRead);
	while(Text != EOF)
	{	
		if(Text == '\n')
		{
			Count++; 	
		} 
		Text = getc(CsvRead);
	}
	fclose(CsvRead);
	return Count;
}

//dataframe 
void DataFrame(char * file,int row,int col,double DF[row][col])
{
	int Row = 0; 
	int Col = 0; 
	int CharNum = 1; 
	char * Data = malloc(sizeof(char) * CharNum);
	int Count = 0;  
	char Text; 
	FILE * CsvRead = fopen(file,"r");
	if(CsvRead == NULL)
	{
		printf("Failed to openfile\n");
	}
	Text = getc(CsvRead);
	while(Text != '\n')
	{
		//Skips the first line 
		Text = getc(CsvRead);
	}
	Text = getc(CsvRead);
	while(Text != EOF)
	{
		
		switch(Text)
		{
			case ',':
				Data[CharNum - 1] = '\0';
				DF[Row][Col] = StrToDouble(Data);
				Col++; 
				CharNum = 1;   
				break;

			case '\n':
				Data[CharNum - 1] = '\0';
				DF[Row][Col] = StrToDouble(Data);
				CharNum = 1; 
				Col = 0; 
				Row++; 
				Count++; 
				break; 
			default:
				Data[CharNum - 1] = Text; 
				CharNum++; 
				Data = realloc(Data,(sizeof(char) * CharNum));
				break; 
		}
		Text = getc(CsvRead);
	}
	fclose(CsvRead);
	free(Data);
}

void DataFramePrint(char * file,int row, int col, double DF[row][col]) 
{	
	char Text;
	FILE * CsvRead = fopen(file,"r");
	Text = getc(CsvRead);
	if(row > 10)
	{
		row = 10; 
	}
	while(Text != '\n')
	{	
		if(Text == ',')
		{
			printf("\t");
		} 
		else
		{
			printf("%c",Text);
		}
		Text = getc(CsvRead);
	}
	printf("\n");	
	for(int i = 0;i < row;i++)
	{
		for(int j = 0;j < col;j++)
		{
			printf("%lf |",DF[i][j]);
		}
		printf("\n");
	}
	fclose(CsvRead);
}

//readcsv
void ReadCsv(char * file)
{
	char Text;
	int Count = 0; 
	FILE * CsvRead = fopen(file,"r");
	if(CsvRead == NULL)
	{
		printf("Failed to openfile\n");
	}
	printf("N "); 
	Text = getc(CsvRead);
	while(Text != '\n')
	{	
		if(Text == ',')
		{
			printf("\t");
		} 
		else
		{
			printf("%c",Text);
		}
		Text = getc(CsvRead);
	}
	while(Text != EOF)
	{
		switch(Text)
		{
			case ',':
				printf("\t\t");
				break;
			case '\n':
				if(Count < RowCount(file))
				{
					printf("\n%i ",Count);
					Count++; 
				}
				break; 
			default:
				printf("%c",Text);
				break; 
		}
		Text = getc(CsvRead);
	}
	printf("\n");
	fclose(CsvRead);
}

double Sigmoid(double Z) 
{
	return (1.0/( 1.0+exp(-1.0 * Z)));
}

/*
double Sigmoid(double z)
{
    if (z >= 0) {
        return 1.0 / (1.0 + exp(-z));
    } 
    else {
        double exp_z = exp(z);
        return exp_z / (1.0 + exp_z);
    }
}
*/

double LogLiklyHood(double Lamda,double * W,int Row,int Col,double DF[Row][Col]) 
{
	double Z,LL,P,prob; 
        LL = 0.0;
	P = 0.0;  
	for(int i = 0;i < Row;i++) 
	{
		Z = 0.0;
		for(int x = 1;x < Col;x++)
		{
			Z = Z + W[x]*DF[i][x - 1];
		}
		Z = Z + W[0];
		prob = Sigmoid(Z);
		//if (prob < 1e-15) prob = 1e-15;
		//if (prob > 1 - 1e-15) prob = 1 - 1e-15;
		//LL = LL + DF[i][Col - 1]*log( Sigmoid(Z) ) + (1-DF[i][Col - 1]) * log(1 - Sigmoid(Z));
		LL = LL + DF[i][Col - 1]*log( prob ) + (1-DF[i][Col - 1]) * log(1 - prob);
	}
	for(int i = 1;i < Col;i++)
	{
		P = P + pow(W[i],2);
	}
	//return LL - Lamda * P; 
	return LL; 
}

void GradientDesent(double * W,double * PD,int Row,int Col,double A,double Lamda,double DF[Row][Col]) 
{
	double Z;
	for(int i = 0;i < Col;i++)
	{
		PD[i] = 0.0; 
	}
	//INTER
	for(int i = 0;i < Row;i++)
	{
		Z = 0.0;
		for(int x = 1;x < Col ;x++)
		{	
			Z = Z + W[x]*DF[i][x - 1];
		}
		Z = Z + W[0];
		//Z = W[1]*DF[i][0] + W[0];
                PD[0] = PD[0] + ((DF[i][Col - 1] - Sigmoid(Z)) * 1);
	}
	for(int a = 1;a < Col;a++)
	{	
		for(int i = 0;i < Row;i++)
		{	
			Z = 0.0;
			for(int x = 1;x < Col ;x++)
			{	
				Z = Z + W[x]*DF[i][x - 1];
			}
			Z = Z + W[0];
			PD[a] = PD[a] + ((DF[i][Col - 1] - Sigmoid(Z)) * DF[i][a - 1]);
		}
		PD[a] = PD[a] - 2 * Lamda * W[a]; 
	} 	
	//NEW WEIGHTS 
	for(int i = 0;i<Col;i++)
	{
		W[i] = W[i] + A * PD[i];
	}
}

void LogisticRegression(double Lamda,double Alpha,int Iteration,int Row,int Col,int TestRow,double DF[Row][Col],double TD[TestRow][Col]) 
{
	//Weights
	double Prediction; 
	double RS[TestRow]; 
	double W[Col];
	double PD[Col];
	printf("%i\n",Col);
	//Initial values
	for(int i = 0;i < Col;i++)
	{
		W[i] = 0.0; 	
	}	
	printf("LL SCORE FIRST:%lf\n",LogLiklyHood(Lamda,W,Row,Col,DF)); 
	//MAIN LOOP 
	for(int i = 0;i < Iteration;i++)
	{	
		printf("LL SCORE:%lf\n",LogLiklyHood(Lamda,W,Row,Col,DF)); 
		GradientDesent(W,PD,Row,Col,Alpha,Lamda,DF);
	}
	//final values 
	for(int i = 0;i < Col;i++)
	{
		printf("Weight %i : %.10lf\n",i,W[i]); 
	}
	// filling the results array to compare. 
	for(int i = 0;i < TestRow;i++)
	{
		Prediction = 0.0; 
		for(int j = 1;j < Col;j++)
		{
				
			Prediction = Prediction + (W[j]*TD[i][j-1]); 
		}
		Prediction = Prediction + W[0];
		Prediction = Sigmoid(Prediction);
		if(Prediction >= 0.5)
		{
			Prediction = 1.0;
		}	
		else
		{
			Prediction = 0.0; 
		}
		//array
		RS[i] = Prediction;
	}
	int Count; 
	for(int i = 0;i < TestRow;i++)
	{
		if(RS[i] == TD[i][Col-1])
		{
			Count++; 
		}
	}
	printf("Count : %i. Row: %i\n",Count,TestRow);	
	printf("Accuracy= %f%\n",((double)Count/TestRow) * 100);
}

void Scale(int Row, int Col, double DF[Row][Col])
{
	double Mean,Sd;
        for(int j = 0;j < Col - 1;j++)
        {
                Mean = 0;
                Sd = 0;
                for(int i = 0;i< Row;i++)
                {
                        //Mean
                        Mean = Mean + DF[i][j];
                }
                Mean = Mean / Row;
                //SD
                for(int i = 0;i<Row;i++)
                {
                        Sd = Sd + pow(DF[i][j] - Mean,2);
                }
                Sd = Sd / Row;
                Sd = sqrt(Sd);
                //new values
                for(int i = 0;i < Row;i++)
                {
                        DF[i][j] = (DF[i][j] - Mean) / Sd;
                }
        }
}
