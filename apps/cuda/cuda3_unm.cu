#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include "cuda_img.h"

__global__ void kernel_draw_circle( CudaImg t_color_cuda_img, int2 t_pos, int t_r, uchar3 t_color )
{

	int l_y = blockDim.y * blockIdx.y + threadIdx.y;
	int l_x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( l_y >= t_color_cuda_img.m_size.y ) return;
	if ( l_x >= t_color_cuda_img.m_size.x ) return;

	int l_dx = l_x - t_pos.x;
	int l_dy = l_y - t_pos.y;
	int l_r = sqrtf( l_dx * l_dx + l_dy * l_dy );

	t_color_cuda_img.m_p_uchar4[ l_y * t_color_cuda_img.m_size.x + l_x ] =
		{ t_color.x, t_color.y, t_color.z, ( unsigned char ) ( 1 *  (l_r < t_r))};
}

void cu_draw_circle( CudaImg t_color_cuda_img, int2 t_pos, int t_r, uchar3 t_color )
{
	cudaError_t l_cerr;

	int l_block_size = 32;
	dim3 l_blocks( ( t_color_cuda_img.m_size.x + l_block_size - 1 ) / l_block_size,
			       ( t_color_cuda_img.m_size.y + l_block_size - 1 ) / l_block_size );
	dim3 l_threads( l_block_size, l_block_size );
	kernel_draw_circle<<< l_blocks, l_threads >>>( t_color_cuda_img, t_pos, t_r, t_color );

	if ( ( l_cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( l_cerr ) );

	cudaDeviceSynchronize();
}

__global__ void kernel_insertimage( CudaImg t_big_cuda_pic, CudaImg t_small_cuda_pic, int2 t_position )
{
	int l_y = blockDim.y * blockIdx.y + threadIdx.y;
	int l_x = blockDim.x * blockIdx.x + threadIdx.x;
	if ( l_y >= t_small_cuda_pic.m_size.y ) return;
	if ( l_x >= t_small_cuda_pic.m_size.x ) return;
	int l_by = l_y + t_position.y;
	int l_bx = l_x + t_position.x;
	if ( l_by >= t_big_cuda_pic.m_size.y || l_by < 0 ) return;
	if ( l_bx >= t_big_cuda_pic.m_size.x || l_bx < 0 ) return;

	uchar4 l_fg_bgra = t_small_cuda_pic.m_p_uchar4[ l_y * t_small_cuda_pic.m_size.x + l_x ];
	uchar3 l_bg_bgr = t_big_cuda_pic.m_p_uchar3[ l_by * t_big_cuda_pic.m_size.x + l_bx ];
	uchar3 l_bgr = { 0, 0, 0 };

	l_bgr.x = l_fg_bgra.x * l_fg_bgra.w / 255 + l_bg_bgr.x * ( 255 - l_fg_bgra.w ) / 255;
	l_bgr.y = l_fg_bgra.y * l_fg_bgra.w / 255 + l_bg_bgr.y * ( 255 - l_fg_bgra.w ) / 255;
	l_bgr.z = l_fg_bgra.z * l_fg_bgra.w / 255 + l_bg_bgr.z * ( 255 - l_fg_bgra.w ) / 255;

	t_big_cuda_pic.m_p_uchar3[ l_by * t_big_cuda_pic.m_size.x + l_bx ] = l_bgr;
}

void cu_insertimage( CudaImg t_big_cuda_pic, CudaImg t_small_cuda_pic, int2 t_position )
{
	cudaError_t l_cerr;

	int l_block_size = 32;
	dim3 l_blocks( ( t_small_cuda_pic.m_size.x + l_block_size - 1 ) / l_block_size,
			       ( t_small_cuda_pic.m_size.y + l_block_size - 1 ) / l_block_size );
	dim3 l_threads( l_block_size, l_block_size );
	kernel_insertimage<<< l_blocks, l_threads >>>( t_big_cuda_pic, t_small_cuda_pic, t_position );

	if ( ( l_cerr = cudaGetLastError() ) != cudaSuccess )
		printf( "CUDA Error [%d] - '%s'\n", __LINE__, cudaGetErrorString( l_cerr ) );

	cudaDeviceSynchronize();
}


