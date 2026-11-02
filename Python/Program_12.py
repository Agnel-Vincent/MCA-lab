def calculate_bill():
    try:
        units = float(input("Enter the number of units consumed: "))

        if units < 0:
            raise ValueError("Units cannot be negative!")

    except ValueError as e:
        print("Error:", e)

    else:
        if units <= 100:
            bill = units * 1.50
        elif units <= 200:
            bill = (100 * 1.50) + (units - 100) * 2.50
        else:
            bill = (100 * 1.50) + (100 * 2.50) + (units - 200) * 4.00

        print("\n--- Electricity Bill Summary ---")
        print("Units Consumed:", units)
        print(f"Total Bill Amount: ₹{bill:.2f}")

    finally:
        print("Calculation completed. Thank you!")


if __name__ == "__main__":
    calculate_bill()