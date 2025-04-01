import time
import argparse
import pandas as pd

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.chrome.service import Service as ChromeService
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver import ChromeOptions
from selenium.webdriver.common.keys import Keys



# CHROME WINDOW SETTINGS
def baseOptions (no_window: bool):
    options = ChromeOptions ()
    if no_window: options.add_argument ("--headless=new")
    options.add_argument ("--disable-blink-features=AutomationControlled")
    options.add_argument ("window_size=1280,800")
    options.add_argument ("--disable-popup-blocking")
    options.add_argument ("--disable-save-password-bubble")
    return options

# LOGGING IN TO X
def xLogIn (driver, info):
    driver.get ("https://x.com/i/flow/login")

    WebDriverWait(driver, 20).until(EC.visibility_of_element_located((By.XPATH, '//input'))).send_keys (info.xUsername)
    driver.find_element (By.XPATH, '//button[@class="css-175oi2r r-sdzlij r-1phboty r-rs99b7 r-lrvibr r-ywje51 r-184id4b r-13qz1uu r-2yi16 r-1qi8awa r-3pj75a r-1loqt21 r-o7ynqc r-6416eg r-1ny4l3l"]').click ()
    
    # if len (driver.find_elements (By.XPATH,'//*[name="password"]')) == 0:
    #     driver.find_element (By.XPATH,'//input').send_keys (email)
    #     time.sleep (1)
    #     driver.find_elements (By.XPATH, '//*[@role="button"]')[1].click ()
    #     time.sleep (2)

    WebDriverWait(driver, 20).until(EC.visibility_of_element_located((By.XPATH, '//input[@type="password"]'))).send_keys (info.xPassword)
    driver.find_elements (By.XPATH, '//*[@role="button"]')[3].click ()
    time.sleep (1.5)

# LOGGING IN TO MICROSOFT LISTS
def listLogIn (driver, info):
    driver.get ("https://lists.live.com/?listId=029f2ab5de3e47f99b768906150d9e3d%5F7427cb0e3787e72f")

    try:
        element = WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//input[@id="i0116"]')))
    except:
        driver.find_element (By.XPATH, '//input[@id="usernameEntry"]').send_keys (info.lEmail)
        driver.find_element (By.XPATH, '//button[@type="submit"]').click ()

        WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//input[@id="passwordEntry"]'))).send_keys (info.lPassword)
        # driver.find_element (By.XPATH, '//input[@id="passwordEntry"]').send_keys (info.lPassword)
        driver.find_element (By.XPATH, '//button[@type="submit"]').click ()

        WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//button[@data-testid="secondaryButton"]'))).click ()
        # driver.find_element (By.XPATH, '//button[@data-testid="secondaryButton"]').click ()
    else:
        element.send_keys (info.lEmail)
        driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()
        
        WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//input[@id="i0118"]'))).send_keys (info.lPassword)
        driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()

        WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//button[@id="declineButton"]'))).click ()

    # try:
    #     element = WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//input[@id="i0118"]')))
    # except:
    #     driver.find_element (By.XPATH, '//input[@id="passwordEntry"]').send_keys (info.lPassword)
    #     driver.find_element (By.XPATH, '//button[@type="submit"]').click ()
    # else:
    #     element.send_keys (info.lPassword)
    #     driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()

    # try:
    #     element = WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//button[@id="declineButton"]')))
    # except:
    #     driver.find_element (By.XPATH, '//button[@data-testid="secondaryButton"]').click ()
    # else:
    #     element.click ()
    time.sleep (2)


# SCRAPE ACCOUNT INFORMATION 
def scrapeAccounts (driver, info):
    list = []

    for account in info.accounts:
        driver.get (account)
        WebDriverWait(driver, 3).until(EC.visibility_of_element_located((By.XPATH, '//*[contains(text(),"photos & videos")]')))
        item = []
        item.append (account)
        item.append (account[14:-6])
        item.append (toNearestMax (int (driver.find_element (By.XPATH, '//*[contains(text(),"photos & videos")]').get_attribute ("innerHTML").split (" ")[0].replace (",", ""))))
        list.append (item)

    return list

# UPLOAD ACCOUNT INFORMATION INTO MICROSOFT LISTS
def uploadData (driver, data):
    driver.get ("https://lists.live.com/?listId=029f2ab5de3e47f99b768906150d9e3d%5F7427cb0e3787e72f")
    time.sleep (3)

    frame = driver.find_element (By.XPATH, '//iframe')
    driver.switch_to.frame (frame)
    time.sleep (1.5)

    for i in range (len (data)):        
        driver.find_element (By.XPATH, '//button[@data-id="new"]').click ()    

        WebDriverWait(driver, 20).until(EC.visibility_of_element_located((By.XPATH, '//../div[@class="ReactFieldEditor"]')))
        fields = driver.find_elements (By.XPATH, '//../div[@class="ReactFieldEditor"]')
        
        fields[2].find_element (By.XPATH, './span/div/div[1]/div/div/input').send_keys (data[i][0])
        fields[2].find_element (By.XPATH, './span/div/div[2]/div/div/input').send_keys (data[i][1])
        fields[3].find_element (By.XPATH, './span/div').click ()
        driver.switch_to.active_element.send_keys (data[i][2])
        driver.find_element (By.XPATH, '//div[@id="Flyout-0"]').click ()    
        driver.find_element (By.XPATH, '//button[@data-automationid="ReactClientFormSaveButton"]').click ()
        time.sleep (1)

# Transform the actual number of media into the nearest max number
def toNearestMax (value):
    if value <= 200:
        return "200"
    elif value <= 300:
        return "300"
    elif value <= 400:
        return "400"
    elif value <= 500:
        return "500"
    elif value <= 600:
        return "600"
    elif value <= 700:
        return "700"
    elif value <= 800:
        return "800"
    elif value <= 900:
        return "900"
    elif value <= 1000:
        return "1000"
    elif value <= 1250:
        return "1250"
    elif value <= 1500:
        return "1500"
    elif value <= 1750:
        return "1750"
    elif value <= 2000:
        return "2000"
    elif value <= 2500:
        return "2500"
    elif value <= 3000:
        return "3000"
    else:
        return "3000+"
    
# Parse the accounts in accounts.txt file
def parseAccounts ():
    accounts = []

    file = open ('accounts.txt', 'r')
    for account in file:
        accounts.append (account.strip ())

    file.close ()

    return accounts

# Download the csv file from lists
def downloadCSV (driver):
    frame = driver.find_element (By.XPATH, '//iframe')
    driver.switch_to.frame (frame)

    WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, '//button[@data-id="export"]'))).click()
    WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, '//button[@data-automationid="exportListToCSVCommand"]'))).click()
    WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.XPATH, '//button[@data-automationid="splitbuttonprimary"]')))

# Check that any of the accounts to be added is not already in the list
def checkDupe (info):
    df = pd.read_csv (info.csvFile)
    links = df.pop('Account Link').dropna ()

    for i in range (len (links)):
        if not links[i].endswith ("/media"):
            links = links.drop (i)
            i -= 1

    links = links.tolist ()
    for account in info.accounts:
        if account in links:
            info.accounts.remove (account)



class information:
    def __init__ (self, xEmail: str, xUsername: str, xPassword: str, lEmail: str, lPassword: str, downloc:str, accounts: list):
        self.xEmail = xEmail
        self.xPassword = xPassword
        self.xUsername = xUsername
        self.lEmail = lEmail
        self.lPassword = lPassword
        self.csvFile = downloc + 'Accounts.csv'
        self.accounts = []

        for account in accounts:
            self.accounts.append ("https://x.com/" + account + "/media")




if __name__ == "__main__":
    parser = argparse.ArgumentParser ("Creating a list of accounts to scrape their images")
    parser.add_argument ('-nw', '--no_window', action="store_true")
    parser.add_argument ('-uf', '--use_file', action="store_true")
    parser.add_argument ('-xe', '--xEmail',  metavar="xEmail", type=str, nargs=1, help="x email to log in", default="deadone1001@gmail.com")
    parser.add_argument ('-un', '--username',  metavar="username", type=str, nargs=1, help="x username to log in", default="deadone1001")
    parser.add_argument ('-xp', '--xPassword',  metavar="xPassword", type=str, nargs=1, help="x password to log in", default="1234567890qwerpoiuty..")
    parser.add_argument ('-le', '--lEmail', metavar='lEmail', type=str, nargs=1, help='lists email to log in', default='')
    parser.add_argument ('-lp', '--lPassword', metavar='lPassword', type=str, nargs=1, help='lists password to log in', default='')
    parser.add_argument ('-dl', '--download_location', metavar='downloc', type=str, nargs=1, help='The normal file download location to use the csv file from lists', default="C:\\Users\\josue\\Downloads\\")
    parser.add_argument ('-u', '--users',  metavar="users", type=str, nargs='+', help="Users to parse info from")

    args = parser.parse_args ()

    # Initialize information object
    if isinstance (args.xEmail, list):          args.xEmail = args.xEmail[0]
    if isinstance (args.username, list):      args.username = args.username[0]
    if isinstance (args.xPassword, list):      args.xPassword = args.xPassword[0]
    if isinstance (args.lEmail, list):          args.lEmail = args.lEmail[0]
    if isinstance (args.lPassword, list):      args.lPassword = args.lPassword[0]
    info = information (args.xEmail, args.username, args.xPassword, args.lEmail, args.lPassword, args.download_location, parseAccounts () if args.use_file else args.users)

    # Initialize webdriver
    print ("BEGINNING INITIALIZATION OF WEBDRIVER")
    options = baseOptions (args.no_window)
    driver = webdriver.Chrome (options=options, service=ChromeService (ChromeDriverManager ().install ()))
    print ("FINISHED INITIALIZATION OF WEBDRIVER")

    # Log in to x and lists
    print ("BEGINNING LOG IN PROCESS OF X")
    xLogIn (driver, info)
    print ("FINISHED LOG IN PROCESS OF X")

    print ("BEGINNING LOG IN PROCESS OF LISTS")
    listLogIn (driver, info)
    print ("FINISHED LOG IN PROCESS OF LISTS")

    # Download the csv file to make sure an account is not added twice
    print ("BEGINNING CSV DOWNLOAD PROCESS")
    downloadCSV (driver)
    print ("FINISHED CSV DOWNLOAD PROCESS")

    # Make sure each account is not already in the list
    print ("BEGINNING DUPLICATE CHECKING PROCESS")
    checkDupe (info)
    print ("FINISHED DUPLICATE CHECKING PROCESS")

    # Extract all the necessary information for the list
    print ("BEGINNING DATA SCRAPING PROCESS")
    data = scrapeAccounts (driver, info)
    print ("FINISHED DATA SCRAPING PROCESS")

    # Upload all the information to the list
    print ("BEGINNING DATA UPLOAD PROCESS")
    uploadData (driver, data)
    print ("FINISHED DATA UPLOADING PROCESS")

    driver.quit ()
    print ("FINISHED ENTIRE PROCESS :)")
