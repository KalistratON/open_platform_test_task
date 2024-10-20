#include "Book.h"


Book::Book (const std::string& theTitle) :
    myTitle (theTitle)
{};

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

size_t BookHash::operator() (const Book& theBook) const
{
    return std::hash<std::string>() (theBook.Title());
}

bool BookTitleLess::operator() (const Book& theLhs, const Book& theRhs) const
{
    return theLhs.Title() < theRhs.Title();
}

bool BookAuthorLess::operator() (const Book& theLhs, const Book& theRhs) const
{
    return theLhs.Author() < theRhs.Author();
}

bool BookYearLess::operator() (const Book& theLhs, const Book& theRhs) const
{
    return theLhs.PublishedYear() < theRhs.PublishedYear();
}