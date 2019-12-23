%module exercise
%{
#include "src/exercise.h"
extern post_type* get_post_details(int post_id);
%}

%include "std_string.i"
%include "src/exercise.h"
extern post_type* get_post_details(int post_id);
