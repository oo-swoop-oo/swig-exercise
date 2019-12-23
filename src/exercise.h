#ifndef _EXERCISE_H_
#define _EXERCISE_H_

#include <string>

using namespace std;

struct response_type
{
    string body;
};

struct post_type
{
    int user_id;
    char *title;
};

#endif // _EXERCISE_H_
