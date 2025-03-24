import json
import os


import json
import os

class Saver:
    def __init__(self, filename):
        self.filename = filename

    def read(self):
        if not os.path.exists(self.filename):
            return []  # Return an empty list if file doesn't exist

        try:
            with open(self.filename, "r") as file:
                data = file.read().strip()
                return json.loads(data) if data else []
        except json.JSONDecodeError:
            print("⚠️ Warning: passwords.txt contains invalid JSON. Resetting to an empty list.")
            return []

    def save(self, data):
        with open(self.filename, "w") as file:
            json.dump(data, file, indent=4)

















































#class Saver:
#    def __init__(self, file):
#        self.file = file
#
#        
#        if not os.path.exists(self.file):
#            with open(self.file, "w") as f:
#                json.dump([], f, indent=4)
#
#    def save(self, data):
#        """Saves data to the file."""
#        with open(self.file, "w") as file:  
#            json.dump(data, file, indent=4)
#
#    def read(self):
#        """Reads data from the file."""
#        if os.stat(self.file).st_size == 0:  
#            return []
#        
#        with open(self.file, "r") as file:
#            return json.load(file)  
#