
__attribute__((intel_reqd_sub_group_size(8)))
__kernel void Dot_opt1(int n, __global float* x, __global float* y, __global float* result)
{
    int gid = get_global_id(0);
    result[gid] = x[gid] * y[gid];
}

__attribute__((intel_reqd_sub_group_size(8)))
__kernel void Dot_opt2(int n, __global float* x, __global float* y, __global float* result)
{
    int gid = get_global_id(0);
    float8 x_v = vload8(gid, x);
    float8 y_v = vload8(gid, y);
    float8 r_v = x_v * y_v;
    vstore8(r_v, gid, result);
}


__attribute__((intel_reqd_sub_group_size(16)))
__kernel void Dot_opt3(int n, __global float* x, __global float* y, __global float* result)
{
    int gid = get_global_id(0);

    float acc = 0.f;
    int element_id = gid;
    for (int i = 0; i < (n / 16); ++i)
    {
        acc += x[element_id] * y[element_id];
        element_id += 16;
    }
    // leftovers
    if (element_id < n)
        acc += x[element_id] * y[element_id];

    // sum all of the accumulators
    float simd_acc = sub_group_reduce_add(acc);
    if (gid == 0)
    {
        result[0] = simd_acc;
    }
}

#define SIMDS_COUNT (256/16)
__attribute__((intel_reqd_sub_group_size(16)))
__kernel void Dot_opt4(int n, __global float* x, __global float* y, __global float* result)
{
    int gid = get_global_id(0);
    int simd_id = get_sub_group_id();

    __local float local_acc[SIMDS_COUNT];

    float acc = 0.f;
    int element_id = gid;
    for (int i = 0; i < (n / 256); ++i)
    {
        acc += x[element_id] * y[element_id];
        element_id += 256;
    }
    // leftovers
    if (element_id < n)
        acc += x[element_id] * y[element_id];

    // sum all of the accumulators
    float simd_acc = sub_group_reduce_add(acc);

    local_acc[simd_id] = simd_acc;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (simd_id == 0)
    {
        float _local_acc = local_acc[get_sub_group_local_id()];

        float final_acc = sub_group_reduce_add(_local_acc);
        result[0] = final_acc;
    }
}


#define SIMDS_COUNT (256/16)
__attribute__((intel_reqd_sub_group_size(16)))
__kernel void Dot_opt5(int n, __global float* x, __global float* y, __global float* result)
{
    int gid = get_global_id(0);
    int simd_id = get_sub_group_id();
    int groups_num = get_num_groups(0);
    int group_id = get_group_id(0);

    __local float local_acc[SIMDS_COUNT];

    float acc = 0.f;
    int element_id = gid;

    for (int i = 0; i < (n / (256 * groups_num)); ++i)
    {
        acc += x[element_id] * y[element_id];
        element_id += 256 * groups_num;
    }
    // leftovers
    if (element_id < n)
        acc += x[element_id] * y[element_id];

    // sum all of the accumulators
    float simd_acc = sub_group_reduce_add(acc);

    local_acc[simd_id] = simd_acc;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (simd_id == 0)
    {
        float _local_acc = local_acc[get_sub_group_local_id()];

        float final_acc = sub_group_reduce_add(_local_acc);
        result[group_id] = final_acc;
    }
}



#define SIMDS_COUNT (256/16)
__attribute__((intel_reqd_sub_group_size(32)))
__kernel void Dot_opt6(int n, __global float* x, __global float* y, __global float* result)
{
    int gid = get_global_id(0);
    int simd_id = get_sub_group_id();
    int groups_num = get_num_groups(0);
    int group_id = get_group_id(0);

    __local float local_acc[SIMDS_COUNT];

    //printf("get_local_size: %d\n", get_local_size(0));

    float acc = 0.f;
    int element_id = gid;

    for (int i = 0; i < (n / (256 * groups_num)); ++i)
    {
        acc += x[element_id] * y[element_id];
        element_id += 256 * groups_num;
    }
    // leftovers
    if (element_id < n)
        acc += x[element_id] * y[element_id];

    // sum all of the accumulators
    float simd_acc = sub_group_reduce_add(acc);

    local_acc[simd_id] = simd_acc;
    barrier(CLK_LOCAL_MEM_FENCE);

    if (simd_id == 0)
    {
        float _local_acc = local_acc[get_sub_group_local_id()];

        float final_acc = sub_group_reduce_add(_local_acc);
        result[group_id] = final_acc;
    }
}

__attribute__((intel_reqd_sub_group_size(32)))
__kernel void sum(int n, __global float* x, __global float* result)
{
    int gid = get_global_id(0);
    float acc = 0;
    if (gid < n)
        acc += x[gid];

    float simd_acc = sub_group_reduce_add(acc);
    result[0] = simd_acc;
}
