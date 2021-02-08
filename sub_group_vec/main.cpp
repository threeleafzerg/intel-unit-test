#include <iostream>
#include "CL/cl.h"
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>

using namespace std;

#define MEM_SIZE (1)
#define MAX_SOURCE_SIZE (0x100000)

void verifyResult(const float *arr, int num) {
  for (int i = 0; i < num; i++) {
    if (arr[i] != 1) {
      std::cout << "verify failed!" << std::endl;
    }
  }
}

int main(int argc, char* argv[])
{
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem memobjX = NULL;
    cl_mem memobjY = NULL;
    cl_mem memobjResult = NULL;
    cl_mem memobjResultSum = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_kernel kernelSum = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret;

    int num, test;

    if (argc == 2)
    {
        num = atoi(argv[1]);
        test = 0;
    }
    if (argc == 3)
    {
        num = atoi(argv[1]);
        test = atoi(argv[2]);
    }
    else
    {
        num = 256 * 256 * 256;
        test = 0;
    }

    const int incx = 1;
    const int incy = 1;

    cout.precision(10);

    cout << "OpenCL Dot Product example for this number of workitems: " << num << endl;

    float* x = (float*)malloc(num * sizeof(float));
    float* y = (float*)malloc(num * sizeof(float));
    float* result = (float*)malloc(num * sizeof(float));


    for (int i = 0; i < num; ++i)
    {
        x[i] = 1; y[i] = 1;
    }

    auto start = std::chrono::system_clock::now();

    float acc = 0.f;
    for (int i = 0; i < num; ++i)
    {
        acc += x[i] * y[i];
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << endl << "CPU: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << acc << "\n";

    FILE* fp;
    char fileName[] = "kernels.cl";
    char* source_str;
    size_t source_size;

    fp = fopen(fileName, "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);


    ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    memobjX = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * num, NULL, &ret);
    memobjY = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * num, NULL, &ret);
    memobjResult = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * num, NULL, &ret);

    ret = clEnqueueWriteBuffer(command_queue, memobjX, CL_TRUE, 0, sizeof(float) * num, x, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, memobjY, CL_TRUE, 0, sizeof(float) * num, y, 0, NULL, NULL);

    program = clCreateProgramWithSource(context, 1, (const char**)& source_str, (const size_t*)& source_size, &ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (ret != CL_SUCCESS) {
      std::cout << "clBuildProgram fail ret:" << ret  << std::endl;
    }

    size_t global_item_size = num;
    size_t local_item_size = 1;

    /* Optimization 1 */
    if (test == 0 || test == 1)
    {
        kernel = clCreateKernel(program, "Dot_opt1", &ret);
        ret = clSetKernelArg(kernel, 0, sizeof(int), &num);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)& memobjX);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)& memobjY);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)& memobjResult);


        global_item_size = num;
        local_item_size = 256;

        start = std::chrono::system_clock::now();
        //ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
        ret = clEnqueueReadBuffer(command_queue, memobjResult, CL_TRUE, 0, sizeof(cl_float) * num, result, 0, NULL, NULL);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        std::cout << endl << "Optimized 1: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << result[0] << "\n";
        verifyResult(result, num);
    }

    /* Optimization 2 */
    if (test == 0 || test == 2)
    {
        kernel = clCreateKernel(program, "Dot_opt2", &ret);
        ret = clSetKernelArg(kernel, 0, sizeof(int), &num);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)& memobjX);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)& memobjY);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)& memobjResult);

        global_item_size = num/8;
        local_item_size = 256;

        start = std::chrono::system_clock::now();
        //ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
        ret = clEnqueueReadBuffer(command_queue, memobjResult, CL_TRUE, 0, sizeof(cl_float) * num, result, 0, NULL, NULL);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        std::cout << endl << "Optimized 2: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << result[0] << "\n";
        verifyResult(result, num);
    }

    /* Optimization 3 */
    if (test == 0 || test == 3)
    {
        kernel = clCreateKernel(program, "Dot_opt3", &ret);
        ret = clSetKernelArg(kernel, 0, sizeof(int), &num);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)& memobjX);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)& memobjY);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)& memobjResult);

        global_item_size = 16;
        local_item_size = 16;

        start = std::chrono::system_clock::now();
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
        ret = clEnqueueReadBuffer(command_queue, memobjResult, CL_TRUE, 0, sizeof(cl_float), result, 0, NULL, NULL);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        std::cout << endl << "Optimized 3: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << result[0] << "\n";
    }

    /* Optimization 4 */
    if (test == 0 || test == 4 || test == 7)
    {
        kernel = clCreateKernel(program, "Dot_opt4", &ret);
        ret = clSetKernelArg(kernel, 0, sizeof(int), &num);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)& memobjX);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)& memobjY);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)& memobjResult);

        global_item_size = 256;
        local_item_size = 256;

        start = std::chrono::system_clock::now();
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
        ret = clEnqueueReadBuffer(command_queue, memobjResult, CL_TRUE, 0, sizeof(cl_float), result, 0, NULL, NULL);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        std::cout << endl << "Optimized 4: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << result[0] << "\n";
    }

    /* Optimization 5 */
    int sizeFactor = 32;
    if (test == 0 || test == 5 || test == 7)
    {
        kernel = clCreateKernel(program, "Dot_opt5", &ret);

        memobjResult = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * sizeFactor, NULL, &ret);
        ret = clSetKernelArg(kernel, 0, sizeof(int), &num);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)& memobjX);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)& memobjY);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)& memobjResult);

        global_item_size = 256 * sizeFactor;
        local_item_size = 256;

        start = std::chrono::system_clock::now();
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, NULL, 0, NULL, NULL);
        ret = clEnqueueReadBuffer(command_queue, memobjResult, CL_TRUE, 0, sizeof(cl_float) * sizeFactor, result, 0, NULL, NULL);

        float sum = 0;
        for (int i = 0; i < sizeFactor; ++i)
        {
            sum += result[i];
        }

        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;

        std::cout << endl << "Optimized 5: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << sum << "\n";
    }

    /* Optimization 6 */
    if (test == 0 || test == 6 || test == 7)
    {
        kernel = clCreateKernel(program, "Dot_opt6", &ret);
        kernelSum = clCreateKernel(program, "sum", &ret);
        memobjResult = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * sizeFactor, NULL, &ret);
        memobjResultSum = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float), NULL, &ret);

        ret = clSetKernelArg(kernel, 0, sizeof(int), &num);
        ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)& memobjX);
        ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)& memobjY);
        ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)& memobjResult);

        ret = clSetKernelArg(kernelSum, 0, sizeof(int), &sizeFactor);
        ret = clSetKernelArg(kernelSum, 1, sizeof(cl_mem), (void*)& memobjResult);
        ret = clSetKernelArg(kernelSum, 2, sizeof(cl_mem), (void*)& memobjResultSum);

        global_item_size = 256 * sizeFactor;
        local_item_size = 256;

        size_t iSize = sizeFactor;
        cl_event kernel_event;

        start = std::chrono::system_clock::now();
        ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, NULL, 0, NULL, &kernel_event);
        //clWaitForEvents(1, &kernel_event);
        ret = clEnqueueNDRangeKernel(command_queue, kernelSum, 1, NULL, &iSize, NULL, 0, NULL, NULL);
        ret = clEnqueueReadBuffer(command_queue, memobjResultSum, CL_TRUE, 0, sizeof(cl_float), result, 0, NULL, NULL);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        std::cout << endl << "Optimized 6: Elapsed time: " << elapsed_seconds.count() << "s, Result: " << result[0] << "\n";
    }

    /* Finalization */
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseKernel(kernelSum);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(memobjX);
    ret = clReleaseMemObject(memobjY);
    ret = clReleaseMemObject(memobjResult);
    ret = clReleaseMemObject(memobjResultSum);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    free(source_str);
    free(x);
    free(y);

    return 0;
}
