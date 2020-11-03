#include <iostream>                 
#include <string>
#include <pcl/io/pcd_io.h>          //I/O操作头文件
#include <pcl/point_types.h>        //点类型定义头文件
#include <pcl/registration/icp.h>   //ICP配准类相关头文件
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <sstream> 
#include <ctime>

using namespace std;

void icp(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_1, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_2){
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;//创建IterativeClosestPoint的对象
                 //cloud_out设置为与cloud_in对应的匹配目标
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_1_ds(new pcl::PointCloud<pcl::PointXYZ>); 
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_2_ds(new pcl::PointCloud<pcl::PointXYZ>); 
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud(cloud_1);
    sor.setLeafSize(0.5f, 0.5f, 0.5f);
    sor.filter(*cloud_1_ds);
    sor.setInputCloud(cloud_2);
    sor.filter(*cloud_2_ds);
    PCL_INFO("cloud_1 downsample points is %d. \n", cloud_1_ds->points.size());
    PCL_INFO("cloud_2 downsample points is %d. \n", cloud_2_ds->points.size());

    icp.setInputCloud(cloud_1_ds);                 //cloud_in设置为点云的源点
    icp.setInputTarget(cloud_2_ds);  

    pcl::PointCloud<pcl::PointXYZ>::Ptr Final(new pcl::PointCloud<pcl::PointXYZ>);        //存储经过配准变换点云后的点云
    clock_t startTime,endTime;
    startTime = clock();
    icp.align(*Final); 
    endTime = clock();
    cout << "The align time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud (new pcl::PointCloud<pcl::PointXYZ> ());
    pcl::transformPointCloud (*cloud_1, *transformed_cloud, icp.getFinalTransformation());

    pcl::visualization::PCLVisualizer viewer ("map viewer");
    std::cout << "Transformation: "<< "\n" << icp.getFinalTransformation() << std::endl;
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler_1 (transformed_cloud, 255, 0, 0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler_2 (cloud_2, 0, 255, 0);
    // pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler_3 (Final, 255, 255, 255);
    viewer.addPointCloud<pcl::PointXYZ>(transformed_cloud, cloud_color_handler_1, "cloud_"+to_string(1));
    viewer.addPointCloud<pcl::PointXYZ>(cloud_2, cloud_color_handler_2, "cloud_"+to_string(2));
    // viewer.addPointCloud<pcl::PointXYZ>(Final, cloud_color_handler_3, "cloud_"+to_string(3));
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.0, "cloud_"+to_string(1));
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.0, "cloud_"+to_string(2));
    // viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1.0, "cloud_"+to_string(3));
    

    while (!viewer.wasStopped ()) { // 在按下 "q" 键之前一直会显示窗口
        viewer.spinOnce ();
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr merge(new pcl::PointCloud<pcl::PointXYZ>);
    *merge = *cloud_2 + *transformed_cloud; 
    if(pcl::io::savePCDFileASCII("../aligned_pointcloud.pcd", *merge) == -1){
        PCL_ERROR("Fialed save the pcd file!");
        return;
    }
}

void ndt(){

}


int main (int argc, char** argv)
{ 
  //创建两个pcl::PointCloud<pcl::PointXYZ>共享指针，并初始化它们
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_1 (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_2 (new pcl::PointCloud<pcl::PointXYZ>);
    
    cout << "Read pcd file in curren directory"  << ".\n";
    string pcd_path_1 = {"../cloud_002.pcd"};
    string pcd_path_2 = {"../cloud_003.pcd"};
    if(pcl::io::loadPCDFile(pcd_path_1, *cloud_1) < 0){
        PCL_ERROR("Couldn't read the file which path is %s \n", pcd_path_1);
    }else{
        PCL_INFO("load pcd successfully, points is %d. \n", cloud_1->points.size());
    }
    if(pcl::io::loadPCDFile(pcd_path_2, *cloud_2) < 0){
        PCL_ERROR("Couldn't read the file which path is %s \n", pcd_path_2);
    }else{
        PCL_INFO("load pcd successfully, points is %d. \n", cloud_2->points.size());
    }
 
    icp(cloud_1, cloud_2);
    
         
    // //打印配准相关输入信息
    // std::cout << "has converged:" << icp.hasConverged() << " score: " <<
    // std::cout << "Transformation: "<< "\n" << icp.getFinalTransformation() << std::endl;
 
    return (0);
}