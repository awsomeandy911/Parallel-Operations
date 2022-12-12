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
#define FUN_NAME variant1_transpose
#endif

void FUN_NAME(int m, int n, float *src, int rs_s, int cs_s, float *dst, int rs_d, int cs_d) {
  int block = 32;
  // For row major source to column major destination
  // The matrix is stored row-major order internally. Traverse dst by hopping across blocks
  if ((rs_s == 1) && (cs_d == 1)) {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; j+=block) {
	for (int k = 0; (k < block) && (j+k < n); ++k) {
	  dst[i*m+j+k] = src[(i+k)*n+j];
	}
      }
    }
  }
  // For column major source to row major destination
  // The matrix is stored row-major order internally anyways. Traverse src by hopping across blocks
  else if ((cs_s == 1) && (rs_d == 1)) {
    for (int i = 0; i < m; i+=block) {
      for (int j = 0; j < n; ++j) {
	for (int k = 0; (k < block) && (i+k < n); ++k) {
	  dst[i*m+j+k] = src[(j+k)*n+i];
  	}
      }
    }
  }
  // For row major source to row major destination, column major source to column major destination
  else {
    for (int i = 0; i < m; i+=block) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; (k < block) && (i+k < n); ++k) {
	  dst[j*m+i+k] = src[(i+k)*n+j];
        }
      }
    }
  }
}
