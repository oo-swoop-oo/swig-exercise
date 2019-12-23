{
  "targets": [
    {
      "target_name": "exercise",
      "sources": [ "src/exercise.cpp", "exercise_wrap.cxx", "lib/cJSON.c" ],
      "include_dirs": [ "/usr/include/nodejs/src", "/usr/include/nodejs/deps/v8/include", "/usr/include/x86_64-linux-gnu" ],
      "libraries": [ "-lcurl" ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ]
    }
  ]
}
