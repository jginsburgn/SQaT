#!/usr/bin/env python3

import time
from selenium import webdriver

driver = webdriver.Chrome()
driver.get("http://itsof.me/WebAppDev/deliverables/003/solution/")

#universal
print("Universal: *")
content = driver.find_elements_by_css_selector('*')
for element in content:
    print(element)

#grouping
print("Grouping: div, img")
content = driver.find_elements_by_css_selector('img, div')
for element in content:
    print(element)

#descendant
print("Descendant: nav *")
content = driver.find_elements_by_css_selector('nav *')
for element in content:
    print(element)

#child
print("Child: .container > *")
content = driver.find_elements_by_css_selector('.container > *')
for element in content:
    print(element)

#sibings
print("Siblings: .scene ~ .scene")
content = driver.find_elements_by_css_selector('.scene ~ .scene')
for element in content:
    print(element)

#class
print("Class: .captions")
content = driver.find_elements_by_css_selector('.captions')
for element in content:
    print(element)

#id
print("Id: #unexistent")
content = driver.find_elements_by_css_selector('#unexistent')
for element in content:
    print(element)

#pseudo-elements
print("Pseudo-Elements: p::first-line")
content = driver.find_elements_by_css_selector('p::first-line')
for element in content:
    print(element)

#pseudo-class
print("Pseudo-Class: .scene:last-of-type")
content = driver.find_elements_by_css_selector('.scene:last-of-type')
for element in content:
    print(element)

time.sleep(5)
driver.close()
