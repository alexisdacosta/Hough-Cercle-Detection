/**
 * ================================================================================
 * @file main.cpp 
 * @author Julien SAVE & Alexis DA COSTA
 * @brief TI - TP2 : Circle Detection by Hough Transform
 * @version 0.1
 * @date 2021-10-16
 * 
 * @copyright APP5 INFO - Polytech Paris-Saclay ©Copyright (c) 2021
 * ================================================================================
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

#define DIV         " ========== "          /* Divider */
#define UNDER       "\033[4m"                /* Underline */
#define RESET       "\033[0m"               /* Reset */
#define BLACK       "\033[30m"              /* Black */
#define RED         "\033[31m"              /* Red */
#define GREEN       "\033[32m"              /* Green */
#define YELLOW      "\033[33m"              /* Yellow */
#define BLUE        "\033[34m"              /* Blue */
#define MAGENTA     "\033[35m"              /* Magenta */
#define CYAN        "\033[36m"              /* Cyan */
#define WHITE       "\033[37m"              /* White */
#define BOLD        "\033[1m"               /* Bold */
#define BOLDBLACK   "\033[1m\033[30m"       /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"       /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"       /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"       /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"       /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"       /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"       /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"       /* Bold White */

typedef cv::Mat Matrice; 
typedef std::string string; 

#define displayImage(title, path) {cv::imshow(title, path);};
#define print(x) {std::cout<<x<<"\n";};
#define exception(code, message){ std::cerr << BOLDRED << "ERROR : " << RESET << RED << code << " - " << message << RESET << "\n"; exit(code);}


using circle = std::vector<size_t>; 

/**
 * @brief Convert a image to a matrix
 * 
 * @param filePath 
 * @return Matrice 
 */
Matrice fileToMatrice(std::string filePath){
    Matrice image = cv::imread(filePath);

    if (image.empty())
       exception(1, "Could not open or find the image");
    
    return image;
}

/**
 * @brief Apply an Gaussian Filter to an image matrix using cv::GaussianBlur function
 * 
 * @param image 
 */
void gaussianFilter(Matrice& image){
    print(BOLD << "Gaussian Filter..." << RESET);
    
    try {
        Matrice image_blurred_with_5x5_kernel;
        cv::GaussianBlur(image, image_blurred_with_5x5_kernel, cv::Size(5, 5), 0);
        image = image_blurred_with_5x5_kernel;
    }
    catch(const std::exception& e) {   
        exception(2, "gaussianFilter : " + (string)e.what());
    }  

    print(GREEN << "Done successfully\n" << RESET);
}

/**
 * @brief Apply a Sobel Filter to a image matrix
 * 
 * @param image 
 */
void sobelFilter(Matrice& image){
    Matrice image_with_sobel_filter;

    Matrice sx, sy;
    cv::Sobel(image, sx, CV_64F, 1, 0);
    cv::Sobel(image, sy, CV_64F, 0, 1);

    displayImage("filtre de sobel sx", sx); 
    displayImage("filtre de sobel sy", sy);

    cv::sqrt(sx.mul(sx) + sy.mul(sy), image_with_sobel_filter);
    displayImage("Delta I avec sobel", image_with_sobel_filter); 

    image = image_with_sobel_filter;
}

/**
 * @brief Do a convolution product between a matrix and a kernel
 * 
 * @param matrice 
 * @param kernel 
 * @return Matrice 
 */
Matrice convolute(Matrice matrice, Matrice kernel){
    Matrice convoluteMatrice = cv::Mat(3,3, CV_64F, 0.0); 

    for (size_t i = 0; i < matrice.rows; i++)
    {
        for (size_t j = 0; j < matrice.cols; j++)
        {
        
            double sumHx = 0.0, sumHy = 0.0; 
            
            for (size_t ii = std::max(0, (int)i-1); ii <= std::min(matrice.rows-1, (int)i+1); ii++)
            {
                for (size_t jj = std::max(0,(int)j-1); jj <= std::min(matrice.cols, (int)j+1); jj++)
                {
                    convoluteMatrice += matrice.at<size_t>(ii,jj) * kernel.at<size_t>(i-ii +1, j-jj+1); 
                }
            }
        }
    }

    return convoluteMatrice;
}

/**
 * @brief Make a cercle detection using Hough Circle Transform OpenCV function
 * 
 * @param image 
 */
void houghCircleDetectionWithLib(Matrice& image) {
    print(BOLD << "Hough Circle Detection using OpenCV lib..." << RESET);

    Matrice grayImage;
    try
    {
        cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    }
    catch(const std::exception& e)
    {
        exception(4, "gray image convertion problem : " + (string)e.what());
    }
    
    Matrice bluredImage; 
    try
    {
        cv::medianBlur(grayImage, bluredImage, 5);
    }
    catch(const std::exception& e)
    {
        exception(4, "reduction noise problem : " + (string)e.what());
    }
    
    
    std::vector<cv::Vec3f>  circles;
    try
    {
        cv::HoughCircles(bluredImage, circles, cv::HOUGH_GRADIENT, 1, bluredImage.rows/26, 100, 30, 30, 70);

        print(" Circle found by Hough Transform : " << circles.size());

        for(size_t i=0; i<circles.size(); i++) {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            cv::circle(image, center, radius, cv::Scalar(0,255,0), 3, cv::LINE_AA);
        }
    }
    catch(const std::exception& e)
    {
        exception(4, "Hough Circle Detection problem : " + (string)e.what());
    }
    
    displayImage("Hough Cercle Detection with OpenCV function", image);
    print(GREEN << "Done successfully\n" << RESET);
}

/**
 * @brief Make a cercle dectection by implementing an Hough Circle Detection Transform algorithm
 * 
 * @param image 
 */
void houghCircleDetectionImpl(Matrice& image){
    print(BOLD << "Hough Circle Detection using our own implementation..." << RESET);

    // Gray Image Convertion
    Matrice imageGray;  
    try {
        cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
        displayImage("Image gray", imageGray);
        print(" Gray image convertion" << GREEN << " done" << RESET);
    }
    catch(const std::exception& e) {
        exception(4, "gray image convertion problem " + (string)e.what());
    }
    

    // Kernel Hx
    Matrice Hx = (cv::Mat_<double>(3,3) <<  -1, 0, 1, 
                                            -2, 0, 2, 
                                            -1, 0, 1);

    // Kernel Hy
    Matrice Hy = (cv::Mat_<double>(3,3) <<  -1, -2, -1, 
                                             0,  0,  0, 
                                             1,  2,  1);


    // Calcul du Produit de Convolution 
    Matrice i, j, in, jn, i2, j2;
    try {
        cv::filter2D(imageGray, i, -1, Hx);
        cv::filter2D(imageGray, j, -1, Hy);

        cv::filter2D(imageGray, in, -1, -Hx);
        cv::filter2D(imageGray, jn, -1, -Hy);

        cv::filter2D(imageGray, i2, CV_64FC1, Hx);
        cv::filter2D(imageGray, j2, CV_64FC1, Hy);
        print(" Convolution product" << GREEN << " done" << RESET);
    }
    catch(const std::exception& e){
        exception(5, "convolution matrix problem " + (string)e.what());
    }
    
    
    // Calcul Magnitude du Gradient - Methode A 
    Matrice magnitudeGradientA; 
    try {
        magnitudeGradientA = i+j+in+jn;
        displayImage("Magnitude du gradient de I - Methode A", magnitudeGradientA);
        print(" Gradient Magnitud Calcul with A method" << GREEN << " done" << RESET);
    }
    catch(const std::exception& e){
        exception(6, "gradient magnitud calcul met.A problem " + (string)e.what());
    }
    
    // Calcul Magnitude du Gradient - Methode B
    Matrice magnitudeGradientB;
    try {
        cv::magnitude(i2, j2, magnitudeGradientB);
        displayImage("Magnitude du gradient de I - Methode B", magnitudeGradientB);
        print(" Gradient Magnitud Calcul with B method" << GREEN << " done" << RESET);
    }
    catch(const std::exception& e) {
        exception(7, "Gradient Magnitud Calcul with B method problem \n" + (string)e.what());
    }
    
    // Maximum Magnitud determination
    double minVal; 
    double maxVal; 
    cv::Point minLoc; 
    cv::Point maxLoc;
    double t;
    try {
        cv::minMaxLoc(magnitudeGradientA, &minVal, &maxVal, &minLoc, &maxLoc); 
        t = maxVal;
        print(" Maximum Magnitude du Gradient : " << BOLD << "t = " << t << RESET);
    }
    catch(const std::exception& e){
        exception(8, "Maximum gradient magnitud determination problem " + (string)e.what());
    }
    

    
    // Creating Accumulator 3D Matrix
    int deltar = 1, rmin = 0, rmax = image.rows;
    int deltac = 1, cmin = 0, cmax = image.cols;
    int radmax = 90;
    int radmin = 4;
    int deltaRad = 1;

    int size[] {rmax, cmax, radmax - radmin};
    Matrice acc = cv::Mat::zeros(3, size, cv::COLOR_BGR2GRAY);

    print(" Accumulator 3D Matrix creation & zero initialization" << GREEN << " done" << RESET
        << "\n Accumulator 3D Matrix Size :" << BOLD << " size = " << acc.size << RESET);
    

    // Edges pixel selection
    Matrice edges;
    magnitudeGradientA.copyTo(edges);

    for (size_t ir = 0; ir < edges.rows; ir++)
    {
        for (size_t jc = 0; jc < edges.cols; jc++)
        {
            if (edges.at<uchar>(ir,jc) >= t){
                edges.at<uchar>(ir,jc) = 255; 
            }
            else{
                edges.at<uchar>(ir,jc) = 0;  
            }
        }
    }
    displayImage("Edges", edges);
    print(" Edges pixel selection" << GREEN << " done" << RESET);


    // All possible circles vote
    int c = 0;
    double bgrPixel;
    double a, b, h;
    t = 0.5 * t; 

    if (edges.rows != image.rows && edges.cols != edges.cols)
        exception(8, "MERDE");

    for (int i = 0; i < edges.rows; i++)
    {
        for (int j = 0; j < edges.cols; j++)
        {
            int bgrPixel = edges.at<uchar>(i, j);
            if ((int)bgrPixel >= (int)t ){
                for (int k = 0; k < acc.size[0]; k++)
                {
                    for (int l = 0; l < acc.size[1]; l++)
                    {
                        a = std::abs((i * deltar + rmin) - (k * deltar + rmin));
                        b = std::abs((j * deltac + cmin) - (l * deltac + cmin));
                        h = sqrt(a * a + b * b);
                        
                        if (radmin < h && h < radmax) {
                            acc.at<double>(k,l,(int)(h / deltaRad - radmin)) += 1.0 / h;  
                        }        
                    }
                }
            }
        }
    }
    print(" The Best Candidate Cercle vote into accumulator 3D Matrix" << GREEN << " done" << RESET);


    // Local maximum determination 
    int findSize = 26; 
    int weight = 4.5; 
    using circle = std::vector<size_t>; 
    std::vector<circle> circles; 
    int count = 0; 

    for (size_t i = 0; i < acc.size[0]; i++)
    {
        for (size_t j = 0; j < acc.size[1]; j++)
        {
            for (size_t k = 0; k < acc.size[2]; k++)
            {
                bool isMax = true;
                for (size_t ii = i - 1 ; ii <= i + 1; ii++)
                {
                    for (size_t jj = j - 1; jj <= j + 1; jj++)
                    {
                        for (size_t kk = k - 1; kk <= k + 1; kk++)
                        {
                            if((ii != i || jj != j || kk != k) 
                            && (ii > 0 && ii < acc.size[0]) 
                            && (jj > 0 && jj < acc.size[1]) 
                            && (kk > 0 && kk < acc.size[2])){
                                if (acc.at<double>(ii,jj,kk) > acc.at<double>(i,j,k)){
                                    isMax = false;
                                    break;
                                }
                            }
                            if (isMax == false) break; 
                        }
                        if (isMax == false) break; 
                    }
                    if (isMax == false) break; 
                }
                if (isMax) count++;

                if(isMax && acc.at<double>(i,j,k) > weight){
                    circles.push_back({i,j,k,(std::size_t)acc.at<double>(i,j,k)});
                }
                
            }
            
        }
        
    }

    print(" Local maximum determination into accumulator" << RED << " N.A" << RESET);
    print(" " << BOLD << circles.size() << " circles finded & " << count << " local maxima finded " << RESET);


    // Hough Circle determination & draw
    for (auto e:circles){
        cv::Point center(cvRound((double)e[1]), cvRound((double)e[0]));
        int radius = cvRound((double)e[2]);
        cv::circle(image, center, radius, cv::Scalar(0,255,0), 3, cv::LINE_AA);
    }
    
    displayImage("Final", image);
    print(" Hough Circle determination & draw" << RED << " N.A" << RESET);


    print(RED << "Not done !" << RESET);
}

int main(int argc, char* argv[])
{
    print(BOLD << DIV << "TI - TP2 : Circle Detection by Hough Transform" << DIV << "\n" << RESET
                      << " Julien SAVE & Alexis DA COSTA\n"
                      << " APP5 Info - Polytech Paris-Saclay ©\n");
    
    if (argc != 2)
        exception(0, "Argument missing : image to analyse path");

    print("Image to analyse : " << UNDER << BOLD << argv[1] << RESET);

    Matrice image = fileToMatrice(argv[1]);
    print(" size = [" << image.rows << ", " << image.cols << "]\n" );
    displayImage("Image brut", image);

    gaussianFilter(image); 

    Matrice imgWithLib, imgWithoutLib;
    image.copyTo(imgWithLib);
    image.copyTo(imgWithoutLib); 

    houghCircleDetectionWithLib(imgWithLib);
    houghCircleDetectionImpl(imgWithoutLib);

    cv::waitKey(0);

    return 0;
}