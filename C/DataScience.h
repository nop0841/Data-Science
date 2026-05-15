//DataFrame stuff 
int ColCount(char * file);
int RowCount(char * file);
void ReadCsv(char * file);
void DataFrame(char * file,int Row,int Col,double DF[Row][Col]);
void DataFramePrint(char * file,int row, int col,double DF[row][col]);
//Logistic Regression


double Sigmoid(double Z);
double LogLiklyHood(double Lamda,double * W,int Row,int Col,double DF[Row][Col]); 
void GradientDesent(double * W,double * PD,int Row,int Col,double A,double Lamda,double DF[Row][Col]); 
void LogisticRegression(double Lamda,double Alpha,int Iteration,int Row,int Col,int TestRow,double DF[Row][Col],double TD[TestRow][Col]); 
void Scale(int Row, int Col, double DF[Row][Col]);






