#!/usr/bin/env python3

import subprocess
import random
import string
import json
import time
import sys
from os import path
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

# Obtain credentials to signup and login
print("Retrieving login credentials...")
contact_info_extraction = subprocess.run(path.join(path.dirname(path.abspath(__file__)), "../002/contact_info_extraction.py"), stdout=subprocess.PIPE)
names_and_emails = json.loads(contact_info_extraction.stdout)

# Make unique emails and prepare passwords
for name_and_email in names_and_emails:
    name_and_email["email"] = "".join(random.choices(string.ascii_uppercase + string.digits, k=15)) + name_and_email["email"]
    name_and_email["password"] = "".join(random.choices(string.ascii_uppercase + string.digits, k=15))

# Prepare options for the webdriver
options = Options()
options.add_argument("--headless")

# Get webdriver, with wait enabled
driver = webdriver.Chrome(chrome_options=options)
driver.get("http://blazedemo.com/")
wait = WebDriverWait(driver, 20)

for name_and_email in names_and_emails:

    # Navigate to registration page
    home_link = driver.find_element_by_link_text("home")
    home_link.click()
    register_link = driver.find_element_by_link_text("Register")
    register_link.click()

    # Register
    name_input = driver.find_element_by_css_selector("input#name")
    name_input.send_keys(name_and_email["name"])
    company_input = driver.find_element_by_css_selector("input#company")
    company_input.send_keys("ITESM")
    email_input = driver.find_element_by_css_selector("input#email")
    email_input.send_keys(name_and_email["email"])
    password_input = driver.find_element_by_css_selector("input#password")
    password_input.send_keys(name_and_email["password"])
    password_confirm_input = driver.find_element_by_css_selector("input#password-confirm")
    password_confirm_input.send_keys(name_and_email["password"])
    password_confirm_input.send_keys(Keys.ENTER)

    # Check successful registration
    try:
        if wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, "div.panel-body"))).text == "You are logged in!":
            print(name_and_email["name"], "has been signed up!")
    except Exception as e:
        sys.exit(name_and_email["name"], "could not be signed up. Terminating...")

    # Logout
    dropdown_toggle = driver.find_element_by_css_selector("a.dropdown-toggle")
    dropdown_toggle.click()
    logout_link = driver.find_element_by_css_selector("ul.dropdown-menu a")
    logout_link.click()

    # Navigate to login page
    home_link = driver.find_element_by_link_text("home")
    home_link.click()

    #Login
    email_input = driver.find_element_by_css_selector("input#email")
    email_input.send_keys(name_and_email["email"])
    password_input = driver.find_element_by_css_selector("input#password")
    password_input.send_keys(name_and_email["password"])
    password_input.send_keys(Keys.ENTER)

    # Check successful login
    try:
        if wait.until(EC.presence_of_element_located((By.CSS_SELECTOR, "div.panel-body"))).text == "You are logged in!":
            print(name_and_email["name"], "has been logged in!")
    except Exception as e:
        sys.exit(name_and_email["name"], "could not be logged in. Terminating...")

    # Logout
    dropdown_toggle = driver.find_element_by_css_selector("a.dropdown-toggle")
    dropdown_toggle.click()
    logout_link = driver.find_element_by_css_selector("ul.dropdown-menu a")
    logout_link.click()

# Discard webdriver
driver.close()
