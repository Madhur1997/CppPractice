#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

/*
FR: 1. Post, Comment, Like, Make friends
2. Get feed of posts from friends.
*/

enum PrivacySettings {
    PUBLIC,
    PRIVATE,
    FRIENDS
};

class UserProfile {
    string name;
    int userId;
    string email;
    string phone;
    PrivacySettings privacySettings;
};

class Like {
    int likeId;
    int userId;
};

class Comment {
    int commentId;
    int userId;
    string content;
};

class Post {
    int postId;
    int userId;
    vector<Comment> comment;
    vector<Like> likes;
    string content;
    string photo;

public:
    int getPostId() {
        return postId;
    }
};

class IFeedService {
    public:
        vector<Post> getFeed(int userId) = 0;
};

class IFriendService {
    public:
        vector<UserProfile> getFriends(int userId) = 0;
};

class FriendDao {
    unordered_map<int, vector<int>> friends;
    public:
        vector<int> getFriendIds(int userId) {
            return friends[userId];
        }
};

class FriendService {
    FriendDao* friendDao;
    public:
        vector<int> getFriendIds(int userId) {
            // Get friends from DB
            return friendDao->getFriendIds(userId);
        }
};

class IFeedCache {
    public:
        vector<Post*> getPosts(int userId) = 0;
};

class FeedCache {
    unordered_map<int, vector<Post*>> userPosts;
    public:
        vector<Post*> getPosts(int userId) {
            vector<Post*> posts;
            for(int i=0; i<userPosts[userId].size() && i<5; i++) {
                userPosts[userId][i]->getPostId();
                posts.push_back(userPosts[userId][i]);
            }
        }
};

class FeedService : public IFeedService {
    IFriendService* friendService;
    IFeedCache* feedCache;
public:

    vector<Post> getFeed(int userId) {
        vector<int> friendIds = friendService->getFriendIds(userId);
        vector<Post> feed;
        for(int friendId : friendIds) {
            vector<Post> friendPosts = feedCache->getPosts(friendId);
            feed.insert(feed.end(), friendPosts.begin(), friendPosts.end());
        }
        return feed;
    }

    void updateFeed(int userId, Post* post) {
        feedCache->updateFeed(userId, post);
    }

};

class IPostsService {
public:
    virtual void makePost()=0;
    virtual void likePost()=0;
    virtual void commentPost()=0;
    virtual vector<Post*> listPosts(int userId) = 0;
};

class PostsDao {
    unordered_map<int, vector<Post*>> userIdToPosts;
    unordered_map<int, vector<Post*>> postIdToPosts;
public:
    void makePost(int userId, Post* post) {
        userIdToPosts[userId].push_back(post);
        postIdToPosts[post->getPostId()].push_back(post);
    }

    void likePost(int userId, int postId) {
    }

    void commentPost(int userId, int postId, Comment comment) {
        // Comment post
    }

    vector<Post*> getPostsByUserId(int userId) {
        return userIdToPosts[userId];
    }
};

class PostsService : public IPostsService {
    IFeedService* feedService;
    PostsDao* postsDao;

public:
    void makePost() {
        // Make post
        // Update feed
    }

    void likePost() {
        // Like post
        // Update feed
    }

    void commentPost() {
        // Comment post
        // Update feed
    }

};