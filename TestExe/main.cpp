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
        "1. �������� �����\n"
        "2. ������� �����\n"
        "3. ����� ����� �� ��������\n"
        "4. �������� ��� ����� (���������� �� ��������/������/���� �������)\n"
        "5. ����� ����� � ������� ���������\n"
        "6. �����\n"
        << std::endl;

        std::wcout << "-----------------------------------" << std::endl << "������� �����: ";
        std::wcin >> theCommand;

        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return true;
    }

    const auto& PrintBook = [](const Book& theBook) {
        std::wcout << "��������: ";
        wprintf (L"%s", theBook.Title().c_str());
        std::wcout << std::endl;

        std::wcout << "�����: ";
        wprintf (L"%s", theBook.Author().c_str());
        std::wcout << std::endl;

        std::cout  << "��� �������: "  << theBook.PublishedYear()  << std::endl;
        std::cout  << "����: "         << theBook.Price()          << std::endl;
        std::wcout << "-------------------------------------------" << std::endl;
    };

    std::map<std::wstring, SortType> aSortMap { std::pair (std::wstring (L"��������"), SortType::TITLE),
                                                std::pair (std::wstring (L"�����"),    SortType::AUTHOR),
                                                std::pair (std::wstring (L"���"),      SortType::YEAR) };

    switch (static_cast <CommanType> (theCommand))
    {
    case CommanType::ADD:
        {
            int anYear;
            float aPrice;
            std::wstring aTitle, anAuthor;
            std::wcout << "������� �������� �����: ";
            std::getline (std::wcin, aTitle);
            std::wcout << "������� ������ �����: ";
            std::getline (std::wcin, anAuthor);
            std::wcout << "������� ��� �������: ";
            std::wcin >> anYear;
            std::wcout << "������� ����: ";
            std::wcin >> aPrice;

            if (theBooksStore.AddBook (Book (aTitle, anAuthor, anYear, aPrice))) {
                std::wcout << std::endl << "����� ������� ���������!" << std::endl << std::endl;
            } else {
                std::wcout << std::endl << "����� ��� ����������!" << std::endl << std::endl;
            }
        }
        break;
    case CommanType::REMOVE:
        {
            std::wstring aTitle;
            std::wcout << "������� �������� �����: ";
            std::getline (std::wcin, aTitle);

            if (theBooksStore.RemoveBook (aTitle)) {
                std::wcout << std::endl << "����� ������� �������!";
            } else {
                std::wcout << "����� �� �������!";
            }
            std::wcout << std::endl << std::endl;
        }
        break;
    case CommanType::FIND:
        {
            std::wstring aTitle;
            std::wcout << "������� �������� �����: ";
            std::getline (std::wcin, aTitle);

            const Book* aBook = theBooksStore.FindBook (aTitle);
            if (aBook) {
                PrintBook (*aBook);
            } else {
                std::wcout << "����� �� �������!";
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
                    std::wcout << "�������� ��� ����������!" << std::endl << std::endl;
                }

                std::wcout << "������� ��� ���������� (��������/�����/���): ";
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
                    std::wcout << "�������� ��������!" << std::endl << std::endl;
                }

                std::wcout << "������� ����������� ����: ";
                std::wcin >> aMinPrice;
                std::wcout << "������� ������������ ����: ";
                std::wcin >> aMaxPrice;
            } while (aMinPrice > aMaxPrice);

            auto aDedicatedBooks = theBooksStore.FindBookInPriceRange (aMinPrice, aMaxPrice);
            std::for_each (aDedicatedBooks.begin(), aDedicatedBooks.end(), PrintBook);
            std::wcout << std::endl << std::endl;
        }
        break;
    case CommanType::EXIT:
        std::wcout << "�� ��������!" << std::endl << std::endl;
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