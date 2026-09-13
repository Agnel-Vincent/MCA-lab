def area_of_circle():
  r = int(input("Enter radius of a circle: "))
  pi = 3.14
  area = pi*r**2
  print("Area of circle with radius ",r," is: ",area)

def check_leap_year():
  year = int(input("Enter the year: "))
  if year % 100 == 0:
    if year % 400 == 0:
      print(year, " is a leap year")
    else:
      print(year, " is not a leap year")
  else:
    if year % 4 == 0:
      print(year, " is a leap year")
    else:
      print(year, " is not a leap year")

def largest_of_three_numbers():
  a = int(input("Enter first number: "))
  b = int(input("Enter second number: "))
  c = int(input("Enter third number: "))

  if a > b and a > c:
    print(a, " is greater than ", b," and ",c)
  elif b > a and b > c:
    print(b, " is greater than ", a," and ",c)
  else:
    print(c, " is greater than ", a," and ",b)

def main_menu():
  while True:
    print("\nChoose an option:")
    print("1. Check Leap Year")
    print("2. Calculate Area of Circle")
    print("3. Find Largest of Three Numbers")
    print("4. Exit")

    choice = input("Enter your choice (1-4): ")

    if choice == '1':
      check_leap_year()
    elif choice == '2':
      area_of_circle()
    elif choice == '3':
      largest_of_three_numbers()
    elif choice == '4':
      print("Exiting program. Goodbye!")
      break
    else:
      print("Invalid choice. Please try again.")

# Call the main menu function to run the program
main_menu()