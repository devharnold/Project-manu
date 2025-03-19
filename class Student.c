class Student:
    def __init__(self, name, reg_no, course, department):
        self.name = name
        self.reg_no = reg_no
        self.course = course
        self.department = department
        self.scores = []  # List to store scores

    def add_score(self, score):
        self.scores.append(score)

    def calculate_average(self):
        if not self.scores:
            return 0
        return sum(self.scores) / len(self.scores)

    def get_grade(self):
        average_score = self.calculate_average()
        if 90 <= average_score <= 100:
            return 'A'
        elif 80 <= average_score < 90:
            return 'B'
        elif 70 <= average_score < 80:
            return 'C'
        elif 60 <= average_score < 70:
            return 'D'
        else:
            return 'FAIL'

def main():
    students = []  # List to store student objects

    def add_student():
        name = input("Enter student name: ")
        reg_no = input("Enter registration number: ")
        course = input("Enter course: ")
        department = input("Enter department: ")

        student = Student(name, reg_no, course, department)
        students.append(student)
        print(f"{name} ({reg_no}) added successfully!")

    def display_student(reg_no):
        for student in students:
            if student.reg_no == reg_no:
                print(f"Name: {student.name}")
                print(f"Course: {student.course}")
                print(f"Department: {student.department}")
                print(f"Average Score: {student.calculate_average()}")
                print(f"Grade: {student.get_grade()}")
                return
        print(f"Student with registration number {reg_no} not found.")

    # Implement other methods (update, delete, search, sort) as needed

    while True:
        print("\nMenu:")
        print("1. Add Student")
        print("2. Display Student Details")
        print("3. Update Student Details")
        print("4. Delete Student")
        print("5. Search Students")
        print("6. Sort Students")
        print("7. Exit")

        choice = int(input("Enter your choice: "))
        if choice == 1:
            add_student()
        elif choice == 2:
            reg_no = input("Enter registration number to display details: ")
            display_student(reg_no)
        # Implement other menu options here

        elif choice == 7:
            print("Exiting program. Goodbye!")
            break
        else:
            print("Invalid choice. Please select a valid option.")

if __name__ == "__main__":
    main()

         

