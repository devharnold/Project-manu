import pyotp

# Generate a new secret key (run this only once and store the key securely)
TOTP_SECRET = pyotp.random_base32()

print("Your 2FA Secret Key:", TOTP_SECRET)
