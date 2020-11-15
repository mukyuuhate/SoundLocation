/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.2
 * C/C++ source code generated on  : 01-Nov-2020 17:27:13
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */

#include "SoundLocation_terminate.h"
#include "main.h"
#include <time.h>

/* Function Declarations */
static double argInit_real_T(void)
{
    return 0.0;
}

/* Function Definitions */

/*
 * Arguments    : double result[3600000]
 * Return Type  : void
 */
static void argInit_10x360000_real_T(double result[3600000])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 10; idx0++) {
    for (idx1 = 0; idx1 < 360000; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 10 * idx1] = argInit_real_T();
    }
  }
}

/*
 * Arguments    : double result[15]
 * Return Type  : void
 */
static void argInit_5x3_real_T(double result[15])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 5; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 5] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 10] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */


double change(char str[]){
    double num=0.0;
    int len=strlen(str);
    int fushu=0;//负数标志
    char *p,*i;
    p=str;
    if(str[0]=='-'){//判断正负号
        fushu=1;
        p++;
    }
    int temp;//当前元素的数值
    while(p<=str+len){
        if(*p>='0'&&*p<='9'){
            temp=*p-'0';//数值本身
            num=num*10+temp;//整数部分处理
            p++;
            continue;//继续循环
        }
        if(*p=='.'){
            p++;
            int n=1;//记录当前为小数点后几位
            for(i=p;i<=str+len;i++){
                if(*p>='0'&&*p<='9'){
                    temp=*p-'0';
                    double pp = 1;
                    for(int i = 0; i < n; i++){
                        pp = pp * 2;
                    }
                    num=num+temp*pp;//小数部分处理
                    p++;
                    n++;
                }
                else break;//退出循环
            }
            if(fushu==0)return num;
            else return num*(-1.0);
        }
        else break;
    }
    if(fushu==0)return num;
    else return num*(-1);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static double* main_SoundLocation(void)
{
  emxArray_real_T *LocEst1;
  static double rxsignal[3600000];
  double fs_tmp;
  double t;
  double Mic_Loc_H_tmp[15];
  double Mic_Loc_L_tmp[15];
  emxInitArray_real_T(&LocEst1, 2);

  /* Initialize function 'SoundLocation' input arguments. */
  /* Initialize function input argument 'rxsignal'. */
    argInit_10x360000_real_T(rxsignal);
    FILE *fp = NULL;
    char *line,*record;
    char buffer[1024];
    int j = 0;
    if ((fp = fopen("D:\\cpp\\clion\\testSoundLocation\\data.txt", "r")) != NULL)
    {
        while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)//当没有读取到文件末尾时循环继续
        {
            record = strtok(line, " ");
            while (record != NULL)//读取每一行的数据
            {
//                rxsignal[(j % 10) * 360000 + j / 10] = change(record);
                rxsignal[j] = change(record);
                record = strtok(NULL, ",");
                j++;
            }
        }
        fclose(fp);
        fp = NULL;
    }


  fs_tmp = 88200.0;
  t = 0.1;

  /* Initialize function input argument 'Mic_Loc_H'. */
    /* Initialize function input argument 'Mic_Loc_L'. */
  for(int i = 0; i < 5; i++){
      Mic_Loc_H_tmp[i] = 50;
      Mic_Loc_H_tmp[i + 5] = 0;
      Mic_Loc_H_tmp[i + 10] = 10 + 0.2 * i;

      Mic_Loc_L_tmp[i + 10] = 50;
      Mic_Loc_L_tmp[i + 5] = 0;
      Mic_Loc_L_tmp[i] = 50 + 0.2 * i;
  }

  /* Call the entry-point 'SoundLocation'. */
  SoundLocation(rxsignal, fs_tmp, t, Mic_Loc_H_tmp, Mic_Loc_L_tmp, LocEst1);
  static double res[5] = {0};
  for(int i = 0; i < 5; i++){
      res[i] = LocEst1->data[i * 40 + 2];
  }
  emxDestroyArray_real_T(LocEst1);
    return res;
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
    clock_t start, finish;
    double Total_time;
    start = clock();
    (void)argc;
    (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
//  SoundLocation_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
    double* a = main_SoundLocation();
    printf("%f " , a[4]);
    finish = clock();
    Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("\ntime: %0.3fms \n", Total_time);
    /* Terminate the application.
       You do not need to do this more than one time. */
  SoundLocation_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
