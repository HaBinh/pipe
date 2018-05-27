#include <stdio.h>
#include <unistd.h>
#include<stdio.h>
#define SIZE 1024 * 10
#define MAX 4000

// STACK
typedef struct stack_t{
	char elements[MAX];
	int top;
} stack;

int isEmpty(stack S){
	return S.top<=-1;
}
int isFull(stack S){
	return S.top >= MAX-1;
}
void create(stack *S){
	S->top=-1;
}
void push(stack *S, char a){
	if(!isFull(*S)){
		S->elements[++S->top] = a;
	}
}
char pop(stack *S){
	if(!isEmpty(*S)){
		return S->elements[S->top--];
	}
	return 0;
}
char peek(stack *S){
	if(!isEmpty(*S)){
		return S->elements[S->top];
	}
	return 0;
}
void print(stack S){
	int i;
	for(i=0;i<=S.top;i++){
		printf("%c ",S.elements[i]);
	}
}
// END STACK

// Thu tu uu tien cac toan tu
int ktuutien(char a)
{
	if (a == '-')
		return 0;
	if (a == '+')
		return 0;
	if (a == '*')
		return 1;
	if (a == '/')
		return 1;
}
int kiemtraso(char a)
{
	if ((a >= '0' && a <= '9') || a == '.')
		return 1;
	return 0;
}
int kttoantu(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	return 0;
}
int toanhang(char a)
{
	if (a >= 48 && a <= 57)
		return 1;
	return 0;
}

/*********************ham` chuyen tu 1 bieu thuc trung to--->hau to *************/
int conver(char a[], char b[])
{
	stack k;
	create(&k);
	int dem = 0;
	for (int i = 0; i < strlen(a); i++)
	{
		if (kttoantu(a[i]) && kttoantu(a[i + 1]))           ///kiem tra du lieu dau vao`
			return 0;
		if ((a[i] >= 97 && a[i] <= 122) || (a[i] >= 65 && a[i] <= 90))
			return 0;
	}
	for (int i = 0; i < strlen(a); i++)
	{
		char ch = a[i];
		if (kiemtraso(ch))
		{
			b[dem++] = ch;
			if (kttoantu(a[i + 1]))
				b[dem++] = ' ';            //dau cach dung de Phan biet giua cac so co nhieu` chu so voi nhau
		}
		if (ch == '(')
			push(&k,ch);
		if (kttoantu(ch))
		{
			if (!isEmpty(k))
			{
				if ((kttoantu(peek(&k))) && (ktuutien(ch) == ktuutien(peek(&k)) || ktuutien(ch) < ktuutien(peek(&k))))                  // cau lenh nay` kiem tra do uu tien giua cac toan tu
				{
					char m;
					m = pop(&k);
					b[dem++] = m;
					push(&k,ch);
				}
				else
				{
					push(&k,ch);
				}
			}
			else
				push(&k,ch);
		}
		if (ch == ')')   // neu Phat hien dau ) thi ta pop cho toi khi gap dau '(" thi` dung`
		{
			char d;
			while (1)
			{
				d=pop(&k);
				if (d == '(')
					break;
				b[dem++] = d;
			}
		}
	}

	// lay toan tu con lai trong stack...
	while (!isEmpty(k))
	{
		char m;
		char n;
		m=pop(&k);
		b[dem++] = m;
	}

	b[dem] = '\0';
}
float doi(char a)
{
	switch (a)
	{
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case '0': return 0;
	}
}

//// ham` bien doi chuoi sang dang so
float biendoi(char a[])
{
	float d = 0;
	int n = strlen(a);
	if (strlen(a))
	{
		for (int i = 0; i < n; i++)
		{
			if (a[i] == '.')
			{
				int dem = 1;
				float bd1 = 1, bd = 0;

				for (int j = i + 1; j < n; j++)
				{
					for (int i = 0; i < dem; i++)
						bd1 = bd1 * 10;
					bd = bd + doi(a[j]) / bd1;
				}
				d = d + bd;
				break;
			}
			else
				d = d * 10 + doi(a[i]);
		}

		return d;
	}
	return 0;
}

// Tinh toan bieu thuc hau to
float tinhtoan(char pos[SIZE])
{
	char ch = '\0';
	int dem1 = 0;
	float data[1000000];
	char postfix[10000];

    conver(pos,postfix);
    pos=postfix;
    int n = strlen(pos);
	for (int i = 0; i < n;)
	{
		char b[100];
		int dem = 0;
		while (pos[i] != ' '&&i < n&&!kttoantu(pos[i]))
		{
			b[dem++] = pos[i++];
		}
		if (dem)
		{
			b[dem] = '\0';
			data[dem1++] = biendoi(b);
		}
		if (kttoantu(pos[i]))
		{
			switch (pos[i])
			{
			case '+':
			{
						float temp = data[dem1 - 1] + data[dem1 - 2];
						data[dem1 - 2] = temp;
						dem1--;
			}break;
			case '-':
			{
						float temp = data[dem1 - 2] - data[dem1 - 1];
						data[dem1 - 2] = temp;
						dem1--;
			}break;
			case '*':
			{
						float temp = data[dem1 - 1] * data[dem1 - 2];
						data[dem1 - 2] = temp;
						dem1--;
			}
				break;
			case '/':
			{
						float temp = data[dem1 - 2] / data[dem1 - 1];
						data[dem1 - 2] = temp;
						dem1--;
			}break;
			}

		}
		i++;
	}
	return data[0];
}

void reader(FILE* stream)
{
  char buffer[SIZE];
  if(!feof(stream) && !ferror(stream) && fgets(buffer,sizeof(buffer),stream) != NULL) {
    fputs(buffer,stdout);
  } else {
    fputs("Something went wrong (Invalid expression...)\n",stdout);
  }
}


int main()
{
  int fds_1[2]; //pipe 1 (result)
  int fds_2[2]; //pipe 2 (inputString)

  pid_t pid;
  pipe(fds_1);
  pipe(fds_2);

  // Read 0, Write 1
  //ParentRead      fds_1[0]
  //ParentWrite     fds_2[1]
  //ChildRead       fds_2[0]
  //ChildWrite      fds_1[1]

  pid = fork();
  if(pid == (pid_t) 0)
  {
    /* Child */
    sleep(1);
    FILE* stream;
    close(fds_2[1]);
    stream = fdopen(fds_2[0], "r");

    char buffer[SIZE];
    fgets(buffer,sizeof(buffer),stream);
    if(sizeof(buffer)>0){
        printf("\n%s\n", "---------- START B -----------");
    }
    char strReceive[SIZE];
    char result[SIZE] = "Result: ";
    char tmpStr[SIZE];

    // Read inputString from parent
    sscanf(buffer, "%s", &strReceive);
    printf("Process B receive expression is %s\n", strReceive);
    close(fds_2[0]);
    printf("%s\n", "Do calculating ...");

    sprintf(tmpStr, "%f", tinhtoan(strReceive));     //tmpStr = tinhtoan(strReceive)
    strcat(result, tmpStr);                          //result += tmpStr

    printf("%s\n", "Done calculate");
    printf("%s\n", "Process B send back result to process A");
    // Write back data (result) to parent.
    close(fds_1[0]);
    stream = fdopen(fds_1[1], "w");
    fprintf(stream, "%s\n", result);
    fflush(stream);
    printf("%s\n", "---------- END B -----------");
    close(fds_1[1]);
  }
  else
  {
    /* Parent */
    FILE* stream;
    close(fds_2[0]);
    stream = fdopen(fds_2[1], "w");

    // The string (inputString) write to child process for calculate.
    printf("\n%s\n", "---------- START A -----------");
    char inputString[SIZE];
    printf("Enter expression : ");
	fflush(stdin);
	gets(inputString);
    printf("Writing expression str = %s to child process for calculate.\n", inputString);
    fprintf(stream, "%s\n", inputString);
    fflush(stream);
    close(fds_2[1]);
    sleep(1);

    // Get back data (result) send from child.
    close(fds_1[1]);
    stream = fdopen(fds_1[0], "r");
    printf("\n%s\n", "Process A wait for get data send back from B.");
    reader(stream);
    printf("%s\n", "---------- END A -----------");
    close(fds_1[0]);
  }
  return 0;
}
