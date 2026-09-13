#check palindrome
text = input("Enter the string: ")
if text == text[::-1]:
    print("The string is palindrome.")
else:
    print("The string is not palindrome.")