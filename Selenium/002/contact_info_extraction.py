#!/usr/bin/env python3

import time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import json
import sys

options = Options()
options.add_argument("--headless")

driver = webdriver.Chrome(chrome_options=options)
driver.get("http://micampus.csf.itesm.mx/index.php/division-de-diseno-ingenieria-y-arquitectura/directorio")

names_with_titles = driver.find_elements_by_xpath('//tr/td[1]')
emails = driver.find_elements_by_xpath('//tr/td[4]')

index = 0
names_and_emails = []
for name_with_title in names_with_titles:
    pure_name = name_with_title.text
    for title in name_with_title.find_elements_by_tag_name("span"):
        pure_name = pure_name.replace(title.text, "")
    pure_name = pure_name.replace("\n", "")
    names_and_emails.append({'name': pure_name, 'email': emails[index].text})
    index += 1

sys.stdout.write(json.dumps(names_and_emails, ensure_ascii=False, indent=2))

driver.close()
