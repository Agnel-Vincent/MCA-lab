def calculate_total(marks):
    return sum(marks)
def calculate_average(total, subjects):
    return total / subjects
def find_highest(marks):
    return max(marks)
def find_lowest(marks):
    return min(marks)
def determine_grade(average):
    if average >= 90:
        return "A+"
    elif average >= 75:
        return "A"
    elif average >= 60:
        return "B"
    elif average >= 50:
        return "C"
    else:
        return "Fail"
n = int(input("Enter the number of students: "))
students = []
for i in range(n):
    print("\nEnter details for Student", i + 1)
    name = input("Enter student name: ")
    subjects = int(input("Enter number of subjects: "))
    marks = []
    for j in range(subjects):
        mark = float(input("Enter mark for subject " + str(j + 1) + ": "))
        marks.append(mark)
    total = calculate_total(marks)
    average = calculate_average(total, subjects)
    highest = find_highest(marks)
    lowest = find_lowest(marks)
    grade = determine_grade(average)
    student = {
        "name": name,
        "marks": marks,
        "total": total,
        "average": average,
        "highest": highest,
        "lowest": lowest,
        "grade": grade
    }
    students.append(student)
students.sort(key=lambda student: student["total"], reverse=True)
print("\n========== STUDENT PERFORMANCE ==========")
for student in students:
    print("\nStudent Name :", student["name"])
    print("Marks        :", student["marks"])
    print("Total Marks  :", student["total"])
    print("Average      :", round(student["average"], 2))
    print("Highest Mark :", student["highest"])
    print("Lowest Mark  :", student["lowest"])
    print("Grade        :", student["grade"])
print("\n==========================================")