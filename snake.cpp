#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define LEN sizeof(struct Snake)
struct coord
{
	int x;
	int y;
};               //����ṹ�壬x��ʾ�ᣬy��ʾ��//

struct Snake         //�ߵĽṹ��//
{
	int x;
	int y;
	struct Snake *previous;    //�ߵ�ǰһ��//
	struct Snake *next;        //�ߵĺ�һ��//
}*head,*tail,*p0,*pt,*p1;
int direct;                  //�ߵ��ƶ�������1,2,3,4�ֱ��ʾ��������//                      
int life=1;                    //��ʾ�ߵ�����״̬��1��ʾ���ţ�0��ʾ����//
struct Food    //ʳ��ṹ��//
{
	struct coord cor;   //ʳ������//
	int flag;           //״̬��0��ʾ��û���ԣ�1��ʾ�Ѿ�����//
}food;

struct Poigrass      //���ݽṹ��//
{
    struct coord cor[8];   //ÿ�Ŷ�������,ÿ�ζ���״̬0��ʾ��ʧ�ˣ�1��ʾ����ʾ����Ļ�ϳ���2�Ŷ���//
	int flag;             //״̬//
}poigrass;

struct Mine            //���׽ṹ��//
{
	struct coord cor;   //��������//
	int flag;           //����״̬��0��ʾδ��������1��ʾ����//
}mine;
int cp;           //�ؿ�//
int endscore;     //��¼ÿ����Ϸ����ʱ�ĵ÷�//
int score=0;      //�÷�//
int speed;        //�ٶ�//
int node;         //�ߵĽ���//
int mid;          //��¼�ߵĽ�����һ��//
int m;
int n;
int end_score[5]={0};  //�洢��ߵ÷�//
time_t tim1,tim2;
FILE *fp,*fp1;     //����ָ���ļ���ָ��//


//�Գ�������Ҫ�õ��ĺ�������ȫ������//
void begin();            //��ʼ��Ϸ����˵�����//
void rules();            //��ʾ��Ϸ����//
void map();              //��ԭʼ��ͼ//
void set_food();         //����ʳ��//
void show_food();        //����Ļ�ϻ���ʳ��//
void show_snake();       //��Ļ����ʾ��//
void set_mine();         //���õ���//
void no_poigrass();      //������ʧ//
void show_mine();        //����Ļ���Ǹ���������//
void set_poigrass();     //���ö���//
void set_poigrass1();    //������һ����ɫ��������//
void ju_eat_food();      //�ж����Ƿ�Ե�ʳ��//
void ju_eat_poigrass();  //�ж����Ƿ�Ե�����//
void ju_meet_mine();     //�ж����Ƿ���������//
void snake_move();       //���ƶ����ı�λ��//
void show_snake();       //����Ļ�ϻ�����//
void change();           //�ı��ߵ��ƶ�����//
void select();           //�ؿ�ѡ��//
void design_cp1();       //���õ�һ��//
void design_cp2();       //���õڶ���//
void design_cp3();       //���õ�����//
void print_score();      //�������//
void gameover();         //������Ϸ//
void set_rank();         //�������а�//
void see_rank();         //�鿴���а�//      


//����ÿһ������//
int main()
{
	begin();
	int i;
	fp=fopen("���а�","r");
    for(i=0;i<5;i++)
	    fread(&end_score[i],2,1,fp);
	fclose(fp);
	MOUSEMSG m;                           //���������Ϣ//
    while(true)
	{
	  m=GetMouseMsg();
	  switch(m.uMsg)
	  {
	  case WM_LBUTTONDOWN:
	   if(m.x>=10&&m.y>=130&&m.y<=200&&m.x<=290)
	       design_cp1();
	   if(m.x>=10&&m.y>=230&&m.y<=300&&m.x<=290)
		   rules();
       if(m.x>=10&&m.y>=330&&m.y<=400&&m.x<=290)
		   select();
	   if(m.x>=10&&m.y>=430&&m.y<=500&&m.x<=290)
		   see_rank();
	   if(m.x>=10&&m.y>=530&&m.y<=600&&m.x<=290)
		   exit(0);
	  }
	}
    return 0;
}

void begin()
{
	IMAGE img;
	initgraph(700,630);
	setbkcolor(GREEN);
	cleardevice();
	loadimage(&img,"E:\\5.jpg");
	putimage(0,0,&img);
	setcolor(RED);
	setfont(100,0,"�����п�");
	outtextxy(110,10,"������С��");
	setcolor(WHITE);
	setfont(70,0,"����");
	outtextxy(10,130,"��ʼ��Ϸ");
	setcolor(BROWN);
	setfont(70,0,"����");
	outtextxy(10,230,"��Ϸ����");
	setcolor(YELLOW);
	setfont(70,0,"����");
	outtextxy(10,330,"�ؿ�ѡ��");
	setcolor(BLUE);
	setfont(70,0,"����");
	outtextxy(10,430,"�÷�����");
	setcolor(WHITE);
	setfont(70,0,"����");
	outtextxy(10,530,"�˳���Ϸ");
}

void  rules()
{
	initgraph(850,600);
    setbkcolor(DARKGRAY);
	cleardevice();
	setcolor(LIGHTGREEN);
	setfont(60,0,"��������");
	outtextxy(270,1,"��Ϸ����");
	setcolor(LIGHTCYAN);
	setfont(40,0,"�����п�");
    outtextxy(20,65,"1.����ɫ��С�����ʾ��ζ��ʳ�");
	outtextxy(20,110,"2.��ɫ��ʵ��СԲ��ʾ�ɶ�ĵ��ס�");
	outtextxy(20,160,"3.��ɫ��ʵ��СԲ��ʾ�ɺ޵Ķ��ݡ�");
	outtextxy(20,210,"4.С��ÿ�Ե�һ��ʳ�����������һ�ڡ�");
	outtextxy(20,260,"5.С���������ף�����ᱻը��һ�롣ҪС��Ŷ����");
	outtextxy(20,310,"6,С���������ݣ��������һ�ڡ�ҪС��Ŷ����");
	outtextxy(20,360,"7.С�ߵ�ͷײ�����ܵ�ǽ������");
	outtextxy(20,410,"8.С�ߵ�ͷײ���Լ�������Ҳ��������");
	outtextxy(20,460,"9.�����������ġ��������򣬻ص���ҳ�档");
	outtextxy(20,510,"10.ף�����ˣ�����");
	setcolor(BROWN);
	setfont(60,0,"��������");
    outtextxy(580,520,"����ҳ��");
	MOUSEMSG m; 
	while(true)
	{
	  m=GetMouseMsg();
	  switch(m.uMsg)
	  {
	  case WM_LBUTTONDOWN:
	   if(m.x>=580&&m.y>=520&&m.y<=580&&m.x<=820)
		   main();
	  }
	}
}
void select()
{
	initgraph(640,480);
	setbkcolor(GREEN);
    cleardevice();
	setcolor(YELLOW);
	setfont(80,0,"�����п�");
	outtextxy(200,40,"��һ��");
	outtextxy(200,200,"�ڶ���");
	outtextxy(200,360,"������");
	MOUSEMSG m; 
	while(true)
	{
	  m=GetMouseMsg();
	  switch(m.uMsg)
	  {
	  case WM_LBUTTONDOWN:
	   if(m.x>=200&&m.y>=40&&m.y<=120&&m.x<=440)
		   design_cp1();
	   if(m.x>=200&&m.y>=200&&m.y<=280&&m.x<=440)
		   design_cp2();
	   if(m.x>=200&&m.y>=360&&m.y<=4400&&m.x<=440)
		   design_cp3();
	  }
	}
}
void see_rank()
{
	initgraph(700,600);
	setbkcolor(DARKGRAY);
	cleardevice();
	char str[10];
	setfont(80,0,"�����п�");
	setcolor(LIGHTGREEN);
	outtextxy(220,20,"���а�");
	setcolor(YELLOW);
	setfont(30,0,"��������");
	sprintf(str,"1 :   %d",end_score[0]);
	outtextxy(280,120,str);
	sprintf(str,"2 :   %d",end_score[1]);
	outtextxy(280,200,str);
	sprintf(str,"3 :   %d",end_score[2]);
	outtextxy(280,280,str);
	sprintf(str,"4 :   %d",end_score[3]);
	outtextxy(280,360,str);
	sprintf(str,"5 :   %d",end_score[4]);
	outtextxy(280,440,str);
}
void set_rank()
{
	int i,j,k;
	k=0;
	for(i=0,j=0;i<5;i++)
	{
		if(endscore>end_score[i])
		{
			k=end_score[i];
			end_score[i]=endscore;			
			break;
		}
	}
	j=i;
	if(k!=0&&j!=4)
	{
	for(i=4;i>=j+2;i--)
		end_score[i]=end_score[i-1];
    end_score[j+1]=k;	
	}
	fp1=fopen("���а�","w");
	   for(i=0;i<10;i++)
		  fwrite(&end_score[i],2,1,fp1);
	   fclose(fp1);
}

void map()
{
	initgraph(900,600);
    setbkcolor(BLACK);
	cleardevice();
	setcolor(YELLOW);
	setfont(70,0,"�����п�");
	outtextxy(730,10,"˵��");
	setcolor(GREEN);
	setfont(25,0,"����");
    outtextxy(715,80,"���ϰ� W���");
    outtextxy(715,105,"���°� S���");
    outtextxy(715,130,"���� A���");
    outtextxy(715,155,"���Ұ� D���");
    outtextxy(715,180,"��ͣ�� �ո�� ");
	setcolor(LIGHTCYAN);
	setfont(50,0,"��������");
	outtextxy(710,220,"�÷֣�");
	setcolor(LIGHTCYAN);
	setfont(50,0,"�����п�");
	outtextxy(835,220,"0");
	setcolor(LIGHTGREEN);
	setfont(50,0,"�����п�");
	outtextxy(710,280,"�ش�:");
	setcolor(BROWN);
	setfont(50,0,"�����п�");
	if(cp==1)
	    outtextxy(840,280,"1");
	if(cp==2)
	    outtextxy(840,280,"2");
	if(cp==3)
		outtextxy(840,280,"3");
	setcolor(RED);
	setfont(40,0,"�����п�");
	outtextxy(705,350,"��Ϸ������");
	setcolor(RED);
	setfont(40,0,"�����п�");
	outtextxy(725,400,"��1406");
    setcolor(LIGHTGREEN);
	setfont(60,0,"�����п�");
	outtextxy(710,470,"������");
	int i,m,n;
	for(i=1,m=0,n=0;i<=35;i++)
	{
		setfillcolor(BROWN);
		setcolor(RED);
		bar(m,n,m+20,n+20);
        m+=20;
	}
    for(i=1,m=0,n=580;i<=35;i++)
	{
		setfillcolor(BROWN);
		setcolor(RED);
		bar(m,n,m+20,n+20);
        m+=20;
	}
	for(i=1,m=0,n=0;i<=30;i++)
	{
		setfillcolor(BROWN);
		setcolor(RED);
		bar(m,n,m+20,n+20);
        n+=20;
	}
	for(i=1,m=680,n=0;i<=40;i++)
	{
		setfillcolor(BROWN);
		setcolor(RED);
		bar(m,n,m+20,n+20);
        n+=20;
	}
	if(cp==2)
	{
	setcolor(BROWN);
	setfillcolor(BROWN);
	bar(200,160,200+20,160+240);
	bar(420,280,420+20,280+160);
	}
	if(cp==3)
	{
	setcolor(BROWN);
	setfillcolor(BROWN);
	bar(200,160,200+20,160+240);
	bar(420,280,420+20,280+160);
    bar(300,200,300+300,200+20);
	}
}

void print_score()
{ 
   setcolor(BLACK);
   setfillcolor(BLACK);
   bar(830,220,830+150,220+50);
   char str[10];
   setcolor(LIGHTCYAN);
   setfont(50,0,"�����п�");
   sprintf(str,"%d",score);
   outtextxy(835,220,str); 
}

void set_food()
{
	food.cor.x=rand()%(700/20-2)*20+20;
    food.cor.y=rand()%(600/20-2)*20+20;
	if(cp==2&&(food.cor.x==200&&(food.cor.y>=160&&food.cor.y<=380)||
		food.cor.x==420&&(food.cor.y>=280&&food.cor.y<=420)))
		food.cor.x+=20;
	if(cp==3&&(food.cor.x==200&&(food.cor.y>=160&&food.cor.y<=380)||
		food.cor.x==420&&(food.cor.y>=280&&food.cor.y<=420)||
		food.cor.y==200&&(food.cor.x>=300&&food.cor.x<=580)))
		food.cor.x+=20;
         
}

void show_food()
{
	setcolor(YELLOW);
	setfillcolor(YELLOW);
	bar(food.cor.x,food.cor.y,food.cor.x+20,food.cor.y+20);
}

void set_mine()
{
	mine.cor.x=rand()%(700/20-2)*20+20;
    mine.cor.y=rand()%(600/20-2)*20+20;
	if(cp==2&&(mine.cor.x==200&&(mine.cor.y>=1600&&mine.cor.y<=380)||
		mine.cor.x==420&&(mine.cor.y>=280&&mine.cor.y<=420)))
		mine.cor.x+=20;
	if(cp==3&&(mine.cor.x==200&&(mine.cor.y>=160&&mine.cor.y<=380)||
		mine.cor.x==420&&(mine.cor.y>=280&&mine.cor.y<=420)||
		mine.cor.y==200&&(mine.cor.x>=300&&mine.cor.x<=580)))
		mine.cor.x+=20;
}
void show_mine()
{
    setfillcolor(LIGHTMAGENTA);
	setcolor(LIGHTMAGENTA);
    fillcircle(mine.cor.x+20/2,mine.cor.y+20/2,20/2);
}

void set_poigrass()
{
	setfillcolor(GREEN);
	fillcircle(poigrass.cor[0].x+20/2,poigrass.cor[0].y+20/2,20/2);
	fillcircle(poigrass.cor[1].x+20/2,poigrass.cor[1].y+20/2,20/2);
	fillcircle(poigrass.cor[2].x+20/2,poigrass.cor[2].y+20/2,20/2);
	if(cp==1)
		Sleep(60);
	if(cp==2)
	{
	fillcircle(poigrass.cor[3].x+20/2,poigrass.cor[3].y+20/2,20/2);
	fillcircle(poigrass.cor[4].x+20/2,poigrass.cor[4].y+20/2,20/2);
	Sleep(40);
	}
	if(cp==3)
	{
	fillcircle(poigrass.cor[3].x+20/2,poigrass.cor[3].y+20/2,20/2);
	fillcircle(poigrass.cor[4].x+20/2,poigrass.cor[4].y+20/2,20/2);
	fillcircle(poigrass.cor[5].x+20/2,poigrass.cor[5].y+20/2,20/2);
	fillcircle(poigrass.cor[6].x+20/2,poigrass.cor[6].y+20/2,20/2);
	Sleep(40);
	}
}

void set_poigrass1()
{
	setfillcolor(WHITE);
	fillcircle(poigrass.cor[0].x+20/2,poigrass.cor[0].y+20/2,20/2);
	fillcircle(poigrass.cor[1].x+20/2,poigrass.cor[1].y+20/2,20/2);
	fillcircle(poigrass.cor[2].x+20/2,poigrass.cor[2].y+20/2,20/2);
	if(cp==2)
	{
	fillcircle(poigrass.cor[3].x+20/2,poigrass.cor[3].y+20/2,20/2);
	fillcircle(poigrass.cor[4].x+20/2,poigrass.cor[4].y+20/2,20/2);
	}
	if(cp==3)
	{
	fillcircle(poigrass.cor[3].x+20/2,poigrass.cor[3].y+20/2,20/2);
	fillcircle(poigrass.cor[4].x+20/2,poigrass.cor[4].y+20/2,20/2);
	fillcircle(poigrass.cor[5].x+20/2,poigrass.cor[5].y+20/2,20/2);
	fillcircle(poigrass.cor[6].x+20/2,poigrass.cor[6].y+20/2,20/2);
	}
}
void no_poigrass()
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(poigrass.cor[0].x+20/2,poigrass.cor[0].y+20/2,20/2);
	fillcircle(poigrass.cor[1].x+20/2,poigrass.cor[1].y+20/2,20/2);
	fillcircle(poigrass.cor[2].x+20/2,poigrass.cor[2].y+20/2,20/2);
	if(cp==2)
	{
	setcolor(BLACK);
	setfillcolor(BLACK);
    fillcircle(poigrass.cor[3].x+20/2,poigrass.cor[3].y+20/2,20/2);
	fillcircle(poigrass.cor[4].x+20/2,poigrass.cor[4].y+20/2,20/2);
	}
	if(cp==3)
	{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(poigrass.cor[3].x+20/2,poigrass.cor[3].y+20/2,20/2);
	fillcircle(poigrass.cor[4].x+20/2,poigrass.cor[4].y+20/2,20/2);
	fillcircle(poigrass.cor[5].x+20/2,poigrass.cor[5].y+20/2,20/2);
	fillcircle(poigrass.cor[6].x+20/2,poigrass.cor[6].y+20/2,20/2);
	}
	poigrass.cor[0].x=240;
	poigrass.cor[0].y=700;
	poigrass.cor[1].x=340;
	poigrass.cor[1].y=700;
	poigrass.cor[2].x=240;
    poigrass.cor[2].y=700;
	if(cp==2)
	{
	poigrass.cor[3].x=60;
	poigrass.cor[3].y=700;
	poigrass.cor[4].x=500;
	poigrass.cor[4].y=700;
	}
	if(cp==3)
	{
    poigrass.cor[3].x=60;
	poigrass.cor[3].y=700;
	poigrass.cor[4].x=500;
	poigrass.cor[4].y=700;
	poigrass.cor[5].x=600;
	poigrass.cor[5].y=700;
	poigrass.cor[6].x=520;
	poigrass.cor[6].y=700;
	}
}

void snake_move()       
{
	node=1;
	setfillcolor(BLACK);
	setcolor(BLACK);
	bar(p0->x,p0->y,p0->x+20,p0->y+20);
    while(p0->previous!=NULL)
			{
				p0->x=p0->previous->x;
				p0->y=p0->previous->y;
				p0=p0->previous;
				node++;
			}
	switch(direct)
			{
			     case 1:head->y-=20;break;
				 case 2:head->y+=20;break;
				 case 3:head->x-=20;break;
				 case 4:head->x+=20;break;
			}
} 

void show_snake()
{
	setfillcolor(YELLOW);
    setcolor(YELLOW);
	p0=head;
	while(p0->next!=NULL)
	{
		bar(p0->x,p0->y,p0->x+20,p0->y+20);
		bar(p0->next->x,p0->next->y,p0->next->x+20,p0->next->y+20);
		p0=p0->next;
	}
	setfillcolor(BLACK);
	setcolor(BLACK);
	bar(head->x,head->y,head->x+20,head->y+20);
    setfillcolor(YELLOW);
	setcolor(YELLOW);
	fillcircle(head->x+20/2,head->y+20/2,20/2);
	if(cp==3)
      Sleep(0);
	else Sleep(30);
}

void change()              
{
	char key;
	key=getch();
	switch(key)
	{
		case 'w':
		case 'W':
		case  72:
			if(direct!=2)
				direct=1;
			break;
		case 's':
		case 'S':
		case 80:
			if(direct!=1)
			    direct=2;
			break;
		case 'a':
		case 'A':
		case 75:
			if (direct!=4)
				direct=3;
			break;
		case 'd':
		case 'D':
		case 77:
			if (direct!=3)
				direct=4;
			break;
		case ' ':                       
	        getch();
	}
}

void ju_eat_food()
{
	if(head->x==food.cor.x&&head->y==food.cor.y)
	{
		food.flag=1;
		pt=(struct Snake*)malloc(LEN);
		pt->x=head->x;
		pt->y=head->y;
		pt->previous=NULL;
	    pt->next=head;
        head->previous=pt;
	    head=pt;
		score=score+5;
		print_score();
	}
	else
		food.flag=0;
}

void ju_meet_mine()
{
	if(head->x==mine.cor.x&&head->y==mine.cor.y)
	{
		mine.flag=1;
		int i;
		if(node==1)
			gameover();
		mid=node/2;
        for(i=1;i<=mid;i++)
		{
		   setcolor(BLACK);
		   setfillcolor(BLACK);
		   bar(tail->x,tail->y,tail->x+20,tail->y+20);
	       tail=tail->previous;
		}
        tail->next=NULL;
		score=score-mid*5;
		print_score();
	}
	else
		mine.flag=0;
}
void ju_eat_poigrass()
{
	if(head->x==poigrass.cor[0].x&&head->y==poigrass.cor[0].y)
	{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[0].y=700;
        score=score-5;
		print_score();
	}
	if(head->x==poigrass.cor[1].x&&head->y==poigrass.cor[1].y)
	{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[1].y=700;
		score=score-5;
		print_score();
	}
	if(head->x==poigrass.cor[2].x&&head->y==poigrass.cor[2].y)
	{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[2].y=700;
		score=score-5;
		print_score();
	}
	if(cp==2)
	{
		if(head->x==poigrass.cor[3].x&&head->y==poigrass.cor[3].y)
		{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[3].y=700;
		score=score-5;
		print_score();
		}
		if(head->x==poigrass.cor[4].x&&head->y==poigrass.cor[4].y)
		{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[4].y=700;
		score=score-5;
		print_score();
		}
	}
	if(cp==3)
	{
		if(head->x==poigrass.cor[3].x&&head->y==poigrass.cor[3].y)
		{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[3].y=700;
		score=score-5;
		print_score();
		}
		if(head->x==poigrass.cor[4].x&&head->y==poigrass.cor[4].y)
		{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[4].y=700;
		score=score-5;
		print_score();
		}
		if(head->x==poigrass.cor[5].x&&head->y==poigrass.cor[5].y)
		{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[5].y=700;
		score=score-5;
		print_score();
		}
		if(head->x==poigrass.cor[6].x&&head->y==poigrass.cor[6].y)
		{
		if(node==1)
			gameover();
		setcolor(BLACK);
	    setfillcolor(BLACK);
		bar(tail->x,tail->y,tail->x+20,tail->y+20);
		tail=tail->previous;
        tail->next=NULL;
		poigrass.cor[6].y=700;
		score=score-5;
		print_score();
		}
	}
}

void gameover()
{
	if(cp==1)
	   endscore=score;
	if(cp==2)
		endscore=score+40;
	if(cp==3)
		endscore=score+70;
	Sleep(100);
	initgraph(700,600);
	setbkcolor(BLUE);
	cleardevice();
	setcolor(RED);
	setfont(100,0,"�����п�");
	outtextxy(160,80,"��Ϸ����");
	setcolor(YELLOW);
	setfont(70,0,"�����п�");
	outtextxy(160,210,"���÷�:");
	char str[10];
	setcolor(YELLOW);
	setfont(70,0,"�����п�");
    sprintf(str,"%d",score);
    outtextxy(460,210,str);
	setcolor(CYAN);
	setfont(60,0,"����");
	outtextxy(20,320,"������½Ƿ��ص���ҳ��");
	setcolor(LIGHTGREEN);
	setfont(60,0,"��������");
	outtextxy(440,500,"����ҳ��");
    set_rank();
	MOUSEMSG m; 
	while(true)
	{
	  m=GetMouseMsg();
	  switch(m.uMsg)
	  {
	  case WM_LBUTTONDOWN:
	   if(m.x>=440&&m.y>=500&&m.y<=560&&m.x<=680)
		   main();
	  }
	}
}
void design_cp1()
{
	cp=1;
	srand((unsigned)time(NULL));
	food.flag=1;
	mine.flag=1;
	direct=4;
	score=0;
	poigrass.cor[0].x=240;
	poigrass.cor[0].y=40;
	poigrass.cor[1].x=340;
	poigrass.cor[1].y=180;
	poigrass.cor[2].x=240;
    poigrass.cor[2].y=500;
    p0=(struct Snake*)malloc(LEN);
	head=(struct Snake*)malloc(LEN);
	tail=(struct Snake*)malloc(LEN);
	p1=(struct Snake*)malloc(LEN);
	head->x=2*20;
	head->y=5*20;
	tail->x=20;
	tail->y=5*20;
	p0=tail;
	map();
	IMAGE img;
	tail->x=head->x-20;
	tail->y=head->y;
	head->next=tail;
	head->previous=NULL;
	tail->next=NULL;
	tail->previous=head;
	tim1=(unsigned)time(NULL);
    while(1)
	{
		while(!kbhit())
		{
		  set_poigrass();
		  set_poigrass1();
		  if(food.flag==1)
              set_food();
		  if(mine.flag==1)
	          set_mine();
		  show_food();
	      show_mine();
          snake_move();
		  if(node==10)
		  {
			  initgraph(500,400);
			  setbkcolor(GREEN);
              cleardevice();
			  setcolor(RED);
			  setfont(40,0,"�����п�");
			  outtextxy(70,160,"��ϲ�㣬������һ�أ�");
			  Sleep(3000);
			  design_cp2();
		  }
		  ju_eat_food();
		  ju_meet_mine();
		  ju_eat_poigrass();
          while(p0->next!=NULL)
		  {
	         if((p0->next->x==head->x)&&(p0->next->y==head->y))
		        life=0;      
	    	p0=p0->next; 
		  }
		  if(life==0)
			  gameover();
          if(head->x>=680)
		  {  
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x-20,tail->y,tail->x,tail->y+20);
		      gameover();
		  }
		  if(head->x<20)
		  {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x+20,tail->y,tail->x+40,tail->y+20);
		      gameover();
          }
		  if(head->y>=580)
		  {  
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y-20,tail->x+20,tail->y);
		      gameover();
		  }
		  if(head->y<20)
		  {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y+20,tail->x+20,tail->y+40);
		      gameover();
		  }
		  show_snake();
		  tim2=(unsigned)time(NULL);
		  if(tim2-tim1>=30)
			  no_poigrass();
		}
		change();
	}
}

void design_cp2()
{
	cp=2;
	srand((unsigned)time(NULL));
	food.flag=1;
	mine.flag=1;
	direct=4;
	score=0;
	poigrass.cor[0].x=240;
	poigrass.cor[0].y=40;
	poigrass.cor[1].x=340;
	poigrass.cor[1].y=180;
	poigrass.cor[2].x=240;
    poigrass.cor[2].y=500;
	poigrass.cor[3].x=60;
	poigrass.cor[3].y=240;
	poigrass.cor[4].x=500;
	poigrass.cor[4].y=300;
    p0=(struct Snake*)malloc(LEN);
	head=(struct Snake*)malloc(LEN);
	tail=(struct Snake*)malloc(LEN);
	p1=(struct Snake*)malloc(LEN);
	head->x=2*20;
	head->y=5*20;
	tail->x=20;
	tail->y=5*20;
	p0=tail;
	map();
	tail->x=head->x-20;
	tail->y=head->y;
	head->next=tail;
	head->previous=NULL;
	tail->next=NULL;
	tail->previous=head;
	tim1=(unsigned)time(NULL);
    while(1)
	{
		while(!kbhit())
		{
		  set_poigrass();
		  set_poigrass1();
		  if(food.flag==1)
              set_food();
		  if(mine.flag==1)
	          set_mine();
		  show_food();
	      show_mine();
          snake_move();
		  ju_eat_food();
		  if(node==16)
		  {
			  initgraph(500,400);
			  setbkcolor(GREEN);
              cleardevice();
			  setcolor(RED);
			  setfont(40,0,"�����п�");
			  outtextxy(70,160,"��ϲ�㣬������һ�أ�");
			  Sleep(3000);
			  design_cp3();
		  }
		  ju_meet_mine();
		  ju_eat_poigrass();
          while(p0->next!=NULL)
		  {
	         if((p0->next->x==head->x)&&(p0->next->y==head->y))
		        life=0;
	    	p0=p0->next; 
		  }
		  if(life==0)
			  gameover();
          if(head->x>=680)
		  {  
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x-20,tail->y,tail->x,tail->y+20);
		      gameover();
		  }
		  if(head->x<20)
		  {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x+20,tail->y,tail->x+40,tail->y+20);
		      gameover();
          }
		  if(head->y>=580)
		  {  
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y-20,tail->x+20,tail->y);
		      gameover();
		  }
		  if(head->y<20)
		  {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y+20,tail->x+20,tail->y+40);
		      gameover();
		  }
		  if(direct==4)
		     if(head->x==200&&(head->y>=160&&head->y<=380)||head->x==420&&(head->y>=280&&head->y<=420))
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x-20,tail->y,tail->x,tail->y+20);
		      gameover();
			 }
		  if(direct==3)
		     if(head->x==200&&(head->y>=160&&head->y<=380)||head->x==420&&(head->y>=280&&head->y<=420))
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x+20,tail->y,tail->x+40,tail->y+20);
		      gameover();
			 }
		  if(direct==1)
		     if(head->x==200&&head->y==380||head->x==420&&head->y==420)
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y+20,tail->x+20,tail->y+40);
		      gameover();
			 }
			 if(direct==2)
		     if(head->x==200&&head->y==160||head->x==420&&head->y==280)
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y-20,tail->x+20,tail->y);
		      gameover();
			 }
		  show_snake();
		  tim2=(unsigned)time(NULL);
		  if(tim2-tim1>=50)
			  no_poigrass();
		}
		change();
	}
}

void design_cp3()
{
	cp=3;
	srand((unsigned)time(NULL));
	food.flag=1;
	mine.flag=1;
	direct=4;
	poigrass.cor[0].x=240;
	poigrass.cor[0].y=40;
	poigrass.cor[1].x=340;
	poigrass.cor[1].y=180;
	poigrass.cor[2].x=240;
    poigrass.cor[2].y=500;
	poigrass.cor[3].x=60;
	poigrass.cor[3].y=240;
	poigrass.cor[4].x=500;
	poigrass.cor[4].y=300;
	poigrass.cor[5].x=600;
	poigrass.cor[5].y=120;
	poigrass.cor[6].x=520;
	poigrass.cor[6].y=540;
    p0=(struct Snake*)malloc(LEN);
	head=(struct Snake*)malloc(LEN);
	tail=(struct Snake*)malloc(LEN);
	p1=(struct Snake*)malloc(LEN);
	head->x=2*20;
	head->y=5*20;
	tail->x=20;
	tail->y=5*20;
	p0=tail;
	map();
	tail->x=head->x-20;
	tail->y=head->y;
	head->next=tail;
	head->previous=NULL;
	tail->next=NULL;
	tail->previous=head;
	tim1=(unsigned)time(NULL);
    while(1)
	{
		while(!kbhit())
		{
		  set_poigrass();
		  set_poigrass1();
		  if(food.flag==1)
              set_food();
		  if(mine.flag==1)
	          set_mine();
		  show_food();
	      show_mine();
          snake_move();
		  ju_eat_food();
		  ju_meet_mine();
		  ju_eat_poigrass();
          while(p0->next!=NULL)
		  {
	         if((p0->next->x==head->x)&&(p0->next->y==head->y))
		        life=0;
	    	p0=p0->next; 
		  }
		  if(life==0)
			  gameover();
          if(head->x>=680)
		  {  
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x-20,tail->y,tail->x,tail->y+20);
		      gameover();
		  }
		  if(head->x<20)
		  {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x+20,tail->y,tail->x+40,tail->y+20);
		      gameover();
          }
		  if(head->y>=580)
		  {  
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y-20,tail->x+20,tail->y);
		       gameover();
		  }
		  if(head->y<20)
		  {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y+20,tail->x+20,tail->y+40);
		      gameover();
		  }
		  if(direct==4)
		     if(head->x==200&&(head->y>=160&&head->y<=380)||head->x==420&&(head->y>=280&&head->y<=420)||
				 head->y==200&&head->x==300)
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x-20,tail->y,tail->x,tail->y+20);
		      gameover();
			 }
		  if(direct==3)
		     if(head->x==200&&(head->y>=160&&head->y<=380)||head->x==420&&(head->y>=280&&head->y<=420)||
				 head->y==200&&head->x==580)
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x+20,tail->y,tail->x+40,tail->y+20);
		      gameover();
			 }
		  if(direct==1)
		     if(head->x==200&&head->y==380||head->x==420&&head->y==420||
				 head->y==200&&(head->x>=300&&head->x<=580))
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y+20,tail->x+20,tail->y+40);
		      gameover();
			 }
			 if(direct==2)
		     if(head->x==200&&head->y==160||head->x==420&&head->y==280||
				 head->y==200&&(head->x>=300&&head->x<=580))
			 {
              setfillcolor(YELLOW);
	          setcolor(YELLOW);
	          bar(tail->x,tail->y-20,tail->x+20,tail->y);
		      gameover();
			  tim2=(unsigned)time(NULL);
		      if(tim2-tim1>=80)
			      no_poigrass();
			 }
		  show_snake();
		}
		change();
	}
}
