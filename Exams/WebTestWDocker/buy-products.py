from selenium import webdriver
from selenium.webdriver.common.by import By
import time
from threading import Thread

driver=webdriver.Chrome()
driver.get("http://localhost/")


for x in range(1,3):
	time.sleep(3)
	usern = driver.find_element_by_xpath('//*[@id="search"]/input');
	usern.clear()
	usern.send_keys("prod"+str(x))

	btn1 = driver.find_element_by_xpath('//*[@id="search"]/div/button');
	btn1.click()

	time.sleep(2)

	catalogo = driver.find_element_by_xpath('//*[@id="content"]/div[3]/div/div/div[1]/a');
	catalogo.click()

	time.sleep(2)
	btn1 = driver.find_element_by_xpath('//*[@id="button-cart"]');
	btn1.click()
