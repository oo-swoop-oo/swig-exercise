var Exercise = require('./exercise');

var main = () => {
    var postId = 1;
    var post = Exercise.get_post_details(postId);
    console.log(`user id: ${post['user_id']}`);
    console.log(`title: ${post['title']}`);

    var userId = 10;
    var timing = Exercise.get_request_timing(userId);
    console.log(`timing: ${timing} ms`);
};

main();
