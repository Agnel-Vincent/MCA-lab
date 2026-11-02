class BankAccount:
    def __init__(self, acc_no, name, acc_type, balance):
        self.acc_no = acc_no
        self.name = name
        self.acc_type = acc_type
        self.balance = balance
    def deposit(self, amount):
        self.balance += amount
        print("Amount deposited:", amount)

    def withdraw(self, amount):
        if amount > self.balance:
            print("Insufficient balance!")
        else:
            self.balance -= amount
            print("Amount withdrawn:", amount)
    def display(self):
        print("\n--- Account Details ---")
        print("Account Number:", self.acc_no)
        print("Account Holder:", self.name)
        print("Account Type:", self.acc_type)
        print("Balance:", self.balance)
acc_no = int(input("Enter account number: "))
name = input("Enter account holder name: ")
acc_type = input("Enter account type: ")
balance = float(input("Enter initial balance: "))
acc1 = BankAccount(acc_no, name, acc_type, balance)
acc1.display()
deposit_amt = float(input("\nEnter amount to deposit: "))
acc1.deposit(deposit_amt)
withdraw_amt = float(input("Enter amount to withdraw: "))
acc1.withdraw(withdraw_amt)
acc1.display()