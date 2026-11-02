import os

FILE_NAME = "library.txt"


# Add a new book
def add_book():
    title = input("Enter book title: ")
    author = input("Enter author name: ")
    year = input("Enter publication year: ")

    with open(FILE_NAME, "a") as file:
        file.write(f"{title}|{author}|{year}\n")

    print("Book added successfully!")


# Display all books
def display_books():
    if not os.path.exists(FILE_NAME):
        print("No books available.")
        return

    with open(FILE_NAME, "r") as file:
        books = file.readlines()

    if not books:
        print("No books available.")
        return

    print("\n--- Library Catalogue ---")
    for book in books:
        title, author, year = book.strip().split("|")
        print("Title:", title)
        print("Author:", author)
        print("Year:", year)
        print("------------------------")


# Search book by title or author
def search_book():
    keyword = input("Enter book title or author to search: ").lower()

    if not os.path.exists(FILE_NAME):
        print("No books available.")
        return

    found = False

    with open(FILE_NAME, "r") as file:
        for book in file:
            title, author, year = book.strip().split("|")

            if keyword in title.lower() or keyword in author.lower():
                print("\nBook Found!")
                print("Title:", title)
                print("Author:", author)
                print("Year:", year)
                found = True

    if not found:
        print("Book not found.")


# Generate report for a specific author
def author_report():
    author_name = input("Enter author name: ").strip().lower()
    count = 0

    if not os.path.exists(FILE_NAME):
        print("No books available.")
        return

    with open(FILE_NAME, "r") as file:
        for book in file:
            title, author, year = book.strip().split("|")

            if author.lower() == author_name:
                count += 1

    print("Author:", author_name.title())
    print("Total number of books:", count)


# Main menu
while True:
    print("\n===== LIBRARY CATALOGUE =====")
    print("1. Add New Book")
    print("2. Display All Books")
    print("3. Search Book")
    print("4. Author Report")
    print("5. Exit")

    choice = input("Enter your choice: ")

    if choice == "1":
        add_book()
    elif choice == "2":
        display_books()
    elif choice == "3":
        search_book()
    elif choice == "4":
        author_report()
    elif choice == "5":
        print("Thank you for using the Library Catalogue!")
        break
    else:
        print("Invalid choice. Please try again.")
        