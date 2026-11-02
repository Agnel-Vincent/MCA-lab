import json
cities = []
n = int(input("Enter number of cities: "))
for i in range(n):
    print("\nEnter details of City", i + 1)
    name = input("City name: ")
    temp = float(input("Temperature: "))
    humidity = float(input("Humidity: "))
    city = {
        "location": {"name": name},
        "weather": {
            "temperature": temp,
            "humidity": humidity
        }
    }
    cities.append(city)
data = {"cities": cities}
json_data = json.dumps(data)
weather_data = json.loads(json_data)
print("\n----- WEATHER REPORT -----")
print(f"{'City':<15} {'Temp(C)':<15} {'Humidity(%)':<15}")
print("-" * 45)
total = 0
for city in weather_data["cities"]:
    name = city["location"]["name"]
    temp = city["weather"]["temperature"]
    humidity = city["weather"]["humidity"]
    print(f"{name:<15} {temp:<15.1f} {humidity:<15.1f}")
    total += temp
if n > 0:
    print("\nAverage Temperature:", round(total / n, 2))