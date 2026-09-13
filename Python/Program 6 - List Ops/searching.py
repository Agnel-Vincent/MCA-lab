#Searching in the list
numbers = [10,37,45,12,56,80,96,101]
print("Original list: ", numbers)

num = int(input("Enter the number to search: "))
for i in numbers:
    if i == num:
        print(num, " is in the list")
        break
    else:
        print(num, " is not in the list")
        break