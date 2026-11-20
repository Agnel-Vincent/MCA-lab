import time
from selenium import webdriver
from selenium.webdriver.common.by import By

name = "Agnel T Vincent"
email = "agnel@example.com"
current = "12 MG Road, Kochi"
permanent = "45 Main Street, Thrissur"

driver = webdriver.Chrome()
driver.get("https://demoqa.com/text-box")

# Fill form
driver.find_element(By.ID, "userName").send_keys(name)
driver.find_element(By.ID, "userEmail").send_keys(email)
driver.find_element(By.ID, "currentAddress").send_keys(current)
driver.find_element(By.ID, "permanentAddress").send_keys(permanent)

# Submit
submit = driver.find_element(By.ID, "submit")
driver.execute_script("arguments[0].click();", submit)

# Extract output rendered on page
out_name = driver.find_element(By.CSS_SELECTOR, "#output #name").text
out_email = driver.find_element(By.CSS_SELECTOR, "#output #email").text
out_current = driver.find_element(By.CSS_SELECTOR, "#output #currentAddress").text
out_permanent = driver.find_element(By.CSS_SELECTOR, "#output #permanentAddress").text

# Display extracted data
print("\n--- Form Submitted Data ---")
print(out_name)
print(out_email)
print(out_current)
print(out_permanent)

# Verify
if (name in out_name and email in out_email
        and current in out_current and permanent in out_permanent):
    print("\nResult: Verification Passed")
else:
    print("\nResult: Verification Failed")

# Keep browser open for 3 seconds so the teacher can see it
time.sleep(3)
driver.quit()