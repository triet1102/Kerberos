#ifndef INTTOSTRING_H_   
#define INTTOSTRING_H_

//function use to convert integer to string (in linux we dont have itoa() )
void reverse(char s[]){
     int i, j;
     char c;
     for (i = 0, j = strlen(s)-1; i<j; i++, j--){
     	c = s[i];
        s[i] = s[j];
        s[j] = c;
     }
}

void intToString(int n, char s[]){
	int i, sign;
	if ((sign = n) < 0)  
		n = -n;         
	i = 0;
	do {       
		s[i++] = n % 10 + '0';  
	}while ((n /= 10) > 0);     
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}




#endif
