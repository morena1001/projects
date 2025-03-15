import time
import pandas as pd
from bs4 import BeautifulSoup
from selenium import webdriver
import requests
import io
from PIL import Image
from pathlib import Path
import hashlib

from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver import ChromeOptions

options = ChromeOptions ()
# options.add_argument ("--headless=new")
options.add_argument("--disable-blink-features=AutomationControlled")
options.add_argument("window_size=1280,800")
options.add_argument("--disable-popup-blocking")
options.add_argument("--disable-save-password-bubble")

#email: 
email = 'morena010.kv@gmail.com'
#password:
password = 'FEB.jf.A.0227033926528!'
#username
username = "morena_kv"

driver = webdriver.Chrome (options=options, service=ChromeService (ChromeDriverManager ().install ()))
driver.get ("https://x.com/i/flow/login")
time.sleep(2)
#LOGIN
driver.find_element(By.XPATH,'//input').send_keys(username)
driver.find_elements(By.XPATH, '//*[@role="button"]')[2].click()
time.sleep(2)
# if len(driver.find_elements(By.XPATH,'//*[name="password"]')) == 0:
#     driver.find_element(By.XPATH,'//input').send_keys(email)
#     time.sleep(1)
#     driver.find_elements(By.XPATH, '//*[@role="button"]')[1].click()
#     time.sleep(2)
driver.find_elements(By.XPATH,'//input')[1].send_keys(password)
driver.find_elements(By.XPATH, '//*[@role="button"]')[3].click()
time.sleep(2)
driver.get("https://x.com/sakakaorin/media")

#GRAB CONTENT
content = driver.page_source
soup = BeautifulSoup (content, "html.parser")
time.sleep(5)
driver.quit ()

results = []
def parse_image_urls (classes, location, source):
    print (len (soup.find_all ()))
    print (soup.find_all ())
    for a in soup.find_all (attrs={"class": classes}):
        name = a.find(location)
        if name not in results:
            results.append(name.get(source))
parse_image_urls ("css-175oi2r r-1mlwlqe r-1udh08x r-417010 r-aqfbo4 r-agouwx r-1p0dtai r-1d2f490 r-u8s1d r-zchlnj r-ipm5af", "img", "src")
df = pd.DataFrame ({"links": results})
df.to_csv ("links.csv", index=False, encoding="utf-8")
print ("FINISHED")


# def parse_image_urls (classes, location, source):
#     results = []
#     for a in soup.find_all (attrs={"class": classes}):
#         name = a.find(location)
#         if name not in results:
#             results.append (name.get (source))

#     return results

# if __name__ == "__main__":
#     returned_results = parse_image_urls ("css-175oi2r r-1mlwlqe r-1udh08x r-417010 r-aqfbo4 r-agouwx r-1p0dtai r-1d2f490 r-u8s1d r-zchlnj r-ipm5af", "img", "src")
#     for b in returned_results:
#         image_content = requests.get(b).content
#         image_file = io.BytesIO(image_content)
#         image = Image.open (image_file).convert ("RGB")
#         file_path = Path("images", hashlib.sha1(image_content).hexdigest()[:10] + ".png")
#         image.save (file_path, "PNG", quality=80)
