#include "OpenCV.h"

class Rect: public Nan::ObjectWrap {
public:
  CvRect rect;
  static Nan::Persistent<FunctionTemplate> constructor;
  static void Init(Local<Object> target);
  static NAN_METHOD(New);
  Rect(double x, double y, double width, double height);

  static NAN_GETTER(GetX);
  static NAN_GETTER(GetY);
  static NAN_GETTER(GetWidth);
  static NAN_GETTER(GetHeight);
  static NAN_SETTER(RaiseImmutable);

};
