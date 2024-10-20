#ifndef _BOOK_HEADER
#define _BOOK_HEADER

#include "Macro.h"

#include <string>


class Book final {
public:
    Book() = default;
    explicit Book (const std::wstring& theTitle);

    _EXPORT Book (const std::wstring& theTitle, const std::wstring& theAuthor, int thePublishedYead, float thePrice);

    _EXPORT Book (const Book& theBook) = default;
    _EXPORT Book (Book&& theBook) = default;
    _EXPORT ~Book() = default;

    _EXPORT const Book& operator= (const Book& theBook);
    _EXPORT const Book& operator= (Book&& theBook) noexcept;

    _EXPORT bool operator == (const Book& theBook) const;

    _DEFINE_PROPERTY (int, PublishedYear)
    _DEFINE_PROPERTY (float, Price)
    _DEFINE_PROPERTY (std::wstring, Title)
    _DEFINE_PROPERTY (std::wstring, Author)
};

class BookHash final {
public:
    _EXPORT size_t operator() (const Book& theBook) const;
};

class BookTitleLess {
public:
    bool operator() (const Book& theLhs, const Book& theRhs) const;
};

class BookAuthorLess {
public:
    bool operator() (const Book& theLhs, const Book& theRhs) const;
};

class BookYearLess {
public:
    bool operator() (const Book& theLhs, const Book& theRhs) const;
};

#endif