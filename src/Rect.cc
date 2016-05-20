#include "Rect.h"
#include "OpenCV.h"

Nan::Persistent<FunctionTemplate> Rect::constructor;

void Rect::Init(Local<Object> target) {
  Nan::HandleScope scope;

  // Constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(Rect::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Rect").ToLocalChecked());

  // Prototype
  Local<ObjectTemplate> instance = ctor->InstanceTemplate();
  Nan::SetAccessor(instance, Nan::New("x").ToLocalChecked(), GetX, RaiseImmutable);
  Nan::SetAccessor(instance, Nan::New("y").ToLocalChecked(), GetY, RaiseImmutable);
  Nan::SetAccessor(instance, Nan::New("width").ToLocalChecked(), GetWidth, RaiseImmutable);
  Nan::SetAccessor(instance, Nan::New("height").ToLocalChecked(), GetHeight, RaiseImmutable);

  target->Set(Nan::New("Rect").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Rect::New) {
  Nan::HandleScope scope;

  if (info.This()->InternalFieldCount() == 0) {
    return Nan::ThrowTypeError("Cannot Instantiate without new");
  }

  double x = 0, y = 0, width = 0, height = 0;
  if (info[0]->IsNumber()) {
    x = info[0]->NumberValue();
  }
  if (info[1]->IsNumber()) {
    y = info[1]->NumberValue();
  }
  if (info[2]->IsNumber()) {
    width = info[2]->NumberValue();
  }
  if (info[3]->IsNumber()) {
    height = info[3]->NumberValue();
  }
  Rect *rect = new Rect(x, y, width, height);
  rect->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_GETTER(Rect::GetX) {
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.Holder());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.x));
}

NAN_GETTER(Rect::GetY) {
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.Holder());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.y));
}

NAN_GETTER(Rect::GetWidth) {
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.Holder());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.width));
}

NAN_GETTER(Rect::GetHeight) {
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.Holder());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.height));
}

NAN_SETTER(Rect::RaiseImmutable) {
  Nan::ThrowTypeError("Rect is immutable");
}

Rect::Rect(double x, double y, double width, double height) :
    node_opencv::Rect() {
  rect = cv::Rect((int)x, (int)y, (int)width, (int)height);
}
