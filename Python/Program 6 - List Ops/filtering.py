#Filtering the list based on a condition
numbers = [10,37,45,12,56,80,96,101]
filtered = []
num = int(input("Enter the number: "))
for i in numbers:
    if i>num:
        filtered.append(i)
print("Filtered list: ", filtered)