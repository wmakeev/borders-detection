#include <napi.h>
#include <stdexcept>
#include <iostream>
#include <string>

#include "detect_borders.hpp"

Napi::Array get_napi_borders_array(Napi::Env &env, std::list<PixelsGroup> *pixels_groups)
{
  // groups array
  const int borders_count = pixels_groups->size();
  Napi::Array borders_array = Napi::Array::New(env, borders_count);

  int border_index = 0;
  for (auto g_it = pixels_groups->begin(); g_it != pixels_groups->end(); g_it++)
  {
    Napi::Object group_object = Napi::Object::New(env);

    // .border{}
    Napi::Object border_object = Napi::Object::New(env);

    border_object.Set(
        Napi::String::New(env, "x"),
        Napi::Number::New(env, g_it->border.x));

    border_object.Set(
        Napi::String::New(env, "y"),
        Napi::Number::New(env, g_it->border.y));

    border_object.Set(
        Napi::String::New(env, "width"),
        Napi::Number::New(env, g_it->border.width));

    border_object.Set(
        Napi::String::New(env, "height"),
        Napi::Number::New(env, g_it->border.height));

    group_object.Set(Napi::String::New(env, "border"), border_object);

    // .pixels[]
    Napi::Array pixels_array = Napi::Array::New(env, g_it->pixels.size());
    int pixel_index = 0;
    for (auto p_it = g_it->pixels.begin(); p_it != g_it->pixels.end(); p_it++)
    {
      // pixel
      Napi::Object pixel_array = Napi::Array::New(env, 2);
      pixel_array.Set((uint32_t)0, Napi::Number::New(env, p_it->x));
      pixel_array.Set((uint32_t)1, Napi::Number::New(env, p_it->y));
      pixels_array.Set(pixel_index, pixel_array);
      pixel_index++;
    }

    group_object.Set(Napi::String::New(env, "pixels"), pixels_array);

    // add group object
    borders_array.Set(border_index, group_object);

    border_index++;
  }

  return borders_array;
}

class DetectBordersAsyncWorker : public Napi::AsyncWorker
{
public:
  DetectBordersAsyncWorker(
      const Napi::Function &callback,
      std::string filename,
      const unsigned int min_gap) : Napi::AsyncWorker(callback), filename(filename), min_gap(min_gap)
  {
  }

protected:
  void Execute() override
  {
    pixels_groups = detect_borders(filename.c_str(), min_gap);
  }

  void OnOK() override
  {
    Napi::Env env = Env();

    Callback().MakeCallback(Receiver().Value(),
                            {env.Null(), get_napi_borders_array(env, pixels_groups)});
  }

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();

    Callback().MakeCallback(Receiver().Value(),
                            {e.Value(), env.Undefined()});
  }

private:
  std::string filename;
  unsigned int min_gap;
  std::list<PixelsGroup> *pixels_groups;
};

Napi::Value detect_borders_sync(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  const char *filename = info[0].As<Napi::String>().Utf8Value().c_str();
  unsigned int min_gap = 10; // default gap
  Napi::Object options_object;

  // parse options object
  if (info.Length() == 2)
  {
    if (!info[1].IsObject())
    {
      Napi::TypeError::New(env, "Options agrument expected to be object")
          .ThrowAsJavaScriptException();
      return env.Null();
    }

    options_object = info[1].As<Napi::Object>();

    if (options_object.Has("minGap"))
    {
      min_gap = options_object.Get("minGap").ToNumber().Uint32Value();
    }
  }

  std::list<PixelsGroup> *pixels_groups;
  try
  {
    pixels_groups = detect_borders(filename, min_gap);
  }
  catch (const std::exception &e)
  {
    Napi::TypeError::New(env, e.what()).ThrowAsJavaScriptException();
    return env.Null();
  }

  // groups array
  Napi::Array borders_array = get_napi_borders_array(env, pixels_groups);

  return borders_array;
}

Napi::Value detect_borders_async(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object options_object;
  Napi::Function cb;
  std::string filename;
  unsigned int cb_arg_index = 1;
  unsigned int min_gap = 10; // default gap

  // Parse arguments
  if (info.Length() < 2)
  {
    Napi::TypeError::New(env, "Invalid argument count").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Invalid filename argument").ThrowAsJavaScriptException();
    return env.Null();
  }
  filename = info[0].As<Napi::String>().Utf8Value();

  if (info[cb_arg_index].IsObject())
  {
    cb_arg_index++;
    options_object = info[1].As<Napi::Object>();

    if (options_object.Has("minGap"))
    {
      min_gap = options_object.Get("minGap").ToNumber().Uint32Value();
    }
  }

  if (info.Length() != cb_arg_index + 1 || !info[cb_arg_index].IsFunction())
  {
    Napi::TypeError::New(env, "Callback argument expected").ThrowAsJavaScriptException();
    return env.Null();
  }
  cb = info[cb_arg_index].As<Napi::Function>();

  (new DetectBordersAsyncWorker(cb, filename, min_gap))->Queue();

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
      Napi::String::New(env, "detectBordersSync"),
      Napi::Function::New(env, detect_borders_sync));

  exports.Set(
      Napi::String::New(env, "detectBorders"),
      Napi::Function::New(env, detect_borders_async));

  return exports;
};

NODE_API_MODULE(init, Init);
