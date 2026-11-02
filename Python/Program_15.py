import re
email = input("Enter email: ")
email_pattern = r"[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"
if re.fullmatch(email_pattern, email):
    print("Valid Email")
else:
    print("Invalid Email")
phone = input("Enter phone number: ")
phone_pattern = r"[6-9][0-9]{9}"
if re.fullmatch(phone_pattern, phone):
    print("Valid Phone Number")
else:
    print("Invalid Phone Number")
log = """
Payment successful TXN12345
Payment failed TXN67890
Refund completed TXN54321
"""
ids = re.findall(r"TXN[0-9]+", log)
print("Transaction IDs:", ids)