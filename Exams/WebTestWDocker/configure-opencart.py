from selenium import webdriver
from selenium.webdriver.common.by import By
import time
from threading import Thread

driver=webdriver.Chrome()
driver.get("http://localhost/")

btn1 = driver.find_element_by_xpath("/html/body/div/div/div[1]/form/div[2]/div/input");
btn1.click()

#WebDriverWait(driver, 10).until(ExpectedConditions.presenceOfElementLocated(driver.find_element_by_xpath("/html/body/div/div/div[1]/form/div/div[2]/input")));
time.sleep(2)

btn2 = driver.find_element_by_xpath("/html/body/div/div/div[1]/form/div/div[2]/input");
print(btn2)
btn2.click()

time.sleep(2)
#id
css9 = driver.find_element(By.CSS_SELECTOR,"#input-db-hostname");
css9.clear()
css9.send_keys("mysql")

css9 = driver.find_element(By.CSS_SELECTOR,"#input-db-username");
css9.clear()
css9.send_keys("opencart")

css9 = driver.find_element(By.CSS_SELECTOR,"#input-db-password");
css9.send_keys("opencart")

css9 = driver.find_element(By.CSS_SELECTOR,"#input-db-database");
css9.send_keys("opencart")


css9 = driver.find_element(By.CSS_SELECTOR,"#input-password");
css9.send_keys("admin")

css9 = driver.find_element(By.CSS_SELECTOR,"#input-email");
css9.send_keys("levygad@gmail.com")

btn3 = driver.find_element_by_xpath("/html/body/div/div/div[1]/form/div/div[2]/input");
btn3.click()

time.sleep(2)

btn4 = driver.find_element_by_xpath("/html/body/div/div[2]/div/div[2]/a");
btn4.click()
