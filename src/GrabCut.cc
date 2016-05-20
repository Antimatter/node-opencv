#include "ImgProc.h"
#include "Matrix.h"
#include "Rect.h"

// cv::grabCut( InputArray _img, InputOutputArray _mask, Rect rect,
//                  InputOutputArray _bgdModel, InputOutputArray _fgdModel,
//                  int iterCount, int mode )
// cv::grabCut
NAN_METHOD(ImgProc::grabCut) {
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Object> objReturn = Nan::New<v8::Object>();
  try {
    // Arg 0 is the image
    Matrix* m0 = Nan::ObjectWrap::Unwrap<Matrix>(info[0]->ToObject());
    cv::Mat _img = m0->mat;

    // Arg 1 is the _mask matrix
    Matrix* m1 = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject());
    cv::Mat _mask = m1->mat;

    // Arg 2 is the rect
    Rect* m2 = Nan::ObjectWrap::Unwrap<Rect>(info[2]->ToObject());
    cv::Rect rect = m2->rect;

    // Arg 3 is the _bgdModel
    Matrix* m3 = Nan::ObjectWrap::Unwrap<Matrix>(info[3]->ToObject());
    cv::Mat _bgdModel = m3->mat;

    // Arg 4 is the _fgdModel
    Matrix* m4 = Nan::ObjectWrap::Unwrap<Matrix>(info[4]->ToObject());
    cv::Mat _fgdModel = m4->mat;

    // Arg 5 is the iterCount
    int iterCount = (int)(info[5]->NumberValue());

    // Arg 6 is the mode
    int mode = (int) (info[6]->NumberValue());

    //GrabCut
    cv::grabCut(_img, _mask, rect, _bgdModel, _fgdModel, iterCount, mode);

    // Wrap the output image
    Local<Object> outMatrixWrap = Nan::New(Matrix::constructor)->GetFunction()->NewInstance();
    Matrix *outMatrix = Nan::ObjectWrap::Unwrap<Matrix>(outMatrixWrap);
    outMatrix->mat = _mask.clone();

    objReturn->Set(Nan::New("_mask").ToLocalChecked(), outMatrixWrap);
    objReturn->Set(Nan::New("imageType").ToLocalChecked(), Nan::New(_img.type()));

    info.GetReturnValue().Set(objReturn);
  } catch (cv::Exception &e) {
    const char *err_msg = e.what();
    objReturn->Set(Nan::New("error").ToLocalChecked(), Nan::New(err_msg).ToLocalChecked());
    info.GetReturnValue().Set(objReturn);
    return;
  }
}
