/*演奏乐曲《小星星》《茉莉花》《找朋友》《上学歌》《一分钱》《征服》《沧海一声笑》《童话》《同桌的你》《小熊和洋娃娃》*/
#include <stdio.h>
#include <windows.h>
int main(void)
{
	int choice;
	void play_xiaoxingxing(void);
	void play_molihua(void);
	void play_zhaopengyou(void);
	void play_shangxuege(void);
	void play_yifenqian(void);
	void play_zhengfu(void);
	void play_canghaiyishengxiao(void);
	void play_tonghua(void);
	void play_tongzhuodeni(void);
	void play_xiaoxiongheyangwawa(void);
	while (1)
	{
		printf("请选择需要演奏的曲目：\n");
		printf("【1】《小星星》\n");
		printf("【2】《茉莉花》\n");
		printf("【3】《找朋友》\n");
		printf("【4】《上学歌》\n");
		printf("【5】《一分钱》\n");
		printf("【6】《征服》\n");
		printf("【7】《沧海一声笑》\n");
		printf("【8】《童话》\n");
		printf("【9】《同桌的你》\n");
		printf("【10】《小熊和洋娃娃》\n");
		printf("【0】退出程序\n");
		printf("\n");
		printf("请选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			play_xiaoxingxing();
			break;
		case 2:
			play_molihua();
			break;
		case 3:
			play_zhaopengyou();
			break;
		case 4:
			play_shangxuege();
			break;
		case 5:
			play_yifenqian();
			break;
		case 6:
			play_zhengfu();
			break;
		case 7:
			play_canghaiyishengxiao();
			break;
		case 8:
			play_tonghua();
			break;
		case 9:
			play_tongzhuodeni();
			break;
		case 10:
			play_xiaoxiongheyangwawa();
			break;
		case 0:
			break;
		default:
			printf("输入有误！请正确输入！\n");
		}
		Beep(0, 1000); //暂停一秒钟
		printf("\n");
		if (choice == 0)
		{
			printf("\n谢谢使用，再见！");
			Beep(0, 1000); //暂停一秒钟
			break;
		}
	}
	return 0;
}

/*返回数字简谱中数字t所对应的频率*/
int notation_frequency(int t)
{
	switch (t)
	{
		/*中音部分:1,2,3,4,5,6,7*/
	case 1:
		return 523;
	case 2:
		return 587;
	case 3:
		return 659;
	case 4:
		return 698;
	case 5:
		return 784;
	case 6:
		return 880;
	case 7:
		return 988;
		/*低音部分:-1,-2,-3,-4,-5,-6,-7*/
	case -1:
		return 262;
	case -2:
		return 294;
	case -3:
		return 330;
	case -4:
		return 349;
	case -5:
		return 392;
	case -6:
		return 440;
	case -7:
		return 494;
		/*高音部分:11,12,13,14,15,16,17*/
	case 11:
		return 1047;
	case 12:
		return 1175;
	case 13:
		return 1319;
	case 14:
		return 1397;
	case 15:
		return 1568;
	case 16:
		return 1760;
	case 17:
		return 1976;
		/*安静:0,不合法数值*/
	default:
		return 0;
	}
}

/*演奏《小星星》*/
void play_xiaoxingxing(void)
{
	int i;
	int _xiaoxingxing[48] = {
		1, 1, 5, 5, 6, 6, 5, 0,
		4, 4, 3, 3, 2, 2, 1, 0,
		5, 5, 4, 4, 3, 3, 2, 0,
		5, 5, 4, 4, 3, 3, 2, 0,
		1, 1, 5, 5, 6, 6, 5, 0,
		4, 4, 3, 3, 2, 2, 1, 0}; //小星星乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《小星星》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 47; i++)
	{
		if (_xiaoxingxing[i] == 0)
			printf("\n");
		else
			printf("%d", _xiaoxingxing[i]);
		Beep(notation_frequency(_xiaoxingxing[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}

/*演奏《茉莉花》*/
void play_molihua(void)
{
	int i, t;
	int _molihua[72] = {
		3, 3, 5, 6, 11, 11, 6, 5, 0,
		5, 6, 5, 0,
		3, 3, 5, 6, 11, 11, 6, 5, 0,
		5, 6, 5, 0,
		5, 5, 5, 3, 5, 6, 0,
		6, 6, 5, 0,
		3, 2, 3, 5, 0,
		3, 2, 1, 0,
		1, 2, 1, 0,
		3, 2, 1, 2, 0,
		3, 5, 6, 11, 6, 5, 0,
		5, 2, 3, 5, 3, 2, 1, 2, 1, 0}; //茉莉花乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《茉莉花》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 71; i++)
	{
		t = _molihua[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_molihua[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}

/*演奏《找朋友》*/
void play_zhaopengyou(void)
{
	int i, t;
	int _zhaopengyou[32] = {
		5, 6, 5, 6, 5, 6, 5, 0,
		5, 11, 7, 6, 5, 5, 3, 0,
		5, 5, 3, 3, 5, 5, 3, 0,
		2, 4, 3, 2, 1, 2, 1, 0}; //找朋友乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《找朋友》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 31; i++)
	{
		t = _zhaopengyou[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_zhaopengyou[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}

/*演奏《上学歌》*/
void play_shangxuege(void)
{
	int i, t;
	int _shangxuege[30] = {
		1, 2, 3, 1, 5, 0,
		6, 6, 11, 6, 5, 0,
		6, 6, 11, 0,
		5, 6, 3, 0,
		6, 5, 3, 5, 3, 1, 2, 3, 1, 0}; //找朋友乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《上学歌》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 29; i++)
	{
		t = _shangxuege[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_shangxuege[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}

/*演奏《一分钱》*/
void play_yifenqian(void)
{
	int i, t;
	int _yifenqian[52] = {
		5, 11, 6, 11, 5, 0,
		3, 5, 2, 3, 5, 0,
		3, 5, 6, 11, 5, 6, 5, 3, 5, 1, 0,
		3, 2, 0,
		3, 2, 1, 2, 3, 0,
		6, 5, 3, 5, 6, 0,
		5, 11, 11, 6, 5, 6, 3, 0,
		5, 2, 3, 2, 1, 0}; //找朋友乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《一分钱》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 51; i++)
	{
		t = _yifenqian[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_yifenqian[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}

/*演奏《征服》*/
void play_zhengfu(void)
{
	int i, t;
	int _zhengfu[33] = {
		5, 11, 7, 5, 5, 6, 5, 0,
		5, 11, 7, 5, 6, 3, 6, 0,
		6, 6, 6, 5, 3, 3, 4, 0,
		4, 4, 4, 5, 6, 3, 2, 2, 0}; //征服乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《征服》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 32; i++)
	{
		t = _zhengfu[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_zhengfu[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}

/*演奏《沧海一声笑》*/
void play_canghaiyishengxiao(void)
{
	int i, t;
	int _canghaiyishengxiao[31] = {
		12, 12, 1, 6, 5, 4, 0,
		6, 5, 4, 2, 1, 0,
		1, 2, 1, 2, 4, 4, 5, 6, 11, 0,
		12, 12, 11, 6, 5, 4, 5, 0}; //沧海一声笑乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《沧海一声笑》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 30; i++)
	{
		t = _canghaiyishengxiao[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_canghaiyishengxiao[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}
/*演奏《童话》*/
void play_tonghua(void)
{
	int i, t;
	int _tonghua[46] = {
		5, 4, 3, 0,
		3, 4, 3, 0,
		3, 4, 3, 4, 3, 2, 1, 0,
		1, 3, 5, 6, 0,
		6, 6, 5, 2, 2, 4, 3, 0,
		1, 3, 5, 6, 0,
		6, 6, 7, 6, 5, 4, 3, 4, 3, 2, 1, 0}; //童话乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《童话》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 45; i++)
	{
		t = _tonghua[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_tonghua[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}
/*演奏《同桌的你》*/
void play_tongzhuodeni(void)
{
	int i, t;
	int _tongzhuodeni[71] = {
		5, 5, 5, 5, 3, 4, 5, 7, 0,
		6, 6, 6, 6, 4, 6, 5, 0,
		5, 5, 5, 5, 7, 6, 5, 4, 0,
		4, 4, 4, 4, 3, 2, 1, 0,
		11, 11, 11, 11, 5, 6, 11, 11, 11, 11, 0,
		12, 12, 12, 12, 11, 7, 6, 0,
		7, 7, 7, 7, 7, 11, 12, 0,
		5, 0,
		7, 7, 11, 12, 11, 7, 11, 0}; //同桌的你乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《同桌的你》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 70; i++)
	{
		t = _tongzhuodeni[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_tongzhuodeni[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}
/*演奏《小熊和洋娃娃》*/
void play_xiaoxiongheyangwawa(void)
{
	int i, t;
	int _xiaoxiongheyangwawa[77] = {
		1, 0,
		2, 3, 4, 5, 5, 5, 4, 3, 4, 4, 4, 3, 2, 1, 3, 5, 1, 0,
		2, 3, 4, 5, 5, 5, 4, 3, 4, 4, 4, 3, 2, 1, 3, 1, 6, 0,
		6, 6, 5, 4, 5, 5, 5, 4, 3, 4, 4, 4, 3, 2, 1, 3, 5, 6, 0,
		6, 6, 5, 4, 5, 5, 5, 4, 3, 4, 0,
		4, 4, 3, 2, 1, 0,
		3, 1, 0}; //小熊和洋娃娃乐谱
	int notation_frequency(int t);
	printf("请欣赏乐曲《小熊和洋娃娃》……\n");
	Beep(0, 1000); //暂停一秒钟
	for (i = 0; i <= 76; i++)
	{
		t = _xiaoxiongheyangwawa[i];
		if (t < 0)
			t = -t;
		t = t % 10;
		if (t == 0)
			printf("\n");
		else
			printf("%d", t);
		Beep(notation_frequency(_xiaoxiongheyangwawa[i]), 1000);
	}
	printf("演奏完毕！谢谢欣赏！\n");
}