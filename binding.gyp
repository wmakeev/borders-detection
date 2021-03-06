{
  "targets": [
    {
      "target_name": "borders-detection",
      "sources": [
        "src/init.cpp",
        "src/pixels_groups.cpp",
        "src/image.cpp",
        "src/read_pixels.cpp"
      ],
      "include_dirs" : [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/usr/include",
        "/usr/local/include"
      ],
      "conditions": [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      'defines': [ 'NAPI_CPP_EXCEPTIONS' ]
    }
  ]
}
