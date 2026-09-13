#Generating to List and Tuple
initial_list = input("Enter sequence of numbers: ")
converted_list = initial_list.split(",")
number_list = []
for i in converted_list:
    cleaned = i.strip()
    number_list.append(cleaned)

number_tuple = tuple(number_list)

print("List: ", number_list)
print("Tuple: ", number_tuple)

#Total number of elements
total = len(number_list)
print("Total number of elements: ", total)

#First and Last element
print("First Element: ", number_list[0])
print("Last Element: ", number_list[-1])

#Reverse Order
print("Reversed List: ", number_list[::-1])