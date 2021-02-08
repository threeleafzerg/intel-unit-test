#pragma once

#include "kernel.hpp"

#define HANDLE_CASE(A, B, C, D) \
  launchKernel<A, B, C, D>();

#define HANDLE_D_CASE(A, B, C, D) {      \
  switch (D) {                                 \
    case 1:                                 	 \
      HANDLE_CASE(A, B, C, 1);         	 \
      break;                                	 \
    case 2:                                 	 \
      HANDLE_CASE(A, B, C, 2);         	 \
      break;                                	 \
    case 3:                                 	 \
      HANDLE_CASE(A, B, C, 3);         	 \
      break;                                	 \
    case 4:                                 	 \
      HANDLE_CASE(A, B, C, 4);         	 \
      break;                                	 \
    case 5:                                 	 \
      HANDLE_CASE(A, B, C, 5);         	 \
      break;                                	 \
    case 6:                                 	 \
      HANDLE_CASE(A, B, C, 6);         	 \
      break;                                	 \
    case 7:                                 	 \
      HANDLE_CASE(A, B, C, 7);         	 \
      break;                                	 \
    case 8:                                 	 \
      HANDLE_CASE(A, B, C, 8);         	 \
      break;                                	 \
    case 9:                                 	 \
      HANDLE_CASE(A, B, C, 9);         	 \
      break;                                	 \
    case 10:                                 	 \
      HANDLE_CASE(A, B, C, 10);         	 \
      break;                                	 \
    case 11:                                 	 \
      HANDLE_CASE(A, B, C, 11);         	 \
      break;                                	 \
    default:                                	 \
      HANDLE_CASE(A, B, C,-1);         	 \
      break;                                	 \
  }                                         	 \
}

#define HANDLE_C_CASE(A, B, C, D) {      \
  switch (C) {                                 \
    case 1:                                 	 \
      HANDLE_D_CASE(A, B, 1, D);       	 \
      break;                                	 \
    case 2:                                 	 \
      HANDLE_D_CASE(A, B, 2, D);       	 \
      break;                                	 \
    case 3:                                 	 \
      HANDLE_D_CASE(A, B, 3, D);       	 \
      break;                                	 \
    case 4:                                 	 \
      HANDLE_D_CASE(A, B, 4, D);       	 \
      break;                                	 \
    case 5:                                 	 \
      HANDLE_D_CASE(A, B, 5, D);       	 \
      break;                                	 \
    case 6:                                 	 \
      HANDLE_D_CASE(A, B, 6, D);       	 \
      break;                                	 \
    case 7:                                 	 \
      HANDLE_D_CASE(A, B, 7, D);       	 \
      break;                                	 \
    case 8:                                 	 \
      HANDLE_D_CASE(A, B, 8, D);       	 \
      break;                                	 \
    case 9:                                 	 \
      HANDLE_D_CASE(A, B, 9, D);       	 \
      break;                                	 \
    case 10:                                 	 \
      HANDLE_D_CASE(A, B, 10, D);       	 \
      break;                                	 \
    case 11:                                 	 \
      HANDLE_D_CASE(A, B, 11, D);       	 \
      break;                                	 \
    default:                                	 \
      HANDLE_D_CASE(A, B, -1,D);       	 \
      break;                                	 \
  }                                         	 \
}

#define HANDLE_B_CASE(A, B, C, D) {      \
  switch (B) {                                 \
    case 1:                                 	 \
      HANDLE_C_CASE(A, 1, C, D);       	 \
      break;                                	 \
    case 2:                                 	 \
      HANDLE_C_CASE(A, 2, C, D);       	 \
      break;                                	 \
    case 3:                                 	 \
      HANDLE_C_CASE(A, 3, C, D);       	 \
      break;                                	 \
    case 4:                                 	 \
      HANDLE_C_CASE(A, 4, C, D);       	 \
      break;                                	 \
    case 5:                                 	 \
      HANDLE_C_CASE(A, 5, C, D);       	 \
      break;                                	 \
    case 6:                                 	 \
      HANDLE_C_CASE(A, 6, C, D);       	 \
      break;                                	 \
    case 7:                                 	 \
      HANDLE_C_CASE(A, 7, C, D);       	 \
      break;                                	 \
    case 8:                                 	 \
      HANDLE_C_CASE(A, 8, C, D);       	 \
      break;                                	 \
    case 9:                                 	 \
      HANDLE_C_CASE(A, 9, C, D);       	 \
      break;                                	 \
    case 10:                                 	 \
      HANDLE_C_CASE(A, 10, C, D);       	 \
      break;                                	 \
    case 11:                                 	 \
      HANDLE_C_CASE(A, 11, C, D);       	 \
      break;                                	 \
    default:                                	 \
      HANDLE_C_CASE(A,-1, C, D);       	 \
      break;                                	 \
  }                                         	 \
}

#define HANDLE_A_CASE(A, B, C, D) {      \
  switch (A) {                                 \
    case 1:                                 	 \
      HANDLE_B_CASE(1, B, C, D);       	 \
      break;                                	 \
    case 2:                                 	 \
      HANDLE_B_CASE(2, B, C, D);       	 \
      break;                                	 \
    case 3:                                 	 \
      HANDLE_B_CASE(3, B, C, D);       	 \
      break;                                	 \
    case 4:                                 	 \
      HANDLE_B_CASE(4, B, C, D);       	 \
      break;                                	 \
    case 5:                                 	 \
      HANDLE_B_CASE(5, B, C, D);       	 \
      break;                                	 \
    case 6:                                 	 \
      HANDLE_B_CASE(6, B, C, D);       	 \
      break;                                	 \
    case 7:                                 	 \
      HANDLE_B_CASE(7, B, C, D);       	 \
      break;                                	 \
    case 8:                                 	 \
      HANDLE_B_CASE(8, B, C, D);       	 \
      break;                                	 \
    case 9:                                 	 \
      HANDLE_B_CASE(9, B, C, D);       	 \
      break;                                	 \
    case 10:                                 	 \
      HANDLE_B_CASE(10, B, C, D);       	 \
      break;                                	 \
    case 11:                                 	 \
      HANDLE_B_CASE(11, B, C, D);       	 \
      break;                                	 \
    default:                                	 \
      HANDLE_B_CASE(-1,B, C, D);       	 \
      break;                                	 \
  }                                         	 \
}
