%module exercise
%{
#include "src/exercise.h"
extern response_type* get_request(const char *url);
%}

%include "std_string.i"
%include "src/exercise.h"
extern response_type* get_request(const char *url);
