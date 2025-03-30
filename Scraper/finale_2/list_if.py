import time
import argparse

from selenium import webdriver
from selenium.webdriver.common.by import By
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
    time.sleep (3)
    #LOGIN
    driver.find_element (By.XPATH,'//input').send_keys (info.xUsername)
    driver.find_elements (By.XPATH, '//*[@role="button"]')[2].click ()
    time.sleep (1.5)
    # if len (driver.find_elements (By.XPATH,'//*[name="password"]')) == 0:
    #     driver.find_element (By.XPATH,'//input').send_keys (email)
    #     time.sleep (1)
    #     driver.find_elements (By.XPATH, '//*[@role="button"]')[1].click ()
    #     time.sleep (2)
    driver.find_elements (By.XPATH,'//input')[1].send_keys (info.xPassword)
    driver.find_elements (By.XPATH, '//*[@role="button"]')[3].click ()
    time.sleep (1.5)

# LOGGING IN TO MICROSOFT LISTS
def listLogIn (driver, info):
    driver.get ("https://lists.live.com/?listId=029f2ab5de3e47f99b768906150d9e3d%5F7427cb0e3787e72f")
    time.sleep (3)

    try:
        element = driver.find_element (By.XPATH, '//input[@id="i0116"]')
    except:
        driver.find_element (By.XPATH, '//input[@id="usernameEntry"]').send_keys (info.lEmail)
        driver.find_element (By.XPATH, '//button[@type="submit"]').click ()
    else:
        element.send_keys (info.lEmail)
        driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()
    time.sleep (1)

    try:
        element = driver.find_element (By.XPATH, '//input[@id="i0118"]')
    except:
        driver.find_element (By.XPATH, '//input[@id="passwordEntry"]').send_keys (info.lEmail)
        driver.find_element (By.XPATH, '//button[@type="submit"]').click ()
    else:
        element.send_keys (info.lPassword)
        driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()
    time.sleep (1)

    try:
        element = driver.find_element (By.XPATH, '//button[@id="declineButton"]')
    except:
        driver.find_element (By.XPATH, '//button[@data-testid="secondaryButton"]').click ()
    else:
        element.click ()
    time.sleep (2)

    # element = driver.find_element (By.XPATH, '//input[@id="i0116"]')
    # if element.is_displayed ():
    #     element.send_keys (info.lEmail)
    #     driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()
    # else:
    #     driver.find_element (By.XPATH, '//input[@id="usernameEntry"]').send_keys (info.lEmail)
    #     driver.find_element (By.XPATH, '//button[@type="submit"]').click ()
    # time.sleep (1)

    # element = driver.find_element (By.XPATH, '//input[@id="i0118"]')
    # if element.is_displayed ():
    #     element.send_keys (info.lPassword)
    #     driver.find_element (By.XPATH, '//button[@id="idSIButton9"]').click ()
    # else:
    #     driver.find_element (By.XPATH, '//input[@id="passwordEntry"]').send_keys (info.lEmail)
    #     driver.find_element (By.XPATH, '//button[@type="submit"]').click ()
    # time.sleep (1)

    # element = driver.find_element (By.XPATH, '//button[@id="declineButton"]')
    # if element.is_displayed ():
    #     element.click ()
    # else:
    #     driver.find_element (By.XPATH, '//button[@data-testid="secondaryButton"]').click ()
    # time.sleep (2)


# SCRAPE ACCOUNT INFORMATION 
def scrapeAccounts (driver, info):
    list = []

    for account in info.accounts:
        driver.get (account)
        time.sleep (1)
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
# <button type="button" role="menuitem" class="item_a4f5cb66 primary_a4f5cb66" data-id="new" data-automationid="newCommand" tabindex="0" data-actions="[{&quot;key&quot;:&quot;cmdbar-itm-click&quot;,&quot;data&quot;:&quot;new&quot;}]"><span class="container_a4f5cb66"><i role="presentation" class="icon_ea705809 css-45 " name="CalculatorAddition" data-icon-name="CalculatorAddition" aria-hidden="true"></i><span class="text_a4f5cb66 textWithoutSubMenu_a4f5cb66">Add new item</span></span></button>
    # for item in data:
    # driver.find_element (By.XPATH, '//*[data-id="new"]').click ()
    driver.switch_to.active_element.send_keys (Keys.TAB)
    driver.switch_to.active_element.send_keys (Keys.ENTER)
    time.sleep (2)
    driver.find_element (By.XPATH, '//input[@id="TextField13]').send_keys (info.data[0][0])
    driver.find_element (By.XPATH, '//input[@id="TextField18]').send_keys (info.data[0][1])
    driver.find_element (By.XPATH, '//div[@id="displayView-displayDiv-MaxNumberofMedia"]').send_keys (info.data[0][2])
    driver.find_element (By.XPATH, '//div[@id="Flyout-0"]').click ()
    # driver.find_element (By.XPATH, '//button[@data-automationid="ReactClientFormSaveButton"]').click ()

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



class information:
    def __init__ (self, xEmail: str, xUsername: str, xPassword: str, lEmail: str, lPassword: str, accounts: list):
        self.xEmail = xEmail
        self.xPassword = xPassword
        self.xUsername = xUsername
        self.lEmail = lEmail
        self.lPassword = lPassword
        self.accounts = []

        for account in accounts:
            self.accounts.append ("https://x.com/" + account + "/media")




if __name__ == "__main__":
    parser = argparse.ArgumentParser ("Creating a list of accounts to scrape their images")
    parser.add_argument ('-nw', '--no_window', action="store_true")
    parser.add_argument ('-xe', '--xEmail',  metavar="xEmail", type=str, nargs=1, help="x email to log in", default="deadone1001@gmail.com")
    parser.add_argument ('-un', '--username',  metavar="username", type=str, nargs=1, help="x username to log in", default="deadone1001")
    parser.add_argument ('-xp', '--xPassword',  metavar="xPassword", type=str, nargs=1, help="x password to log in", default="1234567890qwerpoiuty..")
    parser.add_argument ('-le', '--lEmail', metavar='lEmail', type=str, nargs=1, help='lists email to log in', default='')
    parser.add_argument ('-lp', '--lPassword', metavar='lPassword', type=str, nargs=1, help='lists password to log in', default='')
    parser.add_argument ('-u', '--users',  metavar="users", type=str, nargs='+', help="Users to parse info from")

    args = parser.parse_args ()

    # Initialize information object
    if isinstance (args.xEmail, list):          args.xEmail = args.xEmail[0]
    if isinstance (args.username, list):      args.username = args.username[0]
    if isinstance (args.xPassword, list):      args.xPassword = args.xPassword[0]
    if isinstance (args.lEmail, list):          args.lEmail = args.lEmail[0]
    if isinstance (args.lPassword, list):      args.lPassword = args.lPassword[0]
    info = information (args.xEmail, args.username, args.xPassword, args.lEmail, args.lPassword, args.users)

    # Initialize webdriver
    print ("BEGINNING INITIALIZATION OF WEBDRIVER")
    options = baseOptions (args.no_window)
    driver = webdriver.Chrome (options=options, service=ChromeService (ChromeDriverManager ().install ()))
    print ("FINISHED INITIALIZATION OF WEBDRIVER")

    # Log in to x and lists
    # print ("BEGINNING LOG IN PROCESS OF X")
    # xLogIn (driver, info)
    # print ("FINISHED LOG IN PROCESS OF X")

    print ("BEGINNING LOG IN PROCESS OF LISTS")
    listLogIn (driver, info)
    print ("FINISHED LOG IN PROCESS OF LISTS")

    # # Extract all the necessary information for the list
    # print ("BEGINNING DATA SCRAPING PROCESS")
    # data = scrapeAccounts (driver, info)
    # print ("FINISHED DATA SCRAPING PROCESS")

    data = [['https://x.com/yuzu_mog/media', 'yuzu_mog', 2029], ['https://x.com/fallinfIowr/media', 'fallinfIowr', 91], ['https://x.com/OAZ0424SR/media', 'OAZ0424SR', 87]]

    # # Upload all the information to the list
    print ("BEGINNING DATA UPLOAD PROCESS")
    uploadData (driver, data)
    print ("FINISHED DATA UPLOADING PROCESS")

    # print ("FINISHED ENTIRE PROCESS :)")
