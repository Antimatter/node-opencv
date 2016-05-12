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
  Local<ObjectTemplate> proto = ctor->PrototypeTemplate();
  Nan::SetAccessor(proto, Nan::New("x").ToLocalChecked(), GetX, RaiseImmutable);
  Nan::SetAccessor(proto, Nan::New("y").ToLocalChecked(), GetY, RaiseImmutable);
  Nan::SetAccessor(proto, Nan::New("width").ToLocalChecked(), GetWidth, RaiseImmutable);
  Nan::SetAccessor(proto, Nan::New("height").ToLocalChecked(), GetHeight, RaiseImmutable);

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
  Rect *pt = new Rect(x, y, width, height);
  pt->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_GETTER(Rect::GetX) {
  Nan::HandleScope scope;
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.x));
}

NAN_GETTER(Rect::GetY) {
  Nan::HandleScope scope;
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.y));
}

NAN_GETTER(Rect::GetWidth) {
  Nan::HandleScope scope;
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.width));
}

NAN_GETTER(Rect::GetHeight) {
  Nan::HandleScope scope;
  Rect *rect = Nan::ObjectWrap::Unwrap<Rect>(info.This());
  info.GetReturnValue().Set(Nan::New<Number>(rect->rect.height));
}

NAN_SETTER(Rect::RaiseImmutable) {
  Nan::ThrowTypeError("Rect is immutable");
}


Rect::Rect(double x, double y, double width, double height) :
    Nan::ObjectWrap() {
  rect = cv::Rect((int)x, (int)y, (int)width, (int)height);
}
