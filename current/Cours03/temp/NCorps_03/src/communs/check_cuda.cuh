#ifndef __CHECK_CUDA_CUH__
#define __CHECK_CUDA_CUH__

#define checkCudaOperation(call) do { \
  cudaError_t err = call; \
  if (err != cudaSuccess) { \
    fprintf(stderr, "CUDA error in %s at %d: %s \n", \
      __FILE__, __LINE__, cudaGetErrorString(err)); \
      exit(err); \
    } \
  } while (0)

#define checkCudaKernel() {                                      \
  cudaDeviceSynchronize();                                       \
  cudaError_t e = cudaGetLastError();                            \
  if (e!=cudaSuccess) {                                          \
    std::cerr << "Cuda failure " << __FILE__ << ":" << __LINE__  \
              << ":" << cudaGetErrorString(e) << std::endl;      \
    exit(0);                                                     \
  }                                                              \
}

#endif
