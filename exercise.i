%module exercise
%{
#include "src/exercise.h"
extern post_type* get_post_details(int post_id);
extern int get_request_timing(int user_id);
%}

%include "std_string.i"
%include "src/exercise.h"
extern post_type* get_post_details(int post_id);
extern int get_request_timing(int user_id);
