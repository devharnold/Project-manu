import pyotp
import qrcode
import os
from encrypt import AES256
from save import Saver


TOTP_SECRET_FILE = "totp_secret.txt"
QR_CODE_FILE = "2fa_qr.png"

def load_totp_secret():
    """Load or generate a TOTP secret key."""
    if os.path.exists(TOTP_SECRET_FILE):
        with open(TOTP_SECRET_FILE, "r") as file:
            return file.read().strip()
    else:
        secret = pyotp.random_base32()
        with open(TOTP_SECRET_FILE, "w") as file:
            file.write(secret)
        return secret

TOTP_SECRET = load_totp_secret()


masterPasswordCheck = b'LN8lPPibuqkcQUGj/Ca06wvNYrEa8pb2jSs/5pB+Rkw='


saver = Saver("passwords.txt")
passwords = saver.read()
loggedIn = False

def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")

def generate_qr():
    """Generate and save a QR code for 2FA setup."""
    uri = pyotp.TOTP(TOTP_SECRET).provisioning_uri(name="YourApp", issuer_name="YourCompany")
    qr = qrcode.make(uri)
    qr.save(QR_CODE_FILE)  
    print("\n📲 Scan the QR code in Google Authenticator.")
    

    if os.name == "nt":  
        os.system(f"start {QR_CODE_FILE}")
    elif os.name == "posix":  
        os.system(f"xdg-open {QR_CODE_FILE}")

def verify_2fa():
    """Verify the user's 2FA code"""
    totp = pyotp.TOTP(TOTP_SECRET)
    code = input("Enter your 2FA code: ")

    if totp.verify(code):
        print("✅ 2FA verified successfully!")
        return True
    else:
        print("❌ Invalid 2FA code")
        return False

# ---------------------- Login Process ----------------------
while True:
    if not loggedIn:
        print("Master Password: ", end="")
        masterPassword = input()

        encrypter = AES256(masterPassword)

        if encrypter.encrypt("textToMatch") != masterPasswordCheck:
            print("❌ Password Incorrect")
            input("Press Enter to try again...")
            continue
        
        # Show QR code if this is the first time setting up 2FA
        if not os.path.exists(QR_CODE_FILE):
            print("\n🔐 Setting up Two-Factor Authentication...")
            generate_qr()
            input("Press Enter after scanning the QR code...")

        # Verify 2FA
        if not verify_2fa():
            input("Press Enter to try again...")
            continue

        loggedIn = True  # ✅ Correct indentation

    clear_screen()
    print("1. Find password")
    print("2. Add password")
    print("3. Delete password")
    print("4. Show QR Code 🔐")  # New option to display QR Code again

    print("\nChoice:", end=" ")
    try:
        choice = int(input())
    except ValueError:
        print("❌ Invalid input. Enter a number from 1-4.")
        input("Press Enter to continue...")
        continue

    if choice not in [1, 2, 3, 4]:
        print("❌ Choice needs to be a number from 1-4")
        input("Press Enter to continue...")
        continue

    if choice == 4:
        generate_qr()  # Generate and show QR code again
        continue

    print("Application Name:", end=" ")
    app = input()

    if choice == 1:
        found = False
        for entry in passwords:
            if app in encrypter.decrypt(entry[0]):
                print("\n-------------------------------")
                print(f"Application: {encrypter.decrypt(entry[0])}")
                print(f"Password: {encrypter.decrypt(entry[1])}")
                found = True
        if not found:
            print("No password found for that application.")
        input("Press Enter to continue...")

    elif choice == 2:
        print("Password:", end=" ")
        password = input()

        passwords.append([encrypter.encrypt(app).decode(), encrypter.encrypt(password).decode()])
        saver.save(passwords)  
        print("✅ Password added successfully!")
        input("Press Enter to continue...")

    elif choice == 3:
        for entry in passwords:
            if app == encrypter.decrypt(entry[0]):
                print(f"Are you sure you want to delete '{app}'? [Y/N]:", end=" ")
                confirm = input().strip().lower()

                if confirm == "y":
                    passwords.remove(entry)
                    saver.save(passwords)
                    print("✅ Password deleted successfully.")
                else:
                    print("❌ Deletion cancelled.")
                break
        input("Press Enter to continue...")

