#ifndef _BOOK_STORE_HEADER
#define _BOOK_STORE_HEADER

#include "Book.h"
#include "SortType.h"

#include <string>
#include <unordered_set>
#include <vector>


class BookStore final {
public:
    using BookUSet = std::unordered_set<Book, BookHash>;

    _EXPORT BookStore () = default;

    _EXPORT void AddBook (const Book& theBook);
    _EXPORT void RemoveBook (const std::wstring& theBookTitle);
    _EXPORT const Book* FindBook (const std::wstring& theBookTitle);
    _EXPORT std::vector<Book> ListBook (SortType theSortType);
    _EXPORT BookUSet FindBookInPriceRange (float theMinPrice, float theMaxPrice);

private:
    BookUSet myBookMap;
};

#endif