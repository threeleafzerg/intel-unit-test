#include <stdio.h>
#include <vector>

using namespace std;


void rotate(vector<vector<int>>& mat, int N) {

// Consider all squares one by one 
	for (int x = 0; x < N / 2; x++) 
	{ 
  	// Consider elements in group of 4 in  
  	// current square 
  	for (int y = x; y < N-x-1; y++) 
  	{ 
  		// store current cell in temp variable 
  		int temp = mat[x][y]; 
  
  		// move values from right to top 
  		mat[x][y] = mat[y][N-1-x]; 
  
  		// move values from bottom to right 
  		mat[y][N-1-x] = mat[N-1-x][N-1-y]; 
  
  		// move values from left to bottom 
  		mat[N-1-x][N-1-y] = mat[N-1-y][x]; 
 
  		// assign temp to left 
  		mat[N-1-y][x] = temp; 
  	} 
	}
}

bool compare_mat(const vector<vector<int>>&mat_lhs, const vector<vector<int>>&mat_rhs, int N) {
	for (int i = 0; i < N; ++i) 
		for(int j = 0; j < N; ++j)
			if(mat_lhs[i][j] != mat_rhs[i][j]) return false;
	return true;
}

void print_mat(const vector<vector<int>>&mat, int N) {
  for (int i = 0; i < N; ++i)
    for(int j = 0; j < N; ++j)
      printf("mat[%d][%d]=%d\n", i, j, mat[i][j]);
}

bool unit_test(vector<vector<int>>&mat_inp, const vector<vector<int>>&mat_exp, int N) {
  rotate(mat_inp, N);
	return compare_mat(mat_inp, mat_exp, N);	
}

int main(int argc, char **argv) {
  vector<vector<int>> in_mat1{{1}};
  vector<vector<int>> ex_mat1{{1}};
  if (unit_test(in_mat1, ex_mat1, 1)) {
    printf("unit_test pass for mat1!\n");
  } else {
    printf("unit_test fail for mat1!\n");
  }

  vector<vector<int>> in_mat2{{1,2},{3,4}};
  vector<vector<int>> ex_mat2{{2,4},{1,3}};
  if (unit_test(in_mat2, ex_mat2, 2)) {
    printf("unit_test pass for mat2!\n");
  } else {
    printf("unit_test fail for mat2!\n");
  }

  vector<vector<int>> in_mat3{{1,2,3},{4,5,6},{7,8,9}};
  vector<vector<int>> ex_mat3{{3,6,9},{2,5,8},{1,4,7}};
  if (unit_test(in_mat3, ex_mat3, 3)) {
    printf("unit_test pass for mat3!\n");
  } else {
    printf("unit_test fail for mat3!\n");
  }
  return 0;
}

