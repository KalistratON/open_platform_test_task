#include <BookStore.h>
#include <SortType.h>

#include <algorithm>
#include <map>
#include <iostream>


enum class CommanType {
    ADD = 1,
    REMOVE,
    FIND,
    PRINT_SORTED,
    FIND_IN_PRICE_RANGE,
    EXIT
};

static bool PrintMenu (int& theCommand, BookStore& theBooksStore)
{
    if (theCommand < 1 || theCommand > 6) {
        std::wcout <<
        "1. Добавить книгу\n"
        "2. Удалить книгу\n"
        "3. Найти книгу по названию\n"
        "4. Показать все книги (сортировка по названию/автору/году издания)\n"
        "5. Найти книги в ценовом диапазоне\n"
        "6. Выйти\n"
        << std::endl;

        std::wcout << "-----------------------------------" << std::endl << "Введите опцию: ";
        std::wcin >> theCommand;

        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return true;
    }

    const auto& PrintBook = [](const Book& theBook) {
        std::wcout << "Название: ";
        wprintf (L"%s", theBook.Title().c_str());
        std::wcout << std::endl;

        std::wcout << "Автор: ";
        wprintf (L"%s", theBook.Author().c_str());
        std::wcout << std::endl;

        std::cout  << "Год издания: "  << theBook.PublishedYear()  << std::endl;
        std::cout  << "Цена: "         << theBook.Price()          << std::endl;
        std::wcout << "-------------------------------------------" << std::endl;
    };

    std::map<std::wstring, SortType> aSortMap { std::pair (std::wstring (L"название"), SortType::TITLE),
                                                std::pair (std::wstring (L"автор"),    SortType::AUTHOR),
                                                std::pair (std::wstring (L"год"),      SortType::YEAR) };

    switch (static_cast <CommanType> (theCommand))
    {
    case CommanType::ADD:
        {
            int anYear;
            float aPrice;
            std::wstring aTitle, anAuthor;
            std::wcout << "Введите название книги: ";
            std::getline (std::wcin, aTitle);
            std::wcout << "Введите автора книги: ";
            std::getline (std::wcin, anAuthor);
            std::wcout << "Введите год издания: ";
            std::wcin >> anYear;
            std::wcout << "Введите цену: ";
            std::wcin >> aPrice;

            if (theBooksStore.AddBook (Book (aTitle, anAuthor, anYear, aPrice))) {
                std::wcout << std::endl << "Книга успешно добавлена!" << std::endl << std::endl;
            } else {
                std::wcout << std::endl << "Книга уже существует!" << std::endl << std::endl;
            }
        }
        break;
    case CommanType::REMOVE:
        {
            std::wstring aTitle;
            std::wcout << "Введите название книги: ";
            std::getline (std::wcin, aTitle);

            if (theBooksStore.RemoveBook (aTitle)) {
                std::wcout << std::endl << "Книга успешно удалена!";
            } else {
                std::wcout << "Книга не найдена!";
            }
            std::wcout << std::endl << std::endl;
        }
        break;
    case CommanType::FIND:
        {
            std::wstring aTitle;
            std::wcout << "Введите название книги: ";
            std::getline (std::wcin, aTitle);

            const Book* aBook = theBooksStore.FindBook (aTitle);
            if (aBook) {
                PrintBook (*aBook);
            } else {
                std::wcout << "Книга не найдена!";
            }

            std::wcout << std::endl << std::endl;
        }
        break;
    case CommanType::PRINT_SORTED:
        {
            bool anIsFirst = true;
            std::wstring aTitle;
            std::map<std::wstring, SortType>::iterator anIt;
            do {
                if (!anIsFirst) {
                    std::wcout << "Неверный тип сортировки!" << std::endl << std::endl;
                }

                std::wcout << "Введите тип сортировки (название/автор/год): ";
                std::getline (std::wcin, aTitle);

                anIt = aSortMap.find (aTitle);
                anIsFirst = false;
            } while (anIt == aSortMap.end());

            auto aSortedBooks = theBooksStore.ListBook (anIt->second);
            std::for_each (aSortedBooks.begin(), aSortedBooks.end(), PrintBook);

            if (!aSortedBooks.size()) {
                std::wcout << "-------------------------------------------" << std::endl;
            }
            std::wcout << std::endl << std::endl;
        }
        break;
    case CommanType::FIND_IN_PRICE_RANGE:
        {
            bool anIsFirst = true;
            float aMinPrice, aMaxPrice;
            do {
                if (!anIsFirst) {
                    std::wcout << "Неверный диапазон!" << std::endl << std::endl;
                }

                std::wcout << "Введите минимальную цену: ";
                std::wcin >> aMinPrice;
                std::wcout << "Введите максимальную цену: ";
                std::wcin >> aMaxPrice;
            } while (aMinPrice > aMaxPrice);

            auto aDedicatedBooks = theBooksStore.FindBookInPriceRange (aMinPrice, aMaxPrice);
            std::for_each (aDedicatedBooks.begin(), aDedicatedBooks.end(), PrintBook);
            std::wcout << std::endl << std::endl;
        }
        break;
    case CommanType::EXIT:
        std::wcout << "До свидания!" << std::endl << std::endl;
        return false;
    }
    theCommand = -1;
    return true;
}

static void Execute()
{
    BookStore aBookStore;
    int anInputCommand = -1;
    while (PrintMenu (anInputCommand, aBookStore));
}

int main()
{
    setlocale (LC_ALL, "Russian");
    std::wcin.imbue (std::locale ("rus_rus.866"));
    std::wcout.imbue (std::locale ("rus_rus.866"));

    Execute();
    return 0;
}