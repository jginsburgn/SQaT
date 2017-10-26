from selenium import webdriver
from selenium.webdriver.common.by import By
import time
from threading import Thread

driver=webdriver.Chrome()
driver.get("http://localhost/admin")


usern = driver.find_element_by_xpath('//*[@id="input-username"]');
usern.send_keys("admin")

passw = driver.find_element_by_xpath('//*[@id="input-password"]');
passw.send_keys("admin")

btn1 = driver.find_element_by_xpath('//*[@id="content"]/div/div/div/div/div[2]/form/div[3]/button');
btn1.click()

time.sleep(2)




catalogo = driver.find_element_by_xpath('//*[@id="menu-catalog"]/a');
catalogo.click()

btn0 = driver.find_element_by_xpath('//*[@id="collapse1"]/li[2]/a');
btn0.click()

time.sleep(2)

btn2 = driver.find_element_by_xpath('//*[@id="collapse1-1"]/li[1]/a');
btn2.click()


for x in range(1,3):
	time.sleep(5)

	btn3 = driver.find_element_by_xpath('//*[@id="content"]/div[1]/div/div/a');
	print(btn3)
	btn3.click()


	time.sleep(2)

	nombre = driver.find_element_by_xpath('//*[@id="input-name1"]');
	nombre.send_keys("prod"+str(x))

	meta = driver.find_element_by_xpath('//*[@id="input-meta-title1"]');
	meta.send_keys("prod"+str(x))

	btn4 = driver.find_element_by_xpath('//*[@id="form-product"]/ul/li[2]/a');
	btn4.click()


	model = driver.find_element_by_xpath('//*[@id="input-model"]');
	model.send_keys("prod"+str(x))

	btn5 = driver.find_element_by_xpath('//*[@id="content"]/div[1]/div/div/button');
	btn5.click()
