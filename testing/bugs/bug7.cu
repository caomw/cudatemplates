/*
  compiling this program with "nvcc -c bug7.cu" gives the following message:

  ### Assertion failure at line 123 of ../../be/cg/NVISA/expand.cxx:
  ### Compiler Error in file /tmp/tmpxft_00006ce7_00000000-7_bug7.cpp3.i during Code_Expansion phase:
  ### unexpected mtype
  nvopencc INTERNAL ERROR: /usr/open64/lib//be returned non-zero status 1

  Distribution: openSUSE-11.1
  Architecture: x86_64
  gcc-4.3.2
  CUDA toolkit: 2.3beta
*/

__device__ void function()
{
  float3 x0;
  float3 array[8];
  array[0] = x0;
  int i = 0;

  for(;;) {
    if(array[i].x < 0) {
      i++;
      continue;
    }

    array[i] = x0;
  }
}

__global__ void kernel()
{
  function();
}
