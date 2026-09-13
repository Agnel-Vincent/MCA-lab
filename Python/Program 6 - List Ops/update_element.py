#Update a number in list
numbers = [10,37,45,12,56,80,96,101]
print("Original list: ", numbers)
new_number = int(input("Enter the number to update: "))
pos = int(input("Enter the position of new number: "))
numbers[pos] = new_number
print("Updated list: ", numbers)