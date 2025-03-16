import time
import math
import pandas as pd
from bs4 import BeautifulSoup
from selenium import webdriver
import requests
import io
from PIL import Image
from pathlib import Path
import hashlib
import argparse

from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver import ChromeOptions



# CHROME WINDOW SETTINGS
def baseOptions (no_window: bool):
    options = ChromeOptions ()
    if no_window: options.add_argument ("--headless=new")
    options.add_argument ("--disable-blink-features=AutomationControlled")
    options.add_argument ("window_size=1280,800")
    options.add_argument ("--disable-popup-blocking")
    options.add_argument ("--disable-save-password-bubble")
    return options

# NAVIGATING TO ACCOUNT PAGE
def navigateLogIn (driver, info):
    driver.get ("https://x.com/i/flow/login")
    time.sleep (3)
    #LOGIN
    driver.find_element (By.XPATH,'//input').send_keys (info.username)
    driver.find_elements (By.XPATH, '//*[@role="button"]')[2].click ()
    time.sleep (1.5)
    # if len (driver.find_elements (By.XPATH,'//*[name="password"]')) == 0:
    #     driver.find_element (By.XPATH,'//input').send_keys (email)
    #     time.sleep (1)
    #     driver.find_elements (By.XPATH, '//*[@role="button"]')[1].click ()
    #     time.sleep (2)
    driver.find_elements (By.XPATH,'//input')[1].send_keys (info.password)
    driver.find_elements (By.XPATH, '//*[@role="button"]')[3].click ()
    time.sleep (1.5)
    driver.get (info.user)
    time.sleep (1.5)

# SCRAPING LINKS FOR ALL NON NESTED IMAGE
def scrapeLinks (driver):
    inner = driver.find_element (By.XPATH, '//*[contains(text(),"photos & videos")]')
    numPages = math.ceil (int (inner.get_attribute ("innerHTML").split (" ")[0]) / 30)
    stopScrolling = 0
    links = []
    nested_links = []

    while True:
        list = driver.find_elements (By.XPATH, '//img')
        for item in list:
            parent = item.find_element (By.XPATH, "./../../../..")
            svg = parent.find_elements (By.TAG_NAME, "svg")

            if len (svg) != 0:
                nested_links.append (parent.get_attribute ("href"))
            else:    
                src = item.get_attribute ("src")
                if src.startswith ("https://pbs.twimg.com/media/") and src not in links:
                    links.append (src)

        stopScrolling += 1
        driver.execute_script("window.scrollTo(0,document.body.scrollHeight)", "")
        if stopScrolling > numPages:
            break
        time.sleep (1.5)

    for link in nested_links:
        driver.get (link)
        time.sleep (1.5)
        list = driver.find_elements (By.XPATH, '//img')
        for item in list:
            src = item.get_attribute ("src")
            if src.startswith ("https://pbs.twimg.com/media") and src not in links:
                links.append (src)

    driver.quit ()
    return links

# PARSING ALL LINKS INTO CSV FILE
def saveToCSV (links):
    df = pd.DataFrame ({"links": links})
    df.to_csv ("links.csv", index=False, encoding="utf-8")

# DOWNLOADING ALL IMAGES
def downloadImages (links):
    for link in links:
        image_content = requests.get (link).content
        image_file = io.BytesIO (image_content)
        image = Image.open (image_file).convert ("RGB")
        file_path = Path ("images", hashlib.sha1 (image_content).hexdigest ()[:10] + ".png")
        image.save (file_path, "PNG", quality=80)



class information:
    def __init__ (self, user: str, email: str, password: str, username: str):
        self.user = "https://x.com/" + user + "/media"
        self.email = email
        self.password = password
        self.username = username


if __name__ == "__main__":
    parser = argparse.ArgumentParser ("Scrape Pictures off the userpage of a Twitter User")
    parser.add_argument ('-u', '--user',  metavar="user", type=str, nargs=1, help="User to parse from", default="MitsuamiSchema")
    parser.add_argument ('-e', '--email',  metavar="email", type=str, nargs=1, help="Account email to log in", default="deadone1001@gmail.com")
    parser.add_argument ('-p', '--password',  metavar="password", type=str, nargs=1, help="Account password to log in", default="1234567890qwerpoiuty..")
    parser.add_argument ('-un', '--username',  metavar="username", type=str, nargs=1, help="Account username to log in", default="deadone1001")
    parser.add_argument ('-s', '--save', action="store_true")
    parser.add_argument ('-nw', '--no_window', action="store_true")

    args = parser.parse_args()

    # Initialize information object
    if isinstance (args.user, list):        args.user = args.user[0]
    if isinstance (args.email, list):       args.email = args.email[0]
    if isinstance (args.password, list):    args.password = args.password[0]
    if isinstance (args.username, list):    args.username = args.username[0]
    info = information (args.user, args.email, args.password, args.username)

    # Initialize webdriver and navigate to account page
    print ("BEGINNING LOG IN PROCESS")
    options = baseOptions (args.no_window)
    driver = webdriver.Chrome (options=options, service=ChromeService (ChromeDriverManager ().install ()))
    navigateLogIn (driver, info)
    print ("REACHED REQUESTED USER'S MEDIA")

    # Extract all links and save to csv if -s flag is set
    print ("BEGINNING LINK SCRAPING PROCESS")
    links = scrapeLinks (driver)
    print ("FINISHED LINK SCRAPING PROCESS")
    if args.save : 
        print ("BEGINNING SAVING LINKS TO CSV FILE")
        saveToCSV (links)
        print ("FINISHED SAVING LINKS TO CSV FILE")

    # Extract all images and store in a directory called images
    print ("BEGINNING SAVING IMAGES IN IMAGES DIRECTORY")
    Path('images').mkdir(parents=True, exist_ok=True)
    downloadImages (links)
    print ("FINISHED SAVING IMAGES IN IMAGES DIRECTORY")

    print ("FINISHED ENTIRE PROCESS")
