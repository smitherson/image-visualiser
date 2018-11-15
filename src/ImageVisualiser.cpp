#include "ImageVisualiser.h"


using namespace std;
using namespace cv;

ImageVisualiser::ImageVisualiser(const String windowName, Mat image): windowName(windowName) {
    this->image = image.clone();
    imshow(windowName,image);
    setMouseCallback(windowName, onMouseHack, this);
    originalSize = Size(image.cols,image.rows);
    currentRect = Rect(0,0,image.cols,image.rows);
    zoomedImage = image.clone();
    imshow(windowName, image);           
}
void ImageVisualiser::setLeftClickHandler( LeftClickCallbackType callback) {
    leftClickCallback = callback;
}


void ImageVisualiser::onMouseHack(int event, int x, int y, int flags, void* userdata) {
    ImageVisualiser* object = (ImageVisualiser*)userdata;
    object->onMouse(event, x, y, flags);
}

void ImageVisualiser::redraw(RedrawLambda callback) {
    callback(image);
    resize(image, zoomedImage, Size(originalSize.width*currentZoom, originalSize.height*currentZoom), 0,0, INTER_NEAREST);
    redrawImage();
}
void ImageVisualiser::redrawImage() {
    if (currentRect.x < 0) currentRect.x = 0;
    if (currentRect.y < 0) currentRect.y = 0;
    int zoomedWidth, zoomedHeight;

    if (currentUpdatedZoom != 0) {
        zoomedWidth = originalSize.width*currentUpdatedZoom;
        zoomedHeight = originalSize.height*currentUpdatedZoom;
    } else {
        zoomedWidth = originalSize.width*currentZoom;
        zoomedHeight = originalSize.height*currentZoom;
    }
   
    if (currentRect.x + originalSize.width > zoomedWidth) currentRect.x = currentRect.x - (originalSize.width - (zoomedWidth-currentRect.x));
    if (currentRect.y + originalSize.height > zoomedHeight) currentRect.y = currentRect.y - (originalSize.height- (zoomedHeight-currentRect.y));
    //if (zoom > 1) {
    imshow(windowName, zoomedImage(currentRect)); 
    //} else {
    //    imshow(windowName, image);           
    //}

}

void ImageVisualiser::onMouse(int event, int col, int row, int flags)
{

 //getWindowProperty() to de;ete?

    bool doRedraw = false;
    if (event == CV_EVENT_LBUTTONDOWN) {
        int properCol = (col + currentRect.x)/currentZoom;
        int properRow = (row + currentRect.y)/currentZoom;
        Mat imageClone = image.clone(); 
        if (leftClickCallback) {
            leftClickCallback(properRow, properCol, imageClone);
        }
        resize(imageClone, zoomedImage, Size(originalSize.width*currentZoom, originalSize.height*currentZoom), 0,0, INTER_NEAREST);
        doRedraw = true;
    }

    if(event == CV_EVENT_MBUTTONDOWN) {
        if (!middleButtonPressed) {
            middleButtonPressed = true;
            prevCol = col;
            prevRow = row;
        }
    }
    if (event == CV_EVENT_MBUTTONUP) {
        middleButtonPressed = false;
    }

    if (middleButtonPressed) {
        currentRect.x = currentRect.x + (prevCol-col);
        currentRect.y = currentRect.y + (prevRow-row);
        prevCol = col;
        prevRow = row;
        doRedraw = true;
    } 
     
    if(event == CV_EVENT_RBUTTONDOWN) {
        if (!rightButtonPressed) {
            buttonDownCol = col;
            buttonDownRow = row;
            zoomCenterCol = (col + currentRect.x)/currentZoom;
            zoomCenterRow = (row + currentRect.y)/currentZoom;
            rightButtonPressed = true;
        }
    }
  
    int width = originalSize.width;
    int height = originalSize.height;
    int zoomedWidth = width*currentZoom;
    int zoomedHeight = height*currentZoom;
         
    if (rightButtonPressed) {
        int delta = buttonDownRow - row;
        currentUpdatedZoom = currentZoom + delta/(float)100;
        if (currentUpdatedZoom > 1) {
            zoomedWidth = width*currentUpdatedZoom;
            zoomedHeight = height*currentUpdatedZoom;
            
            Size newSize = Size(zoomedWidth, zoomedHeight);
            resize(image, zoomedImage, newSize, 0,0, INTER_NEAREST);

            currentRect = Rect (zoomCenterCol*currentUpdatedZoom - width/2, zoomCenterRow*currentUpdatedZoom - height/2, width, height);
            doRedraw = true;

        } else {
             currentUpdatedZoom = 1; currentRect.x = 0; currentRect.y = 0;
             doRedraw = true; 
        }
    }
    
    if (event == CV_EVENT_RBUTTONUP) {
        rightButtonPressed = false;
        currentZoom = currentUpdatedZoom;
        currentUpdatedZoom = 0;
    }

    if (doRedraw) {
        redrawImage();         
    }
}
