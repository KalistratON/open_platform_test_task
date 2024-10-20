#include "BookStore.h"

#include <algorithm>


void BookStore::AddBook (const Book& theBook)
{
    myBookMap.emplace (theBook).second;
}

void BookStore::RemoveBook (const std::string& theBookTitle)
{
    auto anIt = myBookMap.find (Book (theBookTitle));
    if (anIt == myBookMap.end()) {

    }

    myBookMap.erase (anIt);
}

const Book* BookStore::FindBook (const std::string& theBookTitle)
{
    auto anIt = myBookMap.find (Book (theBookTitle));
    if (anIt == myBookMap.end()) {
        return nullptr;
    }

    return std::addressof (*anIt);
}

std::vector<Book> BookStore::ListBook (SortType theSortType)
{
    std::vector<Book> aSortedBooks (myBookMap.size());
    auto anInBeginIt = myBookMap.cbegin(),
         anInEndIt = myBookMap.cend();
    auto anOutBeginIt = aSortedBooks.begin(),
         anOutEndIt = aSortedBooks.end();

    switch (theSortType)
    {
    case SortType::TITLE:
        std::partial_sort_copy (anInBeginIt, anInEndIt, anOutBeginIt, anOutEndIt, BookTitleLess());
        break;
    case SortType::AUTHOR:
        std::partial_sort_copy (anInBeginIt, anInEndIt, anOutBeginIt, anOutEndIt, BookAuthorLess());
        break;
    case SortType::YEAR:
        std::partial_sort_copy (anInBeginIt, anInEndIt, anOutBeginIt, anOutEndIt, BookYearLess());
        break;
    default:
        break;
    }
    return aSortedBooks;
}

BookStore::BookUSet BookStore::FindBookInPriceRange (float theMinPrice, float theMaxPrice)
{
    BookStore::BookUSet anInPriceRangeBooks;
    for (const auto& aBook : myBookMap) {
        if (aBook.Price() >= theMinPrice && aBook.Price() <= theMaxPrice) {
            anInPriceRangeBooks.emplace (aBook);
        }
    }
    return anInPriceRangeBooks;
}