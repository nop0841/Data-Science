#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char * Ninput(char *User)
{
	int CharNum = 1; 
	char Characters;
	char * Text = (char *)malloc(sizeof(char) * CharNum);
	printf("%s",User);
	while(Characters = getchar())
	{
		if(Characters != '\n')
		{
			Text = (char *)realloc(Text,sizeof(char) * CharNum);
			Text[CharNum - 1] = Characters; 
			CharNum++;
		}
		else 
		{
			break;
		}
	}
	return Text;
}


double StrToDouble(char * Text)
{
        int Dot = -2;
        int i = 0;
        double ASCII;
	double Sign = 1.0; 
        double Number = 0;
        while(Text[i] != '\0')
        {
                if(Text[i] == '.')
                {
                        Dot = i;
                }
		else if(Text[i] == '-')  
		{
			Sign = Sign * -1.0; 
		}
                else
                {
                        ASCII = (double)(Text[i] - 48);
                        Number = ((Number * 10) + ASCII) * Sign;
                }
                i++;
        }
        if(Dot != -2)
        {
                return (Number / pow(10,i - Dot - 1)) * Sign;
        }
        return Number;
}
