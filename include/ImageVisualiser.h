#pragma once
#include <functional>
#include <opencv2/opencv.hpp>

using LeftClickCallbackType = std::function<void(int row, int col, cv::Mat& image)>;
using RedrawLambda = std::function<void(cv::Mat& image)>;

class ImageVisualiser {
    public:
        ImageVisualiser(const cv::String windowName, cv::Mat image);
        void setLeftClickHandler( LeftClickCallbackType callback);
        void redraw(RedrawLambda callback);
    private:
        void redrawImage();
        void static onMouseHack(int event, int x, int y, int flags, void* userdata);
        void onMouse(int event, int col, int row, int flags);
        const cv::String windowName;
        cv::Mat image;
        
        int rightButtonYDelta = 0;
        bool rightButtonPressed = false;

        int buttonDownRow, buttonDownCol;
        int  zoomCenterRow, zoomCenterCol;
        cv::Size originalSize;
        cv::Rect currentRect ;
        float currentZoom = 1, currentUpdatedZoom = 0;
        cv::Mat zoomedImage;

        bool middleButtonPressed = false;
        int prevRow, prevCol;
        LeftClickCallbackType leftClickCallback;
};
