import base64
import hashlib
from Crypto.Cipher import AES  


class AES256:
    def __init__(self, key):

      self.key = hashlib.sha256(key.encode()).digest()
      self.iv = b',\xdf%<\xf8\x9b\xba\xa9\x1cAA\xa3\xfc&\xb4\xeb'

    def encrypt(self, plaintext):
        cipher = AES.new(self.key, AES.MODE_CBC, self.iv)

        padding_length = 16 - (len(plaintext) % 16)
        plaintext += chr(padding_length) * padding_length

        ciphertext = cipher.encrypt(plaintext.encode())
        return base64.b64encode(self.iv + ciphertext)

        def decrypt(self, ciphertext):
            ciphertext = base64.b64decode(ciphertext)

            iv = ciphertext(16)
            cipher = AES.new(self.key, AES.MODE_CBC, iv)
            
            plaintext = cipher.decrypt(ciphertext[16:]).decode()
            padding_length = ord(plaintext[-1])
            return plaintext[:-padding_length]