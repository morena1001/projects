# importing necessary packages
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager

# for holding the resultant list
element_list = []

page_url = "https://x.com/sakakaorin/media"
driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()))
driver.get(page_url)
title = driver.find_elements(By.CLASS_NAME, "css-9pa8c")
# stuff = driver.find_elements (By.PARTIAL_LINK_TEXT,  "/photo/")

# for i in range(len(title)):
#     element_list.append(title)

# for element in element_list:
#     print (element)

# print (len (element_list))

# print (image)
print (title)

#closing the driver
driver.close()
