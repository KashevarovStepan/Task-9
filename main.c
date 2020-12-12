#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <limits.h>
#include <float.h>

int multiplier(int x)
{
    if(x==1)return 1;
    int y=1,ok=0;
    while(!ok)
    {
        y++;
        if(x%y==0)ok=1;
    }
    return y;
}

void Task1()
{
    printf("Задание 1\n");
    int m,n,k,i,j;
    int **mas,*newmas;
    printf("Двумерный -> Одномерный\n");

    printf("Введите количество строк и столбцов через пробел\n");
    scanf("%d %d",&m,&n);
    mas=(int**)malloc(m*sizeof(int*));
    for(i=0;i<m;i++)mas[i]=(int*)malloc(n*sizeof(int));
    k=m*n;
    newmas=(int*)malloc(k*sizeof(int));

    printf("Начальный массив(%dx%d):\n",m,n);
    for(i=0;i<m;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            mas[i][j]=rand()%10;
            printf("%d ",mas[i][j]);
            newmas[i*n+j]=mas[i][j];
        }
    }
    printf("\nНовый массив(%d): ",k);
    for(i=0;i<k;i++)printf("%d ",newmas[i]);

    free(newmas);
    for(i=0;i<m;i++)free(mas[i]);
    free(mas);

    printf("\nОдномерный -> Двумерный\n");
    printf("Введите количество элементов массива\n");
    scanf("%d",&k);
    m=multiplier(k);
    n=k/m;
    newmas=(int*)malloc(k*sizeof(int));
    mas=(int**)malloc(m*sizeof(int*));
    for(i=0;i<m;i++)mas[i]=(int*)malloc(n*sizeof(int));

    printf("\nНачальный массив(%d): ",k);
    for(i=0;i<k;i++)
    {
        newmas[i]=rand()%10;
        printf("%d ",newmas[i]);
        mas[i/n][i%n]=newmas[i];
    }
    printf("\nНовый массив(%dx%d):\n",m,n);
    for(i=0;i<m;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",mas[i][j]);
        }
    }

    free(newmas);
    for(i=0;i<m;i++)free(mas[i]);
    free(mas);
}

void fillMas(int **mas,int m,int n,int pi,int pj,int i,int j)
{
    mas[i][j]=mas[pi][pj]+1;
    //if(i!=0&&j!=0&&i!=m-1&&j!=n-1&&(mas[i-1][j]!=0&&mas[i+1][j]!=0&&mas[i][j-1]!=0&&mas[i][j+1]!=0))return;
    if(((pj==j&&pi>i&&(i==0||mas[i-1][j]!=0)) || (pj<j&&j<n-1&&pi==i)) &&mas[i][j+1]==0) fillMas(mas,m,n,i,j,i,j+1);
    if(((pj==j&&pi<i&&(i==m-1||mas[i+1][j]!=0) || (pj>j&&pi==i&&j>0))) &&mas[i][j-1]==0) fillMas(mas,m,n,i,j,i,j-1);
    if(((pj==j&&pi<i&&i<m-1) || (pj<j&&pi==i&&(j==n-1||mas[i][j+1]!=0))) &&mas[i+1][j]==0) fillMas(mas,m,n,i,j,i+1,j);
    if(((pj==j&&pi>i&&i>0) || (pj>j&&pi==i&&(j==0||mas[i-1][j]!=0))) &&mas[i-1][j]==0) fillMas(mas,m,n,i,j,i-1,j);

    //if(pj<j&&(j<n-1||mas[i][j+1]!=0))fillMas(mas,m,n,i,j,i,j+1);
    //if(pj>j&&(j>0||mas[i][j-1]!=0))fillMas(mas,m,n,i,j,i,j-1);
    //if(pi<i&&(i<m-1||))
}

void Task2()
{
    printf("Задание 2\n");
    int m,n,k,i,j,count=1;
    int **mas;

    printf("Введите количество строк и столбцов через пробел\n");
    scanf("%d %d",&m,&n);
    mas=(int**)malloc(m*sizeof(int*));
    for(i=0;i<m;i++)mas[i]=(int*)malloc(n*sizeof(int));

    printf("Заполнение 1 массива(%dx%d)\n",m,n);
    for(i=0;i<m;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            mas[i][j]=abs(i-j)+1;
            printf("%d ",mas[i][j]);
            mas[i][j]=0;
        }
    }

    printf("\nЗаполнение 2 массива(%dx%d)\n",m,n);
    if(n>=m)
    {
        for(j=0;j<m/2;j++)
        {
            for(i=j;i<n-j;i++)mas[j][i]=count++;
            for(i=j+1;i<m-j;i++)mas[i][n-j-1]=count++;
            for(i=n-j-2;i>j-1;i--)mas[m-j-1][i]=count++;
            for(i=m-j-2;i>j;i--)mas[i][j]=count++;
        }
        if(m%2==1)for(i=m/2;i<n-m/2;i++)mas[m/2][i]=count++;
    }
    else
    {
        for(j=0;j<n/2;j++)
        {
            for(i=j;i<n-j;i++)mas[j][i]=count++;
            for(i=j+1;i<m-j;i++)mas[i][n-j-1]=count++;
            for(i=n-j-2;i>j-1;i--)mas[m-j-1][i]=count++;
            for(i=m-j-2;i>j;i--)mas[i][j]=count++;
        }
        if(n%2==1)for(i=n/2;i<m-n/2;i++)mas[i][n/2]=count++;
    }
    for(i=0;i<m;i++,printf("\n"))for(j=0;j<n;j++)printf("%d ",mas[i][j]);

    for(i=0;i<m;i++)free(mas[i]);
    free(mas);
}

void swap(double*a,double*b)
{
    double t=*a;
    *a=*b;
    *b=t;
}

double*Gauss5(double**mas,double*y,int n)
{
  double *x,max;
  int k,index,i,j;
  const double e=0.00001;
  x=(int*)malloc(n*sizeof(double));
  k=0;
  while(k<n)
  {
    max=fabs(mas[k][k]);
    index=k;
    for(i=k+1;i<n;i++)
    {
      if(fabs(mas[i][k])>max)
      {
        max=fabs(mas[i][k]);
        index=i;
      }
    }
    for(j=0;j<n;j++)swap(&mas[k][j],&mas[index][j]);
    swap(&y[k],&y[index]);

    for(i=k;i<n;i++)
    {
      double t=mas[i][k];
      if(fabs(t)<e)continue;
      for(j=0;j<n;j++)mas[i][j]=mas[i][j]/t;
      y[i]=y[i]/t;
      if(i==k)continue;
      for(j=0;j<n;j++)mas[i][j]=mas[i][j]-mas[k][j];
      y[i]=y[i]-y[k];
    }
    k++;
  }

  for(k=n-1;k>=0;k--)
  {
    x[k]=y[k];
    for(i=0;i<k;i++)y[i]=y[i]-mas[i][k]*x[k];
  }
  return x;
}

void Task5()
{
    printf("Задание 5\n");
    int n,i,j;
    double **mas,*y,*x;
    printf("Введите количество уравнений и неизвестных(n)\n");
    scanf("%d",&n);
    mas=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++)mas[i]=(int*)malloc(n*sizeof(double));
    y=(int*)malloc(n*sizeof(double));
    x=(int*)malloc(n*sizeof(double));

    printf("Матрица\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("Введите коэффициент при переменной %d в уравнении %d: ",j+1,i+1);
            scanf("%lf",&mas[i][j]);
        }
        printf("Введите решение уравнения %d: ",i+1);
        scanf("%lf",&y[i]);
    }

    printf("Матрица\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4.3lf ",mas[i][j]);
        }
        printf("%4.3lf ",y[i]);
    }

    x=Gauss5(mas,y,n);

    printf("Верхнетреугольная матрица\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4.3lf ",mas[i][j]);
        }
        printf("%4.3lf ",y[i]);
    }
    printf("Решения:\n");
    for(i=0;i<n;i++)printf("x[%d] = %lf\n",i,x[i]);

    for(i=0;i<n;i++)free(mas[i]);
    free(mas);
}

void Gauss6(double**mas,double**id,int n)
{
  double **newmas,max;
  int k,index,i,j;
  const double e=0.00001;
  newmas=(int**)malloc(n*sizeof(int*));
  for(i=0;i<n;i++)newmas[i]=(int*)malloc(n*sizeof(double));
  k=0;
  while(k<n)
  {
    max=fabs(mas[k][k]);
    index=k;
    for(i=k+1;i<n;i++)
    {
      if(fabs(mas[i][k])>max)
      {
        max=fabs(mas[i][k]);
        index=i;
      }
    }
    for(j=0;j<n;j++)
    {
        swap(&mas[k][j],&mas[index][j]);
        swap(&id[k][j],&id[index][j]);
    }

    for(i=k;i<n;i++)
    {
      double t=mas[i][k];
      if(fabs(t)<e)continue;
      for(j=0;j<n;j++)
      {
          mas[i][j]=mas[i][j]/t;
          id[i][j]=id[i][j]/t;
      }
      if(i==k)continue;
      for(j=0;j<n;j++)
      {
          mas[i][j]=mas[i][j]-mas[k][j];
          id[i][j]=id[i][j]-id[k][j];
      }
    }
    k++;
  }

  for(k=n-1;k>0;k--)
  {
      for(i=k-1;i>=0;i--)
      {
        double t=mas[i][k];
        if(fabs(t)<e)continue;
        mas[i][k]=mas[i][k]/t;
        for(j=0;j<n;j++)id[i][j]=id[i][j]/t;
        if(i==k)continue;
        mas[i][k]=mas[i][k]-mas[k][k];
        for(j=0;j<n;j++)id[i][j]=id[i][j]-id[k][j];
      }
  }
}

void Task6()
{
    printf("Задание 6\n");
    int n,i,j,k;
    double **mas,**initmas,**check,**id;
    printf("Введите количество строк и столбцов(n)\n");
    scanf("%d",&n);
    mas=(int**)malloc(n*sizeof(int*));
    initmas=(int**)malloc(n*sizeof(int*));
    check=(int**)malloc(n*sizeof(int*));
    id=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++)
    {
        mas[i]=(int*)malloc(n*sizeof(double));
        initmas[i]=(int*)malloc(n*sizeof(double));
        check[i]=(int*)malloc(n*sizeof(double));
        id[i]=(int*)malloc(n*sizeof(double));
    }

    printf("Матрица\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("Введите элемент (%d х %d): ",i+1,j+1);
            scanf("%lf",&mas[i][j]);
            initmas[i][j]=mas[i][j];
            if(i==j)id[i][j]=1;
            else id[i][j]=0;
        }
    }

    printf("Матрица:\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4.3lf ",mas[i][j]);
        }
    }

    Gauss6(mas,id,n);

    printf("Обратная матрица:\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            printf("%4.3lf ",id[i][j]);
        }
    }

    printf("Проверка(результат умножения):\n");
    for(i=0;i<n;i++,printf("\n"))
    {
        for(j=0;j<n;j++)
        {
            check[i][j]=0;
            for(k=0;k<n;k++)check[i][j]=check[i][j]+(id[i][k]*initmas[k][j]);
            printf("%4.3lf ",check[i][j]);
        }
    }

    for(i=0;i<n;i++)
    {
        free(mas[i]);
        free(initmas[i]);
        free(check[i]);
        free(id[i]);
    }
    free(mas);
    free(initmas);
    free(check);
    free(id);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printf("Task 9\n");
    int task;
    do
    {
        printf("Введите номер задания(0-выход,1,2,5,6)\n");
        scanf("%d",&task);
        switch(task)
        {
        case 0:
            break;
        case 1:
            Task1();
            break;
        case 2:
            Task2();
            break;
        case 5:
            Task5();
            break;
        case 6:
            Task6();
            break;
        default:
            printf("Данное задание не выполнено");
            break;
        }
        printf("\n");
    }while(task!=0);
    return 0;
}
