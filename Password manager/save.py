import json
import os

class Saver:
    def __init__(self, file):
        self.file = file

        
        if not os.path.exists(self.file):
            with open(self.file, "w") as f:
                json.dump([], f, indent=4)

    def save(self, data):
        """Saves data to the file."""
        with open(self.file, "w") as file:  
            json.dump(data, file, indent=4)

    def read(self):
        """Reads data from the file."""
        if os.stat(self.file).st_size == 0:  
            return []
        
        with open(self.file, "r") as file:
            return json.load(file)  
