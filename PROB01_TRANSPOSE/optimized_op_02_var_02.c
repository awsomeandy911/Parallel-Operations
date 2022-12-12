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

#include <pthread.h>
#include <stdio.h>

#ifndef NTHREADS
#define NTHREADS 5
#endif

#ifndef FUN_NAME
#define FUN_NAME variant02_transpose
#endif

struct thread_data {
  int m;
  int n;
  float *src;
  int rs_s;
  int cs_s;
  float *dst;
  int rs_d;
  int cs_d;
};

void transpose(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d) {
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      dst[j * rs_d + i * cs_d] = src[i * rs_s + j * cs_s];
    }
  }
}

void thread_func(struct thread_data *args)
{
  int m = (*args).m;
  int n = (*args).n;
  float *src = (*args).src;
  int rs_s = (*args).rs_s;
  int cs_s = (*args).cs_s;
  float *dst = (*args).dst;
  int rs_d = (*args).rs_d;
  int cs_d = (*args).cs_d;

  transpose(m, n, src, rs_s, cs_s, dst, rs_d, cs_d);
}

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d)
{
  // Create 4 threads to transpose each submatrix
  pthread_t tid;
  
  struct thread_data args;
  args.m = m;
  args.n = n;
  args.src = src;
  args.rs_s = rs_s;
  args.cs_s = cs_s;
  args.dst = dst;
  args.rs_d = rs_d;
  args.cs_d = cs_d;

  pthread_create(&tid, NULL, (void *)thread_func, &args);
  pthread_join(tid, NULL);
}