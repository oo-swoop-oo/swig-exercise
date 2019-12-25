package com.domain.main;

import com.domain.exercise.*;

public class main {
    static {
        System.loadLibrary("exercise");
    }

    public static void main(String argv[]) {
        int postId = 1;
        post_type post = exercise.get_post_details(postId);
        System.out.println("user id: " + post.getUser_id());
        System.out.println("title: " + post.getTitle());

        int userId = 10;
        int timing = exercise.get_request_timing(userId);
        System.out.println("timing: " + timing + " ms");
    }
}
