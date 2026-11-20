import requests
import pandas as pd
from bs4 import BeautifulSoup

# Scrape headlines from multiple category pages
categories = ["india", "sports", "technology"]
records = []
headers = {"User-Agent": "Mozilla/5.0"}

for cat in categories:
    url = f"https://indianexpress.com/section/{cat}/"
    response = requests.get(url, headers=headers)
    soup = BeautifulSoup(response.text, "html.parser")

    # Extract headline and publication date
    for item in soup.find_all("div", class_="articles")[:5]:
        title = item.find("h2")
        date = item.find("div", class_="date")
        if title:
            records.append({
                "Headline": title.get_text(strip=True),
                "Date": date.get_text(strip=True) if date else "N/A",
                "Category": cat.capitalize()
            })

# Store extracted data in CSV
df = pd.DataFrame(records)
df.to_csv("news.csv", index=False)

# Analysis
print("--- Extracted News (Preview) ---")
print(df[["Category", "Headline"]].to_string(index=False))

print(f"\nTotal Headlines: {len(df)}")
print("\nHeadlines Per Category:")
print(df["Category"].value_counts())

if not df.empty:
    print("\nMost Frequent Category:", df["Category"].value_counts().idxmax())
