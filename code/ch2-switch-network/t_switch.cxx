#include <stdio.h>

#define NUM_TS  6   //每帧的时隙数

char sm[NUM_TS];   //语音存储器
int  cm[NUM_TS];   //控制存储器

int c_mode = 0;            //控制方式: 0-输入控制, 1-输出控制

char sp_in[NUM_TS]={'\0'};  //输入语音信息
char sp_out[NUM_TS]={'\0'};  //输出语音信息

char tolower(char c)
{//字母转换为小写
    if( c>='A' && c<='Z' ) c = c + ('a'-'A');
    return c;
}

//显示接线器信息
void showSwitch()
{
	int i=0,j=0;
	
	printf("\n");
	printf("T接线器信息: \n");
	printf("一帧时隙数: %d \n", NUM_TS);
	printf("交换容量(时隙x时隙)： %d x %d \n", NUM_TS,NUM_TS);
	
	printf("控制方式：");
	if( c_mode == 0 ) printf("输入控制\n");
	else printf("输出控制\n");
	
	printf("控制存储器内容：");
	for(i=0;i<NUM_TS;i++){
		printf("%d ", cm[i]);
	}
	printf("\n");

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
	
	for(i=0;i<NUM_TS;i++){
		printf("请输入控制存储器内容: ", i); //输入方式： 数字 数字 数字 数字 数字 数字 数字 数字 
		scanf("%d %d %d %d %d %d", &data[0],&data[1],&data[2],&data[3],&data[4],&data[5]);
		if( data[0] >=0 && data[0] < NUM_TS) cm[0] = data[0];
		if( data[1] >=0 && data[1] < NUM_TS) cm[1] = data[1];
		if( data[2] >=0 && data[2] < NUM_TS) cm[2] = data[2];
		if( data[3] >=0 && data[3] < NUM_TS) cm[3] = data[3];
		if( data[4] >=0 && data[4] < NUM_TS) cm[4] = data[4];
		if( data[5] >=0 && data[5] < NUM_TS) cm[5] = data[5];
	}
}

//显示语音信息
void showSpeech(char  data[NUM_TS], const char* tip)
{
	int i=0;
	printf("%s", tip);
	
	printf("HW线语音信息：");
	for(i=0;i<NUM_TS;i++){
		printf("%c ",data[i]);
	}
	printf("\n");
}

//执行交换
void doSwitch()
{
		
	int i=0,j=0,k=0; //i-入线的时隙, j-出线的时隙
	
	//
	printf("请输入语音信息(%d时隙): ", NUM_TS);
	scanf("%c %c %c %c %c %c", &sp_in[0],&sp_in[1],&sp_in[2],&sp_in[3],&sp_in[4],&sp_in[5]);
	
	showSpeech(sp_in,"交换之前\n");
	
	char ch = '\0';
	for(i=0;i<NUM_TS;i++){  //对每个时隙进行交换
		
		ch = sp_in[i];   //输入的第i时隙的话音信息
			
			//======================
			//作业的内容
			//j = ?  找到交换后，在出线上的时隙
			//if( c_mode == 0 )  j = ?      //输入控制
			//else j = ?                    //输出控制
			//
			//======================
			
			
		sp_out[j] = ch;   //输入的语音信息被交换到输出的HW线k上。
		
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
