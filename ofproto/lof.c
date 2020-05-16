#include "lof.h"
#include <math.h> 



float distance(data_t *a, data_t *b)
{
    return sqrt(pow((a->n_flow_norm-b->n_flow_norm),2)+pow((a->traffic_norm-b->traffic_norm),2));
}

float reachability_distance(data_t *a,data_t *b)
{
    if(b->k_distance>distance(a,b))
        return b->k_distance;
    else return distance(a,b);

}

void swap(neighbor_t *a, neighbor_t *b)
{
    neighbor_t tmp;
    tmp=*a;
    *a=*b;
    *b=tmp;
}
//Find k nearest neighbor
void bubble_sort_k(data_t *point, int n,int k)
{
    int i, j; 
    for (i = n; i > n-k; i--)          
        for (j = n-1; j > n-i; j--)  
           if (point->neighbor[j].distance < point->neighbor[j-1].distance) 
              swap(&point->neighbor[j], &point->neighbor[j-1]);
}
void lrd(data_t *Data[],int n)
{
    for(int i=0;i<n;i++)
    {
        Data[i]->id=i;
        for (int j=0;j<n;j++)
        {
            Data[i]->neighbor[j].id=j;
            Data[i]->neighbor[j].distance=distance(Data[i],Data[j]);
        }
        bubble_sort_k(Data[i],n,KNN);
        Data[i]->k_distance=Data[i]->neighbor[KNN].distance;
    }

    //calculate lrd of Data[i]
    for(int i=0;i<n;i++)
    {
        Data[i]->lrd=0;
        for (int j=0;j<KNN;j++)
        {
            Data[i]->lrd+=reachability_distance(Data[i],Data[Data[i]->neighbor[j].id]);
        }   
        Data[i]->lrd=KNN/Data[i]->lrd;
    }

}

// Find LOF of data state
float calc_LOF(data_t *Data[],int n,data_t* point)
{
    for (int i=0;i<n;i++)
    {
        point->neighbor[i].id=i;
        point->neighbor[i].distance=distance(point,Data[i]);
    }
    bubble_sort_k(point,n,KNN);
    point->k_distance=point->neighbor[KNN].distance;
    point->lrd=0;
    for (int i=0;i<KNN;i++)
    {
        point->lrd+=reachability_distance(point,Data[point->neighbor[i].id]);
    }   
    point->lrd=KNN/point->lrd;
    //printf("lrd:%f\n",point->lrd);
    float LOF=0;
    for (int j=0;j<KNN;j++)
        {
            LOF+=Data[point->neighbor[j].id]->lrd;
            //printf("%f\n",LOF);
        }
    LOF=LOF/(KNN*point->lrd);
    return LOF;
}

/* Entropy of fields*/
float calc_n_flow_norm(float* arr,int n)
{
    float sum=0;
    float *p_ent;
    float ent=0;
    p_ent=(float *)malloc(n*sizeof(float));

    for(int i=0;i<n;i++)
        {
            sum=sum+arr[i];
        }
    printf("%f\n",sum );
    for(int i=0;i<n;i++)
    {
        p_ent[i]=arr[i]/sum;
        ent+=p_ent[i]*log(p_ent[i])/log(2);
    }
    ent =0-ent;
    return ent;
}

float calc_mu(float *arr,int n)
{
    float sum=0;
    for (int i=0;i<n;i++)
        sum+=arr[i];
    return sum/n;
}
float calc_sigma(float *arr,int n)
{
    float s=0;
    float mu=calc_mu(arr,n);
    for (int i=0;i<n;i++)
        s+=pow((arr[i]-mu),2);
    return sqrt(s/n);
}
float normalize(float x, float mu,float sigma)
{
    return (tanh(0.1*(x-mu)/sigma)+1)/2;
}
float normalize_minmax(float x, float max,float min)
{
    return (x-min)/(max-min);
}
float get_max(float *arr,int n)
{
    int i=1;
    float max=arr[0];
    while(i<n)
    {
        if (arr[i]>max) 
            max=arr[i];
        i++;
    }
    return max;
}
float get_min(float *arr,int n)
{
    int i=1;
    float min=arr[0];
    while(i<n)
    {
        if (arr[i]<min) 
            min=arr[i];
        i++;
    }
    return min;
}