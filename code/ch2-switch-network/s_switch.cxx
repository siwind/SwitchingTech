#include <stdio.h>

#define NUM_TS  4    //每帧的时隙数
#define NUM_HW  3    //HighWay线数目：3x3的S接线器

int cm[NUM_HW][NUM_TS];   //控制存储器, cm[0],cm[1],..., 代表每个控制存储器

//每条HW线上的输入一帧的语音信息, sp_in[0],sp_in[1],...
char sp_in[NUM_HW][NUM_TS] = {{'A','B','C','D'},{'6','7','8','9'},{'E','F','G','H'}};

//每条HW线上的输出一帧的语音信息
char sp_out[NUM_HW][NUM_TS] = {'0'};

int c_mode = 0;            //控制方式: 0-输入控制, 1-输出控制


char tolower(char c)
{//字母转换为小写
    if( c>='A' && c<='Z' ) c = c + ('a'-'A');
    return c;
}

//显示控制存储器内容
void showSwitch()
{
	int i=0,j=0;
	
	printf("\n");
	printf("S接线器信息: \n");
	printf("一帧时隙数: %d \n", NUM_TS);
	printf("交换容量： %d x %d \n", NUM_HW,NUM_HW);
	
	printf("控制方式：");
	if( c_mode == 0 ) printf("输入控制\n");
	else printf("输出控制\n");
	
	printf("控制存储器内容：\n");
	for(i=0;i<NUM_HW;i++){
		printf("第 %d 号控制存储器内容：", i);
		for(j=0;j<NUM_TS;j++){
			printf("%d  ", cm[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\n");
}

//设置控制方式
void  setMode()
{
	int c = 0;
	printf("请输入控制方式： 0-输入控制, 1-输出控制 \n");
	printf("你的选择: ");
	scanf("%d", &c);
	if( c == 0){
		c_mode = 0;
	}else if( c == 1 ){
		c_mode = 1;
	}else{
		printf("未知输入. %d \n", c);
	}
	
}

void setCM()
{
	int i=0;
	int data[NUM_TS]={0};
	
	for(i=0;i<NUM_HW;i++){
		printf("请输入第 %d 个控制存储器内容: ", i); //输入方式： 数字 数字 数字 数字 
		scanf("%d %d %d %d", &data[0],&data[1],&data[2],&data[3]);
		if( data[0] >=0 && data[0] < NUM_TS) cm[i][0] = data[0];
		if( data[1] >=0 && data[1] < NUM_TS) cm[i][1] = data[1];
		if( data[2] >=0 && data[2] < NUM_TS) cm[i][2] = data[2];
		if( data[3] >=0 && data[3] < NUM_TS) cm[i][3] = data[3];
	}
}

//显示语音信息
void showSpeech(char  data[NUM_HW][NUM_TS], const char* tip)
{
	int i=0,j=0;
	printf("%s", tip);
	
	for(i=0;i<NUM_HW;i++){//第i号 HW线内容
		printf("第 %d 号HW线语音信息：", i);
		for(j=0;j<NUM_TS;j++) printf("%c ",data[i][j]);
		printf("\n");
	}
}

//执行交换
void doSwitch()
{
	
	int i=0,j=0,k=0; //i-当前的时隙, j-当前的入线, k-当前的出线
	
	//
	showSpeech(sp_in,"交换之前\n");
	
	char ch = '\0';
	for(i=0;i<NUM_TS;i++){  //对每个时隙进行交换
		
		for(j=0;j<NUM_HW;j++){
			ch = sp_in[j][i];   //第j号HW线上， 第i时隙的 输入语音信息
			
			//======================
			//作业的内容
			//k = ?  找到交叉的出线号
			//if( c_mode == 0 )  k = ?      //输入控制
			//else k = ?                    //输出控制
			//
			//======================
			
			
			sp_out[k][i] = ch;   //输入的语音信息被交换到输出的HW线k上。
		}
		
	}
	
	//
	showSpeech(sp_out,"交换之后\n");
	
}

int menu()
{
    char  ch = 'q';
	char  str[255]={'\0'};
    do{
        printf("0. 显示当前S-接线器信息\n");
        printf("1. 选择控制方式: 输入控制/输出控制\n");
        printf("2. 设置CM的内容\n");
        printf("3. 执行交换\n");
        printf("q. 退出系统\n");
        printf("请输入你的选择: ");
        scanf("%s", &str);

        ch = tolower(str[0]); //转为小写字母
        if(ch=='0'){
			showSwitch();
        }else if(ch=='1'){
			setMode();
        }else if(ch=='2'){
			setCM();
        }else if(ch=='3'){
			doSwitch();
        }else if(ch!='q'){
            printf("\n未知的命令. %c \n", ch);
        }

    }while(ch!='q');

    return 0;
}


int main()
{
    menu();
    printf("再见.\n");
    return 0;
}
