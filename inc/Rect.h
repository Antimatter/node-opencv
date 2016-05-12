#ifndef NODE_OPENCV_RECT_H
#define NODE_OPENCV_RECT_H
#include <opencv/cv.h>
#include <node_object_wrap.h>

namespace node_opencv {

class Rect: public Nan::ObjectWrap {
public:
  cv::Rect rect;
protected:
  Rect(): Nan::ObjectWrap() {};
};

}
#endif //NODE_OPENCV_RECT_H
