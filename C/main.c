#include <stdio.h>
#include <math.h>
#include "/nop/DataScience.h"

int main() 
{
	//Training 
	char TrainData[] = "train.csv";
	char TestData[] = "test.csv";
	int Row = RowCount(TrainData); 
	int Col = ColCount(TrainData); 
	int TestRow = RowCount(TestData);
	double DF[Row][Col];
	double TD[TestRow][Col];
	DataFrame(TrainData,Row,Col,DF);
	DataFrame(TestData,TestRow,Col,TD);
	Scale(Row,Col,DF);	
	Scale(TestRow,Col,TD);	
	int Iteration = 10000; 
	double Alpha = 0.001;
	double Lamda = 39; 
	LogisticRegression(Lamda,Alpha,Iteration,Row,Col,TestRow,DF,TD);
	return 0; 	
}
