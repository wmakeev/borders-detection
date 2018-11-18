#include <napi.h>
#include <stdexcept>
#include <iostream>
#include <string>

#include "pixels_groups.hpp"

Napi::Object get_napi_groups_array(Napi::Env &env, std::list<PixelsGroup> *pixels_groups,
                                    LONG &width, LONG &height)
{
  // groups array
  Napi::Array groups_array = Napi::Array::New(env, pixels_groups->size());
  Napi::Object result_object = Napi::Object::New(env);

  // image info
  result_object.Set(
      Napi::String::New(env, "imgWidth"),
      Napi::Number::New(env, width));

  result_object.Set(
      Napi::String::New(env, "imgHeight"),
      Napi::Number::New(env, height));

  int bound_index = 0;
  for (auto g_it = pixels_groups->begin(); g_it != pixels_groups->end(); g_it++)
  {
    // Napi::Object group_object = Napi::Object::New(env);

    // .bound{}
    Napi::Object group_object = Napi::Object::New(env);

    group_object.Set(
        Napi::String::New(env, "minX"),
        Napi::Number::New(env, (double)(g_it->bound.min_x) / width));

    group_object.Set(
        Napi::String::New(env, "minY"),
        Napi::Number::New(env, (double)(g_it->bound.min_y) / height));

    group_object.Set(
        Napi::String::New(env, "maxX"),
        Napi::Number::New(env, (double)(g_it->bound.max_x) / width));

    group_object.Set(
        Napi::String::New(env, "maxY"),
        Napi::Number::New(env, (double)(g_it->bound.max_y) / height));

    group_object.Set(
        Napi::String::New(env, "pixelsCount"),
        Napi::Number::New(env, g_it->pixels.size()));

    // add bound object
    groups_array.Set(bound_index, group_object);

    bound_index++;
  }

  result_object.Set(Napi::String::New(env, "groups"), groups_array);

  return result_object;
}

class DetectBordersAsyncWorker : public Napi::AsyncWorker
{
public:
  DetectBordersAsyncWorker(
      const Napi::Function &callback,
      std::string filename,
      const double max_gap_perc) : Napi::AsyncWorker(callback), filename(filename), max_gap_perc(max_gap_perc)
  {
  }

protected:
  void Execute() override
  {
    pixels_groups = get_pixels_groups(filename.c_str(), max_gap_perc, width, height);
  }

  void OnOK() override
  {
    Napi::Env env = Env();

    Callback().MakeCallback(
        Receiver().Value(),
        {env.Null(), get_napi_groups_array(env, pixels_groups, width, height)});
  }

  void OnError(const Napi::Error &e) override
  {
    Napi::Env env = Env();

    Callback().MakeCallback(Receiver().Value(),
                            {e.Value(), env.Undefined()});
  }

private:
  std::string filename;
  double max_gap_perc;
  LONG width, height;
  std::list<PixelsGroup> *pixels_groups;
};

Napi::Value detect_groups_async(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::Object options_object;
  Napi::Function cb;
  std::string filename;
  unsigned int cb_arg_index = 1;
  double max_gap_perc = 0.01; // default gap

  // Parse arguments
  if (info.Length() < 2)
  {
    Napi::TypeError::New(env, "Invalid argument count")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Invalid filename argument")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  filename = info[0].As<Napi::String>().Utf8Value();

  if (info[cb_arg_index].IsObject())
  {
    cb_arg_index++;
    options_object = info[1].As<Napi::Object>();

    if (options_object.Has("maxGap"))
    {
      if (!options_object.Get("maxGap").IsNumber())
      {
        Napi::TypeError::New(env, "Invalid maxGap option value")
            .ThrowAsJavaScriptException();
        return env.Null();
      }
      max_gap_perc = options_object.Get("maxGap").ToNumber().DoubleValue();
    }
  }

  if (info.Length() != cb_arg_index + 1 || !info[cb_arg_index].IsFunction())
  {
    Napi::TypeError::New(env, "Callback argument expected")
        .ThrowAsJavaScriptException();
    return env.Null();
  }
  cb = info[cb_arg_index].As<Napi::Function>();

  (new DetectBordersAsyncWorker(cb, filename, max_gap_perc))->Queue();

  return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
      Napi::String::New(env, "pixelsGroups"),
      Napi::Function::New(env, detect_groups_async));

  return exports;
};

NODE_API_MODULE(init, Init);
