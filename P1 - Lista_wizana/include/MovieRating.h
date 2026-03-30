#pragma once
#include <string>
struct MovieRating
{
    int id;
    std::string title;
    int rating;

    MovieRating() {
        id = 0;
        title = "";
        rating = 0;
    }
    MovieRating(int id_, std::string title_, int rating_) : id{id_}, title{title_}, rating{rating_} {}

    bool operator==(const MovieRating& other) const {
        return id == other.id && 
            title == other.title && 
            rating == other.rating;
    }

    MovieRating& operator=(const MovieRating& other) {
        this->id = other.id;
        this->title = other.title;
        this->rating = other.rating;
        return *this;
    }
};
