#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <io.h>

int *arctg5, *arctg239, *tmp;
int DecLen, BinLen;
int x, n, sign, NonZeroPtr;
int Step;
char fn_status[] = "~pi_sts.___";
char fn_arctg5[] = "~atg5.___";
char fn_arctg239[] = "~atg239.___";
char fn_tmp[] = "~tmp.___";
time_t TotalTime, time1, time2;

void __cdecl FirstDiv(int *arctg_array)
{
    __asm {
        mov esi, arctg_array
        mov dword ptr [esi], 1
        xor edx, edx
        mov ebx, x
        mov ecx, BinLen
fd1:    mov eax, [esi]
        div ebx
        mov [esi], eax
        add esi, 4
        loop fd1
        mov esi, arctg_array
        mov edi, tmp
        mov ecx, BinLen
        pushf
        cld
        rep movsd
        popf
    }
}

void __cdecl arctgx(int *arctg_array)
{
    int NonZeroBytePtr;
    int key;
    FILE *fp;

    for (; NonZeroPtr < BinLen;)
    {
        NonZeroBytePtr = NonZeroPtr * 4;

        if (_kbhit())
        {
            key = _getch();
            if (key == 0 || key == 0xe0)
                _getch();
            if (key == 'p')
            {
                printf("Swap data to disk ...\n");
                if (x == 25)
                    Step = 1;
                else
                    Step = 2;
                time(&time2);
                TotalTime += time2 - time1;
                if ((fp = fopen(fn_status, "wt")) == NULL)
                {
                    printf("Create file %s error!!\n", fn_status);
                    exit(0);
                }
                fprintf(fp, "%d %d %d %d %d %d %d\n",
                        Step, DecLen, BinLen, n, sign, NonZeroPtr, TotalTime);
                fclose(fp);
                if ((fp = fopen(fn_arctg5, "wb")) == NULL)
                {
                    printf("Create file %s error!!\n", fn_arctg5);
                    exit(0);
                }
                if (fwrite(arctg5, 4, BinLen, fp) != (unsigned)BinLen)
                {
                    printf("Write file %s error!!\n", fn_arctg5);
                    exit(0);
                }
                fclose(fp);
                if ((fp = fopen(fn_arctg239, "wb")) == NULL)
                {
                    printf("Create file %s error!!\n", fn_arctg239);
                    exit(0);
                }
                if (fwrite(arctg239, 4, BinLen, fp) != (unsigned)BinLen)
                {
                    printf("Write file %s error!!\n", fn_arctg239);
                    exit(0);
                }
                fclose(fp);
                if ((fp = fopen(fn_tmp, "wb")) == NULL)
                {
                    printf("Create file %s error!!\n", fn_tmp);
                    exit(0);
                }
                if (fwrite(tmp, 4, BinLen, fp) != (unsigned)BinLen)
                {
                    printf("Write file %s error!!\n", fn_tmp);
                    exit(0);
                }
                fclose(fp);
                printf("Exit.\n");
                exit(0);
            }
        }

        __asm {
            mov esi, tmp
            add esi, NonZeroBytePtr
            xor edx, edx
            mov ebx, x
            mov ecx, BinLen
            sub ecx, NonZeroPtr
arctg1:     mov eax, [esi]
            div ebx
            mov [esi], eax
            add esi, 4
            loop arctg1

            cmp sign, 1
            jne sub_

            mov esi, tmp
            add esi, NonZeroBytePtr
            mov edi, arctg_array
            add edi, NonZeroBytePtr
            xor edx, edx
            mov ebx, n
            mov ecx, BinLen
            sub ecx, NonZeroPtr
add_1:      mov eax, [esi]
            div ebx
            add [edi], eax
            adc dword ptr [edi-4], 0
            jnc add_3
            push edi
            sub edi, 4
add_2:      sub edi, 4
            add dword ptr [edi], 1
            jc add_2
            pop edi
add_3:      add esi, 4
            add edi, 4
            loop add_1
            jmp adj_var

sub_:       mov esi, tmp
            add esi, NonZeroBytePtr
            mov edi, arctg_array
            add edi, NonZeroBytePtr
            xor edx, edx
            mov ebx, n
            mov ecx, BinLen
            sub ecx, NonZeroPtr
sub_1:      mov eax, [esi]
            div ebx
            sub [edi], eax
            sbb dword ptr [edi-4], 0
            jnc sub_3
            push edi
            sub edi, 4
sub_2:      sub edi, 4
            sub dword ptr [edi], 1
            jc sub_2
            pop edi
sub_3:      add esi, 4
            add edi, 4
            loop sub_1

adj_var:    add n, 2
            neg sign
            mov esi, tmp
            add esi, NonZeroBytePtr
            cmp dword ptr [esi], 0
            jne adj_var_ok
            inc NonZeroPtr
adj_var_ok:
        }
    }
}

void __cdecl mul_array(int *array, int multiplicator)
{
    __asm {
        mov esi, BinLen
        dec esi
        shl esi, 2
        add esi, array
        mov ecx, BinLen
        mov ebx, multiplicator
        xor edi, edi
mul1:   mov eax, [esi]
        mul ebx
        add eax, edi
        adc edx, 0
        mov [esi], eax
        mov edi, edx
        sub esi, 4
        loop mul1
        mov [esi], edx
    }
}

void __cdecl sub2array(int *array1, int *array2)
{
    __asm {
        mov esi, array1
        mov edi, array2
        mov ecx, BinLen
        dec ecx
sub1:   mov eax, [edi+ecx*4]
        sbb [esi+ecx*4], eax
        loop sub1
    }
}

void main(void)
{
    struct tm *ts;
    FILE *pi, *fp;
    int i, tail, p10tail;

    printf("\nProgram to compute PI, by Jason Chen, May 1999.\n");
    printf("        Dec Length               Time(h:m:s)\n");
    printf("            20000                 00:00:07\n");
    printf("           100000                 00:02:54\n");
    printf(" (Running on PII-233, 128MB, Win98 Dos mode)\n");
    printf("        Homepage: http://www.jason314.com\n");
    printf("           Email: jason@szonline.net\n\n");

    if ((fp = fopen(fn_status, "rt")) == NULL)
    {
        printf("Decimal length位数 = ");
        scanf("%d", &DecLen);
        if (DecLen < 100)
            DecLen = 100;
        BinLen = (int)(DecLen / log10(2) / 32) + 2;
        Step = 0;
        TotalTime = 0;
    }
    else
    {
        printf("Reading previous data ...\n");
        fscanf(fp, "%d %d %d %d %d %d %d",
               &Step, &DecLen, &BinLen, &n, &sign, &NonZeroPtr, &TotalTime);
        fclose(fp);
        if (Step * DecLen * BinLen * n * sign * NonZeroPtr * TotalTime == 0)
        {
            printf("File %s error !!\nExit!\n", fn_status);
            exit(0);
        }
    }

    arctg5 = (int *)calloc(BinLen, 4);
    arctg239 = (int *)calloc(BinLen, 4);
    tmp = (int *)calloc(BinLen, 4);
    if (arctg5 == NULL || arctg239 == NULL || tmp == NULL)
    {
        printf("Not enough memory !!\n");
        exit(0);
    }

    if (Step == 0)
    {
        memset(arctg5, 0, BinLen * 4);
        memset(arctg239, 0, BinLen * 4);
        memset(tmp, 0, BinLen * 4);
    }
    else
    {
        if ((fp = fopen(fn_arctg5, "rb")) == NULL)
        {
            printf("Open file %s error!!\n", fn_arctg5);
            exit(0);
        }
        if (fread(arctg5, 4, BinLen, fp) != (unsigned)BinLen)
        {
            printf("File %s error!!\n", fn_arctg5);
            exit(0);
        }
        fclose(fp);
        if ((fp = fopen(fn_arctg239, "rb")) == NULL)
        {
            printf("Open file %s error!!\n", fn_arctg239);
            exit(0);
        }
        if (fread(arctg239, 4, BinLen, fp) != (unsigned)BinLen)
        {
            printf("File %s error!!\n", fn_arctg239);
            exit(0);
        }
        fclose(fp);
        if ((fp = fopen(fn_tmp, "rb")) == NULL)
        {
            printf("Open file %s error!!\n", fn_tmp);
            exit(0);
        }
        if (fread(tmp, 4, BinLen, fp) != (unsigned)BinLen)
        {
            printf("File %s error!!\n", fn_tmp);
            exit(0);
        }
        fclose(fp);
    }

    printf("Working ......\n");
    printf("稍候......");
    time(&time1);

    if (Step == 0)
    {
        x = 5;
        FirstDiv(arctg5);
        x = x * x;
        n = 3;
        sign = -1;
        NonZeroPtr = 1;
        arctgx(arctg5);
    }
    else if (Step == 1)
    {
        x = 5 * 5;
        arctgx(arctg5);
    }

    if (Step == 0 || Step == 1)
    {
        x = 239;
        FirstDiv(arctg239);
        x = x * x;
        n = 3;
        sign = -1;
        NonZeroPtr = 1;
        arctgx(arctg239);
    }
    else
    {
        x = 239 * 239;
        arctgx(arctg239);
    }

    mul_array(arctg5, 16);
    mul_array(arctg239, 4);
    sub2array(arctg5, arctg239);

    if ((pi = fopen("pi.txt", "wt")) == NULL)
    {
        printf("Create file pi.txt error!!\n");
        exit(0);
    }

    printf("正在将结果写入文本文件: pi.txt ...\n");
    fprintf(pi, "%d", arctg5[0]);
    for (i = 1; i <= DecLen / 9; i++)
    {
        arctg5[0] = 0;
        mul_array(arctg5, 1000000000);
        fprintf(pi, "%09d", arctg5[0]);
    }
    tail = DecLen % 9;
    p10tail = 1;
    for (i = 1; i <= tail; i++)
        p10tail *= 10;
    arctg5[0] = 0;
    mul_array(arctg5, p10tail);
    fprintf(pi, "%0*d", tail, arctg5[0]);
    fclose(pi);

    time(&time2);
    TotalTime += time2 - time1;
    printf("已经完成了 !!\n");
    ts = gmtime(&TotalTime);
    ts->tm_mon--;
    ts->tm_mday = ts->tm_mday - 1 + ts->tm_mon * 31;
    printf("耗时 : ");
    if (ts->tm_mday > 0)
        printf("%d Day(s) ", ts->tm_mday);
    printf("%02d:%02d:%02d\n", ts->tm_hour, ts->tm_min, ts->tm_sec);

    if (_unlink(fn_status) == 0)
    {
        _unlink(fn_arctg5);
        _unlink(fn_arctg239);
        _unlink(fn_tmp);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//此程序代码可复制粘贴到vc++6.0调试运行。该程序为Jason Chen于1999年编的。我用过国内流行的
//Turbo c 2.0来运行它。有些标识符，它不认识，无法编译。而在vc++6.0中则顺利通过。
//要读懂此程序，需一定的功力。但照搬是没有问题的。程序用的是马青Machin公式:
// π=16arctg （1/5） - 4arctg（ 1/239 ）。

//arctgx=x-(1/3)(x^3)+(1/5)x^5-(1/7)x^7+(1/9)x^9-.....    Gregory's series 级数。

//用它来 计算π值到10万位在耗时上是没有什么问题的。快得很！当然还有更先进的方法。如日本的金田教授的方法等等。不管快慢如何，问题是这么庞大的位数如何存放在电脑内存中？而且还要保持其准确度！用过此程序后再仔细研究其中的c语言和汇编语言吧。显然,把数值变量转换为字符数组变量,然后逐位计算。并且还用到文件读写管理的方法来记录结果。大致就是这个思路。
// ,美国某大学的一位教授就是这么提示给他的学生的 。这是个关键。
//程序的开头说明部分和程序中的中文是我修改的。我已经运行多次。估计使用它时不会有大问题。
//在VC++中运行调试C语言程序的方法，在此都作了详细的说明。运行时出现命令提示符，
//在等号后面键入你想要的圆周率的位数，回车。等候。完成后电脑自动形成一个文本文件：Pi.txt.存
//放在所编出的程序文件的同一文件夹中。打开它即可看到π值文本。计算π值至10万位所耗时间约为25秒
//（最近出/的电脑）。调试成功后就会产生一个可脱离开发环境而独立执行的自己命名的.exe程序。