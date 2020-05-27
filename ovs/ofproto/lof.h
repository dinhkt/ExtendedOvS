#ifndef __lof_h__
#define __lof_h__


#define DATANUM 500
#define KNN 15

typedef struct neighbor
{
    int id;
    float distance;
}neighbor_t;

typedef struct data
{
    int id;
    float traffic_norm;
    float n_flow_norm;
    float k_distance;
    neighbor_t neighbor[DATANUM];
    float lrd;
    float LOF;
}data_t;

float distance(data_t *a, data_t *b);
float reachability_distance(data_t *a,data_t *b);
void swap(neighbor_t *a, neighbor_t *b);
void bubble_sort_k(data_t *point, int n,int k);
void lrd(data_t *Data[],int n);
float calc_LOF(data_t *Data[],int n,data_t* point);
float calc_ip_ent(float* arr,int n);
float calc_mu(float *arr,int n);
float calc_sigma(float *arr,int n);
float normalize(float x, float mu,float sigma);
float normalize_minmax(float x, float max,float min);
float get_max(float *arr,int n);
float get_min(float *arr,int n);

#endif