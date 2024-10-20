#include "Book.h"


Book::Book (const std::string& theTitle, const std::string& theAuthor, int thePublishedYead, float thePrice) :
    myPublishedYear (thePublishedYead), myPrice (thePrice), myTitle (theTitle), myAuthor (theAuthor)
{}

const Book& Book::operator= (const Book& theBook)
{
    myPublishedYear = theBook.myPublishedYear;
    myPrice = theBook.myPrice;
    myTitle = theBook.myTitle;
    myAuthor = theBook.myAuthor;
    return *this;
}

const Book& Book::operator= (Book&& theBook) noexcept
{
    myPublishedYear = std::move (theBook.myPublishedYear);
    myPrice = std::move (theBook.myPrice);
    myTitle = std::move (theBook.myTitle);
    myAuthor = std::move (theBook.myAuthor);
    return *this;
}

bool Book::operator == (const Book& theBook) const
{
    return myTitle == theBook.myTitle;
}