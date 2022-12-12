/*
  m,n >= 0:   dimension of src matrix
  m: number of rows
  n: number of columns

  float* src: source matrix (m-by-n matrix)
  rs_s, cs_s >= 1: row and column stride of source matrix
  rs_s: distance in memory between rows (rs_s = 1 --> column major ordering)
  cs_s: distance in memory between columns (cs_s = 1 --> row major ordering)

  float* dst: destination matrix (n-by-m matrix)
  rs_d, cs_d >= 1: row and column stride of destination matix

  NOTE: This is an out-of-place transposition meaning src and
        dst WILL NOT OVERLAP.
*/

#ifndef FUN_NAME
#define FUN_NAME variant03_transpose
#endif

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d)
{
  //if row stride of source matrix = 1 && row stride of destination matrix = 1
  if(rs_s == 1 && rs_d == 1)
  {
    #pragma omp parallel for num_threads(16)
    for(int i = 0; i < m * n; i++)
    {
      dst[(i / cs_s) + (i % cs_s) * cs_d] = src[i];
    }
  }
    //if column stride of source matrix = 1 && column stride of destination matrix = 1
    else if (cs_s == 1 && cs_d == 1)
    {
      #pragma omp parallel for num_threads(16)
      for(int i = 0; i < m * n; i++)
      {
        dst[(i / cs_s) + (i % cs_s) * cs_d] = src[i];
      }
    }
      //if row stride of source matrix = 1 && column stride of destination matrix = 1
      else if (rs_s == 1 && cs_d == 1)
      {
        #pragma omp parallel for num_threads(16)
        for(int i = 0; i < m * n; i++)
        {
          dst[i] = src[i];
        }
      }
        //if column stride of source matrix = 1 && row stride of destination matrix = 1
        else if (cs_s == 1 && rs_d == 1)
        {
          #pragma omp parallel for num_threads(16)
          for(int i = 0; i < m * n; i++)
          {
            dst[i] = src[i];
          }
        }
          else
          {
            #pragma omp parallel for num_threads(4)
            for(int i = 0; i < m; i++)
            {
              #pragma omp parallel for num_threads(4)
              for(int j = 0; j < n; j++)
              {
                dst[(j * rs_d) + (i * cs_d)] = src[(j * rs_d) + (i * cs_d)];
              }
            }
          }
}
