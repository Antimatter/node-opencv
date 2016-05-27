#include "ImgProc.h"
#include "Matrix.h"
#include "Rect.h"

// cv::grabCut( InputArray _img, InputOutputArray _mask, Rect rect,
//                  InputOutputArray _bgdModel, InputOutputArray _fgdModel,
//                  int iterCount, int mode )
// cv::grabCut
NAN_METHOD(ImgProc::GrabCut) {
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Object> objReturn = Nan::New<v8::Object>();
  try {
    // Arg 0 is the image
    Matrix* m0 = Nan::ObjectWrap::Unwrap<Matrix>(info[0]->ToObject());
    cv::Mat _img = m0->mat;
	if (m0->mat.type() == CV_8UC1)
	{
		const int channels = 3;
		cv::Mat vChannels[channels] = { m0->mat, m0->mat, m0->mat };
		_img.release();
		_img.create(m0->mat.size(), CV_8UC3);
		cv::merge(vChannels, channels, _img);
	}


    // Arg 1 is the _mask matrix
    Matrix* m1 = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject());
    cv::Mat _mask;
    m1->mat.copyTo(_mask);

    // Arg 2 is the rect
    Rect* m2 = Nan::ObjectWrap::Unwrap<Rect>(info[2]->ToObject());
    cv::Rect rect = m2->rect;

    // Arg 3 is the _bgdModel
    Matrix* m3 = Nan::ObjectWrap::Unwrap<Matrix>(info[3]->ToObject());
    cv::Mat _bgdModel;
    m3->mat.copyTo(_bgdModel);

    // Arg 4 is the _fgdModel
    Matrix* m4 = Nan::ObjectWrap::Unwrap<Matrix>(info[4]->ToObject());
    cv::Mat _fgdModel;
    m4->mat.copyTo(_fgdModel);

    // Arg 5 is the iterCount
    int iterCount = info[5]->IntegerValue();

    // Arg 6 is the mode
    int mode = info[6]->IntegerValue();

    //printf("\tinput image: %d %d\n", _img.cols, _img.rows);
    //printf("\tinput rect: %d %d %d %d\n", rect.x, rect.y, rect.width, rect.height);
    //printf("iterCount: %d, mode: %d\n", iterCount, mode);

    //GrabCut
    cv::grabCut(_img, _mask, rect, _bgdModel, _fgdModel, iterCount, mode);

    Local<Object> _maskOut = Nan::New(Matrix::constructor)->GetFunction()->NewInstance();
    Matrix *_maskMat = Nan::ObjectWrap::Unwrap<Matrix>(_maskOut);
    _maskMat->mat = _mask;

    Local<Object> _bgdModelOut = Nan::New(Matrix::constructor)->GetFunction()->NewInstance();
    Matrix *_bgdModelMat = Nan::ObjectWrap::Unwrap<Matrix>(_bgdModelOut);
    _bgdModelMat->mat = _bgdModel;

    Local<Object> _fgdModelOut = Nan::New(Matrix::constructor)->GetFunction()->NewInstance();
    Matrix *_fgdModelMat = Nan::ObjectWrap::Unwrap<Matrix>(_fgdModelOut);
    _fgdModelMat->mat = _fgdModel;


    Local<v8::Array> _rect = Nan::New<v8::Array>(4);
    _rect->Set(0, Nan::New(rect.x));
    _rect->Set(1, Nan::New(rect.y));
    _rect->Set(2, Nan::New(rect.width));
    _rect->Set(3, Nan::New(rect.height));
    objReturn->Set(Nan::New("rect").ToLocalChecked(), _rect);

    objReturn->Set(Nan::New("_mask").ToLocalChecked(),     _maskOut);
    objReturn->Set(Nan::New("_bgdModel").ToLocalChecked(), _bgdModelOut);
    objReturn->Set(Nan::New("_fgdModel").ToLocalChecked(), _fgdModelOut);

    info.GetReturnValue().Set(objReturn);
  } catch (cv::Exception &e) {
    const char *err_msg = e.what();
    objReturn->Set(Nan::New("error").ToLocalChecked(), Nan::New(err_msg).ToLocalChecked());
    info.GetReturnValue().Set(objReturn);
    return;
  }
}
