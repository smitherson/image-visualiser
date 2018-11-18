#include <opencv2/opencv.hpp>
#include "ImageVisualiser.h"

int main() {

  cv::Mat_<cv::Vec3b> img1 = cv::imread("./example/test.png", CV_LOAD_IMAGE_COLOR);

  ImageVisualiser* imshow1 = new ImageVisualiser("image1 ", img1); 

  imshow1->setLeftClickHandler([ ](int row, int col, cv::Mat& img) {
      printf("clicked %d %d \n", row, col);
      img.at<cv::Vec3b>(row, col) = cv::Vec3b(80, 30, 200);
  });


  cv::waitKey(0);
  return 0;
}
