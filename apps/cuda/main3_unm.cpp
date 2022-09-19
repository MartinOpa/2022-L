#include <stdio.h>
#include <cuda_device_runtime_api.h>
#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>
#include "uni_mem_allocator.h"
#include "cuda_img.h"

void cu_create_alphaimg( CudaImg t_color_cuda_img, uchar3 t_color );
void cu_draw_circle( CudaImg t_color_cuda_img, int2 t_pos, int t_r, uchar3 t_color );
void cu_insertimage( CudaImg t_big_cuda_img, CudaImg t_small_cuda_img, int2 t_position );

#define SIZEX 1500
#define	SIZEY 1000
#define BLOCKX 40
#define BLOCKY 25

int main()
{
	UniformAllocator allocator;
	cv::Mat::setDefaultAllocator( &allocator );

	cv::Mat l_cv_img( SIZEY, SIZEX, CV_8UC3 );

	char3 l_bgr_white = { (char)255, (char)255, (char)255 }; 
    char3 l_bgr_blue = { (char)255, 0, 0 }; 
    char3 l_bgr_red = { (char)60, (char)40, (char)235 };

    for ( int y = 0; y < l_cv_img.rows; y++ ) 
        for ( int x  = 0; x < l_cv_img.cols; x++ )
		{ 
            char3 bgr; 
 
            if(x >= 0 && (x < SIZEX / 3))
            { 
                bgr = l_bgr_blue; 
            }
            
            if ((x >= SIZEX / 3) && (x < SIZEX / 3 * 2))
            { 
                bgr = l_bgr_white; 
            }
			
            if ((x >= SIZEX / 3 * 2) && (x < SIZEX))
            {
                bgr = l_bgr_red; 
            }

			cv::Vec3b l_v3bgr( bgr.x, bgr.y, bgr.z );
			l_cv_img.at<cv::Vec3b>( y, x ) = l_v3bgr;
		}

	CudaImg l_cuda_img;
	l_cuda_img.m_size.x = l_cv_img.size().width;
	l_cuda_img.m_size.y = l_cv_img.size().height;
	l_cuda_img.m_p_uchar3 = ( uchar3* ) l_cv_img.data;

	cv::Mat l_alphaimg_cv_img( 1000, 1000, CV_8UC4 );

	CudaImg l_alphaimg_cuda_img;
	l_alphaimg_cuda_img.m_size.x = l_alphaimg_cv_img.cols;
	l_alphaimg_cuda_img.m_size.y = l_alphaimg_cv_img.rows;
	l_alphaimg_cuda_img.m_p_uchar4 = ( uchar4 * ) l_alphaimg_cv_img.data;

	cu_draw_circle( l_alphaimg_cuda_img, { 500, 500}, 400, { 125, 0, 0 } );

	cu_insertimage( l_cuda_img, l_alphaimg_cuda_img, { 250, 0 } );

	cv::imshow( "Surrender", l_cv_img );

	cv::waitKey( 0 );
}

