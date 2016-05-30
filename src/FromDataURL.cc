#include "OpenCV.h"
#include "Matrix.h"
#include "modp_b64/modp_b64.h"
#include <nan.h>

NAN_METHOD(OpenCV::FromDataURL) {
  Nan::EscapableHandleScope scope;

  REQ_FUN_ARG(1, cb);

  Local<Value> argv[2];
  argv[0] = Nan::Null();

  Local<Object> im_h = Nan::New(Matrix::constructor)->GetFunction()->NewInstance();
  Matrix *img = Nan::ObjectWrap::Unwrap<Matrix>(im_h);
  argv[1] = im_h;

  try {
    cv::Mat mat;

    std::string src = std::string(*Nan::Utf8String(info[0]->ToString()));
    size_t pos = src.find_first_of(',');
    std::string b64s = src.substr(pos+1);

    const char* b64string = b64s.c_str();
    size_t sourcelen = strlen(b64string);
    char* dest = (char*) malloc(modp_b64_decode_len(sourcelen));
    int len = modp_b64_decode(dest, b64string, sourcelen);

    cv::Mat *mbuf = new cv::Mat(len, 1, CV_64FC1, dest);
    mat = cv::imdecode(*mbuf, CV_LOAD_IMAGE_UNCHANGED);

    free(dest);
    img->mat = mat;	
  } catch (cv::Exception& e) {
    argv[0] = Nan::Error(e.what());
    argv[1] = Nan::Null();
  }

  Nan::TryCatch try_catch;
  //cb->Call(Nan::GetCurrentContext()->Global(), 2, argv);
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 2, argv);

  if (try_catch.HasCaught()) {
    Nan::FatalException(try_catch);
  }

  return;
}

NAN_METHOD(OpenCV::EncPngDataURL) {	
  Nan::EscapableHandleScope scope;

  REQ_FUN_ARG(1, cb);
  
  Matrix *_input = Nan::ObjectWrap::Unwrap<Matrix>(info[0]->ToObject());

  Local<Value> argv[2];
  argv[0] = Nan::Null();
  
  std::string dataUrl("data:image/png;base64,");

  try {
	  std::vector<uchar> buf;
	  cv::imencode(".png", _input->mat, buf);
	  std::string png(buf.begin(), buf.end());	  
	  std::string b64 = modp_b64_encode(png);
	  
	  argv[1] = Nan::New<v8::String>(dataUrl + b64).ToLocalChecked();

  } catch (cv::Exception& e) {
    argv[0] = Nan::Error(e.what());
    argv[1] = Nan::Null();
  }

  Nan::TryCatch try_catch;
  cb->Call(Nan::GetCurrentContext()->Global(), 2, argv);

  if (try_catch.HasCaught()) {
    Nan::FatalException(try_catch);
  }

  return;
}

NAN_METHOD(OpenCV::EncDataURL){
 Nan::EscapableHandleScope scope;

 Matrix *_input = Nan::ObjectWrap::Unwrap<Matrix>(info[0]->ToObject());

 std::string dataUrl("data:image/png;base64,");

 try {
 	  std::vector<uchar> buf;
 	  cv::imencode(".png", _input->mat, buf);
 	  std::string png(buf.begin(), buf.end());
 	  std::string b64 = modp_b64_encode(png);

      info.GetReturnValue().Set(Nan::New<v8::String>(dataUrl + b64).ToLocalChecked());
 } catch (cv::Exception& e) {
     const char *err_msg = e.what();
     info.GetReturnValue().Set(Nan::New(err_msg).ToLocalChecked());
     return;
 }

}
